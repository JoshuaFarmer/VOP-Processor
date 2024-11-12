#pragma once
#define MAX_RAM (1 << 24)

char ram[MAX_RAM];

enum InstructionOpcode {
	// 0x00-0x0F STACK OPERATIONS
	PUSH_A_Sn = 0x00,
	POP_A_Sn = 0x01,
	POKE_A_Sn = 0x02,
	PEEK_A_Sn = 0x03,
	
	PUSH_Rn_Sn = 0x04,
	POP_Rn_Sn = 0x05,
	POKE_Rn = 0x06,
	PEEK_Rn = 0x07,

	PUSH_i8 = 0x08,
	PUSH_i16 = 0x09,

	PUSH_P0 = 0x0A,
	PUSH_P1 = 0x0B,
	POP_P1 = 0x0C,

	PUSH_F = 0x0D,
	POP_F = 0x0E,

	// 0x10-0x15 EXCHANGE OPERATIONS
	XC_A_A = 0x10,
	XC_Rn0_Rn1 = 0x11,
	XC_Rn_Sn = 0x12,
	XC_Sn1_Sn2 = 0x13,
	XC_A_Sn = 0x14,
	XC_A_Rn = 0x15,

	// 0x16-0x2A BASIC DATA MANIPULATION
	STORE_A_a16 = 0x16,
	STORE_Rn_a16 = 0x17,
	LOAD_A_a16 = 0x18,
	LOAD_Rn_a16 = 0x19,

	FAR_STORE_A_a24 = 0x1A,
	FAR_STORE_Rn_a24 = 0x1B,
	FAR_LOAD_A_a24 = 0x1C,
	FAR_LOAD_Rn_a24 = 0x1D,

	SET_a16 = 0x1E,
	GET_a16 = 0x1F,

	BLCKGET_a16_n8 = 0x20,
	BLCKSET_a16_n8 = 0x21,

	LD_A_Rn = 0x22,
	LD_A_Sn = 0x23,
	LD_Rn_A = 0x24,
	LD_Sn_A = 0x25,
	LD_Rn_Sn = 0x26,
	LD_Sn_Rn = 0x27,

	LDI_Rn_i16 = 0x28,
	LDI_Sn_i16 = 0x29,
	LDI_A_i16 = 0x2A,

	// 0x2B-0x38 ARITHMETIC OPERATIONS
	ADD_i16 = 0x2B,
	ADD_Sn = 0x2E,
	ADD_Rn = 0x2F,
	ADD_i16_imm = 0x30,
	ADD_Sn_A = 0x31,
	ADD_Rn_A = 0x32,

	SUB_i16 = 0x2B,
	SUB_Sn = 0x2E,
	SUB_Rn = 0x2F,
	SUB_i16_imm = 0x30,
	SUB_Sn_A = 0x31,
	SUB_Rn_A = 0x32,

	CMP_i16 = 0x33,
	CMP_Sn = 0x34,
	CMP_Rn = 0x35,
	CMP_i16_imm = 0x36,
	CMP_Sn_A = 0x37,
	CMP_Rn_A = 0x38,

	// 0x39-0x53 LOGICAL OPERATIONS
	NOT_A = 0x39,
	NEG_A = 0x3A,

	NOT_Rn = 0x3B,
	NEG_Rn = 0x3C,

	NOT_Rn_mem = 0x3D,
	NEG_Rn_mem = 0x3E,

	NOT_Sn = 0x40,
	NEG_Sn = 0x41,

	AND_i16 = 0x43,
	AND_Rn = 0x46,
	AND_Sn = 0x47,
	AND_i16_imm = 0x48,
	AND_Rn_reg = 0x49,

	OR_i16 = 0x4A,
	OR_Rn = 0x4B,
	OR_Sn = 0x4C,
	OR_i16_imm = 0x4D,
	OR_Rn_reg = 0x4E,

	XOR_i16 = 0x4F,
	XOR_Rn = 0x50,
	XOR_Sn = 0x51,
	XOR_i16_imm = 0x52,
	XOR_Rn_reg = 0x53,

	// 0x54-0x69 JUMP AND CALLING/RET
	JUMP_a16 = 0x54,
	JUMP_Sn = 0x55,
	FAR_JUMP_a24 = 0x56,
	REL_JUMP_i8 = 0x57,
	REL_JMZ_i8 = 0x58,
	REL_JMC_i8 = 0x59,
	JMZ_a16 = 0x5A,
	JMC_a16 = 0x5B,
	JP_a16 = 0x5C,
	JNZ_a16 = 0x5D,
	JNC_a16 = 0x5E,
	JNP_a16 = 0x5F,

