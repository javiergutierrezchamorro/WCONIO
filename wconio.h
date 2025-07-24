#pragma once
#ifndef _WCONIO_H_
#define _WCONIO_H_

#include <i86.h>
#include <graph.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif


#define outportb		outp
#define outport			outpw
#define outportd		outpd
#define inportb			inp
#define inport			inpw
#define inportd			inpd

#define peekb(s,o)			(*((unsigned char coniox_far *) MK_FP((s),(o))))
#define peekw(s,o)			(*((unsigned short coniox_far *) MK_FP((s),(o))))
#define peekl(s,o)			(*((unsigned long coniox_far *) MK_FP((s),(o))))
#define pokeb(s,o,x)		(*((unsigned char coniox_far *) MK_FP((s),(o))) = (unsigned char)(x))
#define pokew(s,o,x)		(*((unsigned short coniox_far *) MK_FP((s),(o))) = (unsigned short)(x))
#define pokel(s,o,x)		(*((unsigned long coniox_far *) MK_FP((s),(o))) = (unsigned long)(x))


#pragma pack(push)
#pragma pack(1)

/**
Structure holding information about screen.
@see gettextinfo
*/
struct text_info
{
	unsigned short winleft;
	unsigned short wintop;
	unsigned short winright;
	unsigned short winbottom;
	unsigned short attribute;		/**< current text attribute */
	unsigned short normattr;		/**< original value of text attribute after start of the application. If you don't called the <TT>inittextinfo</TT> on the beginning of the application, this always will be black background and light gray foreground */
	unsigned short currmode;
	unsigned short screenheight;	/**< screen width */
	unsigned short screenwidth;		/**< screen height */
	short curx;						/**< cursor coordinate x */
	short cury;						/**< cursor coordinate y */
} __ti = {1, 1, 80, 25, 7, 7, 3, 80, 25, 1, 1};

/**
Colors which you can use in your application.
*/
#if !defined(__COLORS)
#define __COLORS
	typedef enum _COLORS
	{
		BLACK,			/**< black color */
		BLUE,			/**< blue color */
		GREEN,			/**< green color */
		CYAN,			/**< cyan color */
		RED,			/**< red color */
		MAGENTA,		/**< magenta color */
		BROWN,			/**< brown color */
		LIGHTGRAY,		/**< light gray color */
		DARKGRAY,		/**< dark gray color */
		LIGHTBLUE,		/**< light blue color */
		LIGHTGREEN,		/**< light green color */
		LIGHTCYAN,		/**< light cyan color */
		LIGHTRED,		/**< light red color */
		LIGHTMAGENTA,	/**< light magenta color */
		YELLOW,			/**< yellow color */
		WHITE			/**< white color */
	} COLORS;
#endif

#define BLINK			128 
#define PASS_MAX		8
#define PRINTFBUF_SIZE	255


enum text_modes
{
	/* DOS-compatible modes */
	EXITMODE = -2,
	LASTMODE = -1,
	BW40 = 0,
	C40 = 1,
	BW80,
	C80,
	MONO = 7,
	_ORIGMODE = 65      /* original mode at program startup */
};


/**
@anchor cursortypes
@name Cursor types
Predefined cursor types. */
/*@{*/
#define _NOCURSOR		0			/**< no cursor */
#define _SOLIDCURSOR	1			/**< cursor filling whole cell */
#define _NORMALCURSOR	2			/**< cursor filling 20 percent of cell height */
/*@}*/



/**
Controls de video output.
directvideo controls where your program's console output goes:
0: Goes via ROM calls.
1: (Default) Goes directly to video RAM
*/
#define directvideo 1
#define _directvideo directvideo

/**
Enables or disables scrolling in console I/O functions.
_wscroll is a console I/O flag. You can use it to draw along the edges of a window without having the screen scroll.
*/
#define _wrapon _wscroll


