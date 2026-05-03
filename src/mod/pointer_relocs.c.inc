static u32 save_pointer_relocs(u8* out, u32 off)
{
    /* sCloudTexture */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sCloudTexture != NULL)
        {
            if ((uintptr_t)sCloudTexture >= gArenaStartPtrs[0] && (uintptr_t)sCloudTexture < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sCloudTexture - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sCloudTexture >= gArenaStartPtrs[1] && (uintptr_t)sCloudTexture < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sCloudTexture - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sCloudTexture >= gArenaStartPtrs[2] && (uintptr_t)sCloudTexture < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sCloudTexture - gArenaStartPtrs[2]);
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

    /* sSkyboxTexture */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sSkyboxTexture != NULL)
        {
            if ((uintptr_t)sSkyboxTexture >= gArenaStartPtrs[0] && (uintptr_t)sSkyboxTexture < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sSkyboxTexture - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sSkyboxTexture >= gArenaStartPtrs[1] && (uintptr_t)sSkyboxTexture < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sSkyboxTexture - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sSkyboxTexture >= gArenaStartPtrs[2] && (uintptr_t)sSkyboxTexture < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sSkyboxTexture - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sStarTexture */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sStarTexture != NULL)
        {
            if ((uintptr_t)sStarTexture >= gArenaStartPtrs[0] && (uintptr_t)sStarTexture < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sStarTexture - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sStarTexture >= gArenaStartPtrs[1] && (uintptr_t)sStarTexture < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sStarTexture - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sStarTexture >= gArenaStartPtrs[2] && (uintptr_t)sStarTexture < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sStarTexture - gArenaStartPtrs[2]);
            }
        }

        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));
        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));
    }

    /* sVenueFloorTexture */
    {
        s16 arena_index = -1;
        u32 offset_val = 0;

        if (sVenueFloorTexture != NULL)
        {
            if ((uintptr_t)sVenueFloorTexture >= gArenaStartPtrs[0] && (uintptr_t)sVenueFloorTexture < gArenaEndPtrs[0])
            {
                arena_index = 0;
                offset_val = (u32)((uintptr_t)sVenueFloorTexture - gArenaStartPtrs[0]);
            }
            else if ((uintptr_t)sVenueFloorTexture >= gArenaStartPtrs[1] && (uintptr_t)sVenueFloorTexture < gArenaEndPtrs[1])
            {
                arena_index = 1;
                offset_val = (u32)((uintptr_t)sVenueFloorTexture - gArenaStartPtrs[1]);
            }
            else if ((uintptr_t)sVenueFloorTexture >= gArenaStartPtrs[2] && (uintptr_t)sVenueFloorTexture < gArenaEndPtrs[2])
            {
                arena_index = 2;
                offset_val = (u32)((uintptr_t)sVenueFloorTexture - gArenaStartPtrs[2]);
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

	return off;
}

static u32 load_pointer_relocs(u8* in, u32 off)
{
    /* sCloudTexture */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sCloudTexture = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sCloudTexture = NULL;
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

    /* sSkyboxTexture */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sSkyboxTexture = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sSkyboxTexture = NULL;
        }
    }

    /* sStarTexture */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sStarTexture = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sStarTexture = NULL;
        }
    }

    /* sVenueFloorTexture */
    {
        s16 arena_index;
        u32 offset_val;

        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));
        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));

        if (arena_index >= 0)
        {
            sVenueFloorTexture = (void*)(gArenaStartPtrs[arena_index] + offset_val);
        }
        else
        {
            sVenueFloorTexture = NULL;
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

	return off;
}
