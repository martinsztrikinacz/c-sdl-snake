Ubuntu 16.04:

sudo apt-get install libsdl1.2-dev libsdl-gfx1.2-dev libsdl-image1.2-dev libsdl-ttf2.0-dev libsdl-mixer1.2-dev && gcc main.c foglal.c egyeb.c menu.c rajzol.c `sdl-config --cflags --libs` -lSDL_gfx -lSDL_ttf -lSDL_image -lSDL_mixer && ./a.out
