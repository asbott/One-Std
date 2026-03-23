#ifndef _UNICODE_H
#define _UNICODE_H

#ifndef _BASE_H
#include "base.h"
#endif // _BASE_H

#ifndef _STRING_H
#include "string.h"
#endif // _STRING_H

#define UTF16_SURROGATE_HIGH_START  0xD800
#define UTF16_SURROGATE_HIGH_END    0xDBFF
#define UTF16_SURROGATE_LOW_START   0xDC00
#define UTF16_SURROGATE_LOW_END     0xDFFF
#define UTF16_SURROGATE_OFFSET      0x10000
#define UTF16_SURROGATE_MASK        0x3FF


#define UNI_REPLACEMENT_CHAR 0x0000FFFD
#define UNI_MAX_UTF32        0x7FFFFFFF
#define UNI_MAX_UTF16        0x0010FFFF
#define SURROGATES_START     0xD800
#define SURROGATES_END       0xDFFF

typedef struct {
	u32 utf32;
	s64 continuation_bytes;
	bool reached_end;
	bool error;
} To_Utf32_Result;
typedef struct {
    u32 utf16;
    s64 continuation_bytes;
    bool reached_end;
    bool error;
} To_Utf16_Result;
typedef struct {
    u8  utf8[4];
    s64 bytes_written;
    bool error;
} To_Utf8_Result;

typedef struct {
    u16 *data;
    u64 byte_count;
} Utf16_Iterator;

To_Utf32_Result one_utf8_to_utf32(u8 *s, u64 source_length, bool strict);
To_Utf16_Result one_utf8_to_utf16(u8 *s, u64 source_length, bool strict);
To_Utf8_Result one_utf32_to_utf8(u32 ch, bool strict);
To_Utf16_Result one_utf32_to_utf16(u32 ch, bool strict);
To_Utf32_Result one_utf16_to_utf32(u16 *s, u64 source_length, bool strict);
u32 next_utf16(Utf16_Iterator *it);

u32 next_utf8(string *s);

#ifdef OSTD_IMPL

unit_local const u8 trailing_bytes_for_utf8[] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};
unit_local const u8 utf8_inital_byte_mask[] = { 0x7F, 0x1F, 0x0F, 0x07, 0x03, 0x01 };

// Convert single utf8 character to a single utf32 codepoint
To_Utf32_Result one_utf8_to_utf32(u8 *s, u64 source_length, bool strict) {
    s64 continuation_bytes = trailing_bytes_for_utf8[s[0]];

    if (continuation_bytes + 1 > (s64)source_length) {
        return (To_Utf32_Result){UNI_REPLACEMENT_CHAR, (s64)source_length, true, true};
    }

    u32 ch = s[0] & utf8_inital_byte_mask[continuation_bytes];

    for (s64 i = 1; i <= continuation_bytes; i++) {  // Do nothing if it is 0.
        ch = ch << 6;
        if (strict) if ((s[i] & 0xC0) != 0x80)
            return (To_Utf32_Result){ UNI_REPLACEMENT_CHAR, 1, true, true };
    	ch |= s[i] & 0x3F;
    }

    if (strict) {
        if (ch > UNI_MAX_UTF16 ||
          (SURROGATES_START <= ch && ch <= SURROGATES_END) ||
          (                   ch <= 0x0000007F && continuation_bytes != 0) ||
          (ch > 0x0000007F && ch <= 0x000007FF && continuation_bytes != 1) ||
          (ch > 0x000007FF && ch <= 0x0000FFFF && continuation_bytes != 2) ||
          (ch > 0x0000FFFF &&                     continuation_bytes != 3) ||
          continuation_bytes > 3) {
            return (To_Utf32_Result){UNI_REPLACEMENT_CHAR, continuation_bytes+1, true, true};
        }
    }

    if (ch > UNI_MAX_UTF32) {
	   return (To_Utf32_Result){ UNI_REPLACEMENT_CHAR, continuation_bytes+1, true, true };
    }

	return (To_Utf32_Result){ ch, continuation_bytes+1, false, false };
}

