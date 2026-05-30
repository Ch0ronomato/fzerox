#include "libultra/ultra64.h"
#include "libcart.h"
#include "controller.h"
#include "sys.h"
#include "PR/gbi.h"
#include "PR/os_cont.h"
#include "PR/os_pi.h"
#include "fzx_bordered_box.h"
#include "fzx_camera.h"
#include "fzx_game.h"
#include "fzx_effects.h"
#include "fzx_machine.h"
#include "fzx_math.h"
#include "fzx_object.h"
#include "fzx_course.h"
#include "fzx_save.h"
#include "fzx_racer.h"
#include "functions.h"
#include "src/audio/rom/lib/audio.h"
#include "src/overlays/ovl_i2/transition.h"
#include "src/overlays/ovl_i3/background.h"
#include "src/overlays/ovl_i3/hud.h"
#include "src/overlays/ovl_i3/menus.h"
#include "src/overlays/ovl_i3/ovl_i3.h"
#include "src/overlays/ovl_i3/records_entry.h"
#include "segment_symbols.h"
#include "unk_structs.h"

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

typedef void (*ModSegmentChunkCalculateReferencePosFunc)(SegmentChunk*, f32, f32, Mtx3F*, Vec3f*, Vec3f*, Vec3f*,
                                                         Vec3f*, Vec3f*);
typedef void (*ModSegmentChunkJoinFunc)(SegmentChunk*, SegmentChunk*, f32);

#ifndef EXPANSION_KIT
#define MOD_SEGMENT_CHUNK_GROUP_COUNT 64
#define MOD_SEGMENT_CHUNK_STORAGE_COUNT 1025
#else
#define MOD_SEGMENT_CHUNK_GROUP_COUNT 96
#define MOD_SEGMENT_CHUNK_STORAGE_COUNT 769
#endif

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

#define SECTOR_SIZE 512
#define LBA_OFFSET 2000
#define MOD_MAGIC_SIZE 7
#define MOD_METADATA_SIZE 12
#define MOD_FORMAT_VERSION 1
#define MOD_ARENA_STATE_SIZE (3 * 2 * sizeof(u32))

__attribute__((aligned(16)))
s8 gSaveStateMemory[MOD_HEADER_BUFFER_SIZE];
bool gHaveWrote = false;

static const u8 sModMagic[MOD_MAGIC_SIZE] = { 'D', 'E', 'A', 'D', 'B', 'E', 'E' };
static void WriteRegionToSD(const void* src_, u32 size, u32* io_lba);
static void ReadRegionFromSD(void* dst_, u32 size, u32* io_lba);

/* Size of cartridge SDRAM */
extern u32 cart_size;

/* Cartridge type */
extern int cart_type;

extern uintptr_t gArenaStartPtrs[3];
extern uintptr_t gArenaEndPtrs[3];
static uintptr_t sModArenaBasePtrs[3];
static uintptr_t sModArenaLimitPtrs[3];
#define gArenaStartPtrs sModArenaBasePtrs
#define gArenaEndPtrs sModArenaLimitPtrs
#include "src/mod/pointer_relocs.c.inc"
#undef gArenaStartPtrs
#undef gArenaEndPtrs

extern CourseInfo gCourseInfos[56];
extern Controller gControllers[];
extern CourseEffectsInfo gCourseEffectsInfo;
extern CourseEffectsInfo* D_800E12C0;
extern CourseInfo* gCurrentCourseInfo;
extern Background sBackgrounds[4];
extern s32 sBackgroundCount;
extern BackgroundContext sBackgroundCtx;
extern u16 sSkyboxFlags;
extern s32 sCloudCount;
extern void* sCloudTexture;
extern void* sSkyboxTexture;
extern void* sStarTexture;
extern void* sVenueFloorTexture;
extern s16 sBackgroundSpriteR;
extern s16 sBackgroundSpriteG;
extern s16 sBackgroundSpriteB;
extern CourseVenueFloor* sCourseVenueFloors[];
extern CourseSkyboxes* sCourseSkyboxes[];
extern Ghost gGhosts[3];
extern GhostRacer gGhostRacers[3];
extern Ghost* gFastestGhost;
extern GhostRacer* gFastestGhostRacer;
extern GfxPool* gGfxPool;
extern Racer gRacers[TOTAL_RACER_COUNT];
extern Racer* gRacersByPosition[TOTAL_RACER_COUNT];
extern RacerPairInfo sRacerPairInfo[TOTAL_RACER_COUNT * (TOTAL_RACER_COUNT - 1) / 2];
#ifndef EXPANSION_KIT
extern SegmentChunk gSegmentChunks[MOD_SEGMENT_CHUNK_STORAGE_COUNT];
extern EffectDrawData gEffectsDrawData[192];
#else
extern SegmentChunk gSegmentChunks[MOD_SEGMENT_CHUNK_STORAGE_COUNT];
extern EffectDrawData gEffectsDrawData[2][192];
#endif
extern CourseDecoration gCourseDecorations[32];
extern Effect gEffects[192];
extern Jump gJumps[4];
extern Landmine gLandmines[48];
extern Vtx* gCourseVtxPtr;
extern Vtx* gEffectsVtxEndPtr;
extern Vtx* gEffectsVtxPtr;
extern s32 gCourseIndex;
extern s32 gCurrentGhostType;
extern s32 gTotalRacers;
extern char* gCurrentTrackName;
extern char* gTrackNames[55];
extern s8 sGhostReplayRecordingBuffer[16200];
extern s8* sGhostReplayRecordingPtr;
extern s32 sGhostReplayRecordingSize;
extern Racer* sFastestGhostRacerRacer;
extern Racer* sLastRacer;
extern Racer* sPlayerRacer;
extern unk_800F8958 D_800F8958[2];
extern unk_800F8958* D_800F89B8;
extern unk_800F8958* D_800F89BC;
extern s32 D_800CF500;
extern s32 D_800CF50C;
extern s32 D_800F89C0;
extern SegmentChunk* D_800F89C8;
extern SegmentChunkGroup sSegmentChunkGroups[MOD_SEGMENT_CHUNK_GROUP_COUNT];
extern s32 D_800F892C;
extern s16 D_800F8930[5];
extern s32 D_800F89D4;
extern bool D_800F89D8;
extern s32 D_800E12C8[0x800];
extern SegmentChunk* sWorkingSegmentChunk;
extern SegmentChunk* sWorkingNextSegmentChunk;
extern s32 sLastTrackShapeType;
extern s32 sWorkingChunkJoinInfo;
extern Vec3s sVenuePipeFogColors[40];
extern Vec3s sVenueTunnelFogColors[40];
extern Vec3s* sPipeFogColors;
extern Vec3s* sTunnelFogColors;
extern Vtx* sTerrainEffectVtxStart;
extern bool gInCourseEditor;
extern s32 D_800DCCFC;
extern unk_80225800 D_80225800;
extern u8 aCloudTex[];
extern u8 D_F2207C8[];
extern s32 gNumPlayers;
extern s32 gGameMode;
extern s32 gSkyboxType;
extern s32 gVenueType;
extern uintptr_t gSegments[16];
extern uintptr_t gSegment16C8A0VramStart;
extern uintptr_t gSegment17B1E0VramStart;
extern uintptr_t gSegment1B8550VramStart;
extern uintptr_t gSegment1E23F0VramStart;
extern uintptr_t gSegment22B0A0VramStart;
extern uintptr_t gSegment235130VramStart;
extern uintptr_t gSegment2738A0VramStart;
extern uintptr_t gUnkBssVramStart;
extern u16 D_800CD2E0;
extern s8 D_800CD2E4;
extern s8 D_800CD2E8;
extern s8 D_800CD2EC;
extern s8 D_800CD2F0;
extern s8 D_800CD2F4;
extern Gfx D_80140F0[];
extern Gfx D_8014138[];
extern Gfx D_8014180[];
extern Gfx D_80141C8[];
extern Gfx D_8014210[];
extern Gfx D_8014268[];
extern Gfx D_80142C0[];
extern Gfx D_8014308[];
extern Gfx D_8014350[];
extern Gfx D_8014398[];
extern Gfx D_80143E0[];
extern Gfx D_8014430[];
extern Gfx D_8014480[];
extern Gfx D_80144D0[];
extern Gfx D_8014520[];
extern Gfx D_8014580[];
extern Gfx D_80145E0[];
extern Gfx D_8014640[];