/**
Gets text mode video information.
gettextinfo fills in the text_info structure pointed to by r with the current text video information.
@see text_info
*/
void gettextinfo(struct text_info *__r);


/**
Clears to end of line in text window.
clreol clears all characters from the cursor position to the end of the line within the current text window, without moving the cursor.
*/
void clreol(void);


/**
Clears the text-mode window.
clrscr clears the current text window and places the cursor in the upper 
left corner (at position 1,1). 

*/
void clrscr(void);


/**
Deletes line in text window.
delline deletes the line containing the cursor and moves all lines below it one line up. delline operates within the currently active text window.
*/
void delline(void);


/**
Inserts a blank line in the text window.
insline inserts an empty line in the text window at the cursor position using the current text background color. All lines below the empty one move down one line, and the bottom line scrolls off the bottom of the window.
*/
void insline(void);


/**
Copies text from text mode screen to memory.
gettext stores the contents of an onscreen text rectangle defined by left, top, right, and bottom into the area of memory pointed to by destin.
All coordinates are absolute screen coordinates not window-relative. The upper left corner is (1,1). gettext reads the contents of the rectangle into memory sequentially from left to right and top to bottom.
Each position onscreen takes 2 bytes of memory: The first byte is the character in the cell and the second is the cell's video attribute. The space required for a rectangle w columns wide by h rows high is defined as bytes = (h rows) x (w columns) x 2
@see char_info
@see puttext
@param left Left coordinate of the rectangle, inclusive, starting from 1.
@param top Top coordinate of the rectangle, inclusive, starting from 1.
@param right Right coordinate of the rectangle, inclusive, starting from 1.
@param bottom Bottom coordinate of the rectangle, inclusive, starting from 1.
@param buf You have to pass buffer of size <TT>(right - left + 1) * (bottom - top + 1) * sizeof(char_info)</TT>.
*/
int gettext(int __left, int __top, int __right, int __bottom, void *__destin);


/**
Copies text from memory to the text mode screen.
puttext writes the contents of the memory area pointed to by source out to the onscreen rectangle defined by left, top, right, and bottom.
All coordinates are absolute screen coordinates, not window-relative. The upper left corner is (1,1).
puttext places the contents of a memory area into the defined rectangle sequentially from left to right and top to bottom.
Each position onscreen takes 2 bytes of memory: The first byte is the 	character in the cell, and the second is the cell's video attribute. The space required for a rectangle w columns wide by h rows high is defined as	bytes = (h rows) x (w columns) x 2
puttext is a text mode function performing direct video output.
@see char_info
@see _conio_gettext
@param left Left coordinate of the rectangle, inclusive, starting from 1.
@param top Top coordinate of the rectangle, inclusive, starting from 1.
@param right Right coordinate of the rectangle, inclusive, starting from 1.
@param bottom Bottom coordinate of the rectangle, inclusive, starting from 1.
@param buf You have to pass buffer of size <TT>(right - left + 1) * (bottom - top + 1) * sizeof(char_info)</TT>.
*/
int puttext(int __left, int __top, int __right, int __bottom, void *__source);


/**
Copies text onscreen from one rectangle to another.
movetext copies the contents of the onscreen rectangle defined by left, top, right, and bottom to a new rectangle of the same dimensions. The new rectangle's upper left corner is position (destleft, desttop).
All coordinates are absolute screen coordinates. Rectangles that overlap are moved correctly.
movetext is a text mode function performing direct video output.
@param left Left coordinate of the rectangle, inclusive, starting from 1.
@param top Top coordinate of the rectangle, inclusive, starting from 1.
@param right Right coordinate of the rectangle, inclusive, starting from 1.
@param bottom Bottom coordinate of the rectangle, inclusive, starting from 1.
@param destleft Left coordinate of the destination rectangle.
@param desttop Top coordinate of the destination rectangle.
*/
int movetext(int __left, int __top, int __right, int __bottom, int __destleft, int __desttop);


