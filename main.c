#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define sizex 10
#define sizey 20
//Map drawing
void map(SDL_Surface *s);
//Structures
typedef struct block{int x,y;}block;
typedef struct obj{block a,b,c,d; char e;}obj;
//Placing, generating and drawing
void place(int t[sizey][sizex], block a);
void dis(int t[sizey][sizex], block a);
obj genobj();
void placeobj(int t[sizey][sizex], obj tetris);
void removeobj(int t[sizey][sizex], obj tetris);
void dblocks(SDL_Surface *s,int t[sizey][sizex]);
//Movement
obj downm(obj tetris);
obj down(int t[sizey][sizex], obj tetris);
obj leftm(obj tetris);
obj left(int t[sizey][sizex], obj tetris);
obj rightm(obj tetris);
obj right(int t[sizey][sizex], obj tetris);
obj upm(obj tetris);
obj up(int t[sizey][sizex], obj tetris);
bool lcollide(int t[sizey][sizex], obj tetris);
bool rcollide(int t[sizey][sizex], obj tetris);
bool dcollide(int t[sizey][sizex], obj tetris);
obj dropm(int t[sizey][sizex], obj tetris);
obj drop(int t[sizey][sizex], obj tetris);
obj shift(obj tetris);
block ulm(block a);
block urm(block a);
block dlm(block a);
block drm(block a);
obj lrotate(obj tetris);
obj lftr(int t[sizey][sizex], obj tetris);
bool rotcol(int t[sizey][sizex], obj tetris);
//Game mechanics
void checkrow(int t[sizey][sizex], int r[sizey]);
bool checkloss(int t[sizey][sizex]);
void clrrow(int t[sizey][sizex], int r[sizey]);
void alldown(int t[sizey][sizex], int r[sizey]);
void solidify(int t[sizey][sizex], obj tetris);
void zerow(int r[sizey]);
int cntscore(int r[sizey]);
char* itoa (int value, char *result, int base);
void dscore(int value, char *result, SDL_Surface *w,SDL_Surface *s,TTF_Font *font, SDL_Rect tpos, SDL_Color color);

//System
void print(TTF_Font *font,char* wd,SDL_Color color,SDL_Surface *w,SDL_Surface *s,SDL_Rect tpos){
    w = TTF_RenderUTF8_Solid(font, wd, color);
    SDL_BlitSurface(w, NULL, s, &tpos);
}
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
    int period = 500;
    TTF_Font *font;
    SDL_Surface *words;
    SDL_Rect tpos = { 332, 52, 40, 20 };
    SDL_Color feher = {255, 255, 255};
    int score = 0;
    char *sscore;
    itoa(score,sscore,10);
    bool quit = false,kd = false;
    int i,g;
    int field[sizey][sizex], row[sizey];
    for(i = 0; i < 20; i++)
        {
            row[i] = 0;
            for(g =0; g <10; g++)
                {
                    field[i][g] = 0;
                }
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
    font = TTF_OpenFont("/usr/share/fonts/TTF/UbuntuMono-R.ttf", 16);
    font = TTF_OpenFont("LiberationSerif-Regular.ttf", 16);
    if (!font) {
        fprintf(stderr, "Was not able to open font! %s\n", TTF_GetError());
        exit(1);
    }


    map(screen);
    print(font,"Score:",feher,words,screen,tpos);
    tpos.x = 352;
    tpos.y = 72;
    tpos.w = 40;
    tpos.h = 20;
    print(font,sscore,feher,words,screen,tpos);

    obj current;
    current = genobj();
    placeobj(field,current);
    dblocks(screen,field);
    SDL_Flip(screen);
    t = SDL_AddTimer(period, tr, NULL);
    while (!quit) {
        SDL_WaitEvent(&ev);
        switch(ev.type)
        {
        case SDL_KEYDOWN:
            kd = true;
            switch(ev.key.keysym.sym)
            {
            case SDLK_DOWN:
                if(!dcollide(field,current))
                {
                    current = down(field, current);
                    dblocks(screen, field);
                    SDL_Flip(screen);
                    break;
                }
            case SDLK_LEFT:
                if(!lcollide(field,current))
                {
                    current = left(field, current);
                    dblocks(screen, field);
                    SDL_Flip(screen);
                    break;
                }
            case SDLK_RIGHT:
                if(!rcollide(field,current))
                {
                    current = right(field, current);
                    dblocks(screen, field);
                    SDL_Flip(screen);
                    break;
                }
            case SDLK_UP:
                if(!rotcol(field,current))
                {
                    current = lftr(field, current);
                    dblocks(screen, field);
                    SDL_Flip(screen);
                    break;
                }
            case SDLK_x:
                current = drop(field, current);
                dblocks(screen, field);
                SDL_Flip(screen);
                break;
            }
        case SDL_USEREVENT:
            if(checkloss(field))
            {
                quit = true;
                break;
            }
            if(!kd)
            {
                if(dcollide(field,current) || current.a.y == 19 || current.d.y == 19)
                {
                    solidify(field,current);
                    current = genobj();
                }
                else
                {
                    current = down(field, current);
                }
                checkrow(field,row);
                clrrow(field,row);
                alldown(field,row);
                score += cntscore(row);
                zerow(row);
                dscore(score,sscore,words,screen,font,tpos,feher);
                dblocks(screen, field);
                SDL_Flip(screen);
            }
            kd = false;
            break;
        case SDL_QUIT:
            quit = true;
            break;
        }
    }

    SDL_RemoveTimer(t);
    SDL_FreeSurface(words);
    SDL_Quit();

    return 0;
}

