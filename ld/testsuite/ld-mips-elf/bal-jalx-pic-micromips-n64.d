#name: microMIPS BAL/JALX in PIC mode (n64)
#source: ../../../gas/testsuite/gas/mips/branch-addend-micromips.s
#as: -EB -64 -march=from-abi
#ld: -EB -Ttext 0x1c000000 -e 0x1c000000 -shared
#error: \A[^\n]*: in function `bar':\n
#error:   \(\.text\+0x1014\): unsupported branch between ISA modes\Z