/**
Positions cursor in text window.
gotoxy moves the cursor to the given position in the current text window. If the coordinates are in any way invalid the call to gotoxy is ignored. 
An example of this is a call to 40,30) when (35,25) is the bottom right position in the window. Neither argument to gotoxy can be zero.
@param x horizontal position
@param y vertical position
*/
void gotoxy(int __x, int __y);


/**
Selects cursor appearance.
Sets the cursor type to
_NOCURSOR: Turns off the cursor
_NORMALCURSOR: Normal underscore cursor
_SOLIDCURSOR: Solid block cursor
@see @ref cursortypes
@param type cursor type, under Win32 it is height of the cursor in percents
*/
void _setcursortype(int __cur_t);


/**
Sets text attributes.
textattr lets you set both the foreground and background colors in a single call. (Normally, you set the attributes with textcolor and textbackground.)
This function does not affect any characters currently onscreen; it affects only those characters displayed by functions (such as cprintf) performing text mode, direct video output after this function is called.
@param _attr new text attribute
*/
void textattr(int __newattr);


/**
Selects normal-intensity characters.
normvideo selects normal characters by returning the text attribute (foreground and background) to the value it had when the program started.
This function does not affect any characters currently on the screen, only those displayed by functions (such as cprintf) performing direct console output functions after normvideo is called.
@see text_info
*/
void normvideo(void);


/**
Selects high-intensity characters.
highvideo selects high-intensity characters by setting the high-intensity bit of the currently selected foreground color.
This function does not affect any characters currently onscreen, but does affect those displayed by functions (such as cprintf) that perform direct video, text mode output after highvideo is called.
@see COLORS
@see lowvideo
*/
void highvideo(void);


/**
Selects low-intensity characters.
lowvideo selects low-intensity characters by clearing the high-intensity bit of the currently selected foreground color.
This function does not affect any characters currently onscreen. It affects only those characters displayed by functions that perform text mode, direct console output after this function is called.
@see COLORS
@see highvideo
*/
void lowvideo (void);


/**
Selects new text background color.
textbackground selects the background color. This function works for functions that produce output in text mode directly to the screen. 
newcolor selects the new background color. You can set newcolor to an integer from 0 to 7, or to one of the symbolic constants defined in conio.h. If you use symbolic constants, you must include conio.h.
Once you have called textbackground, all subsequent functions using direct video output (such as cprintf) will use newcolor. textbackground does not affect any characters currently onscreen.
@see COLORS
@param color new background color
*/
void textbackground(int __newcolor);


/**
Selects new character color in text mode.
textcolor selects the foreground character color. This function works for the console output functions. newcolor selects the new foreground color.
You can set newcolor to an integer as given in the table below, or to one of the symbolic constants defined in conio.h. If you use symbolic constants, you must include conio.h.
Once you have called textcolor, all subsequent functions using direct video output (such as cprintf) will use newcolor. textcolor does not affect any characters currently onscreen.
@see COLORS
@param color new foreground color
*/
void textcolor(int __newcolor);


/**
Puts screen in text mode.
*/
void textmode(int __newmode);


/**
Defines active text mode window.
window defines a text window onscreen. If the coordinates are in any way invalid, the call to window is ignored.
left and top are the screen coordinates of the upper left corner of the window.right and bottom are the screen coordinates of the lower right corner.
The minimum size of the text window is one column by one line. The default window is full screen, with the coordinates: 1,1,C,R
where C is the number of columns in the current video mode, and R is the number of rows.
*/
void window(int __left, int __top, int __right, int __bottom);


/**
Scans and formats input from the console.
cscanf scans a series of input fields one character at a time, reading directly from the console. Then each field is formatted according to a format specifier passed to cscanf in the format string pointed to by format.
Finally, cscanf stores the formatted input at an address passed to it as an argument following format, and echoes the input directly to the screen.
There must be the same number of format specifiers and addresses as there are input fields.
Note: For details on format specifiers, see scanf Format Specifiers.
cscanf might stop scanning a particular field before it reaches the normal end-of-field (whitespace) character, or it might terminate entirely for a number of reasons. See scanf for a discussion of possible causes.
*/
int cscanf(const char *__format, ...);


