extern long D_i2_80106F10;
extern unsigned char D_i2_80106F14[24];
extern unsigned char D_i2_80106F2C[11];
static u32 overlays__ovl_i2__race__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, &D_i2_80106F10, 4);
	off = mod_write_bytes(out, off, D_i2_80106F14, 24);
	off = mod_write_bytes(out, off, D_i2_80106F2C, 11);
	return off;
}

static u32 overlays__ovl_i2__race__load(u8* out, u32 off)
{
	off = mod_read_bytes(out, off, &D_i2_80106F10, 4);
	off = mod_read_bytes(out, off, D_i2_80106F14, 24);
	off = mod_read_bytes(out, off, D_i2_80106F2C, 11);
	return off;
}
