#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "ansi.h"
#include "controls.h"
#include "entity_structs.h"
#ifndef _MENUSCREEN_H_
#define _MENUSCREEN_H_

void loadMenu();

void selectInMenu(gameHandler_t *game);

void loadOptions(gameHandler_t *game);

void selectInOptions(gameHandler_t *game);

void loadHowToPlay();

void loadCredits();

void selectInCreditsAndHowToPlay();

void loadPause();

void selectInPause(gameHandler_t *game);

void loadGame();


#endif