// Convert single utf8 character to utf16 code units
To_Utf16_Result one_utf8_to_utf16(u8 *s, u64 source_length, bool strict) {
    To_Utf32_Result utf32_res = one_utf8_to_utf32(s, source_length, strict);
    To_Utf16_Result res = {0};
    res.continuation_bytes = utf32_res.continuation_bytes;
    res.reached_end = utf32_res.reached_end;
    res.error = utf32_res.error;

    u32 ch = utf32_res.utf32;
    if (res.error) ch = UNI_REPLACEMENT_CHAR;

    if (ch <= 0xFFFF) {
        res.utf16 = ch;
        return res;
    }

    if (ch <= UNI_MAX_UTF16) {
        u32 v = ch - UTF16_SURROGATE_OFFSET;
        u16 hi = (u16)(UTF16_SURROGATE_HIGH_START + ((v >> 10) & UTF16_SURROGATE_MASK));
        u16 lo = (u16)(UTF16_SURROGATE_LOW_START  + ( v        & UTF16_SURROGATE_MASK));
        res.utf16 = ((u32)hi << 16) | (u32)lo;
        return res;
    }

    res.utf16 = UNI_REPLACEMENT_CHAR;
    res.error = true;
    return res;
}


To_Utf8_Result one_utf32_to_utf8(u32 ch, bool strict) {
    To_Utf8_Result res = {0};

    if (strict) {
        if (ch > UNI_MAX_UTF16) {
            ch = UNI_REPLACEMENT_CHAR;
            res.error = true;
        }
        if (SURROGATES_START <= ch && ch <= SURROGATES_END) {
            ch = UNI_REPLACEMENT_CHAR;
            res.error = true;
        }
    } else {
        if (ch > UNI_MAX_UTF16) {
            ch = UNI_REPLACEMENT_CHAR;
            res.error = true;
        }
        if (SURROGATES_START <= ch && ch <= SURROGATES_END) {
            ch = UNI_REPLACEMENT_CHAR;
            res.error = true;
        }
        if (ch > UNI_MAX_UTF32) {
            ch = UNI_REPLACEMENT_CHAR;
            res.error = true;
        }
    }

    if (ch <= 0x7F) {
        res.utf8[0] = (u8)ch;
        res.bytes_written = 1;
        return res;
    }

    if (ch <= 0x7FF) {
        res.utf8[0] = (u8)(0xC0 | (ch >> 6));
        res.utf8[1] = (u8)(0x80 | (ch & 0x3F));
        res.bytes_written = 2;
        return res;
    }

    if (ch <= 0xFFFF) {
        res.utf8[0] = (u8)(0xE0 | (ch >> 12));
        res.utf8[1] = (u8)(0x80 | ((ch >> 6) & 0x3F));
        res.utf8[2] = (u8)(0x80 | (ch & 0x3F));
        res.bytes_written = 3;
        return res;
    }

    res.utf8[0] = (u8)(0xF0 | (ch >> 18));
    res.utf8[1] = (u8)(0x80 | ((ch >> 12) & 0x3F));
    res.utf8[2] = (u8)(0x80 | ((ch >> 6) & 0x3F));
    res.utf8[3] = (u8)(0x80 | (ch & 0x3F));
    res.bytes_written = 4;
    return res;
}

To_Utf16_Result one_utf32_to_utf16(u32 ch, bool strict) {
    To_Utf16_Result res = {0};
    res.continuation_bytes = 1;

    if (strict) {
        if (ch > UNI_MAX_UTF16) {
            res.utf16 = UNI_REPLACEMENT_CHAR;
            res.error = true;
            return res;
        }
        if (SURROGATES_START <= ch && ch <= SURROGATES_END) {
            res.utf16 = UNI_REPLACEMENT_CHAR;
            res.error = true;
            return res;
        }
    } else {
        if (ch > UNI_MAX_UTF16) {
            res.utf16 = UNI_REPLACEMENT_CHAR;
            res.error = true;
            return res;
        }
        if (SURROGATES_START <= ch && ch <= SURROGATES_END) {
            res.utf16 = UNI_REPLACEMENT_CHAR;
            res.error = true;
            return res;
        }
        if (ch > UNI_MAX_UTF32) {
            res.utf16 = UNI_REPLACEMENT_CHAR;
            res.error = true;
            return res;
        }
    }

    if (ch <= 0xFFFF) {
        res.utf16 = ch;
        return res;
    }

    // surrogate pair, pack as (high<<16)|low
    ch -= UTF16_SURROGATE_OFFSET;
    u16 hi = (u16)(UTF16_SURROGATE_HIGH_START + ((ch >> 10) & UTF16_SURROGATE_MASK));
    u16 lo = (u16)(UTF16_SURROGATE_LOW_START  + ( ch        & UTF16_SURROGATE_MASK));

    res.utf16 = ((u32)hi << 16) | (u32)lo;
    return res;
}

