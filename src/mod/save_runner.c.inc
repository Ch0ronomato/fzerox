#define MOD_GLOBAL_STATE_SIZE 393144
#define MOD_POINTER_RELOC_SIZE 60
#define MOD_HEADER_SIZE 393244
#define MOD_HEADER_BUFFER_SIZE 393728
#include "src/mod/audio__rom__external.c.inc"
#include "src/mod/audio__rom__lib__load.c.inc"
#include "src/mod/audio__rom__lib__seqplayer.c.inc"
#include "src/mod/game__194E0.c.inc"
#include "src/mod/game__EA20.c.inc"
#include "src/mod/game__bordered_box.c.inc"
#include "src/mod/game__camera.c.inc"
#include "src/mod/game__common.c.inc"
#include "src/mod/game__course.c.inc"
#include "src/mod/game__course_gadget_context.c.inc"
#include "src/mod/game__course_gadgets.c.inc"
#include "src/mod/game__game.c.inc"
#include "src/mod/game__game_context.c.inc"
#include "src/mod/game__object.c.inc"
#include "src/mod/game__racer.c.inc"
#include "src/mod/overlays__ovl_i2__effects.c.inc"
#include "src/mod/overlays__ovl_i2__font.c.inc"
#include "src/mod/overlays__ovl_i2__race.c.inc"
#include "src/mod/overlays__ovl_i2__save.c.inc"
#include "src/mod/overlays__ovl_i2__transition.c.inc"
#include "src/mod/overlays__ovl_i3__background.c.inc"
#include "src/mod/overlays__ovl_i3__cpu.c.inc"
#include "src/mod/overlays__ovl_i3__hud.c.inc"
#include "src/mod/overlays__ovl_i3__menus.c.inc"
#include "src/mod/overlays__ovl_i3__minimap.c.inc"
#include "src/mod/overlays__ovl_i3__records_entry.c.inc"
u32 global_write(u8* out, u32 off)
{
	off = audio__rom__external__save(out, off);
	off = audio__rom__lib__load__save(out, off);
	off = audio__rom__lib__seqplayer__save(out, off);
	off = game__194E0__save(out, off);
	off = game__EA20__save(out, off);
	off = game__bordered_box__save(out, off);
	off = game__camera__save(out, off);
	off = game__common__save(out, off);
	off = game__course__save(out, off);
	off = game__course_gadget_context__save(out, off);
	off = game__course_gadgets__save(out, off);
	off = game__game__save(out, off);
	off = game__game_context__save(out, off);
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

u32 global_load(u8* out, u32 off)
{
	off = audio__rom__external__load(out, off);
	off = audio__rom__lib__load__load(out, off);
	off = audio__rom__lib__seqplayer__load(out, off);
	off = game__194E0__load(out, off);
	off = game__EA20__load(out, off);
	off = game__bordered_box__load(out, off);
	off = game__camera__load(out, off);
	off = game__common__load(out, off);
	off = game__course__load(out, off);
	off = game__course_gadget_context__load(out, off);
	off = game__course_gadgets__load(out, off);
	off = game__game__load(out, off);
	off = game__game_context__load(out, off);
	off = game__object__load(out, off);
	off = game__racer__load(out, off);
	off = overlays__ovl_i2__effects__load(out, off);
	off = overlays__ovl_i2__font__load(out, off);
	off = overlays__ovl_i2__race__load(out, off);
	off = overlays__ovl_i2__save__load(out, off);
	off = overlays__ovl_i2__transition__load(out, off);
	off = overlays__ovl_i3__background__load(out, off);
	off = overlays__ovl_i3__cpu__load(out, off);
	off = overlays__ovl_i3__hud__load(out, off);
	off = overlays__ovl_i3__menus__load(out, off);
	off = overlays__ovl_i3__minimap__load(out, off);
	off = overlays__ovl_i3__records_entry__load(out, off);
	return off;
}