/**
Reads a string from the console.
cgets reads a string of characters from the console, storing the string (and the string length) in the location pointed to by str.
cgets reads characters until it encounters a carriage-return/linefeed (CR/LF) combination, or until the maximum allowable number of characters have been read. If cgets reads a CR/LF combination, it replaces the combination with a \0 (null terminator) before storing the string.
Before cgets is called, set str[0] to the maximum length of the string to be read. On return, str[1] is set to the number of characters actually read. The characters read start at str[2] and end with a null terminator. 
Thus, str must be at least str[0] plus 2 bytes long.
*/
char *cgets(char *__str);


/**
Writes formatted output to the screen.
cprintf accepts a series of arguments, applies to each a format specifier contained in the format string pointed to by format, and outputs the formatted data directly to the current text window on the screen. There must be the same number of format specifiers as arguments. For details details on format specifiers, see printf Format Specifiers.
The string is written either directly to screen memory or by way of a BIOS call, depending on the value of the global variable _directvideo.
Unlike fprintf and printf, cprintf does not translate linefeed characters (\n) into carriage-return/linefeed character pairs (\r\n). Tab characters (specified by \t) are not expanded into spaces.
*/
int cprintf(const char *__format, ...);


/**
Writes a string to the screen.
cputs writes the null-terminated string str to the current text window. It does not append a newline character.
The string is written either directly to screen memory or by way of a BIOS call, depending on the value of the global variable _directvideo.
Unlike puts, cputs does not translate linefeed characters (\n) into carriage-return/linefeed character pairs (\r\n).
*/
int cputs(const char *__str);


/**
Reads a password.
getpass reads a password from the system console after prompting with the null-terminated string prompt and disabling the echo. A pointer is returned to a null-terminated string of up to eight characters (not counting the null-terminator).
@see cgets
@param prompt prompt which will be displayed to user
@param str string for the password. <TT>str[0]</TT> have to contain
length of the <TT>str</TT> - 3
@returns <TT>&str[2]</TT>, the password will be stored in <TT>str</TT>
beginning at <TT>str[2]</TT>, in <TT>str[1]</TT> will be length of the
string without <TT>\\0</TT>, at <TT>str[2 + str[1]]</TT> will be \\0.
*/
char *getpass(const char *__prompt);


/**
Gets character from keyboard, does not echo to screen.
getch reads a single character directly from the keyboard, without echoing to the screen.
*/
int getch(void);


/**
Gets character from the keyboard, echoes to screen.
getche reads a single character from the keyboard and echoes it to the current text window using direct video or BIOS.
*/
int getche(void);


/**
Checks for currently available keystrokes.
kbhit checks to see if a keystroke is currently available. Any available keystrokes can be retrieved with getch or getche.
*/
int kbhit(void);


/**
Outputs character to screen.
putch outputs the character c to the current text window. It is a text mode 
function performing direct video output to the console. putch does not 
translate linefeed characters (\n) into carriage-return/linefeed pairs.
The string is written either directly to screen memory or by way of a BIOS 
call, depending on the value of the global variable _directvideo.
*/
int putch(int __c);



/**
Pushes a character back to the keyboard buffer.
ungetch pushes the character ch back to the console, causing ch to be the next character read. The ungetch function fails if it is called more than once before the next read.
*/
int ungetch(int __ch);


/**
Gives horizontal cursor position within window.
wherex returns the x-coordinate of the current cursor position (within the current text window).
@returns cursor X position
*/
int wherex(void);


/**
Gives vertical cursor position within window.
wherey returns the y-coordinate of the current cursor position (within the current text window).
@returns cursor Y position
*/
int wherey(void);



/**
Pauses program execution for a given time.
@param ms miliseconds
*/
void delay(unsigned int ms);

