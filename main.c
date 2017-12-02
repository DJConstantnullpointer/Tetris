#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "Keys.h"

//System
Uint32 tr(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}

int main(int argc, char *argv[])
{
    srand(time(0));
    SDL_Event ev;
    SDL_Surface *screen;
    SDL_TimerID t;
    int tick = 0, cursor = 0, score = 0, zero = 0, i;
    char speed = 8, sscore [10];
    txt tx16,tx24,tx50,tx88,tx108;
    SDL_Color white = {255, 255, 255}, blue = {0,0,255};
    sprintf(sscore, "%d", score);
    bool quit = false, pause = false, play = false, ctrlscreen = false, hsscreen = false, loss = false;
    obj current,nxt,predict;
    FILE *save,*hs;
    int **field, row[sizey];
    field = (int**) malloc(sizey * sizeof(int*));
    for(i = 0; i < sizey; i++)
        {
            row[i] = 0;
            field[i] = (int*) calloc(sizex,sizeof(int));
        }

    /* Initialize SDL window */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen = SDL_SetVideoMode(410, 470, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Was not able to open window!\n");
        exit(1);
    }
    SDL_WM_SetCaption("Tetris", "Tetris");
    TTF_Init();
    tx16.font = TTF_OpenFont("LiberationSerif-Regular.ttf", 16);
    tx24.font = TTF_OpenFont("LiberationSerif-Regular.ttf", 24);
    tx50.font = TTF_OpenFont("LiberationSerif-Regular.ttf", 50);
    tx88.font = TTF_OpenFont("LiberationSerif-Regular.ttf", 88);
    tx108.font = TTF_OpenFont("LiberationSerif-Regular.ttf", 108);
    tx16.color = tx24.color = tx50.color = tx88.color = white;
    tx108.color = blue;

    dmenu(screen,&tx108,&tx50);
    rectangleRGBA(screen,60,150 + 60*cursor,360,200+ 60*cursor,0,255,0,255);
    SDL_Flip(screen);
    t = SDL_AddTimer(60, tr, NULL);
    while(!quit)
    {
        SDL_WaitEvent(&ev);
        switch(ev.type)
        {
        case SDL_KEYDOWN:
            switch(ev.key.keysym.sym)
            {
                case SDLK_DOWN:
                if(!pause && play && !dcollide(field,current))
                {
                    kdowng(screen,&current,&predict,field);
                }
                else if(cursor == 0 && pause && play)
                {
                    kdownp(screen,&cursor);
                }
                else if(cursor < 4 && !play)
                {
                    kdownm(screen,&cursor);
                }
                break;
            case SDLK_LEFT:
                if(!pause && play && !lcollide(field,current))
                {
                    kleftg(screen,&current,&predict,field);
                }
                break;
            case SDLK_RIGHT:
                if( !pause && play && !rcollide(field,current))
                {
                    krightg(screen,&current,&predict,field);
                }
                break;
            case SDLK_UP:
                if(!pause && play && !rotcol(field,current))
                {
                    kupg(screen,&current,&predict,field);
                }
                else if(cursor == 1 && pause && play)
                {
                    kupp(screen,&cursor);
                }
                else if(cursor > 0 && !play)
                {
                    kupm(screen,&cursor);
                }
                break;
            case SDLK_x:
                if(!pause && play)
                {
                    current = drop(field,current);
                    removepred(field,predict);
                    dblocks(screen, field);
                    SDL_Flip(screen);
                }
                else if(!play && hsscreen)
                {
                    hs = fopen("hs.txt","wb");
                    fwrite(&zero,sizeof(int),1,hs);
                    fclose(hs);
                    dhighscore(screen,&score,sscore,&tx88,&tx50,&tx16,hs);
                }
                break;
            case SDLK_SPACE:
                if(pause && play)
                {
                    pause = !pause;
                    boxRGBA(screen,145,185,265,270,0,0,0,255);
                    boxRGBA(screen,0,0,80,40,0,0,0,255);
                    dblocks(screen,field);
                    SDL_Flip(screen);
                }
                else if(play && !pause)
                {
                    pause = !pause;
                    cursor = 0;
                    dpause(screen,&tx16);
                    SDL_Flip(screen);
                }
                if((!play && ctrlscreen)|| (!play && hsscreen))
                {
                    dmenu(screen,&tx108,&tx50);
                    ctrlscreen = false;
                    hsscreen = false;
                    cursor = 0;
                    SDL_Flip(screen);
                }
                break;
            case SDLK_RETURN:
                    if(pause && play)
                    {
                        kenterg(screen,&play,&pause,&cursor,&tx108,&tx50,&tx16,field,save,&current,&nxt,&predict,&score);
                    }
                    else if(!play && !ctrlscreen && !hsscreen)
                    {
                        kenterm(screen,&play,&quit,&ctrlscreen,&hsscreen,&tx88,&tx50,&tx24,&tx16,
                                field,&current,&nxt,&predict,&score,sscore,&cursor,save,hs);
                        SDL_Flip(screen);
                    }
                    break;
            default:
                break;
            }
        case SDL_USEREVENT:
            if(!pause && play && !loss){
            setspeed(&speed,score);
            tick++;
            if (tick % speed) {
            } else {
                if(checkloss(field))
                {
                    play = false;
                    loss = true;
                    settp(&tx16,0,0,40,20);
                    cleanfield(field);
                    dmenu(screen,&tx108,&tx50);
                    print("You lost",screen,&tx16);
                    SDL_Flip(screen);
                    seths(&score,hs);
                    break;
                }
                    if(current.a.y == 19 || current.d.y == 19 || current.c.y == 19 || current.a.y == 19 || dcollide(field,current))
                    {
                        reachdown(screen,field,&current,&nxt,&predict);
                    }
                    else
                    {
                        current = down(field, current);
                    }
                    stdevent(screen,&tx16,sscore,field,row,&score,&predict,&current);
            }}
            if(loss)
            {
                boxRGBA(screen,0,0,60,50,0,0,0,255);
                loss= false;
            }
            break;
        case SDL_QUIT:
            quit = true;
            break;
            }
        }


     for(i = 0; i < sizey; i++)
        {
            free(field[i]);
        }

    SDL_RemoveTimer(t);
    SDL_FreeSurface(tx16.w);
    SDL_FreeSurface(tx24.w);
    SDL_FreeSurface(tx50.w);
    SDL_FreeSurface(tx88.w);
    SDL_FreeSurface(tx108.w);
    SDL_Quit();

    return 0;
}
