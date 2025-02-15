# Emulator
cd vop16
sh make.sh
cd ..
echo Built Emulator

# Assembly
python3 assembler.py -s assembly/hi.asm bin/hi.vop
python3 assembler.py -s assembly/hi_console.asm bin/hi_con.vop
python3 assembler.py -s assembly/type.asm bin/type.vop
python3 assembler.py -s assembly/get.asm bin/get.vop
python3 assembler.py -s assembly/mul.asm bin/mul.vop
python3 assembler.py -s assembly/relative.asm bin/relative.vop
python3 assembler.py -s assembly/div10.asm bin/div10.vop
python3 assembler.py -s assembly/atoi.asm bin/atoi.vop

python3 assembler2.0.py -s assembly/test2.asm bin/test2.vop

# OS
cd assembly/os
python3 ../../assembler.py -s os.asm ../../bin/os.vop
cd ../..
echo Built Tests