#define _cgets		cgets
#define _cprintf	cprintf
#define _cputs		cputs
#define _cscanf		cscanf
#define _getch		getch

#define gettextsize(__left, __top, __right, __bottom)	(((__right) - (__left) + 1) * ((__bottom) - (__top) + 1) * 2)

#define KEY_SPECIAL     0x100
#define KEY_HOME        71
#define KEY_UP          72
#define KEY_PGUP        73
#define KEY_LEFT        75
#define KEY_CENTER      76
#define KEY_RIGHT       77
#define KEY_END         79
#define KEY_DOWN        80
#define KEY_PGDN        81
#define KEY_INSERT      82
#define KEY_DELETE      83
#define KEY_F1          59
#define KEY_F2          60
#define KEY_F3          61
#define KEY_F4          62
#define KEY_F5          63
#define KEY_F6          64
#define KEY_F7          65
#define KEY_F8          66
#define KEY_F9          67
#define KEY_F10         68
#define KEY_ESC 27
#define MOUSE_CLICK     0x200
#define MOUSE_DBLCLICK  0x201
#define MOUSE_WHEELUP   0x202
#define MOUSE_WHEELDOWN 0x203
#define WINDOW_RESIZE   0x204



#pragma pack(pop)


/* ----------------------------------------------------------------------------------------------------------------- */
void gettextinfo(struct text_info *__r)
{
	struct rccoord cur;

	_gettextwindow((short *) __ti.wintop, (short *) &__ti.winleft, (short *) &__ti.winbottom, (short *) &__ti.winright);
	__ti.attribute = (_getbkcolor() << 4) | _gettextcolor();
	cur = _gettextposition();
	__ti.curx = cur.col;
	__ti.cury = cur.row;
	
	memcpy(&__r, &__ti, sizeof(struct text_info));
	//_gettextcursor
}


/* ----------------------------------------------------------------------------------------------------------------- */
void clreol(void)
{
	unsigned int l;
	char s[PRINTFBUF_SIZE];
	struct rccoord cur;

	l = __ti.winright - __ti.winleft + 2 - cur.col;
	s[l+1] = 0;
	cur = _gettextposition();
	memset(s, ' ', l);
	cputs(s);
	gotoxy(cur.col, cur.row);
}


/* ----------------------------------------------------------------------------------------------------------------- */
void clrscr(void)
{
	_clearscreen(_GWINDOW);
}



/* ----------------------------------------------------------------------------------------------------------------- */
void delline(void)
{
	_scrolltextwindow(_GSCROLLUP);
}


/* ----------------------------------------------------------------------------------------------------------------- */
void insline(void)
{
	//ToDo
}



/* ----------------------------------------------------------------------------------------------------------------- */
int gettext(int __left, int __top, int __right, int __bottom, void* __destin)
{
	//ToDo
	return(0);
}


/* ----------------------------------------------------------------------------------------------------------------- */
int puttext(int __left, int __top, int __right, int __bottom, void *__source)
{
	//ToDo
	return(0);
}


/* ----------------------------------------------------------------------------------------------------------------- */
int movetext(int __left, int __top, int __right, int __bottom, int __destleft, int __desttop)
{
	//ToDo
	return(0);
}


/* ----------------------------------------------------------------------------------------------------------------- */
void gotoxy(int __x, int __y)
{
	_settextposition((short) __y, (short) __x);
}


/* ----------------------------------------------------------------------------------------------------------------- */
void _setcursortype(int __cur_t)
{
	short cursor;
	
	switch (__cur_t)
	{
		case _NOCURSOR:
			cursor = 0x2000;
			break;
		case _SOLIDCURSOR:
			cursor = 0x0007;
			break;
		case _NORMALCURSOR:
		default:
			cursor = 0x0607;
	}
	_settextcursor(cursor);
}


/* ----------------------------------------------------------------------------------------------------------------- */
void textattr(int __newattr)
{
	_settextcolor((short) __newattr & 0xF);
	_setbkcolor((short) ((__newattr >> 4) & 0xF));
}