#ifdef EXPANSION_KIT
extern bool gInCourseEditTestRun;
extern unk_80128C94* D_80128C90;
extern unk_80128C94* D_80128C94;
extern RomOffset gRomSegmentPairs[][2];
#endif

extern void Racer_UpdateRivalRacer(void);
extern void Racer_UpdateRacerPairInfo(void);
extern void Racer_UpdateRacePositions(void);
extern void Racer_UpdateNearestRacer(void);
extern void Background_Init(void);
extern void Background_InitBackgroundSprites(void);
extern void func_80074428(s32 courseIndex);
extern void func_80074634(CourseInfo* courseInfo);
extern void func_80079EC8(void);
extern void Course_GadgetsInit(s32 courseIndex);
extern void Course_SegmentLengthsInit(CourseInfo* courseInfo);
extern s32 Course_SegmentJoinsInit(CourseInfo* courseInfo);
extern void Course_SegmentContinuousFlagInit(CourseInfo* courseInfo);
extern void Course_SegmentFormsInit(CourseInfo* courseInfo);
extern void Course_JumpsViewInteractDataInit(void);
extern void Course_LandminesViewInteractDataInit(void);
extern void Course_DecorationsViewInteractDataInit(void);
extern void Course_EffectsViewInteractDataInit(bool arg0);
extern void Course_ChunkCalculateRoadAirReferencePos(SegmentChunk*, f32, f32, Mtx3F*, Vec3f*, Vec3f*, Vec3f*, Vec3f*,
                                                     Vec3f*);
extern void Course_ChunkCalculateWalledRoadReferencePos(SegmentChunk*, f32, f32, Mtx3F*, Vec3f*, Vec3f*, Vec3f*,
                                                        Vec3f*, Vec3f*);
extern void Course_ChunkCalculatePipeReferencePos(SegmentChunk*, f32, f32, Mtx3F*, Vec3f*, Vec3f*, Vec3f*, Vec3f*,
                                                  Vec3f*);
extern void Course_ChunkCalculateCylinderReferencePos(SegmentChunk*, f32, f32, Mtx3F*, Vec3f*, Vec3f*, Vec3f*,
                                                      Vec3f*, Vec3f*);
extern void Course_ChunkCalculateHalfPipeReferencePos(SegmentChunk*, f32, f32, Mtx3F*, Vec3f*, Vec3f*, Vec3f*,
                                                      Vec3f*, Vec3f*);
extern void Course_ChunkCalculateTunnelReferencePos(SegmentChunk*, f32, f32, Mtx3F*, Vec3f*, Vec3f*, Vec3f*, Vec3f*,
                                                    Vec3f*);
extern void Course_ChunkCalculateBorderlessRoadReferencePos(SegmentChunk*, f32, f32, Mtx3F*, Vec3f*, Vec3f*, Vec3f*,
                                                            Vec3f*, Vec3f*);
extern void Course_ChunkJoinEqual(SegmentChunk*, SegmentChunk*, f32);
extern void Course_ChunkJoinPipeTunnel(SegmentChunk*, SegmentChunk*, f32);
extern void Course_ChunkJoinCylinder(SegmentChunk*, SegmentChunk*, f32);
extern s32 func_800A1954(CourseInfo* courseInfo);
extern void func_800A4BAC(void);
extern void func_800A4B54(void);
extern void func_800A4D0C(s32 arg0);
extern void func_800747EC(s32 venue);
extern void func_8007F4E0(s32 venue, s32 skybox);
extern void func_8009CED0(s32 venue);
extern uintptr_t Segment_SetAddress(s32 segment, uintptr_t addr);
extern uintptr_t Segment_SetPhysicalAddress(s32 segment, uintptr_t addr);
extern ModSegmentChunkCalculateReferencePosFunc sSegmentChunkCalculateReferencePosFuncs[];
extern ModSegmentChunkJoinFunc sSegmentChunkJoinFuncs[];

static u32 Mod_RoundUpToSector(u32 size) {
    return (size + SECTOR_SIZE - 1) / SECTOR_SIZE;
}

static u32 Mod_HeaderByteCount(void)
{
    return MOD_METADATA_SIZE + MOD_GLOBAL_STATE_SIZE + MOD_POINTER_RELOC_SIZE + MOD_ARENA_STATE_SIZE + sizeof(cart_size);
}

static u32 Mod_ArenaStateOffset(void)
{
    return MOD_METADATA_SIZE + MOD_GLOBAL_STATE_SIZE + MOD_POINTER_RELOC_SIZE;
}

