#include "headers/game.h"

int game_matrice[3][3];
int bot_simulation[3][3];

int static level = 0;
////////////////////////////////////////////////////

void play_me_vs_bot(char *p1, char *p2, int niveau){

	level = niveau;

	show_cursor(false);
	bool game_over = false;
	int tour = 1;
	chargement();
	preparation_console();
	print_cadre(2, 6);

	while(!game_over){
		if(tour == 1){
			tour_p1(p1);
			victoire_test(p1, p2, 1);
			tour = 2;
			PlaySound("track/x.wav", NULL, SND_ASYNC);
		}else{
			Sleep(400);
			tour_bot(p2);
			victoire_test(p1, p2, 2);
			tour = 1;
			PlaySound("track/o.wav", NULL, SND_ASYNC);
		}
	}
}

///////////////////////////////////////////////////////////////


void play_me_vs_you(char *p1, char *p2){
	show_cursor(false);
	bool game_over = false;
	int tour = 1;
	chargement();
	preparation_console();
	print_cadre(2, 6);

	while(!game_over){
		if(tour == 1){
			tour_p1(p1);
			victoire_test(p1, p2, 1);
			tour = 2;
			PlaySound("track/x.wav", NULL, SND_ASYNC);
		}else{
			tour_p2(p2);
			victoire_test(p1, p2, 2);
			tour = 1;
			PlaySound("track/o.wav", NULL, SND_ASYNC);
		}
	}
}


////////////////////////////////////////////////////////////////

void tour_p1(char *p1){
	bool valide_imput = false;
	gotoxy(11, 3);
	set_color(4);
	printf("%s c'est votre tour          ", p1);

	while(!valide_imput){
		poll_event();
		if(mouse_x() > 2 && mouse_x() < 17 && mouse_y() > 6 && mouse_y() < 14){
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[0][0] == 0){
			    	set_color(4);
					print_X(6, 9);
					game_matrice[0][0] = 1;
					break;							
				}
			}
		}else if(mouse_x() > 16 && mouse_x() < 31 && mouse_y() > 6 && mouse_y() < 14){
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[0][1] == 0){
			    	set_color(4);
					print_X(20, 9);
					game_matrice[0][1] = 1;
					break;							
				}
			}					
		}else if(mouse_x() > 30 && mouse_x() < 44 && mouse_y() > 6 && mouse_y() < 14){
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[0][2] == 0){
			    	set_color(4);
					print_X(33, 9);
					game_matrice[0][2] = 1;
					break;							
				}
			}					
		}else if(mouse_x() > 2 && mouse_x() < 17 && mouse_y() > 13 && mouse_y() < 21){/////////
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[1][0] == 0){
			    	set_color(4);
					print_X(6, 16);
					game_matrice[1][0] = 1;
					break;							
				}
			}
		}else if(mouse_x() > 16 && mouse_x() < 31 && mouse_y() > 13 && mouse_y() < 21){
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[1][1] == 0){
			    	set_color(4);
					print_X(20, 16);
					game_matrice[1][1] = 1;
					break;							
				}
			}					
		}else if(mouse_x() > 30 && mouse_x() < 44 && mouse_y() > 13 && mouse_y() < 21){
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[1][2] == 0){
			    	set_color(4);
					print_X(34, 16);
					game_matrice[1][2] = 1;
					break;							
				}
			}					
		}else if(mouse_x() > 2 && mouse_x() < 17 && mouse_y() > 20 && mouse_y() < 28){////////
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[2][0] == 0){
			    	set_color(4);
					print_X(6, 23);
					game_matrice[2][0] = 1;
					break;							
				}
			}
		}else if(mouse_x() > 16 && mouse_x() < 31 && mouse_y() > 20 && mouse_y() < 28){
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[2][1] == 0){
			    	set_color(4);
					print_X(20, 23);
					game_matrice[2][1] = 1;
					break;							
				}
			}					
		}else if(mouse_x() > 30 && mouse_x() < 44 && mouse_y() > 20 && mouse_y() < 28){
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[2][2] == 0){
			    	set_color(4);
					print_X(34, 23);
					game_matrice[2][2] = 1;
					break;							
				}
			}					
		}
	}
}


/////////////////////////////////////////////////////////////////////

