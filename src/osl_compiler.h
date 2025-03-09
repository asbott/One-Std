
#ifndef _OSL_COMPILER_H
#define _OSL_COMPILER_H

#ifndef _BASE_H
#include "base.h"
#endif // _BASE_H
#ifndef _STRING_H
#include "string.h"
#endif // _STRING_H
#ifndef _MEMORY_H
#include "memory.h"
#endif // _MEMORY_H
#ifndef _SYSTEM_1_H
#include "system1.h"
#endif // _SYSTEM_1_H
#ifndef _PRINT_H
#include "print.h"
#endif // _PRINT_H

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
    OSL_UNRESOLVED_FUNCTION_OR_INTRINSIC,
    OSL_BAD_CALL_ARGUMENTS,
    OSL_NOT_A_LOGICAL_TYPE,
    OSL_PROCEDURAL_STATEMENT_IN_NON_PROCEDURAL_BLOCK,
    OSL_TYPE_REDEFINITION,
    OSL_NO_SUCH_MEMBER,
    OSL_VIEW_INSTANTIATION,
    OSL_VIEW_CAST,
    OSL_BLOCK_TYPE_IS_NOT_STRUCT,
    OSL_FEATURE_NOT_ENABLED,
    OSL_UNSIZED_ARRAY_NOT_AT_END_OF_STRUCT,
    OSL_INVALID_FBUFFER_VIEW,
    OSL_UNIMPLEMENTED,
} Osl_Result;

typedef enum Osl_Target {
    OSL_TARGET_SPIRV_VULKAN,
} Osl_Target;
typedef enum Osl_Program_Kind {
    OSL_PROGRAM_GPU_FRAGMENT,
    OSL_PROGRAM_GPU_VERTEX,
    OSL_PROGRAM_GPU_COMPUTE,
} Osl_Program_Kind;

typedef enum Osl_Feature_Flag_ {
	OSL_FEATURE_INVOCATION_PIXEL_INTERLOCK = 1 << 1,
} Osl_Feature_Flag_;
typedef u64 Osl_Feature_Flag;

typedef struct Osl_Compile_Desc {
    Osl_Target target;
    Osl_Program_Kind program_kind;
    string code_text;
    Osl_Feature_Flag enabled_features;
} Osl_Compile_Desc;

Osl_Result osl_compile(Allocator a, Osl_Compile_Desc desc, void **pcode, u64 *pcode_size, string *err_log);

#ifdef OSTD_IMPL

typedef enum Spv_Op_Code_Enum {
    OpCapability           = 17,
    OpExtension           = 10,
    OpExtInstImport           = 11,
    OpExtInst           = 12,
    OpMemoryModel          = 14,
    OpEntryPoint           = 15,
    OpTypeSampledImage = 27,
    OpFunction             = 54,
    OpFunctionParameter    = 55,
    OpFunctionEnd          = 56,
    OpTypeVoid             = 19,
    OpTypeFunction         = 33,
    OpTypeBool             = 20,
    OpTypeInt              = 21,
    OpTypeFloat            = 22,
    OpTypeVector           = 23,
    OpTypeArray            = 28,
    OpTypeRuntimeArray            = 29,
    OpTypeStruct            = 30,
    OpExecutionMode        = 16,
    OpLabel                = 248,
    OpBranch                = 249,
    OpBranchConditional                = 250,
    OpReturn               = 253,
    OpTypePointer          = 32,
    OpTypeImage          = 25,
    OpTypeSampler          = 26,
    OpVariable             = 59,
    OpDecorate             = 71,
    OpMemberDecorate             = 72,
    OpLoad                 = 61,
    OpStore                = 62,
    OpCopyMemory           = 63,
    OpCompositeExtract     = 81,
    OpCompositeConstruct   = 80,
    OpConstant             = 43,
    OpConstantComposite    = 44,
    OpAccessChain          = 65,
    OpImageSampleImplicitLod = 87,
    OpImageRead = 98,
    OpImageWrite = 99,
    OpSampledImage = 86,
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
    OpName = 5,
    OpMemberName = 6,
    OpIEqual = 170,
    OpINotEqual = 171,
    OpFOrdEqual = 180,
    OpFOrdNotEqual = 182,
    OpLoopMerge = 246,
    OpSelectionMerge = 247,
    OpFOrdGreaterThan = 186,
    OpUGreaterThan = 172,
    OpSGreaterThan = 173,
    OpFOrdGreaterThanEqual = 190,
    OpUGreaterThanEqual = 174,
    OpSGreaterThanEqual = 175,
    OpFOrdLessThan = 184,
    OpULessThan = 176,
    OpSLessThan = 177,
    OpFOrdLessThanEqual = 189,
    OpULessThanEqual = 178,
    OpSLessThanEqual = 179,
    OpLogicalOr = 166,
    OpLogicalAnd = 167,
    OpSelect = 169,
    OpBeginInvocationInterlockEXT = 5364,
    OpEndInvocationInterlockEXT = 5365,
} Spv_Op_Code_Enum;

typedef enum Spv_Execution_Model {
    SpvExecutionModel_Vertex   = 0,
    SpvExecutionModel_Fragment = 4,
    SpvExecutionModel_Compute  = 5
} Spv_Execution_Model;

typedef enum Spv_Storage_Class {
    SpvStorageClass_UniformConstant       = 0,
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
    SpvCapability_Int64    = 11,
    SpvCapability_FragmentShaderPixelInterlockEXT = 5378,
    SpvCapability_FragmentShaderSampleInterlockEXT = 5363,
    SpvCapability_FragmentShaderShadingRateInterlockEXT = 5372,
} Spv_Capability;

typedef enum Spv_Decoration {
    SpvDecoration_Block    = 2,
    SpvDecoration_RowMajor    = 4,
    SpvDecoration_ColMajor    = 5,
    SpvDecoration_ArrayStride = 6,
    SpvDecoration_Builtin     = 11,
    SpvDecoration_Flat        = 14,
    SpvDecoration_Volatile    = 21,
    SpvDecoration_Location    = 30,
    SpvDecoration_Binding    = 33,
    SpvDecoration_DescriptorSet    = 34,
    SpvDecoration_Offset    = 35,
} Spv_Decoration;