	CALL_a16 = 0x60,
	FAR_CALL_a24 = 0x61,
	CALZ_a16 = 0x62,
	CALC_a16 = 0x63,
	CALL_Sn = 0x64,

	RET = 0x66,
	FAR_RET = 0x67,
	RETZ = 0x68,
	RETC = 0x69,

	// 0x6A-0xF0 OTHER INSTRUCTIONS
	SETFORMAT_i8 = 0x6A,
	OUT = 0x6B,
	IN = 0x6C,
	INT_i8 = 0x6D,
	INT_Rn = 0x6E,
	CLI = 0x6F,
	STI = 0x70,

	LD_Rn0_Rn1 = 0x71,  // Load Rn0 with Rn1
	LD_Rn1_Rn0 = 0x71,  // Reverse load Rn0 from Rn1

	// 0xF0-F1 LOOPS
	REP = 0xF0,
	END = 0xF1
};


class VOP {
	private:

	public:

	uint16_t Tmp;
	uint16_t Acc;
	uint16_t Rn[16];
	uint16_t Sn[3];
	uint16_t PC;
	uint8_t  P0, P1;

	uint16_t __LADR[256][2]; // START ADDR, END ADDR
	uint8_t  __LOC;

	bool busy = false;
	bool zero = false;
	bool carry = false;
	bool parity = false;
	bool interrupt_mask = false;
	bool data_format = false;

	VOP() {
		Acc = 0;
	}

	uint8_t fetch(uint16_t offset, uint8_t segment) {
		size_t addr = ((segment << 16) | offset);
		if (addr >= MAX_RAM) {
			return 0;
		}

		return ram[addr];
	}

	void write(uint16_t offset, uint8_t segment, uint8_t value) {
		size_t addr = ((segment << 16) | offset);
		if (addr >= MAX_RAM) {
			return;
		}

		ram[addr] = value;
	}

	void push(uint16_t value) {
		int n = fetch(PC++, P0) & 0b11;
		if (n > 2) n = 2;
		if (data_format == false) {
			write(Sn[n]--, P1, value);
			write(Sn[n]--, P1, value >> 8);
		} else {
			write(Sn[n]--, P1, value);
		}
	}

	uint16_t pop() {
		int n = fetch(PC++, P0) & 0b11;
		if (n > 2) n = 2;
		int value = 0;
		if (data_format == false) {
			value |= fetch(Sn[n]++, P1) << 8;
			value |= fetch(Sn[n]++, P1);
		} else {
			value |= fetch(Sn[n]++, P1);
		}

		return value;
	}

	void poke(uint16_t value, uint16_t addr) {
		if (data_format == false) {
			write(addr, P1, value);
			write(addr+1, P1, value  >> 8);
		} else {
			write(addr, P1, value);
		}
	}

	uint16_t peek(uint16_t addr) {
		int value = 0x0000;
		if (data_format == false) {
			value |= fetch(addr, P1);
			value |= fetch(addr+1, P1) << 8;
		} else {
			value |= fetch(addr, P1);
		}

		return value;
	}

