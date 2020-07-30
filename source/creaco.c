#include "headers/creaco.h"


/**********************************************************
*
*  CONSTRUCTEURS (structures) :
*
**********************************************************/
/*
   coord fonction initialise une structure COORD
*/
COORD coord(int x, int y)
{
COORD c;
   c.X=x;
   c.Y=y;
   return c;
}

/**********************************************************
*
*  STAFF CONSOLE/LIBRAIRIE
*
**********************************************************/
/*
GetStdout fonction
R�cup�rer le handle pour les sorties sur la fen�tre console
*/
HANDLE GetStdout()
{
static HANDLE h=NULL;
   if (h==NULL){
      h=GetStdHandle(STD_OUTPUT_HANDLE);
      if (h == INVALID_HANDLE_VALUE)
         debug(Fatal,"impossible obtenir std output handle");
   }
   return h;
}


/**********************************************************
GetStdin fonction
R�cup�rer le handle pour les entr�es console
*/
HANDLE GetStdin()
{
static HANDLE h=NULL;
   if (h==NULL){
      h=GetStdHandle(STD_INPUT_HANDLE);
      if (h == INVALID_HANDLE_VALUE)
         debug(Fatal,"impossible obtenir std input handle");
   }
   return h;
}

/**********************************************************
GetConsoleW fonction
R�cup�rer le handle pour la fen�tre console
*/
HANDLE GetConsoleW()
{
static HANDLE h=NULL;
   if (h==NULL){
      h=GetConsoleWindow();
      if (h == INVALID_HANDLE_VALUE)
         debug(Fatal,"impossible obtenir handle fen�tre console");
   }
   return h;
}

/**********************************************************
debug fonction
permet de tracer et g�rer des erreurs.
*/
void debug(int errLevel,char*msg)
{

   gotoxy(0,0);
   switch(errLevel){
      case Info    : printf("Info");      break;
      case Warming : printf("Warming");   break;
      case Error   : printf("Error");     break;
      case Fatal   : printf("Fatal");     break;
   }
   printf(" : %s\nligne %d\nfile %s\n",msg,__LINE__,__FILE__);
   system("PAUSE");
   if(errLevel==Fatal)
      exit(EXIT_FAILURE);

   // �ventuellement possibilit� d'utiliser GetLastError():
   // avec la fonction FormatMessage() qui donne les infos
   // tir�es du System Error Codes.
   // return GetLastError(); // unsigned int
}
/**********************************************************
*
*  SCREEN CONSOLE
*
**********************************************************/
/*
resize_console fonction
Redimensionner la console (buffer des donn�es et fen�tre
affich�e).

width re�oit la largeur voulue pour la fen�tre
height re�oit la hauteur voulue pour la fen�tre
Fen�tre affich�e et buffer des donn�es ont la m�me taille
(pour avoir un buffer plus grand il faut modifier un peu
la fonction)

Il y a une taille minimum qui est de 80 charact�res en largeur
et 25 caract�res en hauteur

Il y a �galement une taille maximum d�termin�e automatiquement
selon la r�solution de l'�cran et la taille des caract�res
(s�lectionn�e directement par l'utilisateur avec une fen�tre
 console ouverte).

La fonction retourne  TRUE (1) en cas de r�ussite et FALSE (0)
en cas d'erreur
*/
BOOL resize_console(int width, int height)
{
COORD size, sizeMax;
// les valeurs minimums au d�part
SMALL_RECT rBuffer={0,0,10,5};//Left,Top,Right,Bottom
SMALL_RECT rWindow={0,0,1,1};


   // chercher la taille minimum ?
   // GetSystemMetric() SM_CXMIN et SM_CYMIN
   // remarque : actuellement impossible g�rer fontes et polices sous mingw

   // r�duire la fen�tre au minimum (possibilit� de faire par �tape
   // pour �viter r�duction brutale parfois visible)
   if(!SetConsoleWindowInfo(GetStdout(),TRUE, &rWindow )){
      debug(Error,"[resize_console]SetConsoleWindowInfo()");
      return FALSE;
   }

   // nouvelle taille du buffer :
   //    - taille minimum : 25*80
   //    - taille maximum du buffer align�e sur taille max de fen�tre
   //
   // Remarque :
   // la taille maximum n'est pas obligatoire pour le buffer.
   // Le buffer console peut ex�der la taille de la fen�tre
   // (mais pas l'inverse)

   sizeMax=GetLargestConsoleWindowSize(GetStdout());

    // contr�le taille min et max
   size.X = (width < rBuffer.Right) ? rBuffer.Right :
            ((width >sizeMax.X) ? sizeMax.X : width);
   size.Y = (height< rBuffer.Bottom)? rBuffer.Bottom:
            ((height>sizeMax.Y) ? sizeMax.Y : height);

   if (!SetConsoleScreenBufferSize(GetStdout(),size)){
      debug(Error,"[resize_console]SetConsoleScreenBufferSize");
      return FALSE;
   }

   // taille fen�tre (identique taille buffer)
   rWindow.Right=size.X-1;
   rWindow.Bottom=size.Y-1;

   if(!SetConsoleWindowInfo(GetStdout(),TRUE, &rWindow )){
      debug(Error,"[resize_console]SetConsoleWindowInfo");
      return FALSE;
   }
   return TRUE;
}