typedef enum Spv_Builtin {
    SpvBuiltin_Position    = 0,
    SpvBuiltin_VertexId    = 5,
    SpvBuiltin_InstanceId    = 6,
    SpvBuiltin_FragCoord = 15,
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
	OSL_TYPE_IMAGE2DF,
	OSL_TYPE_FBUFFER2D,
	OSL_TYPE_SAMPLE_MODE,
	OSL_TYPE_BOOL,
	OSL_TYPE_STRUCT,
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
typedef struct Osl_Type_Info_Image {
	u32 sampled_type_id;
} Osl_Type_Info_Image;

typedef enum Osl_View_Type {
	OSL_VIEW_DEFAULT,
	OSL_VIEW_BLOCK,
	OSL_VIEW_RGBA32F,
	OSL_VIEW_RGBA16F,
	OSL_VIEW_R32F,
	OSL_VIEW_RGBA8_UNORM,
	OSL_VIEW_RGBA8_SNORM,
	OSL_VIEW_RGBA32U,
	OSL_VIEW_RGBA16U,
	OSL_VIEW_RGBA8U,
	OSL_VIEW_R32U,
	OSL_VIEW_RGBA32S,
	OSL_VIEW_RGBA16S,
	OSL_VIEW_RGBA8S,
	OSL_VIEW_R32S,
} Osl_View_Type;
typedef struct Osl_Type_Info_FBuffer2D {
	Osl_View_Type view_type;
} Osl_Type_Info_FBuffer2D;

typedef struct Osl_Type_Info_Struct {
	
	// todo(charlie) #memory #speed beeg
	
	string member_names[128];
	struct Osl_Type_Info *member_types[128];
	u64 member_offsets[128];
	u64 member_count;
	
} Osl_Type_Info_Struct;

typedef struct Osl_Type_Info {
	Osl_Type_Kind kind;
	u32 type_id;
	string name;
	u64 size;
	
	union {
		Osl_Type_Info_Composite comp_type;
		Osl_Type_Info_Int int_type;
		Osl_Type_Info_Array array_type;
		Osl_Type_Info_Image image_type;
		Osl_Type_Info_Struct struct_type;
		Osl_Type_Info_FBuffer2D fbuffer2d_type;
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
	
	u32 current_label;
	
	u32 next_id;
	u32 entry_id;
	
	u32 ext_glsl450_id;
	
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
    
    Osl_Type_Info type_bool;
    Osl_Type_Info type_boolv2;
    Osl_Type_Info type_boolv3;
    Osl_Type_Info type_boolv4;
    
    Osl_Type_Info type_image2df;
    
    Osl_Type_Info type_fbuffer2d_rgba32f;
    Osl_Type_Info type_fbuffer2d_rgba16f;
    Osl_Type_Info type_fbuffer2d_r32f;
    Osl_Type_Info type_fbuffer2d_rgba8_unorm;
    Osl_Type_Info type_fbuffer2d_rgba8_snorm;
    Osl_Type_Info type_fbuffer2d_rgba32u;
    Osl_Type_Info type_fbuffer2d_rgba16u;
    Osl_Type_Info type_fbuffer2d_rgba8u;
    Osl_Type_Info type_fbuffer2d_r32u;
    Osl_Type_Info type_fbuffer2d_rgba32s;
    Osl_Type_Info type_fbuffer2d_rgba16s;
    Osl_Type_Info type_fbuffer2d_rgba8s;
    Osl_Type_Info type_fbuffer2d_r32s;
    
    Osl_Type_Info type_sample_mode;
    
    Arena array_type_arena;
    Osl_Type_Info *array_types;
    u64 array_type_count;
    
    Arena struct_type_arena;
    Osl_Type_Info *struct_types;
    u64 struct_type_count;
	
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
	OSL_TOKEN_KIND_EXCLAMATION = '!',
	OSL_TOKEN_KIND_LT = '<',
	OSL_TOKEN_KIND_GT = '>',
	OSL_TOKEN_KIND_EQUALS = '=',
	OSL_TOKEN_KIND_PLUS = '+',
	OSL_TOKEN_KIND_MINUS = '-',
	OSL_TOKEN_KIND_FSLASH = '/',
	
	OSL_TOKEN_KIND_IDENTIFIER = 128,
	
	OSL_TOKEN_KIND_INT_LITERAL,
	OSL_TOKEN_KIND_FLOAT_LITERAL,
	
	OSL_TOKEN_KIND_EOF,
	
	OSL_TOKEN_KIND_RIGHT_ARROW,
	OSL_TOKEN_KIND_GTE,
	OSL_TOKEN_KIND_LTE,
	OSL_TOKEN_KIND_EQ,
	OSL_TOKEN_KIND_NEQ,
	OSL_TOKEN_KIND_LAND,
	OSL_TOKEN_KIND_LOR,
	OSL_TOKEN_KIND_DOUBLE_COLON,
	
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
		case OSL_TOKEN_KIND_EXCLAMATION: return STR("!");
		case OSL_TOKEN_KIND_LT: return STR("<");
		case OSL_TOKEN_KIND_GT: return STR(">");
		case OSL_TOKEN_KIND_EQUALS: return STR("=");
		case OSL_TOKEN_KIND_PLUS: return STR("+");
		case OSL_TOKEN_KIND_MINUS: return STR("-");
		case OSL_TOKEN_KIND_FSLASH: return STR("/");
		case OSL_TOKEN_KIND_GTE: return STR(">=");
		case OSL_TOKEN_KIND_LTE: return STR("<=");
		case OSL_TOKEN_KIND_EQ: return STR("==");
		case OSL_TOKEN_KIND_NEQ: return STR("!=");
		case OSL_TOKEN_KIND_LAND: return STR("&&");
		case OSL_TOKEN_KIND_LOR: return STR("||");
		case OSL_TOKEN_KIND_DOUBLE_COLON: return STR("::");
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
	Osl_View_Type view_type;
	
	string name;
} Osl_Type_Ident;

typedef enum Osl_Storage_Class {
	OSL_STORAGE_DEFAULT = 0,
	OSL_STORAGE_INPUT = 1,
	OSL_STORAGE_OUTPUT = 2,
	OSL_STORAGE_BINDING = 3,
} Osl_Storage_Class;
typedef enum Osl_Builtin_Kind {
	OSL_BUILTIN_NONE,
	OSL_BUILTIN_VERTEX_POSITION,
	OSL_BUILTIN_VERTEX_INDEX,
	OSL_BUILTIN_VERTEX_ID,
	OSL_BUILTIN_INSTANCE_INDEX,
	OSL_BUILTIN_INSTANCE_ID,
	OSL_BUILTIN_PIXEL_COORD,
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

typedef struct Osl_Call {
	string ident;
	Osl_Arg_List arg_list;
} Osl_Call;

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
	OSL_OP_UNARY_NAUGHT,
	OSL_OP_GT,
	OSL_OP_LT,
	OSL_OP_GTE,
	OSL_OP_LTE,
	OSL_OP_EQ,
	OSL_OP_NEQ,
	OSL_OP_LAND,
	OSL_OP_LOR,
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
		
	case OSL_OP_GT:
	case OSL_OP_LT:
	case OSL_OP_GTE:
	case OSL_OP_LTE:
		return 10;
	
	case OSL_OP_EQ:
	case OSL_OP_NEQ:
		return 5;
		
	case OSL_OP_LAND:
	case OSL_OP_LOR:
		return 1;
		
	case OSL_OP_UNARY_NAUGHT: // fallthrough
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
	OSL_EXPR_ALIAS_IDENT,
	OSL_EXPR_LITERAL_FLOAT,
	OSL_EXPR_LITERAL_INT,
	OSL_EXPR_TYPE_IDENT, 
	OSL_EXPR_INSTANTIATE,
	OSL_EXPR_ACCESS_CHAIN,
	OSL_EXPR_CALL,
} Osl_Expr_Kind;

struct Osl_Expr_Alias;
typedef struct Osl_Expr {
    Osl_Expr_Kind kind;
	union {
		Osl_Value_Decl *decl;
		struct Osl_Expr_Alias *expr_alias;
		Osl_Op op;
		union { u64 lit_int; f64 lit_flt; } lit;
		Osl_Instantiation inst;
		Osl_Type_Ident type_ident;
		Osl_Access_Chain access;
		Osl_Call call;
	} val;
} Osl_Expr;

typedef struct Osl_Expr_Alias {
	string ident;
	Osl_Expr *expr;
} Osl_Expr_Alias;

struct Osl_Node;
typedef struct Osl_Block {
	// todo(charlie) #speed #memory
	// buy more ram kid
	struct Osl_Node *nodes[4096];
	u64 node_count;
	struct Osl_Block *parent;
	u64 top_node_count;
    struct Osl_Node *top_nodes[2048];
	bool is_procedural;
} Osl_Block;

typedef struct Osl_If_Chain {
	// todo(charlie) #speed #memory
	Osl_Block *blocks[128];
	Osl_Expr *conditions[128]; // If last block is without condition, it's an else
	u64 branch_count;
	bool is_compile_time;
} Osl_If_Chain;
typedef struct Osl_Loop {
	Osl_Block *block;
	Osl_Expr *condition;
} Osl_Loop;

typedef struct Osl_Struct_Decl {
	string ident;
	Osl_Block *block;
} Osl_Struct_Decl;



typedef enum Osl_Node_Kind {
	OSL_NODE_BLOCK,
    OSL_NODE_VALUE_DECL,  
    OSL_NODE_EXPR,
    OSL_NODE_IF_CHAIN,
    OSL_NODE_LOOP,
    OSL_NODE_STRUCT_DECL,
    OSL_NODE_EXPR_ALIAS,
} Osl_Node_Kind;

typedef struct Osl_Node {
    Osl_Node_Kind kind;
    Osl_Token *first_token;
    union {
        Osl_Value_Decl value_decl;
        Osl_Expr expr;
        Osl_Block block;
        Osl_If_Chain if_chain;
        Osl_Loop loop;
        Osl_Struct_Decl struct_decl;
        Osl_Expr_Alias expr_alias;
    } val;
} Osl_Node;

unit_local Osl_Node *_osl_get_node(void *node_value) {
	u64 offset = offsetof(Osl_Node, val);
	return (Osl_Node*)((u8*)node_value - offset);
}

typedef struct Osl_Compiler {
    string source;
    Osl_Program_Kind program_kind;
    Osl_Feature_Flag enabled_features;
	Osl_Target target;

    Arena token_arena;
    Osl_Token *tokens;
    u64 token_count;
    
    Arena node_arena;
    u64 total_node_count;
    
    Arena struct_decls_arena;
    Osl_Struct_Decl **struct_decls;
    u64 struct_node_count;
    
    Osl_Block top_block;
    
    Osl_Result result;
    string err_log;
    
    s64 next_vnum;
    
} Osl_Compiler;

unit_local void spv_block_init(Spv_Block *block, u64 initial_capacity) {
	block->arena = make_arena(1024*1024*1024*69, initial_capacity);
    block->data = (u8*)block->arena.start;
    block->count = 0;
    block->current_op_byte_index = -1;
}

unit_local void spv_push_bytes(Spv_Block *block, void *bytes, u64 count) {
    void *backing = arena_push(&block->arena, count);
    memcpy(backing, bytes, (sys_uint)count);
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
    spv->type_f32v3.size = 16;
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
    spv->type_u32.size = 4;
    spv->type_u32.name = STR("u32");
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
    spv->type_u32v3.size = 16;
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
    spv->type_s32v3.size = 16;
    spv->type_s32v3.val.comp_type.component_count = 3;
    spv->type_s32v3.val.comp_type.underlying = &spv->type_s32;
    spv->type_s32v3.type_id = spv_push_decl_vector(spv, &spv->const_block, spv->type_s32.type_id, 3);
    
    spv->type_s32v4.kind = OSL_TYPE_COMPOSITE;
    spv->type_s32v4.name = STR("s32v4");
    spv->type_s32v4.size = 16;
    spv->type_s32v4.val.comp_type.component_count = 4;
    spv->type_s32v4.val.comp_type.underlying = &spv->type_s32;
    spv->type_s32v4.type_id = spv_push_decl_vector(spv, &spv->const_block, spv->type_s32.type_id, 4);
    
    spv->type_image2df.kind = OSL_TYPE_IMAGE2DF;
    spv->type_image2df.name = STR("Image2Df");
    spv_begin_op(&spv->const_block, OpTypeImage);
    spv->type_image2df.type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_push_word(&spv->const_block, spv->type_f32.type_id);
    spv_push_word(&spv->const_block, 1);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 1); // Sampled
    spv_push_word(&spv->const_block, 0);
    spv_end_op(&spv->const_block);
    spv_begin_op(&spv->const_block, OpTypeSampledImage);
    spv->type_image2df.val.image_type.sampled_type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_push_word(&spv->const_block, spv->type_image2df.type_id);
    spv_end_op(&spv->const_block);
    
    spv->type_fbuffer2d_rgba32f.kind = OSL_TYPE_FBUFFER2D;
    spv->type_fbuffer2d_rgba32f.val.fbuffer2d_type.view_type = OSL_VIEW_RGBA32F;
    spv->type_fbuffer2d_rgba32f.name = STR("FBuffer2D(RGBA32F)");
    spv_begin_op(&spv->const_block, OpTypeImage);
    spv->type_fbuffer2d_rgba32f.type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_push_word(&spv->const_block, spv->type_f32.type_id);
    spv_push_word(&spv->const_block, 1);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 2); // Not sampled
    spv_push_word(&spv->const_block, 1); // Rgba32f
    spv_end_op(&spv->const_block);
    
    spv->type_fbuffer2d_rgba16f.kind = OSL_TYPE_FBUFFER2D;
    spv->type_fbuffer2d_rgba16f.val.fbuffer2d_type.view_type = OSL_VIEW_RGBA16F;
    spv->type_fbuffer2d_rgba16f.name = STR("FBuffer2D(RGBA16F)");
    spv_begin_op(&spv->const_block, OpTypeImage);
    spv->type_fbuffer2d_rgba16f.type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_push_word(&spv->const_block, spv->type_f32.type_id);
    spv_push_word(&spv->const_block, 1);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 2); // Not sampled
    spv_push_word(&spv->const_block, 2); // Rgba16f
    spv_end_op(&spv->const_block);
    
    spv->type_fbuffer2d_r32f.kind = OSL_TYPE_FBUFFER2D;
    spv->type_fbuffer2d_r32f.val.fbuffer2d_type.view_type = OSL_VIEW_R32F;
    spv->type_fbuffer2d_r32f.name = STR("FBuffer2D(R32F)");
    spv_begin_op(&spv->const_block, OpTypeImage);
    spv->type_fbuffer2d_r32f.type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_push_word(&spv->const_block, spv->type_f32.type_id);
    spv_push_word(&spv->const_block, 1);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 2); // Not sampled
    spv_push_word(&spv->const_block, 3); // R32f
    spv_end_op(&spv->const_block);
    
    spv->type_fbuffer2d_rgba8_unorm.kind = OSL_TYPE_FBUFFER2D;
    spv->type_fbuffer2d_rgba8_unorm.val.fbuffer2d_type.view_type = OSL_VIEW_RGBA8_UNORM;
    spv->type_fbuffer2d_rgba8_unorm.name = STR("FBuffer2D(RGBA8_UNORM)");
    spv_begin_op(&spv->const_block, OpTypeImage);
    spv->type_fbuffer2d_rgba8_unorm.type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_push_word(&spv->const_block, spv->type_f32.type_id);
    spv_push_word(&spv->const_block, 1);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 2); // Not sampled
    spv_push_word(&spv->const_block, 4); // Rgba8
    spv_end_op(&spv->const_block);
    
    spv->type_fbuffer2d_rgba8_snorm.kind = OSL_TYPE_FBUFFER2D;
    spv->type_fbuffer2d_rgba8_snorm.val.fbuffer2d_type.view_type = OSL_VIEW_RGBA8_SNORM;
    spv->type_fbuffer2d_rgba8_snorm.name = STR("FBuffer2D(RGBA8_SNORM)");
    spv_begin_op(&spv->const_block, OpTypeImage);
    spv->type_fbuffer2d_rgba8_snorm.type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_push_word(&spv->const_block, spv->type_f32.type_id);
    spv_push_word(&spv->const_block, 1);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 2); // Not sampled
    spv_push_word(&spv->const_block, 5); // Rgba8Snorm
    spv_end_op(&spv->const_block);
    
    spv->type_fbuffer2d_rgba32u.kind = OSL_TYPE_FBUFFER2D;
    spv->type_fbuffer2d_rgba32u.val.fbuffer2d_type.view_type = OSL_VIEW_RGBA32U;
    spv->type_fbuffer2d_rgba32u.name = STR("FBuffer2D(RGBA32U)");
    spv_begin_op(&spv->const_block, OpTypeImage);
    spv->type_fbuffer2d_rgba32u.type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_push_word(&spv->const_block, spv->type_u32.type_id);
    spv_push_word(&spv->const_block, 1);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 2); // Not sampled
    spv_push_word(&spv->const_block, 30); // Rgba32ui
    spv_end_op(&spv->const_block);
    
    spv->type_fbuffer2d_rgba16u.kind = OSL_TYPE_FBUFFER2D;
    spv->type_fbuffer2d_rgba16u.val.fbuffer2d_type.view_type = OSL_VIEW_RGBA16U;
    spv->type_fbuffer2d_rgba16u.name = STR("FBuffer2D(RGBA16U)");
    spv_begin_op(&spv->const_block, OpTypeImage);
    spv->type_fbuffer2d_rgba16u.type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_push_word(&spv->const_block, spv->type_u32.type_id);
    spv_push_word(&spv->const_block, 1);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 2); // Not sampled
    spv_push_word(&spv->const_block, 31); // Rgba16ui
    spv_end_op(&spv->const_block);
    
    spv->type_fbuffer2d_rgba8u.kind = OSL_TYPE_FBUFFER2D;
    spv->type_fbuffer2d_rgba8u.val.fbuffer2d_type.view_type = OSL_VIEW_RGBA8U;
    spv->type_fbuffer2d_rgba8u.name = STR("FBuffer2D(RGBA8U)");
    spv_begin_op(&spv->const_block, OpTypeImage);
    spv->type_fbuffer2d_rgba8u.type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_push_word(&spv->const_block, spv->type_u32.type_id);
    spv_push_word(&spv->const_block, 1);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 2); // Not sampled
    spv_push_word(&spv->const_block, 32); // Rgba8ui
    spv_end_op(&spv->const_block);
    
    spv->type_fbuffer2d_r32u.kind = OSL_TYPE_FBUFFER2D;
    spv->type_fbuffer2d_r32u.val.fbuffer2d_type.view_type = OSL_VIEW_R32U;
    spv->type_fbuffer2d_r32u.name = STR("FBuffer2D(R32U)");
    spv_begin_op(&spv->const_block, OpTypeImage);
    spv->type_fbuffer2d_r32u.type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_push_word(&spv->const_block, spv->type_u32.type_id);
    spv_push_word(&spv->const_block, 1);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 2); // Not sampled
    spv_push_word(&spv->const_block, 33); // R32ui
    spv_end_op(&spv->const_block);
    
    spv->type_fbuffer2d_rgba32s.kind = OSL_TYPE_FBUFFER2D;
    spv->type_fbuffer2d_rgba32s.val.fbuffer2d_type.view_type = OSL_VIEW_RGBA32S;
    spv->type_fbuffer2d_rgba32s.name = STR("FBuffer2D(RGBA32S)");
    spv_begin_op(&spv->const_block, OpTypeImage);
    spv->type_fbuffer2d_rgba32s.type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_push_word(&spv->const_block, spv->type_s32.type_id);
    spv_push_word(&spv->const_block, 1);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 2); // Not sampled
    spv_push_word(&spv->const_block, 21); // Rgba32i
    spv_end_op(&spv->const_block);
    
    spv->type_fbuffer2d_rgba16s.kind = OSL_TYPE_FBUFFER2D;
    spv->type_fbuffer2d_rgba16s.val.fbuffer2d_type.view_type = OSL_VIEW_RGBA16S;
    spv->type_fbuffer2d_rgba16s.name = STR("FBuffer2D(RGBA16S)");
    spv_begin_op(&spv->const_block, OpTypeImage);
    spv->type_fbuffer2d_rgba16s.type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_push_word(&spv->const_block, spv->type_s32.type_id);
    spv_push_word(&spv->const_block, 1);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 2); // Not sampled
    spv_push_word(&spv->const_block, 22); // Rgba16i
    spv_end_op(&spv->const_block);
    
    spv->type_fbuffer2d_rgba8s.kind = OSL_TYPE_FBUFFER2D;
    spv->type_fbuffer2d_rgba8s.val.fbuffer2d_type.view_type = OSL_VIEW_RGBA8S;
    spv->type_fbuffer2d_rgba8s.name = STR("FBuffer2D(RGBA8S)");
    spv_begin_op(&spv->const_block, OpTypeImage);
    spv->type_fbuffer2d_rgba8s.type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_push_word(&spv->const_block, spv->type_s32.type_id);
    spv_push_word(&spv->const_block, 1);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 2); // Not sampled
    spv_push_word(&spv->const_block, 23); // Rgba8i
    spv_end_op(&spv->const_block);
    
    spv->type_fbuffer2d_r32s.kind = OSL_TYPE_FBUFFER2D;
    spv->type_fbuffer2d_r32s.val.fbuffer2d_type.view_type = OSL_VIEW_R32S;
    spv->type_fbuffer2d_r32s.name = STR("FBuffer2D(R32S)");
    spv_begin_op(&spv->const_block, OpTypeImage);
    spv->type_fbuffer2d_r32s.type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_push_word(&spv->const_block, spv->type_s32.type_id);
    spv_push_word(&spv->const_block, 1);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 0);
    spv_push_word(&spv->const_block, 2); // Not sampled
    spv_push_word(&spv->const_block, 24); // R32ui
    spv_end_op(&spv->const_block);
    
    
    spv->type_sample_mode.kind = OSL_TYPE_SAMPLE_MODE;
    spv->type_sample_mode.name = STR("SampleMode");
    spv_begin_op(&spv->const_block, OpTypeSampler);
    spv->type_sample_mode.type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_end_op(&spv->const_block);
    
    // This is a spirv thing. I actually want to avoid bool types in OSL
    spv->type_bool.kind = OSL_TYPE_BOOL;
    spv->type_bool.name = STR("________bool");
    spv->type_bool.size = 1;
    spv_begin_op(&spv->const_block, OpTypeBool);
    spv->type_bool.type_id = spv_push_result_arg(spv, &spv->const_block);
    spv_end_op(&spv->const_block);
    
    spv->type_boolv2.kind = OSL_TYPE_COMPOSITE;
    spv->type_boolv2.name = STR("_boolv2");
    spv->type_boolv2.size = 2;
    spv->type_boolv2.val.comp_type.component_count = 2;
    spv->type_boolv2.val.comp_type.underlying = &spv->type_bool;
    spv->type_boolv2.type_id = spv_push_decl_vector(spv, &spv->const_block, spv->type_bool.type_id, 2);
    
    spv->type_boolv3.kind = OSL_TYPE_COMPOSITE;
    spv->type_boolv3.name = STR("_boolv3");
    spv->type_boolv3.size = 4;
    spv->type_boolv3.val.comp_type.component_count = 3;
    spv->type_boolv3.val.comp_type.underlying = &spv->type_bool;
    spv->type_boolv3.type_id = spv_push_decl_vector(spv, &spv->const_block, spv->type_bool.type_id, 3);
    
    spv->type_boolv4.kind = OSL_TYPE_COMPOSITE;
    spv->type_boolv4.name = STR("_boolv4");
    spv->type_boolv4.size = 4;
    spv->type_boolv4.val.comp_type.component_count = 4;
    spv->type_boolv4.val.comp_type.underlying = &spv->type_bool;
    spv->type_boolv4.type_id = spv_push_decl_vector(spv, &spv->const_block, spv->type_bool.type_id, 4);
}

