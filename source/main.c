#include <stdio.h>
#include <stdbool.h>

#include "headers/menu.h"
#include "headers/creaco.h"
#include "headers/param_console.h"

#define width 47
#define height 32

int main(int argc, char const *argv[]){

	show_cursor(false);
	if(!resize_console(width, height)){
		printf("Inpossible de redimentionner la console\n");
		getchar();
		exit(EXIT_FAILURE);
	}

	console_game_mode(); // dans param_console.c
	menu(); // dans menu.c
	return 0;
}