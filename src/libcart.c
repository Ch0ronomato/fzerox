#include "libcart.h"
#include "libultra/ultra64.h"
#ifndef __CARTINT_H__
#define __CARTINT_H__

extern u32 __cart_rd(u32 addr);
extern void __cart_wr(u32 addr, u32 data);
// Some stubs
int ci_init(void) {}
int ed_init(void) {}
int edx_init(void) {}

int ci_card_init(void) {}
int ed_card_init(void) {}
int edx_card_init(void) {}

int ci_card_rd_cart(u32 cart, u32 lba, u32 count) {}
int edx_card_rd_cart(u32 cart, u32 lba, u32 count) {}
int ed_card_rd_cart(u32 cart, u32 lba, u32 count) {}

int ci_card_rd_dram(void *dram, u32 lba, u32 count) {}
int ed_card_rd_dram(void *dram, u32 lba, u32 count) {}
int edx_card_rd_dram(void *dram, u32 lba, u32 count) {}

int ci_card_wr_cart(u32 cart, u32 lba, u32 count) {}
int ed_card_wr_cart(u32 cart, u32 lba, u32 count) {}
int edx_card_wr_cart(u32 cart, u32 lba, u32 count) {}

int ci_card_wr_dram(const void *dram, u32 lba, u32 count) {}
int ed_card_wr_dram(const void *dram, u32 lba, u32 count) {}
int edx_card_wr_dram(const void *dram, u32 lba, u32 count) {}

int ci_exit(void) {}
int ed_exit(void) {}
int edx_exit(void) {}

#define CART_ABORT()            {__cart_acs_rel(); return -1;}

extern u32 __cart_dom1;
extern u32 __cart_dom2;
extern void __cart_acs_get(void);
extern void __cart_acs_rel(void);
extern void __cart_dma_rd(void *dram, u32 cart, u32 size);
extern void __cart_dma_wr(const void *dram, u32 cart, u32 size);
extern void __cart_buf_rd(const void *addr);
extern void __cart_buf_wr(void *addr);
extern u64 __cart_buf[512/8];

#endif /* __CARTINT_H__ */
#ifndef __SD_H__
#define __SD_H__

#define CMD0    (0x40| 0)
#define CMD1    (0x40| 1)
#define CMD2    (0x40| 2)
#define CMD3    (0x40| 3)
#define CMD7    (0x40| 7)
#define CMD8    (0x40| 8)
#define CMD9    (0x40| 9)
#define CMD12   (0x40|12)
#define CMD18   (0x40|18)
#define CMD25   (0x40|25)
#define CMD55   (0x40|55)
#define CMD58   (0x40|58)
#define ACMD6   (0x40| 6)
#define ACMD41  (0x40|41)

extern unsigned char __sd_resp[17];
extern unsigned char __sd_cfg;
extern unsigned char __sd_type;
extern unsigned char __sd_flag;

extern int __sd_crc7(const char *src);
extern void __sd_crc16(u64 *dst, const u64 *src);

#endif /* __SD_H__ */

extern void __osPiGetAccess(void);
extern void __osPiRelAccess(void);

/* Temporary buffer aligned for DMA */
#ifdef __GNUC__
__attribute__((aligned(16)))
#endif
u64 __cart_buf[512/8];

static u32 __cart_dom1_rel;
static u32 __cart_dom2_rel;
u32 __cart_dom1;
u32 __cart_dom2;

u32 cart_size;

void __cart_acs_get(void)
{
	__osPiGetAccess();
	/* Save PI BSD configuration and reconfigure */
	if (__cart_dom1)
	{
		__cart_dom1_rel =
			IO_READ(PI_BSD_DOM1_LAT_REG) <<  0 |
			IO_READ(PI_BSD_DOM1_PWD_REG) <<  8 |
			IO_READ(PI_BSD_DOM1_PGS_REG) << 16 |
			IO_READ(PI_BSD_DOM1_RLS_REG) << 20 |
			1 << 31;
		IO_WRITE(PI_BSD_DOM1_LAT_REG, __cart_dom1 >>  0);
		IO_WRITE(PI_BSD_DOM1_PWD_REG, __cart_dom1 >>  8);
		IO_WRITE(PI_BSD_DOM1_PGS_REG, __cart_dom1 >> 16);
		IO_WRITE(PI_BSD_DOM1_RLS_REG, __cart_dom1 >> 20);
	}
	if (__cart_dom2)
	{
		__cart_dom2_rel =
			IO_READ(PI_BSD_DOM2_LAT_REG) <<  0 |
			IO_READ(PI_BSD_DOM2_PWD_REG) <<  8 |
			IO_READ(PI_BSD_DOM2_PGS_REG) << 16 |
			IO_READ(PI_BSD_DOM2_RLS_REG) << 20 |
			1 << 31;
		IO_WRITE(PI_BSD_DOM2_LAT_REG, __cart_dom2 >>  0);
		IO_WRITE(PI_BSD_DOM2_PWD_REG, __cart_dom2 >>  8);
		IO_WRITE(PI_BSD_DOM2_PGS_REG, __cart_dom2 >> 16);
		IO_WRITE(PI_BSD_DOM2_RLS_REG, __cart_dom2 >> 20);
	}
}

