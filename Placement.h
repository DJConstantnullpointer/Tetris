#include "Datas.h"
#ifndef PLACEMENT_H_INCLUDED
#define PLACEMENT_H_INCLUDED

void place(int **t, block a);
void dis(int **t, block a);
obj genobj();
void placeobj(int **t, obj tetris);
void removeobj(int **t, obj tetris);
void placepred(int **t, obj pred);
void removepred(int **t, obj pred);


#endif // PLACEMENT_H_INCLUDED
