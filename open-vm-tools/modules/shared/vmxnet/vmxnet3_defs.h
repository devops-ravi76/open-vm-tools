/*********************************************************
 * Copyright (C) 2007-2020 VMware, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation version 2 and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *
 *********************************************************/

/*********************************************************
 * The contents of this file are subject to the terms of the Common
 * Development and Distribution License (the "License") version 1.0
 * and no later version.  You may not use this file except in
 * compliance with the License.
 *
 * You can obtain a copy of the License at
 *         http://www.opensource.org/licenses/cddl1.php
 *
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 *********************************************************/

/*
 * vmxnet3_defs.h --
 *
 *      Definitions shared by device emulation and guest drivers for
 *      VMXNET3 NIC
 */

#ifndef _VMXNET3_DEFS_H_
#define _VMXNET3_DEFS_H_

#define INCLUDE_ALLOW_USERLEVEL
#define INCLUDE_ALLOW_VMKERNEL
#define INCLUDE_ALLOW_DISTRIBUTE
#define INCLUDE_ALLOW_VMKDRIVERS
#define INCLUDE_ALLOW_VMCORE
#define INCLUDE_ALLOW_MODULE
#include "includeCheck.h"

#include "upt1_defs.h"

/* all registers are 32 bit wide */
/* BAR 1 */
#define VMXNET3_REG_VRRS  0x0    /* Vmxnet3 Revision Report Selection */
#define VMXNET3_REG_UVRS  0x8    /* UPT Version Report Selection */
#define VMXNET3_REG_DSAL  0x10   /* Driver Shared Address Low */
#define VMXNET3_REG_DSAH  0x18   /* Driver Shared Address High */
#define VMXNET3_REG_CMD   0x20   /* Command */
#define VMXNET3_REG_MACL  0x28   /* MAC Address Low */
#define VMXNET3_REG_MACH  0x30   /* MAC Address High */
#define VMXNET3_REG_ICR   0x38   /* Interrupt Cause Register */
#define VMXNET3_REG_ECR   0x40   /* Event Cause Register */

#define VMXNET3_REG_WSAL  0xF00  /* Wireless Shared Address Lo  */
#define VMXNET3_REG_WSAH  0xF08  /* Wireless Shared Address Hi  */
#define VMXNET3_REG_WCMD  0xF18  /* Wireless Command */

/* BAR 0 */
#define VMXNET3_REG_IMR      0x0   /* Interrupt Mask Register */
#define VMXNET3_REG_TXPROD   0x600 /* Tx Producer Index */
#define VMXNET3_REG_RXPROD   0x800 /* Rx Producer Index for ring 1 */
#define VMXNET3_REG_RXPROD2  0xA00 /* Rx Producer Index for ring 2 */

#define VMXNET3_PT_REG_SIZE     4096    /* BAR 0 */
#define VMXNET3_VD_REG_SIZE     4096    /* BAR 1 */

/*
 * The two Vmxnet3 MMIO Register PCI BARs (BAR 0 at offset 10h and BAR 1 at
 * offset 14h)  as well as the MSI-X BAR are combined into one PhysMem region:
 * <-VMXNET3_PT_REG_SIZE-><-VMXNET3_VD_REG_SIZE-><-VMXNET3_MSIX_BAR_SIZE-->
 * -------------------------------------------------------------------------
 * |Pass Thru Registers  | Virtual Dev Registers | MSI-X Vector/PBA Table  |
 * -------------------------------------------------------------------------
 * VMXNET3_MSIX_BAR_SIZE is defined in "vmxnet3Int.h"
 */
#define VMXNET3_PHYSMEM_PAGES   4

#define VMXNET3_REG_ALIGN       8  /* All registers are 8-byte aligned. */
#define VMXNET3_REG_ALIGN_MASK  0x7

/* I/O Mapped access to registers */
#define VMXNET3_IO_TYPE_PT              0
#define VMXNET3_IO_TYPE_VD              1
#define VMXNET3_IO_ADDR(type, reg)      (((type) << 24) | ((reg) & 0xFFFFFF))
#define VMXNET3_IO_TYPE(addr)           ((addr) >> 24)
#define VMXNET3_IO_REG(addr)            ((addr) & 0xFFFFFF)

#ifndef __le16
#define __le16 uint16
#endif
#ifndef __le32
#define __le32 uint32
#endif
#ifndef __le64
#define __le64 uint64
#endif

