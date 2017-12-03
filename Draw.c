#include "Draw.h"
//Basic writing operation
void print(char* wd,SDL_Surface *s, txt *word){
    word->w = TTF_RenderUTF8_Solid(word->font, wd, word->color);
    SDL_BlitSurface(word->w, NULL, s, &(word->tp));
}
//draws the playingfield
void map(SDL_Surface *s)
{
    /*int i;
    for(i= 100; i < 311; i += 21)
        {
            lineRGBA(s,i,25,i,445,255,255,255,255);
        }
    for(i = 25; i < 446; i += 21)
        {
            lineRGBA(s,100,i,310,i,255,255,255,255);
        }*/
    rectangleRGBA(s,100, 25,310,445,255,255,255,255);
    rectangleRGBA(s,330, 50,400,100,255,255,255,255);
    boxRGBA(s,331,51,399,99,255,0,0,255);
    rectangleRGBA(s,320,150,405,193,255,255,255,255);
}
//Draws menu
void dmenu(SDL_Surface *s, txt *tx108,txt *tx50)
{
    boxRGBA(s,0,0,410,470,0,0,0,255);
    settp(tx108,80,10,200,100);
    print("Tetris",s,tx108);
    rectangleRGBA(s,60,150,360,200,0,255,0,255);
    boxRGBA(s,61,151,359,199,153,0,0,255);
    settp(tx50,95,145,150,100);
    print("Start Game",s,tx50);
    rectangleRGBA(s,60,210,360,260,255,255,255,255);
    boxRGBA(s,61,211,359,259,153,0,0,255);
    settp(tx50,95,205,150,100);
    print("Load Game",s,tx50);
    rectangleRGBA(s,60,270,360,320,255,255,255,255);
    boxRGBA(s,61,271,359,319,153,0,0,255);
    settp(tx50,120,265,150,100);
    print("Controls",s,tx50);
    rectangleRGBA(s,60,330,360,380,255,255,255,255);
    boxRGBA(s,61,331,359,379,153,0,0,255);
    settp(tx50,100,325,150,100);
    print("High Score",s,tx50);
    rectangleRGBA(s,60,390,360,440,255,255,255,255);
    boxRGBA(s,61,391,359,439,153,0,0,255);
    settp(tx50,105,387,150,100);
    print("Exit Game",s,tx50);
}
//Draws blocks on to the field
void dblocks(SDL_Surface *s,int **t)
{
    int i,g;
     for(i=0;i<sizey;i++)
        {
            for(g = 0; g < sizex; g++)
                {
                    if(t[i][g] == 1 || t[i][g] == 2)
                    {
                        boxRGBA(s,101+ g*21,26+i*21,119 +g*21,45+ i*21,0,0,255,255);
                    }
                    else if(t[i][g] == 3)
                    {
                        boxRGBA(s,101 +g*21,26 +i*21,119 +g*21,45 +i*21,0,128,255,255);
                    }
                    else
                    {
                        boxRGBA(s,101 +g*21,26 +i*21,119 +g*21,45 +i*21,0,0,0,255);
                    }
                }
        }
}
//Draws next object
void dnext(SDL_Surface *s,obj nxt)
{
    boxRGBA(s,321,151,404,192,0,0,0,255);
    switch(nxt.e)
    {
    case 'I':
        boxRGBA(s,321,172,341,192,0,0,255,255);
        boxRGBA(s,342,172,362,192,0,0,255,255);
        boxRGBA(s,363,172,383,192,0,0,255,255);
        boxRGBA(s,384,172,404,192,0,0,255,255);
        break;
    case 'R':
        boxRGBA(s,321,172,341,192,0,0,255,255);
        boxRGBA(s,342,172,362,192,0,0,255,255);
        boxRGBA(s,363,172,383,192,0,0,255,255);
        boxRGBA(s,321,151,341,171,0,0,255,255);
        break;
    case 'L':
        boxRGBA(s,384,172,404,192,0,0,255,255);
        boxRGBA(s,342,172,362,192,0,0,255,255);
        boxRGBA(s,363,172,383,192,0,0,255,255);
        boxRGBA(s,384,151,404,171,0,0,255,255);
        break;
    case 'A':
        boxRGBA(s,321,172,341,192,0,0,255,255);
        boxRGBA(s,342,172,362,192,0,0,255,255);
        boxRGBA(s,363,172,383,192,0,0,255,255);
        boxRGBA(s,342,151,362,171,0,0,255,255);
        break;
    case 'O':
        boxRGBA(s,321,172,341,192,0,0,255,255);
        boxRGBA(s,342,172,362,192,0,0,255,255);
        boxRGBA(s,321,151,341,171,0,0,255,255);
        boxRGBA(s,342,151,362,171,0,0,255,255);
        break;
    case 'S':
        boxRGBA(s,363,151,383,171,0,0,255,255);
        boxRGBA(s,342,172,362,192,0,0,255,255);
        boxRGBA(s,363,172,383,192,0,0,255,255);
        boxRGBA(s,384,151,404,171,0,0,255,255);
        break;
    case 'Z':
        boxRGBA(s,321,151,341,171,0,0,255,255);
        boxRGBA(s,342,172,362,192,0,0,255,255);
        boxRGBA(s,363,172,383,192,0,0,255,255);
        boxRGBA(s,342,151,362,171,0,0,255,255);
        break;
    }
}
//Sets position of texts
void settp(txt *wd, int x, int y, int w, int h)
{
    wd->tp.x = x;
    wd->tp.y = y;
    wd->tp.w = w;
    wd->tp.h = h;
}
//Draws pause menu
void dpause(SDL_Surface *s, txt *p)
{
    //205;235
    rectangleRGBA(s,175,185,235,210,255,255,255,255);
    boxRGBA(s,176,186,234,209,153,0,0,255);
    settp(p,187,187,60,30);
    print("Pause",s,p);
    rectangleRGBA(s,145,215,265,240,0,255,0,255);
    boxRGBA(s,146,216,264,239,153,0,0,255);
    settp(p,172,217,60,30);
    print("Save game",s,p);
    rectangleRGBA(s,145,245,265,270,255,255,255,255);
    boxRGBA(s,146,246,264,269,153,0,0,255);
    settp(p,168,248,60,30);
    print("Exit to menu",s,p);
    settp(p,352,72,40,20);
}
//Helps control panel drawing
void dcontrolhelp(SDL_Surface *s, txt *words,int kx, int y, int ex, char* key, char* event)
{
    settp(words,kx,y,100,50);
    print(key,s,words);
    settp(words,ex,y,100,50);
    print(event,s,words);
}
//Draws the Control explanation panel
void dcontrols(SDL_Surface *s, txt *tx88, txt *tx24, txt *tx16)
{
    boxRGBA(s,0,0,410,470,0,0,0,255);
    settp(tx88,50,10,200,100);
    for(int i = 0; i < 6; i++)
    {
        lineRGBA(s,20,190 + 50*i,380,190 + 50*i,255,255,255,255);
    }
    print("Controls",s,tx88);
    dcontrolhelp(s,tx24,20,150,300,"Space","Pause");
    dcontrolhelp(s,tx24,50,200,300,"X","Drop");
    dcontrolhelp(s,tx24,20,250,300,"Up Arrow","Rotate");
    dcontrolhelp(s,tx24,20,300,250,"Down Arrow","Move Down");
    dcontrolhelp(s,tx24,20,350,250,"Left Arrow","Move Left");
    dcontrolhelp(s,tx24,20,400,250,"Right Arrow","Move Right");
    settp(tx16,120,120,100,50);
    print("Press space to menu",s,tx16);
}
//Draws score
void dscore(int value, char *result, SDL_Surface *s, txt *w)
{
    boxRGBA(s,352,72,399,99,255,0,0,255);
    sprintf(result, "%d", value);
    print(result,s,w);
}
//Draws highscore menu
void dhighscore(SDL_Surface *screen,int *score, char *sscore, txt *tx88, txt *tx50,txt *tx16, FILE *hs)
{
    boxRGBA(screen,0,0,410,470,0,0,0,255);
    settp(tx88,10,100,200,100);
    print("High Score",screen,tx88);
    hs = fopen("hs.txt","rb");
    fread(score,sizeof(int),1,hs);
    fclose(hs);
    sprintf(sscore,"%d",*score);
    settp(tx50,100,250,100,50);
    print(sscore,screen,tx50);
    settp(tx16,50,400,100,50);
    print("Press space to menu",screen,tx16);
    settp(tx16,250,400,100,50);
    print("Press x to reset score",screen,tx16);
    SDL_Flip(screen);
}

