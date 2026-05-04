extern long D_800CD1E8;
extern long D_800CD21C;
extern long D_800CD220[11];
extern long D_800CD24C[19];
extern signed char D_800E12B8[8];
extern struct CourseEffectsInfo * D_800E12C0;
extern signed char D_800E12C4[4];
extern long D_800E12C8[2048];
extern long D_800E32CC;
extern int gInCourseEditor;
extern long sCourseDecorationTextureLoadState;
extern float sDashArrowPointScale;
extern float sDashScaleForward;
extern float sDashScaleWidth;
extern Vtx * sTerrainEffectVtxStart;
static u32 game__course_gadgets__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, &D_800CD1E8, 4);
	off = mod_write_bytes(out, off, &D_800CD21C, 4);
	off = mod_write_bytes(out, off, D_800CD220, 88);
	off = mod_write_bytes(out, off, D_800CD24C, 152);
	off = mod_write_bytes(out, off, D_800E12B8, 8);
	off = mod_write_bytes(out, off, D_800E12C4, 4);
	off = mod_write_bytes(out, off, D_800E12C8, 16384);
	off = mod_write_bytes(out, off, &D_800E32CC, 4);
	off = mod_write_bytes(out, off, &gInCourseEditor, 4);
	off = mod_write_bytes(out, off, &sCourseDecorationTextureLoadState, 4);
	off = mod_write_bytes(out, off, &sDashArrowPointScale, 4);
	off = mod_write_bytes(out, off, &sDashScaleForward, 4);
	off = mod_write_bytes(out, off, &sDashScaleWidth, 4);
	return off;
}

static u32 game__course_gadgets__load(u8* out, u32 off)
{
	off = mod_read_bytes(out, off, &D_800CD1E8, 4);
	off = mod_read_bytes(out, off, &D_800CD21C, 4);
	off = mod_read_bytes(out, off, D_800CD220, sizeof(D_800CD220));
	off += 88 - sizeof(D_800CD220);
	off = mod_read_bytes(out, off, D_800CD24C, sizeof(D_800CD24C));
	off += 152 - sizeof(D_800CD24C);
	off = mod_read_bytes(out, off, D_800E12B8, 8);
	off = mod_read_bytes(out, off, D_800E12C4, 4);
	off = mod_read_bytes(out, off, D_800E12C8, sizeof(D_800E12C8));
	off += 16384 - sizeof(D_800E12C8);
	off = mod_read_bytes(out, off, &D_800E32CC, 4);
	off = mod_read_bytes(out, off, &gInCourseEditor, 4);
	off = mod_read_bytes(out, off, &sCourseDecorationTextureLoadState, 4);
	off = mod_read_bytes(out, off, &sDashArrowPointScale, 4);
	off = mod_read_bytes(out, off, &sDashScaleForward, 4);
	off = mod_read_bytes(out, off, &sDashScaleWidth, 4);
	return off;
}