typedef enum {
   VMXNET3_CMD_FIRST_SET = 0xCAFE0000,
   VMXNET3_CMD_ACTIVATE_DEV = VMXNET3_CMD_FIRST_SET,
   VMXNET3_CMD_QUIESCE_DEV,
   VMXNET3_CMD_RESET_DEV,
   VMXNET3_CMD_UPDATE_RX_MODE,
   VMXNET3_CMD_UPDATE_MAC_FILTERS,
   VMXNET3_CMD_UPDATE_VLAN_FILTERS,
   VMXNET3_CMD_UPDATE_RSSIDT,
   VMXNET3_CMD_UPDATE_IML,
   VMXNET3_CMD_UPDATE_PMCFG,
   VMXNET3_CMD_UPDATE_FEATURE,
   VMXNET3_CMD_STOP_EMULATION,
   VMXNET3_CMD_LOAD_PLUGIN,
   VMXNET3_CMD_ACTIVATE_VF,
   VMXNET3_CMD_SET_POLLING,
   VMXNET3_CMD_SET_COALESCE,
   VMXNET3_CMD_REGISTER_MEMREGS,
   VMXNET3_CMD_SET_RSS_FIELDS,
   VMXNET3_CMD_SET_PKTSTEERING, /* 0xCAFE0011 */

   VMXNET3_CMD_FIRST_GET = 0xF00D0000,
   VMXNET3_CMD_GET_QUEUE_STATUS = VMXNET3_CMD_FIRST_GET,
   VMXNET3_CMD_GET_STATS,
   VMXNET3_CMD_GET_LINK,
   VMXNET3_CMD_GET_PERM_MAC_LO,
   VMXNET3_CMD_GET_PERM_MAC_HI,
   VMXNET3_CMD_GET_DID_LO,
   VMXNET3_CMD_GET_DID_HI,
   VMXNET3_CMD_GET_DEV_EXTRA_INFO,
   VMXNET3_CMD_GET_CONF_INTR,
   VMXNET3_CMD_GET_ADAPTIVE_RING_INFO,
   VMXNET3_CMD_GET_TXDATA_DESC_SIZE,
   VMXNET3_CMD_GET_COALESCE,
   VMXNET3_CMD_GET_RSS_FIELDS,
   VMXNET3_CMD_GET_ENCAP_DSTPORT,
   VMXNET3_CMD_GET_PKTSTEERING, /* 0xF00D000E */
   VMXNET3_CMD_GET_MAX_QUEUES_CONF,
   VMXNET3_CMD_GET_RSS_HASH_FUNC,
} Vmxnet3_Cmd;

/* Adaptive Ring Info Flags */
#define VMXNET3_DISABLE_ADAPTIVE_RING 1

/*
 *	Little Endian layout of bitfields -
 *	Byte 0 :	7.....len.....0
 *	Byte 1 :	oco gen 13.len.8
 *	Byte 2 : 	5.msscof.0 ext1  dtype
 *	Byte 3 : 	13...msscof...6
 *
 *	Big Endian layout of bitfields -
 *	Byte 0:		13...msscof...6
 *	Byte 1 : 	5.msscof.0 ext1  dtype
 *	Byte 2 :	oco gen 13.len.8
 *	Byte 3 :	7.....len.....0
 *
 *	Thus, le32_to_cpu on the dword will allow the big endian driver to read
 *	the bit fields correctly. And cpu_to_le32 will convert bitfields
 *	bit fields written by big endian driver to format required by device.
 */

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_TxDesc {
   __le64 addr;

#ifdef __BIG_ENDIAN_BITFIELD
   uint32 msscof:14;  /* MSS, checksum offset, flags */
   uint32 ext1:1;
   uint32 dtype:1;    /* descriptor type */
   uint32 oco:1;      /* Outer csum offload */
   uint32 gen:1;      /* generation bit */
   uint32 len:14;
#else
   uint32 len:14;
   uint32 gen:1;      /* generation bit */
   uint32 oco:1;      /* Outer csum offload */
   uint32 dtype:1;    /* descriptor type */
   uint32 ext1:1;
   uint32 msscof:14;  /* MSS, checksum offset, flags */
#endif  /* __BIG_ENDIAN_BITFIELD */

#ifdef __BIG_ENDIAN_BITFIELD
   uint32 tci:16;     /* Tag to Insert */
   uint32 ti:1;       /* VLAN Tag Insertion */
   uint32 ext2:1;
   uint32 cq:1;       /* completion request */
   uint32 eop:1;      /* End Of Packet */
   uint32 om:2;       /* offload mode */
   uint32 hlen:10;    /* header len */
#else
   uint32 hlen:10;    /* header len */
   uint32 om:2;       /* offload mode */
   uint32 eop:1;      /* End Of Packet */
   uint32 cq:1;       /* completion request */
   uint32 ext2:1;
   uint32 ti:1;       /* VLAN Tag Insertion */
   uint32 tci:16;     /* Tag to Insert */
#endif  /* __BIG_ENDIAN_BITFIELD */
}
#include "vmware_pack_end.h"
Vmxnet3_TxDesc;

/* TxDesc.OM values */
#define VMXNET3_OM_NONE  0          /* 0b00 */
#define VMXNET3_OM_ENCAP 1          /* 0b01 */
#define VMXNET3_OM_CSUM  2          /* 0b10 */
#define VMXNET3_OM_TSO   3          /* 0b11 */

/* fields in TxDesc we access w/o using bit fields */
#define VMXNET3_TXD_EOP_SHIFT 12
#define VMXNET3_TXD_CQ_SHIFT  13
#define VMXNET3_TXD_GEN_SHIFT 14
#define VMXNET3_TXD_EOP_DWORD_SHIFT 3
#define VMXNET3_TXD_GEN_DWORD_SHIFT 2

#define VMXNET3_TXD_CQ  (1 << VMXNET3_TXD_CQ_SHIFT)
#define VMXNET3_TXD_EOP (1 << VMXNET3_TXD_EOP_SHIFT)
#define VMXNET3_TXD_GEN (1 << VMXNET3_TXD_GEN_SHIFT)

#define VMXNET3_TXD_GEN_SIZE 1
#define VMXNET3_TXD_EOP_SIZE 1

#define VMXNET3_HDR_COPY_SIZE   128
typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_TxDataDesc {
   uint8 data[VMXNET3_HDR_COPY_SIZE];
}
#include "vmware_pack_end.h"
Vmxnet3_TxDataDesc;
typedef uint8 Vmxnet3_RxDataDesc;

