extern struct unk_807B3C20 D_802CB6D0;
extern struct unk_807B3C20 D_802CDFD8;
extern struct CourseDecoration gCourseDecorations[32];
extern struct CourseEffect gCourseEffects[192];
extern struct CourseEffectsInfo gCourseEffectsInfo;
extern struct CourseFeature gCourseFeatures[105];
extern struct CourseFeaturesInfo gCourseFeaturesInfo;
extern struct Effect gEffects[192];
extern struct EffectDrawData gEffectsDrawData[192];
extern struct Jump gJumps[4];
extern struct Landmine gLandmines[48];
static u32 game__course_gadget_context__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, &D_802CB6D0, 13832);
	off = mod_write_bytes(out, off, &D_802CDFD8, 13832);
	off = mod_write_bytes(out, off, gCourseDecorations, 2048);
	off = mod_write_bytes(out, off, gCourseEffects, 6144);
	off = mod_write_bytes(out, off, &gCourseEffectsInfo, 16);
	off = mod_write_bytes(out, off, gCourseFeatures, 4200);
	off = mod_write_bytes(out, off, &gCourseFeaturesInfo, 32);
	off = mod_write_bytes(out, off, gEffects, 9216);
	off = mod_write_bytes(out, off, gEffectsDrawData, 6144);
	off = mod_write_bytes(out, off, gJumps, 256);
	off = mod_write_bytes(out, off, gLandmines, 1152);
	return off;
}

static u32 game__course_gadget_context__load(u8* out, u32 off)
{
	off = mod_read_bytes(out, off, &D_802CB6D0, 13832);
	off = mod_read_bytes(out, off, &D_802CDFD8, 13832);
	off = mod_read_bytes(out, off, gCourseDecorations, 2048);
	off = mod_read_bytes(out, off, gCourseEffects, 6144);
	off = mod_read_bytes(out, off, &gCourseEffectsInfo, 16);
	off = mod_read_bytes(out, off, gCourseFeatures, 4200);
	off = mod_read_bytes(out, off, &gCourseFeaturesInfo, 32);
	off = mod_read_bytes(out, off, gEffects, 9216);
	off = mod_read_bytes(out, off, gEffectsDrawData, 6144);
	off = mod_read_bytes(out, off, gJumps, 256);
	off = mod_read_bytes(out, off, gLandmines, 1152);
	return off;
}
