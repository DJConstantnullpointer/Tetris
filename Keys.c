#include "Keys.h"

//Down key instructions
void kdowng(SDL_Surface *screen, obj *current, obj *predict, int **field)
{
    *current = down(field, *current);
    *predict = predm(field,*current,*predict);
    dblocks(screen, field);
    SDL_Flip(screen);
}
void kdownp(SDL_Surface *screen,int *cursor)
{
    rectangleRGBA(screen,146,215 + 30*(*cursor),265,240 + 30*(*cursor),255,255,255,255);
    *cursor += 1;
    rectangleRGBA(screen,146,215 + 30*(*cursor),265,240 + 30*(*cursor),0,255,0,255);
    SDL_Flip(screen);
}
void kdownm(SDL_Surface *screen,int *cursor)
{
    rectangleRGBA(screen,60,150 + 60*(*cursor),360,200+ 60*(*cursor),255,255,255,255);
    *cursor += 1;
    rectangleRGBA(screen,60,150 + 60*(*cursor),360,200+ 60*(*cursor),0,255,0,255);
    SDL_Flip(screen);
}
//Left key instructions
void kleftg(SDL_Surface *screen, obj *current, obj *predict, int **field)
{
    *current = left(field, *current);
    *predict = predm(field,*current,*predict);
    dblocks(screen, field);
    SDL_Flip(screen);
}
//Right key instructions
void krightg(SDL_Surface *screen, obj *current, obj *predict, int **field)
{
    *current = right(field, *current);
    *predict = predm(field,*current,*predict);
    dblocks(screen, field);
    SDL_Flip(screen);
}
//Up key insturctions
void kupg(SDL_Surface *screen, obj *current, obj *predict, int **field)
{
    *current = lftr(field, *current);
    *predict = predm(field,*current,*predict);
    dblocks(screen, field);
    SDL_Flip(screen);
}
void kupp(SDL_Surface *screen,int *cursor)
{
    rectangleRGBA(screen,146,215 + 30*(*cursor),265,240 + 30*(*cursor),255,255,255,255);
    *cursor -= 1;
    rectangleRGBA(screen,146,215 + 30*(*cursor),265,240 + 30*(*cursor),0,255,0,255);
    SDL_Flip(screen);
}
void kupm(SDL_Surface *screen,int *cursor)
{
    rectangleRGBA(screen,60,150 + 60*(*cursor),360,200+ 60*(*cursor),255,255,255,255);
    *cursor -= 1;
    rectangleRGBA(screen,60,150 + 60*(*cursor),360,200+ 60*(*cursor),0,255,0,255);
    SDL_Flip(screen);
}
//Enter key instructions
void kenterg(SDL_Surface *screen, bool *play, bool *pause,int *cursor,txt *tx108,txt *tx50,txt *tx16,
             int **field,FILE *save, obj *current, obj *nxt,obj *predict,int *score)
{
    switch(*cursor)
    {
    case 0:
        save = fopen("savegame.txt","wb");
        fwrite(score,sizeof(int),1,save);
        fwrite(current,sizeof(obj),1,save);
        fwrite(nxt,sizeof(obj),1,save);
        fwrite(predict,sizeof(obj),1,save);
        for(int i = 0; i < sizey; i++)
        {
            fwrite(field[i],sizeof(int),10,save);
        }
        fclose(save);
        settp(tx16,0,0,40,20);
        print("Game saved",screen,tx16);
        settp(tx16,332,52,40,20);
        SDL_Flip(screen);
        break;
    case 1:
        *play = false;
        boxRGBA(screen,0,0,410,470,0,0,0,255);
        dmenu(screen,tx108,tx50);
        SDL_Flip(screen);
        *cursor = 0;
        *pause = false;
        cleanfield(field);
        break;
    }
}
void kenterm(SDL_Surface *screen, bool *play,bool *quit,bool *ctrlscreen,bool *hsscreen,txt *tx88,txt *tx50,txt *tx24, txt *tx16,
             int **field,obj *current, obj *nxt, obj *predict,int *score, char sscore [10], int *cursor, FILE *save,FILE *hs)
{
    switch(*cursor)
    {
    case 0:
        *play = true;
        boxRGBA(screen,0,0,410,470,0,0,0,255);
        map(screen);
        settp(tx16,332,52,40,20);
        print("Score:", screen,tx16);
        settp(tx16,352,72,40,20);
        print(sscore,screen,tx16);
        *current = genobj();
        *nxt = genobj();
        *predict = dropm(field,*current);
        placepred(field,*predict);
        placeobj(field,*current);
        dblocks(screen,field);
        dnext(screen,*nxt);
        SDL_Flip(screen);
        break;
    case 1:
        save = fopen("savegame.txt","rb");
        if (save == NULL) {break;}
        else{
        fread(score,sizeof(int),1,save);
        fread(current,sizeof(obj),1,save);
        fread(nxt,sizeof(obj),1,save);
        fread(predict,sizeof(obj),1,save);
        for(int i = 0; i < sizey; i++)
        {
            fread(field[i],sizeof(int),10,save);
        }
        fclose(save);
            if (!checkfield(field)) {
                *play = true;
                boxRGBA(screen, 0, 0, 410, 470, 0, 0, 0, 255);
                map(screen);
                settp(tx16, 332, 52, 40, 20);
                print("Score:", screen, tx16);
                settp(tx16, 352, 72, 40, 20);
                sprintf(sscore, "%d", *score);
                print(sscore, screen, tx16);
                removepred(field, *predict);
                *predict = dropm(field, *current);
                placepred(field, *predict);
                dblocks(screen, field);
                dnext(screen, *nxt);
                SDL_Flip(screen);
                break;
            } else break;
        }
        case 2:
        dcontrols(screen,tx88,tx24,tx16);
        *ctrlscreen = true;
        *cursor = 0;
        break;
    case 3:
        dhighscore(screen,score,sscore,tx88,tx50,tx16,hs);
        *hsscreen = true;
        *cursor = 0;
        break;
    case 4:
        *quit = true;
        break;
    }
}