#define VMXNET3_TCD_GEN_SHIFT	31
#define VMXNET3_TCD_GEN_SIZE	1
#define VMXNET3_TCD_TXIDX_SHIFT	0
#define VMXNET3_TCD_TXIDX_SIZE	12
#define VMXNET3_TCD_GEN_DWORD_SHIFT	3

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_TxCompDesc {
   uint32 txdIdx:12;    /* Index of the EOP TxDesc */
   uint32 ext1:20;

   __le32 ext2;
   __le32 ext3;

   uint32 rsvd:24;
   uint32 type:7;       /* completion type */
   uint32 gen:1;        /* generation bit */
}
#include "vmware_pack_end.h"
Vmxnet3_TxCompDesc;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_RxDesc {
   __le64 addr;

#ifdef __BIG_ENDIAN_BITFIELD
   uint32 gen:1;        /* Generation bit */
   uint32 rsvd:15;
   uint32 dtype:1;      /* Descriptor type */
   uint32 btype:1;      /* Buffer Type */
   uint32 len:14;
#else
   uint32 len:14;
   uint32 btype:1;      /* Buffer Type */
   uint32 dtype:1;      /* Descriptor type */
   uint32 rsvd:15;
   uint32 gen:1;        /* Generation bit */
#endif
   __le32 ext1;
}
#include "vmware_pack_end.h"
Vmxnet3_RxDesc;

/* values of RXD.BTYPE */
#define VMXNET3_RXD_BTYPE_HEAD   0    /* head only */
#define VMXNET3_RXD_BTYPE_BODY   1    /* body only */

/* fields in RxDesc we access w/o using bit fields */
#define VMXNET3_RXD_BTYPE_SHIFT  14
#define VMXNET3_RXD_GEN_SHIFT    31

#define VMXNET3_RCD_HDR_INNER_SHIFT  13
#define VMXNET3_RCD_RSS_INNER_SHIFT  12

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_RxCompDesc {
#ifdef __BIG_ENDIAN_BITFIELD
   uint32 ext2:1;
   uint32 cnc:1;        /* Checksum Not Calculated */
   uint32 rssType:4;    /* RSS hash type used */
   uint32 rqID:10;      /* rx queue/ring ID */
   uint32 sop:1;        /* Start of Packet */
   uint32 eop:1;        /* End of Packet */
   uint32 ext1:2;       /* bit 0: indicating v4/v6/.. is for inner header */
                        /* bit 1: indicating rssType is based on inner header */
   uint32 rxdIdx:12;    /* Index of the RxDesc */
#else
   uint32 rxdIdx:12;    /* Index of the RxDesc */
   uint32 ext1:2;       /* bit 0: indicating v4/v6/.. is for inner header */
                        /* bit 1: indicating rssType is based on inner header */
   uint32 eop:1;        /* End of Packet */
   uint32 sop:1;        /* Start of Packet */
   uint32 rqID:10;      /* rx queue/ring ID */
   uint32 rssType:4;    /* RSS hash type used */
   uint32 cnc:1;        /* Checksum Not Calculated */
   uint32 ext2:1;
#endif  /* __BIG_ENDIAN_BITFIELD */

   __le32 rssHash;      /* RSS hash value */

#ifdef __BIG_ENDIAN_BITFIELD
   uint32 tci:16;       /* Tag stripped */
   uint32 ts:1;         /* Tag is stripped */
   uint32 err:1;        /* Error */
   uint32 len:14;       /* data length */
#else
   uint32 len:14;       /* data length */
   uint32 err:1;        /* Error */
   uint32 ts:1;         /* Tag is stripped */
   uint32 tci:16;       /* Tag stripped */
#endif  /* __BIG_ENDIAN_BITFIELD */


#ifdef __BIG_ENDIAN_BITFIELD
   uint32 gen:1;        /* generation bit */
   uint32 type:7;       /* completion type */
   uint32 fcs:1;        /* Frame CRC correct */
   uint32 frg:1;        /* IP Fragment */
   uint32 v4:1;         /* IPv4 */
   uint32 v6:1;         /* IPv6 */
   uint32 ipc:1;        /* IP Checksum Correct */
   uint32 tcp:1;        /* TCP packet */
   uint32 udp:1;        /* UDP packet */
   uint32 tuc:1;        /* TCP/UDP Checksum Correct */
   uint32 csum:16;
#else
   uint32 csum:16;
   uint32 tuc:1;        /* TCP/UDP Checksum Correct */
   uint32 udp:1;        /* UDP packet */
   uint32 tcp:1;        /* TCP packet */
   uint32 ipc:1;        /* IP Checksum Correct */
   uint32 v6:1;         /* IPv6 */
   uint32 v4:1;         /* IPv4 */
   uint32 frg:1;        /* IP Fragment */
   uint32 fcs:1;        /* Frame CRC correct */
   uint32 type:7;       /* completion type */
   uint32 gen:1;        /* generation bit */
#endif  /* __BIG_ENDIAN_BITFIELD */
}
#include "vmware_pack_end.h"
Vmxnet3_RxCompDesc;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_RxCompDescExt {
   __le32 dword1;
   uint8  segCnt;       /* Number of aggregated packets */
   uint8  dupAckCnt;    /* Number of duplicate Acks */
   __le16 tsDelta;      /* TCP timestamp difference */

#ifdef __BIG_ENDIAN_BITFIELD
   uint32 encap:1;      /* LRO info refers to inner pkt */
   uint32 reserved:31;
#else
   uint32 reserved:31;
   uint32 encap:1;      /* LRO info refers to inner pkt */
#endif  /* __BIG_ENDIAN_BITFIELD */

#ifdef __BIG_ENDIAN_BITFIELD
   uint32 gen:1;        /* generation bit */
   uint32 type:7;       /* completion type */
   uint32 fcs:1;        /* Frame CRC correct */
   uint32 frg:1;        /* IP Fragment */
   uint32 v4:1;         /* IPv4 */
   uint32 v6:1;         /* IPv6 */
   uint32 ipc:1;        /* IP Checksum Correct */
   uint32 tcp:1;        /* TCP packet */
   uint32 udp:1;        /* UDP packet */
   uint32 tuc:1;        /* TCP/UDP Checksum Correct */
   uint32 mss:16;
#else
   uint32 mss:16;
   uint32 tuc:1;        /* TCP/UDP Checksum Correct */
   uint32 udp:1;        /* UDP packet */
   uint32 tcp:1;        /* TCP packet */
   uint32 ipc:1;        /* IP Checksum Correct */
   uint32 v6:1;         /* IPv6 */
   uint32 v4:1;         /* IPv4 */
   uint32 frg:1;        /* IP Fragment */
   uint32 fcs:1;        /* Frame CRC correct */
   uint32 type:7;       /* completion type */
   uint32 gen:1;        /* generation bit */
#endif  /* __BIG_ENDIAN_BITFIELD */
}
#include "vmware_pack_end.h"
Vmxnet3_RxCompDescExt;

