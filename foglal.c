#include <stdio.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <time.h>
#include "global.h"
//#include <SDL_mixer.h>

int eger_inicializal(eger *e,egyseg *eleje)
{
    int ok = 0;
    int ujx,ujy;
    while(!ok)//na h�t ez a f�ggv�ny m�r egy kis gondolkod�st ig�nyelt,
    {         //addig gener�l �j x,y koordin�t�t, am�g az nincs rajta a k�gy� jelenlegi poz�ci�j�n
        ujx = rand()%((SZELESSEG-NEGYZET)-NEGYZET)+NEGYZET;
        ujy = rand()%((MAGASSAG-NEGYZET)-NEGYZET)+NEGYZET;
        while(eleje->kovetkezo!=NULL)
        {
            if(!(eleje->x==ujx)&&!(eleje->y==ujy))
            {
                break;
            }
            eleje=eleje->kovetkezo;
        }
        ok=1;
    }
    e->x=ujx;
    e->y=ujy;
}

int eger_inicializal2(eger *e,egyseg *kigyo, egyseg *kigyo2)// ez a f�ggv�ny l�nyeg�ben ugyanaz csak 3 param�terrel �s eggyel t�bb while ciklussal
{
    int ok = 0;
    int ujx,ujy;
    while(!ok)
    {
        ujx = rand()%((SZELESSEG-NEGYZET)-NEGYZET)+NEGYZET;
        ujy = rand()%((MAGASSAG-NEGYZET)-NEGYZET)+NEGYZET;
        while(kigyo->kovetkezo!=NULL)
        {
            if(!(kigyo->x==ujx)&&!(kigyo->y==ujy))
            {
                break;
            }
            kigyo=kigyo->kovetkezo;
        }
        while(kigyo2->kovetkezo!=NULL)
        {
            if(!(kigyo2->x==ujx)&&!(kigyo2->y==ujy))
            {
                break;
            }
            kigyo2=kigyo2->kovetkezo;
        }
        ok=1;
    }
    e->x=ujx;
    e->y=ujy;
}

int fej_inicializal(egyseg *feje)//az x,y koordin�t�k a j�tszhat�s�g �rdek�ben a SZELESSEG/2 vagy MAGASSAG/2, 100 intervallumon vannak
{
    feje->irany=balra;
    feje->x=rand()%((SZELESSEG/2-NEGYZET)-100)+100;
    feje->y=rand()%((MAGASSAG/2-NEGYZET)-100)+100;
    feje->kovetkezo=NULL;
    feje->elozo=NULL;
}
int egyseg_inicializal(egyseg *test)//nos szerintem ez sem t�l nagy �rd�ng�ss�g,
{                                   //mindig az el�z� egys�g param�tereit kapja az �jonnan hozz�adott
    test->irany=test->elozo->irany;
    switch(test->elozo->irany)
    {
    case jobbra: test->x=test->elozo->x-NEGYZET; test->y=test->elozo->y; break;
    case balra:  test->x=test->elozo->x+NEGYZET; test->y=test->elozo->y; break;
    case le:     test->y=test->elozo->y-NEGYZET; test->x=test->elozo->x; break;
    case fel:    test->y=test->elozo->y+NEGYZET; test->x=test->elozo->x; break;
    }
}

egyseg * fej_foglal(void)
{   egyseg *feje;
    feje = (egyseg*)(malloc(sizeof(egyseg)));//1 egys�get lefoglalunk, ut�na pedig inicializ�ljuk
    if(feje==NULL)
    {
        fprintf(stderr,"hiba");
        return NULL;
    }
    fej_inicializal(feje);
    return feje;
}
int kigyo_novel(egyseg *kigyo)
{
    egyseg *novekmeny;
    while(kigyo->kovetkezo!=NULL){
        kigyo=kigyo->kovetkezo;
    }
    novekmeny=(egyseg*) malloc(sizeof(egyseg));
    kigyo->kovetkezo=novekmeny;
    novekmeny->elozo=kigyo;
    novekmeny->kovetkezo=NULL;
    egyseg_inicializal(novekmeny);
    return 1;
}

int kigyo_felszabadit(egyseg *kigyo)
{
    egyseg *iter, *temp;
    iter = kigyo;
    while(iter->kovetkezo!=NULL)
    {
        iter->kovetkezo=temp;
        free(iter);
        iter=temp;
    }
    free(iter);
    free(kigyo);
    free(temp);
    return 1;
}


