#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#pragma clang diagnostic ignored "-Wreserved-macro-identifier"
#pragma clang diagnostic ignored "-Wc11-extensions"
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wunused-function"
#ifdef _MSC_VER
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif
#endif

#define OSTD_IMPL
#define OSTD_NO_GRAPHICS
#include "../src/ostd.h"

#define MAX_IR_REGS 1024

unit_local u64 get_next_power_of_two(u64 x) {
	if (x == 0) {
		return 1;
	}
	
	x -= 1;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x |= x >> 32;
	
	return x + 1;
}

typedef enum Token_Kind {
	TOKEN_KIND_UNKNOWN,
	
	TOKEN_KIND_PUNCTUATION_START,
	
	TOKEN_KIND_COLON = ':',
	TOKEN_KIND_DOLLAR = '$',
	TOKEN_KIND_LPAREN = '(',
	TOKEN_KIND_RPAREN = ')',
	TOKEN_KIND_STAR = '*',
	TOKEN_KIND_DOT = '.',
	
	TOKEN_KIND_IDENTIFIER = 128,
	
	TOKEN_KIND_INT_LITERAL,
	TOKEN_KIND_FLOAT_LITERAL,
	
	TOKEN_KIND_EOF,
	
	TOKEN_KIND_PUNCTUATION_END = TOKEN_KIND_IDENTIFIER,
	
} Token_Kind;

unit_local inline string token_kind_str(Token_Kind kind) {
	switch (kind) {
		case TOKEN_KIND_IDENTIFIER: return STR("Identifier");
		case TOKEN_KIND_INT_LITERAL: return STR("Int Literal");
		case TOKEN_KIND_FLOAT_LITERAL: return STR("Float Literal");
		case TOKEN_KIND_COLON:  return STR(":");
		case TOKEN_KIND_DOLLAR: return STR("$");
		case TOKEN_KIND_LPAREN: return STR("(");
		case TOKEN_KIND_RPAREN: return STR(")");
		case TOKEN_KIND_STAR:   return STR("*");
		case TOKEN_KIND_DOT:    return STR(".");
		case TOKEN_KIND_EOF:    return STR("<eof>");
		case TOKEN_KIND_UNKNOWN: //fallthrough
		case TOKEN_KIND_PUNCTUATION_START: //fallthrough
		default: return STR("");
	}
	return STR("");
}

typedef struct Token {
	Token_Kind kind;	
	u64 source_pos;
	u64 length;
} Token;

typedef enum Type {
	TYPE_INVALID,
	TYPE_FLOAT32,
	TYPE_UINT32,
	TYPE_V3F32,
	TYPE_V4F32,
} Type;

typedef enum Storage_Flag {
	STORAGE_DEFAULT = 0,
	STORAGE_INPUT = 1 << 0,
	STORAGE_INPUT_SCALAR = 1 << 1,
	STORAGE_OUTPUT = 1 << 2,
} Storage_Flag;

struct Code_Expr;
typedef struct Code_Decl {
	Type type;
	string type_ident;
	Storage_Flag storage_flags;
	string ident;
	struct Code_Expr *init_expr;
} Code_Decl;

typedef enum Expr_Kind {
	EXPR_OP,
	EXPR_DECL,
	EXPR_LITERAL_FLOAT,
	EXPR_LITERAL_INT,
	EXPR_TYPE, // When casting
} Expr_Kind;

typedef enum Op_Kind {
	OP_INVALID = 0,
	OP_CAST,
	OP_MUL,
	OP_DIV,
	OP_ADD,
	OP_SUB,
	OP_SET,
} Op_Kind;

typedef struct Code_Expr {
	Expr_Kind kind;
	union {
		s64 decl_index;
		struct {  s64 op_result_reg; struct Code_Expr *lhs; struct Code_Expr *rhs; Op_Kind op; };
		struct { union { u64 lit_int; f32 lit_flt; }; s64 imm_index; };
		Type type;
	};
	Type cast_to_type;
	s64 read_reg;
} Code_Expr;


unit_local string source;

unit_local Token tokens[16384];
unit_local u64 token_count = 0;

unit_local Token *decl_tokens[1024];
unit_local u64 decl_token_count = 0;
unit_local Token *statement_tokens[1024];
unit_local u64 statement_token_count = 0;

unit_local Code_Decl decls[1024];
unit_local u64 decl_count = 0;

unit_local Code_Expr exprs[1024];
unit_local u64 expr_count = 0;

unit_local Code_Expr *statements[512];
unit_local u64 statement_count = 0;

unit_local u32 imm_u32s[1024];
unit_local u64 imm_u32_count;

unit_local Allocator ir_allocator;



typedef enum Instr {
	i_mov,
	i_movu,
	i_f32toi32,
	i_i32tof32,
	i_add,
	i_sub,
	i_mul,
	i_div,
	i_broadcast32_scalar,
	i_broadcast64_scalar,
} Instr;

unit_local string instr_avx_str(Instr i) {
	switch (i) {
		case i_mov:      return STR("vmovaps");
		case i_movu:      return STR("vmovups");
		case i_f32toi32: return STR("vcvtps2dq");
		case i_i32tof32: return STR("vcvtdq2ps");
		case i_add:      return STR("vaddps");
		case i_sub:      return STR("vsubps");
		case i_mul:      return STR("vmulps");
		case i_div:      return STR("vdivps");
		case i_broadcast32_scalar:      return STR("vbroadcastss");
		case i_broadcast64_scalar:      return STR("vbroadcastsd");
		default: break;
	}
	return STR("");
}
unit_local Type get_expr_type(Code_Expr *expr);
typedef enum Operand_Kind {
	o_reg,
	o_mem,
	o_builtin,
} Operand_Kind;

typedef enum Operand_Builtin {
	o_in_buffer,
	o_out_buffer
} Operand_Builtin;

typedef struct Operand {
	Operand_Kind kind;
	
	s64 reg;
	bool deref;
	Operand_Builtin builtin;
	u64 builtin_offset;
} Operand;

unit_local inline Operand op_reg(s64 reg) {
	assert(reg > -1);
	
	return (Operand) {o_reg, reg, false, 0, 0};
}
unit_local inline Operand op_deref(s64 reg) {
	assert(reg > -1);
	
	return (Operand) {o_mem, reg, true, 0, 0};
}
unit_local inline Operand op_builtin(Operand_Builtin b, u64 offset) {
	return (Operand) {o_builtin, -1, true, b, offset};
}

unit_local inline Operand noop(void) {
	return (Operand) {0, 0, false, 0, 0};
}

typedef struct IR_Instr {
	Instr i;
	Operand op0, op1, op2;
} IR_Instr;

struct IR_Program;
typedef struct IR_Block {
	struct IR_Program *prog;
	s64 base_vgpr;
	s64 base_sgpr;
	
	IR_Instr *instructions;
	u64 instruction_count;
	u64 instruction_allocated_count;
	
	u64 stack_size;
} IR_Block;

typedef struct IR_Immediate {
	u64 scalar_width;
	u64 scalars[8];
} IR_Immediate;

typedef struct IR_Program {
	
	u64 input_sizes[256];
	u64 input_count;
	u64 input_size_bytes;
	u64 output_sizes[256];
	u64 output_count;
	u64 output_size_bytes;
	
	IR_Immediate immediates[4096];
	u64 immediate_count;
	
	s64 base_vgpr;
	s64 base_sgpr;
	
	s64 output_regs[128];
	s64 input_regs[128];
	
	u64 reg_reference_counts[MAX_IR_REGS];
	
	
	IR_Block init_block;
	IR_Block exit_block;
	
	IR_Block blocks[1024];
	u64 block_count;
	
} IR_Program;

