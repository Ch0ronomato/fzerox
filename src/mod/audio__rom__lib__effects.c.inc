extern char D_800D0840[26];
static u32 audio__rom__lib__effects__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, D_800D0840, 26);
	return off;
}
