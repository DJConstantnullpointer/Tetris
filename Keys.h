#ifndef KEYS_H_INCLUDED
#define KEYS_H_INCLUDED
#include "Game.h"
void kdowng(SDL_Surface *screen, obj *current, obj *predict, int **field,char** cfield);
void kdownp(SDL_Surface *screen,int *cursor);
void kdownm(SDL_Surface *screen,int *cursor);
void kleftg(SDL_Surface *screen, obj *current, obj *predict, int **field,char** cfield);
void krightg(SDL_Surface *screen, obj *current, obj *predict, int **field,char** cfield);
void kupg(SDL_Surface *screen, obj *current, obj *predict, int **field,char** cfield);
void kupp(SDL_Surface *screen,int *cursor);
void kupm(SDL_Surface *screen,int *cursor);
void kenterg(SDL_Surface *screen, bool *play, bool *pause,int *cursor,txt *tx108,txt *tx50,txt *tx16,int **field,char** cfield,
             FILE *save, obj *current, obj *nxt,obj *predict,int *score);
void kenterm(SDL_Surface *screen, bool *play,bool *quit,bool *ctrlscreen,bool *hsscreen,txt *tx88,txt *tx50,txt *tx24, txt *tx16,
             int **field,char** cfield,obj *current, obj *nxt, obj *predict,int *score,char sscore [10], int *cursor,FILE *save,FILE *hs,Mix_Music *music);

#endif // KEYS_H_INCLUDED
