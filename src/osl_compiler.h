
#if 0
#include "ostd.h"
#endif

typedef enum Osl_Result {
    OSL_OK,
    OSL_UNRESOLVED_TYPE,
    OSL_UNEXPECTED_TOKEN,
    OSL_BAD_OPERATOR,
    OSL_ASSIGN_NON_STORAGE_VALUE,
    OSL_UNDEFINED_VALUE,
    OSL_BAD_COMPOSITE_INSTANTIATE,
    OSL_BAD_INSTANTIATION_ARGUMENT,
    OSL_BAD_DEREF,
    OSL_BAD_DECORATION_ARGUMENTS,
    OSL_BAD_DECL_CLASS,
    OSL_EXCEED_MAX_TYPE_INDIRECTIONS,
    OSL_NOT_AN_EXPR,
    OSL_NON_INT_INDEX,
    OSL_CANNOT_CONVERT_TYPES,
    OSL_INVALID_SUBSCRIPT,
    OSL_INVALID_SWIZZLE,
    OSL_SWIZZLE_USED_AS_STORAGE,
    OSL_INVALID_CAST,
    OSL_VALUE_NAME_REDIFINITION,
} Osl_Result;

typedef enum Osl_Target {
    OSL_TARGET_SPIRV,
} Osl_Target;
typedef enum Osl_Program_Kind {
    OSL_PROGRAM_GPU_FRAGMENT,
    OSL_PROGRAM_GPU_VERTEX,
    OSL_PROGRAM_GPU_COMPUTE,
} Osl_Program_Kind;

typedef struct Osl_Compile_Desc {
    Osl_Target target;
    Osl_Program_Kind program_kind;
    string code_text;
} Osl_Compile_Desc;

Osl_Result osl_compile(Allocator a, Osl_Compile_Desc desc, void **pcode, u64 *pcode_size, string *err_log);

#ifdef OSTD_IMPL

typedef enum Spv_Op_Code_Enum {
    OpCapability           = 17,
    OpMemoryModel          = 14,
    OpEntryPoint           = 15,
    OpFunction             = 54,
    OpFunctionParameter    = 55,
    OpFunctionEnd          = 56,
    OpTypeVoid             = 19,
    OpTypeFunction         = 33,
    OpTypeInt              = 21,
    OpTypeFloat            = 22,
    OpTypeVector           = 23,
    OpTypeArray            = 28,
    OpExecutionMode        = 16,
    OpLabel                = 248,
    OpReturn               = 253,
    OpTypePointer          = 32,
    OpVariable             = 59,
    OpDecorate             = 71,
    OpLoad                 = 61,
    OpStore                = 62,
    OpCopyMemory           = 63,
    OpCompositeExtract     = 81,
    OpCompositeConstruct   = 80,
    OpConstant             = 43,
    OpConstantComposite    = 44,
    OpAccessChain          = 65,
    OpSNegate = 126,
    OpFNegate = 127,
    OpIAdd = 128,
    OpFAdd = 129,
    OpISub = 130,
    OpFSub = 131,
    OpIMul = 132,
    OpFMul = 133,
    OpUDiv = 134,
    OpSDiv = 135,
    OpFDiv = 136,
    OpVectorTimesScalar = 142,
    OpVectorShuffle = 79,
    OpUConvert=113,
    OpSConvert=114,
    OpFConvert=115,
    OpConvertFToU=109,
    OpConvertFToS=110,
    OpConvertSToF=111,
    OpConvertUToF=112,
    OpBitcast=124,
    OpName = 5
} Spv_Op_Code_Enum;

typedef enum Spv_Execution_Model {
    SpvExecutionModel_Vertex   = 0,
    SpvExecutionModel_Fragment = 4,
    SpvExecutionModel_Compute  = 5
} Spv_Execution_Model;

typedef enum Spv_Storage_Class {
    SpvStorageClass_Input         = 1,
    SpvStorageClass_Uniform       = 2,
    SpvStorageClass_Output        = 3,
    SpvStorageClass_Workgroup     = 4,
    SpvStorageClass_CrossWorkgroup= 5,
    SpvStorageClass_Private       = 6,
    SpvStorageClass_Function      = 7,
    SpvStorageClass_PushConstant  = 8,
    SpvStorageClass_Image         = 11,
    SpvStorageClass_Literal       = 6   /* alias for Private */
} Spv_Storage_Class;

typedef enum Spv_Capability {
    SpvCapability_Shader   = 1,
    SpvCapability_Kernel   = 6,
    SpvCapability_Vector16 = 7,
    SpvCapability_Float16  = 9,
    SpvCapability_Float64  = 10,
    SpvCapability_Int8     = 39,
    SpvCapability_Int16    = 22,
    SpvCapability_Int64    = 11
} Spv_Capability;

typedef enum Spv_Decoration {
    SpvDecoration_RowMajor    = 4,
    SpvDecoration_ColMajor    = 5,
    SpvDecoration_ArrayStride = 6,
    SpvDecoration_Builtin     = 11,
    SpvDecoration_Flat        = 14,
    SpvDecoration_Volatile    = 21,
    SpvDecoration_Location    = 30
} Spv_Decoration;

typedef enum Spv_Builtin {
    SpvBuiltin_Position    = 0,
    SpvBuiltin_VertexId    = 5,
    SpvBuiltin_InstanceId    = 6,
    SpvBuiltin_VertexIndex    = 42,
    SpvBuiltin_InstanceIndex    = 43,
} Spv_Builtin;

typedef struct Spv_Block {
	Arena arena;
	u8 *data; // arena.start
    u64 count;
    int current_op_byte_index;
} Spv_Block;

typedef enum Osl_Type_Kind {
	OSL_TYPE_INT,
	OSL_TYPE_FLOAT,
	OSL_TYPE_COMPOSITE,
	OSL_TYPE_ARRAY,
} Osl_Type_Kind;

struct Osl_Type_Info;

typedef struct Osl_Type_Info_Composite {
	struct Osl_Type_Info *underlying;
	u64 component_count;
} Osl_Type_Info_Composite;

typedef struct Osl_Type_Info_Int {
	bool is_signed;
} Osl_Type_Info_Int;

typedef struct Osl_Type_Info_Array {
	u64 array_count;
	struct Osl_Type_Info *elem_type;
} Osl_Type_Info_Array;

typedef struct Osl_Type_Info {
	Osl_Type_Kind kind;
	u32 type_id;
	u64 size;
	string name;
	
	union {
		Osl_Type_Info_Composite comp_type;
		Osl_Type_Info_Int int_type;
		Osl_Type_Info_Array array_type;
	} val;
	
} Osl_Type_Info;


struct Osl_Compiler;
typedef struct Spv_Converter {
	struct Osl_Compiler *compiler;

	Spv_Block settings_block;
	Spv_Block header_block;
	Spv_Block const_block;
	Spv_Block entry_block;
	Spv_Block annotations_block;
	Spv_Block debug_block;
	
	u32 next_id;
	u32 entry_id;
	
	u32 id_type_void;
	u32 id_type_void_function;
	
    Osl_Type_Info type_u32;
    Osl_Type_Info type_u32v2;
    Osl_Type_Info type_u32v3;
    Osl_Type_Info type_u32v4;
    Osl_Type_Info type_s32;
    Osl_Type_Info type_s32v2;
    Osl_Type_Info type_s32v3;
    Osl_Type_Info type_s32v4;
    Osl_Type_Info type_f32;
    Osl_Type_Info type_f32v2;
    Osl_Type_Info type_f32v3;
    Osl_Type_Info type_f32v4;
    
    Arena array_type_arena;
    Osl_Type_Info *array_types;
    u64 array_type_count;
    
	
} Spv_Converter;

typedef enum Osl_Token_Kind {
	OSL_TOKEN_KIND_UNKNOWN,
	
	OSL_TOKEN_KIND_SINGLE_PUNC_START,
	
	OSL_TOKEN_KIND_COLON = ':',
	OSL_TOKEN_KIND_SEMICOLON = ';',
	OSL_TOKEN_KIND_DOLLAR = '$',
	OSL_TOKEN_KIND_LPAREN = '(',
	OSL_TOKEN_KIND_RPAREN = ')',
	OSL_TOKEN_KIND_LBRACE = '{',
	OSL_TOKEN_KIND_RBRACE = '}',
	OSL_TOKEN_KIND_LBRACKET = '[',
	OSL_TOKEN_KIND_RBRACKET = ']',
	OSL_TOKEN_KIND_STAR = '*',
	OSL_TOKEN_KIND_DOT = '.',
	OSL_TOKEN_KIND_COMMA = ',',
	
	OSL_TOKEN_KIND_IDENTIFIER = 128,
	
	OSL_TOKEN_KIND_INT_LITERAL,
	OSL_TOKEN_KIND_FLOAT_LITERAL,
	
	OSL_TOKEN_KIND_EOF,
	
	OSL_TOKEN_KIND_RIGHT_ARROW,
	
	OSL_TOKEN_KIND_SINGLE_PUNC_END = OSL_TOKEN_KIND_IDENTIFIER,
	
} Osl_Token_Kind;

unit_local inline string _osl_stringify_token_kind(Osl_Token_Kind kind) {

	if (kind > OSL_TOKEN_KIND_SINGLE_PUNC_START && kind < OSL_TOKEN_KIND_IDENTIFIER) {
		string s = string_allocate(get_temp(), 1);
		*s.data = (u8)kind;
		return s;
	}

	switch (kind) {
		case OSL_TOKEN_KIND_IDENTIFIER: return STR("Identifier");
		case OSL_TOKEN_KIND_INT_LITERAL: return STR("Int Literal");
		case OSL_TOKEN_KIND_FLOAT_LITERAL: return STR("Float Literal");
		case OSL_TOKEN_KIND_COLON:  return STR(":");
		case OSL_TOKEN_KIND_DOLLAR: return STR("$");
		case OSL_TOKEN_KIND_LPAREN: return STR("(");
		case OSL_TOKEN_KIND_RPAREN: return STR(")");
		case OSL_TOKEN_KIND_LBRACE: return STR("{");
		case OSL_TOKEN_KIND_RBRACE: return STR("}");
		case OSL_TOKEN_KIND_LBRACKET: return STR("[");
		case OSL_TOKEN_KIND_RBRACKET: return STR("]");
		case OSL_TOKEN_KIND_STAR:   return STR("*");
		case OSL_TOKEN_KIND_DOT:    return STR(".");
		case OSL_TOKEN_KIND_COMMA:    return STR(",");
		case OSL_TOKEN_KIND_SEMICOLON:    return STR(";");
		case OSL_TOKEN_KIND_RIGHT_ARROW:    return STR("->");
		case OSL_TOKEN_KIND_EOF:    return STR("<eof>");
		case OSL_TOKEN_KIND_UNKNOWN: return STR("<unknown>"); //fallthrough
		case OSL_TOKEN_KIND_SINGLE_PUNC_START: //fallthrough
		default: return STR("<>");
	}
	return STR("<>");
}

typedef struct Osl_Token {
	Osl_Token_Kind kind;	
	u64 source_pos;
	u64 length;
} Osl_Token;

typedef struct Osl_Arg_List {
	// todo(charlie)
	// This is actually really, really bad because it makes the expr union massive and this will completely
	// butcher memory access.
	// And of course array literals are limited to 128 which is fairly unreasonable.
	// Should just put an arena here.
	struct Osl_Expr *args[128];
	u64 arg_count;
} Osl_Arg_List;

typedef struct Osl_Type_Indirection {
	u64 array_count;
} Osl_Type_Indirection;
typedef struct Osl_Type_Ident {
	Osl_Type_Indirection indirections[8]; // Max 8 indirections
	u64 indirection_count;
	Osl_Token *token;
	
	string name;
} Osl_Type_Ident;

typedef enum Osl_Storage_Class {
	OSL_STORAGE_DEFAULT = 0,
	OSL_STORAGE_INPUT = 1,
	OSL_STORAGE_OUTPUT = 2,
} Osl_Storage_Class;
typedef enum Osl_Builtin_Kind {
	OSL_BUILTIN_NONE,
	OSL_BUILTIN_VERTEX_POSITION,
	OSL_BUILTIN_VERTEX_INDEX,
	OSL_BUILTIN_VERTEX_ID,
	OSL_BUILTIN_INSTANCE_INDEX,
	OSL_BUILTIN_INSTANCE_ID,
} Osl_Builtin_Kind;

struct Osl_Expr;
typedef struct Osl_Value_Decl {
	Osl_Type_Ident type_ident;
	Osl_Storage_Class storage_class;
	Osl_Arg_List storage_args;
	Osl_Builtin_Kind builtin_kind;
	string ident;
	struct Osl_Expr *init_expr;
	s64 vnum;
	
	
	u32 spv_loaded_id; // For Spv converter
} Osl_Value_Decl;

typedef enum Osl_Instantiation_Kind {
	OSL_INST_COMP,
	OSL_INST_ARRAY,
} Osl_Instantiation_Kind;

typedef struct Osl_Instantiation {
	Osl_Instantiation_Kind kind;
	Osl_Arg_List list;
	Osl_Type_Ident type_ident;
} Osl_Instantiation;

