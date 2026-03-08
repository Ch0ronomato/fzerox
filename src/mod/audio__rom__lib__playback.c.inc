extern char D_80000800[32];
extern char D_800D0680[46];
extern char D_800D06B0[43];
extern char D_800D06DC[37];
extern char D_800D0704[25];
extern char D_800D0720[28];
extern char D_800D073C[9];
extern char D_800D0748[8];
extern char D_800D0750[48];
extern char D_800D0780[22];
extern char D_800D0798[31];
extern char D_800D07B8[21];
extern char D_800D07D0[13];
extern char D_800D07E0[32];
extern char D_800D0820[22];
static u32 audio__rom__lib__playback__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, D_80000800, 32);
	off = mod_write_bytes(out, off, D_800D0680, 46);
	off = mod_write_bytes(out, off, D_800D06B0, 43);
	off = mod_write_bytes(out, off, D_800D06DC, 37);
	off = mod_write_bytes(out, off, D_800D0704, 25);
	off = mod_write_bytes(out, off, D_800D0720, 28);
	off = mod_write_bytes(out, off, D_800D073C, 9);
	off = mod_write_bytes(out, off, D_800D0748, 8);
	off = mod_write_bytes(out, off, D_800D0750, 48);
	off = mod_write_bytes(out, off, D_800D0780, 22);
	off = mod_write_bytes(out, off, D_800D0798, 31);
	off = mod_write_bytes(out, off, D_800D07B8, 21);
	off = mod_write_bytes(out, off, D_800D07D0, 13);
	off = mod_write_bytes(out, off, D_800D07E0, 32);
	off = mod_write_bytes(out, off, D_800D0820, 22);
	return off;
}