/* fields in RxCompDesc we access via Vmxnet3_GenericDesc.dword[3] */
#define VMXNET3_RCD_TUC_SHIFT  16
#define VMXNET3_RCD_IPC_SHIFT  19

/* fields in RxCompDesc we access via Vmxnet3_GenericDesc.qword[1] */
#define VMXNET3_RCD_TYPE_SHIFT 56
#define VMXNET3_RCD_GEN_SHIFT  63

/* csum OK for TCP/UDP pkts over IP */
#define VMXNET3_RCD_CSUM_OK (1 << VMXNET3_RCD_TUC_SHIFT | 1 << VMXNET3_RCD_IPC_SHIFT)

/* value of RxCompDesc.rssType */
#define VMXNET3_RCD_RSS_TYPE_NONE     0
#define VMXNET3_RCD_RSS_TYPE_IPV4     1
#define VMXNET3_RCD_RSS_TYPE_TCPIPV4  2
#define VMXNET3_RCD_RSS_TYPE_IPV6     3
#define VMXNET3_RCD_RSS_TYPE_TCPIPV6  4
#define VMXNET3_RCD_RSS_TYPE_UDPIPV4  5
#define VMXNET3_RCD_RSS_TYPE_UDPIPV6  6
#define VMXNET3_RCD_RSS_TYPE_ESPIPV4  7
#define VMXNET3_RCD_RSS_TYPE_ESPIPV6  8

/* a union for accessing all cmd/completion descriptors */
typedef union Vmxnet3_GenericDesc {
   __le64                qword[2];
   __le32                dword[4];
   __le16                word[8];
   Vmxnet3_TxDesc        txd;
   Vmxnet3_RxDesc        rxd;
   Vmxnet3_TxCompDesc    tcd;
   Vmxnet3_RxCompDesc    rcd;
   Vmxnet3_RxCompDescExt rcdExt;
} Vmxnet3_GenericDesc;

#define VMXNET3_INIT_GEN       1

#define VMXNET3_INVALID_QUEUEID -1

/* Max size of a single tx buffer */
#define VMXNET3_MAX_TX_BUF_SIZE  (1 << 14)

/* # of tx desc needed for a tx buffer size */
#define VMXNET3_TXD_NEEDED(size) (((size) + VMXNET3_MAX_TX_BUF_SIZE - 1) / VMXNET3_MAX_TX_BUF_SIZE)

/* max # of tx descs for a non-tso pkt */
#define VMXNET3_MAX_TXD_PER_PKT 16

/* Max size of a single rx buffer */
#define VMXNET3_MAX_RX_BUF_SIZE  ((1 << 14) - 1)
/* Minimum size of a type 0 buffer */
#define VMXNET3_MIN_T0_BUF_SIZE  128
#define VMXNET3_MAX_CSUM_OFFSET  1024

/* Ring base address alignment */
#define VMXNET3_RING_BA_ALIGN   512
#define VMXNET3_RING_BA_MASK    (VMXNET3_RING_BA_ALIGN - 1)

/* Ring size must be a multiple of 32 */
#define VMXNET3_RING_SIZE_ALIGN 32
#define VMXNET3_RING_SIZE_MASK  (VMXNET3_RING_SIZE_ALIGN - 1)

/* Rx Data Ring buffer size must be a multiple of 64 bytes */
#define VMXNET3_RXDATA_DESC_SIZE_ALIGN 64
#define VMXNET3_RXDATA_DESC_SIZE_MASK  (VMXNET3_RXDATA_DESC_SIZE_ALIGN - 1)

/* Tx Data Ring buffer size must be a multiple of 64 bytes */
#define VMXNET3_TXDATA_DESC_SIZE_ALIGN 64
#define VMXNET3_TXDATA_DESC_SIZE_MASK  (VMXNET3_TXDATA_DESC_SIZE_ALIGN - 1)

/* Max ring size */
#define VMXNET3_TX_RING_MAX_SIZE   4096
#define VMXNET3_TC_RING_MAX_SIZE   4096
#define VMXNET3_RX_RING_MAX_SIZE   4096
#define VMXNET3_RX_RING2_MAX_SIZE  4096
#define VMXNET3_RC_RING_MAX_SIZE   8192

