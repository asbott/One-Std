
#if 0
#include "ostd.h"
#endif

typedef enum Ol_Result {
    OL_OK,
    OL_UNRESOLVED_TYPE,
    OL_UNEXPECTED_TOKEN
} Ol_Result;

typedef enum Ol_Target {
    OL_TARGET_SPIRV,
} Ol_Target;
typedef enum Ol_Program_Kind {
    OL_PROGRAM_GPU_FRAGMENT,
    OL_PROGRAM_GPU_VERTEX,
    OL_PROGRAM_GPU_COMPUTE,
} Ol_Program_Kind;

typedef struct Ol_Compile_Desc {
    Ol_Target target;
    Ol_Program_Kind program_kind;
    string code_text;
} Ol_Compile_Desc;

Ol_Result ol_compile(Allocator a, Ol_Compile_Desc desc, void **pcode, u64 *pcode_size, string *err_log);

#ifdef OSTD_IMPL

typedef enum Ol_Token_Kind {
	OL_TOKEN_KIND_UNKNOWN,
	
	OL_TOKEN_KIND_PUNCTUATION_START,
	
	OL_TOKEN_KIND_COLON = ':',
	OL_TOKEN_KIND_DOLLAR = '$',
	OL_TOKEN_KIND_LPAREN = '(',
	OL_TOKEN_KIND_RPAREN = ')',
	OL_TOKEN_KIND_STAR = '*',
	OL_TOKEN_KIND_DOT = '.',
	
	OL_TOKEN_KIND_IDENTIFIER = 128,
	
	OL_TOKEN_KIND_INT_LITERAL,
	OL_TOKEN_KIND_FLOAT_LITERAL,
	
	OL_TOKEN_KIND_EOF,
	
	OL_TOKEN_KIND_PUNCTUATION_END = OL_TOKEN_KIND_IDENTIFIER,
	
} Ol_Token_Kind;

unit_local inline string _ol_stringify_token(Ol_Token_Kind kind) {
	switch (kind) {
		case OL_TOKEN_KIND_IDENTIFIER: return STR("Identifier");
		case OL_TOKEN_KIND_INT_LITERAL: return STR("Int Literal");
		case OL_TOKEN_KIND_FLOAT_LITERAL: return STR("Float Literal");
		case OL_TOKEN_KIND_COLON:  return STR(":");
		case OL_TOKEN_KIND_DOLLAR: return STR("$");
		case OL_TOKEN_KIND_LPAREN: return STR("(");
		case OL_TOKEN_KIND_RPAREN: return STR(")");
		case OL_TOKEN_KIND_STAR:   return STR("*");
		case OL_TOKEN_KIND_DOT:    return STR(".");
		case OL_TOKEN_KIND_EOF:    return STR("<eof>");
		case OL_TOKEN_KIND_UNKNOWN: //fallthrough
		case OL_TOKEN_KIND_PUNCTUATION_START: //fallthrough
		default: return STR("");
	}
	return STR("");
}

typedef struct Ol_Token {
	Ol_Token_Kind kind;	
	u64 source_pos;
	u64 length;
} Ol_Token;

typedef enum Ol_Type {
	OL_TYPE_INVALID,
	OL_TYPE_FLOAT32,
	OL_TYPE_UINT32,
	OL_TYPE_V3F32,
	OL_TYPE_V4F32,
} Ol_Type;

typedef enum Ol_Storage_Flag {
	OL_STORAGE_DEFAULT = 0,
	OL_STORAGE_INPUT = 1 << 0,
	OL_STORAGE_OUTPUT = 1 << 1,
} Ol_Storage_Flag;

struct Ol_Expr;
typedef struct Ol_Value_Decl {
    Ol_Type type;
	string type_ident;
	Ol_Storage_Flag storage_flags;
	string ident;
	struct Ol_Expr *init_expr;
} Ol_Value_Decl;

