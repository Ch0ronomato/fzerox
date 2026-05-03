extern struct CourseSegment D_802C2020[64];
extern struct CourseInfo gCourseInfos[56];
extern struct Racer gRacers[30];
extern struct SegmentChunk gSegmentChunks[1025];
static u32 game__game_context__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, D_802C2020, 13824);
	off = mod_write_bytes(out, off, gCourseInfos, 16576);
	off = mod_write_bytes(out, off, gRacers, 33840);
	off = mod_write_bytes(out, off, gSegmentChunks, 106600);
	return off;
}

static u32 game__game_context__load(u8* out, u32 off)
{
	off = mod_read_bytes(out, off, D_802C2020, 13824);
	off = mod_read_bytes(out, off, gCourseInfos, 16576);
	off = mod_read_bytes(out, off, gRacers, 33840);
	off = mod_read_bytes(out, off, gSegmentChunks, 106600);
	return off;
}
