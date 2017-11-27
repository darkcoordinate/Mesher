all:
	gcc open2.c -lSDL2 -lGLESv2 -lm -std=c99 -o game.exe -g
