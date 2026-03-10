extern long D_800F8AB4;
extern long D_800F8AB8;
extern signed char D_800F8ABC[48];
extern int gAudioContextInitialized;
extern AudioSlowLoadBuffer gSlowLoads;
extern long (*)(struct OSPiHandle_s *, OSIoMesg *, long) sDmaHandler;
static u32 audio__rom__lib__load__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, &D_800F8AB4, 4);
	off = mod_write_bytes(out, off, &D_800F8AB8, 4);
	off = mod_write_bytes(out, off, D_800F8ABC, 48);
	off = mod_write_bytes(out, off, &gAudioContextInitialized, 4);
	off = mod_write_bytes(out, off, &gSlowLoads, 392);
	
	return off;
}

static u32 audio__rom__lib__load__load(u8* out, u32 off)
{
	off = mod_read_bytes(out, off, &D_800F8AB4, 4);
	off = mod_read_bytes(out, off, &D_800F8AB8, 4);
	off = mod_read_bytes(out, off, D_800F8ABC, 48);
	off = mod_read_bytes(out, off, &gAudioContextInitialized, 4);
	off = mod_read_bytes(out, off, &gSlowLoads, 392);
	
	return off;
}