void __cart_acs_rel(void)
{
	/* Restore PI BSD configuration */
	if (__cart_dom1_rel)
	{
		IO_WRITE(PI_BSD_DOM1_LAT_REG, __cart_dom1_rel >>  0);
		IO_WRITE(PI_BSD_DOM1_PWD_REG, __cart_dom1_rel >>  8);
		IO_WRITE(PI_BSD_DOM1_PGS_REG, __cart_dom1_rel >> 16);
		IO_WRITE(PI_BSD_DOM1_RLS_REG, __cart_dom1_rel >> 20);
		__cart_dom1_rel = 0;
	}
	if (__cart_dom2_rel)
	{
		IO_WRITE(PI_BSD_DOM2_LAT_REG, __cart_dom2_rel >>  0);
		IO_WRITE(PI_BSD_DOM2_PWD_REG, __cart_dom2_rel >>  8);
		IO_WRITE(PI_BSD_DOM2_PGS_REG, __cart_dom2_rel >> 16);
		IO_WRITE(PI_BSD_DOM2_RLS_REG, __cart_dom2_rel >> 20);
		__cart_dom2_rel = 0;
	}
	__osPiRelAccess();
}

u32 __cart_rd(u32 addr)
{
	while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY|PI_STATUS_IO_BUSY));
	return IO_READ(addr);
}

void __cart_wr(u32 addr, u32 data)
{
	while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY|PI_STATUS_IO_BUSY));
	IO_WRITE(addr, data);
}

typedef struct
{
	OSMesgQueue *messageQueue;
	OSMesg message;
}
__OSEventState;
extern __OSEventState __osEventStateTab[OS_NUM_EVENTS];

void __cart_dma_rd(void *dram, u32 cart, u32 size)
{
	osInvalDCache(dram, size);
	while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY|PI_STATUS_IO_BUSY));
	IO_WRITE(PI_DRAM_ADDR_REG, osVirtualToPhysical(dram));
	IO_WRITE(PI_CART_ADDR_REG, cart);
	IO_WRITE(PI_WR_LEN_REG, size-1);
	osRecvMesg(
		__osEventStateTab[OS_EVENT_PI].messageQueue, NULL, OS_MESG_BLOCK
	);
}

void __cart_dma_wr(const void *dram, u32 cart, u32 size)
{
	osWritebackDCache((void *)dram, size);
	while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY|PI_STATUS_IO_BUSY));
	IO_WRITE(PI_DRAM_ADDR_REG, osVirtualToPhysical((void *)dram));
	IO_WRITE(PI_CART_ADDR_REG, cart);
	IO_WRITE(PI_RD_LEN_REG, size-1);
	osRecvMesg(
		__osEventStateTab[OS_EVENT_PI].messageQueue, NULL, OS_MESG_BLOCK
	);
}

void __cart_buf_rd(const void *addr)
{
	int i;
	const u64 *ptr = addr;
	for (i = 0; i < 512/8; i += 2)
	{
		u64 a = ptr[i+0];
		u64 b = ptr[i+1];
		__cart_buf[i+0] = a;
		__cart_buf[i+1] = b;
	}
}

void __cart_buf_wr(void *addr)
{
	int i;
	u64 *ptr = addr;
	for (i = 0; i < 512/8; i += 2)
	{
		u64 a = __cart_buf[i+0];
		u64 b = __cart_buf[i+1];
		ptr[i+0] = a;
		ptr[i+1] = b;
	}
}
unsigned char __sd_resp[17];
unsigned char __sd_cfg;
unsigned char __sd_type;
unsigned char __sd_flag;