/*********************************************************
resize_console_max fonction
Avoir une fen�tre console de la taille maximum. Cette taille d�pend
de la taille et de la police de caract�res s�lectionn�es par
l'utilisateurde la console.

La fonction retourne TRUE (1) en cas de r�ussite et FALSE (0) en cas
d'erreur
*/
BOOL resize_console_max()
{
COORD sizeMax;
   sizeMax = GetLargestConsoleWindowSize(GetStdout());
   return resize_console(sizeMax.X, sizeMax.Y);
}

/* ********************************************************
screen_w fonction
retourne la largeur maximum de la fen�tre compte tenu de la taille
du buffer.
*/
int screen_w()
{
CONSOLE_SCREEN_BUFFER_INFO info;
   GetConsoleScreenBufferInfo(GetStdout(),&info);
   return info.dwMaximumWindowSize.X;
}

/* ********************************************************
screen_h fonction
retourne la hauteur maximum de la fen�tre compte tenu de la taille
du buffer.
*/
int screen_h()
{
CONSOLE_SCREEN_BUFFER_INFO info;
   GetConsoleScreenBufferInfo(GetStdout(),&info);
   return info.dwMaximumWindowSize.Y;
}

/* ********************************************************
screen_size fonction
retourne une stucture COORD qui contient largeur et hauteur maximum
de la fen�tre.
*/
COORD screen_size()
{
CONSOLE_SCREEN_BUFFER_INFO info;
   GetConsoleScreenBufferInfo(GetStdout(),&info);
   return info.dwMaximumWindowSize;
}

/* ********************************************************
fill_console fonction
Remplit la fen�tre avec le caract�re et la couleur _fond et
face � la fois _sp�cifi�s.
*/
void fill_console(char asciiChar, int color)
{
CONSOLE_SCREEN_BUFFER_INFO info;
static CHAR_INFO*dat=NULL;
static int w=0;
static int h=0;
static SMALL_RECT bRect;
int x,y;

   if (!GetConsoleScreenBufferInfo(GetStdout(),&info)){
      debug(Error,"[fill_console]GetConsoleScreenBufferInfo");
      return;
   }

   // n'est refait qu'� chaque changement
   if (info.dwSize.X!=w || info.dwSize.Y!=h){
      w=info.dwSize.X;
      h=info.dwSize.Y;
      dat=(CHAR_INFO*)malloc(sizeof(CHAR_INFO)*w*h);

      bRect.Left = 0;
      bRect.Top = 0;
      bRect.Right = w-1;
      bRect.Bottom = h-1;
   }

   if ( color == 0 )
      memset(dat,0,sizeof(CHAR_INFO)*w*h);
   else{
      for (y=0; y<h; y++)
         for (x=0; x<w ; x++){
            dat[y*w+x].Attributes=color;
            dat[y*w+x].Char.AsciiChar = asciiChar;
            dat[y*w+x].Char.UnicodeChar = asciiChar;
         }
   }

   if (! WriteConsoleOutput(GetStdout(),// console active cible
                         dat,        // les datas src � afficher
                         coord(w,h),    // sa taille
                         coord(0,0),    // coin src d�part
                         &bRect) )      // rect de destination
      debug(Error,"[fill_console]WriteConsoleOutput");

}

