#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED
#include "Datas.h"

void print(char* wd,SDL_Surface *s, txt *word);
void map(SDL_Surface *s);
void dblocks(SDL_Surface *s,int **t);
void dnext(SDL_Surface *s,obj nxt);
void settp(txt *wd, int x, int y, int w, int h);
void dpause(SDL_Surface *s, txt *p);
void dcontrolhelp(SDL_Surface *s, txt *words,int kx, int y, int ex,char* key, char* event);
void dcontrols(SDL_Surface *s, txt *tx88, txt *tx24, txt *tx16);
void dmenu(SDL_Surface *s, txt *tx108, txt *tx50);
void dscore(int value, char *result,SDL_Surface *s,txt *w);
void dhighscore(SDL_Surface *screen,int *score, char *sscore, txt *tx88, txt *tx50,txt *tx16, FILE *hs);

#endif // DRAW_H_INCLUDED
