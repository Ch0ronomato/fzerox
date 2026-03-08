extern char D_800D16E0[40];
static u32 audio__rom__lib__synthesis__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, D_800D16E0, 40);
	return off;
}