/* ********************************************************
clear_console fonction
efface la console en noir
*/
void clear_console()
{
   fill_console(0,0);
}

#ifdef _VISUALCPP
/* ********************************************************
get_font_size fonction / r�serv� Visual C++
retourne la taille de la fontes courante
*/
COORD get_font_size()
{
CONSOLE_FONT_INFO font;
COORD size={0,0};

   if (!GetCurrentConsoleFont(GetStdout(),FALSE,&font))
      debug(Warming,"[get_font_size]error GetCurrentConsoleFont\n");
   else
      size=font.dwFontSize;

   return size;
}

/* ********************************************************
get_font_type fonction / r�serv� Visual C++
retourne le type de la fontes courante
*/
DWORD get_font_type()
{
CONSOLE_FONT_INFO font;
DWORD type; // unsigned long

   if (!GetCurrentConsoleFont(GetStdout(),FALSE,&font))
      debug(Warming,"[get_font_size]error GetCurrentConsoleFont\n");
   else
      type=font.nFont;

   return type;
}
#endif
/* ********************************************************
test_screen_console_info
Afficher les infos pour l'affichage �cran de la fenetre console
*/
void test_screen_console_info(int x,int y,int color)
{
CONSOLE_SCREEN_BUFFER_INFO info;

   gotoxy(x,y);
   set_color(color);
   printf("SCREEN BUFFER INFO :\n");
   if(!GetConsoleScreenBufferInfo(GetStdout(),&info))
      debug(Error,"[test_screen_console_info]GetConsoleScreenBufferInfo");
   else{
      gotoxy(x,wherey());
      printf("dwSize              : %d-%d    \n",info.dwSize.X,info.dwSize.Y);
      gotoxy(x,wherey());
      printf("dwCursorPosition    : %d-%d    \n",info.dwCursorPosition.X,
                                                 info.dwCursorPosition.Y);
      gotoxy(x,wherey());
      printf("wAttributes         : %d       \n",info.wAttributes);
      gotoxy(x,wherey());
      printf("srWindow            : t%d-L%d-R%d-B%d      \n",
                                                 info.srWindow.Top,
                                                 info.srWindow.Left,
                                                 info.srWindow.Right,
                                                 info.srWindow.Bottom);
      gotoxy(x,wherey());
      printf("dwMaximumWindowSize : %d-%d    \n",info.dwMaximumWindowSize.X,
                                                 info.dwMaximumWindowSize.Y);
   }

#ifdef _VISUALCPP
{
CONSOLE_FONT_INFO font;
   // fontes (pas possibilit� de modification)
   gotoxy(x,wherey());
   printf("FONT :\n");
   if (!GetCurrentConsoleFont(GetStdout(),FALSE,&font))
      debug(Warming,"[test_screen_console_info]error GetCurrentConsoleFont\n");
   else{
      gotoxy(x,wherey());
      printf("dwFontSize : %d, %d\n",  font.dwFontSize.X,font.dwFontSize.Y);
      gotoxy(x,wherey());
      printf("nFont : %d\n",font.nFont);
   }
}
#endif

}

