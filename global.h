#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#define SZELESSEG 640
#define MAGASSAG 480
#define NEGYZET 15


typedef enum iranyok
{
    fel,le,jobbra,balra
}iranyok;

typedef struct egyseg//duplán láncolt lista
{
	iranyok irany;
	int x;
	int y;
    struct egyseg *kovetkezo;
    struct egyseg *elozo;
}egyseg;

typedef struct eger//le minimal
{
    int x;
    int y;
}eger;

//foglal.c
int eger_inicializal(eger *e,egyseg *eleje);
int eger_inicializal2(eger *e,egyseg *kigyo, egyseg *kigyo2);
int fej_inicializal(egyseg *feje);
int egyseg_inicializal(egyseg *test);
egyseg * fej_foglal(void);
int kigyo_novel(egyseg *kigyo);
int kigyo_felszabadit(egyseg *kigyo);
//rajzol.c
void eger_rajzol(SDL_Surface *screen, eger *e,egyseg *eleje);
void eger_rajzol2(SDL_Surface *screen,eger *egerke,egyseg *kigyo,egyseg *kigyo2);
void eger_torol(SDL_Surface *screen, eger *e);
void rajzol(SDL_Surface *screen , egyseg *eleje);
void torol(SDL_Surface *screen, egyseg *eleje);
void leptet(SDL_Surface *screen , egyseg *eleje);
int rand_szam_RGB(void);
int pont_rajzol(SDL_Surface *screen);

//menu.c
int menu(SDL_Surface *screen);
void menu_rajzol(SDL_Surface *screen, int menupont);
//egyeb.c
Uint32 idozit(Uint32 ms, void *param);
int utkozes_eger2(SDL_Surface *screen, eger *e, egyseg *kigyo,egyseg *kigyo2);
int utkozes_eger(SDL_Surface *screen, eger *e, egyseg *eleje);
int utkozes_fal(egyseg *eleje);
int utkozes_test(egyseg *eleje);
int utkozes_test2(egyseg *kigyo,egyseg *kigyo2);
int pont_kezel(int pont1, int pont2);
int melyik_a_nagyobb( const void *a, const void *b);

#endif // GLOBAL_H_INCLUDED
