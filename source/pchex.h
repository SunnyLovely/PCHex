#ifndef PCHEX_H
#define PCHEX_H

#include <3ds.h>
#include "pkx.h"

struct s_stateInfo;

struct s_UIState
{
  void (*initf)(struct s_stateInfo *);
  void (*dispf)(struct s_stateInfo *);
  void (*inputf)(struct s_stateInfo *);
};

//General state structure
struct s_stateInfo
{
  u32 			kPressed; //stores what keys are pressed
  PrintConsole 		*console[2]; //consoles - 0 : top 1 : bottom

  struct s_pkm 		pkm; //the currently edited pokemon
  struct s_pkm 		cpy; //the pokemon in the clipboard
  s16 			pkmSlot; //the current box slot which is edited
  u8 			game; //1 is OR/AS, 0 if X/Y
  u8 			*save; //savefile array

  struct s_UIState 	curState; //current state
  s8 			inState; //ID of what is selected
  u8			inSel; //0 if we're editing a value, 1 if we're not
  u8 			modded; //1 if the pokemon has been modified, 0 if not
  s8 			cont; //if 0, terminate the program, if 1, terminate the program and export the savefile
};

typedef struct s_stateInfo t_stinf;

extern struct s_UIState pkmSelectState;
extern struct s_UIState pkmGeneralState;
extern struct s_UIState pkmCombatState;
extern struct s_UIState pkmManageState;

s32     saveFile(char *path, void *src, u64 size, FS_archive *archive, Handle *fsHandle, u32 *bytesWritten);
s32     saveSFile(char *path, void *src, u64 size, FS_archive *archive, Handle *fsHandle, u32 *bytesWritten);
s32 	loadFile(char *path, void *dst, FS_archive *fsarch, Handle *fshdl, u64 maxSize, u32 *bytesRead);
s32 	deleteFile(char *path, Handle *fshdl, FS_archive *fsarch);
s32 	filesysInit(Handle *, Handle *, FS_archive *, FS_archive *);
s32 	filesysExit(Handle *, Handle *, FS_archive *, FS_archive *);

s32 	backupSave(u8 *save, u8 game, Handle *fshdl, FS_archive *fsarch);
s32 	exportSave(u8 *save, u8 game, Handle *fshdl, FS_archive *fsarch);
s32 	loadSave(u8 *save, Handle *fshdl, FS_archive *fsarch);

s32	loadPokemon(t_stinf *state, u16 slot, u8 *dest);
s32	savePokemon(t_stinf *state, u16 slot, u8 *src);
u32 	getCHKOffset(u8 game, u8 type, u8 index);
s32 	switchState(t_stinf *state, struct s_UIState newst);
s32 	startLoop(u8 *, u8, PrintConsole *, PrintConsole *);

s16 	overlayGetpkm();
s16 	overlayGetMove();
s16 	overlayGetAbility();
s16 	overlayGetItems();
s16 	overlayGetBalls();
s16   overlayGetMLocation();

#endif /* end of include guard: PCHEX_H */