typedef struct Osl_Access_Chain {
	struct Osl_Expr *base_expr;
	// todo(charlie)
	// This is actually really, really bad because it makes the expr union massive and this will completely
	// butcher memory access.
	struct { union { string name; struct Osl_Expr *index; } val; Osl_Token *token; bool is_index; } items[128];
	
	u64 item_count;
} Osl_Access_Chain;

typedef enum Osl_Op_Kind {
	OSL_OP_CAST,
	OSL_OP_MUL,
	OSL_OP_DIV,
	OSL_OP_ADD,
	OSL_OP_SUB,
	OSL_OP_SET,
	OSL_OP_UNARY_NEGATE,
} Osl_Op_Kind;
unit_local u32 _osl_precedence(Osl_Op_Kind op) {
	switch (op) {
	case OSL_OP_CAST:
		return 100000;
		
	case OSL_OP_MUL:
	case OSL_OP_DIV:
		return 10000;
	
	case OSL_OP_ADD:
	case OSL_OP_SUB:
		return 1000;
	
	case OSL_OP_SET:
		return 100;
		
	case OSL_OP_UNARY_NEGATE: // fallthrough
	default:
		assertmsgs(false, tprint("%i", op)); 
		break;
	}
	return 0;
}
typedef struct Osl_Op { 
	struct Osl_Expr *lhs; 
	struct Osl_Expr *rhs; 
	Osl_Op_Kind op_kind; 
	Osl_Token *op_token;
} Osl_Op;

typedef enum Osl_Expr_Kind {
	OSL_EXPR_OP,
	OSL_EXPR_DECL_IDENT,
	OSL_EXPR_LITERAL_FLOAT,
	OSL_EXPR_LITERAL_INT,
	OSL_EXPR_TYPE_IDENT, 
	OSL_EXPR_INSTANTIATE,
	OSL_EXPR_ACCESS_CHAIN,
} Osl_Expr_Kind;

typedef struct Osl_Expr {
    Osl_Expr_Kind kind;
	union {
		Osl_Value_Decl *decl;
		Osl_Op op;
		union { u64 lit_int; f64 lit_flt; } lit;
		Osl_Instantiation inst;
		Osl_Type_Ident type_ident;
		Osl_Access_Chain access;
	} val;
	string cast_to_type_ident;
	s64 vnum;
} Osl_Expr;

typedef enum Osl_Node_Kind {
	OSL_NODE_BLOCK,
    OSL_NODE_VALUE_DECL,  
    OSL_NODE_EXPR,
} Osl_Node_Kind;

struct Osl_Node;
typedef struct Osl_Block {
	struct Osl_Node *nodes[8196];
	u64 node_count;
	struct Osl_Block *parent;
	bool is_procedural;
} Osl_Block;

typedef struct Osl_Node {
    Osl_Node_Kind kind;
    Osl_Token *first_token;
    union {
        Osl_Value_Decl value_decl;
        Osl_Expr expr;
        Osl_Block block;
    } val;
} Osl_Node;

unit_local Osl_Node *_osl_get_node(void *node_value) {
	u64 offset = offsetof(Osl_Node, val);
	return (Osl_Node*)((u8*)node_value - offset);
}

typedef struct Osl_Compiler {
    string source;
    Osl_Program_Kind program_kind;

    Arena token_arena;
    Osl_Token *tokens;
    u64 token_count;
    
    Arena node_arena;
    u64 total_node_count;
    
    Osl_Block top_block;
    Osl_Block *current_block;
    
    
    Osl_Result result;
    string err_log;
    
    s64 next_vnum;
    
    u64 top_node_count;
    Osl_Node *top_nodes[8196];
    
} Osl_Compiler;

unit_local void spv_block_init(Spv_Block *block, u64 initial_capacity) {
	block->arena = make_arena(1024*1024*1024*69, initial_capacity);
    block->data = (u8*)block->arena.start;
    block->count = 0;
    block->current_op_byte_index = -1;
}

unit_local void spv_push_bytes(Spv_Block *block, void *bytes, u64 count) {
    void *backing = arena_push(&block->arena, count);
    memcpy(backing, bytes, count);
    block->count += count;
}

unit_local void spv_push_padding(Spv_Block *block, u64 count) {
    assert(count < 128);
    u8 zeros[128] = {0};
    spv_push_bytes(block, zeros, count);
}

unit_local void spv_push_word(Spv_Block *block, u32 word) {
    spv_push_bytes(block, &word, sizeof(u32));
}

unit_local void spv_push_op_code(Spv_Block *block, u16 word_count, u16 op) {
    u32 op_code = (((u32)word_count) << 16) | ((u32)op);
    spv_push_word(block, op_code);
}

unit_local void spv_begin_op(Spv_Block *block, Spv_Op_Code_Enum op) {
    assert(block->current_op_byte_index == -1 && "Spv op begin/end mismatch");
    block->current_op_byte_index = (int)block->count;
    spv_push_word(block, ((u32)op) & 0x0000FFFF);
}

unit_local void spv_end_op(Spv_Block *block) {
    assert(((s64)block->count - block->current_op_byte_index) % 4 == 0 &&
           "Op size is not aligned to word size");
    u32 word_count = (u32)(((s64)block->count - block->current_op_byte_index) / 4);
    u32 *op_code_ptr = (u32 *)(block->data + block->current_op_byte_index);
    *op_code_ptr |= (word_count << 16);
    block->current_op_byte_index = -1;
}

unit_local u64 spv_push_string_arg(Spv_Block *block, string s) {
    u64 len = s.count;
    u64 word_aligned = align_next(len + 1, 4);
    u64 padding = word_aligned - (len + 1);
    spv_push_bytes(block, s.data, len);
    {
        u8 zero = 0;
        spv_push_bytes(block, &zero, 1);
    }
    if (padding != 0) {
        spv_push_padding(block, padding);
    }
    return padding;
}

unit_local void spv_push_block(Spv_Block *dst, Spv_Block *src) {
    spv_push_bytes(dst, src->data, src->count);
}

unit_local u32 spv_push_result_arg(Spv_Converter *spv, Spv_Block *block) {
    spv_push_word(block, spv->next_id);
    u32 id = spv->next_id;
    spv->next_id++;
    return id;
}

unit_local void spv_push_header(Spv_Block *block, u32 max_id) {
    spv_push_word(block, 0x07230203);
    spv_push_word(block, 0x00010000);
    spv_push_word(block, 69);
    spv_push_word(block, max_id);
    spv_push_word(block, 0);
}

unit_local u32 spv_push_decl_float(Spv_Converter *spv, Spv_Block *block, u32 bit_width) {
    spv_begin_op(block, OpTypeFloat);
    u32 id = spv_push_result_arg(spv, block);
    spv_push_word(block, bit_width);
    spv_end_op(block);
    return id;
}

unit_local u32 spv_push_decl_int(Spv_Converter *spv, Spv_Block *block, u32 bit_width, bool is_signed) {
    spv_begin_op(block, OpTypeInt);
    u32 id = spv_push_result_arg(spv, block);
    spv_push_word(block, bit_width);
    spv_push_word(block, is_signed ? 1 : 0);
    spv_end_op(block);
    return id;
}

unit_local u32 spv_push_decl_vector(Spv_Converter *spv, Spv_Block *block, u32 id_type, u32 comp_count) {
    spv_begin_op(block, OpTypeVector);
    u32 id = spv_push_result_arg(spv, block);
    spv_push_word(block, id_type);
    spv_push_word(block, comp_count);
    spv_end_op(block);
    return id;
}

unit_local u32 spv_decl_proc_type(Spv_Converter *spv, Spv_Block *block, u32 return_type, u32 *param_types, u64 param_count) {
    spv_begin_op(block, OpTypeFunction);
    u32 id = spv_push_result_arg(spv, block);
    spv_push_word(block, return_type);
    for (u64 i = 0; i < param_count; i++) {
        spv_push_word(block, param_types[i]);
    }
    spv_end_op(block);
    return id;
}

unit_local void spv_push_base_decls(Spv_Converter *spv) {
    spv_begin_op(&spv->const_block, OpTypeVoid);
    spv->id_type_void = spv_push_result_arg(spv, &spv->const_block);
    spv_end_op(&spv->const_block);
    spv->id_type_void_function = spv_decl_proc_type(spv, &spv->const_block, spv->id_type_void, 0, 0);
    
    spv->type_f32.kind = OSL_TYPE_FLOAT;
    spv->type_f32.name = STR("f32");
    spv->type_f32.size = 4;
    spv->type_f32.type_id = spv_push_decl_float(spv, &spv->const_block, 32);
    
    spv->type_f32v2.kind = OSL_TYPE_COMPOSITE;
    spv->type_f32v2.name = STR("f32v2");
    spv->type_f32v2.size = 8;
    spv->type_f32v2.val.comp_type.component_count = 2;
    spv->type_f32v2.val.comp_type.underlying = &spv->type_f32;
    spv->type_f32v2.type_id = spv_push_decl_vector(spv, &spv->const_block, spv->type_f32.type_id, 2);
    
    spv->type_f32v3.kind = OSL_TYPE_COMPOSITE;
    spv->type_f32v3.name = STR("f32v3");
    spv->type_f32v3.size = 12; // 16 ?
    spv->type_f32v3.val.comp_type.component_count = 3;
    spv->type_f32v3.val.comp_type.underlying = &spv->type_f32;
    spv->type_f32v3.type_id = spv_push_decl_vector(spv, &spv->const_block, spv->type_f32.type_id, 3);
    
    spv->type_f32v4.kind = OSL_TYPE_COMPOSITE;
    spv->type_f32v4.name = STR("f32v4");
    spv->type_f32v4.size = 16;
    spv->type_f32v4.val.comp_type.component_count = 4;
    spv->type_f32v4.val.comp_type.underlying = &spv->type_f32;
    spv->type_f32v4.type_id = spv_push_decl_vector(spv, &spv->const_block, spv->type_f32.type_id, 4);
    
    spv->type_u32.kind = OSL_TYPE_INT;
    spv->type_u32.name = STR("u32");
    spv->type_u32.size = 4;
    spv->type_u32.val.int_type.is_signed = false;
    spv->type_u32.type_id = spv_push_decl_int(spv, &spv->const_block, 32, false);
    
    spv->type_u32v2.kind = OSL_TYPE_COMPOSITE;
    spv->type_u32v2.name = STR("u32v2");
    spv->type_u32v2.size = 8;
    spv->type_u32v2.val.comp_type.component_count = 2;
    spv->type_u32v2.val.comp_type.underlying = &spv->type_u32;
    spv->type_u32v2.type_id = spv_push_decl_vector(spv, &spv->const_block, spv->type_u32.type_id, 2);
    
    spv->type_u32v3.kind = OSL_TYPE_COMPOSITE;
    spv->type_u32v3.name = STR("u32v3");
    spv->type_u32v3.size = 12; // 16 ?
    spv->type_u32v3.val.comp_type.component_count = 3;
    spv->type_u32v3.val.comp_type.underlying = &spv->type_u32;
    spv->type_u32v3.type_id = spv_push_decl_vector(spv, &spv->const_block, spv->type_u32.type_id, 3);
    
    spv->type_u32v4.kind = OSL_TYPE_COMPOSITE;
    spv->type_u32v4.name = STR("u32v4");
    spv->type_u32v4.size = 16;
    spv->type_u32v4.val.comp_type.component_count = 4;
    spv->type_u32v4.val.comp_type.underlying = &spv->type_u32;
    spv->type_u32v4.type_id = spv_push_decl_vector(spv, &spv->const_block, spv->type_u32.type_id, 4);
    
    spv->type_s32.kind = OSL_TYPE_INT;
    spv->type_s32.name = STR("s32");
    spv->type_s32.size = 4;
    spv->type_s32.val.int_type.is_signed = true;
    spv->type_s32.type_id = spv_push_decl_int(spv, &spv->const_block, 32, true);
    
    spv->type_s32v2.kind = OSL_TYPE_COMPOSITE;
    spv->type_s32v2.name = STR("s32v2");
    spv->type_s32v2.size = 8;
    spv->type_s32v2.val.comp_type.component_count = 2;
    spv->type_s32v2.val.comp_type.underlying = &spv->type_s32;
    spv->type_s32v2.type_id = spv_push_decl_vector(spv, &spv->const_block, spv->type_s32.type_id, 2);
    
    spv->type_s32v3.kind = OSL_TYPE_COMPOSITE;
    spv->type_s32v3.name = STR("s32v3");
    spv->type_s32v3.size = 12; // 16 ?
    spv->type_s32v3.val.comp_type.component_count = 3;
    spv->type_s32v3.val.comp_type.underlying = &spv->type_s32;
    spv->type_s32v3.type_id = spv_push_decl_vector(spv, &spv->const_block, spv->type_s32.type_id, 3);
    
    spv->type_s32v4.kind = OSL_TYPE_COMPOSITE;
    spv->type_s32v4.name = STR("s32v4");
    spv->type_s32v4.size = 16;
    spv->type_s32v4.val.comp_type.component_count = 4;
    spv->type_s32v4.val.comp_type.underlying = &spv->type_s32;
    spv->type_s32v4.type_id = spv_push_decl_vector(spv, &spv->const_block, spv->type_s32.type_id, 4);
    
}