unit_local u32 spv_push_decl_pointer_type(Spv_Converter *spv, Spv_Block *block, u32 type, Spv_Storage_Class storage_class) {
    spv_begin_op(block, OpTypePointer);
    u32 id = spv_push_result_arg(spv, block);
    spv_push_word(block, (u32)storage_class);
    spv_push_word(block, type);
    spv_end_op(block);
    return id;
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
unit_local void spv_push_member_decoration(Spv_Block *block, u32 struct_type, u32 member_index, Spv_Decoration deco, u32 *args, u64 arg_count) {
    spv_begin_op(block, OpMemberDecorate);
    spv_push_word(block, struct_type);
    spv_push_word(block, member_index);
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


unit_local string _osl_token_text(Osl_Compiler *compiler, Osl_Token *token);
unit_local string _osl_tprint_token(Osl_Compiler *compiler, Osl_Token *token, string message);

unit_local Osl_Type_Info *arrayify_type(Spv_Converter *spv, Osl_Type_Info *elem, u64 array_count) {
	for (s64 i = (s64)spv->array_type_count-1; i >= 0; i -= 1) {
		Osl_Type_Info *type = &spv->array_types[i];
		if (type->val.array_type.elem_type == elem && type->val.array_type.array_count == array_count)
			return type;
	}
	
	
	Osl_Type_Info *type = (Osl_Type_Info*)arena_push(&spv->array_type_arena, sizeof(Osl_Type_Info));
	spv->array_type_count += 1;
	type->kind = OSL_TYPE_ARRAY;
	type->name = tprint("[%i]%s", array_count, elem->name);
	type->size = elem->size*array_count;
	type->val.array_type.array_count = array_count;
	type->val.array_type.elem_type = elem;
	
	if (array_count > 0) {
		u32 id_array_count = spv_push_decl_constant_u32(spv, &spv->const_block, spv->type_u32.type_id, (u32)array_count);
		type->type_id = spv_push_decl_array_type(spv, &spv->const_block, elem->type_id, id_array_count);
	} else {
		spv_push_op_code(&spv->const_block, 3, OpTypeRuntimeArray);
	    type->type_id = spv_push_result_arg(spv, &spv->const_block);
	    spv_push_word(&spv->const_block, elem->type_id);
	}
	
	spv_push_decoration(&spv->annotations_block, type->type_id, SpvDecoration_ArrayStride, (u32*)&type->val.array_type.elem_type->size, 1);
	
	return type;
}

unit_local Osl_Type_Info *_osl_resolve_type(Spv_Converter *spv, Osl_Type_Ident type_ident) {

	Osl_Type_Info *type = 0;
	if (strings_match(type_ident.name, STR("f32")) || strings_match(type_ident.name, STR("float"))) {
		type = &spv->type_f32;
	} else if (strings_match(type_ident.name, STR("f32v2")) || strings_match(type_ident.name, STR("float2"))) {
		type = &spv->type_f32v2;
	} else if (strings_match(type_ident.name, STR("f32v3")) || strings_match(type_ident.name, STR("float3"))) {
		type = &spv->type_f32v3;
	} else if (strings_match(type_ident.name, STR("f32v4")) || strings_match(type_ident.name, STR("float4"))) {
		type = &spv->type_f32v4;
	} else if (strings_match(type_ident.name, STR("u32")) || strings_match(type_ident.name, STR("uint"))) {
		type = &spv->type_u32;
	} else if (strings_match(type_ident.name, STR("u32v2")) || strings_match(type_ident.name, STR("uint2"))) {
		type = &spv->type_u32v2;
	} else if (strings_match(type_ident.name, STR("u32v3")) || strings_match(type_ident.name, STR("uint3"))) {
		type = &spv->type_u32v3;
	} else if (strings_match(type_ident.name, STR("u32v4")) || strings_match(type_ident.name, STR("uint4"))) {
		type = &spv->type_u32v4;
	} else if (strings_match(type_ident.name, STR("s32")) || strings_match(type_ident.name, STR("sint"))) {
		type = &spv->type_s32;
	} else if (strings_match(type_ident.name, STR("s32v2")) || strings_match(type_ident.name, STR("sint2"))) {
		type = &spv->type_s32v2;
	} else if (strings_match(type_ident.name, STR("s32v3")) || strings_match(type_ident.name, STR("sint3"))) {
		type = &spv->type_s32v3;
	} else if (strings_match(type_ident.name, STR("s32v4")) || strings_match(type_ident.name, STR("sint4"))) {
		type = &spv->type_s32v4;
	} else if (strings_match(type_ident.name, STR("Image2Df")) || strings_match(type_ident.name, STR("Image2D"))) {
		type = &spv->type_image2df;
	} else if (strings_match(type_ident.name, STR("FBuffer2D"))) {
		switch (type_ident.view_type) {
			case OSL_VIEW_RGBA32F:
				type = &spv->type_fbuffer2d_rgba32f; break;
			case OSL_VIEW_RGBA16F:
				type = &spv->type_fbuffer2d_rgba16f; break;
			case OSL_VIEW_R32F:
				type = &spv->type_fbuffer2d_r32f; break;
			case OSL_VIEW_RGBA8_UNORM:
				type = &spv->type_fbuffer2d_rgba8_unorm; break;
			case OSL_VIEW_RGBA8_SNORM:
				type = &spv->type_fbuffer2d_rgba8_snorm; break;
			case OSL_VIEW_RGBA32U:
				type = &spv->type_fbuffer2d_rgba32u; break;
			case OSL_VIEW_RGBA16U:
				type = &spv->type_fbuffer2d_rgba16u; break;
			case OSL_VIEW_RGBA8U:
				type = &spv->type_fbuffer2d_rgba8u; break;
			case OSL_VIEW_R32U:
				type = &spv->type_fbuffer2d_r32u; break;
			case OSL_VIEW_RGBA32S:
				type = &spv->type_fbuffer2d_rgba32s; break;
			case OSL_VIEW_RGBA16S:
				type = &spv->type_fbuffer2d_rgba16s; break;
			case OSL_VIEW_RGBA8S:
				type = &spv->type_fbuffer2d_rgba8s; break;
			case OSL_VIEW_R32S:
				type = &spv->type_fbuffer2d_r32s; break;
			case OSL_VIEW_DEFAULT: // fallthrough
			case OSL_VIEW_BLOCK: // fallthrough
			default:
				assert(false);
				break;
		}
	} else if (strings_match(type_ident.name, STR("SampleMode"))) {
		type = &spv->type_sample_mode;
	} else {
		for (u64 i = 0; i < spv->struct_type_count; i += 1) {
			Osl_Type_Info *stype = &spv->struct_types[i];
			assert(stype->kind == OSL_TYPE_STRUCT);
			if (strings_match(stype->name, type_ident.name)) {
				type = stype;
				break;
			}
		}
	}
	
	if (type) for (u32 i = 0; i < type_ident.indirection_count; i += 1) {
		Osl_Type_Indirection ind = type_ident.indirections[i];
		type = arrayify_type(spv, type, ind.array_count);
	}
	
	return type;
}

unit_local void _osl_done_spv(Spv_Converter *spv) {
	free_arena(spv->settings_block.arena);
	free_arena(spv->header_block.arena);
	free_arena(spv->const_block.arena);
	free_arena(spv->entry_block.arena);
	free_arena(spv->annotations_block.arena);
	free_arena(spv->debug_block.arena);
	free_arena(spv->array_type_arena);
	free_arena(spv->struct_type_arena);
}
unit_local Osl_Result spv_init(Spv_Converter *spv, Osl_Compiler *compiler, u32 vnum_count) {
	memset(spv, 0, sizeof(*spv));
	spv->compiler = compiler;
	spv_block_init(&spv->settings_block, 1024*10);
	spv_block_init(&spv->header_block, 1024*10);
	spv_block_init(&spv->const_block, 1024*10);
	spv_block_init(&spv->entry_block, 1024*10);
	spv_block_init(&spv->annotations_block, 1024*10);
	spv_block_init(&spv->debug_block, 1024*10);
	
	spv->array_type_arena = make_arena(1024*1024*1024*69, 1024*10);
	spv->array_types = (Osl_Type_Info*)spv->array_type_arena.start;
	
	spv->struct_type_arena = make_arena(1024*1024*1024*69, 1024*10);
	spv->struct_types = (Osl_Type_Info*)spv->struct_type_arena.start;
	
	spv->next_id = vnum_count;
	spv->ext_glsl450_id = spv->next_id++;
	spv->entry_id = spv->next_id++;
	
	spv_push_base_decls(spv);
	
	spv_begin_op(&spv->entry_block, OpLabel);
    spv_push_word(&spv->entry_block, spv->next_id++);
    spv_end_op(&spv->entry_block);
    
    for (u64 i = 0; i < compiler->struct_node_count; i += 1) {
    	Osl_Struct_Decl *decl = compiler->struct_decls[i];
    	
    	Osl_Type_Info *type = (Osl_Type_Info*)arena_push(&spv->struct_type_arena, sizeof(Osl_Type_Info));
    	*type = (Osl_Type_Info){0};
    	type->kind = OSL_TYPE_STRUCT;
    	type->name = decl->ident;
    	spv->struct_type_count += 1;
    	Osl_Type_Info_Struct *struct_type =  &type->val.struct_type;
    	
		struct_type->member_count = decl->block->top_node_count;
    	
    	if (struct_type->member_count > 128) {
    		compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(decl)->first_token, STR("Because this compiler is a prototype, the max count of struct members is limited to 128."));
    		return compiler->result = OSL_UNIMPLEMENTED;
    	}
    		
    	// First pass: make struct types exist
    	for (u64 j = 0; j < decl->block->top_node_count; j += 1) {
    		Osl_Node *node = decl->block->top_nodes[j];
    		assertmsg(node->kind == OSL_NODE_VALUE_DECL, "Struct node is non-value decl");
    		
    		Osl_Value_Decl *vdecl = &node->val.value_decl;
    		
    		struct_type->member_names[j] = vdecl->ident;
    	}
    	
    	// Second pass: resolve member types (they may be types of other structs declared later)
    	u64 offset = 0;
    	for (u64 j = 0; j < struct_type->member_count; j += 1) {
    		Osl_Node *node = decl->block->top_nodes[j];
    		
    		Osl_Value_Decl *vdecl = &node->val.value_decl;
    		
    		
    		struct_type->member_types[j] = _osl_resolve_type(spv, vdecl->type_ident);
    		Osl_Type_Info *member_type = struct_type->member_types[j];
    		if (!member_type) {
    			string a = _osl_tprint_token(compiler, vdecl->type_ident.token, STR("Undefined type used in member declaration"));
    			string b = _osl_tprint_token(compiler, _osl_get_node(decl)->first_token, STR("... Member of this struct"));
    			compiler->err_log = tprint("%s%s", a, b);
    			return compiler->result = OSL_UNRESOLVED_TYPE;
    		}
    		
    		if (member_type->kind == OSL_TYPE_ARRAY && member_type->val.array_type.array_count == 0) {
    			if (j != struct_type->member_count-1) {
    				compiler->err_log = _osl_tprint_token(compiler, vdecl->type_ident.token, STR("Unsized arrays must only appear as the last member of a struct. This does not."));
    				return compiler->result = OSL_UNSIZED_ARRAY_NOT_AT_END_OF_STRUCT;
    			}
    		} else {
    			assertmsgs(member_type->size, _osl_tprint_token(compiler, _osl_get_node(vdecl)->first_token, STR("This member type size is zero. This shouldn't be possible.")));
    		}
    		
    		
    		struct_type->member_offsets[j] = offset;
    		// todo(charlie) #memory #speed alignment, padding, std140
    		offset += member_type->size;
    	}
    	
    	
    	spv_begin_op(&spv->const_block, OpTypeStruct);
    	type->type_id = spv_push_result_arg(spv, &spv->const_block);
    	for (u64 j = 0; j < struct_type->member_count; j += 1) {
    		spv_push_word(&spv->const_block, struct_type->member_types[j]->type_id);
    	}
    	spv_end_op(&spv->const_block);
    	spv_push_decoration(&spv->annotations_block, type->type_id, SpvDecoration_Block, 0, 0);
    	
	    for (u64 j = 0; j < struct_type->member_count; j += 1) {
	    	spv_push_member_decoration(&spv->annotations_block, type->type_id, (u32)j, SpvDecoration_Offset, (u32*)&struct_type->member_offsets[j], 1);
	    	
	    	spv_begin_op(&spv->debug_block, OpMemberName);
			spv_push_word(&spv->debug_block, type->type_id);
			spv_push_word(&spv->debug_block, (u32)j);
			spv_push_string_arg(&spv->debug_block, struct_type->member_names[j]);
			spv_end_op(&spv->debug_block);
	    }
    }
    
    
    return OSL_OK;
}

unit_local Spv_Block *spv_finalize(Spv_Converter *spv) {

	spv_push_op_code(&spv->entry_block, 1, (u16)OpReturn);

	spv_push_header(&spv->header_block, spv->next_id);
	
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
	
	for (u64 i = 0; i < spv->compiler->top_block.top_node_count; i += 1) {
		Osl_Node *n = spv->compiler->top_block.top_nodes[i];
		
		if (n->kind == OSL_NODE_VALUE_DECL && (n->val.value_decl.storage_class == OSL_STORAGE_INPUT || n->val.value_decl.storage_class == OSL_STORAGE_OUTPUT)) {
			assert(n->val.value_decl.vnum >= 0);
			interface[interface_count++] = (u32)n->val.value_decl.vnum;
		}
	}
	
	Spv_Capability caps[512];
	u64 cap_count = 0;
	
	string exts[512];
	u64 ext_count = 0;
	
	caps[cap_count++] = SpvCapability_Shader;
	
	if (spv->compiler->enabled_features & OSL_FEATURE_INVOCATION_PIXEL_INTERLOCK) {
		caps[cap_count++] = SpvCapability_FragmentShaderPixelInterlockEXT;
		exts[ext_count++] = STR("SPV_EXT_fragment_shader_interlock");
	}


	for (u64 i = 0; i < cap_count; i++) {
        spv_begin_op(&spv->settings_block, OpCapability);
        spv_push_word(&spv->settings_block, (u32)caps[i]);
        spv_end_op(&spv->settings_block);
    }
    for (u64 i = 0; i < ext_count; i++) {
	    spv_begin_op(&spv->settings_block, OpExtension);
	    spv_push_string_arg(&spv->settings_block, exts[i]);
	    spv_end_op(&spv->settings_block);
    }
	if (spv->compiler->target == OSL_TARGET_SPIRV_VULKAN) {
		spv_begin_op(&spv->settings_block, OpExtInstImport);
		spv_push_word(&spv->settings_block, spv->ext_glsl450_id);
		spv_push_string_arg(&spv->settings_block, STR("GLSL.std.450"));
		spv_end_op(&spv->settings_block);
	}
    spv_begin_op(&spv->settings_block, OpMemoryModel);
    spv_push_word(&spv->settings_block, 0);
    spv_push_word(&spv->settings_block, 1);
    spv_end_op(&spv->settings_block);
    spv_begin_op(&spv->settings_block, OpEntryPoint);
    spv_push_word(&spv->settings_block, (u32)exec_model);
    spv_push_word(&spv->settings_block, spv->entry_id);
    spv_push_string_arg(&spv->settings_block, STR("main"));
    for (u64 i = 0; i < interface_count; i++) {
        spv_push_word(&spv->settings_block, interface[i]);
    }
    spv_end_op(&spv->settings_block);
    if (exec_model == SpvExecutionModel_Fragment) {
        spv_begin_op(&spv->settings_block, OpExecutionMode);
        spv_push_word(&spv->settings_block, spv->entry_id);
        spv_push_word(&spv->settings_block, 7); /* OriginUpperLeft */
        spv_end_op(&spv->settings_block);
        
        if (spv->compiler->enabled_features & OSL_FEATURE_INVOCATION_PIXEL_INTERLOCK) {
	        spv_begin_op(&spv->settings_block, OpExecutionMode);
	        spv_push_word(&spv->settings_block, spv->entry_id);
	        spv_push_word(&spv->settings_block, 5366); /* PixelInterlockOrderedEXT */
	        spv_end_op(&spv->settings_block);
        }
    }
	
	
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
		
		if (op->op_kind != OSL_OP_CAST && op->op_kind != OSL_OP_UNARY_NEGATE && op->op_kind != OSL_OP_UNARY_NAUGHT) {
			res = spv_emit_expr(spv, block, op->rhs, &op2, &op2_type, false);
			if (res != OSL_OK) return res;
			assert(op2); assert(op2_type);
			
			if ((op1_type->kind == OSL_TYPE_BOOL && op2_type->kind == OSL_TYPE_INT)) {
				u32 id_zero = spv_push_decl_constant_u32(spv, &spv->const_block, spv->type_u32.type_id, 0);
					
				spv_begin_op(block, OpINotEqual);
				spv_push_word(block, spv->type_bool.type_id);
			    u32 new_op2 = spv_push_result_arg(spv, block);
			    spv_push_word(block, op2);
			    spv_push_word(block, id_zero);
				spv_end_op(block);
				
				op2 = new_op2;
				op2_type = &spv->type_bool;			
			} else if ((op2_type->kind == OSL_TYPE_BOOL && op1_type->kind == OSL_TYPE_INT)) {
				u32 id_zero = spv_push_decl_constant_u32(spv, &spv->const_block, spv->type_u32.type_id, 0);
					
				spv_begin_op(block, OpINotEqual);
				spv_push_word(block, spv->type_bool.type_id);
			    u32 new_op1 = spv_push_result_arg(spv, block);
			    spv_push_word(block, op1);
			    spv_push_word(block, id_zero);
				spv_end_op(block);
				
				op1 = new_op1;
				op1_type = &spv->type_bool;
			}
			
			is_vector_v_scalar = op1_type->kind == OSL_TYPE_COMPOSITE && op1_type->val.comp_type.underlying == op2_type;
			is_scalar_v_vector = op2_type->kind == OSL_TYPE_COMPOSITE && op2_type->val.comp_type.underlying == op1_type;
			
			if (op1_type != op2_type && !((op->op_kind == OSL_OP_MUL || op->op_kind == OSL_OP_DIV) && (is_vector_v_scalar || is_scalar_v_vector))) {
				string a = _osl_tprint_token(spv->compiler, op->op_token, STR("Cannot perform this operations on these types ..."));
				string b = _osl_tprint_token(spv->compiler, _osl_get_node(op->lhs)->first_token, tprint("... Left hand side is of type '%s' ... ", op1_type->name));
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
		case OSL_OP_UNARY_NAUGHT: {
		
			assert(!op->rhs);
			if (op1_type->kind == OSL_TYPE_FLOAT || (op1_type->kind == OSL_TYPE_COMPOSITE && op1_type->val.comp_type.underlying->kind == OSL_TYPE_FLOAT)) 
				spv_begin_op(block, OpFOrdEqual);
			else if (op1_type->kind == OSL_TYPE_INT || (op1_type->kind == OSL_TYPE_COMPOSITE && op1_type->val.comp_type.underlying->kind == OSL_TYPE_INT)) 
				spv_begin_op(block, OpIEqual); // todo(charlie) err if int is unsigned
			else assert(false);
			
			u32 zero_id = spv_push_decl_constant_u32(spv, &spv->const_block, spv->type_u32.type_id, 0);
			
			spv_push_word(block, spv->type_bool.type_id);
		    *result_id = spv_push_result_arg(spv, block);
		    spv_push_word(block, op1);
		    spv_push_word(block, zero_id);
		    spv_end_op(block);
		    
		    *type = &spv->type_bool;
			
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
		
		
			if (op1_type == op2_type) {
				
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
						spv_op = OpFDiv;
					else if (scalar_type->kind == OSL_TYPE_INT && scalar_type->val.int_type.is_signed)
						spv_op = OpSDiv;
					else if (scalar_type->kind == OSL_TYPE_INT && !scalar_type->val.int_type.is_signed)
						spv_op = OpUDiv;
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
		case OSL_OP_GT: {
		
			Osl_Type_Info *target_type1 = op1_type;
			if (op1_type->kind == OSL_TYPE_COMPOSITE)
				target_type1 = op1_type->val.comp_type.underlying;
			
			if (target_type1->kind == OSL_TYPE_FLOAT) {
				spv_begin_op(block, OpFOrdGreaterThan);
			} else if (target_type1->kind == OSL_TYPE_INT && !target_type1->val.int_type.is_signed) {
				spv_begin_op(block, OpUGreaterThan);
			} else if (target_type1->kind == OSL_TYPE_INT && target_type1->val.int_type.is_signed) {
				spv_begin_op(block, OpSGreaterThan);
			}
			
			spv_push_word(block, spv->type_bool.type_id);
		    *result_id = spv_push_result_arg(spv, block);
		    spv_push_word(block, op1);
		    spv_push_word(block, op2);
		    spv_end_op(block);
		    
		    *type = &spv->type_bool;
		
			break;
		}
		case OSL_OP_LT: {
		
			Osl_Type_Info *target_type1 = op1_type;
			if (op1_type->kind == OSL_TYPE_COMPOSITE)
				target_type1 = op1_type->val.comp_type.underlying;
			
			if (target_type1->kind == OSL_TYPE_FLOAT) {
				spv_begin_op(block, OpFOrdLessThan);
			} else if (target_type1->kind == OSL_TYPE_INT && !target_type1->val.int_type.is_signed) {
				spv_begin_op(block, OpULessThan);
			} else if (target_type1->kind == OSL_TYPE_INT && target_type1->val.int_type.is_signed) {
				spv_begin_op(block, OpSLessThan);
			}
			
			spv_push_word(block, spv->type_bool.type_id);
		    *result_id = spv_push_result_arg(spv, block);
		    spv_push_word(block, op1);
		    spv_push_word(block, op2);
		    spv_end_op(block);
		    
		    *type = &spv->type_bool;
		
			break;
		}
		case OSL_OP_GTE: {
		
			Osl_Type_Info *target_type1 = op1_type;
			if (op1_type->kind == OSL_TYPE_COMPOSITE)
				target_type1 = op1_type->val.comp_type.underlying;
			
			if (target_type1->kind == OSL_TYPE_FLOAT) {
				spv_begin_op(block, OpFOrdGreaterThanEqual);
			} else if (target_type1->kind == OSL_TYPE_INT && !target_type1->val.int_type.is_signed) {
				spv_begin_op(block, OpUGreaterThanEqual);
			} else if (target_type1->kind == OSL_TYPE_INT && target_type1->val.int_type.is_signed) {
				spv_begin_op(block, OpSGreaterThanEqual);
			}
			
			spv_push_word(block, spv->type_bool.type_id);
		    *result_id = spv_push_result_arg(spv, block);
		    spv_push_word(block, op1);
		    spv_push_word(block, op2);
		    spv_end_op(block);
		    
		    *type = &spv->type_bool;
		
			break;
		}
		case OSL_OP_LTE: {
		
			Osl_Type_Info *target_type1 = op1_type;
			if (op1_type->kind == OSL_TYPE_COMPOSITE)
				target_type1 = op1_type->val.comp_type.underlying;
			
			if (target_type1->kind == OSL_TYPE_FLOAT) {
				spv_begin_op(block, OpFOrdLessThanEqual);
			} else if (target_type1->kind == OSL_TYPE_INT && !target_type1->val.int_type.is_signed) {
				spv_begin_op(block, OpULessThanEqual);
			} else if (target_type1->kind == OSL_TYPE_INT && target_type1->val.int_type.is_signed) {
				spv_begin_op(block, OpSLessThanEqual);
			}
			
			spv_push_word(block, spv->type_bool.type_id);
		    *result_id = spv_push_result_arg(spv, block);
		    spv_push_word(block, op1);
		    spv_push_word(block, op2);
		    spv_end_op(block);
		    
		    *type = &spv->type_bool;
		
			break;
		}
		case OSL_OP_EQ: {
		
			Osl_Type_Info *target_type1 = op1_type;
			if (op1_type->kind == OSL_TYPE_COMPOSITE)
				target_type1 = op1_type->val.comp_type.underlying;
			
			if (target_type1->kind == OSL_TYPE_FLOAT) {
				spv_begin_op(block, OpFOrdEqual);
			} else if (target_type1->kind == OSL_TYPE_INT) {
				spv_begin_op(block, OpIEqual);
			}
			
			spv_push_word(block, spv->type_bool.type_id);
		    *result_id = spv_push_result_arg(spv, block);
		    spv_push_word(block, op1);
		    spv_push_word(block, op2);
		    spv_end_op(block);
		    
		    *type = &spv->type_bool;
		
			break;
		}
		case OSL_OP_NEQ: {
		
			Osl_Type_Info *target_type1 = op1_type;
			if (op1_type->kind == OSL_TYPE_COMPOSITE)
				target_type1 = op1_type->val.comp_type.underlying;
			
			if (target_type1->kind == OSL_TYPE_FLOAT) {
				spv_begin_op(block, OpFOrdNotEqual);
			} else if (target_type1->kind == OSL_TYPE_INT) {
				spv_begin_op(block, OpINotEqual);
			}
			
			spv_push_word(block, spv->type_bool.type_id);
		    *result_id = spv_push_result_arg(spv, block);
		    spv_push_word(block, op1);
		    spv_push_word(block, op2);
		    spv_end_op(block);
		    
		    *type = &spv->type_bool;
		
			break;
		}
		case OSL_OP_LAND: {
		
			if (op1_type->kind == OSL_TYPE_INT) {
				u32 id_zero = spv_push_decl_constant_u32(spv, &spv->const_block, spv->type_u32.type_id, 0);
				
				spv_begin_op(block, OpINotEqual);
				spv_push_word(block, spv->type_bool.type_id);
			    u32 new_op1 = spv_push_result_arg(spv, block);
			    spv_push_word(block, op1);
			    spv_push_word(block, id_zero);
				spv_end_op(block);
				
				op1 = new_op1;
				op1_type = &spv->type_bool;
				
				spv_begin_op(block, OpINotEqual);
				spv_push_word(block, spv->type_bool.type_id);
			    u32 new_op2 = spv_push_result_arg(spv, block);
			    spv_push_word(block, op2);
			    spv_push_word(block, id_zero);
				spv_end_op(block);
				
				op2 = new_op2;
				op2_type = &spv->type_bool;	
			}
		
			if (op1_type->kind != OSL_TYPE_BOOL) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(op->lhs)->first_token, tprint("&& operation expects both operands to be logical values. This ('%s') is not a logical value.", op1_type->name));
				return spv->compiler->result = OSL_NOT_A_LOGICAL_TYPE;
			}
			
			spv_begin_op(block, OpLogicalAnd);
			
			spv_push_word(block, spv->type_bool.type_id);
		    *result_id = spv_push_result_arg(spv, block);
		    spv_push_word(block, op1);
		    spv_push_word(block, op2);
		    spv_end_op(block);
		    
		    *type = &spv->type_bool;
		
			break;
		}
		case OSL_OP_LOR: {
			
			if (op1_type->kind == OSL_TYPE_INT) {
				u32 id_zero = spv_push_decl_constant_u32(spv, &spv->const_block, spv->type_u32.type_id, 0);
				
				spv_begin_op(block, OpINotEqual);
				spv_push_word(block, spv->type_bool.type_id);
			    u32 new_op1 = spv_push_result_arg(spv, block);
			    spv_push_word(block, op1);
			    spv_push_word(block, id_zero);
				spv_end_op(block);
				
				op1 = new_op1;
				op1_type = &spv->type_bool;
				
				spv_begin_op(block, OpINotEqual);
				spv_push_word(block, spv->type_bool.type_id);
			    u32 new_op2 = spv_push_result_arg(spv, block);
			    spv_push_word(block, op2);
			    spv_push_word(block, id_zero);
				spv_end_op(block);
				
				op2 = new_op2;
				op2_type = &spv->type_bool;	
			}
			
			if (op1_type->kind != OSL_TYPE_BOOL) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(op->lhs)->first_token, tprint("|| operation expects both operands to be logical values. This ('%s') is not a logical value.", op1_type->name));
				return spv->compiler->result = OSL_NOT_A_LOGICAL_TYPE;
			}
			
			spv_begin_op(block, OpLogicalOr);
			
			spv_push_word(block, spv->type_bool.type_id);
		    *result_id = spv_push_result_arg(spv, block);
		    spv_push_word(block, op1);
		    spv_push_word(block, op2);
		    spv_end_op(block);
		    
		    *type = &spv->type_bool;
		
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
		
		u32 base_id;
		Osl_Type_Info *base_type;
		Osl_Result res = spv_emit_expr(spv, block, access->base_expr, &base_id, &base_type, accessing_storage);
		if (res != OSL_OK) return res;
		assert(base_id); assert(base_type);
		
		Spv_Storage_Class base_storage_class = SpvStorageClass_Private;
		if (access->base_expr->kind == OSL_EXPR_DECL_IDENT) {
			switch (access->base_expr->val.decl->storage_class) {
			case OSL_STORAGE_DEFAULT: base_storage_class = SpvStorageClass_Private; break;
			case OSL_STORAGE_INPUT:   base_storage_class = SpvStorageClass_Input;   break;
			case OSL_STORAGE_OUTPUT:  base_storage_class = SpvStorageClass_Output;  break;
			case OSL_STORAGE_BINDING: 
				if (base_type->kind == OSL_TYPE_IMAGE2DF || base_type->kind == OSL_TYPE_FBUFFER2D || base_type->kind == OSL_TYPE_SAMPLE_MODE)
					base_storage_class = SpvStorageClass_UniformConstant;
				else
					base_storage_class = SpvStorageClass_Uniform;
				break;
			default:
				assert(false);
				break;
			}
		}
		
		
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
				
				Osl_Type_Info *arg_type;
				Osl_Result index_res = spv_emit_expr(spv, block, index_expr, &arg, &arg_type, false);
				if (index_res != OSL_OK) return index_res;
				assert(arg); assert(arg_type);
				
				if (arg_type->kind != OSL_TYPE_INT) {
					spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(index_expr)->first_token, tprint("Invalid subscript argument expression of type '%s', expected integer expression", arg_type->name));
					return spv->compiler->result = OSL_INVALID_SUBSCRIPT;
				}
				
				if (last_type->val.array_type.array_count && index_expr->kind == OSL_EXPR_LITERAL_INT && index_expr->val.lit.lit_int >= last_type->val.array_type.array_count) {
					spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(index_expr)->first_token, tprint("Subscript evaluated to %i is out of bands for array type %s", index_expr->val.lit.lit_int, last_type->name));
					return spv->compiler->result = OSL_INVALID_SUBSCRIPT;
				}
				
				args[arg_count++] = arg;
				
				last_type = last_type->val.array_type.elem_type;
				
			} else {
				string member_name = access->items[i].val.name;
				
				if (last_type->kind != OSL_TYPE_COMPOSITE && last_type->kind != OSL_TYPE_STRUCT) {
					spv->compiler->err_log = _osl_tprint_token(spv->compiler, access->items[i].token, tprint("Type '%s' has no members, but it is being accessed here as if it does.", last_type->name));
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
				} else if (last_type->kind == OSL_TYPE_STRUCT) {
					Osl_Type_Info_Struct *struct_type = &last_type->val.struct_type;
					s64 member_index = -1;
					for (u64 j = 0; j < struct_type->member_count; j += 1) {
						if (strings_match(member_name, struct_type->member_names[j])) {
							member_index = (s64)j;
							break;
						}
					}
					if (member_index == -1) {
						spv->compiler->err_log = _osl_tprint_token(spv->compiler, access->items[i].token, tprint("Nu such member '%s' in struct '%s'", member_name, last_type->name));
						return spv->compiler->result = OSL_NO_SUCH_MEMBER;
					}
					
					u32 arg = (u32)member_index;
					if (accessing_storage) {
						arg = spv_push_decl_constant_u32(spv, &spv->const_block, spv->type_u32.type_id, arg);
					}
					args[arg_count++] = arg;
					
					last_type = struct_type->member_types[member_index];
					
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
	case OSL_EXPR_ALIAS_IDENT: {
		Osl_Result res = spv_emit_expr(spv, block, expr->val.expr_alias->expr, result_id, type, in_memory);
		if (res) return res;
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
			//if (expr->val.decl->spv_loaded_id == 0) {
				*result_id = spv_push_op_load(spv, block, id_pointer, (*type)->type_id);
				expr->val.decl->spv_loaded_id = *result_id;
			//} else {
			//	*result_id = expr->val.decl->spv_loaded_id;
			//}
		}
		break;
	}
	case OSL_EXPR_CALL: {
		assert(!in_memory);
		Osl_Call *call = &expr->val.call;
		
		if (strings_match(call->ident, STR("sample"))) {
			
			if (call->arg_list.arg_count != 3) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(expr)->first_token, STR("Bad number of arguments. Intrinsic signature is 'xxx sample(image: ImageXDxxx, sample_mode: SampleMode, uv: f32v2)'"));
				return spv->compiler->result = OSL_BAD_CALL_ARGUMENTS;
			}
			
			u32 arg_ids[3];
			Osl_Type_Info *arg_types[3];
			
			Osl_Result res = spv_emit_expr(spv, block, call->arg_list.args[0], &arg_ids[0], &arg_types[0], false);
			if (res != OSL_OK) return res;
			res = spv_emit_expr(spv, block, call->arg_list.args[1], &arg_ids[1], &arg_types[1], false);
			if (res != OSL_OK) return res;
			res = spv_emit_expr(spv, block, call->arg_list.args[2], &arg_ids[2], &arg_types[2], false);
			if (res != OSL_OK) return res;
			
			if (arg_types[0] != &spv->type_image2df || arg_types[1] != &spv->type_sample_mode || arg_types[2] != &spv->type_f32v2) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(expr)->first_token, tprint("Bad argument types (%s, %s, %s). Intrinsic signature is 'xxx sample(image: ImageXDxxx, sample_mode: SampleMode, uv: f32v2)'", arg_types[0]->name, arg_types[1]->name, arg_types[2]->name));
				return spv->compiler->result = OSL_BAD_CALL_ARGUMENTS;
			}

			spv_begin_op(block, OpSampledImage);
			spv_push_word(block, arg_types[0]->val.image_type.sampled_type_id);
			u32 sampled_image_id = spv_push_result_arg(spv, block);
			spv_push_word(block, arg_ids[0]);
			spv_push_word(block, arg_ids[1]);
			spv_end_op(block);
			
			spv_begin_op(block, OpImageSampleImplicitLod);
			spv_push_word(block, spv->type_f32v4.type_id);
			*result_id = spv_push_result_arg(spv, block);
			spv_push_word(block, sampled_image_id);
			spv_push_word(block, arg_ids[2]);
			spv_end_op(block);
			
			*type = &spv->type_f32v4;
			
		} else if (strings_match(call->ident, STR("fbuffer_fetch"))) {
			
			if (call->arg_list.arg_count != 2) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(expr)->first_token, STR("Bad number of arguments. Intrinsic signature is 'fbuffer_fetch :: (src: FBufferX, coords: s32vX) -> x32v4'"));
				return spv->compiler->result = OSL_BAD_CALL_ARGUMENTS;
			}
			
			u32 arg_ids[2];
			Osl_Type_Info *arg_types[2];
			
			Osl_Result res = spv_emit_expr(spv, block, call->arg_list.args[0], &arg_ids[0], &arg_types[0], false);
			if (res != OSL_OK) return res;
			res = spv_emit_expr(spv, block, call->arg_list.args[1], &arg_ids[1], &arg_types[1], false);
			if (res != OSL_OK) return res;
			
			if (arg_types[0]->kind != OSL_TYPE_FBUFFER2D || arg_types[1] != &spv->type_s32v2) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(expr)->first_token, tprint("Bad argument types (%s, %s). Intrinsic signature is 'fbuffer_fetch :: (src: FBufferX, coords: s32vX) -> x32v4'", arg_types[0]->name, arg_types[1]->name));
				return spv->compiler->result = OSL_BAD_CALL_ARGUMENTS;
			}
			
			spv_push_op_code(block, 5, OpImageRead);
			spv_push_word(block, spv->type_f32v4.type_id);
			*result_id = spv_push_result_arg(spv, block);
			spv_push_word(block, arg_ids[0]);
			spv_push_word(block, arg_ids[1]);
			
			*type = &spv->type_f32v4;
			
		} else if (strings_match(call->ident, STR("fbuffer_store"))) {
			
			if (call->arg_list.arg_count != 3) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(expr)->first_token, STR("Bad number of arguments. Intrinsic signature is 'fbuffer_store :: (src: FBufferX, coords: s32vX, data: x32v4)'"));
				return spv->compiler->result = OSL_BAD_CALL_ARGUMENTS;
			}
			
			u32 arg_ids[3];
			Osl_Type_Info *arg_types[3];
			
			Osl_Result res = spv_emit_expr(spv, block, call->arg_list.args[0], &arg_ids[0], &arg_types[0], false);
			if (res != OSL_OK) return res;
			res = spv_emit_expr(spv, block, call->arg_list.args[1], &arg_ids[1], &arg_types[1], false);
			if (res != OSL_OK) return res;
			res = spv_emit_expr(spv, block, call->arg_list.args[2], &arg_ids[2], &arg_types[2], false);
			if (res != OSL_OK) return res;
			
			if (arg_types[0]->kind != OSL_TYPE_FBUFFER2D || arg_types[1] != &spv->type_s32v2 || arg_types[2] != &spv->type_f32v4) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(expr)->first_token, tprint("Bad argument types (%s, %s, %s). Intrinsic signature is 'fbuffer_store :: (src: FBufferX, coords: s32vX, data: x32v4)'", arg_types[0]->name, arg_types[1]->name, arg_types[2]->name));
				return spv->compiler->result = OSL_BAD_CALL_ARGUMENTS;
			}
			
			spv_push_op_code(block, 4, OpImageWrite);
			spv_push_word(block, arg_ids[0]);
			spv_push_word(block, arg_ids[1]);
			spv_push_word(block, arg_ids[2]);
			
			*type = &spv->type_f32v4;
			
		} else if (strings_match(call->ident, STR("invocationPixelInterlockBegin"))) {
			if (!(spv->compiler->enabled_features & OSL_FEATURE_INVOCATION_PIXEL_INTERLOCK)) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(expr)->first_token, STR("This requires features OSL_FEATURE_INVOCATION_PIXEL_INTERLOCK flag to be enabled, but it was not passed in Osl_Compile_Desc::enabled_features."));
				return spv->compiler->result = OSL_FEATURE_NOT_ENABLED;
			}
			spv_push_op_code(block, 1, OpBeginInvocationInterlockEXT);
		} else if (strings_match(call->ident, STR("invocationPixelInterlockEnd"))) {
			spv_push_op_code(block, 1, OpEndInvocationInterlockEXT);
		} else if (strings_match(call->ident, STR("round"))) {
			if (call->arg_list.arg_count != 1) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(expr)->first_token, STR("Bad number of arguments. Intrinsic signature is 'round :: (x: FloatType) -> FloatType'"));
				return spv->compiler->result = OSL_BAD_CALL_ARGUMENTS;
			}
			
			Osl_Expr *arg = call->arg_list.args[0];
			u32 arg_id;
			Osl_Type_Info *arg_type;
			
			Osl_Result res = spv_emit_expr(spv, block, arg, &arg_id, &arg_type, false);
			if (res != OSL_OK) return res;
			
			Osl_Type_Info *underlying = arg_type;
			
			if (arg_type->kind == OSL_TYPE_COMPOSITE) underlying = arg_type->val.comp_type.underlying;
			
			if (underlying->kind != OSL_TYPE_FLOAT) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(arg)->first_token, tprint("Bad argument type. Expected a float type, got '%s'. Intrinsic signature is 'round :: (x: FloatType) -> FloatType'", arg_type->name));
				return spv->compiler->result = OSL_BAD_CALL_ARGUMENTS;
			}
			
			*type = arg_type;
			
			if (spv->compiler->target == OSL_TARGET_SPIRV_VULKAN) {
				
				spv_begin_op(block, OpExtInst);
				spv_push_word(block, arg_type->type_id);
				*result_id = spv_push_result_arg(spv, block);
				spv_push_word(block, spv->ext_glsl450_id);
				spv_push_word(block, 1); // OpRound
				spv_push_word(block, arg_id);
				spv_end_op(block);
				
			} else {
				u32 const_half_id = spv_push_decl_constant_f32(spv, &spv->const_block, spv->type_f32.type_id, 0.5f);
				u32 const_zero_id = spv_push_decl_constant_f32(spv, &spv->const_block, spv->type_f32.type_id, 0.0f);
				
			    Osl_Type_Info *int_type = &spv->type_s32;
			    u32 bool_type = spv->type_bool.type_id;
			    
				if (arg_type->kind == OSL_TYPE_COMPOSITE) {
					u32 comps_half[4] = {const_half_id, const_half_id, const_half_id, const_half_id};
					const_half_id = spv_push_op_composite_construct(spv, block, arg_type->type_id, comps_half, arg_type->val.comp_type.component_count);
					u32 comps_zero[4] = {const_zero_id, const_zero_id, const_zero_id, const_zero_id};
					const_zero_id = spv_push_op_composite_construct(spv, block, arg_type->type_id, comps_zero, arg_type->val.comp_type.component_count);
					
					if (arg_type->val.comp_type.component_count == 2) {
						int_type = &spv->type_s32v2;
						bool_type = spv->type_boolv2.type_id;
					} else if (arg_type->val.comp_type.component_count == 3) {
						int_type = &spv->type_s32v3;
						bool_type = spv->type_boolv3.type_id;
					} else if (arg_type->val.comp_type.component_count == 4) {
						int_type = &spv->type_s32v4;
						bool_type = spv->type_boolv4.type_id;
					} else assert(false);
				}
				
				// Add 0.5 to arg
				spv_push_op_code(block, 5, OpFAdd);
				spv_push_word(block, arg_type->type_id);
			    u32 arg_plus_half_id = spv_push_result_arg(spv, block);
			    spv_push_word(block, arg_id);
			    spv_push_word(block, const_half_id);
			    
			    // neg arg
			    spv_push_op_code(block, 4, OpFNegate);
			    spv_push_word(block, arg_type->type_id);
			    u32 neg_id = spv_push_result_arg(spv, block);
			    spv_push_word(block, arg_id);
			    
			    // add 0.5 to neg arg
			    spv_push_op_code(block, 5, OpFAdd);
				spv_push_word(block, arg_type->type_id);
			    u32 neg_plus_half_id = spv_push_result_arg(spv, block);
			    spv_push_word(block, neg_id);
			    spv_push_word(block, const_half_id);
			    
			    // Truncate arg to int
				spv_push_op_code(block, 4, OpConvertFToS);
				spv_push_word(block, int_type->type_id);
			    u32 arg_trunc = spv_push_result_arg(spv, block);
			    spv_push_word(block, arg_plus_half_id);
			    
			    // Truncate neg to int
				spv_push_op_code(block, 4, OpConvertFToS);
				spv_push_word(block, int_type->type_id);
			    u32 neg_trunc = spv_push_result_arg(spv, block);
			    spv_push_word(block, neg_plus_half_id);
			    
			    // Convert arg back to float
				spv_push_op_code(block, 4, OpConvertSToF);
				spv_push_word(block, arg_type->type_id);
			    u32 arg_rounded = spv_push_result_arg(spv, block);
			    spv_push_word(block, arg_trunc);
			    
			    // Convert neg back to float
				spv_push_op_code(block, 4, OpConvertSToF);
				spv_push_word(block, arg_type->type_id);
			    u32 neg_rounded = spv_push_result_arg(spv, block);
			    spv_push_word(block, neg_trunc);
			    
			    // neg neg
				spv_push_op_code(block, 4, OpFNegate);
				spv_push_word(block, arg_type->type_id);
			    u32 neg_neg_rounded = spv_push_result_arg(spv, block);
			    spv_push_word(block, neg_rounded);
			    
			    
			    
				spv_push_op_code(block, 5, OpFOrdGreaterThanEqual);
				spv_push_word(block, bool_type);
			    u32 mask = spv_push_result_arg(spv, block);
			    spv_push_word(block, arg_id);
			    spv_push_word(block, const_zero_id);
			    
				spv_push_op_code(block, 6, OpSelect);
				spv_push_word(block, arg_type->type_id);
			    *result_id = spv_push_result_arg(spv, block);
			    spv_push_word(block, mask);
			    spv_push_word(block, arg_rounded);
			    spv_push_word(block, neg_neg_rounded);
			}
			
		} else if (strings_match(call->ident, STR("floor"))) {
			
			if (call->arg_list.arg_count != 1) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(expr)->first_token, STR("Bad number of arguments. Intrinsic signature is 'round :: (x: FloatType) -> FloatType'"));
				return spv->compiler->result = OSL_BAD_CALL_ARGUMENTS;
			}
			
			Osl_Expr *arg = call->arg_list.args[0];
			u32 arg_id;
			Osl_Type_Info *arg_type;
			
			Osl_Result res = spv_emit_expr(spv, block, arg, &arg_id, &arg_type, false);
			if (res != OSL_OK) return res;
			
			Osl_Type_Info *underlying = arg_type;
			
			if (arg_type->kind == OSL_TYPE_COMPOSITE) underlying = arg_type->val.comp_type.underlying;
			
			if (underlying->kind != OSL_TYPE_FLOAT) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(arg)->first_token, tprint("Bad argument type. Expected a float type, got '%s'. Intrinsic signature is 'round :: (x: FloatType) -> FloatType'", arg_type->name));
				return spv->compiler->result = OSL_BAD_CALL_ARGUMENTS;
			}
			
			if (spv->compiler->target == OSL_TARGET_SPIRV_VULKAN) {
				
				spv_begin_op(block, OpExtInst);
				spv_push_word(block, arg_type->type_id);
				*result_id = spv_push_result_arg(spv, block);
				spv_push_word(block, spv->ext_glsl450_id);
				spv_push_word(block, 8); // OpFloor
				spv_push_word(block, arg_id);
				spv_end_op(block);
				
			} else {
			
				u32 const_one_id = spv_push_decl_constant_u32(spv, &spv->const_block, spv->type_s32.type_id, 1);
				u32 const_zero_id = spv_push_decl_constant_f32(spv, &spv->const_block, spv->type_f32.type_id, 0.0f);
				
			    Osl_Type_Info *int_type = &spv->type_s32;
			    u32 bool_type = spv->type_bool.type_id;
			    
				if (arg_type->kind == OSL_TYPE_COMPOSITE) {
					u32 comps_one[4] = {const_one_id, const_one_id, const_one_id, const_one_id};
					const_one_id = spv_push_op_composite_construct(spv, block, spv->type_s32.type_id, comps_one, arg_type->val.comp_type.component_count);
					u32 comps_zero[4] = {const_zero_id, const_zero_id, const_zero_id, const_zero_id};
					const_zero_id = spv_push_op_composite_construct(spv, block, spv->type_f32.type_id, comps_zero, arg_type->val.comp_type.component_count);
					
					if (arg_type->val.comp_type.component_count == 2) {
						int_type = &spv->type_s32v2;
						bool_type = spv->type_boolv2.type_id;
					} else if (arg_type->val.comp_type.component_count == 3) {
						int_type = &spv->type_s32v3;
						bool_type = spv->type_boolv3.type_id;
					} else if (arg_type->val.comp_type.component_count == 4) {
						int_type = &spv->type_s32v4;
						bool_type = spv->type_boolv4.type_id;
					} else assert(false);
				}
			    
			    // Truncate arg to int
				spv_push_op_code(block, 4, OpConvertFToS);
				spv_push_word(block, int_type->type_id);
			    u32 arg_trunc = spv_push_result_arg(spv, block);
			    spv_push_word(block, arg_id);
			    
			    // Trunc minus one
				spv_push_op_code(block, 5, OpISub);
				spv_push_word(block, int_type->type_id);
			    u32 arg_trunc_minus_one = spv_push_result_arg(spv, block);
			    spv_push_word(block, arg_trunc);
			    spv_push_word(block, const_one_id);
			    
				spv_push_op_code(block, 5, OpFOrdLessThan);
				spv_push_word(block, bool_type);
			    u32 less_cond = spv_push_result_arg(spv, block);
			    spv_push_word(block, arg_id);
			    spv_push_word(block, const_zero_id);
			    
			    spv_push_op_code(block, 6, OpSelect);
				spv_push_word(block, int_type->type_id);
			    u32 selected_trunc = spv_push_result_arg(spv, block);
			    spv_push_word(block, less_cond);
			    spv_push_word(block, arg_trunc_minus_one);
			    spv_push_word(block, arg_trunc);
			    
			    // Convert selected_trunc back to float
				spv_push_op_code(block, 4, OpConvertSToF);
				spv_push_word(block, arg_type->type_id);
			    *result_id = spv_push_result_arg(spv, block);
			    spv_push_word(block, selected_trunc);
		    }
		    *type = arg_type;
			
		} else if (strings_match(call->ident, STR("ceil"))) {
			if (call->arg_list.arg_count != 1) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(expr)->first_token, STR("Bad number of arguments. Intrinsic signature is 'round :: (x: FloatType) -> FloatType'"));
				return spv->compiler->result = OSL_BAD_CALL_ARGUMENTS;
			}
			
			Osl_Expr *arg = call->arg_list.args[0];
			u32 arg_id;
			Osl_Type_Info *arg_type;
			
			Osl_Result res = spv_emit_expr(spv, block, arg, &arg_id, &arg_type, false);
			if (res != OSL_OK) return res;
			
			Osl_Type_Info *underlying = arg_type;
			
			if (arg_type->kind == OSL_TYPE_COMPOSITE) underlying = arg_type->val.comp_type.underlying;
			
			if (underlying->kind != OSL_TYPE_FLOAT) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(arg)->first_token, tprint("Bad argument type. Expected a float type, got '%s'. Intrinsic signature is 'round :: (x: FloatType) -> FloatType'", arg_type->name));
				return spv->compiler->result = OSL_BAD_CALL_ARGUMENTS;
			}
			if (spv->compiler->target == OSL_TARGET_SPIRV_VULKAN) {
				
				spv_begin_op(block, OpExtInst);
				spv_push_word(block, arg_type->type_id);
				*result_id = spv_push_result_arg(spv, block);
				spv_push_word(block, spv->ext_glsl450_id);
				spv_push_word(block, 9); // OpCeil
				spv_push_word(block, arg_id);
				spv_end_op(block);
				
			} else {
			
				u32 const_one_id = spv_push_decl_constant_u32(spv, &spv->const_block, spv->type_s32.type_id, 1);
				u32 const_zero_id = spv_push_decl_constant_f32(spv, &spv->const_block, spv->type_f32.type_id, 0.0f);
				
			    Osl_Type_Info *int_type = &spv->type_s32;
			    u32 bool_type = spv->type_bool.type_id;
			    
				if (arg_type->kind == OSL_TYPE_COMPOSITE) {
					u32 comps_one[4] = {const_one_id, const_one_id, const_one_id, const_one_id};
					const_one_id = spv_push_op_composite_construct(spv, block, spv->type_s32.type_id, comps_one, arg_type->val.comp_type.component_count);
					u32 comps_zero[4] = {const_zero_id, const_zero_id, const_zero_id, const_zero_id};
					const_zero_id = spv_push_op_composite_construct(spv, block, spv->type_f32.type_id, comps_zero, arg_type->val.comp_type.component_count);
					
					if (arg_type->val.comp_type.component_count == 2) {
						int_type = &spv->type_s32v2;
						bool_type = spv->type_boolv2.type_id;
					} else if (arg_type->val.comp_type.component_count == 3) {
						int_type = &spv->type_s32v3;
						bool_type = spv->type_boolv3.type_id;
					} else if (arg_type->val.comp_type.component_count == 4) {
						int_type = &spv->type_s32v4;
						bool_type = spv->type_boolv4.type_id;
					} else assert(false);
				}
			    
			    // Truncate arg to int
				spv_push_op_code(block, 4, OpConvertFToS);
				spv_push_word(block, int_type->type_id);
			    u32 arg_trunc = spv_push_result_arg(spv, block);
			    spv_push_word(block, arg_id);
			    
			    // Trunc plus one
				spv_push_op_code(block, 5, OpIAdd);
				spv_push_word(block, int_type->type_id);
			    u32 arg_trunc_plus_one = spv_push_result_arg(spv, block);
			    spv_push_word(block, arg_trunc);
			    spv_push_word(block, const_one_id);
			    
				spv_push_op_code(block, 5, OpFOrdGreaterThan);
				spv_push_word(block, bool_type);
			    u32 less_cond = spv_push_result_arg(spv, block);
			    spv_push_word(block, arg_id);
			    spv_push_word(block, const_zero_id);
			    
			    spv_push_op_code(block, 6, OpSelect);
				spv_push_word(block, int_type->type_id);
			    u32 selected_trunc = spv_push_result_arg(spv, block);
			    spv_push_word(block, less_cond);
			    spv_push_word(block, arg_trunc_plus_one);
			    spv_push_word(block, arg_trunc);
			    
			    // Convert selected_trunc back to float
				spv_push_op_code(block, 4, OpConvertSToF);
				spv_push_word(block, arg_type->type_id);
			    *result_id = spv_push_result_arg(spv, block);
			    spv_push_word(block, selected_trunc);
		    }
		    *type = arg_type;
		} else {
			if (!(spv->compiler->enabled_features & OSL_FEATURE_INVOCATION_PIXEL_INTERLOCK)) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(expr)->first_token, STR("This requires features OSL_FEATURE_INVOCATION_PIXEL_INTERLOCK flag to be enabled, but it was not passed in Osl_Compile_Desc::enabled_features."));
				return spv->compiler->result = OSL_FEATURE_NOT_ENABLED;
			}
			spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(expr)->first_token, STR("Could not resolve this to a function or intrinsic, but it is being used in a function call."));
			return spv->compiler->result = OSL_UNRESOLVED_FUNCTION_OR_INTRINSIC;
		}
		
		break;
	}
	case OSL_EXPR_TYPE_IDENT: // fallthrough
	default: {
		assert(false);
		break;
	}
	
	}
	
	return OSL_OK;
}