unit_local void ir_block_reserve(IR_Block *block, u64 required) {
	if (!block->instructions) {
		u64 nsize = max(sizeof(IR_Instr)*1024, sizeof(IR_Instr)*get_next_power_of_two(required));
		block->instructions = (IR_Instr*)allocate(ir_allocator, nsize);
		memset(block->instructions, 0, nsize);
		block->instruction_allocated_count = nsize/sizeof(IR_Instr);
		return;
	}
	
	if (block->instruction_allocated_count >= required) return;
	
	
	u64 nsize = sizeof(IR_Instr)*get_next_power_of_two(required);
	
	IR_Instr *new_buffer = (IR_Instr*)allocate(ir_allocator, nsize);
	memset(new_buffer, 0, nsize);
	memcpy(new_buffer, block->instructions, block->instruction_allocated_count*sizeof(IR_Instr));
	block->instructions = new_buffer;
	block->instruction_allocated_count = nsize/sizeof(IR_Instr);
	
}

unit_local void put_ir_instr_0(IR_Block *block, Instr instr) {
	ir_block_reserve(block, block->instruction_count+1);
	block->instructions[block->instruction_count++] = (IR_Instr) {instr, noop(), noop(), noop() };
}
unit_local void put_ir_instr_1(IR_Block *block, Instr instr, Operand op0) {
	ir_block_reserve(block, block->instruction_count+1);
	if (op0.reg >= 0 && op0.reg <= MAX_IR_REGS) block->prog->reg_reference_counts[op0.reg]++;
	block->instructions[block->instruction_count++] = (IR_Instr) {instr, op0, noop(), noop() };
}
unit_local void put_ir_instr_2(IR_Block *block, Instr instr, Operand op0, Operand op1) {
	ir_block_reserve(block, block->instruction_count+1);
	if (op0.reg >= 0 && op0.reg <= MAX_IR_REGS) block->prog->reg_reference_counts[op0.reg]++;
	if (op1.reg >= 0 && op1.reg <= MAX_IR_REGS) block->prog->reg_reference_counts[op1.reg]++;
	block->instructions[block->instruction_count++] = (IR_Instr) {instr, op0, op1, noop() };
}
unit_local void put_ir_instr_3(IR_Block *block, Instr instr, Operand op0, Operand op1, Operand op2) {
	ir_block_reserve(block, block->instruction_count+1);
	if (op0.reg >= 0 && op0.reg <= MAX_IR_REGS) block->prog->reg_reference_counts[op0.reg]++;
	if (op1.reg >= 0 && op1.reg <= MAX_IR_REGS) block->prog->reg_reference_counts[op1.reg]++;
	if (op2.reg >= 0 && op2.reg <= MAX_IR_REGS) block->prog->reg_reference_counts[op2.reg]++;
	block->instructions[block->instruction_count++] = (IR_Instr) {instr, op0, op1, op2 };
}

unit_local void put_ir_header(IR_Program *prog) {
	
	prog->input_size_bytes = 0;
	prog->output_size_bytes = 0;
	
	prog->input_count = 0;
	prog->output_count = 0;
	
	for (u64 i = 0; i < decl_count; i += 1) {
		Code_Decl *decl = &decls[i];
		
		switch (decl->type) {
			
			case TYPE_UINT32: // fallthrough
			case TYPE_FLOAT32:
				if (decl->storage_flags & STORAGE_INPUT) {
					prog->input_size_bytes += 32;
					prog->input_regs[prog->input_count] = prog->base_vgpr++;
					prog->input_sizes[prog->input_count++] = 32;
				}
				if (decl->storage_flags & STORAGE_INPUT_SCALAR) {
					prog->input_size_bytes += 4;
					prog->input_regs[prog->input_count] = prog->base_vgpr++;
					prog->input_sizes[prog->input_count++] = 4;
				}
				if (decl->storage_flags & STORAGE_OUTPUT) {
					prog->output_size_bytes += 32;
					prog->output_regs[prog->output_count] = prog->base_vgpr++;
					prog->output_sizes[prog->output_count++] = 32;
				}
				break;
			
			case TYPE_INVALID: assert(false); break;
			default: assert(false); break;
		}
	}
	
	for (u32 i = 0; i < imm_u32_count; i += 1) {
		prog->immediates[prog->immediate_count++] = (IR_Immediate){
			4,
			{(u64)imm_u32s[i], (u64)imm_u32s[i], (u64)imm_u32s[i], (u64)imm_u32s[i], (u64)imm_u32s[i], (u64)imm_u32s[i], (u64)imm_u32s[i], (u64)imm_u32s[i]}
		};
	}
	
	prog->base_vgpr = 0;
	
	u64 offset = 0;
	u64 input_index = 0;
	for (u64 i = 0; i < decl_count; i += 1) {
		Code_Decl *decl = &decls[i];
		
		switch (decl->type) {
			
			case TYPE_UINT32: // fallthrough
			case TYPE_FLOAT32:
				if (decl->storage_flags & STORAGE_INPUT_SCALAR) {
					put_ir_instr_2(&prog->init_block, i_broadcast32_scalar, op_reg(prog->input_regs[input_index]), op_builtin(o_in_buffer, offset));
					
					offset += 4;
					input_index += 1;
				}
				if (decl->storage_flags & STORAGE_INPUT) {
					put_ir_instr_2(&prog->init_block, i_movu, op_reg(prog->input_regs[input_index]), op_builtin(o_in_buffer, offset));
					offset += 32;
					input_index += 1;
				}
				break;
			
			case TYPE_INVALID: assert(false); break;
			default: assert(false); break;
		}
	}
}

unit_local void put_ir_op(IR_Block *block, Code_Expr *op_expr) {
	assert(op_expr->kind == EXPR_OP);
	if (op_expr->op == OP_SET && op_expr->lhs->kind == EXPR_DECL && op_expr->lhs->read_reg == op_expr->rhs->read_reg)
		return;
	
	Code_Expr *lexpr = op_expr->lhs;
	Code_Expr *rexpr = op_expr->rhs;
	Op_Kind op = op_expr->op;
	
	Instr i = 0;
	
	switch (op) {
		case OP_CAST: 
			Type ltype = get_expr_type(lexpr);
			
			assert(ltype != TYPE_INVALID);
			
			switch (ltype) {
				case TYPE_FLOAT32: switch (rexpr->type) {
					case TYPE_FLOAT32: return; 
					case TYPE_UINT32:  i = i_f32toi32; break;
					case TYPE_INVALID: assert(false); break; 
					default: assert(false); break; 
				} break;
				case TYPE_UINT32: switch (rexpr->type) {
					case TYPE_FLOAT32: i = i_i32tof32; break; 
					case TYPE_UINT32:  return;
					case TYPE_INVALID: assert(false); break; 
					default: assert(false); break; 
				} break;
				case TYPE_INVALID: assert(false); break; 
				default: assert(false); break; 
			}
			 
			break;
		case OP_MUL:  i = i_mul; break;
		case OP_DIV:  i = i_div; break;
		case OP_ADD:  i = i_add; break;
		case OP_SUB:  i = i_sub; break;
		case OP_SET:  i = i_mov; break;
		
		case OP_INVALID: break;
		default: assert(false); break;
	}
	
	
	switch (i) {
		case i_broadcast32_scalar: 
		case i_broadcast64_scalar: 
		case i_mov: 
		case i_movu: 
			put_ir_instr_2(block, i, op_reg(lexpr->read_reg), op_reg(rexpr->read_reg)); break;
		case i_f32toi32: // fallthrough
		case i_i32tof32:  {
			s64 out_reg = 15;
			if (op_expr->op_result_reg > -1) out_reg = op_expr->op_result_reg;
			put_ir_instr_2(block, i, op_reg(out_reg), op_reg(lexpr->read_reg)); 
			op_expr->op_result_reg = out_reg;
			if (op_expr->read_reg == -1) op_expr->read_reg = out_reg;
			break;
		}
		case i_add: // fallthrough
		case i_sub: // fallthrough
		case i_mul: // fallthrough
		case i_div: {
			s64 out_reg = 15;
			if (op_expr->op_result_reg > -1) out_reg = op_expr->op_result_reg;
			put_ir_instr_3(block, i, op_reg(out_reg), op_reg(lexpr->read_reg), op_reg(rexpr->read_reg)); 
			op_expr->op_result_reg = out_reg;
			if (op_expr->read_reg == -1) op_expr->read_reg = out_reg;
			break;
		}
		default: break;
	}
}
unit_local void put_ir_expr(IR_Block *block, struct Code_Expr *expr)
{
	if (!expr) {
		return;
	}
	
	switch (expr->kind) {
	case EXPR_OP:
	
		if (expr->op == OP_SET && expr->rhs->kind == EXPR_OP &&  expr->lhs->kind == EXPR_DECL) {
			expr->rhs->op_result_reg = expr->lhs->read_reg;
		}
		
		if (expr->read_reg == -1) expr->read_reg = expr->op_result_reg;
		
		put_ir_expr(block, expr->lhs);
		put_ir_expr(block, expr->rhs);
		
		put_ir_op(block, expr);
		break;

	case EXPR_DECL:
	
	
		break;

	case EXPR_LITERAL_FLOAT:
	case EXPR_LITERAL_INT:
		expr->read_reg = MAX_IR_REGS+expr->imm_index;
		break;
	case EXPR_TYPE:
		break;
		
	default: assert(false); break;
	}
}


