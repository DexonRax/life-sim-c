all:
	gcc src/main.c src/humans.c src/player.c -Iinclude -o main.exe -lm -lraylib -lopengl32 -lgdi32 -O3 -lwinmm