unit_local u32 spv_push_decl_pointer_type(Spv_Converter *spv, Spv_Block *block, u32 type, Spv_Storage_Class storage_class) {
    spv_begin_op(block, OpTypePointer);
    u32 id = spv_push_result_arg(spv, block);
    spv_push_word(block, (u32)storage_class);
    spv_push_word(block, type);
    spv_end_op(block);
    return id;
}

unit_local void spv_push_settings(Spv_Block *block, Spv_Capability *capabilities, u64 cap_count, Spv_Execution_Model exec_model, u32 *interface_items, u64 interface_count, string entry, u32 entry_point) {
    for (u64 i = 0; i < cap_count; i++) {
        spv_begin_op(block, OpCapability);
        spv_push_word(block, (u32)capabilities[i]);
        spv_end_op(block);
    }
    spv_begin_op(block, OpMemoryModel);
    spv_push_word(block, 0);
    spv_push_word(block, 1);
    spv_end_op(block);
    spv_begin_op(block, OpEntryPoint);
    spv_push_word(block, (u32)exec_model);
    spv_push_word(block, entry_point);
    spv_push_string_arg(block, entry);
    for (u64 i = 0; i < interface_count; i++) {
        spv_push_word(block, interface_items[i]);
    }
    spv_end_op(block);
    if (exec_model == SpvExecutionModel_Fragment) {
        spv_begin_op(block, OpExecutionMode);
        spv_push_word(block, entry_point);
        spv_push_word(block, 7);
        spv_end_op(block);
    }
}

unit_local void spv_push_decl_variable(Spv_Converter *spv, Spv_Block *block, Spv_Storage_Class storage_class, u32 decl_type, u32 *initial_value, string name, u32 result_id) {
	(void)spv;
    (void)name;
    spv_begin_op(block, OpVariable);
    spv_push_word(block, decl_type);
    spv_push_word(block, result_id);
    spv_push_word(block, (u32)storage_class);
    if (initial_value != 0) {
        spv_push_word(block, *initial_value);
    }
    spv_end_op(block);
}

unit_local void spv_push_decoration(Spv_Block *block, u32 target, Spv_Decoration deco, u32 *args, u64 arg_count) {
    spv_begin_op(block, OpDecorate);
    spv_push_word(block, target);
    spv_push_word(block, (u32)deco);
    for (u64 i = 0; i < arg_count; i++) {
        spv_push_word(block, args[i]);
    }
    spv_end_op(block);
}

unit_local u32 spv_push_decl_constant_u32(Spv_Converter *spv, Spv_Block *block, u32 type, u32 value) {
    spv_begin_op(block, OpConstant);
    spv_push_word(block, type);
    u32 id = spv_push_result_arg(spv, block);
    spv_push_word(block, value);
    spv_end_op(block);
    return id;
}

unit_local u32 spv_push_decl_constant_f32(Spv_Converter *spv, Spv_Block *block, u32 type, float value) {
    spv_begin_op(block, OpConstant);
    spv_push_word(block, type);
    u32 id = spv_push_result_arg(spv, block);
    union { float f; u32 u; } conv;
    conv.f = value;
    spv_push_word(block, conv.u);
    spv_end_op(block);
    return id;
}

unit_local u32 spv_push_decl_array_type(Spv_Converter *spv, Spv_Block *block, u32 elem_type, u32 count) {
    spv_begin_op(block, OpTypeArray);
    u32 id = spv_push_result_arg(spv, block);
    spv_push_word(block, elem_type);
    spv_push_word(block, count);
    spv_end_op(block);
    return id;
}

unit_local u32 spv_push_decl_constant_composite(Spv_Converter *spv, Spv_Block *block, u32 type, u32 *members, u64 member_count) {
    spv_begin_op(block, OpConstantComposite);
    spv_push_word(block, type);
    u32 id = spv_push_result_arg(spv, block);
    for (u64 i = 0; i < member_count; i++) {
        spv_push_word(block, members[i]);
    }
    spv_end_op(block);
    return id;
}

unit_local u32 spv_push_op_load(Spv_Converter *spv, Spv_Block *block, u32 pointer, u32 result_type) {
    spv_begin_op(block, OpLoad);
    spv_push_word(block, result_type);
    u32 id = spv_push_result_arg(spv, block);
    spv_push_word(block, pointer);
    spv_end_op(block);
    return id;
}

unit_local void spv_push_op_store(Spv_Block *block, u32 pointer, u32 obj) {
    spv_begin_op(block, OpStore);
    spv_push_word(block, pointer);
    spv_push_word(block, obj);
    spv_end_op(block);
}

unit_local u32 spv_push_op_composite_extract(Spv_Converter *spv, Spv_Block *block, u32 composite_obj, u32 result_type, u32 *indices, u64 index_count) {
    spv_begin_op(block, OpCompositeExtract);
    spv_push_word(block, result_type);
    u32 id = spv_push_result_arg(spv, block);
    spv_push_word(block, composite_obj);
    for (u64 i = 0; i < index_count; i += 1)
    	spv_push_word(block, indices[i]);
    spv_end_op(block);
    return id;
}

unit_local u32 spv_push_op_access_chain(Spv_Converter *spv, Spv_Block *block, u32 result_type, u32 pointer, u32 *indices, u64 index_count) {
    spv_begin_op(block, OpAccessChain);
    spv_push_word(block, result_type);
    u32 id = spv_push_result_arg(spv, block);
    spv_push_word(block, pointer);
    for (u64 i = 0; i < index_count; i++) {
        spv_push_word(block, indices[i]);
    }
    spv_end_op(block);
    return id;
}

unit_local u32 spv_push_op_composite_construct(Spv_Converter *spv, Spv_Block *block, u32 result_type, u32 *members, u64 member_count) {
    spv_begin_op(block, OpCompositeConstruct);
    spv_push_word(block, result_type);
    u32 id = spv_push_result_arg(spv, block);
    for (u64 i = 0; i < member_count; i++) {
        spv_push_word(block, members[i]);
    }
    spv_end_op(block);
    return id;
}

unit_local u32 spv_push_op_vector_shuffle(Spv_Converter *spv, Spv_Block *block, u32 result_type, u32 vector1, u32 vector2, u32 *indices, u64 index_count) {
    spv_begin_op(block, OpVectorShuffle);
    spv_push_word(block, result_type);
    u32 id = spv_push_result_arg(spv, block);
    spv_push_word(block, vector1);
    spv_push_word(block, vector2);
    for (u64 i = 0; i < index_count; i++) {
        spv_push_word(block, indices[i]);
    }
    spv_end_op(block);
    return id;
}




unit_local void spv_init(Spv_Converter *spv, Osl_Compiler *compiler, u32 vnum_count) {
	*spv = (Spv_Converter){0};
	spv->compiler = compiler;
	spv_block_init(&spv->settings_block, 1024*10);
	spv_block_init(&spv->header_block, 1024*10);
	spv_block_init(&spv->const_block, 1024*10);
	spv_block_init(&spv->entry_block, 1024*10);
	spv_block_init(&spv->annotations_block, 1024*10);
	spv_block_init(&spv->debug_block, 1024*10);
	
	spv->array_type_arena = make_arena(1024*1024*1024*69, 1024*10);
	spv->array_types = (Osl_Type_Info*)spv->array_type_arena.start;
	
	spv->next_id = vnum_count;
	spv->entry_id = spv->next_id++;
	
	spv_push_base_decls(spv);
	
	spv_begin_op(&spv->entry_block, OpLabel);
    spv_push_word(&spv->entry_block, spv->next_id++);
    spv_end_op(&spv->entry_block);
}

unit_local Spv_Block *spv_finalize(Spv_Converter *spv) {

	spv_push_op_code(&spv->entry_block, 1, (u16)OpReturn);

	spv_push_header(&spv->header_block, spv->next_id);
	Spv_Capability caps[] = {
		SpvCapability_Shader
	};
	Spv_Execution_Model exec_model = 0;
	switch (spv->compiler->program_kind) {
	case OSL_PROGRAM_GPU_VERTEX: {
		exec_model = SpvExecutionModel_Vertex;
		break;
	}
	case OSL_PROGRAM_GPU_FRAGMENT: {
		exec_model = SpvExecutionModel_Fragment;
		break;
	}
	case OSL_PROGRAM_GPU_COMPUTE: {
		exec_model = SpvExecutionModel_Compute;
		break;
	}
	default: {
		assert(false);
		break;
	}
	}
	
	u32 interface[1024];
	u64 interface_count = 0;
	
	for (u64 i = 0; i < spv->compiler->top_node_count; i += 1) {
		Osl_Node *n = spv->compiler->top_nodes[i];
		
		if (n->kind == OSL_NODE_VALUE_DECL && n->val.value_decl.storage_class != OSL_STORAGE_DEFAULT) {
			assert(n->val.value_decl.vnum >= 0);
			interface[interface_count++] = (u32)n->val.value_decl.vnum;
		}
	}
	
	spv_push_settings(&spv->settings_block, caps, sizeof(caps)/sizeof(caps[0]), exec_model, interface, interface_count, STR("main"), spv->entry_id);
	
	// Push array types to const block
	
	
	spv_push_block(&spv->header_block, &spv->settings_block);
	spv_push_block(&spv->header_block, &spv->debug_block);
	spv_push_block(&spv->header_block, &spv->annotations_block);
	spv_push_block(&spv->header_block, &spv->const_block);
	
	spv_begin_op(&spv->header_block, OpFunction);
    spv_push_word(&spv->header_block, spv->id_type_void);
    spv_push_word(&spv->header_block, spv->entry_id);
    spv_push_word(&spv->header_block, 0);
    spv_push_word(&spv->header_block, spv->id_type_void_function);
    spv_end_op(&spv->header_block);
    
	spv_push_block(&spv->header_block, &spv->entry_block);
	
	spv_push_op_code(&spv->header_block, 1, (u16)OpFunctionEnd);
	
	return &spv->header_block;
}
unit_local string _osl_tprint_token(Osl_Compiler *compiler, Osl_Token *token, string message);

unit_local Osl_Type_Info *arrayify_type(Spv_Converter *spv, Osl_Type_Info *elem, u64 array_count) {
	for (s64 i = (s64)spv->array_type_count-1; i >= 0; i -= 1) {
		Osl_Type_Info *type = &spv->array_types[i];
		if (type->val.array_type.elem_type == elem && type->val.array_type.array_count == array_count)
			return type;
	}
	
	u32 id_array_count = spv_push_decl_constant_u32(spv, &spv->const_block, spv->type_u32.type_id, (u32)array_count);
	
	Osl_Type_Info *type = (Osl_Type_Info*)arena_push(&spv->array_type_arena, sizeof(Osl_Type_Info));
	spv->array_type_count += 1;
	type->kind = OSL_TYPE_ARRAY;
	type->type_id = spv_push_decl_array_type(spv, &spv->const_block, elem->type_id, id_array_count);
	type->size = array_count*elem->size;
	type->name = tprint("[%i]%s", array_count, elem->name);
	type->val.array_type.array_count = array_count;
	type->val.array_type.elem_type = elem;
	
	
	
	return type;
}