void tour_p2(char *p2){
	bool valide_imput = false;
	gotoxy(11, 3);
	set_color(1);
	printf("%s c'est votre tour          ", p2);

	while(!valide_imput){
		poll_event();
		if(mouse_x() > 2 && mouse_x() < 17 && mouse_y() > 6 && mouse_y() < 14){
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[0][0] == 0){
			    	set_color(1);
					print_O(6, 9);
					game_matrice[0][0] = 2;
					break;							
				}
			}
		}else if(mouse_x() > 16 && mouse_x() < 31 && mouse_y() > 6 && mouse_y() < 14){
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[0][1] == 0){
			    	set_color(1);
					print_O(20, 9);
					game_matrice[0][1] = 2;
					break;							
				}
			}					
		}else if(mouse_x() > 30 && mouse_x() < 44 && mouse_y() > 6 && mouse_y() < 14){
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[0][2] == 0){
			    	set_color(1);
					print_O(33, 9);
					game_matrice[0][2] = 2;
					break;							
				}
			}					
		}else if(mouse_x() > 2 && mouse_x() < 17 && mouse_y() > 13 && mouse_y() < 21){/////////
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[1][0] == 0){
			    	set_color(1);
					print_O(6, 16);
					game_matrice[1][0] = 2;
					break;							
				}
			}
		}else if(mouse_x() > 16 && mouse_x() < 31 && mouse_y() > 13 && mouse_y() < 21){
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[1][1] == 0){
			    	set_color(1);
					print_O(20, 16);
					game_matrice[1][1] = 2;
					break;							
				}
			}					
		}else if(mouse_x() > 30 && mouse_x() < 44 && mouse_y() > 13 && mouse_y() < 21){
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[1][2] == 0){
			    	set_color(1);
					print_O(34, 16);
					game_matrice[1][2] = 2;
					break;							
				}
			}					
		}else if(mouse_x() > 2 && mouse_x() < 17 && mouse_y() > 20 && mouse_y() < 28){////////
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[2][0] == 0){
			    	set_color(1);
					print_O(6, 23);
					game_matrice[2][0] = 2;
					break;							
				}
			}
		}else if(mouse_x() > 16 && mouse_x() < 31 && mouse_y() > 20 && mouse_y() < 28){
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[2][1] == 0){
			    	set_color(1);
					print_O(20, 23);
					game_matrice[2][1] = 2;
					break;							
				}
			}					
		}else if(mouse_x() > 30 && mouse_x() < 44 && mouse_y() > 20 && mouse_y() < 28){
			if(clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
				if(game_matrice[2][2] == 0){
			    	set_color(1);
					print_O(34, 23);
					game_matrice[2][2] = 2;
					break;							
				}
			}					
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////

int tour_bot(char *bot){
	bool valide_imput = false;
	gotoxy(11, 3);
	set_color(1);
	printf("%s: calcul en cours..            ", bot);

	int i,j;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			bot_simulation[i][j] = game_matrice[i][j];
		}
	}

	struct bot_play resultat;

	resultat = bot_move();

	i = resultat.a;
	j = resultat.b;

	if(i==0 && j==0){
		set_color(1);
		print_O(6, 9);
		game_matrice[0][0] = 2;
		return 0;

	}
	if(i==0 && j==1){
		set_color(1);
		print_O(20, 9);
		game_matrice[0][1] = 2;
		return 0;

	}
	if(i==0 && j==2){
    	set_color(1);
		print_O(33, 9);
		game_matrice[0][2] = 2;
		return 0;

	}
	if(i==1 && j==0){
    	set_color(1);
		print_O(6, 16);
		game_matrice[1][0] = 2;
		return 0;

	}
	if(i==1 && j==1){
    	set_color(1);
		print_O(20, 16);
		game_matrice[1][1] = 2;
		return 0;

	}
	if(i==1 && j==2){
    	set_color(1);
		print_O(34, 16);
		game_matrice[1][2] = 2;
		return 0;

	}
	if(i==2 && j==0){
    	set_color(1);
		print_O(6, 23);
		game_matrice[2][0] = 2;
		return 0;

	}
	if(i==2 && j==1){
    	set_color(1);
		print_O(20, 23);
		game_matrice[2][1] = 2;
		return 0;			
	}
	if(i==2 && j==2){
    	set_color(1);
		print_O(34, 23);
		game_matrice[2][2] = 2;
		return 0;			
	}
}

////////////////////////////////////////////////////////////////////////////