static void Mod_CacheArenaBounds(void)
{
    uintptr_t savedStarts[ARRAY_COUNT(sModArenaBasePtrs)];
    uintptr_t savedEnds[ARRAY_COUNT(sModArenaLimitPtrs)];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(savedStarts); i++) {
        savedStarts[i] = gArenaStartPtrs[i];
        savedEnds[i] = gArenaEndPtrs[i];
    }

    Arena_StartInit();
    Arena_EndInit();

    for (i = 0; i < ARRAY_COUNT(sModArenaBasePtrs); i++) {
        sModArenaBasePtrs[i] = gArenaStartPtrs[i];
        sModArenaLimitPtrs[i] = gArenaEndPtrs[i];
        gArenaStartPtrs[i] = savedStarts[i];
        gArenaEndPtrs[i] = savedEnds[i];
    }
}

static bool Mod_ArenaFrontiersAreValid(const uintptr_t* starts, const uintptr_t* ends)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sModArenaBasePtrs); i++) {
        if ((starts[i] < sModArenaBasePtrs[i]) || (starts[i] > ends[i]) || (ends[i] > sModArenaLimitPtrs[i])) {
            return false;
        }
    }

    return true;
}

static u32 Mod_WriteArenaFrontiers(u8* out, u32 off)
{
    u32 value;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sModArenaBasePtrs); i++) {
        value = (u32) gArenaStartPtrs[i];
        off = mod_write_bytes(out, off, &value, sizeof(value));
    }

    for (i = 0; i < ARRAY_COUNT(sModArenaLimitPtrs); i++) {
        value = (u32) gArenaEndPtrs[i];
        off = mod_write_bytes(out, off, &value, sizeof(value));
    }

    return off;
}

static u32 Mod_ReadArenaFrontiers(const u8* in, u32 off, uintptr_t* starts, uintptr_t* ends)
{
    u32 value;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sModArenaBasePtrs); i++) {
        memcpy(&value, in + off, sizeof(value));
        starts[i] = value;
        off += sizeof(value);
    }

    for (i = 0; i < ARRAY_COUNT(sModArenaLimitPtrs); i++) {
        memcpy(&value, in + off, sizeof(value));
        ends[i] = value;
        off += sizeof(value);
    }

    return off;
}

static bool Mod_HeaderIsValid(const u8* in) {
    u32 saved_header_size;
    s8 i = 0;

    for (; i < MOD_MAGIC_SIZE; i++)
    {
        if (sModMagic[i] != in[i])
        {
            return false;
        }
    }

    if (in[MOD_MAGIC_SIZE] != MOD_FORMAT_VERSION)
    {
        return false;
    }

    memcpy(&saved_header_size, in + 8, sizeof(saved_header_size));
    if (saved_header_size != Mod_HeaderByteCount())
    {
        return false;
    }

    if (saved_header_size > sizeof(gSaveStateMemory))
    {
        return false;
    }

    return true;
}

static void Mod_WriteHeaderMetadata(u8* out)
{
    u32 header_size = Mod_HeaderByteCount();

    memcpy(out, sModMagic, MOD_MAGIC_SIZE);
    out[MOD_MAGIC_SIZE] = MOD_FORMAT_VERSION;
    memcpy(out + 8, &header_size, sizeof(header_size));
}

static u32 Mod_HeaderOffsetStart(void)
{
    return MOD_METADATA_SIZE;
}

static u32 Mod_HeaderSectorCount(void)
{
    return Mod_RoundUpToSector(Mod_HeaderByteCount());
}

static void Mod_SaveArenaRegions(u32* io_addr)
{
    u32 size;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sModArenaBasePtrs); i++) {
        size = (u32) (gArenaStartPtrs[i] - sModArenaBasePtrs[i]);
        if (size > 0) {
            WriteRegionToSD((void*) sModArenaBasePtrs[i], size, io_addr);
        }

        size = (u32) (sModArenaLimitPtrs[i] - gArenaEndPtrs[i]);
        if (size > 0) {
            WriteRegionToSD((void*) gArenaEndPtrs[i], size, io_addr);
        }
    }
}

static void Mod_LoadArenaRegions(const uintptr_t* starts, const uintptr_t* ends, u32* io_addr)
{
    u32 size;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sModArenaBasePtrs); i++) {
        size = (u32) (starts[i] - sModArenaBasePtrs[i]);
        if (size > 0) {
            ReadRegionFromSD((void*) sModArenaBasePtrs[i], size, io_addr);
        }

        size = (u32) (sModArenaLimitPtrs[i] - ends[i]);
        if (size > 0) {
            ReadRegionFromSD((void*) ends[i], size, io_addr);
        }
    }
}

static void Mod_RebuildTrackPointers(void) {
    func_8007D9D0();
    if ((gCourseIndex >= 0) && (gCourseIndex < ARRAY_COUNT(gTrackNames))) {
        gCurrentTrackName = gTrackNames[gCourseIndex];
    } else {
        gCurrentTrackName = NULL;
    }
}

static void Mod_RebuildRaceOrder(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gRacersByPosition); i++) {
        gRacersByPosition[i] = NULL;
    }

    for (i = 0; i < gTotalRacers; i++) {
        if ((gRacers[i].position > 0) && (gRacers[i].position <= ARRAY_COUNT(gRacersByPosition))) {
            gRacersByPosition[gRacers[i].position - 1] = &gRacers[i];
        }
    }
}

static void Mod_RebuildGhostPointers(void) {
    s32 i;
    s32 fastestGhostTime = 0x7FFFFFFF;
    s32 fastestGhostRacerTime = 0x7FFFFFFF;

    gFastestGhost = NULL;
    gFastestGhostRacer = NULL;
    sFastestGhostRacerRacer = NULL;

    for (i = 0; i < ARRAY_COUNT(gGhostRacers); i++) {
        if (gGhostRacers[i].replayIndex < 0) {
            gGhostRacers[i].replayIndex = 0;
        } else if (gGhostRacers[i].replayIndex > gGhosts[i].replaySize) {
            gGhostRacers[i].replayIndex = gGhosts[i].replaySize;
        }

        gGhostRacers[i].ghost = &gGhosts[i];
        gGhostRacers[i].replayPtr = &gGhosts[i].replayData[gGhostRacers[i].replayIndex];
        gGhostRacers[i].racer = &gRacers[i + 1];

        if ((gCurrentCourseInfo == NULL) || (gGhosts[i].encodedCourseIndex != gCurrentCourseInfo->encodedCourseIndex)) {
            continue;
        }

        if ((gGhosts[i].ghostType == GHOST_PLAYER) && (gGhosts[i].raceTime < fastestGhostTime)) {
            fastestGhostTime = gGhosts[i].raceTime;
            gFastestGhost = &gGhosts[i];
        }

        if ((gCurrentGhostType != GHOST_NONE) && (gGhosts[i].ghostType == gCurrentGhostType) &&
            (gGhosts[i].raceTime < fastestGhostRacerTime)) {
            fastestGhostRacerTime = gGhosts[i].raceTime;
            gFastestGhostRacer = &gGhostRacers[i];
        }
    }

    if (gFastestGhostRacer != NULL) {
        sFastestGhostRacerRacer = gFastestGhostRacer->racer;
    }
}

