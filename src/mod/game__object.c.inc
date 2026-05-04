extern struct unk_800E33E0 D_800E33E0[200];
extern long D_800E3A20;
extern struct unk_800E3F28 D_800E3F28[16];
extern struct unk_800E4068 D_800E4068[16];
extern struct Object gObjects[32];
static u32 game__object__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, D_800E33E0, 3200);
	off = mod_write_bytes(out, off, &D_800E3A20, 4);
	off = mod_write_bytes(out, off, D_800E3F28, 512);
	off = mod_write_bytes(out, off, D_800E4068, 256);
	off = mod_write_bytes(out, off, gObjects, 2560);
	return off;
}

static u32 game__object__load(u8* out, u32 off)
{
	off = mod_read_bytes(out, off, D_800E33E0, sizeof(D_800E33E0));
	off += 3200 - sizeof(D_800E33E0);
	off = mod_read_bytes(out, off, &D_800E3A20, 4);
	off = mod_read_bytes(out, off, D_800E3F28, sizeof(D_800E3F28));
	off += 512 - sizeof(D_800E3F28);
	off = mod_read_bytes(out, off, D_800E4068, sizeof(D_800E4068));
	off += 256 - sizeof(D_800E4068);
	off = mod_read_bytes(out, off, gObjects, sizeof(gObjects));
	off += 2560 - sizeof(gObjects);
	return off;
}