/* ********************************************************
title_console fonction
Donne un titre � la fenetre console.
Le titre souhait� est pass� sous forme de chaine de caract�res
*/

// Version visual C++
#ifdef _VISUALCPP
void title_console(LPCTSTR title)
{
   SetConsoleTitle(title);
}
#else
// version mingw
void title_console(char*title)
{
TCHAR t[MAX_PATH];
      strcpy(t,TEXT(title));
      SetConsoleTitle(t);
}
#endif

/**********************************************************
*
*  COULEUR
*
**********************************************************/
/*
set_color fonction
donne ensemble couleur de fond et couleur de face (lettre)
*/
void set_color(int color)
{
   SetConsoleTextAttribute(GetStdout(),color);
}

/**********************************************************
set_bf_color fonction
donne distinctement une couleur pour le fond et une couleur
pour la face
*/
void set_bf_color(int backcolor, int forecolor)
{
   SetConsoleTextAttribute(GetStdout(),backcolor*16+forecolor);
}

/**********************************************************
get_back_color fonction
permet de r�cup�rer la couleur du fond active
*/
int get_back_color()
{
CONSOLE_SCREEN_BUFFER_INFO info;
   GetConsoleScreenBufferInfo(GetStdout(),&info);
   return info.wAttributes>>4;
}

/**********************************************************
get_fore_color fonction
permet de r�cup�rer la couleur du face active
*/
int get_fore_color()
{
CONSOLE_SCREEN_BUFFER_INFO info;
   GetConsoleScreenBufferInfo(GetStdout(),&info);
   return info.wAttributes & 15;
}

/**********************************************************
set_back_color fonction
active une couleur pour le fond
*/
void set_back_color(int color)
{
int fcolor = get_fore_color();
   SetConsoleTextAttribute(GetStdout(), (color<<4) + fcolor);
}

/**********************************************************
set_fore_Color fonction
active une couleur de face
*/
void set_fore_color(int color)
{
int bcolor = get_back_color();
   SetConsoleTextAttribute(GetStdout(), (bcolor<<4) + color);
}

/**********************************************************
*
*  CURSEUR
*
**********************************************************/
/*
gotoxy fonction
D�placer le curseur � une position dans la fen�tre console.
La fonction contr�le que l'on reste dans la fen�tre console.
*/
void gotoxy(int x, int y)
{
   if (x >= 0 && y >= 0 && x < screen_w() && y < screen_h())
      SetConsoleCursorPosition(GetStdout(),coord(x,y));
}

/**********************************************************
wherex fonction
retourne la position horizontale du curseur
*/
int wherex()
{
CONSOLE_SCREEN_BUFFER_INFO info;
   GetConsoleScreenBufferInfo(GetStdout(),&info);
   return info.dwCursorPosition.X;
}

/**********************************************************
wherey
retourne la position verticale du curseur
*/
int wherey()
{
CONSOLE_SCREEN_BUFFER_INFO info;
   GetConsoleScreenBufferInfo(GetStdout(),&info);
   return info.dwCursorPosition.Y;
}

/**********************************************************
show_cursor fonction
Montrer ou cacher le curseur selon que le param�tre visible
prend les valeurs 1 (TRUE) ou 0 (FALSE)
*/
void show_cursor(BOOL visible)
{
CONSOLE_CURSOR_INFO info;
   if (!GetConsoleCursorInfo(GetStdout(),&info))
      debug(Error,"[show_cursor]GetConsoleCursorInfo");
   else{
      info.bVisible=visible;
      SetConsoleCursorInfo(GetStdout(),&info);
   }
}

/**********************************************************
size_cursor fonction
permet de modifier la taille du curseur (entre 0 et 100).
le param�tre size correspond � un poucentage de recouvrement
de la cellule o� se trouve le curseur
*/
void size_cursor(unsigned int size)
{
CONSOLE_CURSOR_INFO info;
   if (!GetConsoleCursorInfo(GetStdout(),&info))
      debug(Error,"[size_cursor]GetConsoleCursorInfo");
   else{
      info.dwSize=size;
      SetConsoleCursorInfo(GetStdout(),&info);
   }
}

