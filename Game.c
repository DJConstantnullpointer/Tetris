#include "Game.h"

//Checks what rows are full
void checkrow(int **t, int r[sizey])
{
    int i,g,c;
    for(i = 0; i < sizey; i++)
    {
        c =0;
        for(g = 0; g < sizex; g++)
        {
            if(t[i][g] == 2)
            {
                c+=1;
            }
        }
        if(c == sizex)
        {
            r[i] = 1;
        }
    }
}
//Checks if game is lost
bool checkloss(int **t)
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
void clrrow(int **t, int r[sizey])
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
void alldown(int **t, int r[sizey])
{
    int i,g,j;
    for(i = 0; i < sizey; i++)
    {
        if(r[i] == 1)
        {
            for(j = i; j > -1; j--)
            {
                for(g = 0; g < sizex; g++)
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
void solidify(int **t, obj tetris)
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
    else// if(c == 4)
    {
        return o+c*40;
    }
}
//sets game speed
void setspeed(char *sp, int score)
{
    switch(*sp) {
    case 8:
        if (score> 200)
        {*sp = 7;}
        break;
    case 7:
        if(score> 400)
        {*sp = 6;}
        break;
    case 6:
        if(score> 800)
        {*sp = 5;}
        break;
    case 5:
        if(score> 1000)
        {*sp = 4;}
        break;
    case 4:
        if(score> 1200)
        {*sp= 3;}
        break;
    case 3:
        if(score> 1600)
        {*sp= 2;}
        break;
    case 2:
        if(score> 2000)
        {*sp= 1;}
        break;
    case 1:
        if(score> 2500)
        {*sp= 0;}
        break;}
}
//Cleans out field
void cleanfield(int **t)
{
    int i,g;
    for(i = 0; i < sizey; i++)
    {
        for(g = 0; g< sizex; g++)
        {
            t[i][g] = 0;
        }
    }
}
//Sets highscore
void seths(int *score, FILE *hs)
{
    int high=0;
    hs = fopen("hs.txt","wb+");
    fread(&high,sizeof(int),1,hs);
    if(*score > high)
    {
        high = *score;
        fseek(hs,0,SEEK_SET);
        fwrite(&high,sizeof(int),1,hs);
    }
    fclose(hs);
}
//Events in game
void reachdown(SDL_Surface *screen,int **field,obj *current, obj *nxt, obj *predict)
{
     removepred(field,*predict);
     solidify(field,*current);
     *current= *nxt;
     *nxt = genobj();
     *predict = dropm(field,*current);
     placepred(field,*predict);
     dnext(screen,*nxt);
     SDL_Flip(screen);
}
void stdevent(SDL_Surface *screen,txt *tx16,char sscore[10],int **field, int row[sizey], int *score, obj *predict,obj *current)
{
    checkrow(field,row);
    clrrow(field,row);
    alldown(field,row);
    removepred(field,*predict);
    *predict = dropm(field,*current);
    placepred(field,*predict);
    *score += cntscore(row);
    zerow(row);
    dscore(*score,sscore,screen,tx16);
    dblocks(screen, field);
    SDL_Flip(screen);
}
//Checks if field is empty
bool checkfield(int **field)
{
    int i,g;
    for(i = 0; i < sizey; i++)
    {
        for(g = 0; g < sizex; g++)
        {
            if(field[i][g] == 1 || field[i][g] == 1 )
            {
                return false;
            }
        }
    }
    return true;
}