typedef enum Ol_Expr_Kind {
	OL_EXPR_OP,
	OL_EXPR_DECL,
	OL_EXPR_LITERAL_FLOAT,
	OL_EXPR_LITERAL_INT,
	OL_EXPR_TYPE, // When casting
} Ol_Expr_Kind;

typedef enum Ol_Op_Kind {
	OL_OP_INVALID = 0,
	OL_OP_CAST,
	OL_OP_MUL,
	OL_OP_DIV,
	OL_OP_ADD,
	OL_OP_SUB,
	OL_OP_SET,
} Ol_Op_Kind;
typedef struct Ol_Expr {
    Ol_Expr_Kind kind;
	union {
		s64 decl_index;
		struct {  s64 result_vnum; struct Code_Expr *lhs; struct Code_Expr *rhs; Ol_Op_Kind op_kind; } op;
		struct { union { u64 lit_int; f32 lit_flt; } v; s64 imm_index; } lit;
		Ol_Type type;
	} val;
	Ol_Type cast_to_type;
	s64 vnum;
} Ol_Expr;

typedef enum Ol_Node_Kind {
    OL_NODE_VALUE_DECL,  
    OL_NODE_EXPR,  
} Ol_Node_Kind;

typedef struct Ol_Node {
    Ol_Node_Kind kind;
    union {
        Ol_Value_Decl value_decl;
        Ol_Expr expr;
    } val;
} Ol_Node;

typedef struct Ol_Compiler {
    string source;

    Arena token_arena;
    Ol_Token *tokens;
    u64 token_count;
    
    Arena node_arena;
    
    // todo(charlie)
    Ol_Node *top_nodes[8196];
    u64 top_node_count;
    
    string err_log;
    
    s64 next_vnum;
    
} Ol_Compiler;

unit_local void _ol_tokenize(Ol_Compiler *compiler) {
    string source = compiler->source;
    u8 *p = source.data;
	while (p < source.data + source.count) {
		u8 *end = source.data + source.count;
		while (*p == ' ' || *p == '\n') {  assert(*p != '\r'); p += 1; }
		
		

		while (p[0] == '/' && (p[1] == '/' || p[1] == '*')) {
			while (p[0] == '/' && p[1] == '/') {
				while (p < end && *p != '\n') {  p += 1; }
				if (*p == '\n') p += 1;
			}
			while (*p == ' ' || *p == '\n') {  assert(*p != '\r'); p += 1; }
			u32 depth = 0;
			while (p[0] == '/' && p[1] == '*') {
				while ((p+1) < end && !(p[0] == '*' && p[1] == '/' && depth == 1)) {  
					if (p[0] == '/' && p[1] == '*') depth += 1;
					if (p[0] == '*' && p[1] == '/') depth -= 1;
					p += 1;
				}
				if (p[0] == '*' && p[1] == '/') {  p += 2; }
			}
			while (*p == ' ' || *p == '\n') {  assert(*p != '\r'); p += 1; }
		}
		while (*p == ' ' || *p == '\n') {  assert(*p != '\r'); p += 1; }
		
		
		Ol_Token *token = (Ol_Token*)arena_push(&compiler->token_arena, sizeof(Ol_Token));
		compiler->token_count += 1;
		token->source_pos = (u64)(p-source.data);

		if (is_alpha(*p) || *p == '_') {
			
			while (is_alpha(*p) || *p == '_' || is_digit(*p)) {p += 1;}
			
			token->length = (u64)(p-source.data)-token->source_pos;
			token->kind = OL_TOKEN_KIND_IDENTIFIER;
			continue;
		}
		
		if (is_digit(*p)) {
			bool dot = false;
			
			while (is_digit(*p) || *p == '.') {
				if (*p == '.') {
					if (!dot) dot = true;
					else {
						break;
					}
				}
				p += 1;
			}
			if (dot && *(p-1) == '.') {
				dot = false;
				p--;
			}
			token->length = (u64)(p-source.data)-token->source_pos;
			token->kind = dot ? OL_TOKEN_KIND_FLOAT_LITERAL : OL_TOKEN_KIND_INT_LITERAL;
			continue;
		}
		
		if (*p >= OL_TOKEN_KIND_PUNCTUATION_START && *p < OL_TOKEN_KIND_PUNCTUATION_END) {
			token->kind = (Ol_Token_Kind)*(p++);
			token->length = (u64)(p-source.data)-token->source_pos;
			continue;
		}
		
		if (p == source.data+source.count) {
			token->length = (u64)(p-source.data)-token->source_pos;
			token->kind = OL_TOKEN_KIND_EOF;
			continue;
		}
	}
}

