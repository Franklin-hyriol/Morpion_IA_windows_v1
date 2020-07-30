#include "headers/menu.h"

char sound_active[5] = ":)"; // 1
char sound_desactive[5] = ":("; // 0

char core_2[8] = "core 2 "; // 2
char core_i7[8] = "core i7"; // 7

static param params = {1, 2};

void menu(){

	play_sound_niveau(params);
	preparation_console();

	bool dans_le_menu = true;
	int chois_menu = 0;

	while(dans_le_menu){
		poll_event();
	
		if(mouse_x() > 5 && mouse_x() < 30 && mouse_y() > 11 && mouse_y() < 15){
			set_color(10);

			print_title(2, 3);

			gotoxy(6, 12);
			printf("-----------------------");
			gotoxy(6, 13);
			printf("|   NOUVELLE PARTIE   |");
			gotoxy(6, 14);
			printf("-----------------------");

			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				nouvelle_partie();
			}

		}else if(mouse_x() > 11 && mouse_x() < 35 && mouse_y() > 17 && mouse_y() < 21){
			set_color(6);

			print_title(2, 3);

			gotoxy(12, 18);
			printf("-----------------------");
			gotoxy(12, 19);
			printf("|       OPTIONS       |");
			gotoxy(12, 20);
			printf("-----------------------");

			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				option();
			}
		}else if(mouse_x() > 17 && mouse_x() < 42 && mouse_y() > 23 && mouse_y() < 27){
			set_color(4);

			print_title(2, 3);

			gotoxy(18, 24);
			printf("-----------------------");
			gotoxy(18, 25);
			printf("|       QUITTER       |");
			gotoxy(18, 26);
			printf("-----------------------");

			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				system("cls");
				show_cursor(true);
				set_color(15);
				exit(EXIT_SUCCESS);
			}

		}else{
			set_color(15);

			print_title(2, 3);

			gotoxy(6, 12);
			printf("-----------------------");
			gotoxy(6, 13);
			printf("|   NOUVELLE PARTIE   |");
			gotoxy(6, 14);
			printf("-----------------------");
			gotoxy(12, 18);
			printf("-----------------------");
			gotoxy(12, 19);
			printf("|       OPTIONS       |");
			gotoxy(12, 20);
			printf("-----------------------");
			gotoxy(18, 24);
			printf("-----------------------");
			gotoxy(18, 25);
			printf("|       QUITTER       |");
			gotoxy(18, 26);
			printf("-----------------------");
		}
	}
}


void nouvelle_partie(){

	preparation_console();

	bool dans_le_menu = true;
	int chois_menu = 0;

	while(dans_le_menu){
		poll_event();

		if(mouse_x() > 17 && mouse_x() < 42 && mouse_y() > 14 && mouse_y() < 18){
			set_color(10);

			print_title(2, 3);

			gotoxy(18, 15);
			printf("-----------------------");
			gotoxy(18, 16);
			printf("|    ME versus BOT    |");
			gotoxy(18, 17);
			printf("-----------------------");

			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				me_vs_bot();
			}	
		}else if(mouse_x() > 12 && mouse_x() < 35 && mouse_y() > 20 && mouse_y() < 24){
			set_color(1);

			print_title(2, 3);

			gotoxy(12, 21);
			printf("-----------------------");
			gotoxy(12, 22);
			printf("|    ME versus YOU    |");
			gotoxy(12, 23);
			printf("-----------------------");

			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				me_vs_you();
			}	
		}else if(mouse_x() > 5 && mouse_x() < 30 && mouse_y() > 26 && mouse_y() < 30){
			set_color(6);

			print_title(2, 3);

			gotoxy(6, 27);
			printf("-----------------------");
			gotoxy(6, 28);
			printf("|   REVENIR AU MENU   |");
			gotoxy(6, 29);
			printf("-----------------------");

			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				menu();
			}
		}else{
			set_color(15);

			print_title(2, 3);

			gotoxy(18, 15);
			printf("-----------------------");
			gotoxy(18, 16);
			printf("|    ME versus BOT    |");
			gotoxy(18, 17);
			printf("-----------------------");
			gotoxy(12, 21);
			printf("-----------------------");
			gotoxy(12, 22);
			printf("|    ME versus YOU    |");
			gotoxy(12, 23);
			printf("-----------------------");
			gotoxy(6, 27);
			printf("-----------------------");
			gotoxy(6, 28);
			printf("|   REVENIR AU MENU   |");
			gotoxy(6, 29);
			printf("-----------------------");		
		}
	}
}