static void Mod_RebuildRacerPointers(void) {
    CourseSegment* segments;
    CourseSegment* segmentEnd;
    s32 i;

    if ((gCurrentCourseInfo == NULL) || (gCurrentCourseInfo->segmentCount <= 0)) {
        return;
    }

    segments = gCurrentCourseInfo->courseSegments;
    segmentEnd = &segments[gCurrentCourseInfo->segmentCount];

    for (i = 0; i < gTotalRacers; i++) {
        CourseSegment* segment = gRacers[i].segmentPositionInfo.courseSegment;
        s32 segmentIndex = 0;

        if ((segment >= segments) && (segment < segmentEnd)) {
            segmentIndex = segment - segments;
        } else if ((gRacers[i].lastSegmentIndex >= 0) &&
                   (gRacers[i].lastSegmentIndex < gCurrentCourseInfo->segmentCount)) {
            segmentIndex = gRacers[i].lastSegmentIndex;
        }

        gRacers[i].segmentPositionInfo.courseSegment = &segments[segmentIndex];
        gRacers[i].unk_28C = NULL;
        gRacers[i].racerAhead = NULL;
        gRacers[i].racerBehind = NULL;
    }

    for (i = 0; i < ARRAY_COUNT(sRacerPairInfo); i++) {
        sRacerPairInfo[i].leadRacer = NULL;
        sRacerPairInfo[i].trailRacer = NULL;
        sRacerPairInfo[i].areColliding = false;
    }
}

static void Mod_ReprojectRacersOntoCourse(void) {
    s32 i;

    if ((gCurrentCourseInfo == NULL) || (gCurrentCourseInfo->segmentCount <= 0)) {
        return;
    }

    for (i = 0; i < gTotalRacers; i++) {
        Racer* racer = &gRacers[i];

        if (func_8009EBEC(&racer->segmentPositionInfo, racer->segmentPositionInfo.pos.x, racer->segmentPositionInfo.pos.y,
                          racer->segmentPositionInfo.pos.z, 100, 1.0f) != 0) {
            continue;
        }

        racer->segmentPositionInfo.segmentLengthProportion = Course_SplineGetLengthInfo(
            racer->segmentPositionInfo.courseSegment, racer->segmentPositionInfo.segmentTValue, &racer->lapDistance);
        Course_SplineGetBasis(racer->segmentPositionInfo.courseSegment, racer->segmentPositionInfo.segmentTValue,
                              &racer->segmentBasis, racer->segmentPositionInfo.segmentLengthProportion);

        racer->currentRadiusLeft = (racer->segmentPositionInfo.segmentLengthProportion *
                                    (racer->segmentPositionInfo.courseSegment->next->radiusLeft -
                                     racer->segmentPositionInfo.courseSegment->radiusLeft)) +
                                   racer->segmentPositionInfo.courseSegment->radiusLeft;
        racer->currentRadiusRight = (racer->segmentPositionInfo.segmentLengthProportion *
                                     (racer->segmentPositionInfo.courseSegment->next->radiusRight -
                                      racer->segmentPositionInfo.courseSegment->radiusRight)) +
                                    racer->segmentPositionInfo.courseSegment->radiusRight;
        racer->lastSegmentIndex = racer->segmentPositionInfo.courseSegment->segmentIndex;
    }
}

static void Mod_InitCourseChunkScratch(void) {
    D_800F8958[0].unk_04 = D_80140F0;
    D_800F8958[0].unk_08 = D_8014180;
    D_800F8958[0].unk_0C = D_80140F0;
    D_800F8958[0].unk_10 = D_8014210;
    D_800F8958[0].unk_14 = D_80142C0;
    D_800F8958[0].unk_18 = D_8014308;
    D_800F8958[0].unk_1C = D_80143E0;
    D_800F8958[0].unk_20 = D_8014430;
    D_800F8958[0].unk_24 = D_8014520;
    D_800F8958[0].unk_28 = D_80145E0;
    D_800F8958[0].loadVtxIndex = 0;
    D_800F8958[1].unk_04 = D_8014138;
    D_800F8958[1].unk_08 = D_80141C8;
    D_800F8958[1].unk_0C = D_8014138;
    D_800F8958[1].unk_10 = D_8014268;
    D_800F8958[1].unk_14 = D_8014350;
    D_800F8958[1].unk_18 = D_8014398;
    D_800F8958[1].unk_1C = D_8014480;
    D_800F8958[1].unk_20 = D_80144D0;
    D_800F8958[1].unk_24 = D_8014580;
    D_800F8958[1].unk_28 = D_8014640;
    D_800F8958[1].loadVtxIndex = 8;
}

static void Mod_ResetCourseScratchState(void) {
    s32 i;

    func_800A4BAC();

    D_800F8958[0].chunk = NULL;
    D_800F8958[1].chunk = NULL;
    D_800F89B8 = NULL;
    D_800F89BC = NULL;
    D_800F89C0 = 0;
    D_800F89C8 = NULL;
    sWorkingSegmentChunk = NULL;
    sWorkingNextSegmentChunk = NULL;
    for (i = 0; i < ARRAY_COUNT(sSegmentChunkGroups); i++) {
        sSegmentChunkGroups[i].startChunk = NULL;
        sSegmentChunkGroups[i].endChunk = NULL;
        sSegmentChunkGroups[i].averageDepth = 0.0f;
        sSegmentChunkGroups[i].drawState = 0;
    }
}

