#include "libultra/ultra64.h"
#include "libcart.h"
#include "controller.h"
#include "sys.h"
#include "PR/gbi.h"
#include "PR/os_cont.h"
#include "PR/os_pi.h"
#include "fzx_bordered_box.h"
#include "fzx_camera.h"
#include "fzx_effects.h"
#include "fzx_machine.h"
#include "fzx_math.h"
#include "fzx_object.h"
#include "fzx_racer.h"
#include "src/audio/rom/lib/audio.h"
#include "src/overlays/ovl_i2/transition.h"
#include "src/overlays/ovl_i3/background.h"
#include "src/overlays/ovl_i3/hud.h"
#include "src/overlays/ovl_i3/ovl_i3.h"
#include "src/overlays/ovl_i3/records_entry.h"
#include "unk_structs.h"
#include "controller.h"

typedef struct unk_800CF528 {
    s32 texture;
    f32 textureScale;
    s32 width;
    s32 tile;
    s32 unk_10;
    s16 textureCoordinateMask;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} unk_800CF528; // size = 0x20

typedef struct unk_800F8958 {
    SegmentChunk* chunk;
    Gfx* unk_04;
    Gfx* unk_08;
    Gfx* unk_0C;
    Gfx* unk_10;
    Gfx* unk_14;
    Gfx* unk_18;
    Gfx* unk_1C;
    Gfx* unk_20;
    Gfx* unk_24;
    Gfx* unk_28;
    s32 loadVtxIndex;
} unk_800F8958; // size = 0x30

typedef struct SegmentChunkGroup {
    SegmentChunk* startChunk;
    SegmentChunk* endChunk;
    f32 averageDepth;
    s32 drawState;
} SegmentChunkGroup; // size = 0x10


static u32 mod_write_bytes(u8* out, u32 off, void* src, u32 size) {
    memcpy(out + off, src, size);
    return off + size;
}

static u32 mod_read_bytes(u8* in, u32 off, void* dst, u32 size) {
    memcpy(dst, in + off, size);
    return off + size;
}

// generated methods
#include "src/mod/save_runner.c.inc"

#define KNOWN_SIZE 184630
#define SECTOR_SIZE 512
#define LBA_OFFSET  2000

__attribute__((aligned(16)))
s8 gSaveStateMemory[KNOWN_SIZE];
bool gHaveWrote = false;

/* Size of cartridge SDRAM */
extern u32 cart_size;

/* Cartridge type */
extern int cart_type;

extern uintptr_t gArenaStartPtrs[3];
extern uintptr_t gArenaEndPtrs[3];

void WriteRegionToSD(const void* src_, u32 size, u32* io_lba)
{
    const u8* src = (const u8*)src_;
    u32 remaining = size;
    u32 buffered = 0;

   while (remaining > 0)
    {
        u32 space = KNOWN_SIZE - buffered;
        u32 n = (remaining < space) ? remaining : space;

        /* copy into staging buffer */
        {
            u32 i;
            for (i = 0; i < n; i++)
            {
                gSaveStateMemory[buffered + i] = src[i];
            }
        }

        buffered += n;
        src += n;
        remaining -= n;

        /* write out all full sectors */
        if (buffered >= SECTOR_SIZE)
        {
            u32 full_bytes = buffered & ~(SECTOR_SIZE - 1); /* round down */
            u32 sectors = full_bytes / SECTOR_SIZE;

            osWritebackDCache(gSaveStateMemory, full_bytes);
            sc_card_wr_dram(gSaveStateMemory, *io_lba, sectors);

            *io_lba += sectors;

            /* move remainder down to front */
            {
                u32 remainder = buffered - full_bytes;
                u32 i;
                for (i = 0; i < remainder; i++)
                {
                    gSaveStateMemory[i] = gSaveStateMemory[full_bytes + i];
                }
                buffered = remainder;
            }
        }
    }

    /* After loop ends, buffered may contain <512 bytes.
       We must pad and write exactly one final sector if anything remains. */

    if (buffered > 0)
    {
        u32 i;
        for (i = buffered; i < SECTOR_SIZE; i++)
        {
            gSaveStateMemory[i] = 0;
        }

        osWritebackDCache(gSaveStateMemory, SECTOR_SIZE);
        sc_card_wr_dram(gSaveStateMemory, *io_lba, 1);

        *io_lba += 1;
    }
}

