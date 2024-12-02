// THIS IS THE VOP 2 CPU PROJECT,
// NOT BINARY COMPATIBLE WITH VOP 1

enum Opcodes {
	PUSH_A_SN = 0,
	POP_A_SN
};

struct CPU {
	Registers: [u16; 16];
};

fn main() {
	println!("Hello, World!");
}
