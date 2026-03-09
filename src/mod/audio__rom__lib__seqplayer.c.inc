extern unsigned char sSeqInstructionArgsTable[80];
static u32 audio__rom__lib__seqplayer__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, sSeqInstructionArgsTable, 80);
	return off;
}

static u32 audio__rom__lib__seqplayer__load(u8* out, u32 off)
{
	off = mod_read_bytes(out, off, sSeqInstructionArgsTable, 80);
	return off;
}