/**********************************************************
*
*  EVENTS
*
**********************************************************/
// inputs
static KEYBOARD_DATA _keyboardData = {{0}};
static MOUSE_EVENT_RECORD _mouseData = {{0}};
static int _mouseX = 0;  // pos horizontale
static int _mouseY = 0;  // verticale
static int _mouseB = 0;  // etat des clics (2 ou 3 boutons)
static int _mouseW = 0;   // valeur bouton weel

/**********************************************************
void poll_event() :
R�cup�ration des entr�es
*/
void poll_event()
{
DWORD nbEvents = 0;
DWORD readEvents = 0;
INPUT_RECORD* eventBuffer = NULL;
unsigned int i,key;

   GetNumberOfConsoleInputEvents(GetStdin(),&nbEvents);

   if (nbEvents==0)
      return;

   eventBuffer=(INPUT_RECORD*)malloc(nbEvents*sizeof(INPUT_RECORD));
   ReadConsoleInput(GetStdin(), eventBuffer, nbEvents, &readEvents);

   for (i=0; i < readEvents; i++){

      // CLAVIER
      if (eventBuffer[i].EventType == KEY_EVENT){

         //if(eventBuffer[i].Event.KeyEvent.wRepeatCount==1){
            _keyboardData.controlKeyState = eventBuffer[i].Event.KeyEvent.dwControlKeyState;
         key = eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
            _keyboardData.keyState[key] = eventBuffer[i].Event.KeyEvent.bKeyDown;
         //}
      }
      // SOURIS
      if (eventBuffer[i].EventType == MOUSE_EVENT){

         _mouseData = eventBuffer[i].Event.MouseEvent;
         // si mouvement
         if (eventBuffer[i].Event.MouseEvent.dwEventFlags == MOUSE_MOVED){//1
            _mouseX = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
            _mouseY = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
         }
         // si clic
         else if (eventBuffer[i].Event.MouseEvent.dwEventFlags == 0)//clic simple
            _mouseB = eventBuffer[i].Event.MouseEvent.dwButtonState;
         else if (eventBuffer[i].Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)//2
            ;
         // si wheel
         else if (eventBuffer[i].Event.MouseEvent.dwEventFlags == MOUSE_WHEELED){//4
            if (eventBuffer[i].Event.MouseEvent.dwButtonState & 0xFF000000)
               _mouseW++;
            else
               _mouseW--;
         }
      }
   }
   free(eventBuffer);
}

/**********************************************************
BOOL key_pressed(int keyCode) :
R�cup�ration de touches press�es
*/
BOOL key_pressed(int keyCode)
{
BOOL res;

   res = _keyboardData.keyState[keyCode];
   if (res)
      _keyboardData.keyState[keyCode]^=1;
   return res;

   //return _keyBoardData.keyState[keyCode];
}

/**********************************************************
COORD get_mouse_pos() :
R�cup�ration des positions h et v de la souris
*/
COORD get_mouse_pos()
{
   return _mouseData.dwMousePosition;
}

/**********************************************************
int mouse_x() :
R�cup�ration de la position v de la souris
*/
int mouse_x()
{
   return _mouseX;
}

/**********************************************************
int mouse_y() :
R�cup�ration de la position h de la souris
*/
int mouse_y()
{
   return _mouseY;
}

/**********************************************************
int mouse_w() :
R�cup�ration de la roulette de la souris
*/
int mouse_w()
{
   return _mouseW;
}

/**********************************************************
BOOL clic_pressed(int button) :
R�cup�ration des clics de la souris
*/
BOOL clic_pressed(int button)
{
int res=0;

   if ((_mouseB & button) == button){
      res=1;
      //_mouseB-=button;
   }
   return res;
}

