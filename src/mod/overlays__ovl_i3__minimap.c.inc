extern long gPlayerMinimapLapCounterToggle[4];
extern unsigned short sCourseMinimapPalette[4];
extern unsigned char sCourseMinimapTex[4096];
extern long sPlayerMinimapPositions[4][4][2];
static u32 overlays__ovl_i3__minimap__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, gPlayerMinimapLapCounterToggle, 32);
	off = mod_write_bytes(out, off, sCourseMinimapPalette, 8);
	off = mod_write_bytes(out, off, sCourseMinimapTex, 4096);
	off = mod_write_bytes(out, off, sPlayerMinimapPositions, 256);
	return off;
}

static u32 overlays__ovl_i3__minimap__load(u8* out, u32 off)
{
	off = mod_read_bytes(out, off, gPlayerMinimapLapCounterToggle, sizeof(gPlayerMinimapLapCounterToggle));
	off += 32 - sizeof(gPlayerMinimapLapCounterToggle);
	off = mod_read_bytes(out, off, sCourseMinimapPalette, 8);
	off = mod_read_bytes(out, off, sCourseMinimapTex, 4096);
	off = mod_read_bytes(out, off, sPlayerMinimapPositions, sizeof(sPlayerMinimapPositions));
	off += 256 - sizeof(sPlayerMinimapPositions);
	return off;
}
