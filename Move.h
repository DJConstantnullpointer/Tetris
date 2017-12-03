#include "Placement.h"
#include <stdbool.h>
#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

obj downm(obj tetris);
obj down(int **t, obj tetris);
obj leftm(obj tetris);
obj left(int **t, obj tetris);
obj rightm(obj tetris);
obj right(int **t, obj tetris);
bool lcollide(int **t, obj tetris);
bool rcollide(int **t, obj tetris);
bool dcollide(int **t, obj tetris);
obj dropm(int **t, obj tetris);
obj drop(int **t, obj tetris);
obj predm(int **t, obj tetris,obj pred);
obj shift(obj tetris);
block ulm(block a);
block urm(block a);
block dlm(block a);
block drm(block a);
obj lrotate(obj tetris);
obj lftr(int **t, obj tetris);
bool rotcol(int **t, obj tetris);


#endif // MOVE_H_INCLUDED