To_Utf32_Result one_utf16_to_utf32(u16 *s, u64 source_bytes, bool strict) {
    if (source_bytes <= 0) {
        return (To_Utf32_Result){ UNI_REPLACEMENT_CHAR, 0, true, true };
    }

    u32 w1 = (u32)s[0];

    if (strict) {
        if (w1 > 0xFFFF) {
            return (To_Utf32_Result){ UNI_REPLACEMENT_CHAR, 2, true, true };
        }
    }

    // High surrogate
    if (UTF16_SURROGATE_HIGH_START <= w1 && w1 <= UTF16_SURROGATE_HIGH_END) {
        if (source_bytes < 4) {
            return (To_Utf32_Result){ UNI_REPLACEMENT_CHAR, (s64)source_bytes, true, true };
        }

        u32 w2 = (u32)s[1];

        if (UTF16_SURROGATE_LOW_START <= w2 && w2 <= UTF16_SURROGATE_LOW_END) {
            u32 ch = (((w1 - UTF16_SURROGATE_HIGH_START) & UTF16_SURROGATE_MASK) << 10);
            ch |= ((w2 - UTF16_SURROGATE_LOW_START) & UTF16_SURROGATE_MASK);
            ch += UTF16_SURROGATE_OFFSET;

            if (strict) {
                if (ch > UNI_MAX_UTF16) {
                    return (To_Utf32_Result){ UNI_REPLACEMENT_CHAR, 4, true, true };
                }
            }

            if (ch > UNI_MAX_UTF32) {
                return (To_Utf32_Result){ UNI_REPLACEMENT_CHAR, 4, true, true };
            }

            return (To_Utf32_Result){ ch, 4, false, false };
        }

        // High surrogate not followed by low surrogate
        return (To_Utf32_Result){ UNI_REPLACEMENT_CHAR, 2, true, true };
    }

    // Low surrogate without preceding high surrogate
    if (UTF16_SURROGATE_LOW_START <= w1 && w1 <= UTF16_SURROGATE_LOW_END) {
        return (To_Utf32_Result){ UNI_REPLACEMENT_CHAR, 2, true, true };
    }

    // BMP non-surrogate
    if (strict) {
        if (SURROGATES_START <= w1 && w1 <= SURROGATES_END) {
            return (To_Utf32_Result){ UNI_REPLACEMENT_CHAR, 2, true, true };
        }
        if (w1 > UNI_MAX_UTF16) {
            return (To_Utf32_Result){ UNI_REPLACEMENT_CHAR, 2, true, true };
        }
    }

    if (w1 > UNI_MAX_UTF32) {
        return (To_Utf32_Result){ UNI_REPLACEMENT_CHAR, 2, true, true };
    }

    return (To_Utf32_Result){ w1, 2, false, false };
}

u32 next_utf8(string *s) {
    if (s->count == 0) return 0;
    To_Utf32_Result res = one_utf8_to_utf32(s->data, s->count, true);

    s->data  += (u64)res.continuation_bytes;
    s->count -= (u64)res.continuation_bytes;
    
    assert(res.utf32 <= UNI_MAX_UTF32);

    return res.reached_end || res.error ? 0 : res.utf32;
}

u32 next_utf16(Utf16_Iterator *it) {

    if (it->byte_count == 0) return 0;

    To_Utf32_Result res = one_utf16_to_utf32(it->data, it->byte_count, true);

    it->data = (u16*)((u8*)it->data + (u64)res.continuation_bytes);
    it->byte_count -= (u64)res.continuation_bytes;

    assert(res.utf32 <= UNI_MAX_UTF32);

    return res.reached_end || res.error ? 0 : res.utf32;
}

#endif //OSTD_IMPL


#endif // _UNICODE_H
