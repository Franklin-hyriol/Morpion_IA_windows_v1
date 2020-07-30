#ifndef CREACO_H_INCLUDED
#define CREACO_H_INCLUDED

#define _WIN32_WINNT 0x0501
#define _WIN32_WINDOWS 0x600

// pour compiler des fonctions qui marchent sous VC
// mais qui ne marchent pas sous mingw (fontes)
//#define _VISUALCPP

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

//
typedef enum
{
   Info,
   Warming,
   Error,
   Fatal
}ErrLevel;

// scan clavier
typedef struct
{
   BOOL keyState[256];
   int controlKeyState;
}KEYBOARD_DATA;

// CHBITMAP (matrice de lettres)
typedef struct
{
   int h;         // height, hauteur
   int w;         // width, largeur
   CHAR_INFO*dat; // Les données
}CHBITMAP;

#ifdef __cplusplus
extern "C"{
#endif

/********************************************************
creaco_staff_lib.c
********************************************************/
// Constructeurs
COORD    coord					(int x, int y);

// librairie
HANDLE	 GetStdout				(void);
HANDLE	 GetStdin				(void);
HANDLE	 GetConsoleW			(void);
void	 debug					(int errLevel,char*msg);

/********************************************************
creaco_console.c
********************************************************/
BOOL	resize_console			(int width, int height);
BOOL	resize_console_max		(void);
int		screen_w				(void);
int		screen_h				(void);
COORD	screen_size				(void);
void	fill_console			(char asciiChar, int color);
void	clear_console			(void);
void	test_screen_console_info(int x,int y,int color);

#ifdef _VISUALCPP
COORD	get_font_size			(void);
DWORD	get_font_type			(void);
void	title_console			(LPCTSTR title);
#else
void	title_console			(char*title);
#endif

/********************************************************
creaco_couleur.c
********************************************************/
void	set_color				(int color);
void	set_bf_color			(int backcolor, int forecolor);
int		get_back_color			(void);
int		get_fore_color			(void);
void	set_back_color			(int color);
void	set_fore_color			(int color);

/********************************************************
creaco_curseur.c
********************************************************/
void	gotoxy					(int x, int y);
int		wherex					(void);
int		wherey					(void);
void	show_cursor				(BOOL visible);
void	size_cursor				(unsigned int size);

/********************************************************
creaco_events.c
********************************************************/
void    poll_event				(void);
BOOL    key_pressed				(int keyCode);
COORD   get_mouse_pos			(void);
int		mouse_x					(void);
int		mouse_y					(void);
int		mouse_w					(void);
BOOL    clic_pressed			(int button);

/********************************************************
creaco_CHBITMAP.c
********************************************************/
CHBITMAP*	create_chb			(int width,int height);
CHBITMAP*	free_chb			(CHBITMAP*b);
void		fill_part_chb		(CHBITMAP*b,int x,int y,int w,int h,
								 int asciiChar, int color);
void		fill_chb			(CHBITMAP*b, int asciiChar, int color);
void		clear_chb			(CHBITMAP*b);
void		copy_chb			(CHBITMAP*src,CHBITMAP*dst,int srcX, int srcY,
								 int dstX,int dstY, int w, int h );
void		draw_chb			(CHBITMAP*dst,CHBITMAP*src, int x, int y);
void		show_to_console		(CHBITMAP*b,int x, int y);
CHBITMAP*	MemScreen			(void);
void		show_MemScreen		(void);
void		clear_MemScreen		(void);

/********************************************************
creaco_text.c
********************************************************/
void draw_char(CHBITMAP*b, int x, int y, int color, int asciiChar);

/********************************************************
********************************************************/
#if __cplusplus
}
#endif

#endif // CREACO_H_INCLUDED