void option(){
	preparation_console();

	bool dans_option = true;

	char etat[5];
	char level[8];

	if(params.sound == 1){
		strcpy(etat, sound_active);
	}else{
		strcpy(etat,sound_desactive);
	}

	if(params.niveau == 2){
		strcpy(level, core_2);
	}else{
		strcpy(level, core_i7);
	}

	while(dans_option){
		poll_event();

		if(mouse_x() > 17 && mouse_x() < 42 && mouse_y() > 14 && mouse_y() < 18){
			set_color(10);

			print_title(2, 3);

			if(params.sound == 1){
				strcpy(etat, sound_active);
			}else{
				strcpy(etat,sound_desactive);
			}			

			gotoxy(18, 15);
			printf("-----------------------");
			gotoxy(18, 16);
			printf("| Activer le son: %s  |",etat);
			gotoxy(18, 17);
			printf("-----------------------");

			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(params.sound == 1){
					params.sound = 0;
				}else{
					params.sound = 1;
				}
				Sleep(200);
			}	
		}else if(mouse_x() > 12 && mouse_x() < 35 && mouse_y() > 20 && mouse_y() < 24){
			set_color(1);

			print_title(2, 3);

			if(params.niveau == 2){
				strcpy(level, core_2);
			}else{
				strcpy(level, core_i7);
			}

			gotoxy(12, 21);
			printf("-----------------------");
			gotoxy(12, 22);
			printf("|  niveau bot: %s|",level);
			gotoxy(12, 23);
			printf("-----------------------");

			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(params.niveau == 2){
					params.niveau = 7;
				}else{
					params.niveau = 2;
				}
				Sleep(200);
			}	
		}else if(mouse_x() > 5 && mouse_x() < 30 && mouse_y() > 26 && mouse_y() < 30){
			set_color(6);

			print_title(2, 3);

			gotoxy(6, 27);
			printf("-----------------------");
			gotoxy(6, 28);
			printf("|   REVENIR AU MENU   |");
			gotoxy(6, 29);
			printf("-----------------------");

			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				menu();
			}
		}else{

			if(params.sound == 1){
				strcpy(etat, sound_active);
			}else{
				strcpy(etat,sound_desactive);
			}

			if(params.niveau == 2){
				strcpy(level, core_2);
			}else{
				strcpy(level, core_i7);
			}

			set_color(15);

			print_title(2, 3);

			gotoxy(18, 15);
			printf("-----------------------");
			gotoxy(18, 16);
			printf("| Activer le son: %s  |",etat);
			gotoxy(18, 17);
			printf("-----------------------");
			gotoxy(12, 21);
			printf("-----------------------");
			gotoxy(12, 22);
			printf("|  niveau bot: %s|",level);
			gotoxy(12, 23);
			printf("-----------------------");
			gotoxy(6, 27);
			printf("-----------------------");
			gotoxy(6, 28);
			printf("|   REVENIR AU MENU   |");
			gotoxy(6, 29);
			printf("-----------------------");		
		}
	}	
}


void me_vs_bot(){
	char psedo[20];

show_cursor(true);

	preparation_console();
	set_color(15);

	gotoxy(18, 3);
	printf("PARAMETRE");

	gotoxy(12, 12);
	printf("VOTRE ADVERSAIRE (O): R2P2");

	print_r2p2(14, 14);

	gotoxy(12, 8);
	printf("VOTRE PSEDO (X): ");
	set_color(4);
	scanf("%s", psedo);
	
	fflush(stdin);

	play_me_vs_bot(psedo, "r2p2", params.niveau);
}

void me_vs_you(){
	char psedo_p1[30];
	char psedo_p2[30];

show_cursor(true);

	preparation_console();
	set_color(15);

	gotoxy(18, 3);
	printf("PARAMETRE");

	print_gladiator(14, 18);

	gotoxy(12, 8);
	printf("PSEDO PLAYER 1 (X): ");
	set_color(4);
	scanf("%s", psedo_p1);

	gotoxy(12, 10);
	set_color(15);
	printf("PSEDO PLAYER 2 (O): ");
	set_color(1);
	scanf("%s", psedo_p2);

	fflush(stdin);

	play_me_vs_you(psedo_p1, psedo_p2);

}



int play_sound_niveau(param params){
	if(params.sound == 1)
		PlaySound("track/sound.wav", NULL, SND_ASYNC);
	else{
		PlaySound(NULL, 0, 0);
	}
	return 0;
}

