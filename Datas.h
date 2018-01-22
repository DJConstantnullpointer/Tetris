#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#ifndef DATAS_H_INCLUDED
#define DATAS_H_INCLUDED
#define sizex 10
#define sizey 20
static const char *Tetristheme = "Tetristheme.mp3";

//Structures
typedef struct block {int x,y;} block;
typedef struct obj {block a,b,c,d; char e;} obj;
typedef struct txt {SDL_Surface *w; TTF_Font *font; SDL_Rect tp; SDL_Color color;} txt;

#endif // DATAS_H_INCLUDED