/**********************************************************
*
*  CHBITMAP : char bitmap (chb)
*  buffer de donn�es pour affichage
*
**********************************************************/

/*
CHBITMAP* create_chb (int width, int height)
Allouer une CHBITMAP selon une largeur et une hauteur donn�es
en param�tre.
*/
CHBITMAP* create_chb (int width, int height)
{
CHBITMAP*b=NULL;
   if (width > 0 && height > 0){
      b=(CHBITMAP*)malloc(sizeof(CHBITMAP));
      b->w = width; //(width < 1) ? 1 : width;
      b->h = height; //(height < 1) ? 1 : height;
      b->dat = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)*b->w*b->h);
      // initialise� � 0 au d�part
     if (b->dat != NULL)
      memset(b->dat,0,sizeof(CHAR_INFO)*b->w*b->h);
     else{
      free(b);
      b=NULL;
     }
   }
   return b;
}

/* *********************************************************
CHBITMAP* free_chb(CHBITMAP*b)
Lib�rer la m�moire pr�c�dement allou�e pour une chbitmap
*/
CHBITMAP* free_chb(CHBITMAP*b)
{
   if (b!=NULL){
      free(b->dat);
      free(b);
      b=NULL;
   }
   return b;
}

/**********************************************************
void fill_part_chb(  CHBITMAP*b, int x,int y,int w,int h,
               int asciiChar, int color)
Remplit la chbitmap en entier ou une patie avec une lettre
et couleurs (lettre, fond) choisies
*/
void fill_part_chb(  CHBITMAP*b,    // la chbitmap
               int x,int y,   // position de d�part
               int w,int h,   // taille � partir de la
                           // position de d�part
               int asciiChar,  // lettre de remplissage
               int color)     // couleur de remplissage
{
int i,j;

   if(b != NULL){
      x = (x < 0) ? 0 : ((x > b->w) ? b->w : x);
      y = (y < 0) ? 0 : ((y > b->h) ? b->h : y);
      w = (x+w > b->w) ? b->w : x+w;
      h = (y+h > b->h) ? b->h : y+h;
      for(j=y; j < h; j++ )
         for (i=x; i < w; i++){
            b->dat[ j*b->w + i ].Char.AsciiChar=asciiChar;
            b->dat[ j*b->w + i ].Attributes=color;
         }
   }
   else
      debug(Warming,"[fill_part_chb]chbitmap non initialisee");
}

/**********************************************************
void fill_chb(CHBITMAP*b, int asciiChar, int color)
Remplit le buffer avec une lettre et une couleur
*/
void fill_chb (CHBITMAP*b, int asciiChar, int color)
{
      fill_part_chb(b, 0,0,b->w,b->h,asciiChar,color);
}

/**********************************************************
void clear_chb(CHBITMAP*b)
initialise � 0 une chbitmap
*/
void clear_chb(CHBITMAP*b)
{
   if (b)
      //fill_chbitmap(b,0,0);
      memset(b->dat,0,sizeof(CHAR_INFO)*b->w*b->h);
   else
      debug(Warming,"[clear_chbitmap]chbitmap non initialisee");
}

/**********************************************************
void copy_chb(CHBITMAP*src,CHBITMAP*dst,int srcX, int srcY,
               int dstX,int dstY, int w, int h )
Copie une chbitmap dans une autre enti�rement ou une partie.
*/
void copy_chb (   CHBITMAP*src,     // source
            CHBITMAP*dst,     // destination
            int srcX, int srcY,  // coin haut gauche source
            int dstX,int dstY,   // coin haut gauche destination
            int width, int height )    // taille copie � partir coin
                              // haut gauche source
{
int x,y,sx,sy;
   if (src != NULL && dst != NULL){

      for (y = dstY; y < dstY + height; y++)

         for (x = dstX; x < dstX + width; x++){

            if (x < 0 || x >= dst->w || y < 0 || y >= dst->h)
            continue;

            sy = y - dstY + srcY;
            sx = x - dstX + srcX;

            if (sx < 0 || sx >= src->w || sy < 0 || sy >= src->h)
            continue;

         dst->dat[ y * dst->w + x ] = src->dat[ sy * src->w + sx];

         }
   }
   else
      debug(Warming,"[copy_chbitmap]source ou destination non allouee");
}