unit_local Osl_Type_Info *_osl_resolve_type(Spv_Converter *spv, Osl_Type_Ident type_ident) {

	Osl_Type_Info *type = 0;
	if (strings_match(type_ident.name, STR("f32"))) {
		type = &spv->type_f32;
	} else if (strings_match(type_ident.name, STR("f32v2"))) {
		type = &spv->type_f32v2;
	} else if (strings_match(type_ident.name, STR("f32v3"))) {
		type = &spv->type_f32v3;
	} else if (strings_match(type_ident.name, STR("f32v4"))) {
		type = &spv->type_f32v4;
	} else if (strings_match(type_ident.name, STR("u32"))) {
		type = &spv->type_u32;
	} else if (strings_match(type_ident.name, STR("u32v2"))) {
		type = &spv->type_u32v2;
	} else if (strings_match(type_ident.name, STR("u32v3"))) {
		type = &spv->type_u32v3;
	} else if (strings_match(type_ident.name, STR("u32v4"))) {
		type = &spv->type_u32v4;
	} else if (strings_match(type_ident.name, STR("s32"))) {
		type = &spv->type_s32;
	} else if (strings_match(type_ident.name, STR("s32v2"))) {
		type = &spv->type_s32v2;
	} else if (strings_match(type_ident.name, STR("s32v3"))) {
		type = &spv->type_s32v3;
	} else if (strings_match(type_ident.name, STR("s32v4"))) {
		type = &spv->type_s32v4;
	}
	
	for (u32 i = 0; i < type_ident.indirection_count; i += 1) {
		Osl_Type_Indirection ind = type_ident.indirections[i];
		type = arrayify_type(spv, type, ind.array_count);
	}
	
	return type;
}
unit_local bool _osl_can_expr_have_storage(Osl_Expr *expr) {
	if (expr->kind == OSL_EXPR_DECL_IDENT) 
		return true;
		
	if (expr->kind == OSL_EXPR_ACCESS_CHAIN) {
		return _osl_can_expr_have_storage(expr->val.access.base_expr);
	}
	return false;
}
unit_local Osl_Result spv_emit_expr(Spv_Converter *spv, Spv_Block *block, Osl_Expr *expr, u32 *result_id, Osl_Type_Info **type, bool in_memory) {
	switch (expr->kind) {
	
	case OSL_EXPR_OP: {
		assert(!in_memory);
		Osl_Op *op = &expr->val.op;
		
		u32 op1 = 0;
		Osl_Type_Info *op1_type = 0;
		u32 op2 = 0;
		Osl_Type_Info *op2_type = 0;
		
		Osl_Result res = spv_emit_expr(spv, block, op->lhs, &op1, &op1_type, op->op_kind == OSL_OP_SET);
		if (res != OSL_OK) return res;
		assert(op1); assert(op1_type);
		
		bool is_vector_v_scalar = false;
		bool is_scalar_v_vector = false;
		
		if (op->op_kind != OSL_OP_CAST && op->op_kind != OSL_OP_UNARY_NEGATE && op->op_kind != OSL_OP_UNARY_NEGATE) {
			res = spv_emit_expr(spv, block, op->rhs, &op2, &op2_type, false);
			if (res != OSL_OK) return res;
			assert(op2); assert(op2_type);
			is_vector_v_scalar = op1_type->kind == OSL_TYPE_COMPOSITE && op1_type->val.comp_type.underlying == op2_type;
			is_scalar_v_vector = op2_type->kind == OSL_TYPE_COMPOSITE && op2_type->val.comp_type.underlying == op1_type;
			if (op1_type != op2_type && !((op->op_kind == OSL_OP_MUL || op->op_kind == OSL_OP_DIV) && (is_vector_v_scalar || is_scalar_v_vector))) {
				string a = _osl_tprint_token(spv->compiler, op->op_token, STR("Cannot perform this operations on these types ..."));
				string b = _osl_tprint_token(spv->compiler, _osl_get_node(op->lhs)->first_token, tprint("... Left hand side is of tyoe '%s' ... ", op1_type->name));
				string c = _osl_tprint_token(spv->compiler, _osl_get_node(op->rhs)->first_token, tprint("... Right hand side is of type '%s'", op2_type->name));
				spv->compiler->err_log = tprint("%s\n%s\n%s", a, b, c);
				return spv->compiler->result = OSL_UNRESOLVED_TYPE;
			}
		}
		
		*type = op1_type;
		
		switch (op->op_kind) {
		case OSL_OP_CAST: {
		
			assert(op->rhs->kind == OSL_EXPR_TYPE_IDENT);
			op2_type = _osl_resolve_type(spv, op->rhs->val.type_ident);
			if (!op2_type) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, op->rhs->val.type_ident.token, STR("Unresolved type"));
				return spv->compiler->result = OSL_UNRESOLVED_TYPE;
			}
			*type = op2_type;
			
			Osl_Type_Info *underlying1 = op1_type;
			Osl_Type_Info *underlying2 = op2_type;
			
			if (underlying1->kind == OSL_TYPE_COMPOSITE && underlying2->kind == OSL_TYPE_COMPOSITE 
			 && underlying2->val.comp_type.component_count <= underlying1->val.comp_type.component_count) {
				// Composite conversion
				Osl_Type_Info_Composite *comp1 = &op1_type->val.comp_type;
				Osl_Type_Info_Composite *comp2 = &op2_type->val.comp_type;
				
				if (comp2->component_count < comp1->component_count) {
				
					Osl_Type_Info *trunc_vector_type = 0;
					// Select the truncated vector type; same count as the type we are casting to
					if (comp1->underlying == &spv->type_f32 && comp2->component_count == 2)
						trunc_vector_type = &spv->type_f32v2;
					else if (comp1->underlying == &spv->type_f32 && comp2->component_count == 3)
						trunc_vector_type = &spv->type_f32v3;
					else if (comp1->underlying == &spv->type_f32 && comp2->component_count == 4)
						trunc_vector_type = &spv->type_f32v4;
					else if (comp1->underlying == &spv->type_u32 && comp2->component_count == 2)
						trunc_vector_type = &spv->type_u32v2;
					else if (comp1->underlying == &spv->type_u32 && comp2->component_count == 3)
						trunc_vector_type = &spv->type_u32v3;
					else if (comp1->underlying == &spv->type_u32 && comp2->component_count == 4)
						trunc_vector_type = &spv->type_u32v4;
					else if (comp1->underlying == &spv->type_s32 && comp2->component_count == 2)
						trunc_vector_type = &spv->type_s32v2;
					else if (comp1->underlying == &spv->type_s32 && comp2->component_count == 3)
						trunc_vector_type = &spv->type_s32v3;
					else if (comp1->underlying == &spv->type_s32 && comp2->component_count == 4)
						trunc_vector_type = &spv->type_s32v4;
					else
						assert(false);
				
					u32 indices[] = { 0, 1, 2, 3 };
					op1 = spv_push_op_vector_shuffle(spv, block, trunc_vector_type->type_id, op1, op1, indices, comp2->component_count);
				}
				
				underlying1 = comp1->underlying;
				underlying2 = comp2->underlying;
			} 
			
			if (underlying1->kind == OSL_TYPE_FLOAT && (underlying2->kind == OSL_TYPE_INT && underlying2->val.int_type.is_signed)) {
				spv_begin_op(block, OpConvertFToS);
			} else if (underlying1->kind == OSL_TYPE_FLOAT && (underlying2->kind == OSL_TYPE_INT && !underlying2->val.int_type.is_signed)) {
				spv_begin_op(block, OpConvertFToU);
			} else if ((underlying1->kind == OSL_TYPE_INT && underlying1->val.int_type.is_signed) && underlying2->kind == OSL_TYPE_FLOAT) {
				spv_begin_op(block, OpConvertSToF);
			} else if ((underlying1->kind == OSL_TYPE_INT && !underlying1->val.int_type.is_signed) && underlying2->kind == OSL_TYPE_FLOAT) {
				spv_begin_op(block, OpConvertUToF);
			} else if ((underlying1->kind == OSL_TYPE_INT && underlying1->val.int_type.is_signed) && (underlying2->kind == OSL_TYPE_INT && !underlying2->val.int_type.is_signed)) {
				spv_begin_op(block, OpBitcast);
			} else if ((underlying1->kind == OSL_TYPE_INT && !underlying1->val.int_type.is_signed) && (underlying2->kind == OSL_TYPE_INT && underlying2->val.int_type.is_signed)) {
				spv_begin_op(block, OpBitcast);
			} else {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, op->op_token, tprint("Cannot cast from '%s' to '%s'", underlying1->name, underlying2->name));
				return spv->compiler->result = OSL_INVALID_CAST;
			}
			
			spv_push_word(block, op2_type->type_id);
		    *result_id = spv_push_result_arg(spv, block);
		    spv_push_word(block, op1);
		    
		    spv_end_op(block);
			
			break;
		}
		case OSL_OP_UNARY_NEGATE: {
		
			assert(!op->rhs);
			if (op1_type->kind == OSL_TYPE_FLOAT || (op1_type->kind == OSL_TYPE_COMPOSITE && op1_type->val.comp_type.underlying->kind == OSL_TYPE_FLOAT)) 
				spv_begin_op(block, OpFNegate);
			else if (op1_type->kind == OSL_TYPE_INT || (op1_type->kind == OSL_TYPE_COMPOSITE && op1_type->val.comp_type.underlying->kind == OSL_TYPE_INT)) 
				spv_begin_op(block, OpSNegate); // todo(charlie) err if int is unsigned
			else assert(false);
			
			spv_push_word(block, op1_type->type_id);
		    *result_id = spv_push_result_arg(spv, block);
		    spv_push_word(block, op1);
		    
		    spv_end_op(block);
			
			break;
		}
		case OSL_OP_ADD: {
		
			if (op1_type->kind == OSL_TYPE_FLOAT || (op1_type->kind == OSL_TYPE_COMPOSITE && op1_type->val.comp_type.underlying->kind == OSL_TYPE_FLOAT)) 
				spv_begin_op(block, OpFAdd);
			else if (op1_type->kind == OSL_TYPE_INT || (op1_type->kind == OSL_TYPE_COMPOSITE && op1_type->val.comp_type.underlying->kind == OSL_TYPE_INT)) 
				spv_begin_op(block, OpIAdd);
			else assert(false);
			
			spv_push_word(block, op1_type->type_id);
		    *result_id = spv_push_result_arg(spv, block);
		    spv_push_word(block, op1);
		    spv_push_word(block, op2);
	    	spv_end_op(block);
			
			break;
		}
		case OSL_OP_SUB: {
		
			if (op1_type->kind == OSL_TYPE_FLOAT || (op1_type->kind == OSL_TYPE_COMPOSITE && op1_type->val.comp_type.underlying->kind == OSL_TYPE_FLOAT)) 
				spv_begin_op(block, OpFSub);
			else if (op1_type->kind == OSL_TYPE_INT || (op1_type->kind == OSL_TYPE_COMPOSITE && op1_type->val.comp_type.underlying->kind == OSL_TYPE_INT)) 
				spv_begin_op(block, OpISub);
			else assert(false);
			
			spv_push_word(block, op1_type->type_id);
		    *result_id = spv_push_result_arg(spv, block);
		    spv_push_word(block, op1);
		    spv_push_word(block, op2);
	    	spv_end_op(block);
			
			break;
		}
		case OSL_OP_MUL: {
		
				
			
			if (op1_type == op2_type) {
				
				if (op1_type->kind == OSL_TYPE_FLOAT || (op1_type->kind == OSL_TYPE_COMPOSITE && op1_type->val.comp_type.underlying->kind == OSL_TYPE_FLOAT)) 
					spv_begin_op(block, OpFMul);
				else if (op1_type->kind == OSL_TYPE_INT || (op1_type->kind == OSL_TYPE_COMPOSITE && op1_type->val.comp_type.underlying->kind == OSL_TYPE_INT)) 
					spv_begin_op(block, OpIMul);
				else assert(false);
				
				spv_push_word(block, op1_type->type_id);
			    *result_id = spv_push_result_arg(spv, block);
			    spv_push_word(block, op1);
			    spv_push_word(block, op2);
		    	spv_end_op(block);
				
			} else if ((op1_type->kind == OSL_TYPE_COMPOSITE || op2_type->kind == OSL_TYPE_COMPOSITE)) {
				
				
				Osl_Type_Info *comp_type_base = 
					op1_type->kind == OSL_TYPE_COMPOSITE 
					? op1_type
					: op2_type;
				
				Osl_Type_Info_Composite *comp_type = &comp_type_base->val.comp_type;
				
				Osl_Type_Info *scalar_type = &op1_type->val.comp_type == comp_type ? op2_type : op1_type;
				
				u32 comp_op = comp_type == &op1_type->val.comp_type ? op1 : op2;
				u32 scalar_op = comp_op == op1 ? op2 : op1;
				
				assert(comp_type->underlying == scalar_type);
				
				if (is_vector_v_scalar) {
					
					Spv_Op_Code_Enum spv_op = (Spv_Op_Code_Enum)0;
					if (scalar_type->kind == OSL_TYPE_FLOAT)
						spv_op = OpFMul;
					else if (scalar_type->kind == OSL_TYPE_INT)
						spv_op = OpIMul;
					else assert(false);
					
					assert(comp_type->component_count <= 128);
					u32 results[128];
					
					for (u32 i = 0; i < comp_type->component_count; i += 1) {
						u32 comp_part_id = spv_push_op_composite_extract(spv, block, comp_op, scalar_type->type_id, &i, 1);
						
						spv_begin_op(block, spv_op);
						spv_push_word(block, scalar_type->type_id);
					    results[i] = spv_push_result_arg(spv, block);
					    spv_push_word(block, comp_part_id);
					    spv_push_word(block, scalar_op);
				    	spv_end_op(block);
					}
					
					*result_id = spv_push_op_composite_construct(spv, block, comp_type_base->type_id, results, comp_type->component_count);
					*type = comp_type_base;
					
				} else if (is_scalar_v_vector) {
					
				} else assert(false);
				
			} else assert(false);
			
			break;
		}
		case OSL_OP_DIV: {
		
			if (op1_type->kind == OSL_TYPE_FLOAT || (op1_type->kind == OSL_TYPE_COMPOSITE && op1_type->val.comp_type.underlying->kind == OSL_TYPE_FLOAT)) 
				spv_begin_op(block, OpFDiv);
			else if (op1_type->kind == OSL_TYPE_INT || (op1_type->kind == OSL_TYPE_COMPOSITE && op1_type->val.comp_type.underlying->kind == OSL_TYPE_INT)) 
				spv_begin_op(block, op1_type->val.int_type.is_signed ? OpSDiv : OpUDiv);
			else assert(false);
			
			spv_push_word(block, op1_type->type_id);
		    *result_id = spv_push_result_arg(spv, block);
		    spv_push_word(block, op1);
		    spv_push_word(block, op2);
	    	spv_end_op(block);
			
			break;
		}
		case OSL_OP_SET: {
		
			spv_begin_op(block, OpStore);
			spv_push_word(block, op1);
		    spv_push_word(block, op2);
		    *result_id = op1;
		    
		    if (op->lhs->kind == OSL_EXPR_DECL_IDENT) {
		    	op->lhs->val.decl->spv_loaded_id = op2;
		    }
		    
		    spv_end_op(block);
		    
			break;
		}
		default: {
			assert(false);
			break;
		}
		}
	    
		
		break;
	}
	case OSL_EXPR_INSTANTIATE: {
		assert(!in_memory);
		Osl_Instantiation *inst = &expr->val.inst;
		
		
		Osl_Type_Info *inst_type = _osl_resolve_type(spv, inst->type_ident);
		Osl_Type_Info *underlying = inst_type;
		
		if (!inst_type) {
			spv->compiler->err_log = _osl_tprint_token(spv->compiler, inst->type_ident.token, STR("Unresolved type"));
			return spv->compiler->result = OSL_UNRESOLVED_TYPE;
		}
		
		if (inst->kind == OSL_INST_COMP) {
			if (inst_type->kind != OSL_TYPE_COMPOSITE) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(expr)->first_token, tprint("Attempting to perform a composite instantiation on a non-composite type '%s'. This doesn't make sense.", inst->type_ident));
				return spv->compiler->result = OSL_BAD_COMPOSITE_INSTANTIATE;
			}
			
			if (inst_type->val.comp_type.component_count != inst->list.arg_count) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(expr)->first_token, tprint("Bad number of arguments passed to instantiation. Expected '%i', got '%i'", inst_type->val.comp_type.component_count, inst->list.arg_count));
				return spv->compiler->result = OSL_BAD_COMPOSITE_INSTANTIATE;
			}
			underlying = inst_type->val.comp_type.underlying;
		} else if (inst->kind == OSL_INST_ARRAY) {
			inst_type = arrayify_type(spv, inst_type, inst->list.arg_count);
			underlying = inst_type->val.array_type.elem_type;
		} else
			assert(false);
		
		u32 args[128];
		u64 arg_count = 0;
		for (u64 i = 0; i < inst->list.arg_count; i += 1) {
			Osl_Expr *arg = inst->list.args[i];
			
			u32 id;
			Osl_Type_Info *arg_type;
			Osl_Result res = spv_emit_expr(spv, block, arg, &id, &arg_type, false);
			if (res != OSL_OK) return res;
			assert(id); assert(arg_type);
			
			if (arg_type != underlying) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(arg)->first_token, tprint("Argument type '%s' does not match the underlying type of '%s' which is being instantiated.", arg_type->name, underlying->name));
				return spv->compiler->result = OSL_BAD_INSTANTIATION_ARGUMENT;
			}
			
			args[arg_count++] = id;
		}
		
		spv_begin_op(block, OpCompositeConstruct);
	    spv_push_word(block, inst_type->type_id);
	    *result_id = spv_push_result_arg(spv, block);
		for (u64 i = 0; i < arg_count; i += 1) {
			spv_push_word(block, args[i]);
		}
		spv_end_op(block); // OpCompositeConstruct
		
		*type = inst_type;
		
		break;
	}
	case OSL_EXPR_ACCESS_CHAIN: {
		
		
		Osl_Access_Chain *access = &expr->val.access;
		
		bool accessing_storage = _osl_can_expr_have_storage(access->base_expr);
		
		
		
		if (!accessing_storage) {
			assert(!in_memory);
		}
		
		Spv_Storage_Class base_storage_class = SpvStorageClass_Private;
		if (access->base_expr->kind == OSL_EXPR_DECL_IDENT) {
			switch (access->base_expr->val.decl->storage_class) {
			case OSL_STORAGE_DEFAULT: base_storage_class = SpvStorageClass_Private; break;
			case OSL_STORAGE_INPUT:   base_storage_class = SpvStorageClass_Input;   break;
			case OSL_STORAGE_OUTPUT:  base_storage_class = SpvStorageClass_Output;  break;
			default:
				assert(false);
				break;
			}
		}
		
		u32 base_id;
		Osl_Type_Info *base_type;
		Osl_Result res = spv_emit_expr(spv, block, access->base_expr, &base_id, &base_type, accessing_storage);
		if (res != OSL_OK) return res;
		assert(base_id); assert(base_type);
		
		u32 *args = PushTempBuffer(u32, access->item_count);
		u64 arg_count = 0;
		
		u32 last_base_id = base_id;
		Osl_Type_Info *last_base_type = base_type;
		Osl_Type_Info *last_type = base_type;
		
		for (u32 i = 0; i < access->item_count; i += 1) {
			if (access->items[i].is_index) 
			{
				if (last_type->kind != OSL_TYPE_ARRAY) {
					spv->compiler->err_log = _osl_tprint_token(spv->compiler, access->items[i].token, tprint("Invalid subscript for non-array type '%s'", last_type->name));
					return spv->compiler->result = OSL_INVALID_SUBSCRIPT;
				}
				
				u32 arg;
				Osl_Expr *index_expr = access->items[i].val.index;
				
				if (index_expr->kind == OSL_EXPR_LITERAL_INT) {
					arg = (u32)index_expr->val.lit.lit_int;
					if (accessing_storage) {
						// todo(charlie) constants
						arg = spv_push_decl_constant_u32(spv, &spv->const_block, spv->type_u32.type_id,  arg);
					}
				} else {
					Osl_Type_Info *arg_type;
					Osl_Result index_res = spv_emit_expr(spv, block, index_expr, &arg, &arg_type, false);
					if (index_res != OSL_OK) return index_res;
					assert(arg); assert(arg_type);
					
					if (arg_type->kind != OSL_TYPE_INT) {
						spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(index_expr)->first_token, tprint("Invalid subscript argument expression of type '%s', expected integer expression", arg_type->name));
						return spv->compiler->result = OSL_INVALID_SUBSCRIPT;
					}
				}
				
				args[arg_count++] = arg;
				
				last_type = last_type->val.array_type.elem_type;
				
			} else {
				string member_name = access->items[i].val.name;
				
				if (last_type->kind != OSL_TYPE_COMPOSITE) {
					spv->compiler->err_log = _osl_tprint_token(spv->compiler, access->items[i].token, tprint("Invalid member access for non-composite type '%s'", last_type->name));
					return spv->compiler->result = OSL_INVALID_SUBSCRIPT;
				}
				
				if (last_type->kind == OSL_TYPE_COMPOSITE) {
					
					Osl_Type_Info_Composite *comp_type = &last_type->val.comp_type;
					
					u32 indices[4] = {0, 1, 2, 3};
					
					if (member_name.count > 4) {
						spv->compiler->err_log = _osl_tprint_token(spv->compiler, access->items[i].token, tprint("Invalid component access on type '%s'. Too many components.", last_type->name));
						return spv->compiler->result = OSL_INVALID_SWIZZLE;
					}
					
					for (u32 j = 0; j < member_name.count; j += 1) {
						u8 c = member_name.data[j];
						
						u32 index = 0;
						if (c == 'x' || c == 'r')
							index = 0;
						else if (c == 'y' || c == 'g')
							index = 1;
						else if (c == 'z' || c == 'b')
							index = 2;
						else if (c == 'w' || c == 'a')
							index = 3;
						else {
							// Make token point to the single err'd letter
							Osl_Token *tok = access->items[i].token;
							tok->length = 1;
							tok->source_pos += j;
							string s = (string){1, &c};
							spv->compiler->err_log = _osl_tprint_token(spv->compiler, tok, tprint("Invalid swizzle component '%s'. Valid swizzle components are: x, y, z, w OR r, g, b, a", s));
							return spv->compiler->result = OSL_INVALID_SWIZZLE;
						}
						
						if (index >= comp_type->component_count) {
							// Make token point to the single err'd letter
							Osl_Token *tok = access->items[i].token;
							tok->length = 1;
							tok->source_pos += j+1;
							string s = (string){1, &c};
							spv->compiler->err_log = _osl_tprint_token(spv->compiler, tok, tprint("Invalid swizzle component '%s' is out of range for type '%s'", s, last_type->name));
							return spv->compiler->result = OSL_INVALID_SWIZZLE;
						}
						
						indices[j] = index;
					}
					
					if (member_name.count == 1) {
						u32 arg = indices[0];
						if (accessing_storage) {
							// todo(charlie) constants
							arg = spv_push_decl_constant_u32(spv, &spv->const_block, spv->type_u32.type_id,  arg);
						}
						args[arg_count++] = arg;
						
						last_type = comp_type->underlying;
						
					} else {
						// Swizzle
						
						// #Copypaste
						// We need to do the chain now, and use that value for shuffling.
						if (arg_count > 0) {
							if (accessing_storage) {
								// todo(charlie) storage class should match last_base_id storage class. oof.
								u32 id_type_pointer = spv_push_decl_pointer_type(spv, &spv->const_block, last_type->type_id, base_storage_class);
								last_base_id 
									= spv_push_op_access_chain(spv, block, id_type_pointer, last_base_id, args, arg_count);
									
								if (!in_memory) {
									last_base_id = spv_push_op_load(spv, block, last_base_id, last_type->type_id);
								}
							} else {
								last_base_id 
									= spv_push_op_composite_extract(spv, block, last_base_id, last_type->type_id, args, arg_count);
							}
							last_base_type = last_type;
							
						}
						
						if (accessing_storage) {
							last_base_id = spv_push_op_load(spv, block, last_base_id, last_base_type->type_id);
						}
						
						Osl_Type_Info *swizzle_result_type = 0;
						
						if (comp_type->underlying == &spv->type_f32 && member_name.count == 2)
							swizzle_result_type = &spv->type_f32v2;
						else if (comp_type->underlying == &spv->type_f32 && member_name.count == 3)
							swizzle_result_type = &spv->type_f32v3;
						else if (comp_type->underlying == &spv->type_f32 && member_name.count == 4)
							swizzle_result_type = &spv->type_f32v4;
						else if (comp_type->underlying == &spv->type_u32 && member_name.count == 2)
							swizzle_result_type = &spv->type_u32v2;
						else if (comp_type->underlying == &spv->type_u32 && member_name.count == 3)
							swizzle_result_type = &spv->type_u32v3;
						else if (comp_type->underlying == &spv->type_u32 && member_name.count == 4)
							swizzle_result_type = &spv->type_u32v4;
						else if (comp_type->underlying == &spv->type_s32 && member_name.count == 2)
							swizzle_result_type = &spv->type_s32v2;
						else if (comp_type->underlying == &spv->type_s32 && member_name.count == 3)
							swizzle_result_type = &spv->type_s32v3;
						else if (comp_type->underlying == &spv->type_s32 && member_name.count == 4)
							swizzle_result_type = &spv->type_s32v4;
						else
							assert(false);
						
						last_base_id = spv_push_op_vector_shuffle(spv, block, swizzle_result_type->type_id, last_base_id, last_base_id, indices, member_name.count);
						last_base_type = swizzle_result_type;
						last_type = swizzle_result_type;
						
						// Its a swizzle so it no longer has storage
						accessing_storage = false;
						
						if (in_memory) {
							spv->compiler->err_log = _osl_tprint_token(spv->compiler, access->items[i].token+1, STR("This swizzle/subvector is used as if it has storage. Swizzles/subvectors are non-storage values"));
							return spv->compiler->result = OSL_SWIZZLE_USED_AS_STORAGE;
						}
					}
				} else assert(false);
			}
		}
		// #Copypaste
		if (arg_count > 0) {
			if (accessing_storage) {
				u32 id_type_pointer = spv_push_decl_pointer_type(spv, &spv->const_block, last_type->type_id, base_storage_class);
				last_base_id 
					= spv_push_op_access_chain(spv, block, id_type_pointer, last_base_id, args, arg_count);
					
				if (!in_memory) {
					last_base_id = spv_push_op_load(spv, block, last_base_id, last_type->type_id);
				}
			} else {
				last_base_id 
					= spv_push_op_composite_extract(spv, block, last_base_id, last_type->type_id, args, arg_count);
			}
			last_base_type = last_type;
		}
		
		*result_id = last_base_id;
		*type = last_base_type;
		
		break;
	}
	
	case OSL_EXPR_LITERAL_FLOAT: {
		assert(!in_memory);
		
		*result_id = spv_push_decl_constant_f32(spv, &spv->const_block, spv->type_f32.type_id, (float32)expr->val.lit.lit_flt);
		*type = &spv->type_f32;
		break;
	}
	case OSL_EXPR_LITERAL_INT: {
		assert(!in_memory);
	
		*result_id = spv_push_decl_constant_u32(spv, &spv->const_block, spv->type_u32.type_id, (u32)expr->val.lit.lit_int);
		*type = &spv->type_u32;
		break;
	}
	case OSL_EXPR_DECL_IDENT: {
		
	
		*type = _osl_resolve_type(spv, expr->val.decl->type_ident);
		if (!(*type)) {
			spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(expr)->first_token, STR("Unresolved type"));
			return spv->compiler->result = OSL_UNRESOLVED_TYPE;
		}
		
		u32 id_pointer = (u32)expr->val.decl->vnum;
		if (in_memory) {
			*result_id = id_pointer;
		} else {
			if (expr->val.decl->spv_loaded_id == 0) {
				*result_id = spv_push_op_load(spv, block, id_pointer, (*type)->type_id);
				expr->val.decl->spv_loaded_id = *result_id;
			} else {
				*result_id = expr->val.decl->spv_loaded_id;
			}
		}
		break;
	}
	case OSL_EXPR_TYPE_IDENT: // fallthrough
	default: {
		assert(false);
		break;
	}
	
	}
	
	assert(*result_id);
	assert(*type);
	return OSL_OK;
}

