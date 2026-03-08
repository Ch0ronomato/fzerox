extern short kFont1CharWidths[48];
extern short kFont2CharWidths[48];
extern short kFont3CharWidths[234];
extern short kFont4CharWidths[235];
extern short kFont5CharWidths[235];
extern short kFont6CharWidths[237];
extern short kMachineWeightDigitWidths[10];
static u32 overlays__ovl_i2__font__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, kFont1CharWidths, 96);
	off = mod_write_bytes(out, off, kFont2CharWidths, 96);
	off = mod_write_bytes(out, off, kFont3CharWidths, 468);
	off = mod_write_bytes(out, off, kFont4CharWidths, 470);
	off = mod_write_bytes(out, off, kFont5CharWidths, 470);
	off = mod_write_bytes(out, off, kFont6CharWidths, 474);
	off = mod_write_bytes(out, off, kMachineWeightDigitWidths, 20);
	return off;
}