static void Mod_ResetBackgroundState(void) {
    Background* background;
    Camera* camera;
    CourseVenueFloor* venueFloor;
    CourseSkyboxes* skybox;
    s32 i;

    if ((gVenueType < 0) || (gVenueType > VENUE_ENDING) || (gSkyboxType < 0) || (gSkyboxType > SKYBOX_SKY_BLUE)) {
        return;
    }

    venueFloor = sCourseVenueFloors[gVenueType];
    skybox = sCourseSkyboxes[gSkyboxType];

    sBackgroundCount = gNumPlayers;
    if (sBackgroundCount < 0) {
        sBackgroundCount = 0;
    } else if (sBackgroundCount > ARRAY_COUNT(sBackgrounds)) {
        sBackgroundCount = ARRAY_COUNT(sBackgrounds);
    }

    sBackgroundCtx.venueFloor = venueFloor;
    sBackgroundCtx.skybox = skybox;
    sSkyboxFlags = skybox->flags;

    if (gCurrentCourseInfo != NULL) {
        gCurrentCourseInfo->courseFogColors[0] = skybox->courseFogR;
        gCurrentCourseInfo->courseFogColors[1] = skybox->courseFogG;
        gCurrentCourseInfo->courseFogColors[2] = skybox->courseFogB;

        if ((skybox->racerFogR == 0) && (skybox->racerFogG == 0) && (skybox->racerFogB == 0)) {
            gCurrentCourseInfo->racerFogColors[0] = skybox->courseFogR;
            gCurrentCourseInfo->racerFogColors[1] = skybox->courseFogG;
            gCurrentCourseInfo->racerFogColors[2] = skybox->courseFogB;
        } else {
            gCurrentCourseInfo->racerFogColors[0] = skybox->racerFogR;
            gCurrentCourseInfo->racerFogColors[1] = skybox->racerFogG;
            gCurrentCourseInfo->racerFogColors[2] = skybox->racerFogB;
        }
    }

    sBackgroundSpriteR = skybox->backgroundSpriteR;
    sBackgroundSpriteG = skybox->backgroundSpriteG;
    sBackgroundSpriteB = skybox->backgroundSpriteB;

    if (sSkyboxFlags & SKYBOX_CLOUDY) {
        if (gNumPlayers >= 3) {
            sCloudCount = 0;
            sSkyboxFlags &= ~SKYBOX_CLOUDY;
        } else {
            sCloudCount = 1;
        }
    } else {
        sCloudCount = 0;
    }

    for (i = 0, background = sBackgrounds, camera = gCameras; i < sBackgroundCount; i++, background++, camera++) {
        background->pos.y = -750.0f;
        if (gNumPlayers == 2) {
            background->scrollDepth = 4300.0f;
            background->skyboxDepth = 5300.0f;
        } else {
            background->scrollDepth = 6000.0f;
            background->skyboxDepth = 7000.0f;
        }
        background->floorScroll.relativeEyeHeight = -750.0f;
        background->floorScroll.relativeBackgroundHeight = -750.0f;
        background->floorScroll.xScale = venueFloor->xScale;
        background->floorScroll.zScale = venueFloor->zScale;
        background->floorScroll.xScrollSpeed = venueFloor->xScrollSpeed;
        background->floorScroll.zScrollSpeed = venueFloor->zScrollSpeed;
        background->aspectRatio = camera->fovScaleY / camera->fovScaleX;
    }
}

static void Mod_RebindBackgroundContext(void) {
    if ((gVenueType < 0) || (gVenueType > VENUE_ENDING) || (gSkyboxType < 0) || (gSkyboxType > SKYBOX_SKY_BLUE)) {
        return;
    }

    sBackgroundCtx.venueFloor = sCourseVenueFloors[gVenueType];
    sBackgroundCtx.skybox = sCourseSkyboxes[gSkyboxType];
}

static void Mod_RebindBackgroundTextures(void) {
    if ((sBackgroundCtx.venueFloor == NULL) || (sBackgroundCtx.skybox == NULL)) {
        return;
    }

    sSkyboxTexture = func_80078104(sBackgroundCtx.skybox->texture, 64 * 1 * sizeof(u16), 0, 0, false);
    sVenueFloorTexture = func_80078104(sBackgroundCtx.venueFloor->texture, 64 * 32 * sizeof(u16), 0, 0, false);
    sCloudTexture = NULL;
    sStarTexture = NULL;

    if (sSkyboxFlags & SKYBOX_CLOUDY) {
        sCloudTexture = func_80078104(aCloudTex, 64 * 32 * sizeof(u8), 0, 0, false);
    }
    if (sSkyboxFlags & SKYBOX_STARRY) {
        sStarTexture = func_80078104(D_F2207C8, 8 * 8 * sizeof(u8), 0, 0, false);
    }
}

static void Mod_RebuildBackgroundSprites(void) {
    Background_InitBackgroundSprites();
}

static void Mod_RebuildCourseFunctionTables(void) {
    sSegmentChunkCalculateReferencePosFuncs[0] = Course_ChunkCalculateRoadAirReferencePos;
    sSegmentChunkCalculateReferencePosFuncs[1] = Course_ChunkCalculateWalledRoadReferencePos;
    sSegmentChunkCalculateReferencePosFuncs[2] = Course_ChunkCalculatePipeReferencePos;
    sSegmentChunkCalculateReferencePosFuncs[3] = Course_ChunkCalculateCylinderReferencePos;
    sSegmentChunkCalculateReferencePosFuncs[4] = Course_ChunkCalculateHalfPipeReferencePos;
    sSegmentChunkCalculateReferencePosFuncs[5] = Course_ChunkCalculateTunnelReferencePos;
    sSegmentChunkCalculateReferencePosFuncs[6] = Course_ChunkCalculateRoadAirReferencePos;
    sSegmentChunkCalculateReferencePosFuncs[7] = Course_ChunkCalculateBorderlessRoadReferencePos;

    sSegmentChunkJoinFuncs[0] = Course_ChunkJoinEqual;
    sSegmentChunkJoinFuncs[1] = Course_ChunkJoinEqual;
    sSegmentChunkJoinFuncs[2] = Course_ChunkJoinPipeTunnel;
    sSegmentChunkJoinFuncs[3] = Course_ChunkJoinCylinder;
    sSegmentChunkJoinFuncs[4] = Course_ChunkJoinEqual;
    sSegmentChunkJoinFuncs[5] = Course_ChunkJoinPipeTunnel;
    sSegmentChunkJoinFuncs[6] = Course_ChunkJoinEqual;
    sSegmentChunkJoinFuncs[7] = Course_ChunkJoinEqual;
}

