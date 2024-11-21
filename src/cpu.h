#pragma once
#define MAX_RAM (1 << 24)
#define SCREEN_WIDTH  256
#define SCREEN_HEIGHT 160
#define SCREEN_SCALE 2

unsigned char  ram[MAX_RAM];
unsigned char* video_ram = ram+65536; // Page 0x1

enum {
	POWER_OFF_IO,
	SWAP_BUFFERS,
	TERMINAL,
	TERMINAL_I,
};

class VOP {
	private:
	public:
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

		BLCKGET_a16 = 0x20,
		BLCKSET_a16 = 0x21,

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

		SUB_i16 = 0x33,
		SUB_Sn = 0x34,
		SUB_Rn = 0x35,
		SUB_i16_imm = 0x36,
		SUB_Sn_A = 0x37,
		SUB_Rn_A = 0x38,

		CMP_i16 = 0x73,
		CMP_Sn = 0x74,
		CMP_Rn = 0x75,
		CMP_i16_imm = 0x76,
		CMP_Sn_A = 0x77,
		CMP_Rn_A = 0x78,

		// 0x39-0x53 LOGICAL OPERATIONS
		NOT_A = 0x39,
		NEG_A,

		NOT_Rn,
		NEG_Rn,

		NOT_Rn_mem,
		NEG_Rn_mem,

		NOT_Sn,
		NEG_Sn,

		AND_i16,
		AND_Rn,
		AND_Sn,
		AND_i16_imm,
		AND_Rn_reg,

		OR_i16,
		OR_Rn,
		OR_Sn,
		OR_i16_imm,
		OR_Rn_reg,

		XOR_i16,
		XOR_Rn,
		XOR_Sn,
		XOR_i16_imm,
		XOR_Rn_reg,

		// 0x54-0x69 JUMP AND CALLING/RET
		JUMP_a16 = 0x54,
		JUMP_Rn = 0x55,
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
		CALL_Rn = 0x64,

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

		LDR_Rn0_Rn1 = 0x71,
		STR_Rn0_Rn1 = 0x72,

		INC_Rn = 0x80,
		DEC_Rn = 0x81,
		INC_Sn = 0x82,
		DEC_Sn = 0x83,
		INC_Rn_AT = 0x84,
		DEC_Rn_AT = 0x85,
		INC_Sn_AT = 0x86,
		DEC_Sn_AT = 0x87,

		INC_A = 0x88,
		DEC_A = 0x89,

		BLCKGET_Sn = 0x90,
		BLCKSET_Sn = 0x91,
		NEAR_POKE_Rn,
		NEAR_PEEK_Rn,

		SHL_R,
		SHR_R,

		ADD_Rn_i16,
		SUB_Rn_i16,
		CMP_Rn_i16,
		ADD_Rn1_Rn2,
		SUB_Rn1_Rn2,
		CMP_Rn1_Rn2,
		AND_Rn1_Rn2,
		OR_Rn1_Rn2,
		NAND_Rn1_Rn2,
		XOR_Rn1_Rn2,
		LD_Rn_Rn,

		PEEK_A_Sn_SRn,
		PEEK_A_Sn_ARn,
		POKE_A_Sn_SRn,
		POKE_A_Sn_ARn,

