#include <stdio.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include "global.h"
//#include <dos.h>
#include <SDL_ttf.h>
//#include <SDL2/SDL.h>

int rand_szam_RGB(void)//:)
{
    return rand()%255;
}

int pont_rajzol(SDL_Surface *screen)//tulajdonk�ppen ez az infoc-s p�ldaprogram + k�korszaki f�jlbeolvas�s
{
    boxRGBA(screen,0,0,SZELESSEG,MAGASSAG,255, 0, 255, 255);
    filledCircleRGBA(screen,SZELESSEG/2,MAGASSAG/2,300,0,80,20,255);
    SDL_Flip(screen);
    int quit=0;
    SDL_Event event;
    FILE *file = fopen("pontok.txt", "r");
    int szamok[5];//5 pont van eltarolva maximum

    int i=0;
    int num;
    while(fscanf(file, "%d", &num) != -1)
    {
        szamok[i] = num;
        i++;
    }
    fclose(file);

    SDL_Color kek = {0, 255, 255}, zold = {0, 80, 20};
    SDL_Rect hova = { 0, 0, 0, 0 };
    TTF_Font *font;
    SDL_Surface *felirat;


    TTF_Init();
    font = TTF_OpenFont("Minecrafter_3.ttf", 20);
    if (!font) {
        fprintf(stderr, "Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(2);
    }



    hova.y = MAGASSAG/3;
    hova.x = SZELESSEG/2-80;

    felirat = TTF_RenderUTF8_Shaded(font, "RANGLISTA:", kek, zold);
    SDL_BlitSurface(felirat, NULL, screen, &hova);
    SDL_FreeSurface(felirat);

    hova.y += 30;

    for(i=0;i<5;i++)
    {

        char c[20];
        sprintf(c, "%d", szamok[i]);

        felirat = TTF_RenderUTF8_Shaded(font, c, kek, zold);
        SDL_BlitSurface(felirat, NULL, screen, &hova);
        SDL_FreeSurface(felirat);
        hova.y += 30;
    }

    TTF_CloseFont(font);
    SDL_Flip(screen);
    while(!quit)
    {
		SDL_WaitEvent(&event);
		switch(event.type)
		{
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        return 0;
                        break;
                    default: break;
                }
                break;
            case SDL_QUIT: return 0; break;
		}
    }
    return 1;
}

void eger_rajzol(SDL_Surface *screen, eger *e,egyseg *eleje)
{
    eger_inicializal(e,eleje);
    boxRGBA(screen,e->x,e->y,e->x+NEGYZET,e->y+NEGYZET,0,128,128,255);//kirajzolok egy n�gyzetet a kapott koordin�t�k hely�n
    SDL_Flip(screen);
}
void eger_rajzol2(SDL_Surface *screen,eger *egerke,egyseg *kigyo,egyseg *kigyo2)
{
    eger_inicializal2(egerke,kigyo,kigyo2);
    boxRGBA(screen,egerke->x,egerke->y,egerke->x+NEGYZET,egerke->y+NEGYZET,0,128,128,255);
    SDL_Flip(screen);
}

void eger_torol(SDL_Surface *screen, eger *e)//fekete n�gyzet
{
    boxRGBA(screen,e->x,e->y,e->x+NEGYZET,e->y+NEGYZET,0,0,0,255);
    SDL_Flip(screen);
}


void rajzol(SDL_Surface *screen , egyseg *eleje)
{    while(eleje!=NULL)//v�gigmegyek a lista elemein �s kirajzolom �ket a koordin�t�ikkal
    {
        boxRGBA(screen,eleje->x,eleje->y,eleje->x+NEGYZET,eleje->y+NEGYZET,rand_szam_RGB(),rand_szam_RGB(),rand_szam_RGB(),255);
        eleje=eleje->kovetkezo;
    }
}


void torol(SDL_Surface *screen , egyseg *eleje)//az egys�gek koordin�t�it feket�re festem
{    while(eleje!=NULL)
    {
        boxRGBA(screen,eleje->x,eleje->y,eleje->x+NEGYZET,eleje->y+NEGYZET,0,0,0,255);
        eleje=eleje->kovetkezo;
    }
}

void leptet(SDL_Surface *screen , egyseg *eleje)
{   egyseg *mozgo=eleje;
    while(mozgo->kovetkezo!=NULL) mozgo=mozgo->kovetkezo;//el�sz�r elmegyek a kigy� v�g�re
    torol(screen,eleje);//azt�n t�rl�m az id�-1 poz�ci�ban l�v� k�gy�t
    while(mozgo!=NULL)//ir�nyad�s az egys�geknek
    {
        switch(mozgo->irany){
            case jobbra: mozgo->x+=NEGYZET; break;
            case balra:  mozgo->x-=NEGYZET; break;
            case le:     mozgo->y+=NEGYZET; break;
            case fel:    mozgo->y-=NEGYZET; break;
        }

if(mozgo!=eleje) mozgo->irany=mozgo->elozo->irany;
        mozgo=mozgo->elozo;

    }

    rajzol(screen,eleje);//ha ez k�sz, akkor az �j k�gy�t kirajzolom
    SDL_Flip(screen);
}