static void Mod_RebuildCourseSegmentPointers(void) {
    CourseSegment* segments;
    CourseSegment* segment;
    s32 i;
    s32 j;

    if ((gCurrentCourseInfo == NULL) || (gCurrentCourseInfo->segmentCount <= 0)) {
        return;
    }

    func_800A4B54();

    segments = gCurrentCourseInfo->courseSegments;
    for (i = 0; i < gCurrentCourseInfo->segmentCount; i++) {
        segment = &segments[i];
        segment->segmentIndex = i;
        segment->next = &segments[(i + 1) % gCurrentCourseInfo->segmentCount];
        segment->prev = &segments[(i + gCurrentCourseInfo->segmentCount - 1) % gCurrentCourseInfo->segmentCount];
        segment->startChunk = NULL;
        segment->endChunk = NULL;
        segment->jumpsStart = NULL;
        segment->jumpsEnd = NULL;
        segment->landminesStart = NULL;
        segment->landminesEnd = NULL;
        segment->effectsStart = NULL;
        segment->effectsEnd = NULL;
        for (j = 0; j < ARRAY_COUNT(segment->unk_5C); j++) {
            segment->unk_5C[j] = 0;
        }
    }

    for (i = 0; i < gSegmentChunkCount; i++) {
        s32 segmentIndex = gSegmentChunks[i].segmentIndex;

        if ((segmentIndex < 0) || (segmentIndex >= gCurrentCourseInfo->segmentCount)) {
            continue;
        }

        segment = &segments[segmentIndex];
        if (segment->startChunk == NULL) {
            segment->startChunk = &gSegmentChunks[i];
        }
        segment->endChunk = &gSegmentChunks[i + 1];
    }
}

static void Mod_RebuildCourseViewInteractState(void) {
    bzero(D_800E12C8, sizeof(D_800E12C8));
    bzero(gCourseDecorations, sizeof(gCourseDecorations));
    bzero(gEffects, sizeof(gEffects));
    bzero(gEffectsDrawData, sizeof(gEffectsDrawData));
    bzero(gJumps, sizeof(gJumps));
    bzero(gLandmines, sizeof(gLandmines));

    // These buffers and pointers are rebuilt during Race_Init and are not safe to trust after a raw restore.
    Course_LandminesViewInteractDataInit();
    Course_JumpsViewInteractDataInit();
    Course_DecorationsViewInteractDataInit();
    Course_EffectsViewInteractDataInit(false);
}

static void Mod_RecomputeCourseRenderDistances(void) {
    CourseSegment* segment;
    s32 i;

    if ((gCurrentCourseInfo == NULL) || (gCurrentCourseInfo->segmentCount <= 0)) {
        return;
    }

    sCourseRenderOriginDistance = 900.0f;
    segment = gCurrentCourseInfo->courseSegments;
    for (i = 0; i < gCurrentCourseInfo->segmentCount; i++, segment = segment->next) {
        if (sCourseRenderOriginDistance < segment->radiusLeft) {
            sCourseRenderOriginDistance = segment->radiusLeft;
        }
        if (sCourseRenderOriginDistance < segment->radiusRight) {
            sCourseRenderOriginDistance = segment->radiusRight;
        }
    }
    sCourseRenderOriginDistance += 100.0f;
    sCourseFarRenderDistance = sCourseRenderOriginDistance + 4500.0f;
    D_800F894C += sCourseRenderOriginDistance - 1000.0f;
    D_800F8950 += sCourseRenderOriginDistance - 1000.0f;
}

static bool Mod_SavedCourseRuntimeLooksSane(void) {
    s32 i;

    if ((gCurrentCourseInfo == NULL) || (gCurrentCourseInfo->segmentCount <= 0) || (gCurrentCourseInfo->segmentCount > 64)) {
        return false;
    }

    if ((gSegmentChunkCount <= 0) || (gSegmentChunkCount >= MOD_SEGMENT_CHUNK_STORAGE_COUNT)) {
        return false;
    }

    for (i = 0; i < gSegmentChunkCount; i++) {
        if ((gSegmentChunks[i].segmentIndex < 0) || (gSegmentChunks[i].segmentIndex >= gCurrentCourseInfo->segmentCount)) {
            return false;
        }
    }

    return true;
}

static void Mod_RegenerateCourseRuntimeStateFromCourseData(void) {
    // Fall back to a full rebuild when the saved runtime course state is clearly invalid.
    bzero(gSegmentChunks, sizeof(gSegmentChunks));
    bzero(&D_802C2020, sizeof(D_802C2020));
    bzero(&D_802CDFD8, sizeof(D_802CDFD8));
    gSegmentChunkCount = 0;
    sLastSegmentChunk = NULL;

    if (!gInCourseEditor) {
        func_80074428(gCourseIndex);
        func_80074634(gCurrentCourseInfo);
        Course_SplineCalculateTensions(gCurrentCourseInfo);
        Course_SegmentsInit();
    }

    Mod_RebuildCourseSegmentPointers();
    Course_SegmentLengthsInit(gCurrentCourseInfo);
    Course_GadgetsInit(gCourseIndex);
    Course_SegmentJoinsInit(gCurrentCourseInfo);
    Course_SegmentContinuousFlagInit(gCurrentCourseInfo);
    Course_SegmentFormsInit(gCurrentCourseInfo);
    func_800A1954(gCurrentCourseInfo);
}

static void Mod_RebuildCourseRuntimeState(void) {
    if ((gCurrentCourseInfo == NULL) || (gCurrentCourseInfo->segmentCount <= 0)) {
        sLastSegmentChunk = NULL;
        return;
    }

    D_800CF500 = 0;
    D_800CF50C = 0;
    sLastTrackShapeType = -1;
    D_800F892C = -1;
    bzero(D_800F8930, sizeof(D_800F8930));
    D_800F89D4 = 0;
    D_800F89D8 = true;
    sWorkingChunkJoinInfo = 0;

    func_800A4D0C((gNumPlayers >= 3) ? 2 : 1);
    Mod_RebuildCourseFunctionTables();

    if (Mod_SavedCourseRuntimeLooksSane()) {
        // Prefer the saved runtime chunk table when it survives restore. It matches the
        // original in-race geometry more closely than regenerating from saved CourseData.
        Mod_RebuildCourseSegmentPointers();
    } else {
        Mod_RegenerateCourseRuntimeStateFromCourseData();
    }

    Mod_RecomputeCourseRenderDistances();

    if (gSegmentChunkCount > 0) {
        sLastSegmentChunk = &gSegmentChunks[gSegmentChunkCount];
        gSegmentChunks[gSegmentChunkCount] = gSegmentChunks[0];
    } else {
        sLastSegmentChunk = NULL;
    }
}

