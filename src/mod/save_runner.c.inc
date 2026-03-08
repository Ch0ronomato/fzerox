#include "mod/audio__rom__external.c.inc"
#include "mod/audio__rom__lib__effects.c.inc"
#include "mod/audio__rom__lib__heap.c.inc"
#include "mod/audio__rom__lib__load.c.inc"
#include "mod/audio__rom__lib__playback.c.inc"
#include "mod/audio__rom__lib__seqplayer.c.inc"
#include "mod/audio__rom__lib__synthesis.c.inc"
#include "mod/audio__rom__lib__thread.c.inc"
#include "mod/game__194E0.c.inc"
#include "mod/game__EA20.c.inc"
#include "mod/game__bordered_box.c.inc"
#include "mod/game__camera.c.inc"
#include "mod/game__common.c.inc"
#include "mod/game__course.c.inc"
#include "mod/game__course_gadgets.c.inc"
#include "mod/game__game.c.inc"
#include "mod/game__object.c.inc"
#include "mod/game__racer.c.inc"
#include "mod/overlays__ovl_i2__effects.c.inc"
#include "mod/overlays__ovl_i2__font.c.inc"
#include "mod/overlays__ovl_i2__race.c.inc"
#include "mod/overlays__ovl_i2__save.c.inc"
#include "mod/overlays__ovl_i2__transition.c.inc"
#include "mod/overlays__ovl_i3__background.c.inc"
#include "mod/overlays__ovl_i3__cpu.c.inc"
#include "mod/overlays__ovl_i3__hud.c.inc"
#include "mod/overlays__ovl_i3__menus.c.inc"
#include "mod/overlays__ovl_i3__minimap.c.inc"
#include "mod/overlays__ovl_i3__records_entry.c.inc"
u32 global_write(u8* out, u32 off)
{
	off = audio__rom__external__save(out, off);
	off = audio__rom__lib__effects__save(out, off);
	off = audio__rom__lib__heap__save(out, off);
	off = audio__rom__lib__load__save(out, off);
	off = audio__rom__lib__playback__save(out, off);
	off = audio__rom__lib__seqplayer__save(out, off);
	off = audio__rom__lib__synthesis__save(out, off);
	off = audio__rom__lib__thread__save(out, off);
	off = game__194E0__save(out, off);
	off = game__EA20__save(out, off);
	off = game__bordered_box__save(out, off);
	off = game__camera__save(out, off);
	off = game__common__save(out, off);
	off = game__course__save(out, off);
	off = game__course_gadgets__save(out, off);
	off = game__game__save(out, off);
	off = game__object__save(out, off);
	off = game__racer__save(out, off);
	off = overlays__ovl_i2__effects__save(out, off);
	off = overlays__ovl_i2__font__save(out, off);
	off = overlays__ovl_i2__race__save(out, off);
	off = overlays__ovl_i2__save__save(out, off);
	off = overlays__ovl_i2__transition__save(out, off);
	off = overlays__ovl_i3__background__save(out, off);
	off = overlays__ovl_i3__cpu__save(out, off);
	off = overlays__ovl_i3__hud__save(out, off);
	off = overlays__ovl_i3__menus__save(out, off);
	off = overlays__ovl_i3__minimap__save(out, off);
	off = overlays__ovl_i3__records_entry__save(out, off);
	return off;
}