unit_local Osl_Result spv_emit_node(Spv_Converter *spv, Spv_Block *block, Osl_Node *node) {

	switch (node->kind) {
	case OSL_NODE_BLOCK: {
		for (u32 i = 0; i < node->val.block.node_count; i += 1) {
			Osl_Result res = spv_emit_node(spv, block, node->val.block.nodes[i]);
			if (res != OSL_OK) return res;
		}
		break;
	}
	case OSL_NODE_VALUE_DECL: {
		
		Osl_Value_Decl *decl = &node->val.value_decl;
		
		Osl_Type_Info *decl_type = _osl_resolve_type(spv, decl->type_ident);
		
		if (!decl_type) {
			spv->compiler->err_log = _osl_tprint_token(spv->compiler, decl->type_ident.token, STR("Unresolved type"));
			return spv->compiler->result = OSL_UNRESOLVED_TYPE;
		}
		
		u32 type_id = decl_type->type_id;
		assert(type_id);
		
		spv_begin_op(&spv->debug_block, OpName);
		spv_push_word(&spv->debug_block, (u32)decl->vnum);
		spv_push_string_arg(&spv->debug_block, decl->ident);
		spv_end_op(&spv->debug_block);
		
		Spv_Storage_Class storage_class = SpvStorageClass_Private;
		
		if (decl->storage_class != OSL_STORAGE_DEFAULT) {
			
			switch (decl->storage_class) {
				
			case OSL_STORAGE_INPUT:  storage_class = SpvStorageClass_Input; break;
			case OSL_STORAGE_OUTPUT: storage_class = SpvStorageClass_Output; break;
			
			case OSL_STORAGE_DEFAULT: // fallthrough
			default: assert(false); break;
			}
		}
		
		type_id = spv_push_decl_pointer_type(spv, &spv->const_block, type_id, storage_class);
		
		assert(decl->vnum > 0);
		spv_push_decl_variable(spv, &spv->const_block, storage_class, type_id, 0, decl->ident, (u32)decl->vnum);
		
		if (decl->storage_class != OSL_STORAGE_DEFAULT) {
			
			switch (decl->storage_class) {
				
			case OSL_STORAGE_INPUT: // Fallthrough
			case OSL_STORAGE_OUTPUT:
				
				if (decl->builtin_kind == OSL_BUILTIN_NONE) {
					if (decl->storage_args.arg_count != 1) {
						spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(decl)->first_token, tprint("Expected exactly 1 integer argument for location. Got '%i' arguments.", decl->storage_args.arg_count));
						return spv->compiler->result = OSL_BAD_DECORATION_ARGUMENTS;
					}
					
					if (decl->storage_args.args[0]->kind != OSL_EXPR_LITERAL_INT) {
						spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(decl)->first_token, tprint("Expected exactly 1 INTEGER argument for location."));
						return spv->compiler->result = OSL_BAD_DECORATION_ARGUMENTS;
					}
				}
				
				if (decl->storage_args.arg_count >= 1) {
					spv_push_decoration(&spv->annotations_block, (u32)decl->vnum, SpvDecoration_Location, (u32*)&decl->storage_args.args[0]->val.lit.lit_int, 1); 
				}
				break;
			
			case OSL_STORAGE_DEFAULT: // fallthrough
			default: assert(false); break;
			}
		}
		
		switch (decl->builtin_kind)
		{
		case OSL_BUILTIN_VERTEX_POSITION: {
			u32 arg = SpvBuiltin_Position;
			spv_push_decoration(&spv->annotations_block, (u32)decl->vnum, SpvDecoration_Builtin, &arg, 1); 
			break;
		}
		case OSL_BUILTIN_VERTEX_ID: {
			u32 arg = SpvBuiltin_VertexId;
			spv_push_decoration(&spv->annotations_block, (u32)decl->vnum, SpvDecoration_Builtin, &arg, 1); 
			break;
		}
		case OSL_BUILTIN_VERTEX_INDEX: {
			u32 arg = SpvBuiltin_VertexIndex;
			spv_push_decoration(&spv->annotations_block, (u32)decl->vnum, SpvDecoration_Builtin, &arg, 1); 
			break;
		}
		case OSL_BUILTIN_INSTANCE_ID: {
			u32 arg = SpvBuiltin_InstanceId;
			spv_push_decoration(&spv->annotations_block, (u32)decl->vnum, SpvDecoration_Builtin, &arg, 1); 
			break;
		}
		case OSL_BUILTIN_INSTANCE_INDEX: {
			u32 arg = SpvBuiltin_InstanceIndex;
			spv_push_decoration(&spv->annotations_block, (u32)decl->vnum, SpvDecoration_Builtin, &arg, 1); 
			break;
		}
		case OSL_BUILTIN_NONE: // fallthrough
		default:
			break;
		}
		
		if (decl->init_expr) {
			u32 result_id;
			Osl_Type_Info *type;
			Osl_Result res = spv_emit_expr(spv, block, decl->init_expr, &result_id, &type, false);
			if (res != OSL_OK) return res;
			assert(result_id); assert(type);
			
			if (type != decl_type) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(decl->init_expr)->first_token, tprint("Expression type '%s' does not match value declaration type '%s'", type->name, decl_type->name));
				return spv->compiler->result = OSL_CANNOT_CONVERT_TYPES;
			}
			
			spv_push_op_store(block, (u32)decl->vnum, result_id);
			decl->spv_loaded_id = 0;
		}
		
		break;
	}
	case OSL_NODE_EXPR: {
		u32 _;
		Osl_Type_Info *__;
		Osl_Result res = spv_emit_expr(spv, block, &node->val.expr, &_, &__, false);
		if (res != OSL_OK) return res;
		assert(_); assert(__);
		
		break;
	}
	default: assert(false); break;
	}
	
	return OSL_OK;
}