void victoire_test(char *p1, char *p2, int p1_or_p2){
	if(game_matrice[0][0] == 1 && game_matrice[0][1] == 1 && game_matrice[0][2] == 1){ // player 1
		victoire(p1, p2, p1_or_p2);
	}else if(game_matrice[1][0] == 1 && game_matrice[1][1] == 1 && game_matrice[1][2] == 1){
		victoire(p1, p2, p1_or_p2);
	}else if(game_matrice[2][0] == 1 && game_matrice[2][1] == 1 && game_matrice[2][2] == 1){
		victoire(p1, p2, p1_or_p2);
	}else if(game_matrice[0][0] == 1 && game_matrice[1][0] == 1 && game_matrice[2][0] == 1){
		victoire(p1, p2, p1_or_p2);
	}else if(game_matrice[0][1] == 1 && game_matrice[1][1] == 1 && game_matrice[2][1] == 1){
		victoire(p1, p2, p1_or_p2);
	}else if(game_matrice[0][2] == 1 && game_matrice[1][2] == 1 && game_matrice[2][2] == 1){
		victoire(p1, p2, p1_or_p2);
	}else if(game_matrice[0][0] == 1 && game_matrice[1][1] == 1 && game_matrice[2][2] == 1){
		victoire(p1, p2, p1_or_p2);
	}else if(game_matrice[0][2] == 1 && game_matrice[1][1] == 1 && game_matrice[2][0] == 1){
		victoire(p1, p2, p1_or_p2);
	}else if(game_matrice[0][0] == 2 && game_matrice[0][1] == 2 && game_matrice[0][2] == 2){ //player 2
		victoire(p1, p2, p1_or_p2);
	}else if(game_matrice[1][0] == 2 && game_matrice[1][1] == 2 && game_matrice[1][2] == 2){
		victoire(p1, p2, p1_or_p2);
	}else if(game_matrice[2][0] == 2 && game_matrice[2][1] == 2 && game_matrice[2][2] == 2){
		victoire(p1, p2, p1_or_p2);
	}else if(game_matrice[0][0] == 2 && game_matrice[1][0] == 2 && game_matrice[2][0] == 2){
		victoire(p1, p2, p1_or_p2);
	}else if(game_matrice[0][1] == 2 && game_matrice[1][1] == 2 && game_matrice[2][1] == 2){
		victoire(p1, p2, p1_or_p2);
	}else if(game_matrice[0][2] == 2 && game_matrice[1][2] == 2 && game_matrice[2][2] == 2){
		victoire(p1, p2, p1_or_p2);
	}else if(game_matrice[0][0] == 2 && game_matrice[1][1] == 2 && game_matrice[2][2] == 2){
		victoire(p1, p2, p1_or_p2);
	}else if(game_matrice[0][2] == 2 && game_matrice[1][1] == 2 && game_matrice[2][0] == 2){
		victoire(p1, p2, p1_or_p2);
	}

	int i,j,mach_nul = 0;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			if(game_matrice[i][j] != 0){
				mach_nul++;
			}
		}
	}

	if(mach_nul == 9){
		victoire(p1, p2, 3);
	}
}

///////////////////////////////////////////////////////////////7

void victoire(char *p1, char *p2, int p1_or_p2){
	preparation_console();
	if(p1_or_p2 == 1){
		gotoxy(8, 10);
		set_color(15);
		printf("%s vous avez gagner", p1);
		gotoxy(8, 12);
		set_color(15);
		printf("%s t'est nul :D", p2);
	}else if(p1_or_p2 == 2){
		gotoxy(8, 10);
		set_color(15);
		printf("%s vous avez gagner", p2);
		gotoxy(8, 12);
		set_color(15);
		printf("%s t'est nul :D", p1);

	}else{
		gotoxy(8, 10);
		set_color(15);
		printf("GAME OVER mache nulle");
		gotoxy(5, 12);
		set_color(15);
		printf("%s, %s faite une nouvelle partie", p1, p2);		
	}
	gotoxy(10, 14);
	printf("retour au menu dans");


	int i,j;
	for(i=5; i>0; i--){
		gotoxy(15, 16);
		printf("%d s\r", i);
		Sleep(1000);
	}

	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			game_matrice[i][j] = 0;
		}
	}
	menu();
}

/////////////////////////////////////////////////////

void chargement(){ // sans ca le souris fait des auto_clic
	int i,j;
	preparation_console();
	set_color(10);
	gotoxy(14, 14);
	printf("chargement.20%         ");
	Sleep(200);

	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			game_matrice[i][j] = 0;
		}
	}

	gotoxy(14, 14);
	printf("chargement..40%         ");
	Sleep(200);
	gotoxy(14, 14);
	printf("chargement...60%         ");
	Sleep(200);

	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			bot_simulation[i][j] = 0;
		}
	}

	gotoxy(14, 14);
	printf("chargement....80%         ");
	Sleep(200);
	gotoxy(14, 14);
	printf("chargement......100%         ");

	preparation_console();
	gotoxy(5, 14);
	set_color(15);
	printf("Clique l'ecran pour lamcer la partie\n");
	while(1){
		poll_event();
		if(!clic_pressed(FROM_LEFT_1ST_BUTTON_PRESSED)){
			break;
		}
	}
}