static void Mod_RebindSegmentTable(void) {
    Segment_SetAddress(0, 0);
    Segment_SetPhysicalAddress(1, gGfxPool);
    Segment_SetAddress(2, gUnkBssVramStart);
    Segment_SetAddress(3, gSegment17B1E0VramStart);
    Segment_SetAddress(4, gSegment1B8550VramStart);
    Segment_SetAddress(5, gSegment2738A0VramStart);
    Segment_SetAddress(7, gSegment1E23F0VramStart);
    Segment_SetAddress(8, gSegment16C8A0VramStart);
    Segment_SetAddress(9, gSegment22B0A0VramStart);
    Segment_SetAddress(10, gSegment235130VramStart);

#ifdef EXPANSION_KIT
    Segment_SetPhysicalAddress(6, &D_80128C90[D_800DCCFC]);
#endif
}

static void Mod_ReloadCourseTrackGfx(void) {
    uintptr_t src;

    CLEAR_DATA_CACHE(osPhysicalToVirtual(gSegment16C8A0VramStart), SEGMENT_DATA_SIZE_CONST(course_track_gfx));
#ifndef EXPANSION_KIT
    Dma_LoadAssets(SEGMENT_ROM_START(course_track_gfx),
                   (u8*) ((uintptr_t) osPhysicalToVirtual(gSegment16C8A0VramStart) +
                          (size_t) SEGMENT_DATA_SIZE_CONST(course_track_gfx)),
                   SEGMENT_ROM_SIZE(course_track_gfx));
#else
    Dma_LoadAssets(gRomSegmentPairs[15][0],
                   (u8*) ((uintptr_t) osPhysicalToVirtual(gSegment16C8A0VramStart) +
                          (size_t) SEGMENT_DATA_SIZE_CONST(course_track_gfx)),
                   SEGMENT_VRAM_SIZE(course_track_gfx));
#endif

    src = (uintptr_t) osPhysicalToVirtual(gSegment16C8A0VramStart) + (size_t) SEGMENT_DATA_SIZE_CONST(course_track_gfx);
    mio0Decode((u8*) src, osPhysicalToVirtual(gSegment16C8A0VramStart));
}

static void Mod_RearmGraphicsAssetLoads(void) {
    D_800CD2E0 = 0;
    D_800CD2E4 = false;
    D_800CD2E8 = false;
    D_800CD2EC = false;
    D_800CD2F0 = -1;
    D_800CD2F4 = false;

    switch (gGameMode) {
        case GAMEMODE_GP_RACE:
        case GAMEMODE_PRACTICE:
        case GAMEMODE_VS_2P:
        case GAMEMODE_VS_3P:
        case GAMEMODE_VS_4P:
        case GAMEMODE_RECORDS:
        case GAMEMODE_TIME_ATTACK:
        case GAMEMODE_DEATH_RACE:
            D_800CD2E0 = 1;
            D_800CD2E4 = true;
            D_800CD2EC = true;
            break;
        case GAMEMODE_GP_END_CS:
            D_800CD2E0 = 1;
            D_800CD2E4 = true;
            D_800CD2EC = true;
            D_800CD2F4 = true;
            break;
#ifdef EXPANSION_KIT
        case GAMEMODE_COURSE_EDIT:
            D_800CD2E0 = 1;
            D_800CD2E4 = true;
            D_800CD2E8 = true;
            D_800CD2EC = true;
            break;
        case GAMEMODE_CREATE_MACHINE:
            D_800CD2E0 = 1;
            D_800CD2E4 = true;
            D_800CD2E8 = true;
            break;
#endif
        default:
            break;
    }
}

static void Mod_PostLoadFixups(void) {
    Mod_RebuildTrackPointers();
    Mod_RebindSegmentTable();
    Mod_ReloadCourseTrackGfx();

    if (gInCourseEditor) {
        gCurrentCourseInfo = &gCourseInfos[0];
    } else if ((gCourseIndex >= 0) && (gCourseIndex < ARRAY_COUNT(gCourseInfos))) {
        gCurrentCourseInfo = &gCourseInfos[gCourseIndex];
    } else {
        gCurrentCourseInfo = NULL;
    }

    D_800E12C0 = &gCourseEffectsInfo;

    gCourseVtxPtr = gGfxPool->courseVtxBuffer;
    gEffectsVtxPtr = gGfxPool->effectsVtxBuffer;
    gEffectsVtxEndPtr = &gGfxPool->effectsVtxBuffer[0x7FF];
    // The NinTex sign draw path consumes animated matrices from the current gfx pool.
    // Rebuild them here so a restore does not rely on the next update tick running first.
    // func_80074844();

    if ((gTotalRacers > 0) && (gTotalRacers <= TOTAL_RACER_COUNT)) {
        sLastRacer = &gRacers[gTotalRacers - 1];
    } else {
        sLastRacer = NULL;
    }

    if (sGhostReplayRecordingSize < 0) {
        sGhostReplayRecordingSize = 0;
    } else if (sGhostReplayRecordingSize > ARRAY_COUNT(sGhostReplayRecordingBuffer)) {
        sGhostReplayRecordingSize = ARRAY_COUNT(sGhostReplayRecordingBuffer);
    }
    sGhostReplayRecordingPtr = &sGhostReplayRecordingBuffer[sGhostReplayRecordingSize];
    Mod_RebuildGhostPointers();
    Mod_ResetCourseScratchState();

    if (gCurrentCourseInfo != NULL) {
        func_8007F4E0(COURSE_CONTEXT()->courseData.venue, COURSE_CONTEXT()->courseData.skybox);
        func_800747EC(COURSE_CONTEXT()->courseData.venue);
        func_8009CED0(COURSE_CONTEXT()->courseData.venue);
    }
    Mod_RearmGraphicsAssetLoads();

    if (gCurrentCourseInfo != NULL) {
        sPipeFogColors = &sVenuePipeFogColors[COURSE_CONTEXT()->courseData.venue * PIPE_MAX];
        sTunnelFogColors = &sVenueTunnelFogColors[COURSE_CONTEXT()->courseData.venue * TUNNEL_MAX];
    } else {
        sPipeFogColors = NULL;
        sTunnelFogColors = NULL;
    }

    if (gCurrentCourseInfo == NULL) {
        Mod_ResetBackgroundState();
    }

#ifdef EXPANSION_KIT
    if (gInCourseEditor) {
        D_80128C94 = &D_80128C90[D_800DCCFC];
        if (!gInCourseEditTestRun) {
            sTerrainEffectVtxStart = D_80128C94->terrainEffectVtx;
        } else {
            sTerrainEffectVtxStart = D_80225800.terrainEffectVtx;
        }
    } else {
        sTerrainEffectVtxStart = D_80225800.terrainEffectVtx;
    }
#else
    sTerrainEffectVtxStart = D_80225800.terrainEffectVtx;
#endif

    if (gCurrentCourseInfo != NULL) {
        func_80079EC8();
        gCourseFeaturesInfo.features = gCourseFeatures;
        gCourseEffectsInfo.effects = gCourseEffects;
        Mod_RebuildCourseRuntimeState();
        // Rebuild gadget descriptors from course data instead of trusting raw restored arrays.
        // Course_GadgetsInit(gCourseIndex);
        Background_Init();
        Hud_ReloadAssets();
        Menus_ReloadAssets();
        Mod_RebuildCourseViewInteractState();
    } else {
        sLastSegmentChunk = NULL;
    }

    sPlayerRacer = gRacers;
    Mod_RebuildRacerPointers();
    Mod_ReprojectRacersOntoCourse();
    if ((gCurrentCourseInfo != NULL) && (gTotalRacers > 0)) {
        Racer_UpdateRacerPairInfo();
        Racer_UpdateRacePositions();
        Racer_UpdateNearestRacer();
    }
    Mod_RebuildRaceOrder();
    Racer_UpdateRivalRacer();
}