unit_local void _osl_tokenize(Osl_Compiler *compiler) {
    string source = compiler->source;
    u8 *p = source.data;
	while (p < source.data + source.count) {
		u8 *end = source.data + source.count;
		while (is_whitespace(*p)) { p += 1; }

		while (p[0] == '/' && (p[1] == '/' || p[1] == '*')) {
			while (p[0] == '/' && p[1] == '/') {
				while (p < end && *p != '\n') { p += 1; }
				if (*p == '\n') p += 1;
			}
			while (is_whitespace(*p)) { p += 1; }
			u32 depth = 0;
			while (p[0] == '/' && p[1] == '*') {
				while ((p+1) < end && !(p[0] == '*' && p[1] == '/' && depth == 1)) {  
					if (p[0] == '/' && p[1] == '*') depth += 1;
					if (p[0] == '*' && p[1] == '/') depth -= 1;
					p += 1;
				}
				if (p[0] == '*' && p[1] == '/') { p += 2; }
			}
			while (is_whitespace(*p)) { p += 1; }
		}
		while (is_whitespace(*p)) { p += 1; }
		
		Osl_Token *token = (Osl_Token*)arena_push(&compiler->token_arena, sizeof(Osl_Token));
		compiler->token_count += 1;
		token->source_pos = (u64)(p-source.data);

		if (is_alpha(*p) || *p == '_') {
			
			while (is_alpha(*p) || *p == '_' || is_digit(*p)) {p += 1;}
			
			token->length = (u64)(p-source.data)-token->source_pos;
			token->kind = OSL_TOKEN_KIND_IDENTIFIER;
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
			token->kind = dot ? OSL_TOKEN_KIND_FLOAT_LITERAL : OSL_TOKEN_KIND_INT_LITERAL;
			continue;
		}
		
		if (p < end-2 && strings_match((string){2, p}, STR("->"))) {
			token->length = 2;
			token->kind = OSL_TOKEN_KIND_RIGHT_ARROW;
			p += 2;
			continue;
		}
		
		if (*p >= OSL_TOKEN_KIND_SINGLE_PUNC_START && *p < OSL_TOKEN_KIND_SINGLE_PUNC_END) {
			token->kind = (Osl_Token_Kind)*(p++);
			token->length = (u64)(p-source.data)-token->source_pos;
			continue;
		}
		
		if (p == source.data+source.count) {
			token->source_pos = source.count-1;
			token->length = 1;
			token->kind = OSL_TOKEN_KIND_EOF;
			continue;
		}
	}
	
	// It's not retarded if it's shipper
	for (u64 i = 0; i < 10000; i += 1) {
		Osl_Token *token = (Osl_Token*)arena_push(&compiler->token_arena, sizeof(Osl_Token));
		compiler->token_count += 1;
		token->source_pos = source.count-1;
		token->length = 1;
		token->kind = OSL_TOKEN_KIND_EOF;
	}
}

unit_local string _osl_tprint_token(Osl_Compiler *compiler, Osl_Token *token, string message) {
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
	
	string kind_str = _osl_stringify_token_kind(token->kind);
	return tprint("Line %u, Token '%s' (%s): %s\n    %s\n    %s%s\n", line_counter, token_str, kind_str, message, line, space, arrows);
}

unit_local bool _osl_exp_token(Osl_Compiler *compiler, Osl_Token *token, Osl_Token_Kind kind) {
	if (token->kind != kind) {
		compiler->result = OSL_UNEXPECTED_TOKEN;
		string kind_str = _osl_stringify_token_kind(kind);
		compiler->err_log = _osl_tprint_token(compiler, token, tprint("Unexpected token. Expected '%s', got this", kind_str));
		return false;
	}
	return true;
}
unit_local bool _osl_exp_token_msg(Osl_Compiler *compiler, Osl_Token *token, Osl_Token_Kind kind, string msg) {
	if (token->kind != kind) {
		compiler->result = OSL_UNEXPECTED_TOKEN;
		string kind_str = _osl_stringify_token_kind(kind);
		compiler->err_log = _osl_tprint_token(compiler, token, tprint("Unexpected token: %s. Expected '%s', got this", msg, kind_str));
		return false;
	}
	return true;
}

unit_local Osl_Expr *_osl_parse_expr(Osl_Compiler *compiler, Osl_Token *expr_start, Osl_Token **done_token);

unit_local Osl_Result _osl_parse_type_ident(Osl_Compiler *compiler, Osl_Token *first, Osl_Token **done_token, Osl_Type_Ident *result) {
	*result = (Osl_Type_Ident) {0};
	result->token = first;
	if (first->kind == OSL_TOKEN_KIND_IDENTIFIER) {
		result->name = (string) { first->length, compiler->source.data + first->source_pos };
		*done_token = first+1;
		return OSL_OK;
	} 
	
	
	Osl_Token *next = first;
	
	while (next->kind == OSL_TOKEN_KIND_LBRACKET) {
		
		if (result->indirection_count >= 8) {
			compiler->err_log = _osl_tprint_token(compiler, next, STR("The max number of type indirections is 8. This exceeds that."));
			return compiler->result = OSL_EXCEED_MAX_TYPE_INDIRECTIONS;
		}
		
		Osl_Token *count_tok = next+1;
		
		Osl_Token *close_bracket;
		Osl_Expr *count_expr = _osl_parse_expr(compiler, count_tok, &close_bracket);
		
		// todo(charlie) parse expression and try to resolve it to an int otherwise err
		// Or maybe just make _osl_parse_expr resolve any literal ops and return a result literal instead ?
		if (count_expr->kind != OSL_EXPR_LITERAL_INT) {
			compiler->err_log = _osl_tprint_token(compiler, count_tok, STR("Expected a single integer literal. Compile-time expressions are not yet available."));
			return compiler->result = OSL_UNEXPECTED_TOKEN;
		}
		
		if (!_osl_exp_token(compiler, close_bracket, OSL_TOKEN_KIND_RBRACKET)) {
			return compiler->result;
		}
		
		
		result->indirections[result->indirection_count++].array_count = count_expr->val.lit.lit_int;
		
		next = close_bracket+1;
	}
	
	if (!_osl_exp_token_msg(compiler, next, OSL_TOKEN_KIND_IDENTIFIER, STR("Expected a type identifier"))) {
		return compiler->result;
	}
	
	result->name = (string) { next->length, compiler->source.data + next->source_pos };
	
	*done_token = next+1;
	
	assert(result->token);
	return OSL_OK;
}

