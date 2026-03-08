extern int D_800CD510;
extern struct RaceStats gCupRaceStats[1][6];
extern short gForceCredits;
extern signed char gRecordNameEntered[4];
extern long gSkyboxType;
extern long gVenueType;
static u32 game__194E0__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, &D_800CD510, 4);
	off = mod_write_bytes(out, off, gCupRaceStats, 144);
	off = mod_write_bytes(out, off, &gForceCredits, 2);
	off = mod_write_bytes(out, off, gRecordNameEntered, 4);
	off = mod_write_bytes(out, off, &gSkyboxType, 4);
	off = mod_write_bytes(out, off, &gVenueType, 4);
	return off;
}
