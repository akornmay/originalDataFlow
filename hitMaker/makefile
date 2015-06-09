# define compile command

CC = g++

CFLAGS  = -g -Wno-deprecated
#CFLAGS  = -O3 -Wno-deprecated -funroll-loops 
LDFLAGS = -L/usr/local/lib
LDFLAGS+=-L/usr/lib

SRC 	= HitMaker.cpp FillMaker.cpp TreeMaker.cpp
OBJ 	= HitMaker.o FillMaker.o TreeMaker.o
HEAD    = HitMaker.h FillMaker.h TreeMaker.h

ROOTCFLAGS    =$(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      =$(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     =$(shell $(ROOTSYS)/bin/root-config --glibs) 

CFLAGS       += $(ROOTCFLAGS)

FillMaker: $(OBJ) makefile
	$(CC) $(OBJ) $(LDFLAGS) $(ROOTGLIBS) $(ROOTLIBS) -o FillMaker

%.o: %.cpp %.h global_constants.h
	$(CC) $(ROOTCFLAGS) $(CFLAGS) -c -o $@ $<

clean:	
	rm -f *.o FillMaker *~ FillMaker

