/* Target-dependent code for S390.
   Copyright (C) 2017 Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef S390_TDEP_H
#define S390_TDEP_H

/* Holds the current set of options to be passed to the disassembler.  */
static char *s390_disassembler_options;

enum s390_abi_kind
{
  ABI_LINUX_S390,
  ABI_LINUX_ZSERIES
};

enum s390_vector_abi_kind
{
  S390_VECTOR_ABI_NONE,
  S390_VECTOR_ABI_128
};

/* The tdep structure.  */

struct gdbarch_tdep
{
  /* ABI version.  */
  enum s390_abi_kind abi;

  /* Vector ABI.  */
  enum s390_vector_abi_kind vector_abi;

  /* Pseudo register numbers.  */
  int gpr_full_regnum;
  int pc_regnum;
  int cc_regnum;
  int v0_full_regnum;

  int have_linux_v1;
  int have_linux_v2;
  int have_tdb;
};

/* Named opcode values for the S/390 instructions we recognize.  Some
   instructions have their opcode split across two fields; those are the
   op1_* and op2_* enums.  */

enum
  {
    op1_lhi  = 0xa7,   op2_lhi  = 0x08,
    op1_lghi = 0xa7,   op2_lghi = 0x09,
    op1_lgfi = 0xc0,   op2_lgfi = 0x01,
    op_lr    = 0x18,
    op_lgr   = 0xb904,
    op_l     = 0x58,
    op1_ly   = 0xe3,   op2_ly   = 0x58,
    op1_lg   = 0xe3,   op2_lg   = 0x04,
    op_lm    = 0x98,
    op1_lmy  = 0xeb,   op2_lmy  = 0x98,
    op1_lmg  = 0xeb,   op2_lmg  = 0x04,
    op_st    = 0x50,
    op1_sty  = 0xe3,   op2_sty  = 0x50,
    op1_stg  = 0xe3,   op2_stg  = 0x24,
    op_std   = 0x60,
    op_stm   = 0x90,
    op1_stmy = 0xeb,   op2_stmy = 0x90,
    op1_stmg = 0xeb,   op2_stmg = 0x24,
    op1_aghi = 0xa7,   op2_aghi = 0x0b,
    op1_ahi  = 0xa7,   op2_ahi  = 0x0a,
    op1_agfi = 0xc2,   op2_agfi = 0x08,
    op1_afi  = 0xc2,   op2_afi  = 0x09,
    op1_algfi= 0xc2,   op2_algfi= 0x0a,
    op1_alfi = 0xc2,   op2_alfi = 0x0b,
    op_ar    = 0x1a,
    op_agr   = 0xb908,
    op_a     = 0x5a,
    op1_ay   = 0xe3,   op2_ay   = 0x5a,
    op1_ag   = 0xe3,   op2_ag   = 0x08,
    op1_slgfi= 0xc2,   op2_slgfi= 0x04,
    op1_slfi = 0xc2,   op2_slfi = 0x05,
    op_sr    = 0x1b,
    op_sgr   = 0xb909,
    op_s     = 0x5b,
    op1_sy   = 0xe3,   op2_sy   = 0x5b,
    op1_sg   = 0xe3,   op2_sg   = 0x09,
    op_nr    = 0x14,
    op_ngr   = 0xb980,
    op_la    = 0x41,
    op1_lay  = 0xe3,   op2_lay  = 0x71,
    op1_larl = 0xc0,   op2_larl = 0x00,
    op_basr  = 0x0d,
    op_bas   = 0x4d,
    op_bcr   = 0x07,
    op_bc    = 0x0d,
    op_bctr  = 0x06,
    op_bctgr = 0xb946,
    op_bct   = 0x46,
    op1_bctg = 0xe3,   op2_bctg = 0x46,
    op_bxh   = 0x86,
    op1_bxhg = 0xeb,   op2_bxhg = 0x44,
    op_bxle  = 0x87,
    op1_bxleg= 0xeb,   op2_bxleg= 0x45,
    op1_bras = 0xa7,   op2_bras = 0x05,
    op1_brasl= 0xc0,   op2_brasl= 0x05,
    op1_brc  = 0xa7,   op2_brc  = 0x04,
    op1_brcl = 0xc0,   op2_brcl = 0x04,
    op1_brct = 0xa7,   op2_brct = 0x06,
    op1_brctg= 0xa7,   op2_brctg= 0x07,
    op_brxh  = 0x84,
    op1_brxhg= 0xec,   op2_brxhg= 0x44,
    op_brxle = 0x85,
    op1_brxlg= 0xec,   op2_brxlg= 0x45,
    op_svc   = 0x0a,
  };

