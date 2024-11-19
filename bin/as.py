from sys import argv

opcodes = {
	"PUSHA,S":0,
	"POPA,S":1,
	"POKEA,S":2,
	"PEEKA,S":3,
	"PUSHR,S":4,
	"POPR,S":5,
	"POKER,S":6,
	"PEEKR,S":7,
	"PUSH.#,S":8,
	"PUSH#,S":9,
	"PUSHP0,S":10,
	"PUSHP1,S":11,
	"POPP1,S":12,
	"PUSHF,S":13,
	"POPF,S":14,

	"NOP":16,
	"XCR,R":17,
	"XCR,S":18,
	"XCS,S":19,
	"XCA,S":20,
	"XCA,R":21,

	"STOA,#":22,
	"STOR,#":23,
	"LODA,#":24,
	"LODR,#":25,

	"STOA,F#":26,
	"STOR,F#":27,
	"LODA,F#":28,
	"LODR,F#":29,

	"GET#":30,
	"SET#":31,

	"GETB#":32,
	"SETB#":33,

	"GETS":0x90,
	"SETS":0x91,

	"LDA,R":0x22,
	"LDA,S":0x23,
	"LDR,A":0x24,
	"LDS,A":0x25,
	"LDR,S":0x26,
	"LDS,R":0x27,

	"LDR,#":0x28,
	"LDS,#":0x29,
	"LDA,#":0x2A,

	"ADD$#":0x2B,
	"ADD$S":0x2E,
	"ADD$R":0x2F,
	"ADD#":0x30,
	"ADDS":0x31,
	"ADDR":0x32,

	"SUB$#":0x33,
	"SUB$S":0x34,
	"SUB$R":0x35,
	"SUB#":0x36,
	"SUBS":0x37,
	"SUBR":0x38,

	"CMP$#":0x73,
	"CMP$S":0x74,
	"CMP$R":0x75,
	"CMP#":0x76,
	"CMPS":0x77,
	"CMPR":0x78,

	"NOT":57,
	"NEG":58,
	"NOTR":59,
	"NEGR":60,
	"NOT$R":61,
	"NEG$R":62,
	"NOT$S":63,
	"NEG$S":64,

	"AND$#":65,
	"AND$S":66,
	"AND$R":67,
	"AND#":68,
	"ANDR":69,

	"OR$#":70,
	"OR$S":71,
	"OR$R":72,
	"OR#":73,
	"ORR":74,

	"XOR$#":75,
	"XOR$S":76,
	"XOR$R":77,
	"XOR#":78,
	"XORR":79,

	"JMP#":0x54,
	"JMPR":0x55,
	"JMPF#":0x56,
	"JMP.#":0x57,
	"BZ.#":0x58,
	"BC.#":0x59,
	"BZ#":0x5A,
	"BC#":0x5B,
	"BP#":0x5C,
	"BNZ#":0x5D,
	"BNC#":0x5E,
	"BNP#":0x5F,

	"CALL#":0x60,
	"CALLF#":0x61,
	"CZ#":0x62,
	"CC#":0x63,
	"CALLR":0x64,

	"RET":0x66,
	"RETF":0x67,
	"RETZ":0x68,
	"RETC":0x69,

	"FORMAT.#":0x6A,
	"OUT":0x6B,
	"IN":0x6C,
	"INT.#":0x6D,
	"INTR":0x6E,
	"CLI":0x6F,
	"STI":0x70,
	"LDR,$R":0x71,
	"STR,$R":0x72,

	"INCR":0x80,
	"DECR":0x81,
	"INCS":0x82,
	"DECS":0x83,

	"INC$R":0x84,
	"DEC$R":0x85,
	"INC$S":0x86,
	"DEC$S":0x87,

	"INCA":0x88,
	"DECA":0x89,

	"POKER,.S":146,
	"PEEKR,.S":147,
	
	"REP":0xF0,
	"END":0xF1,
}