/* Large enough to accommodate typical payload + encap + extension header */
#define VMXNET3_RXDATA_DESC_MAX_SIZE   2048
#define VMXNET3_TXDATA_DESC_MIN_SIZE   128
#define VMXNET3_TXDATA_DESC_MAX_SIZE   2048

/* a list of reasons for queue stop */

#define VMXNET3_ERR_NOEOP        0x80000000  /* cannot find the EOP desc of a pkt */
#define VMXNET3_ERR_TXD_REUSE    0x80000001  /* reuse a TxDesc before tx completion */
#define VMXNET3_ERR_BIG_PKT      0x80000002  /* too many TxDesc for a pkt */
#define VMXNET3_ERR_DESC_NOT_SPT 0x80000003  /* descriptor type not supported */
#define VMXNET3_ERR_SMALL_BUF    0x80000004  /* type 0 buffer too small */
#define VMXNET3_ERR_STRESS       0x80000005  /* stress option firing in vmkernel */
#define VMXNET3_ERR_SWITCH       0x80000006  /* mode switch failure */
#define VMXNET3_ERR_TXD_INVALID  0x80000007  /* invalid TxDesc */

/* completion descriptor types */
#define VMXNET3_CDTYPE_TXCOMP      0    /* Tx Completion Descriptor */
#define VMXNET3_CDTYPE_RXCOMP      3    /* Rx Completion Descriptor */
#define VMXNET3_CDTYPE_RXCOMP_LRO  4    /* Rx Completion Descriptor for LRO */

#define VMXNET3_GOS_BITS_UNK    0   /* unknown */
#define VMXNET3_GOS_BITS_32     1
#define VMXNET3_GOS_BITS_64     2

#define VMXNET3_GOS_TYPE_UNK        0 /* unknown */
#define VMXNET3_GOS_TYPE_LINUX      1
#define VMXNET3_GOS_TYPE_WIN        2
#define VMXNET3_GOS_TYPE_SOLARIS    3
#define VMXNET3_GOS_TYPE_FREEBSD    4
#define VMXNET3_GOS_TYPE_PXE        5

/* All structures in DriverShared are padded to multiples of 8 bytes */

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_GOSInfo {
#ifdef __BIG_ENDIAN_BITFIELD
   uint32   gosMisc: 10;    /* other info about gos */
   uint32   gosVer:  16;    /* gos version */
   uint32   gosType: 4;     /* which guest */
   uint32   gosBits: 2;     /* 32-bit or 64-bit? */
#else
   uint32   gosBits: 2;     /* 32-bit or 64-bit? */
   uint32   gosType: 4;     /* which guest */
   uint32   gosVer:  16;    /* gos version */
   uint32   gosMisc: 10;    /* other info about gos */
#endif  /* __BIG_ENDIAN_BITFIELD */
}
#include "vmware_pack_end.h"
Vmxnet3_GOSInfo;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_DriverInfo {
   __le32          version;        /* driver version */
   Vmxnet3_GOSInfo gos;
   __le32          vmxnet3RevSpt;  /* vmxnet3 revision supported */
   __le32          uptVerSpt;      /* upt version supported */
}
#include "vmware_pack_end.h"
Vmxnet3_DriverInfo;

#define VMXNET3_REV1_MAGIC  0xbabefee1

/* 
 * QueueDescPA must be 128 bytes aligned. It points to an array of
 * Vmxnet3_TxQueueDesc followed by an array of Vmxnet3_RxQueueDesc.
 * The number of Vmxnet3_TxQueueDesc/Vmxnet3_RxQueueDesc are specified by
 * Vmxnet3_MiscConf.numTxQueues/numRxQueues, respectively.
 */
#define VMXNET3_QUEUE_DESC_ALIGN  128

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_MiscConf {
   Vmxnet3_DriverInfo driverInfo;
   __le64             uptFeatures;
   __le64             ddPA;         /* driver data PA */
   __le64             queueDescPA;  /* queue descriptor table PA */
   __le32             ddLen;        /* driver data len */
   __le32             queueDescLen; /* queue descriptor table len, in bytes */
   __le32             mtu;
   __le16             maxNumRxSG;
   uint8              numTxQueues;
   uint8              numRxQueues;
   __le32             reserved[4];
}
#include "vmware_pack_end.h"
Vmxnet3_MiscConf;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_TxQueueConf {
   __le64    txRingBasePA;
   __le64    dataRingBasePA;
   __le64    compRingBasePA;
   __le64    ddPA;         /* driver data */
   __le64    reserved;
   __le32    txRingSize;   /* # of tx desc */
   __le32    dataRingSize; /* # of data desc */
   __le32    compRingSize; /* # of comp desc */
   __le32    ddLen;        /* size of driver data */
   uint8     intrIdx;
   uint8     _pad1[1];
   __le16    txDataRingDescSize;
   uint8     _pad2[4];
}
#include "vmware_pack_end.h"
Vmxnet3_TxQueueConf;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_RxQueueConf {
   __le64    rxRingBasePA[2];
   __le64    compRingBasePA;
   __le64    ddPA;            /* driver data */
   __le64    rxDataRingBasePA;
   __le32    rxRingSize[2];   /* # of rx desc */
   __le32    compRingSize;    /* # of rx comp desc */
   __le32    ddLen;           /* size of driver data */
   uint8     intrIdx;
   uint8     _pad1[1];
   __le16    rxDataRingDescSize; /* size of rx data ring buffer */
   uint8     _pad2[4];
}
#include "vmware_pack_end.h"
Vmxnet3_RxQueueConf;

