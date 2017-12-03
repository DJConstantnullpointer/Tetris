#include "Placement.h"

//places blocks into the grid
void place(int **t,block a)
{
   t[a.y][a.x] = 1;
}
//Removes blocks from grid
void dis(int **t, block a)
{
    t[a.y][a.x] = 0;
}
//Places objects into the grid
void placeobj(int **t, obj tetris)
{
    place(t,tetris.a);
    place(t,tetris.b);
    place(t,tetris.c);
    place(t,tetris.d);
}
//Removes object from the grid
void removeobj(int **t, obj tetris)
{
    dis(t,tetris.a);
    dis(t,tetris.b);
    dis(t,tetris.c);
    dis(t,tetris.d);
}
//Places prediction on the field
void placepred(int **t, obj pred)
{
    t[pred.a.y][pred.a.x] = 3;
    t[pred.b.y][pred.b.x] = 3;
    t[pred.c.y][pred.c.x] = 3;
    t[pred.d.y][pred.d.x] = 3;
}
//REmoves prediction on the field
void removepred(int **t, obj pred)
{
    t[pred.a.y][pred.a.x] = 0;
    t[pred.b.y][pred.b.x] = 0;
    t[pred.c.y][pred.c.x] = 0;
    t[pred.d.y][pred.d.x] = 0;
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