unit_local void put_ir_footer(IR_Program *prog) {

	s64 r = 0;
	u64 offset = 0;
	for (u64 i = 0; i < decl_count; i += 1) {
		Code_Decl *decl = &decls[i];
		
		switch (decl->type) {
			
			case TYPE_UINT32: // fallthrough
			case TYPE_FLOAT32:
				if (decl->storage_flags & STORAGE_OUTPUT) {
					put_ir_instr_2(&prog->exit_block, i_mov, op_builtin(o_out_buffer, offset), op_reg(prog->output_regs[r]));
					r += 1;
					offset += 32;
				}
				break;
			
			case TYPE_INVALID: assert(false); break;
			default: assert(false); break;
		}
	}
}

typedef struct Text_X64_Reg_State {
	s64 ir_reg_current;
	bool locked;
} Text_X64_Reg_State;
typedef struct Text_X64_Emitter {
	IR_Program *ir;
	File_Handle file;
	
	Text_X64_Reg_State regs[15];
	s64 ir_reg_stack[MAX_IR_REGS];
	u64 ir_reg_stack_offsets[MAX_IR_REGS];
	u64 ir_reg_stack_count;
	
	u64 reg_reference_counts[MAX_IR_REGS];
	
	u64 stack_position;
} Text_X64_Emitter;

unit_local void text_x64_lock_reg(Text_X64_Emitter *x64, s64 x64_reg) {
	x64->regs[x64_reg].locked = true;
}
unit_local void text_x64_unlock_reg(Text_X64_Emitter *x64, s64 x64_reg) {
	x64->regs[x64_reg].locked = false;
}

unit_local s64 text_x64_get_or_allocate_reg(Text_X64_Emitter *x64, s64 ir_reg, Text_X64_Reg_State **result) {
	assert(ir_reg > -1);
	u64 reg_count = sizeof(x64->regs)/sizeof(x64->regs[0]);
	
	// First, see if the ir reg is loaded in an actual reg
	for (u64 i = 0; i < reg_count; i += 1) {
		if (x64->regs[i].ir_reg_current == ir_reg) {
			if (result) *result = &x64->regs[ir_reg];
			return (s64)i;
		}
	}
	
	// Then, see if the ir_reg is currently spilled to the stack, and in that case swap a
	// reg value with the spilled stack value
	for (u64 j = 0; j < x64->ir_reg_stack_count; j += 1) {
		if (x64->ir_reg_stack[j] == ir_reg) {
			for (u64 i = 0; i < reg_count; i += 1) {
				Text_X64_Reg_State *reg = &x64->regs[i];
				if (reg->locked) continue;
				
				if (reg->ir_reg_current == -1) {
					fprint(x64->file, "\n; stack $%u -> ymm%u\n", ir_reg, i);
					if (x64->ir_reg_stack_offsets[j]) 
						fprint(x64->file, "add rbx, %u\n", x64->ir_reg_stack_offsets[j]);
					fprint(x64->file, "vmovdqu ymm%u, ymmword ptr [rbx]\n", i);
					if (x64->ir_reg_stack_offsets[j]) 
						fprint(x64->file, "sub rbx, %u\n", x64->ir_reg_stack_offsets[j]);
					return (s64)i;
				} else {
					fprint(x64->file, "\n; stack $%u -> ymm%u | $%u -> stack \n", ir_reg, i, reg->ir_reg_current);
					if (x64->ir_reg_stack_offsets[j]) 
						fprint(x64->file, "add rbx, %u\n", x64->ir_reg_stack_offsets[j]);
					fprint(x64->file, "vmovdqu ymm15, ymmword ptr [rbx]\n");
					fprint(x64->file, "vmovdqu ymmword ptr [rbx], ymm%u\n", i);
					if (x64->ir_reg_stack_offsets[j]) 
						fprint(x64->file, "sub rbx, %u\n", x64->ir_reg_stack_offsets[j]);
					fprint(x64->file, "\n");
					
					Swap(reg->ir_reg_current, x64->ir_reg_stack[j]);
					if (result) *result = &x64->regs[i];
					reg->ir_reg_current = ir_reg;
					return (s64)i;
				}
			}
		}
	}
	
	// Lastly, spill a reg to the stack
	s64 reg_index = -1;
	for (u64 i = 0; i < reg_count; i += 1) {
		if (x64->regs[i].ir_reg_current == -1) {
			reg_index = (s64)i;
			break;
		}
	}
	
	if (reg_index == -1) {
		for (u64 i = 0; i < reg_count; i += 1) {
			if (x64->regs[i].locked == false) {
				reg_index = (s64)i;
				break;
			}
		}
	}
	
	assert(reg_index != -1);
	
	Text_X64_Reg_State *reg = &x64->regs[reg_index];
	
	if (reg->ir_reg_current != -1) {
		x64->ir_reg_stack_offsets[x64->ir_reg_stack_count] = x64->stack_position;
		x64->ir_reg_stack[x64->ir_reg_stack_count++] = reg->ir_reg_current;
		fprint(x64->file, "\n; ymm%u $%u -> stack | $%u -> ymm%u\n", reg_index, reg->ir_reg_current, ir_reg, reg_index);
		fprint(x64->file, "add rbx, %u\n", x64->stack_position);
		fprint(x64->file, "vmovdqu ymmword ptr [rbx], ymm%u\n", reg_index);
		fprint(x64->file, "sub rbx, %u\n\n", x64->stack_position);
		x64->stack_position += 32;
	}
	
	reg->ir_reg_current = ir_reg;
	if (result) *result = &x64->regs[reg_index];
	return reg_index;
}

unit_local void text_x64_free_reg(Text_X64_Emitter *x64, s64 ir_reg) {
	u64 reg_count = sizeof(x64->regs)/sizeof(x64->regs[0]);
	// First, see if the ir reg is loaded in an actual reg, and free it
	for (u64 i = 0; i < reg_count; i += 1) {
		if (x64->regs[i].ir_reg_current == ir_reg) {
			x64->regs[i].ir_reg_current = -1;
		}
	}
	
	
	for (u64 i = 0; i < reg_count; i += 1) {
		for (u64 j = 0; j < x64->ir_reg_stack_count; j += 1) {
			if (x64->ir_reg_stack[j] == ir_reg) {
				x64->ir_reg_stack[j] = -1;
			}
		}
	}
	
	fprint(x64->file, "\n; Free $%u\n\n", ir_reg);
}

