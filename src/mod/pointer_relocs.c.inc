static u32 save_pointer_relocs(u8* out, u32 off)
{
    /* D_800E12C0 */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (D_800E12C0 != NULL)
        {
            if ((uintptr_t)D_800E12C0 >= gArenaStartPtrs[0] && (uintptr_t)D_800E12C0 < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)D_800E12C0 - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)D_800E12C0 >= gArenaStartPtrs[1] && (uintptr_t)D_800E12C0 < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)D_800E12C0 - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)D_800E12C0 >= gArenaStartPtrs[2] && (uintptr_t)D_800E12C0 < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)D_800E12C0 - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* D_800F89B8 */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (D_800F89B8 != NULL)
        {
            if ((uintptr_t)D_800F89B8 >= gArenaStartPtrs[0] && (uintptr_t)D_800F89B8 < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)D_800F89B8 - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)D_800F89B8 >= gArenaStartPtrs[1] && (uintptr_t)D_800F89B8 < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)D_800F89B8 - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)D_800F89B8 >= gArenaStartPtrs[2] && (uintptr_t)D_800F89B8 < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)D_800F89B8 - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* D_800F89BC */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (D_800F89BC != NULL)
        {
            if ((uintptr_t)D_800F89BC >= gArenaStartPtrs[0] && (uintptr_t)D_800F89BC < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)D_800F89BC - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)D_800F89BC >= gArenaStartPtrs[1] && (uintptr_t)D_800F89BC < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)D_800F89BC - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)D_800F89BC >= gArenaStartPtrs[2] && (uintptr_t)D_800F89BC < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)D_800F89BC - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* D_800F89C8 */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (D_800F89C8 != NULL)
        {
            if ((uintptr_t)D_800F89C8 >= gArenaStartPtrs[0] && (uintptr_t)D_800F89C8 < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)D_800F89C8 - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)D_800F89C8 >= gArenaStartPtrs[1] && (uintptr_t)D_800F89C8 < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)D_800F89C8 - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)D_800F89C8 >= gArenaStartPtrs[2] && (uintptr_t)D_800F89C8 < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)D_800F89C8 - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* gCourseVtxPtr */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (gCourseVtxPtr != NULL)
        {
            if ((uintptr_t)gCourseVtxPtr >= gArenaStartPtrs[0] && (uintptr_t)gCourseVtxPtr < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)gCourseVtxPtr - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)gCourseVtxPtr >= gArenaStartPtrs[1] && (uintptr_t)gCourseVtxPtr < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)gCourseVtxPtr - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)gCourseVtxPtr >= gArenaStartPtrs[2] && (uintptr_t)gCourseVtxPtr < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)gCourseVtxPtr - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* gCurrentCourseInfo */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (gCurrentCourseInfo != NULL)
        {
            if ((uintptr_t)gCurrentCourseInfo >= gArenaStartPtrs[0] && (uintptr_t)gCurrentCourseInfo < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)gCurrentCourseInfo - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)gCurrentCourseInfo >= gArenaStartPtrs[1] && (uintptr_t)gCurrentCourseInfo < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)gCurrentCourseInfo - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)gCurrentCourseInfo >= gArenaStartPtrs[2] && (uintptr_t)gCurrentCourseInfo < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)gCurrentCourseInfo - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* gCurrentTrackName */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (gCurrentTrackName != NULL)
        {
            if ((uintptr_t)gCurrentTrackName >= gArenaStartPtrs[0] && (uintptr_t)gCurrentTrackName < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)gCurrentTrackName - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)gCurrentTrackName >= gArenaStartPtrs[1] && (uintptr_t)gCurrentTrackName < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)gCurrentTrackName - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)gCurrentTrackName >= gArenaStartPtrs[2] && (uintptr_t)gCurrentTrackName < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)gCurrentTrackName - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* gEffectsVtxEndPtr */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (gEffectsVtxEndPtr != NULL)
        {
            if ((uintptr_t)gEffectsVtxEndPtr >= gArenaStartPtrs[0] && (uintptr_t)gEffectsVtxEndPtr < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)gEffectsVtxEndPtr - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)gEffectsVtxEndPtr >= gArenaStartPtrs[1] && (uintptr_t)gEffectsVtxEndPtr < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)gEffectsVtxEndPtr - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)gEffectsVtxEndPtr >= gArenaStartPtrs[2] && (uintptr_t)gEffectsVtxEndPtr < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)gEffectsVtxEndPtr - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* gEffectsVtxPtr */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (gEffectsVtxPtr != NULL)
        {
            if ((uintptr_t)gEffectsVtxPtr >= gArenaStartPtrs[0] && (uintptr_t)gEffectsVtxPtr < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)gEffectsVtxPtr - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)gEffectsVtxPtr >= gArenaStartPtrs[1] && (uintptr_t)gEffectsVtxPtr < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)gEffectsVtxPtr - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)gEffectsVtxPtr >= gArenaStartPtrs[2] && (uintptr_t)gEffectsVtxPtr < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)gEffectsVtxPtr - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* gFastestGhost */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (gFastestGhost != NULL)
        {
            if ((uintptr_t)gFastestGhost >= gArenaStartPtrs[0] && (uintptr_t)gFastestGhost < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)gFastestGhost - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)gFastestGhost >= gArenaStartPtrs[1] && (uintptr_t)gFastestGhost < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)gFastestGhost - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)gFastestGhost >= gArenaStartPtrs[2] && (uintptr_t)gFastestGhost < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)gFastestGhost - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* gFastestGhostRacer */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (gFastestGhostRacer != NULL)
        {
            if ((uintptr_t)gFastestGhostRacer >= gArenaStartPtrs[0] && (uintptr_t)gFastestGhostRacer < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)gFastestGhostRacer - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)gFastestGhostRacer >= gArenaStartPtrs[1] && (uintptr_t)gFastestGhostRacer < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)gFastestGhostRacer - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)gFastestGhostRacer >= gArenaStartPtrs[2] && (uintptr_t)gFastestGhostRacer < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)gFastestGhostRacer - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sFastestGhostRacerRacer */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sFastestGhostRacerRacer != NULL)
        {
            if ((uintptr_t)sFastestGhostRacerRacer >= gArenaStartPtrs[0] && (uintptr_t)sFastestGhostRacerRacer < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sFastestGhostRacerRacer - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sFastestGhostRacerRacer >= gArenaStartPtrs[1] && (uintptr_t)sFastestGhostRacerRacer < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sFastestGhostRacerRacer - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sFastestGhostRacerRacer >= gArenaStartPtrs[2] && (uintptr_t)sFastestGhostRacerRacer < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sFastestGhostRacerRacer - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sGhostReplayRecordingPtr */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sGhostReplayRecordingPtr != NULL)
        {
            if ((uintptr_t)sGhostReplayRecordingPtr >= gArenaStartPtrs[0] && (uintptr_t)sGhostReplayRecordingPtr < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sGhostReplayRecordingPtr - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sGhostReplayRecordingPtr >= gArenaStartPtrs[1] && (uintptr_t)sGhostReplayRecordingPtr < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sGhostReplayRecordingPtr - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sGhostReplayRecordingPtr >= gArenaStartPtrs[2] && (uintptr_t)sGhostReplayRecordingPtr < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sGhostReplayRecordingPtr - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sLastRacer */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sLastRacer != NULL)
        {
            if ((uintptr_t)sLastRacer >= gArenaStartPtrs[0] && (uintptr_t)sLastRacer < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sLastRacer - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sLastRacer >= gArenaStartPtrs[1] && (uintptr_t)sLastRacer < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sLastRacer - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sLastRacer >= gArenaStartPtrs[2] && (uintptr_t)sLastRacer < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sLastRacer - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sLastSegmentChunk */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sLastSegmentChunk != NULL)
        {
            if ((uintptr_t)sLastSegmentChunk >= gArenaStartPtrs[0] && (uintptr_t)sLastSegmentChunk < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sLastSegmentChunk - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sLastSegmentChunk >= gArenaStartPtrs[1] && (uintptr_t)sLastSegmentChunk < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sLastSegmentChunk - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sLastSegmentChunk >= gArenaStartPtrs[2] && (uintptr_t)sLastSegmentChunk < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sLastSegmentChunk - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sLoserPalette */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sLoserPalette != NULL)
        {
            if ((uintptr_t)sLoserPalette >= gArenaStartPtrs[0] && (uintptr_t)sLoserPalette < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sLoserPalette - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sLoserPalette >= gArenaStartPtrs[1] && (uintptr_t)sLoserPalette < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sLoserPalette - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sLoserPalette >= gArenaStartPtrs[2] && (uintptr_t)sLoserPalette < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sLoserPalette - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sLoserTexture */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sLoserTexture != NULL)
        {
            if ((uintptr_t)sLoserTexture >= gArenaStartPtrs[0] && (uintptr_t)sLoserTexture < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sLoserTexture - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sLoserTexture >= gArenaStartPtrs[1] && (uintptr_t)sLoserTexture < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sLoserTexture - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sLoserTexture >= gArenaStartPtrs[2] && (uintptr_t)sLoserTexture < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sLoserTexture - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sPipeFogColors */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sPipeFogColors != NULL)
        {
            if ((uintptr_t)sPipeFogColors >= gArenaStartPtrs[0] && (uintptr_t)sPipeFogColors < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sPipeFogColors - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sPipeFogColors >= gArenaStartPtrs[1] && (uintptr_t)sPipeFogColors < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sPipeFogColors - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sPipeFogColors >= gArenaStartPtrs[2] && (uintptr_t)sPipeFogColors < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sPipeFogColors - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sPlayerRacer */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sPlayerRacer != NULL)
        {
            if ((uintptr_t)sPlayerRacer >= gArenaStartPtrs[0] && (uintptr_t)sPlayerRacer < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sPlayerRacer - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sPlayerRacer >= gArenaStartPtrs[1] && (uintptr_t)sPlayerRacer < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sPlayerRacer - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sPlayerRacer >= gArenaStartPtrs[2] && (uintptr_t)sPlayerRacer < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sPlayerRacer - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sRetirePalette */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sRetirePalette != NULL)
        {
            if ((uintptr_t)sRetirePalette >= gArenaStartPtrs[0] && (uintptr_t)sRetirePalette < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sRetirePalette - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sRetirePalette >= gArenaStartPtrs[1] && (uintptr_t)sRetirePalette < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sRetirePalette - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sRetirePalette >= gArenaStartPtrs[2] && (uintptr_t)sRetirePalette < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sRetirePalette - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sRetireTexture */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sRetireTexture != NULL)
        {
            if ((uintptr_t)sRetireTexture >= gArenaStartPtrs[0] && (uintptr_t)sRetireTexture < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sRetireTexture - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sRetireTexture >= gArenaStartPtrs[1] && (uintptr_t)sRetireTexture < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sRetireTexture - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sRetireTexture >= gArenaStartPtrs[2] && (uintptr_t)sRetireTexture < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sRetireTexture - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sRivalRacer */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sRivalRacer != NULL)
        {
            if ((uintptr_t)sRivalRacer >= gArenaStartPtrs[0] && (uintptr_t)sRivalRacer < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sRivalRacer - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sRivalRacer >= gArenaStartPtrs[1] && (uintptr_t)sRivalRacer < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sRivalRacer - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sRivalRacer >= gArenaStartPtrs[2] && (uintptr_t)sRivalRacer < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sRivalRacer - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sTerrainEffectVtxStart */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sTerrainEffectVtxStart != NULL)
        {
            if ((uintptr_t)sTerrainEffectVtxStart >= gArenaStartPtrs[0] && (uintptr_t)sTerrainEffectVtxStart < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sTerrainEffectVtxStart - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sTerrainEffectVtxStart >= gArenaStartPtrs[1] && (uintptr_t)sTerrainEffectVtxStart < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sTerrainEffectVtxStart - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sTerrainEffectVtxStart >= gArenaStartPtrs[2] && (uintptr_t)sTerrainEffectVtxStart < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sTerrainEffectVtxStart - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sTunnelFogColors */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sTunnelFogColors != NULL)
        {
            if ((uintptr_t)sTunnelFogColors >= gArenaStartPtrs[0] && (uintptr_t)sTunnelFogColors < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sTunnelFogColors - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sTunnelFogColors >= gArenaStartPtrs[1] && (uintptr_t)sTunnelFogColors < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sTunnelFogColors - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sTunnelFogColors >= gArenaStartPtrs[2] && (uintptr_t)sTunnelFogColors < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sTunnelFogColors - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sWinnerPalette */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sWinnerPalette != NULL)
        {
            if ((uintptr_t)sWinnerPalette >= gArenaStartPtrs[0] && (uintptr_t)sWinnerPalette < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sWinnerPalette - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sWinnerPalette >= gArenaStartPtrs[1] && (uintptr_t)sWinnerPalette < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sWinnerPalette - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sWinnerPalette >= gArenaStartPtrs[2] && (uintptr_t)sWinnerPalette < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sWinnerPalette - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sWinnerTexture */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sWinnerTexture != NULL)
        {
            if ((uintptr_t)sWinnerTexture >= gArenaStartPtrs[0] && (uintptr_t)sWinnerTexture < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sWinnerTexture - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sWinnerTexture >= gArenaStartPtrs[1] && (uintptr_t)sWinnerTexture < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sWinnerTexture - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sWinnerTexture >= gArenaStartPtrs[2] && (uintptr_t)sWinnerTexture < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sWinnerTexture - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sWorkingNextSegmentChunk */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sWorkingNextSegmentChunk != NULL)
        {
            if ((uintptr_t)sWorkingNextSegmentChunk >= gArenaStartPtrs[0] && (uintptr_t)sWorkingNextSegmentChunk < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sWorkingNextSegmentChunk - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sWorkingNextSegmentChunk >= gArenaStartPtrs[1] && (uintptr_t)sWorkingNextSegmentChunk < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sWorkingNextSegmentChunk - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sWorkingNextSegmentChunk >= gArenaStartPtrs[2] && (uintptr_t)sWorkingNextSegmentChunk < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sWorkingNextSegmentChunk - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sWorkingSegmentChunk */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sWorkingSegmentChunk != NULL)
        {
            if ((uintptr_t)sWorkingSegmentChunk >= gArenaStartPtrs[0] && (uintptr_t)sWorkingSegmentChunk < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sWorkingSegmentChunk - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sWorkingSegmentChunk >= gArenaStartPtrs[1] && (uintptr_t)sWorkingSegmentChunk < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sWorkingSegmentChunk - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sWorkingSegmentChunk >= gArenaStartPtrs[2] && (uintptr_t)sWorkingSegmentChunk < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sWorkingSegmentChunk - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

	return off;
}

static u32 load_pointer_relocs(u8* in, u32 off)
{
    /* D_800E12C0 */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            D_800E12C0 = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            D_800E12C0 = NULL;
        }
    }

    /* D_800F89B8 */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            D_800F89B8 = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            D_800F89B8 = NULL;
        }
    }

    /* D_800F89BC */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            D_800F89BC = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            D_800F89BC = NULL;
        }
    }

    /* D_800F89C8 */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            D_800F89C8 = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            D_800F89C8 = NULL;
        }
    }

    /* gCourseVtxPtr */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            gCourseVtxPtr = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            gCourseVtxPtr = NULL;
        }
    }

    /* gCurrentCourseInfo */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            gCurrentCourseInfo = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            gCurrentCourseInfo = NULL;
        }
    }

    /* gCurrentTrackName */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            gCurrentTrackName = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            gCurrentTrackName = NULL;
        }
    }

    /* gEffectsVtxEndPtr */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            gEffectsVtxEndPtr = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            gEffectsVtxEndPtr = NULL;
        }
    }

    /* gEffectsVtxPtr */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            gEffectsVtxPtr = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            gEffectsVtxPtr = NULL;
        }
    }

    /* gFastestGhost */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            gFastestGhost = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            gFastestGhost = NULL;
        }
    }

    /* gFastestGhostRacer */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            gFastestGhostRacer = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            gFastestGhostRacer = NULL;
        }
    }

    /* sFastestGhostRacerRacer */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sFastestGhostRacerRacer = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sFastestGhostRacerRacer = NULL;
        }
    }

    /* sGhostReplayRecordingPtr */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sGhostReplayRecordingPtr = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sGhostReplayRecordingPtr = NULL;
        }
    }

    /* sLastRacer */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sLastRacer = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sLastRacer = NULL;
        }
    }

    /* sLastSegmentChunk */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sLastSegmentChunk = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sLastSegmentChunk = NULL;
        }
    }

    /* sLoserPalette */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sLoserPalette = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sLoserPalette = NULL;
        }
    }

    /* sLoserTexture */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sLoserTexture = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sLoserTexture = NULL;
        }
    }

    /* sPipeFogColors */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sPipeFogColors = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sPipeFogColors = NULL;
        }
    }

    /* sPlayerRacer */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sPlayerRacer = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sPlayerRacer = NULL;
        }
    }

    /* sRetirePalette */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sRetirePalette = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sRetirePalette = NULL;
        }
    }

    /* sRetireTexture */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sRetireTexture = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sRetireTexture = NULL;
        }
    }

    /* sRivalRacer */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sRivalRacer = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sRivalRacer = NULL;
        }
    }

    /* sTerrainEffectVtxStart */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sTerrainEffectVtxStart = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sTerrainEffectVtxStart = NULL;
        }
    }

    /* sTunnelFogColors */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sTunnelFogColors = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sTunnelFogColors = NULL;
        }
    }

    /* sWinnerPalette */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sWinnerPalette = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sWinnerPalette = NULL;
        }
    }

    /* sWinnerTexture */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sWinnerTexture = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sWinnerTexture = NULL;
        }
    }

    /* sWorkingNextSegmentChunk */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sWorkingNextSegmentChunk = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sWorkingNextSegmentChunk = NULL;
        }
    }

    /* sWorkingSegmentChunk */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sWorkingSegmentChunk = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sWorkingSegmentChunk = NULL;
        }
    }

	return off;
}