unit_local string tprint_token(Ol_Compiler *compiler, Ol_Token *token, string message) {
    string source = compiler->source;
	string token_str = (string){token->length, source.data+token->source_pos};
	u32 line_counter = 1;
	
	u32 l0 = 0;
	for (u32 i = 0; i < token->source_pos; i += 1) {
		if (source.data[i] == '\n') {
			l0 = i+1;
			line_counter += 1;
		}
	}
	
	u32 l1 = l0;
	
	for (u32 i = (u32)token->source_pos; i < (u32)(source.count); i += 1) {
		l1 = i;
		if (source.data[i] == '\n') {
			break;
		}
	}
	
	string line = (string){l1-l0, source.data+l0};
	
	u32 pos_in_line = (u32)token->source_pos - l0;
	
	string space = string_allocate(get_temp(), pos_in_line);
	memset(space.data, '-', pos_in_line);
	
	string arrows = string_allocate(get_temp(), token->length);
	memset(arrows.data, '^', token->length);
	
	return tprint("Line %u, Token '%s': %s\n    %s\n    %s%s", line_counter, token_str, message, line, space, arrows);
}

Ol_Result ol_compile(Allocator a, Ol_Compile_Desc desc, void **pcode, u64 *pcode_size, string *err_log) {
    
    Ol_Compiler compiler = (Ol_Compiler){0};
    compiler.source = desc.code_text;
    compiler.token_arena = make_arena(1024*1024*1024*69, 1024*100);
    compiler.tokens = (Ol_Token*)compiler.token_arena.start;
    compiler.node_arena = make_arena(1024*1024*1024*69, 1024*100);
    
    _ol_tokenize(&compiler);
    
    Ol_Result res = OL_OK;
    
    Ol_Token *current = compiler.tokens;
    
    while (current->kind != OL_TOKEN_KIND_EOF) {
        
        Ol_Token *next = current + 1;
        if (current->kind == OL_TOKEN_KIND_IDENTIFIER && next->kind == ':') {
            Ol_Node *n = (Ol_Node*)arena_push(&compiler.node_arena, sizeof(Ol_Node));
            n->kind = OL_NODE_VALUE_DECL;
            Ol_Value_Decl *decl = &n->val.value_decl;
            
            Ol_Token *type_token = next+1;
            
            if (type_token->kind != OL_TOKEN_KIND_IDENTIFIER) {
                compiler.err_log = tprint_token(type_token, STR("Unexpected token. Expected type identifier, got this"));
                return OL_UNEXPECTED_TOKEN;
            }
            
            string type_string = (string){type_token->length, compiler.source.data+type_token->source_pos};
            
            if (strings_match(type_string, STR("f32")))
                decl->type = OL_TYPE_FLOAT32;
            else if (strings_match(type_string, STR("u32")))
                decl->type = OL_TYPE_UINT32;
            else if (strings_match(type_string, STR("v3f32")))
                decl->type = OL_TYPE_V3F32;
            else if (strings_match(type_string, STR("v4f32")))
                decl->type = OL_TYPE_V4F32;
            else {
                compiler.err_log = tprint_token(type_token, STR("Unresolved type"));
                return OL_UNRESOLVED_TYPE;
            }
        }
        
    }
    
    switch (desc.target) {
        case OL_TARGET_SPIRV:
            break;
        default:
            assert(false); break;
    }
    
    if (res != OL_OK) {
        if (err_log) *err_log = compiler.err_log;
        return res;
    }
    
    return OL_OK;
}

#endif // OSTD_IMPL