unit_local string text_x64_format_op(Text_X64_Emitter *x64, Operand op, s64 i, Text_X64_Reg_State **result) {
	string sop = STR("");
	switch (op.kind) {
		case o_reg: {
			s64 x64_op = op.reg < MAX_IR_REGS ? text_x64_get_or_allocate_reg(x64, op.reg, result) : 0;
			sop = (op.reg < MAX_IR_REGS ? tprint("ymm%u", x64_op) : tprint("i%u", i));
			break;
		}
		case o_mem: {
			s64 x64_op = text_x64_get_or_allocate_reg(x64, op.reg, result);
			sop = tprint("[ymm%u]", x64_op);
			break;
		}
		case o_builtin:
			switch(op.builtin) {
			
				case o_in_buffer:
					sop = tprint("in_buffer[%u]", op.builtin_offset);
					break;
				case o_out_buffer:
					sop = tprint("out_buffer[%u]", op.builtin_offset);
					break;
				
				default: assert(false);
			}
		
			break;
		default: assert(false);
	}
	return sop;
}
unit_local void emit_text_x64_block(Text_X64_Emitter *x64, IR_Block *block) {
	
	if (block->stack_size > 0) {
		fprint(x64->file, "\npush rbp\n");
		fprint(x64->file, "mov rbp, rsp\n");
		u64 sz = get_next_power_of_two(block->stack_size);
		fprint(x64->file, "sub rsp, %u\n", sz);
		fprint(x64->file, "mov rbx, rsp\n\n");
	}
	
	for (u64 i = 0; i < block->instruction_count; i += 1) {
		IR_Instr instr = block->instructions[i];
		
		Operand op0 = instr.op0;
		Operand op1 = instr.op1;
		Operand op2 = instr.op2;
		s64 i0 = op0.reg-MAX_IR_REGS;
		s64 i1 = op1.reg-MAX_IR_REGS;
		s64 i2 = op2.reg-MAX_IR_REGS;
		Text_X64_Reg_State *reg0 = 0, *reg1 = 0, *reg2 = 0;
		string sop0 = text_x64_format_op(x64, op0, i0, &reg0);
		if (reg0) reg0->locked = true;
		string sop1 = text_x64_format_op(x64, op1, i1, &reg1);
		if (reg1) reg1->locked = true;
		string sop2 = text_x64_format_op(x64, op2, i2, &reg2);
		if (reg2) reg2->locked = true;
		string istr = instr_avx_str(instr.i);
		
		switch (instr.i) {
			case i_f32toi32: // fallthrough
			case i_i32tof32: // fallthrough
			case i_movu: // fallthrough
			case i_mov:
				fprint(x64->file, "; %s $%i, $%i\n", istr, op0.reg, op1.reg);
				fprint(x64->file, "%s %s, %s", istr, sop0, sop1);
				break;
			case i_add: // fallthrough
			case i_sub: // fallthrough
			case i_mul: // fallthrough
			case i_div:
				fprint(x64->file, "; %s $%i, $%i, $%i\n", istr, op0.reg, op1.reg, op2.reg);
				fprint(x64->file, "%s %s, %s, %s", istr, sop0, sop1, sop2);
				break;
			case i_broadcast32_scalar: 
				fprint(x64->file, "mov eax, %s\n", sop1);
				fprint(x64->file, "vmovd xmm0, eax\n");
				fprint(x64->file, "%s %s, xmm0", istr, sop0);
				break;
			case i_broadcast64_scalar:
				fprint(x64->file, "mov rax, %s\n", sop1);
				fprint(x64->file, "vmovq %s, rax\n", sop0);
				fprint(x64->file, "%s %s, %s", istr, sop0, sop0);
				break;
				
			default: assert(false); break;
		}
		
		if (reg0) reg0->locked = false;
		if (reg1) reg1->locked = false;
		if (reg2) reg2->locked = false;
		
		if (reg0) {
			x64->reg_reference_counts[reg0->ir_reg_current]++;
			if (x64->reg_reference_counts[reg0->ir_reg_current] >= x64->ir->reg_reference_counts[reg0->ir_reg_current]) {
				text_x64_free_reg(x64, reg0->ir_reg_current);
			}
		}
		if (reg1) {
			x64->reg_reference_counts[reg1->ir_reg_current]++;
			if (x64->reg_reference_counts[reg1->ir_reg_current] >= x64->ir->reg_reference_counts[reg1->ir_reg_current]) {
				text_x64_free_reg(x64, reg1->ir_reg_current);
			}
			x64->reg_reference_counts[reg1->ir_reg_current]++;
		}
		if (reg2) {
			x64->reg_reference_counts[reg2->ir_reg_current]++;
			if (x64->reg_reference_counts[reg2->ir_reg_current] >= x64->ir->reg_reference_counts[reg2->ir_reg_current]) {
				text_x64_free_reg(x64, reg2->ir_reg_current);
			}
			x64->reg_reference_counts[reg2->ir_reg_current]++;
		}
		
		fprint(x64->file, "\n");
	}
	
	if (block->stack_size > 0) {
		//fprint(x64->file, "\nmov rsp, rbp\n");
		//fprint(x64->file, "pop rbp\n\n");
	}
}

unit_local void emit_text_x64_header(Text_X64_Emitter *x64) {
	fprint(x64->file, ".data\n");
	
	for (u64 i = 0; i < x64->ir->immediate_count; i += 1) {
		IR_Immediate im = x64->ir->immediates[i];
		
		fprint(x64->file, "ALIGN 8\n");
		
		if (im.scalar_width == 1) {
			fprint(x64->file, "i%u db ", i);
			for (u64 j = 0; j < 8; j += 1) {
				u64 scu8 = (u8)(im.scalars[j]);
				if (j != 7) fprint(x64->file, "%u, ", scu8);
				else fprint(x64->file, "%u\n", scu8);
			}
		} else if (im.scalar_width == 2) {
			fprint(x64->file, "i%u dw ", i);
			for (u64 j = 0; j < 8; j += 1) {
				u64 scu16 = (u16)(im.scalars[j]);
				if (j != 7) fprint(x64->file, "%u, ", scu16);
				else fprint(x64->file, "%u\n", scu16);
			}
		} else if (im.scalar_width == 4) {
			fprint(x64->file, "i%u dd ", i);
			for (u64 j = 0; j < 8; j += 1) {
				u64 scu32 = (u32)(im.scalars[j]);
				if (j != 7) fprint(x64->file, "%u, ", scu32);
				else fprint(x64->file, "%u\n", scu32);
			}
		} else if (im.scalar_width == 8) {
			fprint(x64->file, "i%u dq ", i);
			for (u64 j = 0; j < 8; j += 1) {
				u64 scu64 = (u64)(im.scalars[j]);
				if (j != 7) fprint(x64->file, "%u, ", scu64);
				else fprint(x64->file, "%u\n", scu64);
			}
			
		} else assert(false);
	}
	
	
	fprint(x64->file, "PUBLIC out_buffer\n");
	fprint(x64->file, "PUBLIC in_buffer\n");
	fprint(x64->file, "out_buffer DD %u DUP(0)\n", x64->ir->output_size_bytes);
	fprint(x64->file, "in_buffer DD %u DUP(0)\n", x64->ir->input_size_bytes);
	
	fprint(x64->file, "\n");
	
	fprint(x64->file, ".code\n");
	fprint(x64->file, "PUBLIC GO\n");
	fprint(x64->file, "GO PROC EXPORT\n");
	
	fprint(x64->file, "\n");
	
	emit_text_x64_block(x64, &x64->ir->init_block);
	
	fprint(x64->file, "\n");
}