unit_local Osl_Result _osl_parse_arg_list(Osl_Compiler *compiler, Osl_Token_Kind close_token, Osl_Token *start, Osl_Token **done_token, Osl_Arg_List *list) {
	*list = (Osl_Arg_List){0};
	
	Osl_Token_Kind open_token = 0;
	if (close_token == OSL_TOKEN_KIND_RPAREN) {
		open_token = OSL_TOKEN_KIND_LPAREN;
	} else if (close_token == OSL_TOKEN_KIND_RBRACKET) {
		open_token = OSL_TOKEN_KIND_LBRACKET;
	} else if (close_token == OSL_TOKEN_KIND_RBRACE) {
		open_token = OSL_TOKEN_KIND_LBRACE;
	} else {
		assert(false);
	}
	
	if (!_osl_exp_token(compiler, start, open_token))
		return compiler->result;
	
	Osl_Token *next = start;
	
	while (next->kind != OSL_TOKEN_KIND_EOF && next->kind != close_token) {

		next += 1;
		assertmsg(list->arg_count < 128, "Exceeding max allowed argument count of 128");
		
		
		Osl_Token *sub_expr_start = next;
		Osl_Expr *arg = _osl_parse_expr(compiler, sub_expr_start, &next);
		if (!arg) return compiler->result;
		
		list->args[list->arg_count++] = arg;
		
		if (next->kind != close_token && !_osl_exp_token(compiler, next, OSL_TOKEN_KIND_COMMA)) {
			return compiler->result;
		}
		
	}
	if (!_osl_exp_token(compiler, next, close_token))
		return compiler->result;
	*done_token = next+1;
	return OSL_OK;
} 

unit_local bool _osl_does_token_terminate_expr(Osl_Token_Kind kind) {
	return kind == OSL_TOKEN_KIND_SEMICOLON
	    || kind == OSL_TOKEN_KIND_COMMA
	    || kind == OSL_TOKEN_KIND_RPAREN
	    || kind == OSL_TOKEN_KIND_RBRACKET;
}


unit_local Osl_Expr *_osl_parse_expr_rec(Osl_Compiler *compiler, Osl_Token *expr_start, Osl_Token **done_token, Osl_Op_Kind left_op);

unit_local Osl_Expr *_osl_parse_one_expr(Osl_Compiler *compiler, Osl_Token *expr_start, Osl_Token **done_token, Osl_Op_Kind left_op) {
	
	Osl_Expr *expr = 0;
	
	if (expr_start->kind == '-') {
		Osl_Expr *negated_expr = _osl_parse_expr(compiler, expr_start+1, done_token);
		if (!negated_expr) return 0;
		
		Osl_Node *op_expr_node = (Osl_Node*)arena_push(&compiler->node_arena, sizeof(Osl_Node));
		op_expr_node->first_token = expr_start;
	    op_expr_node->kind = OSL_NODE_EXPR;
	    compiler->total_node_count += 1;
	    compiler->current_block->nodes[compiler->current_block->node_count++] = op_expr_node;
		Osl_Expr *op_expr = &op_expr_node->val.expr;
		*op_expr = (Osl_Expr){0};
		op_expr->vnum = -1;
		op_expr->kind = OSL_EXPR_OP;
		
		op_expr->val.op.op_kind = OSL_OP_UNARY_NEGATE;
		op_expr->val.op.op_token = expr_start-1;
		op_expr->val.op.lhs = negated_expr;
		
		expr = op_expr;
	} else if (expr_start->kind == OSL_TOKEN_KIND_LPAREN) {
		Osl_Expr *enclosed_expr = _osl_parse_expr(compiler, expr_start+1, done_token);
		if (!enclosed_expr) return 0;
		
		if (!_osl_exp_token(compiler, *done_token, OSL_TOKEN_KIND_RPAREN)) {
			string b = _osl_tprint_token(compiler, expr_start, STR("Expected a match for this"));
			compiler->err_log = tprint("%s%s", compiler->err_log, b);
			return 0;
		}
		
		*done_token += 1;
		expr = enclosed_expr;
	} else {
	
		Osl_Node *expr_node = (Osl_Node*)arena_push(&compiler->node_arena, sizeof(Osl_Node));
		expr_node->first_token = expr_start;
	    expr_node->kind = OSL_NODE_EXPR;
	    compiler->total_node_count += 1;
	    compiler->current_block->nodes[compiler->current_block->node_count++] = expr_node;
		expr = &expr_node->val.expr;
		*expr = (Osl_Expr){0};
		expr->vnum = -1;
		
		string expr_ident = (string) { expr_start->length, compiler->source.data+expr_start->source_pos };
		if (expr_start->kind == OSL_TOKEN_KIND_IDENTIFIER) {
			if (expr_start[1].kind == OSL_TOKEN_KIND_DOT && (expr_start[2].kind == OSL_TOKEN_KIND_LPAREN || expr_start[2].kind == OSL_TOKEN_KIND_LBRACKET)) {
				expr->kind = OSL_EXPR_INSTANTIATE;
				
				Osl_Instantiation *inst = &expr->val.inst;
				
				Osl_Token_Kind list_end = OSL_TOKEN_KIND_RPAREN;
				
				if (expr_start[2].kind == OSL_TOKEN_KIND_LPAREN) {
					inst->kind = OSL_INST_COMP;
					list_end = OSL_TOKEN_KIND_RPAREN;
				} else if (expr_start[2].kind == OSL_TOKEN_KIND_LBRACKET) {
					inst->kind = OSL_INST_ARRAY;
					list_end = OSL_TOKEN_KIND_RBRACKET;
				} else 
					assert(false);
				
				Osl_Result type_res = _osl_parse_type_ident(compiler, expr_start, done_token, &inst->type_ident);
				if (type_res != OSL_OK) return 0;
				
				
				Osl_Result res = _osl_parse_arg_list(compiler, list_end, &expr_start[2], done_token, &inst->list);
				if (res != OSL_OK) return 0;
				
				if (inst->type_ident.indirection_count >= 8) {
					compiler->err_log = _osl_tprint_token(compiler, expr_start, STR("The max number of type indirections is 8. This exceeds that."));
					compiler->result = OSL_EXCEED_MAX_TYPE_INDIRECTIONS;
					return 0;
				}
				
			} else {
				expr->kind = OSL_EXPR_DECL_IDENT;
				for (u64 j = 0; j < compiler->current_block->node_count; j += 1) {
					Osl_Node *node = compiler->current_block->nodes[j];
					
					if (node->kind == OSL_NODE_VALUE_DECL) {
						Osl_Value_Decl *decl = &node->val.value_decl;
						if (strings_match(expr_ident, decl->ident)) {
							expr->val.decl = decl;
							expr->vnum = decl->vnum;
							break;
						}
					}
				}
				
				if (!expr->val.decl) {
					if (left_op != 0xFFFF && left_op == OSL_OP_CAST) {
						expr->kind = OSL_EXPR_TYPE_IDENT;
						Osl_Result type_res = _osl_parse_type_ident(compiler, expr_start, done_token, &expr->val.type_ident);
						if (type_res != OSL_OK) return 0;
						assert(expr->val.type_ident.token);
					} else {
						compiler->err_log = _osl_tprint_token(compiler, expr_start, tprint("No value named '%s' was defined here yet in this procedural block", expr_ident));
						compiler->result = OSL_UNDEFINED_VALUE;
						return 0;
					}
				}
				*done_token = expr_start+1;
			}
		} else if (expr_start->kind == OSL_TOKEN_KIND_FLOAT_LITERAL) {
			expr->kind = OSL_EXPR_LITERAL_FLOAT;
			bool conv_ok;
			expr->val.lit.lit_flt = string_to_float(expr_ident, &conv_ok);
			assert(conv_ok);
			*done_token = expr_start+1;
		} else if (expr_start->kind == OSL_TOKEN_KIND_INT_LITERAL) {
			expr->kind = OSL_EXPR_LITERAL_INT;
			bool conv_ok;
			expr->val.lit.lit_int = string_to_unsigned_int(expr_ident, 10, &conv_ok);
			assert(conv_ok);
			*done_token = expr_start+1;
		} else {
			compiler->err_log = _osl_tprint_token(compiler, expr_start, STR("Expected an expression here, but it is not recognized as such."));
			compiler->result = OSL_NOT_AN_EXPR;
			return 0;
		}
	}
	
	if ((*done_token)->kind == OSL_TOKEN_KIND_DOT || (*done_token)->kind == OSL_TOKEN_KIND_LBRACKET) {
		Osl_Token *next = *done_token;
		
		Osl_Node *parent_expr_node = (Osl_Node*)arena_push(&compiler->node_arena, sizeof(Osl_Node));
		parent_expr_node->first_token = expr_start;
	    parent_expr_node->kind = OSL_NODE_EXPR;
	    compiler->total_node_count += 1;
	    compiler->current_block->nodes[compiler->current_block->node_count++] = parent_expr_node;
		Osl_Expr *parent_expr = &parent_expr_node->val.expr;
		*parent_expr = (Osl_Expr){0};
		parent_expr->vnum = -1;
		parent_expr->kind = OSL_EXPR_ACCESS_CHAIN;
		
		Osl_Access_Chain *access = &parent_expr->val.access;
		
		access->base_expr = expr;
		expr = parent_expr;
		
		while (next->kind == OSL_TOKEN_KIND_DOT || next->kind == OSL_TOKEN_KIND_LBRACKET) {
			
			if (next->kind == OSL_TOKEN_KIND_DOT) {
				Osl_Token *access_token = next + 1;
				
				if (!_osl_exp_token(compiler, access_token, OSL_TOKEN_KIND_IDENTIFIER)) {
					return 0;
				}
				
				access->items[access->item_count].token = next;
				access->items[access->item_count++].val.name = (string) { access_token->length, compiler->source.data+access_token->source_pos };
				next = access_token + 1;
			} else if (next->kind == OSL_TOKEN_KIND_LBRACKET) {
				Osl_Token *access_token = next + 1;
				
				u64 access_index = access->item_count++;
				access->items[access_index].token = next;
				access->items[access_index].is_index = true;
				access->items[access_index].val.index = _osl_parse_expr(compiler, access_token, &next);
				if (!access->items[access_index].val.index) {
					return 0;
				}
				if (!_osl_exp_token(compiler, next, OSL_TOKEN_KIND_RBRACKET)) {
					return 0;
				}
				next += 1;
				
			} else {
				assert(false);
			}
			
			
		}
		
		*done_token = next;
	}
	
	return expr;
}
unit_local Osl_Expr *_osl_parse_expr_rec(Osl_Compiler *compiler, Osl_Token *expr_start, Osl_Token **done_token, Osl_Op_Kind left_op) {

	Osl_Expr *lexpr = _osl_parse_one_expr(compiler, expr_start, done_token, left_op);
	if (!lexpr)  return 0;
	
	if (_osl_does_token_terminate_expr((*done_token)->kind)) {
		return lexpr;
	}
	
	Osl_Token *op_token = *done_token;
	
	Osl_Op_Kind rop;
	if (op_token->kind == '+') rop = OSL_OP_ADD;
	else if (op_token->kind == '-') rop = OSL_OP_SUB;
	else if (op_token->kind == '*') rop = OSL_OP_MUL;
	else if (op_token->kind == '/') rop = OSL_OP_DIV;
	else if (op_token->kind == '=') rop = OSL_OP_SET;
	else if (op_token->kind == OSL_TOKEN_KIND_RIGHT_ARROW) rop = OSL_OP_CAST;
	else {
		compiler->err_log = _osl_tprint_token(compiler, op_token, STR("Bad operator"));
		compiler->result = OSL_BAD_OPERATOR;
		return 0;
	}
	
	
	
	if (left_op != 0xffff && _osl_precedence(left_op) >= _osl_precedence(rop)) {
		*done_token = op_token;
		return lexpr;
	} else {
		Osl_Expr *rexpr = _osl_parse_expr_rec(compiler, op_token+1, done_token, rop);
		
		if (!rexpr) 
			return 0;
		
		Osl_Node *parent_node = (Osl_Node*)arena_push(&compiler->node_arena, sizeof(Osl_Node));
        parent_node->first_token = expr_start;
        parent_node->kind = OSL_NODE_EXPR;
        compiler->total_node_count += 1;
        compiler->current_block->nodes[compiler->current_block->node_count++] = parent_node;
		Osl_Expr *parent_op = &parent_node->val.expr;
		*parent_op = (Osl_Expr){0};
		parent_op->vnum = -1;
		parent_op->kind = OSL_EXPR_OP;
		parent_op->val.op.op_kind = rop;
		parent_op->val.op.op_token = op_token;
		
		if (rop == OSL_OP_SET && !_osl_can_expr_have_storage(lexpr)) {
			Osl_Node *rop_node = _osl_get_node(parent_op);
			compiler->err_log = _osl_tprint_token(compiler, rop_node->first_token, STR("Cannot assign to an expression that does not have storage"));
			compiler->result = OSL_ASSIGN_NON_STORAGE_VALUE;
			return 0;
		}
		
		parent_op->val.op.lhs = lexpr;
		parent_op->val.op.rhs = rexpr;
		
		if (parent_op->val.op.op_kind == OSL_OP_CAST) {
			if (parent_op->val.op.rhs->kind != OSL_EXPR_TYPE_IDENT) {
				Osl_Token *tok = _osl_get_node(parent_op->val.op.rhs)->first_token;
				string tok_string = (string) {tok->length, compiler->source.data+tok->source_pos };
				compiler->err_log = _osl_tprint_token(compiler, tok, tprint("Cannot cast to '%s'. This is not a type. If this looks like a type, make sure you haven't shadowed a type name with a value declaration", tok_string));
				compiler->result = OSL_INVALID_CAST;
				return 0;
			}
			
		}
		
		return parent_op;
	}
}
	
