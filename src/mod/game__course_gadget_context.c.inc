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
	struct CourseEffectsInfo courseEffectsInfo;
	struct CourseFeaturesInfo courseFeaturesInfo;

	off = mod_read_bytes(out, off, &D_802CB6D0, sizeof(D_802CB6D0));
	off += 13832 - sizeof(D_802CB6D0);
	off = mod_read_bytes(out, off, &D_802CDFD8, sizeof(D_802CDFD8));
	off += 13832 - sizeof(D_802CDFD8);
	off = mod_read_bytes(out, off, gCourseDecorations, sizeof(gCourseDecorations));
	off += 2048 - sizeof(gCourseDecorations);
	off = mod_read_bytes(out, off, gCourseEffects, sizeof(gCourseEffects));
	off += 6144 - sizeof(gCourseEffects);
	off = mod_read_bytes(out, off, &courseEffectsInfo, sizeof(courseEffectsInfo));
	off += 16 - sizeof(courseEffectsInfo);
	gCourseEffectsInfo.effects = gCourseEffects;
	gCourseEffectsInfo.count = courseEffectsInfo.count;
	off = mod_read_bytes(out, off, gCourseFeatures, sizeof(gCourseFeatures));
	off += 4200 - sizeof(gCourseFeatures);
	off = mod_read_bytes(out, off, &courseFeaturesInfo, sizeof(courseFeaturesInfo));
	off += 32 - sizeof(courseFeaturesInfo);
	gCourseFeaturesInfo.features = gCourseFeatures;
	gCourseFeaturesInfo.featureCount = courseFeaturesInfo.featureCount;
	gCourseFeaturesInfo.landmineCount = courseFeaturesInfo.landmineCount;
	gCourseFeaturesInfo.jumpCount = courseFeaturesInfo.jumpCount;
	off = mod_read_bytes(out, off, gEffects, sizeof(gEffects));
	off += 9216 - sizeof(gEffects);
	off = mod_read_bytes(out, off, gEffectsDrawData, sizeof(gEffectsDrawData));
	off += 6144 - sizeof(gEffectsDrawData);
	off = mod_read_bytes(out, off, gJumps, sizeof(gJumps));
	off = mod_read_bytes(out, off, gLandmines, sizeof(gLandmines));
	off += 1152 - sizeof(gLandmines);
	return off;
}
