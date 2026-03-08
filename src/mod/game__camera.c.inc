extern f32 D_800CD8A8;
extern f32 D_800CD8AC;
extern f32 D_800CDA90;
extern f32 D_800CDA94;
extern f32 D_800CDA98;
extern const CameraOrbitData D_800D4CF8;
extern const CameraFollowSmoothData D_800D4DA4;
extern const CameraOrbitData D_800D4F58;
extern const CameraOrbitData D_800D5004;
extern const CameraOrbitData D_800D50B0;
extern const CameraAtEyeData D_800D515C;
extern const CameraAtEyeData D_800D51D4;
extern const CameraOrbitData D_800D524C;
extern const CameraFollowSmoothData D_800D5358;
extern const CameraFollowSmoothData D_800D544C;
extern s16 D_800E5E8C;
extern struct Camera gCameras[4];
extern struct FinishedSuccessScript gFinishedSuccessScript[5];
extern ScissorBox gScissorBoxBottomCenterQuarter;
extern ScissorBox gScissorBoxBottomHalf;
extern ScissorBox gScissorBoxBottomLeftQuarter;
extern ScissorBox gScissorBoxBottomRightQuarter;
extern ScissorBox gScissorBoxFullScreen;
extern ScissorBox gScissorBoxLeftCenterQuarter;
extern ScissorBox gScissorBoxLeftHalf;
extern ScissorBox gScissorBoxRightCenterQuarter;
extern ScissorBox gScissorBoxRightHalf;
extern ScissorBox gScissorBoxTopCenterQuarter;
extern ScissorBox gScissorBoxTopHalf;
extern ScissorBox gScissorBoxTopLeftQuarter;
extern ScissorBox gScissorBoxTopRightQuarter;
extern const CameraAtEyeData kDefaultAtEyeData;
extern const CameraLocalAnchorData kDefaultLocalAnchorData;
extern long kFourCameraScissorBoxTypes[4];
extern struct CameraRaceSettingInfo kRegularCameraRaceSettings[4];
extern long kSingleCameraScissorBoxTypes[1];
extern long kThreeCameraScissorBoxTypes[3];
extern long kTwoCameraScissorBoxTypes[2];
extern struct CameraRaceSettingInfo kWidescreenCameraRaceSettings[4];
extern bool sAllowCameraLookBack;
extern s16 sCameraEndingFocusRacer;
extern s16 sCameraInfoInitialized;
extern struct CameraScriptManager sCameraScriptMgrs[4];
extern struct CameraSettings sCameraSettings[4];
extern s32 sEndingCameraMessage;
extern EyeFromRacerInfo sEyeFromRacerInfo0;
extern EyeFromRacerInfo sEyeFromRacerInfo4;
extern Vec3f sFinishedSuccessFollowRacerEye[4];
extern LerpLocalAtEyeInfo sLerpLocalAtEyeInfo1;
extern LerpLocalAtEyeInfo sLerpLocalAtEyeInfo2;
extern LerpLocalAtEyeInfo sLerpLocalAtEyeInfo3;
extern s32 sMaxCameraLookBackRotate;
extern s32 sMultiplayerFocusCameraId;
extern s32 sNumCameras;
extern struct SplineControlPointTimers sSplineControlPointTimers[4];
static u32 game__camera__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, &D_800CD8A8, 4);
	off = mod_write_bytes(out, off, &D_800CD8AC, 4);
	off = mod_write_bytes(out, off, &D_800CDA90, 4);
	off = mod_write_bytes(out, off, &D_800CDA94, 4);
	off = mod_write_bytes(out, off, &D_800CDA98, 4);
	
	
	
	
	
	
	
	
	
	
	off = mod_write_bytes(out, off, &D_800E5E8C, 2);
	off = mod_write_bytes(out, off, gCameras, 2048);
	off = mod_write_bytes(out, off, gFinishedSuccessScript, 80);
	off = mod_write_bytes(out, off, &gScissorBoxBottomCenterQuarter, 32);
	off = mod_write_bytes(out, off, &gScissorBoxBottomHalf, 32);
	off = mod_write_bytes(out, off, &gScissorBoxBottomLeftQuarter, 32);
	off = mod_write_bytes(out, off, &gScissorBoxBottomRightQuarter, 32);
	off = mod_write_bytes(out, off, &gScissorBoxFullScreen, 32);
	off = mod_write_bytes(out, off, &gScissorBoxLeftCenterQuarter, 32);
	off = mod_write_bytes(out, off, &gScissorBoxLeftHalf, 32);
	off = mod_write_bytes(out, off, &gScissorBoxRightCenterQuarter, 32);
	off = mod_write_bytes(out, off, &gScissorBoxRightHalf, 32);
	off = mod_write_bytes(out, off, &gScissorBoxTopCenterQuarter, 32);
	off = mod_write_bytes(out, off, &gScissorBoxTopHalf, 32);
	off = mod_write_bytes(out, off, &gScissorBoxTopLeftQuarter, 32);
	off = mod_write_bytes(out, off, &gScissorBoxTopRightQuarter, 32);
	
	
	off = mod_write_bytes(out, off, kFourCameraScissorBoxTypes, 32);
	off = mod_write_bytes(out, off, kRegularCameraRaceSettings, 48);
	off = mod_write_bytes(out, off, kSingleCameraScissorBoxTypes, 8);
	off = mod_write_bytes(out, off, kThreeCameraScissorBoxTypes, 24);
	off = mod_write_bytes(out, off, kTwoCameraScissorBoxTypes, 16);
	off = mod_write_bytes(out, off, kWidescreenCameraRaceSettings, 48);
	off = mod_write_bytes(out, off, &sAllowCameraLookBack, 4);
	off = mod_write_bytes(out, off, &sCameraEndingFocusRacer, 2);
	off = mod_write_bytes(out, off, &sCameraInfoInitialized, 2);
	off = mod_write_bytes(out, off, sCameraScriptMgrs, 288);
	off = mod_write_bytes(out, off, sCameraSettings, 1024);
	off = mod_write_bytes(out, off, &sEndingCameraMessage, 4);
	off = mod_write_bytes(out, off, &sEyeFromRacerInfo0, 12);
	off = mod_write_bytes(out, off, &sEyeFromRacerInfo4, 12);
	off = mod_write_bytes(out, off, sFinishedSuccessFollowRacerEye, 48);
	off = mod_write_bytes(out, off, &sLerpLocalAtEyeInfo1, 56);
	off = mod_write_bytes(out, off, &sLerpLocalAtEyeInfo2, 56);
	off = mod_write_bytes(out, off, &sLerpLocalAtEyeInfo3, 56);
	off = mod_write_bytes(out, off, &sMaxCameraLookBackRotate, 4);
	off = mod_write_bytes(out, off, &sMultiplayerFocusCameraId, 4);
	off = mod_write_bytes(out, off, &sNumCameras, 4);
	off = mod_write_bytes(out, off, sSplineControlPointTimers, 256);
	return off;
}
