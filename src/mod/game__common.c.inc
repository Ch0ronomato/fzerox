extern long D_800CD384;
extern signed char D_800CD3AC[4];
extern signed char D_800CD3C4;
extern long D_800CD4E0[12];
extern long D_800E4168;
extern float gCharacterLastEngine[30];
extern signed char gCupNumDifficultiesCleared[4];
extern long gCurrentGhostType;
extern char * gCurrentTrackName;
extern long gLastCourseSelectCourseIndex;
extern long gLastRecordsCourseIndex;
extern long gMachineSelectState;
extern long gMachineSettingsState;
extern long gModeSubOption[8];
extern signed char gPlayerSelectionLock[4];
extern long gSelectedMode;
extern signed char gSettingEverythingUnlocked;
extern char * gTrackNames[55];
extern signed char gUnlockableLevel;
extern signed char kMachineSelectCharacterList[31];
static u32 game__common__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, &D_800CD384, 4);
	off = mod_write_bytes(out, off, D_800CD3AC, 4);
	off = mod_write_bytes(out, off, &D_800CD3C4, 1);
	off = mod_write_bytes(out, off, D_800CD4E0, 96);
	off = mod_write_bytes(out, off, &D_800E4168, 4);
	off = mod_write_bytes(out, off, gCharacterLastEngine, 120);
	off = mod_write_bytes(out, off, gCupNumDifficultiesCleared, 4);
	off = mod_write_bytes(out, off, &gCurrentGhostType, 4);
	off = mod_write_bytes(out, off, &gCurrentTrackName, 8);
	off = mod_write_bytes(out, off, &gLastCourseSelectCourseIndex, 4);
	off = mod_write_bytes(out, off, &gLastRecordsCourseIndex, 4);
	off = mod_write_bytes(out, off, &gMachineSelectState, 4);
	off = mod_write_bytes(out, off, &gMachineSettingsState, 4);
	off = mod_write_bytes(out, off, gModeSubOption, 64);
	off = mod_write_bytes(out, off, gPlayerSelectionLock, 4);
	off = mod_write_bytes(out, off, &gSelectedMode, 4);
	off = mod_write_bytes(out, off, &gSettingEverythingUnlocked, 1);
	off = mod_write_bytes(out, off, gTrackNames, 440);
	off = mod_write_bytes(out, off, &gUnlockableLevel, 1);
	off = mod_write_bytes(out, off, kMachineSelectCharacterList, 31);
	return off;
}

static u32 game__common__load(u8* out, u32 off)
{
	off = mod_read_bytes(out, off, &D_800CD384, 4);
	off = mod_read_bytes(out, off, D_800CD3AC, 4);
	off = mod_read_bytes(out, off, &D_800CD3C4, 1);
	off = mod_read_bytes(out, off, D_800CD4E0, 96);
	off = mod_read_bytes(out, off, &D_800E4168, 4);
	off = mod_read_bytes(out, off, gCharacterLastEngine, 120);
	off = mod_read_bytes(out, off, gCupNumDifficultiesCleared, 4);
	off = mod_read_bytes(out, off, &gCurrentGhostType, 4);
	off = mod_read_bytes(out, off, &gCurrentTrackName, 8);
	off = mod_read_bytes(out, off, &gLastCourseSelectCourseIndex, 4);
	off = mod_read_bytes(out, off, &gLastRecordsCourseIndex, 4);
	off = mod_read_bytes(out, off, &gMachineSelectState, 4);
	off = mod_read_bytes(out, off, &gMachineSettingsState, 4);
	off = mod_read_bytes(out, off, gModeSubOption, 64);
	off = mod_read_bytes(out, off, gPlayerSelectionLock, 4);
	off = mod_read_bytes(out, off, &gSelectedMode, 4);
	off = mod_read_bytes(out, off, &gSettingEverythingUnlocked, 1);
	off = mod_read_bytes(out, off, gTrackNames, 440);
	off = mod_read_bytes(out, off, &gUnlockableLevel, 1);
	off = mod_read_bytes(out, off, kMachineSelectCharacterList, 31);
	return off;
}
