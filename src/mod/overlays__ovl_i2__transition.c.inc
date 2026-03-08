extern short D_i2_80106DA0;
extern Gfx D_i2_80106DB8[1];
extern long gTransitionState;
extern long kTransitionRandomSelection[7];
extern float sStripMoveSpeed;
extern long sSurroundingTileSkipChanceMask[8];
extern short sSurroundingTilesRelativeIndex[8];
extern unsigned short sTiledPerspectiveScale;
extern struct Transition sTransition;
extern short sTransitionIntermediateFillBlack;
extern unsigned short sTransitionPalette[32];
extern unsigned short * sTransitionPalettePtr;
extern short sTransitionTypeArgument;
extern short sTransitionTypeWithArgument;
extern short sWipePos;
static u32 overlays__ovl_i2__transition__save(u8* out, u32 off)
{
	off = mod_write_bytes(out, off, &D_i2_80106DA0, 2);
	off = mod_write_bytes(out, off, D_i2_80106DB8, 16);
	off = mod_write_bytes(out, off, &gTransitionState, 4);
	off = mod_write_bytes(out, off, kTransitionRandomSelection, 56);
	off = mod_write_bytes(out, off, &sStripMoveSpeed, 4);
	off = mod_write_bytes(out, off, sSurroundingTileSkipChanceMask, 64);
	off = mod_write_bytes(out, off, sSurroundingTilesRelativeIndex, 16);
	off = mod_write_bytes(out, off, &sTiledPerspectiveScale, 2);
	off = mod_write_bytes(out, off, &sTransition, 88);
	off = mod_write_bytes(out, off, &sTransitionIntermediateFillBlack, 2);
	off = mod_write_bytes(out, off, sTransitionPalette, 64);
	off = mod_write_bytes(out, off, &sTransitionPalettePtr, 8);
	off = mod_write_bytes(out, off, &sTransitionTypeArgument, 2);
	off = mod_write_bytes(out, off, &sTransitionTypeWithArgument, 2);
	off = mod_write_bytes(out, off, &sWipePos, 2);
	return off;
}
