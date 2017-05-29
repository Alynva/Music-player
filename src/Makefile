# Project: Music-player

# Compilador
CPP				= g++
# Versão do compilador
CXX_VERSION		= -std=c++0x
# Flags do compilador
CC_FLAGS		= -g -Wall
# Linkers do compilador
CC_LINKERS		= 
ifeq ($(OS),Windows_NT)
	CC_LINKERS	+= -lmingw32 -L../bin -L../lib
endif
CC_LINKERS		+= -lSDL2 -lSDL2_mixer -lSDL2main

# Arquivo principal
MAIN_FILE		= main.cpp
# Arquivo auxiliares
AUX_FILES		= 

# Includes
INCS			= -I"../include"

#Arquivo de saída
ifeq ($(OS),Windows_NT)
	OUT_FILE	= ../bin/Music-player.exe
else
	OUT_FILE	= ../bin/freecell.out
endif

# Flags do clean
RM				= rm -f

# SDL flags
SDL_FLAGS		= `sdl-config --cflags`

# Argumentos do run
ARGS			=

.PHONY: all main-build clean run

all: main-build run

clean:
	${RM} $(OUT_FILE)

main-build:
	$(CPP) $(CXX_VERSION) $(MAIN_FILE) $(AUX_FILES) $(CC_FLAGS) $(INCS) $(CC_LINKERS) -o $(OUT_FILE)

main.o: main.cpp
	$(CPP) -c -o main.o

run:
	$(OUT_FILE) $(ARGS)