void Mod_Entry(void)
{
    if (cart_init() != 0) return;
    if (cart_type != CART_SC) return;
    if (cart_card_init() != 0) return;
}

void Mod_Save(void)
{
    u32 addr;
    u32 size;
    u32 offset;
    u32 sectors;
    u32 lastSectorWrite;
    gSaveStateMemory[4] = 'B';
    gSaveStateMemory[3] = 'D';
    gSaveStateMemory[0] = 'D';
    gSaveStateMemory[1] = 'E';
    gSaveStateMemory[2] = 'A';
    gSaveStateMemory[5] = 'E';
    gSaveStateMemory[6] = 'E';
    gSaveStateMemory[7] = 'F';
    
    offset = global_write(gSaveStateMemory, 8);
    *(u32*)&gSaveStateMemory[offset] = cart_size;
    offset += 4;
    sectors = (offset + SECTOR_SIZE - 1) / SECTOR_SIZE;
    addr = (cart_size / SECTOR_SIZE) - LBA_OFFSET;
    osWritebackDCache(gSaveStateMemory, sectors * SECTOR_SIZE);
    cart_card_wr_dram(gSaveStateMemory, addr, sectors);
    addr += sectors;
    size = (u32)(gArenaEndPtrs[0] - gArenaStartPtrs[0]);
    if (size > 0)
        WriteRegionToSD((void*)gArenaStartPtrs[0], size, &addr);

    size = (u32)(gArenaEndPtrs[1] - gArenaStartPtrs[1]);
    if (size > 0)
        WriteRegionToSD((void*)gArenaStartPtrs[1], size, &addr);

    size = (u32)(gArenaEndPtrs[2] - gArenaStartPtrs[2]);
    if (size > 0)
        WriteRegionToSD((void*)gArenaStartPtrs[2], size, &addr);
}

void Mod_Load(void)
{
  u32 addr;
  u32 size;
  u32 offset;
  u32 sectors;
  u32 lastSectorWrite;
  sectors = KNOWN_SIZE / SECTOR_SIZE;
  offset = LBA_OFFSET;
  sc_card_rd_dram(gSaveStateMemory, offset, sectors);
  osInvalDCache(gSaveStateMemory, sectors);

  // double check for dead beef
  global_load(gSaveStateMemory, 8);

  // Load all the arenas
}

extern Controller gControllers[];
void Mod_Main(void)
{
  u16 buttons;
  u16 pressed;

  /* Current buttons */
  buttons = gControllers[0].buttonPrev;
  if ((buttons & BTN_CDOWN) && (buttons & BTN_CRIGHT))
  {
    Mod_Save();
  }

  if ((buttons & BTN_CUP) && (buttons & BTN_CLEFT))
  {
    Mod_Load();
  }

}

void b(void)
{
    // @todo: Should probably only allow player 1?
    /*
    if ((gTestMessageSet == 0) && (racer->stateFlags & RACER_STATE_FLAGS_400000)) // && ((controller->buttonCurrent & (BTN_CDOWN | BTN_CUP | BTN_CLEFT | BTN_CRIGHT)) == 15))
    {
        buttonsCurrent = &gControllers[gPlayerControlPorts[racer->id]].buttonCurrent;
        // Scrambled slightly so I don't get confused if I see the rom
        if ((buttonsCurrent & BTN_START))
        {
          gTestMessageSet++;
        }
    }
    */
}