/* Hardware capabilities. */

#ifndef HWCAP_S390_HIGH_GPRS
#define HWCAP_S390_HIGH_GPRS 512
#endif

#ifndef HWCAP_S390_TE
#define HWCAP_S390_TE 1024
#endif

#ifndef HWCAP_S390_VX
#define HWCAP_S390_VX 2048
#endif

/* Register information.  */

/* Program Status Word.  */
#define S390_PSWM_REGNUM 0
#define S390_PSWA_REGNUM 1
/* General Purpose Registers.  */
#define S390_R0_REGNUM 2
#define S390_R1_REGNUM 3
#define S390_R2_REGNUM 4
#define S390_R3_REGNUM 5
#define S390_R4_REGNUM 6
#define S390_R5_REGNUM 7
#define S390_R6_REGNUM 8
#define S390_R7_REGNUM 9
#define S390_R8_REGNUM 10
#define S390_R9_REGNUM 11
#define S390_R10_REGNUM 12
#define S390_R11_REGNUM 13
#define S390_R12_REGNUM 14
#define S390_R13_REGNUM 15
#define S390_R14_REGNUM 16
#define S390_R15_REGNUM 17
/* Access Registers.  */
#define S390_A0_REGNUM 18
#define S390_A1_REGNUM 19
#define S390_A2_REGNUM 20
#define S390_A3_REGNUM 21
#define S390_A4_REGNUM 22
#define S390_A5_REGNUM 23
#define S390_A6_REGNUM 24
#define S390_A7_REGNUM 25
#define S390_A8_REGNUM 26
#define S390_A9_REGNUM 27
#define S390_A10_REGNUM 28
#define S390_A11_REGNUM 29
#define S390_A12_REGNUM 30
#define S390_A13_REGNUM 31
#define S390_A14_REGNUM 32
#define S390_A15_REGNUM 33
/* Floating Point Control Word.  */
#define S390_FPC_REGNUM 34
/* Floating Point Registers.  */
#define S390_F0_REGNUM 35
#define S390_F1_REGNUM 36
#define S390_F2_REGNUM 37
#define S390_F3_REGNUM 38
#define S390_F4_REGNUM 39
#define S390_F5_REGNUM 40
#define S390_F6_REGNUM 41
#define S390_F7_REGNUM 42
#define S390_F8_REGNUM 43
#define S390_F9_REGNUM 44
#define S390_F10_REGNUM 45
#define S390_F11_REGNUM 46
#define S390_F12_REGNUM 47
#define S390_F13_REGNUM 48
#define S390_F14_REGNUM 49
#define S390_F15_REGNUM 50
/* General Purpose Register Upper Halves.  */
#define S390_R0_UPPER_REGNUM 51
#define S390_R1_UPPER_REGNUM 52
#define S390_R2_UPPER_REGNUM 53
#define S390_R3_UPPER_REGNUM 54
#define S390_R4_UPPER_REGNUM 55
#define S390_R5_UPPER_REGNUM 56
#define S390_R6_UPPER_REGNUM 57
#define S390_R7_UPPER_REGNUM 58
#define S390_R8_UPPER_REGNUM 59
#define S390_R9_UPPER_REGNUM 60
#define S390_R10_UPPER_REGNUM 61
#define S390_R11_UPPER_REGNUM 62
#define S390_R12_UPPER_REGNUM 63
#define S390_R13_UPPER_REGNUM 64
#define S390_R14_UPPER_REGNUM 65
#define S390_R15_UPPER_REGNUM 66
/* GNU/Linux-specific optional registers.  */
#define S390_ORIG_R2_REGNUM 67
#define S390_LAST_BREAK_REGNUM 68
#define S390_SYSTEM_CALL_REGNUM 69
/* Transaction diagnostic block.  */
#define S390_TDB_DWORD0_REGNUM 70
#define S390_TDB_ABORT_CODE_REGNUM 71
#define S390_TDB_CONFLICT_TOKEN_REGNUM 72
#define S390_TDB_ATIA_REGNUM 73
#define S390_TDB_R0_REGNUM 74
#define S390_TDB_R1_REGNUM 75
#define S390_TDB_R2_REGNUM 76
#define S390_TDB_R3_REGNUM 77
#define S390_TDB_R4_REGNUM 78
#define S390_TDB_R5_REGNUM 79
#define S390_TDB_R6_REGNUM 80
#define S390_TDB_R7_REGNUM 81
#define S390_TDB_R8_REGNUM 82
#define S390_TDB_R9_REGNUM 83
#define S390_TDB_R10_REGNUM 84
#define S390_TDB_R11_REGNUM 85
#define S390_TDB_R12_REGNUM 86
#define S390_TDB_R13_REGNUM 87
#define S390_TDB_R14_REGNUM 88
#define S390_TDB_R15_REGNUM 89
/* Vector registers.  */
#define S390_V0_LOWER_REGNUM 90
#define S390_V1_LOWER_REGNUM 91
#define S390_V2_LOWER_REGNUM 92
#define S390_V3_LOWER_REGNUM 93
#define S390_V4_LOWER_REGNUM 94
#define S390_V5_LOWER_REGNUM 95
#define S390_V6_LOWER_REGNUM 96
#define S390_V7_LOWER_REGNUM 97
#define S390_V8_LOWER_REGNUM 98
#define S390_V9_LOWER_REGNUM 99
#define S390_V10_LOWER_REGNUM 100
#define S390_V11_LOWER_REGNUM 101
#define S390_V12_LOWER_REGNUM 102
#define S390_V13_LOWER_REGNUM 103
#define S390_V14_LOWER_REGNUM 104
#define S390_V15_LOWER_REGNUM 105
#define S390_V16_REGNUM 106
#define S390_V17_REGNUM 107
#define S390_V18_REGNUM 108
#define S390_V19_REGNUM 109
#define S390_V20_REGNUM 110
#define S390_V21_REGNUM 111
#define S390_V22_REGNUM 112
#define S390_V23_REGNUM 113
#define S390_V24_REGNUM 114
#define S390_V25_REGNUM 115
#define S390_V26_REGNUM 116
#define S390_V27_REGNUM 117
#define S390_V28_REGNUM 118
#define S390_V29_REGNUM 119
#define S390_V30_REGNUM 120
#define S390_V31_REGNUM 121
/* Control registers.  */
#define S390_TIMER_REGNUM 122
#define S390_TODCMP_REGNUM 123
#define S390_TODPREG_REGNUM 124
#define S390_CR0_REGNUM 125
#define S390_CR1_REGNUM 126
#define S390_CR2_REGNUM 127
#define S390_CR3_REGNUM 128
#define S390_CR4_REGNUM 129
#define S390_CR5_REGNUM 130
#define S390_CR6_REGNUM 131
#define S390_CR7_REGNUM 132
#define S390_CR8_REGNUM 133
#define S390_CR9_REGNUM 134
#define S390_CR10_REGNUM 135
#define S390_CR11_REGNUM 136
#define S390_CR12_REGNUM 137
#define S390_CR13_REGNUM 138
#define S390_CR14_REGNUM 139
#define S390_CR15_REGNUM 140
#define S390_PREFIX_REGNUM 141

