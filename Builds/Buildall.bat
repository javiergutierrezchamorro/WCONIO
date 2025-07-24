@ECHO OFF

:oc20
rem *** OPENWATCOM C++ 2.0 *** 
SET WATCOM=D:\FICHEROS\OC
SET OLDPATH=%PATH%
SET PATH=%WATCOM%\BINNT;%WATCOM%\BINW;%WATCOM%\BINP;%PATH%
SET EDPATH=%WATCOM%\EDDAT
SET INCLUDE=%WATCOM%\H;%WATCOM%\MFC\INCLUDE;%WATCOM%\H\NT;INCLUDE;
SET LIB=LIB;
rem *** Win32 ***
DEL wconio_ocw32.exe
rem WCL386 -w3 -oneatx -ohirbk -ol -ol+ -oi -ei -zp16 -6r  -fpi87 -fp6 -mf -s -ri -zm /bt=nt /l=nt /fhwe /"OPTION ELIMINATE" /"OPTION VFREMOVAL" ..\coniodemo.c ..\coniox.c
REN coniodemo.exe coniox_ocw32.exe
rem *** DOS16 ***
DEL wconio0.exe
WCL -w3 -oneatx -ohirbk -ol -ol+ -oi -ei -zp4 -0 -mc -s -ri -zm /bt=dos /l=dos /fhwe /"OPTION ELIMINATE" /"OPTION VFREMOVAL" ..\wconio.c
ren wconio.exe wconio0.exe

rem *** DOS32 ***
DEL wconio3.exe
rem WCL386 -w3 -oneatx -ohirbk -ol -ol+ -oi -ei -zp16 -6r -fpi87 -fp6 -mf -s -ri -zm /bt=dos /l=pmodew /fhwe /"OPTION ELIMINATE" /"OPTION VFREMOVAL" ..\wconio.c
ren wconio.exe wconio3.exe

SET WATCOM=
SET PATH=%OLDPATH%
SET EDPATH=
SET INCLUDE=
SET LIB=

:FIN
DEL *.obj
DEL *.pch
DEL *.tds
DEL *.bak
DEL *.err
DEL *.map
DEL *.sym