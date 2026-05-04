extern long sBorderedBoxCount;
extern struct BorderedBoxWidget sBorderedBoxes[3];
static u32 game__bordered_box__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, &sBorderedBoxCount, 4);
	off = mod_write_bytes(out, off, sBorderedBoxes, 120);
	return off;
}

static u32 game__bordered_box__load(u8* out, u32 off)
{
	off = mod_read_bytes(out, off, &sBorderedBoxCount, 4);
	off = mod_read_bytes(out, off, sBorderedBoxes, sizeof(sBorderedBoxes));
	off += 120 - sizeof(sBorderedBoxes);
	return off;
}
