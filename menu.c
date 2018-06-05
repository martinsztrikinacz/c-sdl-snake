#include <stdio.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <time.h>
#include "global.h"
//#include <SDL_mixer.h>


void menu_rajzol(SDL_Surface *screen, int menupont)
{


    switch(menupont)
    {
        case 1://ez szerintem triviális, úgyhogy ide nem írok semmit :)
            stringRGBA(screen, SZELESSEG/2-50, MAGASSAG/2-20, "1 jatekos", 255, 0, 255, 255);
            stringRGBA(screen, SZELESSEG/2-50, MAGASSAG/2, "2 jatekos", 255, 255, 255, 255);
            stringRGBA(screen, SZELESSEG/2-50, MAGASSAG/2+20, "Pontok", 255, 255, 255, 255);
            break;
        case 2:
            stringRGBA(screen, SZELESSEG/2-50, MAGASSAG/2-20, "1 jatekos", 255, 255, 255, 255);
            stringRGBA(screen, SZELESSEG/2-50, MAGASSAG/2, "2 jatekos", 255, 0, 255, 255);
            stringRGBA(screen, SZELESSEG/2-50, MAGASSAG/2+20, "Pontok", 255, 255, 255, 255);
            break;

        case 3:
            stringRGBA(screen, SZELESSEG/2-50, MAGASSAG/2-20, "1 jatekos", 255, 255, 255, 255);
            stringRGBA(screen, SZELESSEG/2-50, MAGASSAG/2, "2 jatekos", 255, 255, 255, 255);
            stringRGBA(screen, SZELESSEG/2-50, MAGASSAG/2+20, "Pontok", 255, 0, 255, 255);
            break;

    }
}

int menu(SDL_Surface *screen)//a mainben létrehozott timert használva usereventeknél kirajzolja a menüt, a kiválasztott menüpontot más színnel
{
    SDL_Event event;
    int x, y, i;enum { MERETX=640, MERETY=640 };
    int r=1;
    int valtozoszin;
    int menupont=1;
    int quit = 0;
    boxRGBA(screen,0,0,SZELESSEG,MAGASSAG,0,0,0,255);
    /*Mix_Chunk *beep = NULL;
    Mix_Chunk *beep_ok = NULL;
    beep_ok = Mix_LoadWAV( "beep.wav" );//rosszul mentettem el...
    beep = Mix_LoadWAV( "beep_ok.wav" );
    if( ( beep == NULL ) || ( beep_ok == NULL ))
    {
        printf("hiba");
    }*/

    stringRGBA(screen, 0, 480-10, "Coded by Martin Molnar", 255, 0, 255, 255);
    SDL_Flip(screen);

    menu_rajzol(screen,menupont);
    while(!quit)
    {
		SDL_WaitEvent(&event);
		switch(event.type)
		{
           case SDL_USEREVENT:

                menu_rajzol(screen,menupont);
                SDL_Flip((screen));
                break;
		    case SDL_KEYDOWN:
                 switch (event.key.keysym.sym)
                 {
                    case SDLK_UP:
                        if(menupont!=1)
                            //Mix_PlayChannel(-1,beep,0);
                            menupont--;
                            menu_rajzol(screen,menupont);
                            SDL_Flip(screen);

                        break;
                    case SDLK_DOWN:
                        if(menupont!=3)
                            //Mix_PlayChannel(-1,beep,0);
                            menupont++;
                            menu_rajzol(screen,menupont);
                            SDL_Flip(screen);
                        break;
                    case SDLK_RETURN:
                        //Mix_PlayChannel(-1,beep_ok,0);
                        switch(menupont)//és akkor itt tér vissza a mainbe
                        {
                            case 1:
                                return 1;
                                break;
                            case 2:
                                return 2;
                                break;
                            case 3:
                                return 3;
                                break;
                        }
                        break;
                    default:
                        break;
                 }
                break;
            case SDL_QUIT:
                /*free(screen);
                SDL_Quit();*/
                return 0;
                /*quit=1;
                return 0;*/
                break;
		}
    }
}


