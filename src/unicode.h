#if 0
#include "ostd.h" // For syntax highlighting.
#endif

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
} Utf8_To_Utf32_Result;
typedef struct {
    u32 utf32;
    s64 continuation_bytes;
    bool reached_end;
    bool error;
} Utf8_To_Utf16_Result;

Utf8_To_Utf32_Result one_utf8_to_utf32(u8 *s, s64 source_length, bool strict);
Utf8_To_Utf16_Result one_utf8_to_utf16(u8 *s, s64 source_length, bool strict);

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
Utf8_To_Utf32_Result one_utf8_to_utf32(u8 *s, s64 source_length, bool strict) {
    s64 continuation_bytes = trailing_bytes_for_utf8[s[0]];

    if (continuation_bytes + 1 > source_length) {
        return (Utf8_To_Utf32_Result){UNI_REPLACEMENT_CHAR, source_length, true, true};
    }

    u32 ch = s[0] & utf8_inital_byte_mask[continuation_bytes];

    for (s64 i = 1; i <= continuation_bytes; i++) {  // Do nothing if it is 0.
        ch = ch << 6;
        if (strict) if ((s[i] & 0xC0) != 0x80)  return (Utf8_To_Utf32_Result){UNI_REPLACEMENT_CHAR, i - 1, true, true};
    	ch |= s[i] & 0x3F;
    }

    if (strict) {
        if (ch > UNI_MAX_UTF16 ||
          (SURROGATES_START <= ch && ch <= SURROGATES_END) ||
          (ch <= 0x0000007F && continuation_bytes != 0) ||
          (ch <= 0x000007FF && continuation_bytes != 1) ||
          (ch <= 0x0000FFFF && continuation_bytes != 2) ||
          continuation_bytes > 3) {
            return (Utf8_To_Utf32_Result){UNI_REPLACEMENT_CHAR, continuation_bytes+1, true, true};
        }
    }

    if (ch > UNI_MAX_UTF32) {
        ch = UNI_REPLACEMENT_CHAR;
    }

	return (Utf8_To_Utf32_Result){ ch, continuation_bytes+1, false, false };
}

// Convert single utf8 character to utf16 code units
Utf8_To_Utf16_Result one_utf8_to_utf16(u8 *s, s64 source_length, bool strict) {
    Utf8_To_Utf32_Result utf32_res = one_utf8_to_utf32(s, source_length, strict);
    Utf8_To_Utf16_Result res = {0};
    res.utf32 = utf32_res.utf32;
    res.continuation_bytes = utf32_res.continuation_bytes;
    res.reached_end = utf32_res.reached_end;
    res.error = utf32_res.error;

    if (res.error) {
        res.utf32 = UNI_REPLACEMENT_CHAR;
    }

    if (res.utf32 <= 0xFFFF) {
        res.utf32 = res.utf32;
    }
    else if (res.utf32 <= UNI_MAX_UTF16) {
        res.utf32 -= UTF16_SURROGATE_OFFSET;
        res.utf32 = UTF16_SURROGATE_HIGH_START + ((res.utf32 >> 10) & UTF16_SURROGATE_MASK);
        res.utf32 = (UTF16_SURROGATE_LOW_START) | (res.utf32 & UTF16_SURROGATE_MASK);
    }
    else {
        res.utf32 = UNI_REPLACEMENT_CHAR;
    }

    return res;
}

#endif //OSTD_IMPL