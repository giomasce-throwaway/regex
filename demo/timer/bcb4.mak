
# very basic makefile for timer.exe
#
# Borland C++ tools
#
# BCROOT defines the root directory of your bc builder install
#

!ifndef BCROOT
BCROOT=$(MAKEDIR)\..
!endif

BCC32   = $(BCROOT)\bin\Bcc32.exe 

IDE_LinkFLAGS32 =  -L$(BCROOT)\LIB
COMPOPTS= -O2 -tWC -tWM- -D_NO_VCL; -I../../../../; -L..\..\lib\bcb4


timer.exe : regex_timer.cpp
  $(BCC32) @&&|
 $(COMPOPTS) -e$@ regex_timer.cpp
|






















