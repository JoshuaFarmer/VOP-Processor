# simple tests
python3 as.py -s assembly/hi.asm bin/hi.vop
python3 as.py -s assembly/hi_console.asm bin/hi_con.vop
python3 as.py -s assembly/type.asm bin/type.vop
python3 as.py -s assembly/get.asm bin/get.vop
python3 as.py -s assembly/mul.asm bin/mul.vop
python3 as.py -s assembly/relative.asm bin/relative.vop

# OS
cd assembly/os
python3 ../../as.py -s os.asm ../../bin/os.vop
cd ../../