static void WriteRegionToSD(const void* src_, u32 size, u32* io_lba)
{
    const u8* src = (const u8*)src_;
    u32 remaining = size;
    u32 buffered = 0;

   while (remaining > 0)
    {
        u32 space = sizeof(gSaveStateMemory) - buffered;
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

static void ReadRegionFromSD(void* dst_, u32 size, u32* io_lba)
{
    u8* dst = (u8*)dst_;
    u32 remaining = size;
    u32 buffered = 0;      /* bytes currently in staging buffer */
    u32 offset = 0;        /* read offset within staging buffer */

    while (remaining > 0)
    {
        /* If staging buffer is empty, fetch next sector */
        if (offset >= buffered)
        {
            sc_card_rd_dram(gSaveStateMemory, *io_lba, 1);
            osInvalDCache(gSaveStateMemory, SECTOR_SIZE);

            (*io_lba)++;
            buffered = SECTOR_SIZE;
            offset = 0;
        }

        /* Determine how many bytes we can copy this iteration */
        {
            u32 available = buffered - offset;
            u32 n = (remaining < available) ? remaining : available;
            u32 i;

            for (i = 0; i < n; i++)
            {
                dst[i] = gSaveStateMemory[offset + i];
            }

            dst += n;
            offset += n;
            remaining -= n;
        }
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
    u32 clear;
    u32 offset;
    u32 sectors;

    Mod_CacheArenaBounds();
    if (!Mod_ArenaFrontiersAreValid(gArenaStartPtrs, gArenaEndPtrs)) {
        return;
    }

    clear = 0;
    for (; clear < sizeof(gSaveStateMemory); clear++)
    {
      gSaveStateMemory[clear] = 0;
    }
    Mod_WriteHeaderMetadata(gSaveStateMemory);

    offset = global_write(gSaveStateMemory, Mod_HeaderOffsetStart());
    offset = save_pointer_relocs(gSaveStateMemory, offset);
    offset = Mod_WriteArenaFrontiers(gSaveStateMemory, offset);
    offset = mod_write_bytes(gSaveStateMemory, offset, &cart_size, sizeof(cart_size));
    sectors = Mod_HeaderSectorCount();
    addr = (cart_size / SECTOR_SIZE) - LBA_OFFSET;
    osWritebackDCache(gSaveStateMemory, sectors * SECTOR_SIZE);
    cart_card_wr_dram(gSaveStateMemory, addr, sectors);
    addr += sectors;
    Mod_SaveArenaRegions(&addr);
}

bool Mod_Load(void)
{
    u32 addr;
    u32 saved_cart_size;
    u32 off;
    u32 sectors;
    uintptr_t savedStarts[ARRAY_COUNT(sModArenaBasePtrs)];
    uintptr_t savedEnds[ARRAY_COUNT(sModArenaLimitPtrs)];
    s32 i;

    Mod_CacheArenaBounds();

    addr = (cart_size / SECTOR_SIZE) - LBA_OFFSET;
    cart_card_rd_dram(gSaveStateMemory, addr, MOD_HEADER_BUFFER_SIZE / SECTOR_SIZE);
    osInvalDCache(gSaveStateMemory, MOD_HEADER_BUFFER_SIZE);

    if (!Mod_HeaderIsValid(gSaveStateMemory)) {
        return false;
    }

    off = Mod_ArenaStateOffset();
    off = Mod_ReadArenaFrontiers(gSaveStateMemory, off, savedStarts, savedEnds);
    off = mod_read_bytes(gSaveStateMemory, off, &saved_cart_size, sizeof(saved_cart_size));

    if (saved_cart_size != cart_size) {
        return false;
    }

    if (!Mod_ArenaFrontiersAreValid(savedStarts, savedEnds)) {
        return false;
    }

    sectors = Mod_HeaderSectorCount();
    addr += sectors;
    Mod_LoadArenaRegions(savedStarts, savedEnds, &addr);

    for (i = 0; i < ARRAY_COUNT(savedStarts); i++) {
        gArenaStartPtrs[i] = savedStarts[i];
        gArenaEndPtrs[i] = savedEnds[i];
    }

    /* Arena streaming reuses gSaveStateMemory as a sector buffer, so reload the header before applying globals. */
    addr = (cart_size / SECTOR_SIZE) - LBA_OFFSET;
    cart_card_rd_dram(gSaveStateMemory, addr, MOD_HEADER_BUFFER_SIZE / SECTOR_SIZE);
    osInvalDCache(gSaveStateMemory, MOD_HEADER_BUFFER_SIZE);

    off = Mod_HeaderOffsetStart();
    off = global_load(gSaveStateMemory, off);
    off = load_pointer_relocs(gSaveStateMemory, off);
    off = Mod_ReadArenaFrontiers(gSaveStateMemory, off, savedStarts, savedEnds);
    off = mod_read_bytes(gSaveStateMemory, off, &saved_cart_size, sizeof(saved_cart_size));

    Mod_PostLoadFixups();

    return true;
}

extern Controller gSharedController;
bool Mod_Main(void)
{
    u16 buttons;
    u16 down;

    buttons = gSharedController.buttonCurrent;
    down = gSharedController.buttonPressed;
    if ((buttons & BTN_L) && (buttons & BTN_R) && (down & BTN_CDOWN)) {
        Mod_Save();
    }

    if ((buttons & BTN_L) && (buttons & BTN_R) && (down & BTN_CUP)) {
        if (Mod_Load()) {
            return true;
        }
    }
    return false;
}