//draws the playingfield
void map(SDL_Surface *s)
{
    int i;
    for(i= 100; i < 311; i += 21)
        {
            lineRGBA(s,i,25,i,445,255,255,255,255);
        }
    for(i = 25; i < 446; i += 21)
        {
            lineRGBA(s,100,i,310,i,255,255,255,255);
        }
    rectangleRGBA(s,330, 50,400,100,255,255,255,255);
    boxRGBA(s,331,51,399,99,255,0,0,255);
}
//places blocks into the grid
void place(int t[sizey][sizex],block a)
{
   t[a.y][a.x] = 1;
}
//Removes blocks from grid
void dis(int t[sizey][sizex], block a)
{
    t[a.y][a.x] = 0;
}
//Places objects into the grid
void placeobj(int t[sizey][sizex], obj tetris)
{
    place(t,tetris.a);
    place(t,tetris.b);
    place(t,tetris.c);
    place(t,tetris.d);
}
//Removes object from the grid
void removeobj(int t[sizey][sizex], obj tetris)
{
    dis(t,tetris.a);
    dis(t,tetris.b);
    dis(t,tetris.c);
    dis(t,tetris.d);
}
//Generates object
obj genobj()
{
    obj objout;
    int ro,rp;
    ro = rand()%7 + 1;
    switch(ro)
    {
        case 1:
            rp = rand()%5 +1;
            objout.e = 'I';
            objout.a.x = rp;
            objout.a.y =1;
            objout.b.x = objout.a.x + 1;
            objout.b.y = 1;
            objout.c.x = objout.a.x + 2;
            objout.c.y = 1;
            objout.d.x = objout.a.x + 3;
            objout.d.y = 1;
            break;
        case 2:
            rp = rand()%6 +1;
            objout.e = 'A';
            objout.a.x = rp;
            objout.a.y =1;
            objout.b.x = objout.a.x + 1;
            objout.b.y = 1;
            objout.c.x = objout.a.x + 1;
            objout.c.y = 0;
            objout.d.x = objout.a.x + 2;
            objout.d.y = 1;
            break;
        case 3:
            rp = rand()%7 +1;
            objout.e = 'O';
            objout.a.x = rp;
            objout.a.y =1;
            objout.b.x = objout.a.x;
            objout.b.y = 0;
            objout.c.x = objout.a.x + 1;
            objout.c.y = 0;
            objout.d.x = objout.a.x + 1;
            objout.d.y = 1;
            break;
        case 4:
            rp = rand()%6 +1;
            objout.e = 'L';
            objout.a.x = rp;
            objout.a.y =1;
            objout.b.x = objout.a.x + 1;
            objout.b.y = 1;
            objout.c.x = objout.a.x + 2;
            objout.c.y = 1;
            objout.d.x = objout.a.x + 2;
            objout.d.y = 0;
            break;
        case 5:
            rp = rand()%6 +1;
            objout.e = 'R';
            objout.a.x = rp;
            objout.a.y =0;
            objout.b.x = objout.a.x;
            objout.b.y = 1;
            objout.c.x = objout.a.x + 1;
            objout.c.y = 1;
            objout.d.x = objout.a.x + 2;
            objout.d.y = 1;
            break;
        case 6:
            rp = rand()%6 +1;
            objout.e = 'Z';
            objout.a.x = rp;
            objout.a.y =0;
            objout.b.x = objout.a.x+1;
            objout.b.y = 0;
            objout.c.x = objout.a.x + 1;
            objout.c.y = 1;
            objout.d.x = objout.a.x + 2;
            objout.d.y = 1;
            break;
        case 7:
            rp = rand()%6 +1;
            objout.e = 'S';
            objout.a.x = rp;
            objout.a.y =1;
            objout.b.x = objout.a.x+1;
            objout.b.y = 1;
            objout.c.x = objout.a.x + 1;
            objout.c.y = 0;
            objout.d.x = objout.a.x + 2;
            objout.d.y = 0;
            break;
    }
    return objout;
}
//Draws blocks on to the field
void dblocks(SDL_Surface *s,int t[sizey][sizex])
{
    int i,g;
     for(i=0;i<20;i++)
        {
            for(g = 0; g < 10; g++)
                {
                    if(t[i][g] == 1 || t[i][g] == 2)
                        {
                            boxRGBA(s,101+ g*21,26+i*21,119 +g*21,45+ i*21,0,0,255,255);
                        }
                    else if(t[i][g] == 0)
                        {
                            boxRGBA(s,101 +g*21,26 +i*21,119 +g*21,45 +i*21,0,0,0,255);
                        }
                }
        }
}
//Moves object down
obj downm(obj tetris)
{
    if(tetris.a.y < 19 && tetris.d.y < 19)
    {
        tetris.a.y += 1;
        tetris.b.y += 1;
        tetris.c.y += 1;
        tetris.d.y += 1;
    }
    return tetris;
}
//Downward cycle
obj down(int t[sizey][sizex], obj tetris)
{
    obj tmp;
    tmp = tetris;
    tetris = downm(tetris);
    removeobj(t,tmp);
    placeobj(t,tetris);
    return tetris;
}
// Moves object left
obj leftm(obj tetris)
{
    if(tetris.a.x > 0 && tetris.b.x > 0 && tetris.c.x > 0 && tetris.d.x > 0)
    {
        tetris.a.x -= 1;
        tetris.b.x -= 1;
        tetris.c.x -= 1;
        tetris.d.x -= 1;
    }
    return tetris;
}
//Leftward cycle
obj left(int t[sizey][sizex], obj tetris)
{
    obj tmp;
    tmp = tetris;
    tetris = leftm(tetris);
    removeobj(t,tmp);
    placeobj(t,tetris);
    return tetris;
}
// Moves object right
obj rightm(obj tetris)
{
    if(tetris.a.x < 9 && tetris.b.x < 9 && tetris.c.x < 9 && tetris.d.x < 9)
    {
        tetris.a.x += 1;
        tetris.b.x += 1;
        tetris.c.x += 1;
        tetris.d.x += 1;
    }
    return tetris;
}
//Rightward cycle
obj right(int t[sizey][sizex], obj tetris)
{
    obj tmp;
    tmp = tetris;
    tetris = rightm(tetris);
    removeobj(t,tmp);
    placeobj(t,tetris);
    return tetris;
}
//Moves object up
obj upm(obj tetris)
{
    tetris.a.y -= 1;
    tetris.b.y -= 1;
    tetris.c.y -= 1;
    tetris.d.y -= 1;
    return tetris;
}
//Upward cycle
obj up(int t[sizey][sizex], obj tetris)
{
    obj tmp;
    tmp = tetris;
    tetris = upm(tetris);
    removeobj(t,tmp);
    placeobj(t,tetris);
    return tetris;
}
//Determines the case of collision
bool lcollide(int t[sizey][sizex], obj tetris)
{
   obj nxt;
   nxt = leftm(tetris);
   if(t[nxt.a.y][nxt.a.x] == 2 || t[nxt.b.y][nxt.b.x] == 2 || t[nxt.c.y][nxt.c.x] == 2 || t[nxt.d.y][nxt.d.x] == 2 )
   {
       return true;
   }
   return false;
}
bool rcollide(int t[sizey][sizex], obj tetris)
{
   obj nxt;
   nxt = rightm(tetris);
   if(t[nxt.a.y][nxt.a.x] == 2 || t[nxt.b.y][nxt.b.x] == 2 || t[nxt.c.y][nxt.c.x] == 2 || t[nxt.d.y][nxt.d.x] == 2 )
   {
       return true;
   }
   return false;
}
bool dcollide(int t[sizey][sizex], obj tetris)
{
   obj nxt;
   nxt = downm(tetris);
   if(t[nxt.a.y][nxt.a.x] == 2 || t[nxt.b.y][nxt.b.x] == 2 || t[nxt.c.y][nxt.c.x] == 2 || t[nxt.d.y][nxt.d.x] == 2 )
   {
       return true;
   }
   return false;
}
//Drops object
obj dropm(int t[sizey][sizex], obj tetris)
{
    while(!dcollide(t,tetris) && tetris.a.y < 19 && tetris.d.y < 19)
    {
        tetris = downm(tetris);
    }
    return tetris;
}
//Dropmove cycle
obj drop(int t[sizey][sizex], obj tetris)
{
    obj tmp;
    tmp = tetris;
    tetris = dropm(t,tetris);
    removeobj(t,tmp);
    placeobj(t,tetris);
    return tetris;
}
//shifts blocks within object
obj shift(obj tetris)
{
    block tmp;
    tmp = tetris.a;
    tetris.a = tetris.d;
    tetris.d = tmp;
    tmp = tetris.b;
    tetris.b = tetris.c;
    tetris.c = tmp;
    return tetris;
}
//Upward left movment
block ulm(block a)
{
    a.x -= 1;
    a.y -= 1;
    return a;
}
//Upward right movement
block urm(block a)
{
    a.x += 1;
    a.y -= 1;
    return a;
}
//Downward left movement
block dlm(block a)
{
    a.x -= 1;
    a.y += 1;
    return a;
}
//Downward right movement
block drm(block a)
{
    a.x += 1;
    a.y += 1;
    return a;
}
//Rotates object left
obj lrotate(obj tetris)
{
    if('I' == tetris.e)
    {
        if(tetris.b.y < tetris.c.y)
        {
            tetris = shift(tetris);
        }
        if(tetris.b.y > tetris.c.y)
        {
            tetris.a = urm(tetris.a);
            tetris.c = dlm(tetris.c);
            tetris.d = dlm(dlm(tetris.d));
        }
        else if(tetris.b.y == tetris.c.y)
        {
            if(tetris.b.x > tetris.c.x)
            {
                tetris = shift(tetris);
            }
            if(tetris.b.x < tetris.c.x)
            {
                tetris.a = drm(tetris.a);
                tetris.c = ulm(tetris.c);
                tetris.d = ulm(ulm(tetris.d));
            }

        }
    }
    if(tetris.e == 'A')
    {
        if(tetris.b.y > tetris.c.y)
        {
            tetris.a = drm(tetris.a);
            tetris.c = dlm(tetris.c);
            tetris.d = ulm(tetris.d);
        }
        else if(tetris.b.x > tetris.c.x)
        {
            tetris.a = urm(tetris.a);
            tetris.c = drm(tetris.c);
            tetris.d = dlm(tetris.d);
        }
        else if(tetris.b.y < tetris.c.y)
        {
            tetris.a = ulm(tetris.a);
            tetris.c = urm(tetris.c);
            tetris.d = drm(tetris.d);
        }
        else if(tetris.b.x < tetris.c.x)
        {
            tetris.a = dlm(tetris.a);
            tetris.c = ulm(tetris.c);
            tetris.d = urm(tetris.d);
        }
    }
    if(tetris.e == 'L')
    {
        if(tetris.b.x < tetris.c.x)
        {
            tetris.a = drm(tetris.a);
            tetris.c = ulm(tetris.c);
            tetris.d.x -= 2;
        }
        else if(tetris.b.y > tetris.c.y)
        {
            tetris.a = urm(tetris.a);
            tetris.c = dlm(tetris.c);
            tetris.d.y += 2;
        }
        else if(tetris.b.x > tetris.c.x)
        {
            tetris.a = ulm(tetris.a);
            tetris.c = drm(tetris.c);
            tetris.d.x += 2;
        }
         else if(tetris.b.y < tetris.c.y)
        {
            tetris.a = dlm(tetris.a);
            tetris.c = urm(tetris.c);
            tetris.d.y -= 2;
        }
    }
    if(tetris.e == 'R')
    {
        if(tetris.b.x < tetris.c.x)
        {
            tetris.a.y += 2;
            tetris.b = drm(tetris.b);
            tetris.d = ulm(tetris.d);
        }
        else if(tetris.b.y > tetris.c.y)
        {
            tetris.a.x += 2;
            tetris.b = urm(tetris.b);
            tetris.d = dlm(tetris.d);
        }
        else if(tetris.b.x > tetris.c.x)
        {
            tetris.a.y -= 2;
            tetris.b = ulm(tetris.b);
            tetris.d = drm(tetris.d);
        }
        else if(tetris.b.y < tetris.c.y)
        {
            tetris.a.x -= 2;
            tetris.b = dlm(tetris.b);
            tetris.d = urm(tetris.d);
        }
    }
    if(tetris.e == 'Z')
    {
        if(tetris.b.y > tetris.c.y)
        {
            tetris = shift(tetris);
        }
        if(tetris.b.y < tetris.c.y)
        {
            tetris.a = drm(tetris.a);
            tetris.c = urm(tetris.c);
            tetris.d.y -= 2;
        }
        else{
            if(tetris.b.x > tetris.c.x)
        {
            tetris = shift(tetris);
        }
        if(tetris.b.x < tetris.c.x)
        {
            tetris.a = urm(tetris.a);
            tetris.c = ulm(tetris.c);
            tetris.d.x -= 2;
        }}
    }
    if(tetris.e == 'S')
    {
        if(tetris.b.y < tetris.c.y)
        {
            tetris = shift(tetris);
        }
        if(tetris.b.y > tetris.c.y)
        {
            tetris.a.x += 2;
            tetris.b = urm(tetris.b);
            tetris.d = ulm(tetris.d);
        }
        else{if(tetris.b.x < tetris.c.x)
        {
            tetris = shift(tetris);
        }
        if(tetris.b.x > tetris.c.x)
        {
            tetris.a.y -= 2;
            tetris.b = ulm(tetris.b);
            tetris.d = dlm(tetris.d);
        }}
    }
    return tetris;
}
//Leftward rotation cycle
obj lftr(int t[sizey][sizex], obj tetris)
{
    obj tmp;
    tmp = tetris;
    tetris = lrotate(tetris);
    removeobj(t,tmp);
    placeobj(t,tetris);
    return tetris;
}
//Determines collision for rotatation
bool rotcol(int t[sizey][sizex], obj tetris)
{
   obj nxt;
   nxt = lrotate(tetris);
   if(t[nxt.a.y][nxt.a.x] == 2 || t[nxt.b.y][nxt.b.x] == 2 || t[nxt.c.y][nxt.c.x] == 2 || t[nxt.d.y][nxt.d.x] == 2 )
   {
       return true;
   }
   if(nxt.a.y > 19 || nxt.b.y > 19 || nxt.c.y > 19 || nxt.d.y > 19)
   {
       return true;
   }
   if(nxt.a.x > 9 || nxt.b.x > 9 || nxt.c.x > 9 || nxt.d.x > 9)
   {
       return true;
   }
   if(nxt.a.x < 0 || nxt.b.x < 0 || nxt.c.x < 0 || nxt.d.x < 0)
   {
       return true;
   }
   return false;
}
//Checks what rows are full
void checkrow(int t[sizey][sizex], int r[sizey])
{
    int i,g,c;
    for(i = 0; i < 20; i++)
    {
        c =0;
        for(g = 0; g < 10; g++)
        {
            if(t[i][g] == 2)
            {
                c+=1;
            }
        }
        if(c == 10)
        {
            r[i] = 1;
        }
    }
}
//Checks if game is lost
bool checkloss(int t[sizey][sizex])
{
    int i;
    for(i = 0; i < sizex; i++)
    {
        if(t[1][i] == 2)
        {
            return true;
        }
    }
    return false;
}
//Clearing rows
void clrrow(int t[sizey][sizex], int r[sizey])
{
    int i,g;
    for(i = 0; i < 20; i++)
    {
        if(r[i] == 1)
        {
            for(g = 0; g < 10; g++)
            {
                t[i][g] = 0;
            }
        }
    }
}
//Pushes solidified blocsk down
void alldown(int t[sizey][sizex], int r[sizey])
{
    int i,g,j;
    for(i = 0; i < 20; i++)
    {
        if(r[i] == 1)
        {
            for(j = i; j > -1; j--)
            {
                for(g = 0; g < 10; g++)
                {
                    if(t[j][g] == 2 && t[j+1][g] == 0)
                    {
                        t[j][g] = 0;
                        t[j+1][g] = 2;
                    }
                }
            }
        }
    }
}
//Saves the state of the field
void solidify(int t[sizey][sizex], obj tetris)
{
    t[tetris.a.y][tetris.a.x] = 2;
    t[tetris.b.y][tetris.b.x] = 2;
    t[tetris.c.y][tetris.c.x] = 2;
    t[tetris.d.y][tetris.d.x] = 2;
}
//Zeros every rowindexnumber
void zerow(int r[sizey])
{
    int i;
    for(i = 0; i < 20; i++)
    {
        r[i] = 0;
    }
}
//Converts score into string
char* itoa(int value, char *result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}
//Counts gamescore
int cntscore(int r[sizey])
{
    int i,c,o;
    c = 0;
    o=0;
    for(i = 0; i< 20; i++)
    {
        if(r[i] == 1)
        {
            c +=1;
        }
    }
    if(c == 0)
    {
        return o;
    }
    else if(c == 1)
    {
        return o+c*10;
    }
    else if(c == 2)
    {
        return o+c*20;
    }
    else if(c == 3)
    {
        return o+c*30;
    }
    else if(c == 4)
    {
        return o+c*40;
    }
}
//Draws score
void dscore(int value, char *result, SDL_Surface *w,SDL_Surface *s,TTF_Font *font, SDL_Rect tpos, SDL_Color color)
{
    boxRGBA(s,352,72,399,99,255,0,0,255);
    itoa(value,result,10);
    print(font,result,color,w,s,tpos);
}












