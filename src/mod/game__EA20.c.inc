extern s32 D_800CD2A0;
static u32 game__EA20__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, &D_800CD2A0, 4);
	return off;
}