/**********************************************************
void draw_chb(CHBITMAP*dst,CHBITMAP*src, int x, int y)
copie un buffer dans un autre � partir d'une position donn�e
*/
void draw_chb(CHBITMAP*dst,CHBITMAP*src, int x, int y)
{
   if (dst != NULL && src != NULL)
      copy_chb (src,dst,0,0,x,y,src->w,src->h);
   else
      debug(Warming,"[draw_buffer]chbitmap source ou destination non allouee");
}

/**********************************************************
void show_to_console(CHBITMAP*b)
Permet d'afficher une chbitmap dans la fen�tre console.
La fonction WriteConsoleOutput respecte le rect de la fen�tre
console et n'�crit pas en dehors.
*/
void show_to_console(CHBITMAP*b, int x, int y)
{
SMALL_RECT bRect;

   if ( b!=NULL  ){
      bRect.Left = x;
      bRect.Top = y;
      bRect.Right = x + b->w - 1;
      bRect.Bottom = y+ b->h - 1;

      if (! WriteConsoleOutput(GetStdout(),     // console active cible
                         b->dat,      // les datas src � afficher
                         coord(b->w,b->h),// sa taille
                         coord(0,0),     // coin src d�part
                         &bRect) )       // rect de destination
         debug(Error,"[show_to_console]erreur WriteConsoleOutput");
   }
   else
      debug(Warming,"[show_to_console] chbitmap non allouee");
 }

/**********************************************************
CHBITMAP* MemScreen()
Permet d'obtenir l'adresse de la chbitmap _screen. Cette chbitmap
correspond � l'espace de la fen�tre console accessible en �criture.
Elle sert de double buffer. Tous les affichages ont lieu d'abord
dans _screen et ensuite _screen est affich�e dans la fen�tre console.

*/

CHBITMAP* MemScreen()
{
static CHBITMAP*_screen = NULL;
COORD size;
   size = screen_size();
   if (_screen == NULL )
      _screen = create_chb(size.X,size.Y);
   else if (_screen->w != size.X || _screen->h != size.Y){
      _screen->w = size.X;
      _screen->h = size.Y;
      _screen->dat=(CHAR_INFO*)realloc(_screen->dat,sizeof(CHAR_INFO)*_screen->w*_screen->h);
   }
   return _screen;
}

/**********************************************************
void show_MemScreen()
Affiche la chbitmap _screen dans la fen�tre console
*/
void show_MemScreen()
{
   show_to_console(MemScreen(),0,0);
}

/**********************************************************
void clear_MemScreen()
Efface � 0 la chbitmap _screen sans toucher � la fen�tre
console
*/
void clear_MemScreen()
{
   clear_chb(MemScreen());
}

/**********************************************************
*
*   CHTEXT : op�rations de text en mode CHBITMAP
*
**********************************************************/
/* *********************************************************
void draw_char(CHBITMAP*b, int x, int y, int color, int asciiChar)
Affiche le caract�re sp�cifi� en asciiChar avec la couleur
color � la position x, y dans la CHBITMAP b
*/
void draw_char(CHBITMAP*b, int x, int y, int color, int asciiChar)
{
    // impossible si
    if (b==NULL || x<0 || x>=b->w || y<0 || y>=b->h)
        return;

    b->dat[b->w*y + x].Char.AsciiChar=asciiChar;
    b->dat[b->w*y + x].Attributes = color;
}
/**********************************************************
*/