unit_local void emit_text_x64_footer(Text_X64_Emitter *x64) {
	fprint(x64->file, "\n");
	
	emit_text_x64_block(x64, &x64->ir->exit_block);

	// todo(charlie) move this to end of blocks, and restore registers before
	fprint(x64->file, "\nmov rsp, rbp\n");
	fprint(x64->file, "pop rbp\n\n");

	fprint(x64->file, "\nGO ENDP\n");
	fprint(x64->file, "DllMain PROC hinstDLL:QWORD, fdwReason:QWORD, lpReserved:QWORD\n");
	fprint(x64->file, "mov  eax, 1\n");
	fprint(x64->file, "ret\n");
	fprint(x64->file, "DllMain ENDP\n");
	fprint(x64->file, "END");
}

typedef struct Spirv_Emitter {
	IR_Program *ir;
	File_Handle file;
} Spirv_Emitter;

struct Code_Expr;
unit_local void emit_expr(struct Code_Expr *expr);
unit_local void emit_op(struct Code_Expr *op_expr);

unit_local void emit_header_x64(void);
unit_local void emit_footer(void);

unit_local Type get_expr_type(Code_Expr *expr) {
	switch (expr->kind) {
		case EXPR_OP:
			Type ltype = get_expr_type(expr->lhs);
			if (expr->rhs->kind == EXPR_TYPE && expr->op == OP_CAST) {
				ltype = expr->rhs->type;
			} else {
				assert(ltype == get_expr_type(expr->rhs));
			}
			return ltype;
		case EXPR_DECL: return decls[expr->decl_index].type;
		case EXPR_LITERAL_INT: return TYPE_UINT32;
		case EXPR_LITERAL_FLOAT: return TYPE_FLOAT32;
		case EXPR_TYPE: return TYPE_INVALID;
		default: return TYPE_INVALID;
	}
}

