extern char D_i2_8010ADE0[8];
extern char D_i2_8010ADE8[8];
extern unsigned char D_i2_80111848[30];
extern s16 gSettingSoundMode;
extern OSPiHandle * gSramPiHandlePtr;
extern OSIoMesg sSramIoMesg;
extern OSPiHandle sSramPiHandle;
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
