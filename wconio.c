#include "wconio.h"


void main (void)
{
	unsigned int i;
	_setcursortype(_NOCURSOR);

	window(10, 5, 70, 20);
	textbackground(BLUE);
	clrscr();

	textattr(16 * CYAN + BLACK);
	cputs("           WCONIO: CONIO.H emulation for Watcom C                ");
	window(10, 6, 70, 20);
	textattr(16 * BLUE + WHITE);
	
	for (i = 0; i < 1000; i++)
	{
		cputs("WCONIO: CONIO.H emulation for Watcom C ");
	}
	
	
	textcolor(YELLOW);
	gotoxy(1, 20);
	cputs("-- Press any key --");
	
	
	getch();
	gotoxy(1, 20);
	delline();
	getch();
	
	_setcursortype(_NORMALCURSOR);
}
