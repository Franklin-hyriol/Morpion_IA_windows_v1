#include "headers/param_console.h"

#define width 47
#define height 32

void preparation_console(){

	CHBITMAP *preparation = create_chb(width, height);
	fill_chb(preparation, 0, 0);
	show_to_console(preparation, 0, 0);

	free_chb(preparation);
}

void console_game_mode(){
	HANDLE hinput = GetConsoleW();
	 SetWindowLong(hinput, GWL_STYLE,
               GetWindowLong(hinput, GWL_STYLE) & ~WS_MAXIMIZEBOX);

	 SetConsoleMode(hinput, ENABLE_EXTENDED_FLAGS);
}