	void executeNext() {
		int instruction = fetch(PC++, P0);
		switch (instruction) {
			case PUSH_A_Sn:
				push(Acc);
				break;
			case POP_A_Sn:
				Acc = pop();
				break;
			case POKE_A_Sn:
				int idx = (fetch(PC, P0) >> 4) & 0xF;
				poke(Acc, Sn[idx]);
				break;
			case PEEK_A_Sn:
				int idx = (fetch(PC, P0) >> 4) & 0xF;
				Acc = peek(Sn[idx]);
				break;
			case PUSH_Rn_Sn: {
				int idx = (fetch(PC, P0) >> 4) & 0xF;
				push(Rn[idx]);
				} break;
			case POP_Rn_Sn: {
				int idx = (fetch(PC, P0) >> 4) & 0xF;
				Rn[idx] = pop();
				} break;
			case POKE_Rn:
				int idx0 = (fetch(PC, P0)) & 0xF;
				int idx1 = (fetch(PC, P0) >> 4) & 0xF;
				poke(Rn[idx1], Sn[idx0]);
				break;
			case PEEK_Rn:
				int idx0 = (fetch(PC, P0)) & 0xF;
				int idx1 = (fetch(PC, P0) >> 4) & 0xF;
				Rn[idx1] = peek(Sn[idx0]);
				break;
			case PUSH_i8:
				int val = fetch(PC++, P0);
				push(val);
				break;
			case PUSH_i16:
				int val  = fetch(PC++, P0);
				    val |= fetch(PC++, P0) << 8;
				push(val);
				break;
			case PUSH_P0:
				push(P0);
				break;
			case PUSH_P1:
				push(P1);
				break;
			case POP_P1:
				P1 = pop();
				break;
			case PUSH_F: {
				int value = zero | \
				            (carry << 1)  | \
				            (parity << 2) | \
				            (interrupt_mask << 3) | \
				            (data_format << 4);
				push(value);
				}
				break;
			case POP_F:
				int value = pop();
				zero           = value & 0b00001;
				carry          = value & 0b00010;
				parity         = value & 0b00100;
				interrupt_mask = value & 0b01000;
				data_format    = value & 0b10000;
				break;

			case XC_A_A: // NOP
				break;
			case XC_Rn0_Rn1: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0xF;
				int n1  = (idx >> 4) & 0xF;

				Tmp = Rn[n0];
				Rn[n0] = Rn[n1];
				Rn[n1] = Tmp;
				} break;
			case XC_Rn_Sn: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0xF;
				int n1  = (idx >> 4) & 0xF;

				Tmp = Rn[n0];
				Rn[n0] = Sn[n1];
				Sn[n1] = Tmp;
				} break;
			case XC_Sn1_Sn2: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0xF;
				int n1  = (idx >> 4) & 0xF;

				Tmp = Sn[n0];
				Sn[n0] = Sn[n1];
				Sn[n1] = Tmp;
				} break;
			case XC_A_Sn: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0xF;

				Tmp = Acc;
				Acc = Sn[n0];
				Sn[n0] = Tmp;
				} break;
			case XC_A_Rn: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0xF;

				Tmp = Acc;
				Acc = Rn[n0];
				Rn[n0] = Tmp;
				} break;
			case STORE_A_a16: {
				int address  = fetch(PC++, P0);
				    address |= fetch(PC++, P0) << 8;
				write(address, P1, Acc);
				} break;
			case STORE_Rn_a16: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0xF;
				int address  = fetch(PC++, P0);
				    address |= fetch(PC++, P0) << 8;
				write(address, P1, Rn[n0]);
				} break;
			case LOAD_A_a16: {
				int address  = fetch(PC++, P0);
				    address |= fetch(PC++, P0) << 8;
				Acc = fetch(address, P1);
				} break;
			case LOAD_Rn_a16: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0xF;
				int address  = fetch(PC++, P0);
				    address |= fetch(PC++, P0) << 8;
				Rn[n0] = fetch(address, P1);
				} break;
			case FAR_STORE_A_a24: {
				int address  = fetch(PC++, P0);
				    address |= fetch(PC++, P0) << 8;
				int seg      = fetch(PC++, P0);
				write(address, seg, Acc);
				} break;
			case FAR_STORE_Rn_a24: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0xF;
				int address  = fetch(PC++, P0);
				    address |= fetch(PC++, P0) << 8;
				int seg      = fetch(PC++, P0);
				write(address, seg, Rn[n0]);
				} break;
			case FAR_LOAD_A_a24: {
				int address  = fetch(PC++, P0);
				    address |= fetch(PC++, P0) << 8;
				int seg      = fetch(PC++, P0);
				Acc = fetch(address, seg);
				} break;
			case FAR_LOAD_Rn_a24: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0xF;
				int address  = fetch(PC++, P0);
				    address |= fetch(PC++, P0) << 8;
				int seg      = fetch(PC++, P0);
				Rn[n0] = fetch(address, seg);
				} break;

			case GET_a16: {
				int off = fetch(PC++, P0);
				Acc = fetch(Sn[2] - off, P1);
				} break;
			case SET_a16: {
				int off = fetch(PC++, P0);
				write(Sn[2] - off, P1, Acc);
				} break;
			case BLCKGET_a16_n8: {
				int addr  = fetch(PC++, P0);
				    addr |= fetch(PC++, P0) << 8;
				int count = fetch(PC++, P0);
				for (int i = 0; i < count && i < 16; ++i) {
					Rn[i] = fetch(addr+i, P1);
				}
				} break;
			case BLCKSET_a16_n8: {
				int addr  = fetch(PC++, P0);
				    addr |= fetch(PC++, P0) << 8;
				int count = fetch(PC++, P0);
				for (int i = 0; i < count && i < 16; ++i) {
					write(addr+i, P1, Rn[i]);
				}
				} break;
		}
	}
};