enum vmxnet3_intr_mask_mode {
   VMXNET3_IMM_AUTO   = 0,
   VMXNET3_IMM_ACTIVE = 1,
   VMXNET3_IMM_LAZY   = 2
};

enum vmxnet3_intr_type {
   VMXNET3_IT_AUTO = 0,
   VMXNET3_IT_INTX = 1,
   VMXNET3_IT_MSI  = 2,
   VMXNET3_IT_MSIX = 3
};

#define VMXNET3_MAX_TX_QUEUES  8
#define VMXNET3_MAX_RX_QUEUES  16
/* addition 1 for events */
#define VMXNET3_MAX_INTRS      25

/* Version 6 and later will use below macros */
#define VMXNET3_EXT_MAX_TX_QUEUES  32
#define VMXNET3_EXT_MAX_RX_QUEUES  32
/* addition 1 for events */
#define VMXNET3_EXT_MAX_INTRS      65
#define VMXNET3_FIRST_SET_INTRS    64

/* value of intrCtrl */
#define VMXNET3_IC_DISABLE_ALL  0x1   /* bit 0 */

#define VMXNET3_COAL_STATIC_MAX_DEPTH        128
#define VMXNET3_COAL_RBC_MIN_RATE            100
#define VMXNET3_COAL_RBC_MAX_RATE            100000

enum Vmxnet3_CoalesceMode {
   VMXNET3_COALESCE_DISABLED   = 0,
   VMXNET3_COALESCE_ADAPT      = 1,
   VMXNET3_COALESCE_STATIC     = 2,
   VMXNET3_COALESCE_RBC        = 3
};

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_CoalesceRbc {
   uint32 rbc_rate;
}
#include "vmware_pack_end.h"
Vmxnet3_CoalesceRbc;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_CoalesceStatic {
   uint32 tx_depth;
   uint32 tx_comp_depth;
   uint32 rx_depth;
}
#include "vmware_pack_end.h"
Vmxnet3_CoalesceStatic;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_CoalesceScheme {
   enum Vmxnet3_CoalesceMode coalMode;
   union {
      Vmxnet3_CoalesceRbc    coalRbc;
      Vmxnet3_CoalesceStatic coalStatic;
   } coalPara;
}
#include "vmware_pack_end.h"
Vmxnet3_CoalesceScheme;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_IntrConf {
   uint8  autoMask;      /* on/off flag */
   uint8  numIntrs;      /* # of interrupts */
   uint8  eventIntrIdx;
   uint8  modLevels[VMXNET3_MAX_INTRS]; /* moderation level for each intr */
   __le32 intrCtrl;
   __le32 reserved[2];
}
#include "vmware_pack_end.h"
Vmxnet3_IntrConf;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_IntrConfExt {
   uint8  autoMask;
   uint8  numIntrs;      /* # of interrupts */
   uint8  eventIntrIdx;
   uint8  reserved;
   __le32 intrCtrl;
   __le32 reserved1;
   uint8  modLevels[VMXNET3_EXT_MAX_INTRS]; /* moderation level for each intr */
   uint8  reserved2[3];
}
#include "vmware_pack_end.h"
Vmxnet3_IntrConfExt;

/* one bit per VLAN ID, the size is in the units of uint32 */
#define VMXNET3_VFT_SIZE  (4096 / (sizeof(uint32) * 8))

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_QueueStatus {
   uint8   stopped;    /* on/off flag */
   uint8   _pad[3];
   __le32  error;
}
#include "vmware_pack_end.h"
Vmxnet3_QueueStatus;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_TxQueueCtrl {
   __le32  txNumDeferred;
   __le32  txThreshold;
   __le64  reserved;
}
#include "vmware_pack_end.h"
Vmxnet3_TxQueueCtrl;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_RxQueueCtrl {
   uint8   updateRxProd;   /* on/off flag */
   uint8   _pad[7];
   __le64  reserved;
}
#include "vmware_pack_end.h"
Vmxnet3_RxQueueCtrl;

#define VMXNET3_RXM_UCAST     0x01  /* unicast only */
#define VMXNET3_RXM_MCAST     0x02  /* multicast passing the filters */
#define VMXNET3_RXM_BCAST     0x04  /* broadcast only */
#define VMXNET3_RXM_ALL_MULTI 0x08  /* all multicast */
#define VMXNET3_RXM_PROMISC   0x10  /* promiscuous */

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_RxFilterConf {
   __le32   rxMode;       /* VMXNET3_RXM_xxx */
   __le16   mfTableLen;   /* size of the multicast filter table */
   __le16   _pad1;
   __le64   mfTablePA;    /* PA of the multicast filters table */
   __le32   vfTable[VMXNET3_VFT_SIZE]; /* vlan filter */
}
#include "vmware_pack_end.h"
Vmxnet3_RxFilterConf;

#define ETH_ADDR_LENGTH 6

#define VMXNET3_PKTSTEERING_VERSION_ONE    1
#define VMXNET3_PKTSTEERING_CURRENT_VERSION    VMXNET3_PKTSTEERING_VERSION_ONE

typedef uint8_t Eth_Address[ETH_ADDR_LENGTH];