/* Total.  */
#define S390_NUM_REGS 142
#define S390_NUM_GPRS 16
#define S390_NUM_FPRS 16

#define S390_MAX_INSTR_SIZE 6

/* Special register usage.  */
#define S390_SP_REGNUM S390_R15_REGNUM
#define S390_RETADDR_REGNUM S390_R14_REGNUM
#define S390_FRAME_REGNUM S390_R11_REGNUM

#define S390_IS_GREGSET_REGNUM(i)					\
  (((i) >= S390_PSWM_REGNUM && (i) <= S390_A15_REGNUM)			\
   || ((i) >= S390_R0_UPPER_REGNUM && (i) <= S390_R15_UPPER_REGNUM)	\
   || (i) == S390_ORIG_R2_REGNUM)

#define S390_IS_FPREGSET_REGNUM(i)			\
  ((i) >= S390_FPC_REGNUM && (i) <= S390_F15_REGNUM)

#define S390_IS_TDBREGSET_REGNUM(i)				\
  ((i) >= S390_TDB_DWORD0_REGNUM && (i) <= S390_TDB_R15_REGNUM)

/* Definitions for address translation.  */
/* DAT Table types.  */
#define S390_LK_DAT_TT_REGION1  3
#define S390_LK_DAT_TT_REGION2  2
#define S390_LK_DAT_TT_REGION3  1
#define S390_LK_DAT_TT_SEGMENT  0