int __sd_crc7(const char *src)
{
	int i;
	int n;
	int crc = 0;
	for (i = 0; i < 5; i++)
	{
		crc ^= src[i];
		for (n = 0; n < 8; n++)
		{
			if ((crc <<= 1) & 0x100) crc ^= 0x12;
		}
	}
	return (crc & 0xFE) | 1;
}
/* Thanks to anacierdem for this brilliant implementation. */

/* Spread lower 32 bits into 64 bits */
/* x =     **** **** **** **** abcd efgh ijkl mnop */
/* result: a0b0 c0d0 e0f0 g0h0 i0j0 k0l0 m0n0 o0p0 */
static u64 __sd_crc16_spread(u64 x)
{
	x = (x << 16 | x) & 0x0000FFFF0000FFFF;
	x = (x <<  8 | x) & 0x00FF00FF00FF00FF;
	x = (x <<  4 | x) & 0x0F0F0F0F0F0F0F0F;
	x = (x <<  2 | x) & 0x3333333333333333;
	x = (x <<  1 | x) & 0x5555555555555555;
	return x;
}

/* Shuffle 32 bits of two values into 64 bits */
/* x =     **** **** **** **** abcd efgh ijkl mnop */
/* y =     **** **** **** **** ABCD EFGH IJKL MNOP */
/* result: aAbB cCdD eEfF gGhH iIjJ kKlL mMnN oOpP */
static u64 __sd_crc16_shuffle(u32 x, u32 y)
{
	return __sd_crc16_spread(x) << 1 | __sd_crc16_spread(y);
}

void __sd_crc16(u64 *dst, const u64 *src)
{
	int i;
	int n;
	u64 x;
	u64 y;
	u32 a;
	u32 b;
	u16 crc[4] = {0};
	for (i = 0; i < 512/8; i++)
	{
		x = src[i];
		/* Transpose every 2x2 bit block in the 8x8 matrix */
		/* abcd efgh     aick emgo */
		/* ijkl mnop     bjdl fnhp */
		/* qrst uvwx     qys0 u2w4 */
		/* yz01 2345  \  rzt1 v3x5 */
		/* 6789 ABCD  /  6E8G AICK */
		/* EFGH IJKL     7F9H BJDL */
		/* MNOP QRST     MUOW QYS? */
		/* UVWX YZ?!     NVPX RZT! */
		y = (x ^ (x >> 7)) & 0x00AA00AA00AA00AA;
		x ^= y ^ (y << 7);
		/* Transpose 2x2 blocks inside their 4x4 blocks in the 8x8 matrix */
		/* aick emgo     aiqy emu2 */
		/* bjdl fnhp     bjrz fnv3 */
		/* qys0 u2w4     cks0 gow4 */
		/* rzt1 v3x5  \  dlt1 hpx5 */
		/* 6E8G AICK  /  6EMU AIQY */
		/* 7F9H BJDL     7FNV BJRZ */
		/* MUOW QYS?     8GOW CKS? */
		/* NVPX RZT!     9HPX DLT! */
		y = (x ^ (x >> 14)) & 0x0000CCCC0000CCCC;
		x ^= y ^ (y << 14);
		/* Interleave */
		/* x =     aiqy 6EMU bjrz 7FNV cks0 8GOW dlt1 9HPX */
		/* y =     emu2 AIQY fnv3 BJRZ gow4 CKS? hpx5 DLT! */
		/* result: aeim quy2 6AEI MQUY bfjn rvz3 7BFJ NRVZ */
		/*         cgko sw04 8CGK OSW? dhlp tx15 9DHL PTX! */
		x = __sd_crc16_shuffle(
			(x >> 32 & 0xF0F0F0F0) | (x >> 4 & 0x0F0F0F0F),
			(x >> 28 & 0xF0F0F0F0) | (x >> 0 & 0x0F0F0F0F)
		);
		for (n = 3; n >= 0; n--)
		{
			a = crc[n];
			/* (crc >> 8) ^ dat[0] */
			b = ((x ^ a) >> 8) & 0xFF;
			b ^= b >> 4;
			a = (a << 8) ^ b ^ (b << 5) ^ (b << 12);
			/* (crc >> 8) ^ dat[1] */
			b = (x ^ (a >> 8)) & 0xFF;
			b ^= b >> 4;
			a = (a << 8) ^ b ^ (b << 5) ^ (b << 12);
			crc[n] = a;
			x >>= 16;
		}
	}
	/* Interleave CRC */
	x = __sd_crc16_shuffle(crc[0] << 16 | crc[1], crc[2] << 16 | crc[3]);
	*dst = __sd_crc16_shuffle(x >> 32, x);
}
int cart_card_init(void)
{
	static int (*const card_init[CART_MAX])(void) =
	{
		ci_card_init,
		edx_card_init,
		ed_card_init,
		sc_card_init,
	};
	if (cart_type < 0) return -1;
	return card_init[cart_type]();
}
char cart_card_byteswap;