typedef enum {
   VMXNET3_PKTSTEERING_NOACTION,
   VMXNET3_PKTSTEERING_ACCEPT,
   VMXNET3_PKTSTEERING_REJECT,
   VMXNET3_PKTSTEERING_ACTION_MAX,
} Vmxnet3_PktSteeringAction;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_PktSteeringActionData {
   uint8_t      action; /* enum Vmxnet3PktSteeringAction */
   uint8_t      rxQid;
}
#include "vmware_pack_end.h" 
Vmxnet3_PktSteeringActionData;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_PktSteeringInput {
   uint16_t     l3proto;
   uint8_t      l4proto;
   uint8_t      pad;

   uint16_t     srcPort;
   uint16_t     dstPort;

   union {
      struct {
         uint32_t     srcIPv4;
         uint32_t     dstIPv4;
      };
      struct {
         uint8_t      srcIPv6[16];
         uint8_t      dstIPv6[16];
      };
   };

   Eth_Address  dstMAC;
   Eth_Address  srcMAC;
}
#include "vmware_pack_end.h"
Vmxnet3_PktSteeringInput;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_PktSteeringFilterConf {
   uint8_t                            version;
   uint8_t                            priority;
   Vmxnet3_PktSteeringActionData      actionData;
   Vmxnet3_PktSteeringInput           spec;
   Vmxnet3_PktSteeringInput           mask;
   uint8_t                            pad[4];
}
#include "vmware_pack_end.h"
Vmxnet3_PktSteeringFilterConf;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_PktSteeringVerInfo {
   uint8_t      version;
   uint8_t      pad;
   uint16_t     maxMasks;
   uint32_t     maxFilters;
}
#include "vmware_pack_end.h"
Vmxnet3_PktSteeringVerInfo;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_PktSteeringFilterStats {
   uint64_t      packets;
}
#include "vmware_pack_end.h"
Vmxnet3_PktSteeringFilterStats;

typedef enum {
   VMXNET3_PKTSTEERING_CMD_GET_VER = 0x0, /* start of GET commands */
   VMXNET3_PKTSTEERING_CMD_GET_FILTER_STATS,

   VMXNET3_PKTSTEERING_CMD_ADD_FILTER = 0x80, /*start of SET commands */
   VMXNET3_PKTSTEERING_CMD_DEL_FILTER,
   VMXNET3_PKTSTEERING_CMD_FLUSH,
} Vmxnet3_PktSteeringCmd;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_PktSteeringCmdMsg {
   uint16_t                       cmd; /* enum Vmxnet3PktSteeringCmd */
   uint16_t                       msgSize;
   uint32_t                       outputLen;
   uint64_t                       outputPA;
   Vmxnet3_PktSteeringFilterConf  fConf;
}
#include "vmware_pack_end.h"
Vmxnet3_PktSteeringCmdMsg;

#define VMXNET3_PM_MAX_FILTERS        6
#define VMXNET3_PM_MAX_PATTERN_SIZE   128
#define VMXNET3_PM_MAX_MASK_SIZE      (VMXNET3_PM_MAX_PATTERN_SIZE / 8)

#define VMXNET3_PM_WAKEUP_MAGIC       0x01  /* wake up on magic pkts */
#define VMXNET3_PM_WAKEUP_FILTER      0x02  /* wake up on pkts matching filters */

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_PM_PktFilter {
   uint8 maskSize;
   uint8 patternSize;
   uint8 mask[VMXNET3_PM_MAX_MASK_SIZE];
   uint8 pattern[VMXNET3_PM_MAX_PATTERN_SIZE];
   uint8 pad[6];
}
#include "vmware_pack_end.h"
Vmxnet3_PM_PktFilter;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_PMConf {
   __le16               wakeUpEvents;  /* VMXNET3_PM_WAKEUP_xxx */
   uint8                numFilters;
   uint8                pad[5];
   Vmxnet3_PM_PktFilter filters[VMXNET3_PM_MAX_FILTERS];
}
#include "vmware_pack_end.h"
Vmxnet3_PMConf;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_VariableLenConfDesc {
   __le32              confVer;
   __le32              confLen;
   __le64              confPA;
}
#include "vmware_pack_end.h"
Vmxnet3_VariableLenConfDesc;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_DSDevRead {
   /* read-only region for device, read by dev in response to a SET cmd */
   Vmxnet3_MiscConf     misc;
   Vmxnet3_IntrConf     intrConf;
   Vmxnet3_RxFilterConf rxFilterConf;
   Vmxnet3_VariableLenConfDesc  rssConfDesc;
   Vmxnet3_VariableLenConfDesc  pmConfDesc;
   Vmxnet3_VariableLenConfDesc  pluginConfDesc;
}
#include "vmware_pack_end.h"
Vmxnet3_DSDevRead;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_DSDevReadExt {
   /* read-only region for device, read by dev in response to a SET cmd */
   Vmxnet3_IntrConfExt     intrConfExt;
}
#include "vmware_pack_end.h"
Vmxnet3_DSDevReadExt;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_TxQueueDesc {
   Vmxnet3_TxQueueCtrl ctrl;
   Vmxnet3_TxQueueConf conf;
   /* Driver read after a GET command */
   Vmxnet3_QueueStatus status;
   UPT1_TxStats        stats;
   uint8               _pad[88]; /* 128 aligned */
}
#include "vmware_pack_end.h"
Vmxnet3_TxQueueDesc;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_RxQueueDesc {
   Vmxnet3_RxQueueCtrl ctrl;
   Vmxnet3_RxQueueConf conf;
   /* Driver read after a GET command */
   Vmxnet3_QueueStatus status;
   UPT1_RxStats        stats;
   uint8               _pad[88]; /* 128 aligned */
}
#include "vmware_pack_end.h"
Vmxnet3_RxQueueDesc;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_SetPolling {
   uint8               enablePolling;
}
#include "vmware_pack_end.h"
Vmxnet3_SetPolling;

typedef
#include "vmware_pack_begin.h"