//////////////////////////////////////////////////////
int minimax(int p1_or_bot){ 
    int score = evaluation();
  
    if(score == 10){ 
        return score;
    } 
  
    if(score == -10){
        return score;    	
    } 
 

    if(tab_test_full() == false){
        return 0;    	
    } 
 
  

  int i,j;

    if(p1_or_bot == 2) { //max move
        int best = -1000; 
   
        for (i = 0; i<3; i++) { 
            for (j = 0; j<3; j++) { 
                if(bot_simulation[i][j]==0){ 
                    bot_simulation[i][j]=2;

                    best = maximun(best, minimax(1)); 

                    bot_simulation[i][j]=0; 
                } 
            } 
        } 
        return best;

    }else{ /////min move

        int best = 1000;  
        for (int i = 0; i<3; i++) { 
            for (int j = 0; j<3; j++){ 
                if (bot_simulation[i][j]==0){

                    bot_simulation[i][j]=1; 

                    best = minimum(best, minimax(2)); 

  					bot_simulation[i][j]=0;   
                } 
            } 
        } 
        return best; 
    } 
}

//////////////////////////////////////////////

int maximun(int a, int b){
	if(a>b){
		return a;
	}else{
		return b;
	}
}

int minimum(int a, int b){
	if(a>b){
		return b;
	}else{
		return a;
	}
}


///////////////////////////////////////////////////

struct bot_play bot_move(){
    int bestVal = -1000; 
    struct bot_play bestMove; 
    bestMove.a = -1; 
    bestMove.b = -1; 
  
  	int i,j;

    for(i=0; i<3; i++){ 
        for(j=0; j<3; j++){
            if(bot_simulation[i][j]==0){ 

                bot_simulation[i][j] = 2; 

                int moveVal = minimax(1); 
  
                bot_simulation[i][j]=0;
  
                if (moveVal > bestVal){ 
                    bestMove.a = i; 
                    bestMove.b = j; 
                    bestVal = moveVal; 
                } 
            } 
        } 
    }

    return bestMove; 
}

///////////////////////////////////////////////////

int evaluation(){
	if(bot_simulation[0][0] == bot_simulation[0][1] && bot_simulation[0][1] == bot_simulation[0][2] && bot_simulation[0][0] != 0){
		if(bot_simulation[0][0] == 2){
			return 10;
		}else{
			return -10;
		}
	}

	if(bot_simulation[1][0] == bot_simulation[1][1] && bot_simulation[1][1] == bot_simulation[1][2] && bot_simulation[1][0] != 0){
		if(bot_simulation[1][0] == 2){
			return 10;
		}else{
			return -10;
		}
	}

	if(bot_simulation[2][0] == bot_simulation[2][1] && bot_simulation[2][1] == bot_simulation[2][2] && bot_simulation[2][0] != 0){
		if(bot_simulation[2][0] == 2){
			return 10;
		}else{
			return -10;
		}
	}

/////////////////////////////////////////

	if(bot_simulation[0][0] == bot_simulation[1][0] && bot_simulation[1][0] == bot_simulation[2][0] && bot_simulation[0][0] != 0){
		if(bot_simulation[0][0] == 2){
			return 10;
		}else{
			return -10;
		}
	}	

	if(bot_simulation[0][1] == bot_simulation[1][1] && bot_simulation[1][1] == bot_simulation[2][1] && bot_simulation[0][1] != 0){
		if(bot_simulation[0][1] == 2){
			return 10;
		}else{
			return -10;
		}
	}

	if(bot_simulation[0][2] == bot_simulation[1][2] && bot_simulation[1][2] == bot_simulation[2][2] && bot_simulation[0][2] != 0){
		if(bot_simulation[0][2] == 2){
			return 10;
		}else{
			return -10;
		}
	}

/////////////////////////////

	if(bot_simulation[0][0] == bot_simulation[1][1] && bot_simulation[1][1] == bot_simulation[2][2] && bot_simulation[0][0] != 0){
		if(bot_simulation[0][0] == 2){
			return 10;
		}else{
			return -10;
		}
	}

	if(bot_simulation[0][2] == bot_simulation[1][1] && bot_simulation[1][1] == bot_simulation[2][0] && bot_simulation[0][2] != 0){
		if(bot_simulation[0][2] == 2){
			return 10;
		}else{
			return -10;
		}
	}



	return 0;
}

int tab_test_full(){
	int i,j;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			if(bot_simulation[i][j] == 0){
				return true;
			}
		}
	}
return false;
}