int cart_card_rd_cart(u32 cart, u32 lba, u32 count)
{
	static int (*const card_rd_cart[CART_MAX])(
		u32 cart, u32 lba, u32 count
	) =
	{
		ci_card_rd_cart,
		edx_card_rd_cart,
		ed_card_rd_cart,
		sc_card_rd_cart,
	};
	if (cart_type < 0) return -1;
	return card_rd_cart[cart_type](cart, lba, count);
}
int cart_card_rd_dram(void *dram, u32 lba, u32 count)
{
	static int (*const card_rd_dram[CART_MAX])(
		void *dram, u32 lba, u32 count
	) =
	{
		ci_card_rd_dram,
		edx_card_rd_dram,
		ed_card_rd_dram,
		sc_card_rd_dram,
	};
	if (cart_type < 0) return -1;
	return card_rd_dram[cart_type](dram, lba, count);
}

int cart_card_wr_cart(u32 cart, u32 lba, u32 count)
{
	static int (*const card_wr_cart[CART_MAX])(
		u32 cart, u32 lba, u32 count
	) =
	{
		ci_card_wr_cart,
		edx_card_wr_cart,
		ed_card_wr_cart,
		sc_card_wr_cart,
	};
	if (cart_type < 0) return -1;
	return card_wr_cart[cart_type](cart, lba, count);
}

int cart_card_wr_dram(const void *dram, u32 lba, u32 count)
{
	static int (*const card_wr_dram[CART_MAX])(
		const void *dram, u32 lba, u32 count
	) =
	{
		ci_card_wr_dram,
		edx_card_wr_dram,
		ed_card_wr_dram,
		sc_card_wr_dram,
	};
	if (cart_type < 0) return -1;
	return card_wr_dram[cart_type](dram, lba, count);
}

int cart_exit(void)
{
	static int (*const exit[CART_MAX])(void) =
	{
		ci_exit,
		edx_exit,
		ed_exit,
		sc_exit,
	};
	if (cart_type < 0) return -1;
	return exit[cart_type]();
}

int cart_type = CART_NULL;

int cart_init(void)
{
	static int (*const init[CART_MAX])(void) =
	{
		ci_init,
		edx_init,
		ed_init,
		sc_init,
	};
	int i, result;
	/* bbplayer */
	if ((IO_READ(MI_VERSION_REG) & 0xF0) == 0xB0) return -1;
	if (!__cart_dom1)
	{
		__cart_dom1 = 0x8030FFFF;
		__cart_acs_get();
		__cart_dom1 = __cart_rd(0x10000000);
		__cart_acs_rel();
	}
	if (!__cart_dom2) __cart_dom2 = __cart_dom1;
	if (cart_type < 0)
	{
		for (i = 0; i < CART_MAX; i++)
		{
			if ((result = init[i]()) >= 0)
			{
				cart_type = i;
				return result;
			}
		}
		return -1;
	}
	return init[cart_type]();
}
#ifndef __SC_H__
#define __SC_H__

#define SC_BASE_REG             0x1FFF0000
#define SC_BUFFER_REG           0x1FFE0000

#define SC_STATUS_REG           (SC_BASE_REG+0x00)
#define SC_COMMAND_REG          (SC_BASE_REG+0x00)
#define SC_DATA0_REG            (SC_BASE_REG+0x04)
#define SC_DATA1_REG            (SC_BASE_REG+0x08)
#define SC_IDENTIFIER_REG       (SC_BASE_REG+0x0C)
#define SC_KEY_REG              (SC_BASE_REG+0x10)

#define SC_CMD_BUSY             0x80000000
#define SC_CMD_ERROR            0x40000000
#define SC_IRQ_PENDING          0x20000000