		// 0xF0-F1 LOOPS
		REP = 0xF0,
		END = 0xF1
	};

	uint16_t Tmp=0x0000;
	uint16_t Res=0x0000;
	uint16_t Acc=0x0000;
	uint16_t Rn[16]={0x0000};
	uint16_t Sn[4]={0x5000, 0x6000, 0x7000, 0x8000};
	uint16_t PC=0x0000;
	uint8_t  P0=0x0000, P1=0x0000;

	uint8_t  IO[65536] = {0};

	uint16_t __LADR[256][2]; // START ADDR, END ADDR
	uint8_t  __LOC;

	bool busy = false;
	bool zero = false;
	bool carry = false;
	bool parity = false;
	bool interrupt_mask = false;
	bool data_format = false;

	VOP(int initSegment, int initOff) {
		P0 = initSegment;
		PC = initOff;
		Acc = 0x00;
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

	void poke(uint16_t value, uint16_t addr, uint8_t P) {
		if (data_format == false) {
			write(addr, P, value);
			write(addr+1, P, value  >> 8);
		} else {
			write(addr, P, value);
		}
	}

	uint16_t peek(uint16_t addr, uint8_t P) {
		int value = 0x0000;
		if (data_format == false) {
			value |= fetch(addr, P);
			value |= fetch(addr+1, P) << 8;
		} else {
			value |= fetch(addr, P);
		}

		return value;
	}

	void interrupt(uint8_t x)
	{
		// 4 bytes per entry
		uint16_t addr = peek(x * 4, 0x00);
		uint8_t  page = fetch(x+2, 0x00);

		write(Sn[3]--, 0xFF, PC);
		write(Sn[3]--, 0xFF, PC >> 8);
		write(Sn[3]--, 0xFF, P0);
		
		P0 = page;
		PC = addr;
	}

	void flags() {
		zero   = (Res == 0);
		carry  = (Tmp > Res);
		parity = __builtin_parity(Res);
	}

	int find_end_of_rep(int Addr) {
		int old = Addr;
		int X = 0, bounds = 65536 - Addr;
		while (X != 1 && --bounds) {
			int _ = fetch(Addr++, P0);
			if (_ == REP) X--;
			if (_ == END) X++;
		}

		if (bounds == 0) {
			printf("Error: No matching END found for REP at addRess 0x%X\n", old);
			return old;
		}

		return Addr;
	}

	void executeNext() {
		int instruction = fetch(PC++, P0);
		switch (instruction) {
			case PUSH_A_Sn: {
				push(Acc);
				} break;
			case POP_A_Sn: {
				Acc = pop();
				} break;
			case POKE_A_Sn: {
				int idx = (fetch(PC++, P0)) & 0xF;
				poke(Acc, Sn[idx]);
				} break;
			case PEEK_A_Sn: {
				int idx = (fetch(PC++, P0)) & 0xF;
				Acc = peek(Sn[idx]);
				} break;
			case PUSH_Rn_Sn: {
				int idx = (fetch(PC++, P0)) & 0xF;
				push(Rn[idx]);
				} break;
			case POP_Rn_Sn: {
				int idx = (fetch(PC++, P0)) & 0xF;
				Rn[idx] = pop();
				} break;
			case POKE_Rn: {
				int idx0 = (fetch(PC++, P0)) & 0xF;
				int idx1 = (fetch(PC++, P0)) & 0xF;
				poke(Rn[idx0], Sn[idx1]);
				} break;
			case PEEK_Rn: {
				int idx0 = (fetch(PC++, P0)) & 0xF;
				int idx1 = (fetch(PC++, P0)) & 0xF;
				Rn[idx0] = peek(Sn[idx1]);
				} break;
			case PUSH_i8: {
				int val = fetch(PC++, P0);
				push(val);
				} break;
			case PUSH_i16: {
				int val  = fetch(PC++, P0);
				    val |= fetch(PC++, P0) << 8;
				push(val);
				} break;
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
				{
				int value = pop();
				zero           = value & 0b00001;
				carry          = value & 0b00010;
				parity         = value & 0b00100;
				interrupt_mask = value & 0b01000;
				data_format    = value & 0b10000;
				} break;

			case XC_A_A: // NOP
				break;
			case XC_Rn0_Rn1: {
				int n0  = fetch(PC++, P0) & 0xF;
				int n1  = fetch(PC++, P0) & 0xF;

				Tmp = Rn[n0];
				Rn[n0] = Rn[n1];
				Rn[n1] = Tmp;
				} break;
			case XC_Rn_Sn: {
				int n0  = fetch(PC++, P0) & 0xF;
				int n1  = fetch(PC++, P0) & 0b11;

				Tmp = Rn[n0];
				Rn[n0] = Sn[n1];
				Sn[n1] = Tmp;
				} break;
			case XC_Sn1_Sn2: {
				int n0  = fetch(PC++, P0) & 0b11;
				int n1  = fetch(PC++, P0) & 0b11;

				Tmp = Sn[n0];
				Sn[n0] = Sn[n1];
				Sn[n1] = Tmp;
				} break;
			case XC_A_Sn: {
				int n0  = fetch(PC++, P0) & 0b11;

				Tmp = Acc;
				Acc = Sn[n0];
				Sn[n0] = Tmp;
				} break;
			case XC_A_Rn: {
				int n0  = fetch(PC++, P0) & 0xF;

				Tmp = Acc;
				Acc = Rn[n0];
				Rn[n0] = Tmp;
				} break;
			case STORE_A_a16: {
				int addRess  = fetch(PC++, P0);
				    addRess |= fetch(PC++, P0) << 8;
				poke(Acc, addRess, P1);
				} break;
			case STORE_Rn_a16: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0xF;
				int addRess  = fetch(PC++, P0);
				    addRess |= fetch(PC++, P0) << 8;
				poke(Rn[n0], addRess, P1);
				} break;
			case LOAD_A_a16: {
				int addRess  = fetch(PC++, P0);
				    addRess |= fetch(PC++, P0) << 8;
				Acc = peek(addRess, P1);
				} break;
			case LOAD_Rn_a16: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0xF;
				int addRess  = fetch(PC++, P0);
				    addRess |= fetch(PC++, P0) << 8;
				Rn[n0] = peek(addRess, P1);
				} break;
			case FAR_STORE_A_a24: {
				int addRess  = fetch(PC++, P0);
				    addRess |= fetch(PC++, P0) << 8;
				int seg      = fetch(PC++, P0);
				poke(Acc, addRess, seg);
				} break;
			case FAR_STORE_Rn_a24: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0xF;
				int addRess  = fetch(PC++, P0);
				    addRess |= fetch(PC++, P0) << 8;
				int seg      = fetch(PC++, P0);
				poke(Rn[n0], addRess, seg);
				} break;
			case FAR_LOAD_A_a24: {
				int addRess  = fetch(PC++, P0);
				    addRess |= fetch(PC++, P0) << 8;
				int seg      = fetch(PC++, P0);
				Acc = peek(addRess, seg);
				} break;
			case FAR_LOAD_Rn_a24: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0xF;
				int addRess  = fetch(PC++, P0);
				    addRess |= fetch(PC++, P0) << 8;
				int seg      = fetch(PC++, P0);
				Rn[n0] = peek(addRess, seg);
				} break;

			case GET_a16: {
				int off = fetch(PC++, P0);
				Acc = peek(Sn[2] - off, P1);
				} break;
			case SET_a16: {
				int off = fetch(PC++, P0);
				poke(Acc, Sn[2] - off, P1);
				} break;
			case BLCKGET_a16: {
				int addr  = fetch(PC++, P0);
				    addr |= fetch(PC++, P0) << 8;
				int count = Rn[0];

				for (int off = 0, r = 0; r < count && r < 16; off+=2 && ++r) {
					Rn[r] = peek(addr+off, P1);
				}
				} break;
			case BLCKSET_a16: {
				int addr  = fetch(PC++, P0);
				    addr |= fetch(PC++, P0) << 8;
				int count = Rn[0];
				for (int off = 0, r = 0; r < count && r < 16; off+=2 && ++r) {
					poke(Rn[r], addr+off, P1);
				}
				} break;
			case BLCKGET_Sn: {
				int idx  = fetch(PC++, P0);
				int addr = Sn[idx & 0b11];
				int count = Rn[0];

				for (int off = 0, r = 0; r < count && r < 16; off+=2 && ++r) {
					Rn[r] = peek(addr+off, P1);
				}
				} break;
			case BLCKSET_Sn: {
				int idx  = fetch(PC++, P0);
				int addr = Sn[idx & 0b11];
				int count = Rn[0];
				for (int off = 0, r = 0; r < count && r < 16; off+=2 && ++r) {
					poke(Rn[r], addr+off, P1);
				}
				} break;
			case LD_A_Rn: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0xF;
				Acc = Rn[n0];
				} break;
			case LD_Rn_A: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0xF;
				Rn[n0] = Acc;
				} break;
			case LD_A_Sn: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0b11;
				Acc = Sn[n0];
				} break;
			case LD_Sn_A: {
				int idx = fetch(PC++, P0);
				int n0  = idx & 0b11;
				Sn[n0] = Acc;
				} break;
			case LD_Rn_Sn: {
				int n0  = fetch(PC++, P0) & 0xF;
				int n1  = fetch(PC++, P0) & 0b11;

				Rn[n0] = Sn[n1];
				} break;
			case LD_Sn_Rn: {
				int n0  = fetch(PC++, P0) & 0b11;
				int n1  = fetch(PC++, P0) & 0b11;

				Sn[n0] = Sn[n1];
				} break;
			case LDI_A_i16: {
				int i16  = fetch(PC++, P0);
				    i16 |= fetch(PC++, P0) << 8;
				Acc = i16;
				} break;
			case LDI_Rn_i16: {
				int idx = fetch(PC++, P0) & 0xF;
				int i16  = fetch(PC++, P0);
				    i16 |= fetch(PC++, P0) << 8;
				Rn[idx] = i16;
				} break;
			case LDI_Sn_i16: {
				int idx = fetch(PC++, P0) & 0b11;
				int i16  = fetch(PC++, P0);
				    i16 |= fetch(PC++, P0) << 8;
				Sn[idx] = i16;
				} break;

			// ADDITION
			case ADD_i16: {
				int addr  = fetch(PC++, P0);
				    addr |= fetch(PC++, P0) << 8;
				Tmp = Acc;
				Res = Acc + peek(addr, P1);
				flags();
				Acc = Res;
				}
				break;
			case ADD_Rn_A: {
				int idx = fetch(PC++, P0) & 0xF;
				Tmp = Acc;
				Res = Acc + peek(Rn[idx], P1);
				flags();
				Acc = Res;
				}
				break;
			case ADD_Sn_A: {
				int idx = fetch(PC++, P0) & 0b11;
				Tmp = Acc;
				Res = Acc + peek(Sn[idx], P1);
				flags();
				Acc = Res;
				}
				break;
			case ADD_i16_imm: {
				int x  = fetch(PC++, P0);
				    x |= fetch(PC++, P0) << 8;
				Tmp = Acc;
				Res = Acc + x;
				flags();
				Acc = Res;
				}
				break;
			case ADD_Rn: {
				int idx = fetch(PC++, P0) & 0xF;
				Tmp = Acc;
				Res = Acc + Rn[idx];
				flags();
				Acc = Res;
				}
				break;
			case ADD_Sn: {
				int idx = fetch(PC++, P0) & 0b11;
				Tmp = Acc;
				Res = Acc + Sn[idx];
				flags();
				Acc = Res;
				}
				break;

			// SUBTRACTION
			case SUB_i16: {
				int addr  = fetch(PC++, P0);
				    addr |= fetch(PC++, P0) << 8;
				Tmp = Acc;
				Res = Acc - peek(addr, P1);
				flags();
				Acc = Res;
				}
				break;
			case SUB_Rn_A: {
				int idx = fetch(PC++, P0) & 0xF;
				Tmp = Acc;
				Res = Acc - peek(Rn[idx], P1);
				flags();
				Acc = Res;
				}
				break;
			case SUB_Sn_A: {
				int idx = fetch(PC++, P0) & 0b11;
				Tmp = Acc;
				Res = Acc - peek(Sn[idx], P1);
				flags();
				Acc = Res;
				}
				break;
			case SUB_i16_imm: {
				int x  = fetch(PC++, P0);
				    x |= fetch(PC++, P0) << 8;
				Tmp = Acc;
				Res = Acc - x;
				flags();
				Acc = Res;
				}
				break;
			case SUB_Rn: {
				int idx = fetch(PC++, P0) & 0xF;
				Tmp = Acc;
				Res = Acc - Rn[idx];
				flags();
				Acc = Res;
				}
				break;
			case SUB_Sn: {
				int idx = fetch(PC++, P0) & 0b11;
				Tmp = Acc;
				Res = Acc - Sn[idx];
				flags();
				Acc = Res;
				}
				break;
			
			// COMPARISON
			case CMP_i16: {
				int addr  = fetch(PC++, P0);
				    addr |= fetch(PC++, P0) << 8;
				Tmp = Acc;
				Res = Acc - peek(addr, P1);
				flags();
				}
				break;
			case CMP_Rn_A: {
				int idx = fetch(PC++, P0) & 0xF;
				Tmp = Acc;
				Res = Acc - peek(Rn[idx], P1);
				flags();
				}
				break;
			case CMP_Sn_A: {
				int idx = fetch(PC++, P0) & 0b11;
				Tmp = Acc;
				Res = Acc - peek(Sn[idx], P1);
				flags();
				}
				break;
			case CMP_i16_imm: {
				int x  = fetch(PC++, P0);
				    x |= fetch(PC++, P0) << 8;
				Tmp = Acc;
				Res = Acc - x;
				flags();
				}
				break;
			case CMP_Rn: {
				int idx = fetch(PC++, P0) & 0xF;
				Tmp = Acc;
				Res = Acc - Rn[idx];
				flags();
				}
				break;
			case CMP_Sn: {
				int idx = fetch(PC++, P0) & 0b11;
				Tmp = Acc;
				Res = Acc - Sn[idx];
				flags();
				}
				break;

			// LOGICAL
			case NOT_A:
				Acc = ~Acc;
				break;
			case NEG_A:
				Acc = -Acc;
				break;

			case NOT_Rn: {
				int idx = fetch(PC++, P0) & 0xF;
				Acc = ~Rn[idx];
				} break;
			case NEG_Rn: {
				int idx = fetch(PC++, P0) & 0xF;
				Acc = -Rn[idx];
				} break;

			case NOT_Rn_mem: {
				int idx = fetch(PC++, P0) & 0xF;
				poke(~peek(Sn[idx], P1), Sn[idx], P1);
				} break;
			case NEG_Rn_mem: {
				int idx = fetch(PC++, P0) & 0xF;
				poke(-peek(Sn[idx], P1), Sn[idx], P1);
				} break;

			case NOT_Sn: {
				int idx = fetch(PC++, P0) & 0b11;
				poke(~peek(Sn[idx], P1), Sn[idx], P1);
				} break;
			case NEG_Sn: {
				int idx = fetch(PC++, P0) & 0b11;
				poke(-peek(Sn[idx], P1), Sn[idx], P1);
				} break;
			
			// AND
			case AND_i16: {
				int addr  = fetch(PC++, P0);
				    addr |= fetch(PC++, P0) << 8;
				Tmp = Acc;
				Res = Acc & peek(addr, P1);
				Acc = Res;
				}
				break;
			case AND_Rn: {
				int idx = fetch(PC++, P0) & 0xF;
				Tmp = Acc;
				Res = Acc & peek(Rn[idx], P1);
				Acc = Res;
				}
				break;
			case AND_Sn: {
				int idx = fetch(PC++, P0) & 0b11;
				Tmp = Acc;
				Res = Acc & peek(Sn[idx], P1);
				Acc = Res;
				}
				break;
			case AND_i16_imm: {
				int x  = fetch(PC++, P0);
				    x |= fetch(PC++, P0) << 8;
				Tmp = Acc;
				Res = Acc & x;
				Acc = Res;
				}
				break;
			case AND_Rn_reg: {
				int idx = fetch(PC++, P0) & 0xF;
				Tmp = Acc;
				Res = Acc & Rn[idx];
				Acc = Res;
				}
				break;

			// OR
			case OR_i16: {
				int addr  = fetch(PC++, P0);
				    addr |= fetch(PC++, P0) << 8;
				Tmp = Acc;
				Res = Acc | peek(addr, P1);
				Acc = Res;
				}
				break;
			case OR_Rn: {
				int idx = fetch(PC++, P0) & 0xF;
				Tmp = Acc;
				Res = Acc | peek(Rn[idx], P1);
				Acc = Res;
				}
				break;
			case OR_Sn: {
				int idx = fetch(PC++, P0) & 0b11;
				Tmp = Acc;
				Res = Acc | peek(Sn[idx], P1);
				Acc = Res;
				}
				break;
			case OR_i16_imm: {
				int x  = fetch(PC++, P0);
				    x |= fetch(PC++, P0) << 8;
				Tmp = Acc;
				Res = Acc | x;
				Acc = Res;
				}
				break;
			case OR_Rn_reg: {
				int idx = fetch(PC++, P0) & 0xF;
				Tmp = Acc;
				Res = Acc | Rn[idx];
				Acc = Res;
				}
				break;

			// XOR
			case XOR_i16: {
				int addr  = fetch(PC++, P0);
				    addr |= fetch(PC++, P0) << 8;
				Tmp = Acc;
				Res = Acc ^ peek(addr, P1);
				Acc = Res;
				}
				break;
			case XOR_Rn: {
				int idx = fetch(PC++, P0) & 0xF;
				Tmp = Acc;
				Res = Acc ^ peek(Rn[idx], P1);
				Acc = Res;
				}
				break;
			case XOR_Sn: {
				int idx = fetch(PC++, P0) & 0b11;
				Tmp = Acc;
				Res = Acc ^ peek(Sn[idx], P1);
				Acc = Res;
				}
				break;
			case XOR_i16_imm: {
				int x  = fetch(PC++, P0);
				    x |= fetch(PC++, P0) << 8;
				Tmp = Acc;
				Res = Acc ^ x;
				Acc = Res;
				}
				break;
			case XOR_Rn_reg: {
				int idx = fetch(PC++, P0) & 0xF;
				Tmp = Acc;
				Res = Acc ^ Rn[idx];
				Acc = Res;
				}
				break;
			
			// JUMPING AND CALLING
