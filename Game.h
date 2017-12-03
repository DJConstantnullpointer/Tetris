#include "Move.h"
#include "Draw.h"
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

void checkrow(int **t, int r[sizey]);
bool checkloss(int **t);
void clrrow(int **t, int r[sizey]);
void alldown(int **t, int r[sizey]);
void solidify(int **t, obj tetris);
void zerow(int r[sizey]);
int cntscore(int r[sizey]);
void setspeed(char *sp, int score);
void cleanfield(int **t);
void seths(int *score, FILE *hs);
void reachdown(SDL_Surface *screen,int **field,obj *current, obj *nxt, obj *predict);
void stdevent(SDL_Surface *screen,txt *tx16,char sscore [10],int **field, int row[sizey], int *score, obj *predict,obj *current);
bool checkfield(int **field);

#endif // GAME_H_INCLUDED