#define SC_CONFIG_GET           'c'
#define SC_CONFIG_SET           'C'
#define SC_SD_OP                'i'
#define SC_SD_SECTOR_SET        'I'
#define SC_SD_READ              's'
#define SC_SD_WRITE             'S'

#define SC_CFG_ROM_WRITE        1
#define SC_CFG_DD_MODE          3
#define SC_CFG_SAVE_TYPE        6

#define SC_SD_DEINIT            0
#define SC_SD_INIT              1
#define SC_SD_GET_STATUS        2
#define SC_SD_GET_INFO          3
#define SC_SD_BYTESWAP_ON       4
#define SC_SD_BYTESWAP_OFF      5

#define SC_DD_MODE_REGS         1
#define SC_DD_MODE_IPL          2

#define SC_IDENTIFIER           0x53437632  /* SCv2 */

#define SC_KEY_RESET            0x00000000
#define SC_KEY_LOCK             0xFFFFFFFF
#define SC_KEY_UNL              0x5F554E4C  /* _UNL */
#define SC_KEY_OCK              0x4F434B5F  /* OCK_ */

extern int __sc_sync(void);

#endif /* __SC_H__ */
int __sc_sync(void)
{
	while (__cart_rd(SC_STATUS_REG) & SC_CMD_BUSY);
	if (__cart_rd(SC_STATUS_REG) & SC_CMD_ERROR) return -1;
	return 0;
}
int sc_card_init(void)
{
	__cart_acs_get();
	__sc_sync();
	__cart_wr(SC_DATA1_REG, SC_SD_INIT);
	__cart_wr(SC_COMMAND_REG, SC_SD_OP);
	if (__sc_sync()) CART_ABORT();
	__cart_acs_rel();
	return 0;
}
int sc_card_rd_cart(u32 cart, u32 lba, u32 count)
{
	__cart_acs_get();
	__sc_sync();
	if (cart_card_byteswap)
	{
		__cart_wr(SC_DATA1_REG, SC_SD_BYTESWAP_ON);
		__cart_wr(SC_COMMAND_REG, SC_SD_OP);
		if (__sc_sync()) CART_ABORT();
	}
	__cart_wr(SC_DATA0_REG, lba);
	__cart_wr(SC_COMMAND_REG, SC_SD_SECTOR_SET);
	if (__sc_sync()) CART_ABORT();
	__cart_wr(SC_DATA0_REG, cart);
	__cart_wr(SC_DATA1_REG, count);
	__cart_wr(SC_COMMAND_REG, SC_SD_READ);
	if (__sc_sync()) CART_ABORT();
	if (cart_card_byteswap)
	{
		__cart_wr(SC_DATA1_REG, SC_SD_BYTESWAP_OFF);
		__cart_wr(SC_COMMAND_REG, SC_SD_OP);
		if (__sc_sync()) CART_ABORT();
	}
	__cart_acs_rel();
	return 0;
}

