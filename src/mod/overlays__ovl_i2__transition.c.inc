extern short D_i2_80106DA0;
extern Gfx D_i2_80106DB8[1];
extern long kTransitionRandomSelection[7];
static u32 overlays__ovl_i2__transition__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, &D_i2_80106DA0, 2);
	off = mod_write_bytes(out, off, D_i2_80106DB8, 16);
	off = mod_write_bytes(out, off, kTransitionRandomSelection, 56);
	return off;
}

static u32 overlays__ovl_i2__transition__load(u8* out, u32 off)
{
	off = mod_read_bytes(out, off, &D_i2_80106DA0, 2);
	off = mod_read_bytes(out, off, D_i2_80106DB8, 16);
	off = mod_read_bytes(out, off, kTransitionRandomSelection, 56);
	return off;
}