struct Vmxnet3_MemoryRegion {
   __le64            startPA;  // starting physical address
   __le32            length;   // limit the length to be less than 4G
   /*
    * any bits is set in txQueueBits or rxQueueBits indicate this region
    * is applicable for the relevant queue
    */
   __le16            txQueueBits; // bit n corresponding to tx queue n
   __le16            rxQueueBits; // bit n corresponding to rx queueb n
}
#include "vmware_pack_end.h"
Vmxnet3_MemoryRegion;

/*
 * Assume each queue can have upto 16 memory region
 * we have 8 + 8 = 16 queues. So max regions is
 * defined as 16 * 16
 * when more region is passed to backend, the handling
 * is undefined, Backend can choose to fail the the request
 * or ignore the extra region.
 */
#define MAX_MEMORY_REGION_PER_QUEUE 16
#define MAX_MEMORY_REGION_PER_DEVICE (16 * 16)

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_MemRegs {
   __le16           numRegs;
   __le16           pad[3];
   Vmxnet3_MemoryRegion memRegs[1];
}
#include "vmware_pack_end.h"
Vmxnet3_MemRegs;

typedef enum Vmxnet3_RSSField {
   VMXNET3_RSS_FIELDS_TCPIP4 = 0x1UL,
   VMXNET3_RSS_FIELDS_TCPIP6 = 0x2UL,
   VMXNET3_RSS_FIELDS_UDPIP4 = 0x4UL,
   VMXNET3_RSS_FIELDS_UDPIP6 = 0x8UL,
   VMXNET3_RSS_FIELDS_ESPIP4 = 0x10UL,
   VMXNET3_RSS_FIELDS_ESPIP6 = 0x20UL,

   VMXNET3_RSS_FIELDS_INNER_IP4 = 0x100UL,
   VMXNET3_RSS_FIELDS_INNER_TCPIP4 = 0x200UL,
   VMXNET3_RSS_FIELDS_INNER_IP6 = 0x400UL,
   VMXNET3_RSS_FIELDS_INNER_TCPIP6 = 0x800UL,
   VMXNET3_RSS_FIELDS_INNER_UDPIP4 = 0x1000UL,
   VMXNET3_RSS_FIELDS_INNER_UDPIP6 = 0x2000UL,
   VMXNET3_RSS_FIELDS_INNER_ESPIP4 = 0x4000UL,
   VMXNET3_RSS_FIELDS_INNER_ESPIP6 = 0x8000UL,
} Vmxnet3_RSSField;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_EncapDstPort {
   __le16            geneveDstPort;
   __le16            vxlanDstPort;
}
#include "vmware_pack_end.h"
Vmxnet3_EncapDstPort;

/*
 * If a command data does not exceed 16 bytes, it can use
 * the shared memory directly. Otherwise use variable length
 * configuration descriptor to pass the data.
 */
typedef
#include "vmware_pack_begin.h"
union Vmxnet3_CmdInfo {
   Vmxnet3_VariableLenConfDesc varConf;
   Vmxnet3_SetPolling          setPolling;
   Vmxnet3_RSSField            setRSSFields;
   Vmxnet3_EncapDstPort        encapDstPort;
   __le64                      data[2];
}
#include "vmware_pack_end.h"
Vmxnet3_CmdInfo;

typedef
#include "vmware_pack_begin.h"
struct Vmxnet3_DriverShared {
   __le32               magic;
   __le32               pad; /* make devRead start at 64-bit boundaries */
   Vmxnet3_DSDevRead    devRead;
   __le32               ecr;
   __le32               reserved;
   union {
      __le32            reserved1[4];
      Vmxnet3_CmdInfo   cmdInfo; /* only valid in the context of executing the relevant
                                  * command.
                                  */
   } cu;
   Vmxnet3_DSDevReadExt devReadExt;
}
#include "vmware_pack_end.h"
Vmxnet3_DriverShared;

#define VMXNET3_ECR_RQERR       (1 << 0)
#define VMXNET3_ECR_TQERR       (1 << 1)
#define VMXNET3_ECR_LINK        (1 << 2)
#define VMXNET3_ECR_DIC         (1 << 3)
#define VMXNET3_ECR_DEBUG       (1 << 4)

/* flip the gen bit of a ring */
#define VMXNET3_FLIP_RING_GEN(gen) ((gen) = (gen) ^ 0x1)

/* only use this if moving the idx won't affect the gen bit */
#define VMXNET3_INC_RING_IDX_ONLY(idx, ring_size) \
do {\
   (idx)++;\
   if (UNLIKELY((idx) == (ring_size))) {\
      (idx) = 0;\
   }\
} while (0)

#define VMXNET3_SET_VFTABLE_ENTRY(vfTable, vid) \
   (vfTable)[(vid) >> 5] |= (1 << ((vid) & 31))
#define VMXNET3_CLEAR_VFTABLE_ENTRY(vfTable, vid) \
   (vfTable)[(vid) >> 5] &= ~(1 << ((vid) & 31))

#define VMXNET3_VFTABLE_ENTRY_IS_SET(vfTable, vid) \
   (((vfTable)[(vid) >> 5] & (1 << ((vid) & 31))) != 0)

#define VMXNET3_MAX_MTU     9000
#define VMXNET3_MIN_MTU     60

#define VMXNET3_LINK_UP         (10000 << 16 | 1)    // 10 Gbps, up
#define VMXNET3_LINK_DOWN       0

#define VMXWIFI_DRIVER_SHARED_LEN 8192

#define VMXNET3_DID_PASSTHRU    0xFFFF

#endif /* _VMXNET3_DEFS_H_ */