def decode(_op, labels):
	idx = []
	tmp = _op.split("\\")
	
	if "," in _op:
		tmp = tmp[1].split(",")
	
	for i in range(len(tmp)):
		tmp[i] = tmp[i].strip()
		
	if "," in _op:
		op1 = [_op.split("\\")[0], tmp[0], tmp[1]]
	elif len(tmp) > 1:
		op1 = [_op.split("\\")[0], tmp[1]]
	else:
		op1 = _op.split("\\")
	
	retstr = op1[0]
	for i in range(len(op1)):
		op = op1
		if i == 0:
			continue
		for x in range(8):
			if str(op[i]) == f"W{x}":
				retstr += "R"
				idx.append(x)
				x = 8
			elif str(op[i]) == f"X{x}":
				retstr += "R"
				idx.append(x + 8)
				x = 8
			elif str(op[i]) == f"S{x}":
				retstr += "S"
				idx.append(x)
				x = 8
			elif str(op[i]) == f"A":
				retstr += "A"
				break
			elif str(op[i])[0] == f"P":
				retstr += "P1"
				break
			elif str(op[i])[0] == f"#":
				retstr += "#"+str(str(op[i])[1:])
				break
			elif str(op[i])[0] == f"B":
				retstr += "B#"+str(str(op[i])[2:])
				break
			elif str(op[i])[0] == f"F":
				retstr += "F#"+str(str(op[i])[2:])
				break
			elif str(op[i])[0] == f".":
				retstr += str(str(op[i]))
				break
			elif str(op[i])[0] == f"%":
				# if not found, assume in first pass
				if str(op[i])[1:] in labels:
					retstr += "#"+str(labels[str(op[i])[1:]])
				else:
					retstr += "#0"
				break
			elif str(op[i])[0] == f"$":
				__op = op[i][1:]
				if str(__op) == f"W{x}":
					retstr += "$R"
					idx.append(x)
					break
				elif str(__op) == f"T{x}":
					retstr += "$R"
					idx.append(x + 8)
					break
				elif str(__op) == f"S{x}":
					retstr += "$S"
					idx.append(x)
					break
				elif str(__op) == f"A":
					retstr += "$A"
					break
		if i < len(op)-1:
			retstr += ","

	return retstr, idx

def get_opcode(text, labels):
	_op = ["\\".join(text.split(" ", 1))][0].strip()
	_op = _op.upper()
	op = _op

	op, idx = decode(op, labels)
	bytearr = []
	
	if '.' in op and '#' not in op:
		_idx = decode("TEMP:\\" + op.split(".")[1], labels)
		op = op.split(".")[0] + "." + _idx[0].split("TEMP:")[1]
		idx.append(_idx[1][0])
	if '#' in op:
		opcode = ""
		operands = []
		if ',' in op and len(op.split("#")[1].split(",")) > 1:
			opcode = op.split("#")[0] + '#,' + op.split("#")[1].split(",")[1]
			operands = [op.split("#")[1].split(",")[0]]
		#	print(opcode, operands)
		else:
			opcode = op.split("#")[0] + '#'
			operands = [op.split("#")[1]]
		#	print(opcode, operands)

		bytearr.append(opcodes[opcode])
		for x in idx:
			bytearr.append(x)
		for operand in operands:
			if '.' in op:
				bytearr.append(int(operand) & 255)
			elif 'F' in op:
				bytearr.append(int(operand) & 255)
				bytearr.append((int(operand) >> 8) & 255)
				bytearr.append((int(operand) >> 16) & 255)
			else:
				bytearr.append(int(operand) & 255)
				bytearr.append((int(operand) >> 8) & 255)
	elif '%' in op:
		print("ERR:", op)
	else:
		bytearr.append(opcodes[op])
		for x in idx:
			bytearr.append(x)
	sz = len(bytearr)
	return sz, bytearr

def first_pass(text):
	labels = {}
	byteOff = 0
	for l in text.split("\n"):
		if l:
			l = l.strip()
			if l[0] == ';' or l[0] == '!':
				continue
			elif l[-1] == ':':
				labels[l[0:-1].upper()] = byteOff
				continue
			elif l.split(" ")[0] == "org":
				byteOff = int(l.split(" ")[1])
				continue
			elif l.split(" ")[0] == "db":
				byteOff += 1
				continue
			elif l.split(" ")[0] == "define":
				labels[l.split(" ")[1].upper()] = int(l.split(" ")[2])
				continue
			elif l.split("\"")[0].strip() == "ds":
				for c in l.split("\"")[1]:
					byteOff += 1
				continue
			else:
				byteOff += len(get_opcode(l, labels)[1])
	return labels

def second_pass(text, labels):
	byteOff = 0
	arr = []
	for l in text.split("\n"):
		if l:
			l = l.strip()
			if l[0] == ';' or l[0] == '!':
				continue
			elif l[-1] == ':':
				continue
			elif l.split(" ")[0] == "org":
				byteOff = int(l.split(" ")[1])
				continue
			elif l.split(" ")[0] == "define":
				continue
			elif l.split(" ")[0] == "db":
				byteOff += 1
				arr.append(int(l.split(" ")[1]))
				continue
			elif l.split("\"")[0].strip() == "ds":
				for c in l.split("\"")[1]:
					arr.append(ord(c))
					byteOff += 1
				continue
			else:
				data = get_opcode(l, labels)
				byteOff += data[0]
				for x in data[1]:
					arr.append(x)
	return arr

for i in range(len(argv)):
	if argv[i] == "-s":
		if i < len(argv)-2:
			inputf = argv[i+1]
			outf = argv[i+2]

			readFile = open(inputf, "r")
			writeFile = open(outf, "wb")

			text = readFile.read()
			readFile.close()

			labels = first_pass(text)
			out = second_pass(text, labels)

			writeFile.write(bytearray(out))
			writeFile.close()
			i += 2
		else:
			print("Invalid Argument")
			exit(1)