unit_local Osl_Expr *_osl_parse_expr(Osl_Compiler *compiler, Osl_Token *expr_start, Osl_Token **done_token) {


	Osl_Expr *last_expr = _osl_parse_expr_rec(compiler, expr_start, done_token, (Osl_Op_Kind)0xFFFF);
	if (!last_expr) return 0;
	
	while (!_osl_does_token_terminate_expr((*done_token)->kind)) {
		Osl_Token *op_token = *done_token;
		
		Osl_Op_Kind rop;
		if (op_token->kind == '+') rop = OSL_OP_ADD;
		else if (op_token->kind == '-') rop = OSL_OP_SUB;
		else if (op_token->kind == '*') rop = OSL_OP_MUL;
		else if (op_token->kind == '/') rop = OSL_OP_DIV;
		else if (op_token->kind == '=') rop = OSL_OP_SET;
		else if (op_token->kind == OSL_TOKEN_KIND_RIGHT_ARROW) rop = OSL_OP_CAST;
		else {
			compiler->err_log = _osl_tprint_token(compiler, op_token, STR("Bad operator"));
			compiler->result = OSL_BAD_OPERATOR;
			return 0;
		}
		
		Osl_Token *next_expr_start = op_token+1;
		
		Osl_Expr *next_expr = _osl_parse_expr_rec(compiler, next_expr_start, done_token, rop);
		if (!next_expr) return 0;
		
		Osl_Node *next = (Osl_Node*)arena_push(&compiler->node_arena, sizeof(Osl_Node));
        next->first_token = expr_start;
        next->kind = OSL_NODE_EXPR;
        compiler->total_node_count += 1;
        compiler->current_block->nodes[compiler->current_block->node_count++] = next;
		Osl_Expr *next_op = &next->val.expr;
		*next_op = (Osl_Expr){0};
		next_op->vnum = -1;
		next_op->kind = OSL_EXPR_OP;
		next_op->val.op.op_kind = rop;
		next_op->val.op.op_token = op_token;
		if (last_expr->kind == OSL_EXPR_OP && _osl_precedence(rop) > _osl_precedence(last_expr->val.op.op_kind)) {
			next_op->val.op.lhs = last_expr->val.op.rhs;
			next_op->val.op.rhs = next_expr;
			last_expr->val.op.rhs = next_op;
		} else {
			next_op->val.op.lhs = last_expr;
			next_op->val.op.rhs = next_expr;
			last_expr = next_op;
		}
		
		if (last_expr->val.op.op_kind == OSL_OP_CAST) {
			if (last_expr->val.op.rhs->kind != OSL_EXPR_TYPE_IDENT) {
				Osl_Token *tok = _osl_get_node(last_expr->val.op.rhs)->first_token;
				string tok_string = (string) {tok->length, compiler->source.data+tok->source_pos };
				compiler->err_log = _osl_tprint_token(compiler, tok, tprint("Cannot cast to '%s'. This is not a type, so that doesn't make sense.", tok_string));
				compiler->result = OSL_INVALID_CAST;
				return 0;
			}
		}
		
		if (rop == OSL_OP_SET && !_osl_can_expr_have_storage(last_expr->val.op.lhs)) {
			Osl_Node *rop_node = _osl_get_node(next_op);
			compiler->err_log = _osl_tprint_token(compiler, rop_node->first_token, STR("Cannot assign to an expression that does not have storage"));
			compiler->result = OSL_ASSIGN_NON_STORAGE_VALUE;
			return 0;
		}
	}
	
	return last_expr;
}

Osl_Result osl_compile(Allocator a, Osl_Compile_Desc desc, void **pcode, u64 *pcode_size, string *err_log) {
    (void)a;
    (void)pcode;
    (void)pcode_size;
    Osl_Compiler *compiler = PushTemp(Osl_Compiler);
    compiler->source = string_replace(get_temp(), desc.code_text, STR("\t"), STR(""));
    compiler->next_vnum = 1;
    compiler->program_kind = desc.program_kind;
    compiler->token_arena = make_arena(1024*1024*1024*69, 1024*100);
    compiler->tokens = (Osl_Token*)compiler->token_arena.start;
    compiler->node_arena = make_arena(1024*1024*1024*69, 1024*100);
    compiler->result = OSL_OK;
    compiler->top_block.is_procedural = true;
    compiler->current_block = &compiler->top_block;
    
    _osl_tokenize(compiler);
    
    Osl_Token *current = compiler->tokens;
    
    while (current->kind != OSL_TOKEN_KIND_EOF) {
    	Osl_Token *first = current;
        Osl_Token *next = ++current;
    	assert(current->kind != OSL_TOKEN_KIND_UNKNOWN);
    	assert(next->kind != OSL_TOKEN_KIND_UNKNOWN);
        if (first->kind == OSL_TOKEN_KIND_IDENTIFIER) {
        	if (next->kind == ':') {
        		
	            Osl_Node *n = (Osl_Node*)arena_push(&compiler->node_arena, sizeof(Osl_Node));
	            n->kind = OSL_NODE_VALUE_DECL;
	            n->first_token = first;
	            compiler->total_node_count += 1;
	            compiler->top_block.nodes[compiler->top_block.node_count++] = n;
	            Osl_Value_Decl *decl = &n->val.value_decl;
	            *decl = (Osl_Value_Decl){0};
	           
	            decl->ident = (string) { first->length, compiler->source.data+first->source_pos };
	            
	            Osl_Token *prev_defined_token = 0;
	            for (u64 j = 0; j < compiler->current_block->node_count-1; j += 1) {
					Osl_Node *node = compiler->current_block->nodes[j];
					if (node->kind == OSL_NODE_VALUE_DECL) {
						Osl_Value_Decl *existing_decl = &node->val.value_decl;
						if (strings_match(decl->ident, existing_decl->ident)) {
							prev_defined_token = _osl_get_node(existing_decl)->first_token;
							break;
						}
					}
				}
				
				if (prev_defined_token) {
					string msga = _osl_tprint_token(compiler, first, STR("Redefinition of value symbol ... "));
					string msgb = _osl_tprint_token(compiler, prev_defined_token, STR("... Previously defined here"));
					compiler->err_log = tprint("%s%s", msga, msgb);
					compiler->result = OSL_VALUE_NAME_REDIFINITION;
					break;
				}
	            
	            Osl_Token *type_token = ++current;
	            
	            Osl_Result type_res = _osl_parse_type_ident(compiler, type_token, &current, &decl->type_ident);
	            if (type_res != OSL_OK) break;
	            
	            next = current;
	             
	            if (next->kind == '$') {
	            	
	            	Osl_Token *deco_token = ++current;
	            	
		            if (!_osl_exp_token(compiler, deco_token, OSL_TOKEN_KIND_IDENTIFIER))
		            	break;
	            	
	            	string decoration_string = (string) { deco_token->length, compiler->source.data+deco_token->source_pos };
	            	
	            	if ((compiler->program_kind == OSL_PROGRAM_GPU_VERTEX
            		   || compiler->program_kind == OSL_PROGRAM_GPU_FRAGMENT)
            		   && strings_match(decoration_string, STR("Input"))) {
	            		decl->storage_class = OSL_STORAGE_INPUT;
	            		Osl_Result res = _osl_parse_arg_list(compiler, OSL_TOKEN_KIND_RPAREN, ++current, &current, &decl->storage_args);
						if (res != OSL_OK) break;
						if (decl->builtin_kind == OSL_BUILTIN_NONE && decl->storage_args.arg_count != 1) {
							compiler->err_log = _osl_tprint_token(compiler, deco_token, tprint("Expected exactly 1 integer argument, but got %i", decl->storage_args.arg_count));
							compiler->result = OSL_BAD_DECORATION_ARGUMENTS;
							break;
						}
	            	} else if ((compiler->program_kind == OSL_PROGRAM_GPU_VERTEX
	            		   || compiler->program_kind == OSL_PROGRAM_GPU_FRAGMENT)
	            		   && strings_match(decoration_string, STR("Output"))) {
	            		decl->storage_class = OSL_STORAGE_OUTPUT;
	            		Osl_Result res = _osl_parse_arg_list(compiler, OSL_TOKEN_KIND_RPAREN, ++current, &current, &decl->storage_args);
						if (res != OSL_OK) break;
						if (decl->builtin_kind == OSL_BUILTIN_NONE && decl->storage_args.arg_count != 1) {
							compiler->err_log = _osl_tprint_token(compiler, deco_token, tprint("Expected exactly 1 integer argument, but got %i", decl->storage_args.arg_count));
							compiler->result = OSL_BAD_DECORATION_ARGUMENTS;
							break;
						}
	            	} else if ((compiler->program_kind == OSL_PROGRAM_GPU_VERTEX
	            		   || compiler->program_kind == OSL_PROGRAM_GPU_FRAGMENT)
	            		   && (strings_match(decoration_string, STR("VertexPosition")))) {
	            		decl->builtin_kind = OSL_BUILTIN_VERTEX_POSITION;
	            		if (compiler->program_kind == OSL_PROGRAM_GPU_VERTEX) {
	            			decl->storage_class = OSL_STORAGE_OUTPUT;
	            		} else if (compiler->program_kind == OSL_PROGRAM_GPU_VERTEX) {
	            			decl->storage_class = OSL_STORAGE_INPUT;
	            		} else assert(false);
	            		current += 1;
	            	} else if (compiler->program_kind == OSL_PROGRAM_GPU_VERTEX && strings_match(decoration_string, STR("VertexId"))) {
	            		decl->builtin_kind = OSL_BUILTIN_VERTEX_ID;
	            		decl->storage_class = OSL_STORAGE_INPUT;
	            		current += 1;
	            	} else if (compiler->program_kind == OSL_PROGRAM_GPU_VERTEX && strings_match(decoration_string, STR("VertexIndex"))) {
	            		decl->builtin_kind = OSL_BUILTIN_VERTEX_INDEX;
	            		decl->storage_class = OSL_STORAGE_INPUT;
	            		current += 1;
	            	} else if (compiler->program_kind == OSL_PROGRAM_GPU_VERTEX && strings_match(decoration_string, STR("InstanceId"))) {
	            		decl->builtin_kind = OSL_BUILTIN_INSTANCE_ID;
	            		decl->storage_class = OSL_STORAGE_INPUT;
	            		current += 1;
	            	} else if (compiler->program_kind == OSL_PROGRAM_GPU_VERTEX && strings_match(decoration_string, STR("InstanceIndex"))) {
	            		decl->builtin_kind = OSL_BUILTIN_INSTANCE_INDEX;
	            		decl->storage_class = OSL_STORAGE_INPUT;
	            		current += 1;
	            	} else {
	            		compiler->err_log = _osl_tprint_token(compiler, deco_token, STR("Invalid declaration token"));
	            		compiler->result = OSL_BAD_DECL_CLASS;
	            		break;
	            	}
	            	
	            	
	            	next = current;
	            }
	         	if (next->kind == '=') {
	            	decl->init_expr = _osl_parse_expr(compiler, next+1, &current);
	            	if (!decl->init_expr)
	            		break;
	            }	
	            
	            if (!_osl_exp_token(compiler, current++, (Osl_Token_Kind)';'))
	            	break;
	            	
	            decl->vnum = compiler->next_vnum++;
	            
	            compiler->top_nodes[compiler->top_node_count++] = _osl_get_node(decl);
	           
        	} else {
        		Osl_Expr *expr = _osl_parse_expr(compiler, first, &current);
	            if (!expr) {
	            	break;
	            }
	            if (!_osl_exp_token(compiler, current++, OSL_TOKEN_KIND_SEMICOLON)) {
	            	break;
	            }
	            compiler->top_nodes[compiler->top_node_count++] = _osl_get_node(expr);
        	}
        } else {
        	compiler->err_log = _osl_tprint_token(compiler, first, STR("Unable to infer intent with this top-level statement"));
            compiler->result =  OSL_UNEXPECTED_TOKEN;
        	break;
        }
    }
    
    switch (desc.target) {
        case OSL_TARGET_SPIRV:
            break;
        default:
            assert(false); break;
    }
    
    if (compiler->result != OSL_OK) {
        if (err_log) *err_log = compiler->err_log;
    } else {
    
    	Spv_Converter *spv = PushTemp(Spv_Converter);
    	spv_init(spv, compiler, (u32)compiler->next_vnum);
    	
    	for (u64 i = 0; i < compiler->top_node_count; i += 1) {
    		Osl_Node *n = compiler->top_nodes[i];
    		if (n->kind == OSL_NODE_VALUE_DECL && n->val.value_decl.storage_class != OSL_STORAGE_DEFAULT)
    			spv_emit_node(spv, &spv->const_block, n);    		
    		else
    			spv_emit_node(spv, &spv->entry_block, n); 
    			
    		if (compiler->result != OSL_OK) break;
    	} 
    	
		if (compiler->result == OSL_OK) {
	    	Spv_Block *block = spv_finalize(spv);
	    	*pcode = block->data;
	    	*pcode_size = block->count;
		}
    }
    
    if (compiler->result != OSL_OK) {
        if (err_log) *err_log = compiler->err_log;
    }
    return compiler->result;
}

#endif // OSTD_IMPL
