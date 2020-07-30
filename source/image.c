#include "headers/image.h"

void print_cadre(int x, int y){// 34, 15

set_color(15);
gotoxy(x, y);
printf("                  MORPION                  ");
gotoxy(x, y+1);
printf("___________________________________________");
gotoxy(x, y+2);
printf("|             |             |             |");
gotoxy(x, y+3);
printf("|             |             |             |");
gotoxy(x, y+4);
printf("|             |             |             |");
gotoxy(x, y+5);
printf("|             |             |             |");
gotoxy(x, y+6);
printf("|             |             |             |");
gotoxy(x, y+7);
printf("|             |             |             |");
gotoxy(x, y+8);
printf("|_____________|_____________|_____________|");
gotoxy(x, y+9);
printf("|             |             |             |");
gotoxy(x, y+10);
printf("|             |             |             |");
gotoxy(x, y+11);
printf("|             |             |             |");
gotoxy(x, y+12);
printf("|             |             |             |");
gotoxy(x, y+13);
printf("|             |             |             |");
gotoxy(x, y+14);
printf("|             |             |             |");
gotoxy(x, y+15);
printf("|_____________|_____________|_____________|");
gotoxy(x, y+16);
printf("|             |             |             |");
gotoxy(x, y+17);
printf("|             |             |             |");
gotoxy(x, y+18);
printf("|             |             |             |");
gotoxy(x, y+19);
printf("|             |             |             |");
gotoxy(x, y+20);
printf("|             |             |             |");
gotoxy(x, y+21);
printf("|             |             |             |");
gotoxy(x, y+22);
printf("|_____________|_____________|_____________|");
gotoxy(x, y+24);
printf(" UTILISER LA SOURIS POUR ENTRER LES TUILS ");

}


void print_X(int x, int y){
	set_color(4);
	gotoxy(x, y);
	printf("\\\\   //");
	gotoxy(x+1, y+1);
	printf("\\\\ //");
	gotoxy(x+3, y+2);
	printf("X");
	gotoxy(x+1, y+3);
	printf("// \\\\");
	gotoxy(x, y+4);
	printf("//   \\\\");
}


void print_O(int x, int y){
	set_color(1);
	gotoxy(x, y);
	printf("OOOOOOO");
	gotoxy(x, y+1);
	printf("OO   OO");
	gotoxy(x, y+2);
	printf("OO   OO");
	gotoxy(x, y+3);
	printf("OO   OO");
	gotoxy(x, y+4);
	printf("OOOOOOO");
}

void print_title(int x, int y){
	gotoxy(x, y);
	printf("M     M OOOOO RRRRR  PPPPP III OOOOO N    N");
	gotoxy(x, y+1);
	printf("M M M M O   O R    R P   P  I  O   O N N  N");
	gotoxy(x, y+2);
	printf("M  M  M O   O RRRRR  PPPPP  I  O   O N  N N");
	gotoxy(x, y+3);
	printf("M     M OOOOO R    R P     III OOOOO N    N");
}

void print_r2p2(int x, int y){
	gotoxy(x, y);
	printf("       _____");
	gotoxy(x, y+1);
	printf("     .'/L|__`.");
	gotoxy(x, y+2);
	printf("    / =[_]O|` \\");
	gotoxy(x, y+3);
	printf("    |\"+_____\":|");
	gotoxy(x, y+4);
	printf("  __:='|____`-:__");
	gotoxy(x, y+5);
	printf(" ||[] ||====| []||");
	gotoxy(x, y+6);
	printf(" ||[] | |=| | []||");
	gotoxy(x, y+7);
	printf(" |:||_|=|U| |_||:|");
	gotoxy(x, y+8);
	printf(" |:|||]_=_ =[_||:|");
	gotoxy(x, y+9);
	printf(" | |||] [_][]C|| |");
	gotoxy(x, y+10);
	printf(" | ||-'\"\"\"\"\"`-|| |");
	gotoxy(x, y+11);
	printf(" /|\\\\_\\_|_|_/_//|\\");
	gotoxy(x, y+12);
	printf("|___|   /|\\   |___|");
	gotoxy(x, y+13);
	printf("`---'  |___|  `---'");
	gotoxy(x, y+14);
	printf("       `---'");
	gotoxy(x, y+16);
	printf("ENTRER POUR VALIDEE");

}

void print_gladiator(int x, int y){
	gotoxy(x, y);
	printf("     ___");
	gotoxy(x, y+1);
	printf("    /___\\");
	gotoxy(x, y+2);
	printf("   (|0 0|)");
	gotoxy(x, y+3);
	printf(" __/{\\U/}\\_ ___/vvv");
	gotoxy(x, y+4);
	printf("/ \\  {~}   / _|_P|");
	gotoxy(x, y+5);
	printf("| /\\  ~   /_/   ||");
	gotoxy(x, y+6);
	printf("| /\\  ~   /_/   ||");
	gotoxy(x, y+7);
	printf("|_| (____)      ||");
	gotoxy(x, y+8);
	printf("\\_]/______\\  /\\_||_/\\");
	gotoxy(x, y+9);
	printf("   _\\_||_/_ |] _||_ [|");
	gotoxy(x, y+10);
	printf("  (_,_||_,_) \\/ [] \\/");
	gotoxy(x, y+12);
	printf("ENTRER POUR VALIDEE\n");

}














   