unit_local Osl_Result spv_emit_node(Spv_Converter *spv, Spv_Block *block, Osl_Node *node) {

	switch (node->kind) {
	case OSL_NODE_BLOCK: {
		for (u32 i = 0; i < node->val.block.top_node_count; i += 1) {
			Osl_Result res = spv_emit_node(spv, block, node->val.block.top_nodes[i]);
			if (res != OSL_OK) return res;
		}
		break;
	}
	case OSL_NODE_STRUCT_DECL: {
		break;
	}
	case OSL_NODE_EXPR_ALIAS: {
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
		
		if (decl->type_ident.view_type == OSL_VIEW_BLOCK) {
			if (decl_type->kind != OSL_TYPE_STRUCT) {
				spv->compiler->err_log = _osl_tprint_token(spv->compiler, decl->type_ident.token, STR("BlockView's must have a struct type as the interpretation type."));
				return spv->compiler->result = OSL_BLOCK_TYPE_IS_NOT_STRUCT;
			}
		}
		
		spv_begin_op(&spv->debug_block, OpName);
		spv_push_word(&spv->debug_block, (u32)decl->vnum);
		spv_push_string_arg(&spv->debug_block, decl->ident);
		spv_end_op(&spv->debug_block);
		
		Spv_Storage_Class storage_class = SpvStorageClass_Private;
		
		if (decl->storage_class != OSL_STORAGE_DEFAULT) {
			
			switch (decl->storage_class) {
				
			case OSL_STORAGE_INPUT:  storage_class = SpvStorageClass_Input; break;
			case OSL_STORAGE_OUTPUT: storage_class = SpvStorageClass_Output; break;
			case OSL_STORAGE_BINDING: 
				if (decl_type->kind == OSL_TYPE_IMAGE2DF || decl_type->kind == OSL_TYPE_FBUFFER2D || decl_type->kind == OSL_TYPE_SAMPLE_MODE)
					storage_class = SpvStorageClass_UniformConstant;
				else
					storage_class = SpvStorageClass_Uniform;
				break;
			
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
					
					if (decl->storage_args.arg_count >= 1) {
						spv_push_decoration(&spv->annotations_block, (u32)decl->vnum, SpvDecoration_Location, (u32*)&decl->storage_args.args[0]->val.lit.lit_int, 1); 
					}
				}
				break;
			
			case OSL_STORAGE_BINDING:
				if (decl->storage_args.arg_count != 1) {
					spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(decl)->first_token, tprint("Expected exactly 1 integer argument for location. Got '%i' arguments.", decl->storage_args.arg_count));
					return spv->compiler->result = OSL_BAD_DECORATION_ARGUMENTS;
				}
				
				if (decl->storage_args.args[0]->kind != OSL_EXPR_LITERAL_INT) {
					spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(decl)->first_token, tprint("Expected exactly 1 INTEGER argument for location."));
					return spv->compiler->result = OSL_BAD_DECORATION_ARGUMENTS;
				}
				
				if (decl->storage_args.arg_count >= 1) {
					spv_push_decoration(&spv->annotations_block, (u32)decl->vnum, SpvDecoration_Binding, (u32*)&decl->storage_args.args[0]->val.lit.lit_int, 1); 
					u32 zero = 0;
					spv_push_decoration(&spv->annotations_block, (u32)decl->vnum, SpvDecoration_DescriptorSet, &zero, 1); 
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
		case OSL_BUILTIN_PIXEL_COORD: {
			u32 arg = SpvBuiltin_FragCoord;
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
	
	case OSL_NODE_IF_CHAIN: {
		
		Osl_If_Chain *if_chain = &node->val.if_chain;
		
		// Reserve ids for future labels
		u32 base_label_id = spv->next_id;
		spv->next_id += if_chain->branch_count;
		u32 base_cond_id = spv->next_id;
		spv->next_id += if_chain->branch_count;
		u32 base_merge_id = spv->next_id;
		spv->next_id += if_chain->branch_count;
		
		spv_push_op_code(block, 2, OpBranch);
		spv_push_word(block, base_cond_id);
    	
    	for (u64 i = 0; i < if_chain->branch_count; i += 1) {
    		
			spv_push_op_code(block, 2, OpLabel);
    		spv_push_word(block, base_cond_id+(u32)i);
    		
			if (!if_chain->conditions[i]) {
				assert(i == if_chain->branch_count-1);
				spv_push_op_code(block, 2, OpBranch);
	    		spv_push_word(block, base_label_id+(u32)i);
			} else {
				Osl_Type_Info *cond_type;
				u32 cond_id;
				Osl_Result res = spv_emit_expr(spv, block, if_chain->conditions[i], &cond_id, &cond_type, false);
				if (res != OSL_OK) return res;
				
				// Convert int to bool
				if (cond_type->kind == OSL_TYPE_INT) {
					u32 id_zero = spv_push_decl_constant_u32(spv, &spv->const_block, spv->type_u32.type_id, 0);
				
					spv_begin_op(block, OpINotEqual);
					spv_push_word(block, spv->type_bool.type_id);
				    u32 new_cond_id = spv_push_result_arg(spv, block);
				    spv_push_word(block, cond_id);
				    spv_push_word(block, id_zero);
					spv_end_op(block);
					
					cond_id = new_cond_id;
					cond_type = &spv->type_bool;
				}
				
				if (cond_type->kind != OSL_TYPE_BOOL) {
					spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(if_chain->conditions[i])->first_token, tprint("Expected an expression which evaluates to a logical value, but got an expressions which evaluates to a value of type %s.", cond_type->name));
					return spv->compiler->result = OSL_NOT_A_LOGICAL_TYPE;
				}
				
				spv_push_op_code(block, 3, OpSelectionMerge);
				spv_push_word(block, base_merge_id+(u32)i);
				spv_push_word(block, 0); // todo(charlie) @flatten @noflatten
				
				spv_begin_op(block, OpBranchConditional);
				spv_push_word(block, cond_id);
				spv_push_word(block, base_label_id+(u32)i);
				if (i != if_chain->branch_count-1) 
					spv_push_word(block, base_cond_id+(u32)i+1);
				else
					spv_push_word(block, base_merge_id+(u32)i); // Last condition branch must end up at merge point on false
				spv_end_op(block);
			}
			
			
			spv_push_op_code(block, 2, OpLabel);
    		spv_push_word(block, base_label_id+(u32)i);
    		
			Osl_Result res = spv_emit_node(spv, block, _osl_get_node(if_chain->blocks[i]));
			if (res != OSL_OK) return res;
			spv_push_op_code(block, 2, OpBranch);
		    spv_push_word(block, base_merge_id+(u32)i);
		}
		
		assert(if_chain->branch_count > 0);
    	for (s64 i = (s64)if_chain->branch_count-1; i >= 0; i -= 1) {
    		spv_push_op_code(block, 2, OpLabel);
    		spv_push_word(block, base_merge_id+(u32)i);
    		
    		if (i > 0) {
	    		spv_push_op_code(block, 2, OpBranch);
	    		spv_push_word(block, base_merge_id+(u32)i-1);
    		}
    	}
		
		break;
	}
	case OSL_NODE_LOOP: {
	
		Osl_Loop *loop = &node->val.loop;
	
		u32 start_label = spv->next_id++;
		u32 cond_label = spv->next_id++;
		u32 body_label = spv->next_id++;
		u32 continue_label = spv->next_id++;
		u32 break_label = spv->next_id++;
		
		spv_push_op_code(block, 2, OpBranch);
		spv_push_word(block, start_label);
		spv_push_op_code(block, 2, OpLabel);
		spv_push_word(block, start_label);
		
		spv_push_op_code(block, 4, OpLoopMerge);
		spv_push_word(block, break_label);
		spv_push_word(block, continue_label);
		spv_push_word(block, 0);
		
		spv_push_op_code(block, 2, OpBranch);
		spv_push_word(block, cond_label);
		spv_push_op_code(block, 2, OpLabel);
		spv_push_word(block, cond_label);
		
		Osl_Type_Info *cond_type;
		u32 cond_id;
		Osl_Result res = spv_emit_expr(spv, block, loop->condition, &cond_id, &cond_type, false);
		if (res != OSL_OK) return res;
		
		// Convert int to bool
		if (cond_type->kind == OSL_TYPE_INT) {
			u32 id_zero = spv_push_decl_constant_u32(spv, &spv->const_block, spv->type_u32.type_id, 0);
		
			spv_begin_op(block, OpINotEqual);
			spv_push_word(block, spv->type_bool.type_id);
		    u32 new_cond_id = spv_push_result_arg(spv, block);
		    spv_push_word(block, cond_id);
		    spv_push_word(block, id_zero);
			spv_end_op(block);
			
			cond_id = new_cond_id;
			cond_type = &spv->type_bool;
		}
		
		if (cond_type->kind != OSL_TYPE_BOOL) {
			spv->compiler->err_log = _osl_tprint_token(spv->compiler, _osl_get_node(loop->condition)->first_token, tprint("Expected an expression which evaluates to a logical value, but got an expressions which evaluates to a value of type %s.", cond_type->name));
			return spv->compiler->result = OSL_NOT_A_LOGICAL_TYPE;
		}
		
		spv_begin_op(block, OpBranchConditional);
		spv_push_word(block, cond_id);
		spv_push_word(block, body_label);
		spv_push_word(block, break_label);
		spv_end_op(block);
		
		spv_push_op_code(block, 2, OpLabel);
		spv_push_word(block, body_label);
		
		res = spv_emit_node(spv, block, _osl_get_node(loop->block));
		if (res != OSL_OK) return res;
		
		spv_push_op_code(block, 2, OpBranch);
		spv_push_word(block, continue_label);
		
		spv_push_op_code(block, 2, OpLabel);
		spv_push_word(block, continue_label);
		spv_push_op_code(block, 2, OpBranch);
		spv_push_word(block, start_label);
		
		spv_push_op_code(block, 2, OpLabel);
		spv_push_word(block, break_label);
		
		break;
	}
	case OSL_NODE_EXPR: {
		u32 _;
		Osl_Type_Info *__;
		Osl_Result res = spv_emit_expr(spv, block, &node->val.expr, &_, &__, false);
		if (res != OSL_OK) return res;
		
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
		} else if (p < end-2 && strings_match((string){2, p}, STR(">="))) {
			token->length = 2;
			token->kind = OSL_TOKEN_KIND_GTE;
			p += 2;
			continue;
		} else if (p < end-2 && strings_match((string){2, p}, STR("<="))) {
			token->length = 2;
			token->kind = OSL_TOKEN_KIND_LTE;
			p += 2;
			continue;
		} else if (p < end-2 && strings_match((string){2, p}, STR("=="))) {
			token->length = 2;
			token->kind = OSL_TOKEN_KIND_EQ;
			p += 2;
			continue;
		} else if (p < end-2 && strings_match((string){2, p}, STR("!="))) {
			token->length = 2;
			token->kind = OSL_TOKEN_KIND_NEQ;
			p += 2;
			continue;
		} else if (p < end-2 && strings_match((string){2, p}, STR("&&"))) {
			token->length = 2;
			token->kind = OSL_TOKEN_KIND_LAND;
			p += 2;
			continue;
		} else if (p < end-2 && strings_match((string){2, p}, STR("||"))) {
			token->length = 2;
			token->kind = OSL_TOKEN_KIND_LOR;
			p += 2;
			continue;
		} else if (p < end-2 && strings_match((string){2, p}, STR("::"))) {
			token->length = 2;
			token->kind = OSL_TOKEN_KIND_DOUBLE_COLON;
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
unit_local string _osl_token_text(Osl_Compiler *compiler, Osl_Token *token) {
	return (string) { token->length, compiler->source.data+token->source_pos };
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
	memset(arrows.data, '^', (sys_uint)token->length);
	
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
unit_local inline bool _osl_can_be_start_of_expr(Osl_Token *token) {
	return (token->kind == OSL_TOKEN_KIND_IDENTIFIER && (token+1)->kind != OSL_TOKEN_KIND_IDENTIFIER)
	    || token->kind == '-'
	    || token->kind == '('
	    ;
}
unit_local Osl_Expr *_osl_parse_expr(Osl_Compiler *compiler, Osl_Block *block, Osl_Token *expr_start, Osl_Token **done_token);

unit_local Osl_Result _osl_parse_type_ident(Osl_Compiler *compiler, Osl_Block *block, Osl_Token *first, Osl_Token **done_token, Osl_Type_Ident *result) {
	*result = (Osl_Type_Ident) {0};
	result->token = first;
	string first_text = (string) { first->length, compiler->source.data + first->source_pos };
	if (first->kind == OSL_TOKEN_KIND_IDENTIFIER && !strings_match(STR("BlockView"), first_text) && !strings_match(STR("FBuffer2D"), first_text)) {
		result->name = first_text;
		*done_token = first+1;
		return OSL_OK;
	}
	
	if (strings_match(STR("BlockView"), first_text)) {
		if (!_osl_exp_token(compiler, first+1, OSL_TOKEN_KIND_LPAREN))
			return compiler->result;
		if (!_osl_exp_token(compiler, first+2, OSL_TOKEN_KIND_IDENTIFIER))
			return compiler->result;
		if (!_osl_exp_token(compiler, first+3, OSL_TOKEN_KIND_RPAREN))
			return compiler->result;
		
		Osl_Token *type_token = first+2;
		
		result->view_type = OSL_VIEW_BLOCK;
		result->name = (string) { type_token->length, compiler->source.data + type_token->source_pos };
		
		*done_token = first+4;
	} else if (strings_match(STR("FBuffer2D"), first_text)) {
		if (!_osl_exp_token(compiler, first+1, OSL_TOKEN_KIND_LPAREN))
			return compiler->result;
		if (!_osl_exp_token(compiler, first+2, OSL_TOKEN_KIND_IDENTIFIER))
			return compiler->result;
		if (!_osl_exp_token(compiler, first+3, OSL_TOKEN_KIND_RPAREN))
			return compiler->result;
		
		Osl_Token *view_token = first+2;
		
		result->name = first_text;
		
		
		string view_text = _osl_token_text(compiler, view_token);
		if (strings_match(view_text, STR("RGBA32F")))
			result->view_type = OSL_VIEW_RGBA32F;
		else if (strings_match(view_text, STR("RGBA16F")))
			result->view_type = OSL_VIEW_RGBA16F;
		else if (strings_match(view_text, STR("R32F")))
			result->view_type = OSL_VIEW_R32F;
		else if (strings_match(view_text, STR("RGBA8_UNORM")))
			result->view_type = OSL_VIEW_RGBA8_UNORM;
		else if (strings_match(view_text, STR("RGBA8_SNORM")))
			result->view_type = OSL_VIEW_RGBA8_SNORM;
		else if (strings_match(view_text, STR("RGBA32U")))
			result->view_type = OSL_VIEW_RGBA32U;
		else if (strings_match(view_text, STR("RGBA16U")))
			result->view_type = OSL_VIEW_RGBA16U;
		else if (strings_match(view_text, STR("RGBA8U")))
			result->view_type = OSL_VIEW_RGBA8U;
		else if (strings_match(view_text, STR("R32U")))
			result->view_type = OSL_VIEW_R32U;
		else if (strings_match(view_text, STR("RGBA32S")))
			result->view_type = OSL_VIEW_RGBA32S;
		else if (strings_match(view_text, STR("RGBA16S")))
			result->view_type = OSL_VIEW_RGBA16S;
		else if (strings_match(view_text, STR("RGBA8S")))
			result->view_type = OSL_VIEW_RGBA8S;
		else if (strings_match(view_text, STR("R32S")))
			result->view_type = OSL_VIEW_R32S;
		else {
			compiler->err_log = _osl_tprint_token(compiler, view_token, STR("This is not a valid FBuffer view type. It must be one of the following: RGBA32F, RGBA16F, R32F, RGBA8_UNORM, RGBA8_SNORM, RGBA32U, RGBA16U, RGBA8U, R32U, RGBA32S, RGBA16S, RGBA8S, R32S"));
			return compiler->result = OSL_INVALID_FBUFFER_VIEW;
		}
		
		*done_token = first+4;
	} else {
		Osl_Token *next = first;
		
		while (next->kind == OSL_TOKEN_KIND_LBRACKET) {
			
			if (result->indirection_count >= 8) {
				compiler->err_log = _osl_tprint_token(compiler, next, STR("The max number of type indirections is 8. This exceeds that."));
				return compiler->result = OSL_EXCEED_MAX_TYPE_INDIRECTIONS;
			}
			
			Osl_Token *count_tok = next+1;
			
			if (count_tok->kind == '?') {
				if (!_osl_exp_token(compiler, count_tok+1, OSL_TOKEN_KIND_RBRACKET)) {
					return compiler->result;
				}
				result->indirections[result->indirection_count++].array_count = 0;
				next = count_tok+2;
			} else {
				Osl_Token *close_bracket;
				Osl_Expr *count_expr = _osl_parse_expr(compiler, block, count_tok, &close_bracket);
				if (!count_expr) return compiler->result;
				
				if (!_osl_exp_token(compiler, close_bracket, OSL_TOKEN_KIND_RBRACKET)) {
					return compiler->result;
				}
				
				
				result->indirections[result->indirection_count++].array_count = count_expr->val.lit.lit_int;
				next = close_bracket+1;
			}
			
			
		}
		
		if (!_osl_exp_token_msg(compiler, next, OSL_TOKEN_KIND_IDENTIFIER, STR("Expected a type identifier"))) {
			return compiler->result;
		}
		
		result->name = (string) { next->length, compiler->source.data + next->source_pos };
		
		*done_token = next+1;
	}
	
	
	assert(result->token);
	return OSL_OK;
}

unit_local Osl_Result _osl_parse_arg_list(Osl_Compiler *compiler, Osl_Block *block, Osl_Token_Kind close_token, Osl_Token *start, Osl_Token **done_token, Osl_Arg_List *list) {
	*list = (Osl_Arg_List){0};
	assert(list->arg_count == 0); // todo(charlie) tcc compiler bug causes crash here. Maybe we can work around it?
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
	
	if (start[1].kind == close_token) {
		*done_token = start+2;
		return OSL_OK;
	}
	
	Osl_Token *next = start;
	
	while (next->kind != OSL_TOKEN_KIND_EOF && next->kind != close_token) {

		next += 1;
		assertmsgs(list->arg_count < 128, _osl_tprint_token(compiler, next, tprint("Exceeding max allowed argument count of 128 (%i)", list->arg_count)));
		
		
		Osl_Token *sub_expr_start = next;
		Osl_Expr *arg = _osl_parse_expr(compiler, block, sub_expr_start, &next);
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

unit_local inline bool _osl_is_token_two_sided_operator(Osl_Token_Kind kind) {
	return kind == OSL_TOKEN_KIND_STAR
	    || kind == OSL_TOKEN_KIND_LT
	    || kind == OSL_TOKEN_KIND_EQUALS
		|| kind == OSL_TOKEN_KIND_PLUS
		|| kind == OSL_TOKEN_KIND_MINUS
		|| kind == OSL_TOKEN_KIND_FSLASH
	    || kind == OSL_TOKEN_KIND_GT
	    || kind == OSL_TOKEN_KIND_RIGHT_ARROW
		|| kind == OSL_TOKEN_KIND_GTE
		|| kind == OSL_TOKEN_KIND_LTE
		|| kind == OSL_TOKEN_KIND_EQ
		|| kind == OSL_TOKEN_KIND_NEQ
		|| kind == OSL_TOKEN_KIND_LAND
		|| kind == OSL_TOKEN_KIND_LOR
	    ;
}

unit_local Osl_Node *_osl_make_node(Osl_Compiler *compiler, Osl_Block *block, Osl_Token *first, Osl_Node_Kind kind, void **impl_node) {
	Osl_Node *node = (Osl_Node*)arena_push(&compiler->node_arena, sizeof(Osl_Node));
	*node = (Osl_Node){0};
	node->first_token = first;
    node->kind = kind;
    compiler->total_node_count += 1;
    block->nodes[block->node_count++] = node;
    
    switch (kind) {
    	case OSL_NODE_BLOCK:
    		*impl_node = &node->val.block;
    		break;
	    case OSL_NODE_VALUE_DECL:
    		*impl_node = &node->val.value_decl;
	    	break;  
	    case OSL_NODE_EXPR:
    		*impl_node = &node->val.expr;
	    	break;
	    case OSL_NODE_IF_CHAIN:
    		*impl_node = &node->val.if_chain;
	    	break;
	    case OSL_NODE_LOOP:
    		*impl_node = &node->val.loop;
	    	break;
	    case OSL_NODE_STRUCT_DECL:
    		*impl_node = &node->val.struct_decl;
	    	break;
	    case OSL_NODE_EXPR_ALIAS:
    		*impl_node = &node->val.expr_alias;
	    	break;
	    default: assert(false); break;
    }
    return node;
}

unit_local Osl_Expr *_osl_parse_expr_rec(Osl_Compiler *compiler, Osl_Block *block, Osl_Token *expr_start, Osl_Token **done_token, Osl_Op_Kind left_op);

unit_local Osl_Expr *_osl_parse_one_expr(Osl_Compiler *compiler, Osl_Block *block, Osl_Token *expr_start, Osl_Token **done_token, Osl_Op_Kind left_op) {
	
	Osl_Expr *expr = 0;
	
	if (expr_start->kind == '-') {
		Osl_Expr *negated_expr = _osl_parse_expr(compiler, block, expr_start+1, done_token);
		if (!negated_expr) return 0;
		
		if (negated_expr->kind == OSL_EXPR_LITERAL_FLOAT) {
			negated_expr->val.lit.lit_flt = -negated_expr->val.lit.lit_flt;
			expr = negated_expr;
			_osl_get_node(expr)->first_token = expr_start;
		} else if (negated_expr->kind == OSL_EXPR_LITERAL_INT) {
			negated_expr->val.lit.lit_int = -negated_expr->val.lit.lit_int;
			expr = negated_expr;
			_osl_get_node(expr)->first_token = expr_start;
		} else {
			Osl_Expr *op_expr;
			_osl_make_node(compiler, block, expr_start, OSL_NODE_EXPR, (void**)&op_expr);
			op_expr->kind = OSL_EXPR_OP;
			
			op_expr->val.op.op_kind = OSL_OP_UNARY_NEGATE;
			op_expr->val.op.op_token = expr_start-1;
			op_expr->val.op.lhs = negated_expr;
			
			expr = op_expr;
		}
	} else if (expr_start->kind == '!') {
		Osl_Expr *negated_expr = _osl_parse_expr(compiler, block, expr_start+1, done_token);
		if (!negated_expr) return 0;
		if (negated_expr->kind == OSL_EXPR_LITERAL_FLOAT) {
			negated_expr->val.lit.lit_int = (u64)(negated_expr->val.lit.lit_flt == 0.0);
			expr = negated_expr;
			_osl_get_node(expr)->first_token = expr_start;
		} else if (negated_expr->kind == OSL_EXPR_LITERAL_INT) {
			negated_expr->val.lit.lit_int = (u64)(negated_expr->val.lit.lit_int == 0);
			expr = negated_expr;
			_osl_get_node(expr)->first_token = expr_start;
		} else {
			Osl_Expr *op_expr;
			_osl_make_node(compiler, block, expr_start, OSL_NODE_EXPR, (void**)&op_expr);
			op_expr->kind = OSL_EXPR_OP;
			
			op_expr->val.op.op_kind = OSL_OP_UNARY_NAUGHT;
			op_expr->val.op.op_token = expr_start-1;
			op_expr->val.op.lhs = negated_expr;
			
			expr = op_expr;
		}
	} else if (expr_start->kind == OSL_TOKEN_KIND_LPAREN) {
		Osl_Expr *enclosed_expr = _osl_parse_expr(compiler, block, expr_start+1, done_token);
		if (!enclosed_expr) return 0;
		
		if (!_osl_exp_token(compiler, *done_token, OSL_TOKEN_KIND_RPAREN)) {
			string b = _osl_tprint_token(compiler, expr_start, STR("Expected a match for this"));
			compiler->err_log = tprint("%s%s", compiler->err_log, b);
			return 0;
		}
		
		*done_token += 1;
		expr = enclosed_expr;
	} else {
	
		_osl_make_node(compiler, block, expr_start, OSL_NODE_EXPR, (void**)&expr);
		
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
				
				Osl_Result type_res = _osl_parse_type_ident(compiler, block, expr_start, done_token, &inst->type_ident);
				if (type_res != OSL_OK) return 0;
				
				if (inst->type_ident.view_type != OSL_VIEW_DEFAULT) {
					compiler->err_log = _osl_tprint_token(compiler, inst->type_ident.token, STR("Cannot instantiate View types, this doesn't make any sense."));
					compiler->result = OSL_VIEW_INSTANTIATION;
					return 0;
				}
				
				Osl_Result res = _osl_parse_arg_list(compiler, block, list_end, &expr_start[2], done_token, &inst->list);
				if (res != OSL_OK) return 0;
				
				if (inst->type_ident.indirection_count >= 8) {
					compiler->err_log = _osl_tprint_token(compiler, expr_start, STR("The max number of type indirections is 8. This exceeds that."));
					compiler->result = OSL_EXCEED_MAX_TYPE_INDIRECTIONS;
					return 0;
				}
				
			} else if (expr_start[1].kind == OSL_TOKEN_KIND_LPAREN) {
				expr->kind = OSL_EXPR_CALL;
				
				Osl_Call *call = &expr->val.call;
				
				Osl_Token_Kind list_end = OSL_TOKEN_KIND_RPAREN;
				
				call->ident = (string) {expr_start->length, compiler->source.data+expr_start->source_pos};
				
				Osl_Result res = _osl_parse_arg_list(compiler, block, list_end, &expr_start[1], done_token, &call->arg_list);
				if (res != OSL_OK) return 0;
				
				
			} else {
				expr->kind = OSL_EXPR_DECL_IDENT;
				Osl_Block *next_block = block;
				while (next_block) {
					for (u64 j = 0; j < next_block->node_count; j += 1) {
						Osl_Node *node = next_block->nodes[j];
						
						if (node->kind == OSL_NODE_VALUE_DECL) {
							Osl_Value_Decl *decl = &node->val.value_decl;
							if (strings_match(expr_ident, decl->ident)) {
								expr->val.decl = decl;
								break;
							}
						}
					}
					next_block = next_block->parent;
				}
				
				if (!expr->val.decl) {
					expr->kind = OSL_EXPR_ALIAS_IDENT;
					next_block = block;
					while (next_block) {
						for (u64 j = 0; j < next_block->node_count; j += 1) {
							Osl_Node *node = next_block->nodes[j];
							
							if (node->kind == OSL_NODE_EXPR_ALIAS) {
								Osl_Expr_Alias *alias = &node->val.expr_alias;
								if (strings_match(expr_ident, alias->ident)) {
									expr->val.expr_alias = alias;
									break;
								}
							}
						}
						next_block = next_block->parent;
					}
				}
				
				if (!expr->val.decl && !expr->val.expr_alias) {
					if (left_op != 0xFFFF && left_op == OSL_OP_CAST) {
						expr->kind = OSL_EXPR_TYPE_IDENT;
						Osl_Result type_res = _osl_parse_type_ident(compiler, block, expr_start, done_token, &expr->val.type_ident);
						if (expr->val.type_ident.view_type != OSL_VIEW_DEFAULT) {
							compiler->err_log = _osl_tprint_token(compiler, expr->val.type_ident.token, STR("Cast to a View type. This doesn't make any sense."));
							compiler->result = OSL_VIEW_CAST;
							return 0;
						}
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
		
		Osl_Expr *parent_expr;
		_osl_make_node(compiler, block, expr_start, OSL_NODE_EXPR, (void**)&parent_expr);
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
				access->items[access_index].val.index = _osl_parse_expr(compiler, block, access_token, &next);
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

unit_local Osl_Expr * _osl_try_resolve_op(Osl_Expr *lexpr, Osl_Expr *rexpr, Osl_Op_Kind op) {
	if (lexpr->kind == rexpr->kind && lexpr->kind == OSL_EXPR_LITERAL_FLOAT) {
			
			f64 left = lexpr->val.lit.lit_flt;
			f64 right = rexpr->val.lit.lit_flt;
			
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif
		switch (op) {
			case OSL_OP_MUL:  lexpr->val.lit.lit_flt = (f64)(left *  right); break;
			case OSL_OP_DIV:  lexpr->val.lit.lit_flt = (f64)(left /  right); break;
			case OSL_OP_ADD:  lexpr->val.lit.lit_flt = (f64)(left +  right); break;
			case OSL_OP_SUB:  lexpr->val.lit.lit_flt = (f64)(left -  right); break;
			case OSL_OP_GT:   lexpr->val.lit.lit_flt = (f64)(left >  right); break;
			case OSL_OP_LT:   lexpr->val.lit.lit_flt = (f64)(left <  right); break;
			
			case OSL_OP_GTE:  
				lexpr->kind = OSL_EXPR_LITERAL_INT;
				lexpr->val.lit.lit_int = (u64)(left >= right); 
				break;
			case OSL_OP_LTE:  
				lexpr->kind = OSL_EXPR_LITERAL_INT;
				lexpr->val.lit.lit_int = (u64)(left <= right); 
				break;
			case OSL_OP_EQ:   
				lexpr->kind = OSL_EXPR_LITERAL_INT;
				lexpr->val.lit.lit_int = (u64)(left == right); 
				break;
			case OSL_OP_NEQ:  
				lexpr->kind = OSL_EXPR_LITERAL_INT;
				lexpr->val.lit.lit_int = (u64)(left != right); 
				break;
			case OSL_OP_LAND: 
				lexpr->kind = OSL_EXPR_LITERAL_INT;
				lexpr->val.lit.lit_int = (u64)((left != 0.0) && (right != 0.0)); 
				break;
			case OSL_OP_LOR:  
				lexpr->kind = OSL_EXPR_LITERAL_INT;
				lexpr->val.lit.lit_int = (u64)((left != 0.0) || (right != 0.0)); 
				break;
			
			case OSL_OP_CAST: // fallthrough
			case OSL_OP_SET: // fallthrough
			case OSL_OP_UNARY_NEGATE: // fallthrough
			case OSL_OP_UNARY_NAUGHT: // fallthrough
			default: assert(false); break;
		}
#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif			
		
		return lexpr;
		
	} else if (lexpr->kind == rexpr->kind && lexpr->kind == OSL_EXPR_LITERAL_INT) {
		
		u64 left = lexpr->val.lit.lit_int;
		u64 right = rexpr->val.lit.lit_int;
		
		switch (op) {
			case OSL_OP_MUL:  lexpr->val.lit.lit_int = (u64)(left *  right); break;
			case OSL_OP_DIV:  lexpr->val.lit.lit_int = (u64)(left /  right); break;
			case OSL_OP_ADD:  lexpr->val.lit.lit_int = (u64)(left +  right); break;
			case OSL_OP_SUB:  lexpr->val.lit.lit_int = (u64)(left -  right); break;
			case OSL_OP_GT:   lexpr->val.lit.lit_int = (u64)(left >  right); break;
			case OSL_OP_LT:   lexpr->val.lit.lit_int = (u64)(left <  right); break;
			case OSL_OP_GTE:  lexpr->val.lit.lit_int = (u64)(left >= right); break;
			case OSL_OP_LTE:  lexpr->val.lit.lit_int = (u64)(left <= right); break;
			case OSL_OP_EQ:   lexpr->val.lit.lit_int = (u64)(left == right); break;
			case OSL_OP_NEQ:  lexpr->val.lit.lit_int = (u64)(left != right); break;
			case OSL_OP_LAND: lexpr->val.lit.lit_int = (u64)(left && right); break;
			case OSL_OP_LOR:  lexpr->val.lit.lit_int = (u64)(left || right); break;
			
			case OSL_OP_CAST: // fallthrough
			case OSL_OP_SET: // fallthrough
			case OSL_OP_UNARY_NEGATE: // fallthrough
			case OSL_OP_UNARY_NAUGHT: // fallthrough
			default: assert(false); break;
		}
		
		return lexpr;
		
	}
	return 0;
}

unit_local Osl_Expr *_osl_parse_expr_rec(Osl_Compiler *compiler, Osl_Block *block, Osl_Token *expr_start, Osl_Token **done_token, Osl_Op_Kind left_op) {

	Osl_Expr *lexpr = _osl_parse_one_expr(compiler, block, expr_start, done_token, left_op);
	if (!lexpr)  return 0;
	
	if (!_osl_is_token_two_sided_operator((*done_token)->kind)) {
		return lexpr;
	}
	
	Osl_Token *op_token = *done_token;
	
	Osl_Op_Kind rop;
	if (op_token->kind == '+') rop = OSL_OP_ADD;
	else if (op_token->kind == '-') rop = OSL_OP_SUB;
	else if (op_token->kind == '*') rop = OSL_OP_MUL;
	else if (op_token->kind == '/') rop = OSL_OP_DIV;
	else if (op_token->kind == '=') rop = OSL_OP_SET;
	else if (op_token->kind == '>') rop = OSL_OP_GT;
	else if (op_token->kind == '<') rop = OSL_OP_LT;
	else if (op_token->kind == OSL_TOKEN_KIND_RIGHT_ARROW) rop = OSL_OP_CAST;
	else if (op_token->kind == OSL_TOKEN_KIND_GTE) rop = OSL_OP_GTE;
	else if (op_token->kind == OSL_TOKEN_KIND_LTE) rop = OSL_OP_LTE;
	else if (op_token->kind == OSL_TOKEN_KIND_EQ) rop = OSL_OP_EQ;
	else if (op_token->kind == OSL_TOKEN_KIND_NEQ) rop = OSL_OP_NEQ;
	else if (op_token->kind == OSL_TOKEN_KIND_LAND) rop = OSL_OP_LAND;
	else if (op_token->kind == OSL_TOKEN_KIND_LOR) rop = OSL_OP_LOR;
	else {
		compiler->err_log = _osl_tprint_token(compiler, op_token, STR("Bad operator"));
		compiler->result = OSL_BAD_OPERATOR;
		return 0;
	}
	
	
	
	if (left_op != 0xffff && _osl_precedence(left_op) >= _osl_precedence(rop)) {
		*done_token = op_token;
		return lexpr;
	} else {
		Osl_Expr *rexpr = _osl_parse_expr_rec(compiler, block, op_token+1, done_token, rop);
		
		if (!rexpr) 
			return 0;
		
		Osl_Expr *resolved_expr = _osl_try_resolve_op(lexpr, rexpr, rop);
		if (resolved_expr) return resolved_expr;
		
		Osl_Expr *parent_op;
		_osl_make_node(compiler, block, expr_start, OSL_NODE_EXPR, (void**)&parent_op);
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
	
	assert(false);
	return 0;
}
	
unit_local Osl_Expr *_osl_parse_expr(Osl_Compiler *compiler, Osl_Block *block, Osl_Token *expr_start, Osl_Token **done_token) {


	Osl_Expr *last_expr = _osl_parse_expr_rec(compiler, block, expr_start, done_token, (Osl_Op_Kind)0xFFFF);
	if (!last_expr) return 0;
	
	while (_osl_is_token_two_sided_operator((*done_token)->kind)) {
		Osl_Token *op_token = *done_token;
		
		Osl_Op_Kind rop;
		if (op_token->kind == '+') rop = OSL_OP_ADD;
		else if (op_token->kind == '-') rop = OSL_OP_SUB;
		else if (op_token->kind == '*') rop = OSL_OP_MUL;
		else if (op_token->kind == '/') rop = OSL_OP_DIV;
		else if (op_token->kind == '=') rop = OSL_OP_SET;
		else if (op_token->kind == '>') rop = OSL_OP_GT;
		else if (op_token->kind == '<') rop = OSL_OP_LT;
		else if (op_token->kind == OSL_TOKEN_KIND_RIGHT_ARROW) rop = OSL_OP_CAST;
		else if (op_token->kind == OSL_TOKEN_KIND_GTE) rop = OSL_OP_GTE;
		else if (op_token->kind == OSL_TOKEN_KIND_LTE) rop = OSL_OP_LTE;
		else if (op_token->kind == OSL_TOKEN_KIND_EQ) rop = OSL_OP_EQ;
		else if (op_token->kind == OSL_TOKEN_KIND_NEQ) rop = OSL_OP_NEQ;
		else if (op_token->kind == OSL_TOKEN_KIND_LAND) rop = OSL_OP_LAND;
		else if (op_token->kind == OSL_TOKEN_KIND_LOR) rop = OSL_OP_LOR;
		else {
			compiler->err_log = _osl_tprint_token(compiler, op_token, STR("Bad operator"));
			compiler->result = OSL_BAD_OPERATOR;
			return 0;
		}
		
		Osl_Token *next_expr_start = op_token+1;
		
		Osl_Expr *next_expr = _osl_parse_expr_rec(compiler, block, next_expr_start, done_token, rop);
		if (!next_expr) return 0;
		
		Osl_Expr *next_op;
		if (last_expr->kind == OSL_EXPR_OP && _osl_precedence(rop) > _osl_precedence(last_expr->val.op.op_kind)) {
			Osl_Expr *resolved_expr = _osl_try_resolve_op(last_expr->val.op.rhs, next_expr, rop);
			if (resolved_expr) return resolved_expr;
			
			_osl_make_node(compiler, block, expr_start, OSL_NODE_EXPR, (void**)&next_op);
			next_op->kind = OSL_EXPR_OP;
			next_op->val.op.op_kind = rop;
			next_op->val.op.op_token = op_token;
			next_op->val.op.lhs = last_expr->val.op.rhs;
			next_op->val.op.rhs = next_expr;
			last_expr->val.op.rhs = next_op;
		} else {
			Osl_Expr *resolved_expr = _osl_try_resolve_op(last_expr, next_expr, rop);
			if (resolved_expr) return resolved_expr;
			
			_osl_make_node(compiler, block, expr_start, OSL_NODE_EXPR, (void**)&next_op);
			next_op->kind = OSL_EXPR_OP;
			next_op->val.op.op_kind = rop;
			next_op->val.op.op_token = op_token;
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



unit_local Osl_Result _osl_parse_some(Osl_Compiler *compiler, Osl_Block *block, Osl_Token *start, Osl_Token **done_token, Osl_Token_Kind end_token);

unit_local Osl_Result _osl_parse_one(Osl_Compiler *compiler, Osl_Block *block, Osl_Token *current, Osl_Token **done_token) {
	Osl_Token *first = current;
	Osl_Token *next = ++current;
	if (block->is_procedural && (strings_match(_osl_token_text(compiler, first), STR("if"))
							 || (first->kind == '#' && strings_match(_osl_token_text(compiler, next), STR("if"))))) {
	
		
		Osl_If_Chain *if_chain;
		Osl_Node *n = _osl_make_node(compiler, block, first, OSL_NODE_IF_CHAIN, (void**)&if_chain);
        
		if (first->kind == '#') {
			if_chain->is_compile_time = true;
			next = ++current;
		}
		
        Osl_Expr *first_cond = _osl_parse_expr(compiler, block, next, &current);
        if (!first_cond) return compiler->result;
        
        Osl_Block *first_block;
		_osl_make_node(compiler, block, current, OSL_NODE_BLOCK, (void**)&first_block);
        first_block->is_procedural = true;
        first_block->parent = block;
        
        if (current->kind == OSL_TOKEN_KIND_LBRACE) {
        	_osl_parse_some(compiler, first_block, current+1, &current, OSL_TOKEN_KIND_RBRACE);
        	if (compiler->result != OSL_OK) return compiler->result;
        } else {
        	_osl_parse_one(compiler, first_block, current, &current);
        	if (compiler->result != OSL_OK) return compiler->result;
        }
        
        if_chain->conditions[if_chain->branch_count] = first_cond;
        if_chain->blocks[if_chain->branch_count++] = first_block;
        
        while (strings_match(_osl_token_text(compiler, current), STR("else"))) {
        	
        	bool is_final_block = !strings_match(_osl_token_text(compiler, current+1), STR("if"));
        	if (!is_final_block) current++;
        	
        	Osl_Expr *cond = 0;
        	
        	if (!is_final_block) {
		        cond = _osl_parse_expr(compiler, block, current+1, &current);
	        	if (!cond) return compiler->result;
        	} else {
        		current += 1;
        	}
	        
	        Osl_Block *sub_block;
			_osl_make_node(compiler, block, current, OSL_NODE_BLOCK, (void**)&sub_block);
	        sub_block->is_procedural = true;
	        sub_block->parent = block;
	        
	        if (current->kind == OSL_TOKEN_KIND_LBRACE) {
        		_osl_parse_some(compiler, sub_block, current+1, &current, OSL_TOKEN_KIND_RBRACE);
        		if (compiler->result != OSL_OK) return compiler->result;
	        } else {
	        	_osl_parse_one(compiler, sub_block, current, &current);
	        	if (compiler->result != OSL_OK) return compiler->result;
	        }
	        
	        if_chain->conditions[if_chain->branch_count] = cond;
	        if_chain->blocks[if_chain->branch_count++] = sub_block;
        }
        
        // Eliminate dead branches
        bool any_live = false;
        for (s64 i = 0; i < (s64)if_chain->branch_count; i += 1) {
        	Osl_Expr *cond = if_chain->conditions[i];
        	
        	bool is_literal = cond && (cond->kind == OSL_EXPR_LITERAL_FLOAT || cond->kind == OSL_EXPR_LITERAL_INT);
        	
        	if (is_literal && cond->val.lit.lit_int == 0) {
        		if_chain->branch_count -= 1;
        		if (i < (s64)if_chain->branch_count) {
        			memmove(&if_chain->conditions[i], &if_chain->conditions[i+1], (sys_uint)(if_chain->branch_count-(u64)i) * sizeof(void*));
        			memmove(&if_chain->blocks[i], &if_chain->blocks[i+1], (sys_uint)(if_chain->branch_count-(u64)i) * sizeof(void*));
        		}
        		i -= 1;
        	} else {
        		any_live = true;
        		
        		if (is_literal) {
        			// A branch condition is non-zero literal, which means it will pass, which means
        			// any branches following this branch wont ever be executed or even evaluated.
	        		// todo(charlie) #memory #speed pop back node_arena position
        			if_chain->branch_count = (u64)i+1;
        			if_chain->conditions[i] = 0; // Treat this as the last else block, because its the last block and its always true
        			break;
        		}
        	}
        }
        
        // Only add as a top node if any condition is not 0 at compile time
        // todo(charlie) #memory #speed pop back node_arena position
        if (if_chain->branch_count == 1 && if_chain->conditions[0] == 0) {
        	block->top_nodes[block->top_node_count++] = _osl_get_node(if_chain->blocks[0]);
        } else if (any_live) {
        	block->top_nodes[block->top_node_count++] = n;
        }
        
	} else if (block->is_procedural && strings_match(_osl_token_text(compiler, first), STR("while"))) {
		Osl_Loop *loop;
		Osl_Node *n = _osl_make_node(compiler, block, first, OSL_NODE_LOOP, (void**)&loop);
        
        
        Osl_Expr *cond = _osl_parse_expr(compiler, block, next, &current);
        if (!cond) return compiler->result;
        
        Osl_Block *body;
		_osl_make_node(compiler, block, current, OSL_NODE_BLOCK, (void**)&body);
        body->is_procedural = true;
        body->parent = block;
        
        if (current->kind == OSL_TOKEN_KIND_LBRACE) {
        	_osl_parse_some(compiler, body, current+1, &current, OSL_TOKEN_KIND_RBRACE);
        	if (compiler->result != OSL_OK) return compiler->result;
        } else {
        	_osl_parse_one(compiler, body, current, &current);
        	if (compiler->result != OSL_OK) return compiler->result;
        }
        
        loop->condition = cond;
        loop->block = body;
        
        // Only add as a top node if condition is not 0 at compile time
        // todo(charlie) #memory #speed pop back node_arena position
        if (!((loop->condition->kind == OSL_EXPR_LITERAL_FLOAT || loop->condition->kind == OSL_EXPR_LITERAL_INT) && loop->condition->val.lit.lit_int == 0))
    		block->top_nodes[block->top_node_count++] = n;
        
    } else if (first->kind == OSL_TOKEN_KIND_IDENTIFIER && next->kind == OSL_TOKEN_KIND_DOUBLE_COLON) {
    	
    	Osl_Token *decl_kw = ++current;
    	
    	if (strings_match(_osl_token_text(compiler, decl_kw), STR("struct"))) {
    		if (!_osl_exp_token(compiler, ++current, OSL_TOKEN_KIND_LBRACE))
    			return compiler->result;
    		
    		Osl_Block *struct_block;
			_osl_make_node(compiler, block, current, OSL_NODE_BLOCK, (void**)&struct_block);
	        struct_block->is_procedural = false;
	        struct_block->parent = block;
	        
	        
	        _osl_parse_some(compiler, struct_block, current+1, &current, OSL_TOKEN_KIND_RBRACE);
        	if (compiler->result != OSL_OK) return compiler->result;
        	
    		Osl_Struct_Decl *struct_decl;
			_osl_make_node(compiler, block, current, OSL_NODE_STRUCT_DECL, (void**)&struct_decl);
        	
	        struct_decl->ident = _osl_token_text(compiler, first);
	        struct_decl->block = struct_block;
	        
	        for (u64 i = 0; i < compiler->struct_node_count; i += 1) {
		    	Osl_Struct_Decl *decl = compiler->struct_decls[i];
		    	if (strings_match(decl->ident, struct_decl->ident)) {
		    		string a = _osl_tprint_token(compiler, _osl_get_node(struct_decl)->first_token, STR("Redefinition of type name ..."));
		    		string b = _osl_tprint_token(compiler, _osl_get_node(decl)->first_token, STR("... Previous definition was here"));
		    		compiler->err_log = tprint("%s%s", a, b);
		    		return compiler->result = OSL_TYPE_REDEFINITION;
		    	}
		    }
	        
        	arena_push_copy(&compiler->struct_decls_arena, &struct_decl, sizeof(void*));
        	compiler->struct_node_count += 1;
        	
    	} else {
    		compiler->err_log = _osl_tprint_token(compiler, decl_kw, STR("Unexpected token. Expected a static declaration keyword."));
    		return compiler->result = OSL_UNEXPECTED_TOKEN;
    	}
    	
    } else if (first->kind == OSL_TOKEN_KIND_IDENTIFIER && next->kind == ':') {
		
		Osl_Value_Decl *decl;
		_osl_make_node(compiler, block, first, OSL_NODE_VALUE_DECL, (void**)&decl);
		
        decl->ident = (string) { first->length, compiler->source.data+first->source_pos };
        
        Osl_Token *prev_defined_token = 0;
        for (u64 j = 0; j < block->node_count-1; j += 1) {
			Osl_Node *node = block->nodes[j];
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
			return compiler->result;
		}
        
        Osl_Token *type_token = ++current;
        
        Osl_Result type_res = _osl_parse_type_ident(compiler, block, type_token, &current, &decl->type_ident);
        if (type_res != OSL_OK) return compiler->result;
        
        next = current;
         
        if (next->kind == '$') {
        	
        	Osl_Token *deco_token = ++current;
        	
            if (!_osl_exp_token(compiler, deco_token, OSL_TOKEN_KIND_IDENTIFIER))
            	return compiler->result;
        	
			string decoration_string = (string) { deco_token->length, compiler->source.data+deco_token->source_pos };
        	
        	if ((compiler->program_kind == OSL_PROGRAM_GPU_VERTEX
    		   || compiler->program_kind == OSL_PROGRAM_GPU_FRAGMENT)
    		   && strings_match(decoration_string, STR("Input"))) {
        		decl->storage_class = OSL_STORAGE_INPUT;
        		Osl_Result res = _osl_parse_arg_list(compiler, block, OSL_TOKEN_KIND_RPAREN, ++current, &current, &decl->storage_args);
				if (res != OSL_OK) return compiler->result;
				if (decl->storage_args.arg_count != 1) {
					compiler->err_log = _osl_tprint_token(compiler, deco_token, tprint("Expected exactly 1 integer argument, but got %i", decl->storage_args.arg_count));
					compiler->result = OSL_BAD_DECORATION_ARGUMENTS;
					return compiler->result;
				}
        	} else if ((compiler->program_kind == OSL_PROGRAM_GPU_VERTEX
        		   || compiler->program_kind == OSL_PROGRAM_GPU_FRAGMENT)
        		   && strings_match(decoration_string, STR("Output"))) {
        		decl->storage_class = OSL_STORAGE_OUTPUT;
        		Osl_Result res = _osl_parse_arg_list(compiler, block, OSL_TOKEN_KIND_RPAREN, ++current, &current, &decl->storage_args);
				if (res != OSL_OK) return compiler->result;
				if (decl->storage_args.arg_count != 1) {
					compiler->err_log = _osl_tprint_token(compiler, deco_token, tprint("Expected exactly 1 integer argument, but got %i", decl->storage_args.arg_count));
					compiler->result = OSL_BAD_DECORATION_ARGUMENTS;
					return compiler->result;
				}
        	} else if ((compiler->program_kind == OSL_PROGRAM_GPU_VERTEX
        		   || compiler->program_kind == OSL_PROGRAM_GPU_FRAGMENT)
        		   && strings_match(decoration_string, STR("UniformBinding"))) {
        		decl->storage_class = OSL_STORAGE_BINDING;
        		Osl_Result res = _osl_parse_arg_list(compiler, block, OSL_TOKEN_KIND_RPAREN, ++current, &current, &decl->storage_args);
				if (res != OSL_OK) return compiler->result;
				if (decl->storage_args.arg_count != 1) {
					compiler->err_log = _osl_tprint_token(compiler, deco_token, tprint("Expected exactly 1 integer argument, but got %i", decl->storage_args.arg_count));
					compiler->result = OSL_BAD_DECORATION_ARGUMENTS;
					return compiler->result;
				}
        	} else if ((compiler->program_kind == OSL_PROGRAM_GPU_VERTEX
        		   || compiler->program_kind == OSL_PROGRAM_GPU_FRAGMENT)
        		   && (strings_match(decoration_string, STR("VertexPosition")))) {
        		decl->builtin_kind = OSL_BUILTIN_VERTEX_POSITION;
        		if (compiler->program_kind == OSL_PROGRAM_GPU_VERTEX) {
        			decl->storage_class = OSL_STORAGE_OUTPUT;
        		} else if (compiler->program_kind == OSL_PROGRAM_GPU_FRAGMENT) {
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
        	} else if (compiler->program_kind == OSL_PROGRAM_GPU_FRAGMENT && strings_match(decoration_string, STR("PixelCoord"))) {
        		decl->builtin_kind = OSL_BUILTIN_PIXEL_COORD;
        		decl->storage_class = OSL_STORAGE_INPUT;
        		current += 1;
        	} else {
        		compiler->err_log = _osl_tprint_token(compiler, deco_token, STR("Invalid declaration class token"));
        		compiler->result = OSL_BAD_DECL_CLASS;
        		return compiler->result;
        	}
        	
        	
        	next = current;
        }
     	if (next->kind == '=') {
        	decl->init_expr = _osl_parse_expr(compiler, block, next+1, &current);
        	if (!decl->init_expr)
        		return compiler->result;
        }	
        
        if (!_osl_exp_token(compiler, current++, (Osl_Token_Kind)';')) {
        	string a = _osl_tprint_token(compiler, current-2, STR("... Expected a semi-colon after this token"));
        	compiler->err_log = tprint("%s%s", compiler->err_log, a);
        	return compiler->result;
        }
        	
        decl->vnum = compiler->next_vnum++;
        
        block->top_nodes[block->top_node_count++] = _osl_get_node(decl);
       
	} else if (_osl_can_be_start_of_expr(first)) {
		if (!block->is_procedural) {
			string a = _osl_tprint_token(compiler, first, STR("This looks like the start of an expression, but it appears in a non-procedural block where procedural statements are not allowed ..."));
			string b = _osl_tprint_token(compiler, _osl_get_node(block)->first_token, STR("... This is where the current procedural block starts"));
			compiler->err_log = tprint("%s%s", a, b);
			return compiler->result = OSL_PROCEDURAL_STATEMENT_IN_NON_PROCEDURAL_BLOCK;
		
		}
		Osl_Expr *expr = _osl_parse_expr(compiler, block, first, &current);
        if (!expr) {
        	return compiler->result;
        }
        if (!_osl_exp_token(compiler, current++, OSL_TOKEN_KIND_SEMICOLON)) {
        	string a = _osl_tprint_token(compiler, current-2, STR("Expected a semi-colon after this token"));
        	compiler->err_log = tprint("%s%s", compiler->err_log, a);
        	return compiler->result;
        }
        block->top_nodes[block->top_node_count++] = _osl_get_node(expr);
	} else if (first->kind == OSL_TOKEN_KIND_IDENTIFIER && (first+1)->kind == OSL_TOKEN_KIND_IDENTIFIER && ((first+2)->kind == ';' || (first+2)->kind == '=')) {
    	compiler->err_log = _osl_tprint_token(compiler, first, STR("This looks like a C-style value declaration. But this is not C. Variable are declared like: `var: Type;`"));
        return compiler->result =  OSL_UNEXPECTED_TOKEN;
	} else {
		
		string s = block->is_procedural ? STR("procedural") : STR("non-procedural");
    	compiler->err_log = _osl_tprint_token(compiler, first, tprint("Unable to infer intent with this token in %s block", s));
        return compiler->result =  OSL_UNEXPECTED_TOKEN;
    }
    
    *done_token = current;
    return OSL_OK;
}

unit_local Osl_Result _osl_parse_some(Osl_Compiler *compiler, Osl_Block *block, Osl_Token *start, Osl_Token **done_token, Osl_Token_Kind end_token) {
	*done_token = start;
    while ((*done_token)->kind != end_token) {
    	_osl_parse_one(compiler, block, *done_token, done_token);
    	if (compiler->result != OSL_OK) return compiler->result;
    }
    *done_token += 1;
    return compiler->result;
}

unit_local void _osl_done_compiler(Osl_Compiler *compiler) {
	free_arena(compiler->token_arena);
	free_arena(compiler->node_arena);
	free_arena(compiler->struct_decls_arena);
}



Osl_Result osl_compile(Allocator a, Osl_Compile_Desc desc, void **pcode, u64 *pcode_size, string *err_log) {
    (void)a;
    (void)pcode;
    (void)pcode_size;
    Osl_Compiler *compiler = PushTemp(Osl_Compiler);
    *compiler = (Osl_Compiler){0};
    compiler->source = string_replace(get_temp(), desc.code_text, STR("\t"), STR(""));
    compiler->next_vnum = 1;
    compiler->program_kind = desc.program_kind;
    compiler->enabled_features = desc.enabled_features;
    compiler->target = desc.target;
    compiler->token_arena = make_arena(1024*1024*1024*69, 1024*100);
    compiler->tokens = (Osl_Token*)compiler->token_arena.start;
    compiler->node_arena = make_arena(1024*1024*1024*69, 1024*100);
    compiler->struct_decls_arena = make_arena(1024*1024*1024*69, 1024*100);
    compiler->struct_decls = (Osl_Struct_Decl**)compiler->struct_decls_arena.start;
    compiler->result = OSL_OK;
    compiler->top_block.is_procedural = true;
    
    _osl_tokenize(compiler);
    
    Osl_Token *_;
    
    Osl_Expr *true_expr;
    _osl_make_node(compiler, &compiler->top_block, compiler->tokens, OSL_NODE_EXPR, (void**)&true_expr);
    true_expr->kind = OSL_EXPR_LITERAL_INT;
    true_expr->val.lit.lit_int = 1;
    Osl_Expr *false_expr;
    _osl_make_node(compiler, &compiler->top_block, compiler->tokens, OSL_NODE_EXPR, (void**)&false_expr);
    false_expr->kind = OSL_EXPR_LITERAL_INT;
    false_expr->val.lit.lit_int = 0;
    
    Osl_Expr_Alias *stage_vertex_alias;
    Osl_Node *vnode = _osl_make_node(compiler, &compiler->top_block, compiler->tokens, OSL_NODE_EXPR_ALIAS, (void**)&stage_vertex_alias);
    stage_vertex_alias->ident = STR("STAGE_VERTEX");
    stage_vertex_alias->expr = false_expr;
    
    Osl_Expr_Alias *stage_fragment_alias;
    Osl_Node *fnode = _osl_make_node(compiler, &compiler->top_block, compiler->tokens, OSL_NODE_EXPR_ALIAS, (void**)&stage_fragment_alias);
    stage_fragment_alias->ident = STR("STAGE_FRAGMENT");
    stage_fragment_alias->expr = false_expr;
    
    Osl_Expr_Alias *stage_compute_alias;
    Osl_Node *cnode = _osl_make_node(compiler, &compiler->top_block, compiler->tokens, OSL_NODE_EXPR_ALIAS, (void**)&stage_compute_alias);
    stage_compute_alias->ident = STR("STAGE_COMPUTE");
    stage_compute_alias->expr = false_expr;
    
    switch (compiler->program_kind) {
	case OSL_PROGRAM_GPU_VERTEX: {
		stage_vertex_alias->expr = true_expr;
		break;
	}
	case OSL_PROGRAM_GPU_FRAGMENT: {
		stage_fragment_alias->expr = true_expr;
		break;
	}
	case OSL_PROGRAM_GPU_COMPUTE: {
		stage_compute_alias->expr = true_expr;
		break;
	}
	default: {
		assert(false);
		break;
	}
	}
	
	compiler->top_block.top_nodes[compiler->top_block.top_node_count++] = vnode;
	compiler->top_block.top_nodes[compiler->top_block.top_node_count++] = fnode;
	compiler->top_block.top_nodes[compiler->top_block.top_node_count++] = cnode;
    
    _osl_parse_some(compiler, &compiler->top_block, compiler->tokens, &_, OSL_TOKEN_KIND_EOF);
    
    if (compiler->result != OSL_OK) {
        if (err_log) *err_log = compiler->err_log;
    } else {
    
    	Spv_Converter *spv = PushTemp(Spv_Converter);
    	Osl_Result res = spv_init(spv, compiler, (u32)compiler->next_vnum);
    	if (res != OSL_OK) {
    		if (err_log) *err_log = compiler->err_log;
    		_osl_done_compiler(compiler);
    		_osl_done_spv(spv);
    		return res;
    	}
    	
    	for (u64 i = 0; i < compiler->top_block.top_node_count; i += 1) {
    		Osl_Node *n = compiler->top_block.top_nodes[i];
    		if (n->kind == OSL_NODE_VALUE_DECL && n->val.value_decl.storage_class != OSL_STORAGE_DEFAULT)
    			spv_emit_node(spv, &spv->const_block, n);    		
    		else
    			spv_emit_node(spv, &spv->entry_block, n); 
    			
    		if (compiler->result != OSL_OK) break;
    	} 
    	
		if (compiler->result == OSL_OK) {
	    	Spv_Block *block = spv_finalize(spv);
	    	*pcode_size = block->count;
	    	*pcode = allocate(a, block->count);
	    	memcpy(*pcode, block->data, (sys_uint)block->count);
		}
		_osl_done_spv(spv);
    }
    
    if (compiler->result != OSL_OK) {
        if (err_log) *err_log = compiler->err_log;
    }
    return compiler->result;
}

#endif // OSTD_IMPL


#endif // _OSL_COMPILER_H
