extern char D_i2_8010ADE0[8];
extern char D_i2_8010ADE8[8];
extern unsigned char D_i2_80111848[30];
extern short gSettingSoundMode;
extern struct OSPiHandle_s * gSramPiHandlePtr;
extern OSIoMesg sSramIoMesg;
extern struct OSPiHandle_s sSramPiHandle;
static u32 overlays__ovl_i2__save__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, D_i2_8010ADE0, 8);
	off = mod_write_bytes(out, off, D_i2_8010ADE8, 8);
	off = mod_write_bytes(out, off, D_i2_80111848, 30);
	off = mod_write_bytes(out, off, &gSettingSoundMode, 2);
	off = mod_write_bytes(out, off, &gSramPiHandlePtr, 8);
	off = mod_write_bytes(out, off, &sSramIoMesg, 48);
	off = mod_write_bytes(out, off, &sSramPiHandle, 224);
	return off;
}

static u32 overlays__ovl_i2__save__load(u8* out, u32 off)
{
	off = mod_read_bytes(out, off, D_i2_8010ADE0, 8);
	off = mod_read_bytes(out, off, D_i2_8010ADE8, 8);
	off = mod_read_bytes(out, off, D_i2_80111848, 30);
	off = mod_read_bytes(out, off, &gSettingSoundMode, 2);
	off = mod_read_bytes(out, off, &gSramPiHandlePtr, 8);
	off = mod_read_bytes(out, off, &sSramIoMesg, 48);
	off = mod_read_bytes(out, off, &sSramPiHandle, 224);
	return off;
}