/* ----------------------------------------------------------------------------------------------------------------- */
void highvideo(void)
{
	short c;
	
	c = _gettextcolor();
	_settextcolor(c & 0xF);
}


/* ----------------------------------------------------------------------------------------------------------------- */
void lowvideo(void)
{
	short c;
	
	c = _gettextcolor();
	_settextcolor(c & ~0x08);
}



/* ----------------------------------------------------------------------------------------------------------------- */
void normvideo(void)
{
	_settextcolor(__ti.normattr & 0xF);
}



/* ----------------------------------------------------------------------------------------------------------------- */
void textbackground(int __newcolor)
{
	_setbkcolor((short) __newcolor);
}


/* ----------------------------------------------------------------------------------------------------------------- */
void textcolor(int __newcolor)
{
	_settextcolor((short) __newcolor);
}


/* ----------------------------------------------------------------------------------------------------------------- */
void textmode(int __newmode)
{
	if (__newmode == LASTMODE)
	{
		__newmode = __ti.currmode;
	}
	if (__newmode != __ti.currmode)
	{
		switch (__newmode)
		{
			case BW40:
			case C40:
				__ti.screenwidth = 40;
				__ti.screenheight = 25;
				break;
			case BW80:
			case C80:
			case _ORIGMODE:
			case MONO:
			default:
				__ti.screenwidth = 80;
				__ti.screenheight = 25;
		}
		_setvideomode((short) __newmode);
	}
	window(1, 1, __ti.screenwidth, __ti.screenheight);
	textattr(__ti.normattr);
	clrscr();
	_setcursortype(_NORMALCURSOR);
}


/* ----------------------------------------------------------------------------------------------------------------- */
void window(int __left, int __top, int __right, int __bottom)
{
	_settextwindow((short) __top, (short) __left, (short) __bottom, (short) __right);
}



/* ----------------------------------------------------------------------------------------------------------------- */
//int cscanf(const char *__format, ...);



/* ----------------------------------------------------------------------------------------------------------------- */
//char *cgets(char *__str);


#undef cprintf
/* ----------------------------------------------------------------------------------------------------------------- */
int cprintf (const char *__format, ...)
{
	int r;
	va_list ap;
	char buffer[PRINTFBUF_SIZE];

	va_start(ap, __format);
	r = vsprintf(buffer, __format, ap);
	va_end(ap);
	cputs(buffer);
	return(r);
}


#undef cputs
/* ----------------------------------------------------------------------------------------------------------------- */
int cputs(const char *__str)
{
	_outtext((char *) __str);
	return(strlen(__str));	
}



/* ----------------------------------------------------------------------------------------------------------------- */
char *getpass(const char *__prompt)
{
	//ToDo
	return(NULL);
}



/* ----------------------------------------------------------------------------------------------------------------- */
//int getch(void);
//Already available in Watcom


/* ----------------------------------------------------------------------------------------------------------------- */
//int getche(void);
//Already available but not honoring windows


/* ----------------------------------------------------------------------------------------------------------------- */
//int kbhit(void);
//Already available in Watcom


/* ----------------------------------------------------------------------------------------------------------------- */
//int putch(int __c);
//Already available but not honoring windows


/* ----------------------------------------------------------------------------------------------------------------- */
//int ungetch(int __ch);


/* ----------------------------------------------------------------------------------------------------------------- */
int wherex(void)
{
	struct rccoord cur;

	cur = _gettextposition();
	return((int) cur.col);
}


/* ----------------------------------------------------------------------------------------------------------------- */
int wherey(void)
{
	struct rccoord cur;

	cur = _gettextposition();
	return((int) cur.row);
}


/* ----------------------------------------------------------------------------------------------------------------- */
//void delay(unsigned int ms)

















#ifdef __cplusplus
}
#endif

#endif /* _WONIO_H_ */