int sc_card_rd_dram(void *dram, u32 lba, u32 count)
{
	char *addr = dram;
	int i;
	int n;
	__cart_acs_get();
	__sc_sync();
	while (count > 0)
	{
		n = count < 16 ? count : 16;
		__cart_wr(SC_DATA0_REG, lba);
		__cart_wr(SC_COMMAND_REG, SC_SD_SECTOR_SET);
		if (__sc_sync()) CART_ABORT();
		__cart_wr(SC_DATA0_REG, SC_BUFFER_REG);
		__cart_wr(SC_DATA1_REG, n);
		__cart_wr(SC_COMMAND_REG, SC_SD_READ);
		if (__sc_sync()) CART_ABORT();
		if ((long)addr & 7)
		{
			for (i = 0; i < n; i++)
			{
				__cart_dma_rd(__cart_buf, SC_BUFFER_REG+512*i, 512);
				__cart_buf_wr(addr);
				addr += 512;
			}
		}
		else
		{
			__cart_dma_rd(addr, SC_BUFFER_REG, 512*n);
			addr += 512*n;
		}
		lba += n;
		count -= n;
	}
	__cart_acs_rel();
	return 0;
}
int sc_card_wr_cart(u32 cart, u32 lba, u32 count)
{
	__cart_acs_get();
	__sc_sync();
	__cart_wr(SC_DATA0_REG, lba);
	__cart_wr(SC_COMMAND_REG, SC_SD_SECTOR_SET);
	if (__sc_sync()) CART_ABORT();
	__cart_wr(SC_DATA0_REG, cart);
	__cart_wr(SC_DATA1_REG, count);
	__cart_wr(SC_COMMAND_REG, SC_SD_WRITE);
	if (__sc_sync()) CART_ABORT();
	__cart_acs_rel();
	return 0;
}
int sc_card_wr_dram(const void *dram, u32 lba, u32 count)
{
	const char *addr = dram;
	int i;
	int n;
	__cart_acs_get();
	__sc_sync();
	while (count > 0)
	{
		n = count < 16 ? count : 16;
		if ((long)addr & 7)
		{
			for (i = 0; i < n; i++)
			{
				__cart_buf_rd(addr);
				__cart_dma_wr(__cart_buf, SC_BUFFER_REG+512*i, 512);
				addr += 512;
			}
		}
		else
		{
			__cart_dma_wr(addr, SC_BUFFER_REG, 512*n);
			addr += 512*n;
		}
		__cart_wr(SC_DATA0_REG, lba);
		__cart_wr(SC_COMMAND_REG, SC_SD_SECTOR_SET);
		if (__sc_sync()) CART_ABORT();
		__cart_wr(SC_DATA0_REG, SC_BUFFER_REG);
		__cart_wr(SC_DATA1_REG, n);
		__cart_wr(SC_COMMAND_REG, SC_SD_WRITE);
		if (__sc_sync()) CART_ABORT();
		lba += n;
		count -= n;
	}
	__cart_acs_rel();
	return 0;
}

int sc_exit(void)
{
	__cart_acs_get();
	__sc_sync();
	__cart_wr(SC_DATA1_REG, SC_SD_DEINIT);
	__cart_wr(SC_COMMAND_REG, SC_SD_OP);
	__sc_sync();
	__cart_wr(SC_DATA0_REG, SC_CFG_ROM_WRITE);
	__cart_wr(SC_DATA1_REG, 0);
	__cart_wr(SC_COMMAND_REG, SC_CONFIG_SET);
	__sc_sync();
	__cart_wr(SC_KEY_REG, SC_KEY_RESET);
	__cart_wr(SC_KEY_REG, SC_KEY_LOCK);
	__cart_acs_rel();
	return 0;
}
int sc_init(void)
{
	u32 cfg;
	__cart_acs_get();
	__cart_wr(SC_KEY_REG, SC_KEY_RESET);
	__cart_wr(SC_KEY_REG, SC_KEY_UNL);
	__cart_wr(SC_KEY_REG, SC_KEY_OCK);
	if (__cart_rd(SC_IDENTIFIER_REG) != SC_IDENTIFIER) CART_ABORT();
	__sc_sync();
	__cart_wr(SC_DATA0_REG, SC_CFG_ROM_WRITE);
	__cart_wr(SC_DATA1_REG, 1);
	__cart_wr(SC_COMMAND_REG, SC_CONFIG_SET);
	__sc_sync();
	/* SC64 uses SDRAM for 64DD */
	__cart_wr(SC_DATA0_REG, SC_CFG_DD_MODE);
	__cart_wr(SC_COMMAND_REG, SC_CONFIG_GET);
	__sc_sync();
	cfg = __cart_rd(SC_DATA1_REG);
	/* Have registers */
	if (cfg & SC_DD_MODE_REGS)
	{
		cart_size = 0x2000000; /* 32 MiB */
	}
	/* Have IPL */
	else if (cfg & SC_DD_MODE_IPL)
	{
		cart_size = 0x3BC0000; /* 59.75 MiB */
	}
	else
	{
		/* SC64 does not have physical SRAM on board */
		/* The end of SDRAM is used for SRAM or FlashRAM save types */
		__cart_wr(SC_DATA0_REG, SC_CFG_SAVE_TYPE);
		__cart_wr(SC_COMMAND_REG, SC_CONFIG_GET);
		__sc_sync();
		/* Have SRAM or FlashRAM */
		if (__cart_rd(SC_DATA1_REG) >= 3)
		{
			cart_size = 0x3FE0000; /* 64 MiB - 128 KiB */
		}
		else
		{
			cart_size = 0x4000000; /* 64 MiB */
		}
	}
	__cart_dom1 = 0x802F0C05;
	__cart_acs_rel();
	return 0;
}