U_JUMP_LA:
			case JUMP_a16: {
				int x  = fetch(PC++, P0);
				    x |= fetch(PC++, P0) << 8;
				PC = x;
				}
				break;
			case JUMP_Rn: {
				int i  = fetch(PC++, P0) & 0xF;
				PC = Rn[i];
				}
				break;

			case FAR_JUMP_a24: {
				int x  = fetch(PC++, P0);
				    x |= fetch(PC++, P0) << 8;
				P0 = fetch(PC++, P0);
				PC = x;
				}
				break;
R_JUMP_LA:
			case REL_JUMP_i8: {
				int x = fetch(PC++, P0);
				if (x >> 7) {
					x = (x & 0b1111111);
					PC -= x;
				} else {
					PC += x;
				}
				}
				break;
			
			case REL_JMZ_i8: {
				if (zero) {
					goto R_JUMP_LA;
				}
				PC += 1;
				} break;
			case REL_JMC_i8: {
				if (carry) {
					goto R_JUMP_LA;
				}
				PC += 1;
				} break;
			
			case JMZ_a16: {
				if (zero) {
					goto U_JUMP_LA;
				}
				PC += 2;
				} break;
			case JMC_a16: {
				if (carry) {
					goto U_JUMP_LA;
				}
				PC += 2;
				} break;
			case JP_a16: {
				if (parity) {
					goto U_JUMP_LA;
				}
				PC += 2;
				} break;
			case JNZ_a16: {
				if (!zero == true) {
					goto U_JUMP_LA;
				}
				PC += 2;
				} break;
			case JNC_a16: {
				if (!carry == true) {
					goto U_JUMP_LA;
				}
				PC += 2;
				} break;
			case JNP_a16: {
				if (!parity == true) {
					goto U_JUMP_LA;
				}
				PC += 2;
				} break;
			case CALL_a16: {
U_CALL_LA:
				int x  = fetch(PC++, P0);
				    x |= fetch(PC++, P0) << 8;
				write(Sn[3]--, 0xFF, PC);
				write(Sn[3]--, 0xFF, PC >> 8);
				PC = x;
				}
				break;
			case FAR_CALL_a24: {
				int x  = fetch(PC++, P0);
				    x |= fetch(PC++, P0) << 8;
				write(Sn[3]--, 0xFF, PC);
				write(Sn[3]--, 0xFF, PC >> 8);
				write(Sn[3]--, 0xFF, P0);
				P0 = fetch(PC++, P0);
				PC = x;
				}
				break;

			case CALZ_a16: {
				if (zero == true) {
					goto U_CALL_LA;
				}
				PC += 2;
				} break;
			case CALC_a16: {
				if (carry == true) {
					goto U_CALL_LA;
				}
				PC += 2;
				} break;

			case CALL_Rn: {
				int i  = fetch(PC++, P0) & 0xF;
				push(PC);
				PC = Rn[i];
				}
				break;

			case RET: {
U_RET:
				PC  = fetch(++Sn[3], 0xFF) << 8;
				PC |= fetch(++Sn[3], 0xFF);
				} break;
			case FAR_RET: {
				P0  = fetch(++Sn[3], 0xFF);
				PC  = fetch(++Sn[3], 0xFF) << 8;
				PC |= fetch(++Sn[3], 0xFF);
				} break;

			case RETZ: {
				if (zero == true)
					goto U_RET;
				} break;
			case RETC: {
				if (carry == true)
					goto U_RET;
				} break;
			
			// OTHER
			case SETFORMAT_i8: {
				data_format = fetch(PC++, P0) & 1;
				} break;
			case OUT: {
				IO[Sn[0]] = Acc;
				}
				break;
			case IN: {
				Acc = IO[Sn[0]];
				IO[Sn[0]] = 0;
				}
				break;
			case CLI:
				interrupt_mask = false;
				break;
			case STI:
				interrupt_mask = true;
				break;
			
			case LDR_Rn0_Rn1: {
				int n0  = fetch(PC++, P0) & 0xF;
				int n1  = fetch(PC++, P0) & 0xF;

				Rn[n0] = peek(Rn[n1], P1);
				} break;
			case STR_Rn0_Rn1: {
				int n0  = fetch(PC++, P0) & 0xF;
				int n1  = fetch(PC++, P0) & 0xF;

				poke(Rn[n1], Rn[n0]);
				} break;

			case INC_Rn: {
				int idx = fetch(PC++, P0) & 0xF;
				Tmp = Rn[idx];
				Res = Rn[idx] + 1;
				flags();
				Rn[idx] = Res;
			} break;

			case DEC_Rn: {
				int idx = fetch(PC++, P0) & 0xF;
				Tmp = Rn[idx];
				Res = Rn[idx] - 1;
				flags();
				Rn[idx] = Res;
			} break;

			case DEC_Sn: {
				int idx = fetch(PC++, P0) & 0b11;
				Tmp = Sn[idx];
				Res = Sn[idx] - 1;
				flags();
				Sn[idx] = Res;
			} break;

			case INC_Sn: {
				int idx = fetch(PC++, P0) & 0b11;
				Tmp = Sn[idx];
				Res = Sn[idx] + 1;
				flags();
				Sn[idx] = Res;
			} break;

			case INC_Rn_AT: {
				int idx = fetch(PC++, P0) & 0xF;
				int old = peek(Rn[idx]);
				poke(old+1, Rn[idx]);
			} break;

			case DEC_Rn_AT: {
				int idx = fetch(PC++, P0) & 0xF;
				int old = peek(Rn[idx]);
				poke(old-1, Rn[idx]);
			} break;

			case DEC_Sn_AT: {
				int idx = fetch(PC++, P0) & 0b11;
				int old = peek(Rn[idx]);
				poke(old-1, Sn[idx]);
			} break;

			case INC_Sn_AT: {
				int idx = fetch(PC++, P0) & 0b11;
				int old = peek(Sn[idx]);
				poke(old+1, Sn[idx]);
			} break;

			case INC_A:
				++Acc;
				break;
			case DEC_A:
				--Acc;
				break;

			case NEAR_POKE_Rn: {
				int idx0 = (fetch(PC++, P0)) & 0xF;
				int idx1 = (fetch(PC++, P0)) & 0b11;
				poke(Rn[idx0], Sn[idx1], P0);
			} break;

			case NEAR_PEEK_Rn: {
				int idx0 = (fetch(PC++, P0)) & 0xF;
				int idx1 = (fetch(PC++, P0)) & 0b11;
				Rn[idx0] = peek(Sn[idx1], P0);
			} break;

			case SHL_R: {
				int idx = fetch(PC++, P0) & 0xF;
				Tmp = Acc;
				Res = Acc << Rn[idx];
				Acc = Res;
				}
				break;
			
			case SHR_R: {
				int idx = fetch(PC++, P0) & 0xF;
				Tmp = Acc;
				Res = Acc >> Rn[idx];
				Acc = Res;
				}
				break;

			case ADD_Rn_i16:
			{
				int idx0 = (fetch(PC++, P0)) & 0xF;
				int i16 = (fetch(PC++, P0));
				    i16|= (fetch(PC++, P0)) << 8;
				Tmp = Rn[idx0];
				Res = Rn[idx0] + i16;
				flags();
				Rn[idx0] = Res;
			} break;

			case SUB_Rn_i16:
			{
				int idx0 = (fetch(PC++, P0)) & 0xF;
				int i16 = (fetch(PC++, P0));
				    i16|= (fetch(PC++, P0)) << 8;
				Tmp = Rn[idx0];
				Res = Rn[idx0] - i16;
				flags();
				Rn[idx0] = Res;
			} break;

			case CMP_Rn_i16:
			{
				int idx0 = (fetch(PC++, P0)) & 0xF;
				int i16 = (fetch(PC++, P0));
				    i16|= (fetch(PC++, P0)) << 8;
				Tmp = Rn[idx0];
				Res = Rn[idx0] - i16;
				flags();
			} break;

			case ADD_Rn1_Rn2:
			{
				int idx0 = (fetch(PC++, P0)) & 0xF;
				int idx1 = (fetch(PC++, P0)) & 0xF;
				Tmp = Rn[idx0];
				Res = Rn[idx0] + Rn[idx1];
				flags();
				Rn[idx0] = Res;
			} break;

			case SUB_Rn1_Rn2:
			{
				int idx0 = (fetch(PC++, P0)) & 0xF;
				int idx1 = (fetch(PC++, P0)) & 0xF;
				Tmp = Rn[idx0];
				Res = Rn[idx0] - Rn[idx1];
				flags();
				Rn[idx0] = Res;
			} break;

			case CMP_Rn1_Rn2:
			{
				int idx0 = (fetch(PC++, P0)) & 0xF;
				int idx1 = (fetch(PC++, P0)) & 0xF;
				Tmp = Rn[idx0];
				Res = Rn[idx0] - Rn[idx1];
				flags();
			} break;

			case AND_Rn1_Rn2:
			{
				int idx0 = (fetch(PC++, P0)) & 0xF;
				int idx1 = (fetch(PC++, P0)) & 0xF;
				Rn[idx0] &= Rn[idx1];
			} break;

			case OR_Rn1_Rn2:
			{
				int idx0 = (fetch(PC++, P0)) & 0xF;
				int idx1 = (fetch(PC++, P0)) & 0xF;
				Rn[idx0] |= Rn[idx1];
			} break;

			case NAND_Rn1_Rn2:
			{
				int idx0 = (fetch(PC++, P0)) & 0xF;
				int idx1 = (fetch(PC++, P0)) & 0xF;
				Rn[idx0] &= ~Rn[idx1];
			} break;

			case XOR_Rn1_Rn2:
			{
				int idx0 = (fetch(PC++, P0)) & 0xF;
				int idx1 = (fetch(PC++, P0)) & 0xF;
				Rn[idx0] ^= Rn[idx1];
			} break;

			case LD_Rn_Rn:
			{
				int idx0 = (fetch(PC++, P0)) & 0xF;
				int idx1 = (fetch(PC++, P0)) & 0xF;
				Rn[idx0] = Rn[idx1];
			} break;

			case INT_i8:
			{
				interrupt(fetch(PC++, P0));
			} break;

			case INT_Rn:
			{
				interrupt(Rn[fetch(PC++, P0) & 0xF]);
			} break;

			case PEEK_A_Sn_SRn:
			{
				int Ridx = fetch(PC++, P0) & 0xF;
				Acc = peek(Sn[0] - Rn[Ridx], P1);
			} break;

			case PEEK_A_Sn_ARn:
			{
				int Ridx = fetch(PC++, P0) & 0xF;
				Acc = peek(Sn[0] + Rn[Ridx], P1);
			} break;

			case POKE_A_Sn_SRn:
			{
				int Ridx = fetch(PC++, P0) & 0xF;
				poke(Acc, Sn[0] - Rn[Ridx], P1);
			} break;

			case POKE_A_Sn_ARn:
			{
				int Ridx = fetch(PC++, P0) & 0xF;
				poke(Acc, Sn[0] + Rn[Ridx], P1);
			} break;

			// LOOPS
			case REP: {
				++__LOC;
				__LADR[__LOC][0] = PC;
				__LADR[__LOC][1] = find_end_of_rep(++PC);
				if (PC == __LADR[__LOC][1]) break;
				while (true) {
					if (PC == __LADR[__LOC][1]) {
						PC = __LADR[__LOC][0];
						if (zero) break;
					}
					else {
						executeNext();
					}
				}
				--__LOC;
			} break;

			case END: {
				break;
			}

			default:
				printf("Invalid Opcode\n");
				return;
		}
	}

	void load_from_file(const char* path, int off)
	{
		FILE* fp = fopen(path, "rb");
		fseek(fp, 0, SEEK_END);
		size_t len = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		if (len >= MAX_RAM) {
			fclose(fp);
			return;
		}

		size_t x = fread(&ram[off], 1, len, fp);
		printf("%lu bytes read\n", x);
		fclose(fp);
	}

	void display() {
		printf("PC: %.4x\n", PC);
		printf("A : %.4x   S0: %.4x   S1: %.4x   S2: %.4x   S3: %.4x\n", Acc, Sn[0], Sn[1], Sn[2], Sn[3]);
		printf("Te: %.4x   Re: %.4x   P0: %.4x   P1: %.4x\n", Tmp, Res, P0, P1);
		for (int i = 0; i < 8; i += 4) {
			printf("W%x: %.4x   W%x: %.4x   W%x: %.4x   W%x: %.4x\n", i, Rn[i], i+1, Rn[i+1], i+2, Rn[i+2], i+3, Rn[i+3]);
		}

		for (int i = 8; i < 16; i += 4) {
			printf("X%x: %.4x   X%x: %.4x   X%x: %.4x   X%x: %.4x\n", i-8, Rn[i], i-7, Rn[i+1], i-6, Rn[i+2], i-5, Rn[i+3]);
		}

		printf("STACK: (S2 - 8) TO (S2 + 8)\n");
		for (int i = Sn[2] - 8; i < Sn[2] + 8; i += 4) {
			int a = i;
			if (a >= MAX_RAM || a < 0) {
				// Wrap around logic (or clamping) should be fixed
				a = (a + MAX_RAM) % MAX_RAM;  // EnsuRes the addRess is wrapped correctly
			}
			printf("%.6x: %.2x   %.6x: %.2x   %.6x: %.2x   %.6x: %.2x\n", a, ram[a], a+1, ram[a+1], a+2, ram[a+2], a+3, ram[a+3]);
		}
	}
};
