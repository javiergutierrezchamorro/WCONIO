# WCONIO.H
WCONIO is a Borlands's CONIO.H emulation for Watcom C/C++ and OpenWatcom C/C++. WCONIO is built over existing console/text functions in Watcom's graph.h, so it is simple and stable.

If you are already using Turbo/Borland CONIO.H in you DOS development, and want to go further than existing cputs and cprintf, such as supporting window, _setcursortype or textcolor... This is your choice.

WCONIO.H is compatible with DOS far data real-mode memory models (Compact, Large, Huge) as well as 32 bit protected mode (Flat). To use it, simply include "WCONIO.H" in your project/file.

Already compile executables ara available in the Builds directory (CONIO0.EXE for 8088+ Compact memory model and CONIO3.EXE for 386+ Flat protected mode binded to [PMODE/W](https://github.com/javiergutierrezchamorro/pmodew).

<img width="720" height="400" alt="WCONIO.H" src="https://github.com/user-attachments/assets/37a711fb-0bc9-44e0-a886-57d43cbffd7b" />



