#include <stdio.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include "global.h"
#include <time.h>
//#include <SDL_mixer.h>

#define GYORSITAS_INTERVALLUM 10
#define MAXSEBESSEG 30

int main(int argc, char **argv)
{
    int szamlalo=0;/*ezek a változók dokumentálják magukat*/
    int sebesseg=210;
    int pont=0;int pont2=0;

    int hanyjatekos;
    int eger_lent=0;
    int quit = 0;

    egyseg *kigyo;
    egyseg *kigyo2;
    eger egerke;

	SDL_Surface *screen;
	SDL_Event event;
	SDL_TimerID id;
    srand(time(0));

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);/*sdl inicializálás*/
	screen = SDL_SetVideoMode(SZELESSEG, MAGASSAG, 0, SDL_ANYFORMAT);
	if(screen == NULL)
    {
        printf("Nem sikerült inicializálni a játékot.");
	}

	SDL_WM_SetCaption("Snake 0.3 By Martin Molnar", NULL);
    id=SDL_AddTimer(sebesseg, idozit, NULL);

    /*Na ezt leírtam a dokumentációban is de a zene részt végig kikommenteztem, hogy könnyebben lehessen fordítani, de lásd, hogy
    amúgy lett volna benne zene.
    Mix_Music *music = NULL;
    Mix_Chunk *beep_eat = NULL;
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        printf("hiba");
    }
    music = Mix_LoadMUS( "b6.wav" );
    beep_eat = Mix_LoadWAV( "beep_eat.wav" );
    if( (music == NULL)||(beep_eat==NULL) )
    {
        printf("hiba");
    }*/

    hanyjatekos=menu(screen);//itt a menu fv visszatér egy inttel

    switch (hanyjatekos)//switchelünk a visszatérési értékre
    {
        case 1: kigyo=fej_foglal();//1 kígyó foglalás

                break;
        case 2: kigyo=fej_foglal();//2 kígyó foglalás
                kigyo2=fej_foglal();
                break;
        case 3: hanyjatekos=pont_rajzol(screen);//ebben az esetben meg kirajzolom a pontokat,visszatér 0-val, kilépek
                free(screen);
                SDL_Quit();
                return 0;
                break;
        case 0: free(screen);
                SDL_Quit();
                return 0;
        default: break;
    }

    boxRGBA(screen,0,0,SZELESSEG,MAGASSAG,0,0,0,255);
    SDL_Flip((screen));
    //Mix_PlayMusic(music,-1);

    while(!quit)//játékciklus
    {
		SDL_WaitEvent(&event);
		switch(event.type)
		{
            case SDL_USEREVENT:
                szamlalo++;//ez a sebesség növelése miatt kell
                if(szamlalo==GYORSITAS_INTERVALLUM)//x usereventenként gyorsít
                {
                    SDL_RemoveTimer(id);
                    if(sebesseg>MAXSEBESSEG)
                        sebesseg-=2;
                    id=SDL_AddTimer(sebesseg,idozit,NULL);//és akkor itt új értéket kell adni a timernek
                    szamlalo=0;
                }
                if(hanyjatekos==1)
                {
                    if(eger_lent==0)//ha nincs a pályán egér, újat rajzolunk
                    {
                        eger_rajzol(screen,&egerke,kigyo);
                        eger_lent=1;
                    }
                    leptet(screen,kigyo);
                    if(utkozes_eger(screen,&egerke,kigyo)){ /*Mix_PlayChannel(-1,beep_eat,0);*/eger_lent=0;pont++;}
                    if(utkozes_fal(kigyo)||utkozes_test(kigyo))
                    {
                        //Mix_HaltMusic();
                        pont_kezel(pont,pont2);//itt a pont2 0-ra van inicializálva, szóval nem fog gondot jelenteni egyjátékos módban
                        SDL_RemoveTimer(id);
                        boxRGBA(screen,0,0,SZELESSEG,MAGASSAG,255,0,0,255);
                        stringRGBA(screen, SZELESSEG/2-130, MAGASSAG/2-30, "A jatek veget ert. A pontjaid:", 255, 255, 255, 255);
                        stringRGBA(screen, SZELESSEG/2-130, MAGASSAG/2, "A kilepeshez nyomd meg az Esc-et.", 255, 255, 255, 255);
                        char c[10];
                        sprintf(c, "%d", pont);
                        stringRGBA(screen, SZELESSEG/2+130, MAGASSAG/2-30, c, 255, 255, 255, 255);
                        SDL_Flip(screen);

                        kigyo_felszabadit(kigyo);
                        kigyo_felszabadit(kigyo2);
                        free(screen);
                    }
                }
                else if(hanyjatekos==2)
                {

                    if(eger_lent==0)
                    {
                        eger_rajzol2(screen,&egerke,kigyo,kigyo2);
                        eger_lent=1;
                    }
                    leptet(screen,kigyo);
                    leptet(screen,kigyo2);
                    if((utkozes_eger2(screen,&egerke,kigyo,kigyo2)==1))
                    {
                        //Mix_PlayChannel(-1,beep_eat,0);
                        pont++;
                        eger_lent = 0;
                    }
                    else if((utkozes_eger2(screen,&egerke,kigyo,kigyo2)==2))
                    {
                        //Mix_PlayChannel(-1,beep_eat,0);
                        pont2++;
                        eger_lent = 0;
                    }
                    if(utkozes_fal(kigyo)||utkozes_fal(kigyo2)||utkozes_test2(kigyo,kigyo2))
                    {
                        //Mix_HaltMusic();
                        //ez a rész önmagát dokumentálja
                        pont_kezel(pont,pont2);
                        SDL_RemoveTimer(id);
                        boxRGBA(screen,0,0,SZELESSEG,MAGASSAG,255,0,0,255);
                        stringRGBA(screen, SZELESSEG/2-130, MAGASSAG/2-30, "A jatek veget ert. A pontjaitok:", 255, 255, 255, 255);
                        char c1[1000];sprintf(c1, "%d", pont);
                        char c2[1000];sprintf(c2, "%d", pont2);
                        stringRGBA(screen, SZELESSEG/2-130, MAGASSAG/2, "A nyilakkal jatszo jatekos:", 255, 131, 255, 255);
                        stringRGBA(screen, SZELESSEG/2+100, MAGASSAG/2, c1, 255, 255, 255, 255);

                        stringRGBA(screen, SZELESSEG/2-130, MAGASSAG/2+30, "WASD-vel jatszo jatekos:", 255, 255, 22, 255);
                        stringRGBA(screen, SZELESSEG/2+100, MAGASSAG/2+30, c2, 255, 255, 255, 255);
                        stringRGBA(screen, SZELESSEG/2-130, MAGASSAG/2+60, "A kilepeshez nyomd meg az Esc-et.", 255, 255, 255, 255);

                        SDL_Flip(screen);

                        kigyo_felszabadit(kigyo);
                        kigyo_felszabadit(kigyo2);
                        free(screen);
                    }
                }
                break;
            case SDL_KEYDOWN://na hát ez a rész egy kicsit sormintás, de jobban nem tudtam megoldani
                 switch (event.key.keysym.sym)
                 {
                    case SDLK_ESCAPE: quit=1; break;
                    case SDLK_UP: if(!(kigyo->irany==le)||(kigyo->kovetkezo==NULL))//az if-ben a jobb oldali feltétel azért kell, mert, ha a kígyó
                                  {                                                //még csak egy egységből áll, akkor másképp viselkedik
                                        kigyo->irany=fel;                          //mind a négy irányba mozoghat
                                  }
                                  break;

                    case SDLK_DOWN: if(!(kigyo->irany==fel)||(kigyo->kovetkezo==NULL))kigyo->irany=le; break;
                    case SDLK_RIGHT: if(!(kigyo->irany==balra)||(kigyo->kovetkezo==NULL))kigyo->irany=jobbra; break;
                    case SDLK_LEFT: if(!(kigyo->irany==jobbra)||(kigyo->kovetkezo==NULL))kigyo->irany=balra; break;
                    /*if(hanyjatekos==2)
                    {
                        case SDLK_w: if(!(kigyo2->irany==le)||(kigyo2->kovetkezo==NULL))kigyo2->irany=fel; break;
                        case SDLK_s: if(!(kigyo2->irany==fel)||(kigyo2->kovetkezo==NULL))kigyo2->irany=le; break;
                        case SDLK_d: if(!(kigyo2->irany==balra)||(kigyo2->kovetkezo==NULL))kigyo2->irany=jobbra; break;
                        case SDLK_a: if(!(kigyo2->irany==jobbra)||(kigyo2->kovetkezo==NULL))kigyo2->irany=balra; break;
                    }*/
                    case SDLK_w:
                                if(hanyjatekos==2)
                                {
                                    if(!(kigyo2->irany==le)||(kigyo2->kovetkezo==NULL))
                                    {
                                        kigyo2->irany=fel;
                                    }
                                }
                                break;
                    case SDLK_s:
                                if(hanyjatekos==2)
                                {
                                    if(!(kigyo2->irany==fel)||(kigyo2->kovetkezo==NULL))
                                    {
                                        kigyo2->irany=le;
                                    }
                                }
                                break;
                    case SDLK_d:
                                if(hanyjatekos==2)
                                {
                                    if(!(kigyo2->irany==balra)||(kigyo2->kovetkezo==NULL))
                                    {
                                        kigyo2->irany=jobbra;
                                    }
                                }
                                break;
                    case SDLK_a:
                                if(hanyjatekos==2)
                                {
                                    if(!(kigyo2->irany==jobbra)||(kigyo2->kovetkezo==NULL))
                                    {
                                        kigyo2->irany=balra;
                                    }
                                }
                                break;
                    default: break;
                 }
                break;
            case SDL_QUIT:
                free(screen);
                SDL_Quit();
                return 0;
                //quit=1;
                break;
		}

    }
	return 0;
}