/* Region-First-Table */
#define S390_LK_RFTE_TL  0x3ULL		/* Table-Length */
#define S390_LK_RFTE_TT  0xcULL		/* Table-Type */
#define S390_LK_RFTE_I   0x20ULL	/* Region-Invalid Bit */
#define S390_LK_RFTE_TF  0xc0ULL	/* Table Offset */
#define S390_LK_RFTE_P   0x200ULL	/* DAT-Protection Bit */
#define S390_LK_RFTE_O  ~0xfffULL	/* Region-Second-Table Origin */

/* Region-Second-Table flags.  */
#define S390_LK_RSTE_TL  0x3ULL		/* Table-Length */
#define S390_LK_RSTE_TT  0xcULL		/* Table-Type */
#define S390_LK_RSTE_I   0x20ULL	/* Region-Invalid Bit */
#define S390_LK_RSTE_TF  0xc0ULL	/* Table Offset */
#define S390_LK_RSTE_P   0x200ULL	/* DAT-Protection Bit */
#define S390_LK_RSTE_O  ~0xfffULL	/* Region-Third-Table Origin */

/* Region-Third-Table flags.  */
#define S390_LK_RTTE_TL    0x3ULL	/* Table-Length */
#define S390_LK_RTTE_TT    0xcULL	/* Table-Type */
#define S390_LK_RTTE_CR    0x10ULL	/* Common-Region Bit */
#define S390_LK_RTTE_I     0x20ULL	/* Region-Invalid Bit */
#define S390_LK_RTTE_TF    0xc0ULL	/* Table Offset */
#define S390_LK_RTTE_P     0x200ULL	/* DAT-Protection Bit */
#define S390_LK_RTTE_FC    0x400ULL	/* Format-Control Bit */
#define S390_LK_RTTE_F     0x800ULL	/* Fetch-Protection Bit */
#define S390_LK_RTTE_ACC   0xf000ULL	/* Access-Control Bits */
#define S390_LK_RTTE_AV    0x10000ULL	/* ACCF-Validity Control */
#define S390_LK_RTTE_O    ~0xfffULL	/* Segment-Table Origin */
#define S390_LK_RTTE_RFAA ~0x7fffffffULL /* Region-Frame Absolute Address */

/* Segment-Table flags.  */
#define S390_LK_STE_TT    0xcULL	/* Table-Type */
#define S390_LK_STE_I     0x20ULL	/* Segment-Invalid Bit */
#define S390_LK_STE_TF    0xc0ULL	/* Table Offset */
#define S390_LK_STE_P     0x200ULL	/* DAT-Protection Bit */
#define S390_LK_STE_FC    0x400ULL	/* Format-Control Bit */
#define S390_LK_STE_F     0x800ULL	/* Fetch-Protection Bit */
#define S390_LK_STE_ACC   0xf000ULL	/* Access-Control Bits */
#define S390_LK_STE_AV    0x10000ULL	/* ACCF-Validity Control */
#define S390_LK_STE_O    ~0x7ffULL	/* Page-Table Origin */
#define S390_LK_STE_SFAA ~0xfffffULL	/* Segment-Frame Absolute Address */

/* Page-Table flags.  */
#define S390_LK_PTE_P     0x200ULL	/* DAT-Protection Bit */
#define S390_LK_PTE_I     0x400ULL	/* Page-Invalid Bit */
#define S390_LK_PTE_PFAA ~0xfffULL	/* Page-Frame Absolute Address */

/* Virtual Address Fields.  */
#define S390_LK_VADDR_RFX 0xffe0000000000000ULL
#define S390_LK_VADDR_RSX 0x001ffc0000000000ULL
#define S390_LK_VADDR_RTX 0x000003ff80000000ULL
#define S390_LK_VADDR_SX  0x000000007ff00000ULL
#define S390_LK_VADDR_PX  0x00000000000ff000ULL
#define S390_LK_VADDR_BX  0x0000000000000fffULL

#endif /* S390_TDEP_H */
