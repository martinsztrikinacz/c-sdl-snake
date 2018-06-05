#include <stdio.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include "global.h"
//#include <SDL_mixer.h>


int melyik_a_nagyobb( const void *a, const void *b)//ez a qsort függvényhez kell, a programnak ez az egyetlen része, amit nem én írtam
{                                                  //http://www.cplusplus.com/reference/cstdlib/qsort/
   int int_a = * ( (int*) a );
   int int_b = * ( (int*) b );

   return (int_a > int_b) - (int_a < int_b);
}

int pont_kezel(int pont1, int pont2)//véleményem szerint ez a legérdekesebb függvény a programban
{
    FILE *file = fopen("pontok.txt", "r");
    if(file==NULL){
        return 0;
    }
    int szamok[7];//5 pont van eltarolva maximum, *qsort* a két legkisebbet levágom

    int i=0;
    int num;
    /*while(fscanf(file, "%d", &num) != EOF)
    {
        szamok[i] = num;
        i++;
    }*/
    for(i=0;i<5;i++)//itt végigmegyek az öt soron
    {
        fscanf(file,"%d",&num);
        szamok[i]=num;
    }
    fclose(file);//aztán itt becsukom a fájlt, mert az rw paraméter valamiért nem működött
    file=fopen("pontok.txt","w");

    szamok[5]=pont1;//a tömb utolsó két eleme a paraméterként kapott értékek
    szamok[6]=pont2;

    qsort( szamok, 7, sizeof(int), melyik_a_nagyobb );//rendezem a c által biztosított qsort algoritmussal!



    for(i=7-1;i!=2-1;i--)//hogy utána levágjam a két legkisebbet és visszaírjam a fájlba az új értékeket
    {
        fprintf(file,"%d",szamok[i]);
        fprintf(file,"%s","\n");
    }

    fclose(file);
    return 1;
}



Uint32 idozit(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}

int utkozes_eger(SDL_Surface *screen, eger *e, egyseg *eleje)//ha koordináta+NÉGYZET intervallumon belül vagyunk, akkor van ütközés
{   int utkozes=0;
    int egerx=e->x;
    int egery=e->y;
    int kigyox=eleje->x;
    int kigyoy=eleje->y;
    if((kigyox>=egerx && kigyox<=egerx+NEGYZET) || (kigyox+NEGYZET>=egerx && kigyox+NEGYZET<=egerx+NEGYZET))
        if((kigyoy>=egery && kigyoy<=egery+NEGYZET) || (kigyoy+NEGYZET>=egery && kigyoy+NEGYZET<=egery+NEGYZET)) utkozes=1;

    if(utkozes)
    {
        eger_torol(screen,e);
        kigyo_novel(eleje);
        return 1;
    }
    return 0;
}

int utkozes_eger2(SDL_Surface *screen, eger *e, egyseg *kigyo,egyseg *kigyo2)
{
    int egerx=e->x;
    int egery=e->y;
    int kigyo1x=kigyo->x;
    int kigyo1y=kigyo->y;
    int kigyo2x=kigyo2->x;
    int kigyo2y=kigyo2->y;
    if((kigyo1x>=egerx && kigyo1x<=egerx+NEGYZET) || (kigyo1x+NEGYZET>=egerx && kigyo1x+NEGYZET<=egerx+NEGYZET))
    {
        if((kigyo1y>=egery && kigyo1y<=egery+NEGYZET) || (kigyo1y+NEGYZET>=egery && kigyo1y+NEGYZET<=egery+NEGYZET))
        {
            eger_torol(screen,e);
            kigyo_novel(kigyo);
            return 1;
        }
    }
    else if((kigyo2x>=egerx && kigyo2x<=egerx+NEGYZET) || (kigyo2x+NEGYZET>=egerx && kigyo2x+NEGYZET<=egerx+NEGYZET))
    {
        if((kigyo2y>=egery && kigyo2y<=egery+NEGYZET) || (kigyo2y+NEGYZET>=egery && kigyo2y+NEGYZET<=egery+NEGYZET))
        {
            eger_torol(screen,e);
            kigyo_novel(kigyo2);
            return 2;
        }
    }
    return 0;
}

int utkozes_fal(egyseg *eleje)//..
{
    if((eleje->x<0)||(eleje->x>SZELESSEG-NEGYZET)||(eleje->y<0||eleje->y>MAGASSAG-NEGYZET))
    {
        return 1;
    }
    return 0;
}

int utkozes_test(egyseg *eleje)
{
    if(eleje->kovetkezo!=NULL){//a saját fejével nem tud ütközni
        egyseg *mozgo=eleje->kovetkezo;

        while(mozgo->kovetkezo!=NULL)
        {
            int mozgox=mozgo->x;
            int mozgoy=mozgo->y;
            int kigyox=eleje->x;
            int kigyoy=eleje->y;
            if(kigyox==mozgox&&kigyoy==mozgoy)
            {
                return 1;
            }
            else
            {
                mozgo=mozgo->kovetkezo;
            }
        }
    }
    return 0;
}

int utkozes_test2(egyseg *kigyo,egyseg *kigyo2)//ennek azért csináltam külön függvényt, mert egyben az egyjátékossal átláthatatlan lett volna
{

    int kigyo1x=kigyo->x;
    int kigyo1y=kigyo->y;
    int kigyo2x=kigyo2->x;
    int kigyo2y=kigyo2->y;
    if((kigyo1x>=kigyo2x && kigyo1x<=kigyo2x+NEGYZET) || (kigyo1x+NEGYZET>=kigyo2x && kigyo1x+NEGYZET<=kigyo2x+NEGYZET))
    {
        if((kigyo1y>=kigyo2y && kigyo1y<=kigyo2y+NEGYZET) || (kigyo1y+NEGYZET>=kigyo2y && kigyo1y+NEGYZET<=kigyo2y+NEGYZET))
        {

            return 1;
        }
    }
    else if((kigyo2x>=kigyo1x && kigyo2x<=kigyo1x+NEGYZET) || (kigyo2x+NEGYZET>=kigyo1x && kigyo2x+NEGYZET<=kigyo1x+NEGYZET))
    {
        if((kigyo2y>=kigyo1y && kigyo2y<=kigyo1y+NEGYZET) || (kigyo2y+NEGYZET>=kigyo1y && kigyo2y+NEGYZET<=kigyo1y+NEGYZET))
        {

            return 1;
        }
    }
    return 0;
}


