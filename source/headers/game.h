#ifndef GAME_H
#define GAME_H

#include "creaco.h"
#include <stdio.h>
#include <stdbool.h>
#include <mmsystem.h>
#include "image.h"
#include "param_console.h"
#include "menu.h"

void chargement();
void play_me_vs_bot(char *p1, char *p2, int niveau);
void play_me_vs_you(char *p1, char *p2);
void tour_p1(char *p1);
void tour_p2(char *p2);
void victoire_test(char *p1, char *p2, int p1_or_p2);
void victoire(char *p1, char *p2, int p1_or_p2);

///////////////foction est variable pour le bot
typedef struct bot_play{
	int a;
	int b;
}bot_play;


int maximun(int a, int b);
int minimum(int a, int b);

int tab_test_full(); //si le tableau et plain

int minimax(int p1_or_bot);
struct bot_play bot_move();
int tour_bot(char *bot);
int evaluation();
#endif
