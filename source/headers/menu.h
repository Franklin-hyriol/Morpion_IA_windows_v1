#ifndef MENU_H
#define MENU_H

#include "creaco.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <mmsystem.h>

#include "image.h"
#include "param_console.h"
#include "game.h"

typedef struct param{
	int sound;
	int niveau;
}param;

int play_sound_niveau(param params);

void menu();
void nouvelle_partie();
void option();
void me_vs_bot();
void me_vs_you();

#endif