unit_local string tprint_token(Token *token, string message) {
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

unit_local Code_Expr *parse_one_expr(Token *expr_start, Token **next, Op_Kind left_op) {
	Code_Expr *expr = &exprs[expr_count++];
	*expr = (Code_Expr){0};
	expr->read_reg = -1;
	expr->imm_index = -1;
	expr->decl_index= -1;
	string expr_ident = (string) { expr_start->length, source.data+expr_start->source_pos };
	if (expr_start->kind == TOKEN_KIND_IDENTIFIER) {
		expr->kind = EXPR_DECL;
		for (u64 j = 0; j < decl_count; j += 1) {
			if (strings_match(expr_ident, decls[j].ident)) {
				expr->decl_index = (s64)j;
				expr->read_reg = expr->decl_index;
				break;
			}
		}
		
		if (expr->decl_index == -1) {
			bool is_type = false;
			if (left_op == OP_CAST) {
				string type_ident = (string) {expr_start->length, source.data+expr_start->source_pos};
				if (strings_match(type_ident, STR("u32"))) {
					expr->type = TYPE_UINT32;
					is_type = true;
				} else if (strings_match(type_ident, STR("f32"))) {
					expr->type = TYPE_FLOAT32;
					is_type = true;
				}
			}
			
			if (!is_type) {
				log(0, "Could not find declaration for '%s' used in an expression", expr_ident);
				return 0;
			} else {
				expr->kind = EXPR_TYPE;
			}
		}
	} else if (expr_start->kind == TOKEN_KIND_FLOAT_LITERAL) {
		expr->kind = EXPR_LITERAL_FLOAT;
		bool conv_ok;
		expr->lit_flt = (f32)string_to_float(expr_ident, &conv_ok);
		assert(conv_ok);
		for (s64 i = 0; i < (s64)imm_u32_count; i += 1) {
			if (imm_u32s[i] == (u32)expr->lit_int) {
				expr->imm_index = i;
				break;
			}
		}
		if (expr->imm_index == -1) {
			expr->imm_index = (s64)imm_u32_count;
			imm_u32s[imm_u32_count++] = (u32)expr->lit_int;
		}
	} else if (expr_start->kind == TOKEN_KIND_INT_LITERAL) {
		expr->kind = EXPR_LITERAL_INT;
		bool conv_ok;
		expr->lit_int = string_to_unsigned_int(expr_ident, 10, &conv_ok);
		for (s64 i = 0; i < (s64)imm_u32_count; i += 1) {
			if (imm_u32s[i] == (u32)expr->lit_int) {
				expr->imm_index = i;
				break;
			}
		}
		if (expr->imm_index == -1) {
			expr->imm_index = (s64)imm_u32_count;
			imm_u32s[imm_u32_count++] = (u32)expr->lit_int;
		}
		
		assert(conv_ok);
	}
	*next = expr_start+1;
	
	return expr;
}
unit_local Code_Expr *parse_expr_rec(Token *expr_start, Token **next, Op_Kind left_op) {

	Token *op_token = expr_start+1;
	
	if (op_token->kind == ';') {
		return parse_one_expr(expr_start, next, left_op);
	}

	Op_Kind rop;
	if (op_token->kind == '+') rop = OP_ADD;
	else if (op_token->kind == '-') rop = OP_SUB;
	else if (op_token->kind == '*') rop = OP_MUL;
	else if (op_token->kind == '/') rop = OP_DIV;
	else if (op_token->kind == '=') rop = OP_SET;
	else if (op_token->kind == '.') rop = OP_CAST;
	else {
		string msg = tprint_token(op_token, STR("Bad operator"));
		logs(0, msg);
		return 0;
	}
	
	
	
	if (left_op < rop) {
		Code_Expr *expr = parse_one_expr(expr_start, next, left_op);
		return expr;
	} else {
		Code_Expr *lexpr = parse_one_expr(expr_start, next, left_op);
		Code_Expr *rexpr = parse_expr_rec(op_token+1, next, rop);
		
		if (!lexpr || !rexpr) 
			return 0;
		
		Code_Expr *parent_op = &exprs[expr_count++];
		parent_op->read_reg = -1;
		parent_op->imm_index = -1;
		parent_op->decl_index = -1;
		parent_op->kind = EXPR_OP;
		parent_op->op = rop;
		
		if (lexpr->kind != EXPR_DECL && rop == OP_SET) {
			log(0, "Trying to assign to an expression that does not have storage.");
			return 0;
		}
		
		if (rop != OP_CAST && get_expr_type(lexpr) != get_expr_type(rexpr)) {
			log(0, "Implicit cast detected, program rejected");
			return 0;
		}
		
		if (rop == OP_SET) {
			if (rexpr->kind == EXPR_OP) rexpr->op_result_reg = lexpr->read_reg;
			assert(lexpr->kind == EXPR_DECL);
			parent_op->op_result_reg = lexpr->read_reg;
		}
		
		
		
		
		parent_op->lhs = lexpr;
		parent_op->rhs = rexpr;
		
		return parent_op;
	}
}
	
unit_local Code_Expr *parse_expr(Token *expr_start, Token **next) {
	
	Code_Expr *expr = 0;
	
	Token *op_token = expr_start+1;
	if (op_token->kind == ';') {
		return parse_one_expr(expr_start, next, (Op_Kind)0xffff);
	}
	
	while  (op_token->kind != ';') {

		Code_Expr *rexpr = parse_expr_rec(expr_start, next, (Op_Kind)0xffff);
		if (!rexpr)  
			return 0;

		if (expr) {
			Code_Expr *parent_op = &exprs[expr_count++];
			parent_op->read_reg = -1;
			parent_op->imm_index = -1;
			parent_op->kind = EXPR_OP;
			if (op_token->kind == '+') parent_op->op = OP_ADD;
			else if (op_token->kind == '-') parent_op->op = OP_SUB;
			else if (op_token->kind == '*') parent_op->op = OP_MUL;
			else if (op_token->kind == '/') parent_op->op = OP_DIV;
			else if (op_token->kind == '=') parent_op->op = OP_SET;
			else if (op_token->kind == '.') parent_op->op = OP_CAST;
			else {
				string msg = tprint_token(op_token, STR("Bad operator"));
				logs(0, msg);
				return 0;
			}
			
			if (expr->kind != EXPR_DECL && parent_op->op == OP_SET) {
				log(0, "Trying to assign to an expression that does not have storage.");
				return 0;
			}
			
			if (parent_op->op != OP_CAST && get_expr_type(expr) != get_expr_type(rexpr)) {
				log(0, "Implicit cast detected, program rejected");
				return 0;
			}
			
			if (parent_op->op == OP_SET) {
				if (rexpr->kind == EXPR_OP) rexpr->op_result_reg = expr->read_reg;
				assert(expr->kind == EXPR_DECL);
				parent_op->op_result_reg = expr->read_reg;
			}
			parent_op->lhs = expr;
			parent_op->rhs = rexpr;
			expr = parent_op;
		} else {
			expr = rexpr;
		}
		
		op_token = *next;
		expr_start = op_token+1;
	}
	return expr;
}

unit_local bool is_alpha(u8 c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
unit_local bool is_digit(u8 c) {
	return (c >= '0' && c <= '9');
}



int main(int argc, char **argv) {
	(void)argc; (void)argv;
	log(0, "Program started.\n");
	
	Arena arena = make_arena(1024ULL*1024ULL*1024ULL*40ULL, 1024ULL*10ULL);
	Allocator a = arena_allocator(&arena);
	ir_allocator = a;

	string in_path = STR("tests/test.simd");
	string out_path = STR("tests/test.dll");

	if (argc > 2) {
		in_path = STR(argv[1]);
		out_path = STR(argv[2]);
	}
	
	SetLastError(0);
	bool ok = sys_read_entire_file(a, in_path, &source);
	assert(ok);
	
	
	
	
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
		
		
		Token *token = &tokens[token_count++];
		token->source_pos = (u64)(p-source.data);
		Token *prev_token = token_count > 1 ? &tokens[token_count-2] : 0;

		if (is_alpha(*p) || *p == '_') {
			
			while (is_alpha(*p) || *p == '_' || is_digit(*p)) {p += 1;}
			
			token->length = (u64)(p-source.data)-token->source_pos;
			token->kind = TOKEN_KIND_IDENTIFIER;
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
			token->kind = dot ? TOKEN_KIND_FLOAT_LITERAL : TOKEN_KIND_INT_LITERAL;
			continue;
		}
		
		if (*p >= TOKEN_KIND_PUNCTUATION_START && *p < TOKEN_KIND_PUNCTUATION_END) {
			token->kind = (Token_Kind)*(p++);
			token->length = (u64)(p-source.data)-token->source_pos;
			
			if (prev_token && token->kind == ':' && prev_token->kind == TOKEN_KIND_IDENTIFIER) {
				decl_tokens[decl_token_count++] = prev_token;
			}
			
			if (token->kind == ';') {
				if (prev_token)  for (s64 j = (s64)token_count-2; j >= 0; j -= 1) {
					if (tokens[j].kind == ';') {
						statement_tokens[statement_token_count++] = &tokens[j+1];
						break;
					} else if (j == 0) {
						statement_tokens[statement_token_count++] = &tokens[0];
						break;
					}
				}
			}
			
			continue;
		}
		
		if (p == source.data+source.count) {
			token->length = (u64)(p-source.data)-token->source_pos;
			token->kind = TOKEN_KIND_EOF;
			continue;
		}
	}
	
	for (u64 i = 0; i < token_count; i += 1) {
		//string s = tprint_token(&tokens[i], STR("Tokenized"));
		
		//logs(0, s);
	}
	
	
	for (u64 i = 0; i < statement_token_count; i += 1) {
		//string s = tprint_token(statement_tokens[i], STR("Statement"));
		//logs(0, s);
		
		Token *first = statement_tokens[i];
		
		bool do_parse_expr = true;
		Token *expr_start = first;
		
		Code_Decl *lhs_decl = 0;
		u64 lhs_decl_index = 0;
		
		if ((first+1)->kind == ':') {
			// Declaration
			
			Code_Decl *decl = &decls[decl_count++];
			*decl = (Code_Decl){0};
			
			do_parse_expr = false;
			
			Token *type = first+2;
			if (type->kind != TOKEN_KIND_IDENTIFIER) {
				log(0, "Unexpected token\n");
				return 1;
			}
			
			string type_ident = (string){ type->length, source.data+type->source_pos };
			
			if (strings_match(type_ident, STR("u32"))) {
				decl->type = TYPE_UINT32;
			} else if (strings_match(type_ident, STR("f32"))) {
				decl->type = TYPE_FLOAT32;
			} else {
				prints(tprint_token(type, STR("Unknown type")));
				return 1;
			}
			decl->type_ident = type_ident;
			decl->ident = (string){ first->length, source.data+first->source_pos };
			
			Token *trailing = type+1;
			
			if (trailing->kind == ';') {
				
			} else if (trailing->kind == '$') {
				Token *spec = trailing+1;
				
				string spec_string =  (string){ spec->length, source.data+spec->source_pos };
				
				if (strings_match(spec_string, STR("Input"))) {
					decl->storage_flags |= STORAGE_INPUT;
				} else if (strings_match(spec_string, STR("InputScalar"))) {
					decl->storage_flags |= STORAGE_INPUT_SCALAR;
				} else if (strings_match(spec_string, STR("Output"))) {
					decl->storage_flags |= STORAGE_OUTPUT;
				} else {
					log(0, "Unexpected post-declaration token\n", type_ident);
					return 1;
				}
				
			} else if (trailing->kind == '=') {
				do_parse_expr = true;
				expr_start = trailing+1;
				lhs_decl = decl;
				lhs_decl_index = decl_count-1;
			} else {
				string trailing_str = (string){ trailing->length, source.data+trailing->source_pos };
				log(0, "Unexpected token '%s' trailing declaration '%s'\n", trailing_str, decl->ident);
				return 1;
			}
			
		} 
		
		if (do_parse_expr) {
			// Expression
			Token *next;
			Code_Expr *expr = parse_expr(expr_start, &next);
			if (!expr) {
				return 1;
			}
			if (lhs_decl) {
				if (expr->kind == EXPR_OP) expr->op_result_reg = (s64)lhs_decl_index;
				Code_Expr *decl_expr = &exprs[expr_count++];
				*decl_expr = (Code_Expr){0};
				decl_expr->imm_index = -1;
				decl_expr->read_reg = (s64)lhs_decl_index;
				decl_expr->decl_index = (s64)lhs_decl_index;
				decl_expr->kind = EXPR_DECL;
				
				Code_Expr *set_expr = &exprs[expr_count++];
				*set_expr = (Code_Expr){0};
				set_expr->imm_index = -1;
				set_expr->decl_index= -1;
				set_expr->op_result_reg = decl_expr->read_reg;
				set_expr->kind = EXPR_OP;
				set_expr->op = OP_SET;
				set_expr->lhs = decl_expr;
				set_expr->rhs = expr;
				
				statements[statement_count++] = set_expr;
				lhs_decl->init_expr = set_expr;
			} else {
				statements[statement_count++] = expr;
			}
			
			
			
			if (next->kind != ';') {
				string next_str = (string) {next->length, source.data+next->source_pos};
				log(0, "Expected ; after statement-level expression, got %s\n", next_str);
				return 1;
			}
		}
		
	}
	
	
	/*emit_header_x64();
	for (u64 i = 0; i < statement_count; i += 1) {
		Code_Expr *expr = statements[i];
		
		if (expr->kind == EXPR_OP) {
			
			emit_expr(expr);
			
		}
	}
	emit_footer();*/
	
	
	
	IR_Program ir = (IR_Program){0};
	ir.init_block.prog = &ir;
	ir.exit_block.prog = &ir;
	
	put_ir_header(&ir);
	
	IR_Block *main_block = &ir.blocks[ir.block_count++];
	*main_block = (IR_Block){0};
	main_block->stack_size = decl_count*32;
	main_block->base_vgpr = ir.base_vgpr;
	main_block->prog = &ir;
	
	for (u64 i = 0; i < statement_count; i += 1) {
		Code_Expr *expr = statements[i];
		
		put_ir_expr(main_block, expr);
	}
	put_ir_footer(&ir);

	{	
		Text_X64_Emitter x64 = (Text_X64_Emitter){0};
		x64.ir = &ir;
		x64.file = sys_open_file(tprint("%s.asm", in_path), FILE_OPEN_WRITE | FILE_OPEN_CREATE | FILE_OPEN_RESET);
		for (u64 i = 0; i < sizeof(x64.regs)/sizeof(x64.regs[0]); i += 1) {
			x64.regs[i].ir_reg_current = -1;
		}
		
		emit_text_x64_header(&x64);
		emit_text_x64_block(&x64, main_block);
		emit_text_x64_footer(&x64);
		
		sys_close(x64.file);
	}
	
	/*{	
		Spirv_Emitter spv = (Spirv_Emitter){0};
		spv.ir = &ir;
		spv.file = sys_open_file(tprint("%s.spv", in_path), FILE_OPEN_WRITE | FILE_OPEN_CREATE | FILE_OPEN_RESET);;
		for (u64 i = 0; i < sizeof(spv.regs)/sizeof(spv.regs[0]); i += 1) {
			spv.regs[i].ir_reg_current = -1;
		}
		
		emit_spv_header(&spv);
		emit_spv_block(&spv, main_block);
		emit_spv_footer(&spv);
		
		sys_close(spv.file);
	}
    
    print("Program exit early");
    volatile bool t = true;
    if (t) return 0;*/
    
    Easy_Command_Result assembler_res = sys_run_command_easy(tprint("\"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.42.34433\\bin\\Hostx86\\x64\\ml64.exe\" /c /Fo\"%s.obj\" \"%s.asm\"", in_path, in_path));
    assert(assembler_res.process_start_success && assembler_res.exit_code == 0 || assembler_res.exit_code == 1104);
    
    Easy_Command_Result linker_res = sys_run_command_easy(tprint("\"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.42.34433\\bin\\Hostx64\\x64\\link.exe\" /DLL /EXPORT:out_buffer /EXPORT:in_buffer /SUBSYSTEM:WINDOWS /ENTRY:DllMain /OUT:%s %s.obj", out_path, in_path));
    assert(linker_res.process_start_success && linker_res.exit_code == 0);
	
	u32 in0 = 5;
	f32 in1[] = {9.3f, 2.3f, 1.3f, 3.3f, 9.3f, 2.3f, 1.3f, 3.3f};
	
	void *lib = sys_load_library(STR("tests/test.dll"));
	
	f32* in_buffer = (float*)sys_get_library_symbol(lib, STR("in_buffer"));
    assert(in_buffer);
    
    *(u32*)in_buffer = in0;
    memcpy(in_buffer+1, in1, sizeof(in1));
	
	f32* out = (float*)sys_get_library_symbol(lib, STR("out_buffer"));
    assert(out);
    
	void (*GO)(void) = (void (*)(void))sys_get_library_symbol(lib, STR("GO"));
	assert(GO);
	GO();
	
    
    
    
    log(0, "in0: %u", in0);
    log(0, "in1: %f", in1);
    
    log(0, "out[0]: x: %f, y: %f, z: %f, w: %f", out[0], out[8], out[16], out[24]);
    log(0, "out[1]: x: %f, y: %f, z: %f, w: %f", out[1], out[9], out[17], out[25]);
    log(0, "out[2]: x: %f, y: %f, z: %f, w: %f", out[2], out[10], out[18], out[26]);
    log(0, "out[3]: x: %f, y: %f, z: %f, w: %f", out[3], out[11], out[19], out[27]);
    log(0, "out[0]: x: %f, y: %f, z: %f, w: %f", out[4], out[12], out[20], out[28]);
    log(0, "out[0]: x: %f, y: %f, z: %f, w: %f", out[5], out[13], out[21], out[29]);
    log(0, "out[0]: x: %f, y: %f, z: %f, w: %f", out[6], out[14], out[22], out[30]);
    log(0, "out[0]: x: %f, y: %f, z: %f, w: %f", out[7], out[15], out[23], out[31]);
	
	log(0, "Program ended.\n");
	
	
}








/*unit_local void emit_instr_0(Instr instr) {
	string istr = instr_avx_str(instr);
	fprint(out_file, "%s\n", istr);
}
unit_local void emit_instr_1(Instr instr, Operand op0) {
	string istr = instr_avx_str(instr);
	s64 i0 = op0.reg-MAX_IR_REGS;
	string sop0 = op0.kind == o_reg ? (op0.reg < MAX_IR_REGS ? tprint("ymm%u", op0.reg) : tprint("i%u", i0)) : tprint("[%s]", op0.addr);
	fprint(out_file, "%s %s\n", istr, sop0);
}
unit_local void emit_instr_2(Instr instr, Operand op0, Operand op1) {
	string istr = instr_avx_str(instr);
	s64 i0 = op0.reg-MAX_IR_REGS;
	string sop0 = op0.kind == o_reg ? (op0.reg < MAX_IR_REGS ? tprint("ymm%u", op0.reg) : tprint("i%u", i0)) : tprint("[%s]", op0.addr);
	s64 i1 = op1.reg-MAX_IR_REGS;
	string sop1 = op1.kind == o_reg ? (op1.reg < MAX_IR_REGS ? tprint("ymm%u", op1.reg) : tprint("i%u", i1)) : tprint("[%s]", op1.addr);
	fprint(out_file, "%s %s, %s\n", istr, sop0, sop1);
}
unit_local void emit_instr_3(Instr instr, Operand op0, Operand op1, Operand op2) {
	string istr = instr_avx_str(instr);
	s64 i0 = op0.reg-MAX_IR_REGS;
	string sop0 = op0.kind == o_reg ? (op0.reg < MAX_IR_REGS ? tprint("ymm%u", op0.reg) : tprint("i%u", i0)) : tprint("[%s]", op0.addr);
	s64 i1 = op1.reg-MAX_IR_REGS;
	string sop1 = op1.kind == o_reg ? (op1.reg < MAX_IR_REGS ? tprint("ymm%u", op1.reg) : tprint("i%u", i1)) : tprint("[%s]", op1.addr);
	s64 i2 = op2.reg-MAX_IR_REGS;
	string sop2 = op2.kind == o_reg ? (op2.reg < MAX_IR_REGS ? tprint("ymm%u", op2.reg) : tprint("i%u", i2)) : tprint("[%s]", op2.addr);
	fprint(out_file, "%s %s, %s, %s\n", istr, sop0, sop1, sop2);
}



unit_local void emit_op(struct Code_Expr *op_expr) {
	
	if (op_expr->op == OP_SET && op_expr->lhs->kind == EXPR_DECL && op_expr->lhs->read_reg == op_expr->rhs->read_reg)
		return;
	
	Code_Expr *lexpr = op_expr->lhs;
	Code_Expr *rexpr = op_expr->rhs;
	Op_Kind op = op_expr->op;
	
	Instr i = 0;
	
	switch (op) {
		case OP_CAST: 
			Type ltype = get_expr_type(lexpr);
			
			assert(ltype != TYPE_INVALID);
			
			switch (ltype) {
				case TYPE_FLOAT32: switch (rexpr->type) {
					case TYPE_FLOAT32: return; 
					case TYPE_UINT32:  i = i_f32toi32; break;
					case TYPE_INVALID: assert(false); break; 
					default: assert(false); break; 
				} break;
				case TYPE_UINT32: switch (rexpr->type) {
					case TYPE_FLOAT32: i = i_i32tof32; break; 
					case TYPE_UINT32:  return;
					case TYPE_INVALID: assert(false); break; 
					default: assert(false); break; 
				} break;
				case TYPE_INVALID: assert(false); break; 
				default: assert(false); break; 
			}
			 
			break;
		case OP_MUL:  i = i_mul; break;
		case OP_DIV:  i = i_div; break;
		case OP_ADD:  i = i_add; break;
		case OP_SUB:  i = i_sub; break;
		case OP_SET:  i = i_mov; break;
		
		case OP_INVALID: break;
		default: assert(false); break;
	}
	
	
	//string mnemonic = instr_avx_str(i);
	//fprint(out_file, "%s\n", mnemonic);
	
	switch (i) {
		case i_mov: emit_instr_2(i, op_reg(lexpr->read_reg), op_reg(rexpr->read_reg)); break;
		case i_f32toi32: // fallthrough
		case i_i32tof32:  {
			s64 out_reg = 15;
			if (op_expr->op_result_reg > -1) out_reg = op_expr->op_result_reg;
			emit_instr_2(i, op_reg(out_reg), op_reg(lexpr->read_reg)); 
			op_expr->op_result_reg = out_reg;
			if (op_expr->read_reg == -1) op_expr->read_reg = out_reg;
			break;
		}
		case i_add: // fallthrough
		case i_sub: // fallthrough
		case i_mul: // fallthrough
		case i_div: {
			s64 out_reg = 15;
			if (op_expr->op_result_reg > -1) out_reg = op_expr->op_result_reg;
			emit_instr_3(i, op_reg(out_reg), op_reg(lexpr->read_reg), op_reg(rexpr->read_reg)); 
			op_expr->op_result_reg = out_reg;
			if (op_expr->read_reg == -1) op_expr->read_reg = out_reg;
			break;
		}
		default: break;
	}
}

unit_local void emit_expr(struct Code_Expr *expr)
{
	if (!expr) {
		return;
	}

	switch (expr->kind) {
	case EXPR_OP:
	
		if (expr->op == OP_SET && expr->rhs->kind == EXPR_OP &&  expr->lhs->kind == EXPR_DECL) {
			expr->rhs->op_result_reg = expr->lhs->read_reg;
		}
		
		if (expr->read_reg == -1) expr->read_reg = expr->op_result_reg;
		
		//if (expr->op == OP_SET && expr->lhs->kind == EXPR_DECL && expr->rhs->kind == EXPR_DECL && expr->lhs->decl_index == expr->rhs->decl_index) return;
		
		emit_expr(expr->lhs);
		emit_expr(expr->rhs);
		
		emit_op(expr);
		break;

	case EXPR_DECL:
	
	
		break;

	case EXPR_LITERAL_FLOAT:
	case EXPR_LITERAL_INT:
		expr->read_reg = MAX_IR_REGS+expr->imm_index;
		break;
	case EXPR_TYPE:
		break;
		
	default: assert(false); break;
	}
}

void emit_block_x64_text(IR_Block *block) {
	
}
unit_local void emit_header_x64_text(IR_Program *prog, File_Handle file) {
	fprint(file, ".data\n");
	
	for (u64 i = 0; i < imm_u32_count; i += 1) {
		fprint(file, "ALIGN 8\n");
		fprint(file, "i%u dd ", i);
		for (u64 j = 0; j < 8; j += 1) {
			if (j != 7) fprint(file, "%u, ", imm_u32s[i]);
			else fprint(file, "%u\n", imm_u32s[i]);
		}
	}
	
	u64 input_size = 0;
	u64 output_size = 0;
	
	for (u64 i = 0; i < decl_count; i += 1) {
		Code_Decl *decl = &decls[i];
		
		switch (decl->type) {
			
			case TYPE_FLOAT32:
				if (decl->storage_flags & STORAGE_INPUT) input_size += 4;
				if (decl->storage_flags & STORAGE_INPUT_SCALAR) input_size += 16;
				if (decl->storage_flags & STORAGE_OUTPUT) output_size += 4;
				break;
			case TYPE_UINT32:
				if (decl->storage_flags & STORAGE_INPUT) input_size += 4;
				if (decl->storage_flags & STORAGE_INPUT_SCALAR) input_size += 16;
				if (decl->storage_flags & STORAGE_OUTPUT) output_size += 4;
				break;
			
			case TYPE_INVALID: assert(false); break;
			default: assert(false); break;
		}
	}
	
	fprint(file, "PUBLIC out_buffer\n");
	fprint(file, "PUBLIC in_buffer\n");
	fprint(file, "out_buffer DD %u DUP(0)\n", output_size);
	fprint(file, "in_buffer DD %u DUP(0)\n", input_size);
	
	fprint(file, "\n");
	
	fprint(file, ".code\n");
	fprint(file, "PUBLIC GO\n");
	fprint(file, "GO PROC EXPORT\n");
	
	
	
	
	fprint(file, "\n");
	
	s64 r = 8;
	u64 offset = 0;
	for (u64 i = 0; i < decl_count; i += 1) {
		Code_Decl *decl = &decls[i];
		
		switch (decl->type) {
			
			case TYPE_FLOAT32:
				if (decl->storage_flags & STORAGE_INPUT_SCALAR) {
					fprint(file, "mov r%ud, in_buffer[%u]\n", r, offset);
					fprint(file, "movd ymm%u, r%ud\n", i, r);
					fprint(file, "vbroadcastss ymm%u, ymm%u\n", i, i);
					r += 1;
					offset += 4;
				}
				if (decl->storage_flags & STORAGE_INPUT) {
					fprint(file, "vmovups ymm%u, in_buffer[%u]\n", i, offset);
					r += 1;
					offset += 16;
				}
				break;
			case TYPE_UINT32:
				if (decl->storage_flags & STORAGE_INPUT_SCALAR) {
					fprint(file, "mov r%ud, in_buffer[%u]\n", r, offset);
					fprint(file, "movd ymm%u, r%ud\n", i, r);
					fprint(file, "vbroadcastss ymm%u, ymm%u\n", i, i);
					r += 1;
					offset += 4;
				}
				if (decl->storage_flags & STORAGE_INPUT) {
					fprint(file, "vmovups ymm%u, in_buffer[%u]\n", i, offset);
					r += 1;
					offset += 16;
				}
				break;
			
			case TYPE_INVALID: assert(false); break;
			default: assert(false); break;
		}
	}
	
	fprint(file, "\n");
}

unit_local void emit_footer_x64_text(IR_Program *prog) {

	fprint(out_file, "\n");
	
	u64 input_count = 0;
	
	for (u64 i = 0; i < decl_count; i += 1) {
		Code_Decl *decl = &decls[i];
		
		if (decl->storage_flags & STORAGE_INPUT) input_count += 1;
		if (decl->storage_flags & STORAGE_INPUT_SCALAR) input_count += 1;
	}
	
	u64 r = input_count;
	u64 offset = 0;
	for (u64 i = 0; i < decl_count; i += 1) {
		Code_Decl *decl = &decls[i];
		
		switch (decl->type) {
			
			case TYPE_FLOAT32:
				if (decl->storage_flags & STORAGE_OUTPUT) {
					fprint(out_file, "movaps out_buffer[%u], ymm%u\n", offset, r);
					r += 1;
					offset += 16;
				}
				break;
			case TYPE_UINT32:
				if (decl->storage_flags & STORAGE_OUTPUT) {
					fprint(out_file, "movaps out_buffer[%u], ymm%u\n", offset, r);
					r += 1;
					offset += 16;
				}
				break;
			
			case TYPE_INVALID: assert(false); break;
			default: assert(false); break;
		}
	}

	fprint(out_file, "\nGO ENDP\n");
	fprint(out_file, "DllMain PROC hinstDLL:QWORD, fdwReason:QWORD, lpReserved:QWORD\n");
	fprint(out_file, "mov  eax, 1\n");
	fprint(out_file, "ret\n");
	fprint(out_file, "DllMain ENDP\n");
	fprint(out_file, "END");
	
}
*/

