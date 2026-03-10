extern long D_800CD01C;
extern long D_800DCE40;
extern long D_800DCE4C;
extern long D_800DCE50;
extern long D_800DCE54;
extern long D_800DCE60;
extern long gAntiPiracyAddedDifficulty;
extern long gCupType;
extern long gDifficulty;
extern long gNumPlayers;
extern long gTotalLapCount;
extern signed char sTitleDemoCourses[5];
extern long sTitleDemoGameModes[3];
extern long sTitleDemoNumPlayers[3];
static u32 game__game__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, &D_800CD01C, 4);
	off = mod_write_bytes(out, off, &D_800DCE40, 4);
	off = mod_write_bytes(out, off, &D_800DCE4C, 4);
	off = mod_write_bytes(out, off, &D_800DCE50, 4);
	off = mod_write_bytes(out, off, &D_800DCE54, 4);
	off = mod_write_bytes(out, off, &D_800DCE60, 4);
	off = mod_write_bytes(out, off, &gAntiPiracyAddedDifficulty, 4);
	off = mod_write_bytes(out, off, &gCupType, 4);
	off = mod_write_bytes(out, off, &gDifficulty, 4);
	off = mod_write_bytes(out, off, &gNumPlayers, 4);
	off = mod_write_bytes(out, off, &gTotalLapCount, 4);
	off = mod_write_bytes(out, off, sTitleDemoCourses, 5);
	off = mod_write_bytes(out, off, sTitleDemoGameModes, 24);
	off = mod_write_bytes(out, off, sTitleDemoNumPlayers, 24);
	return off;
}

static u32 game__game__load(u8* out, u32 off)
{
	off = mod_read_bytes(out, off, &D_800CD01C, 4);
	off = mod_read_bytes(out, off, &D_800DCE40, 4);
	off = mod_read_bytes(out, off, &D_800DCE4C, 4);
	off = mod_read_bytes(out, off, &D_800DCE50, 4);
	off = mod_read_bytes(out, off, &D_800DCE54, 4);
	off = mod_read_bytes(out, off, &D_800DCE60, 4);
	off = mod_read_bytes(out, off, &gAntiPiracyAddedDifficulty, 4);
	off = mod_read_bytes(out, off, &gCupType, 4);
	off = mod_read_bytes(out, off, &gDifficulty, 4);
	off = mod_read_bytes(out, off, &gNumPlayers, 4);
	off = mod_read_bytes(out, off, &gTotalLapCount, 4);
	off = mod_read_bytes(out, off, sTitleDemoCourses, 5);
	off = mod_read_bytes(out, off, sTitleDemoGameModes, 24);
	off = mod_read_bytes(out, off, sTitleDemoNumPlayers, 24);
	return off;
}
