#include "Move.h"

//Moves object down
obj downm(obj tetris)
{
    if(tetris.a.y < sizey-1 && tetris.d.y < sizey-1)
    {
        tetris.a.y += 1;
        tetris.b.y += 1;
        tetris.c.y += 1;
        tetris.d.y += 1;
    }
    return tetris;
}
//Downward cycle
obj down(int **t,char **cl, obj tetris)
{
    obj tmp;
    tmp = tetris;
    tetris = downm(tetris);
    removeobj(t,cl,tmp);
    placeobj(t,cl,tetris);
    return tetris;
}
// Moves object left
obj leftm(obj tetris)
{
    if(tetris.a.x > 0 && tetris.b.x > 0 && tetris.c.x > 0 && tetris.d.x > 0)
    {
        tetris.a.x -= 1;
        tetris.b.x -= 1;
        tetris.c.x -= 1;
        tetris.d.x -= 1;
    }
    return tetris;
}
//Leftward cycle
obj left(int **t,char **cl, obj tetris)
{
    obj tmp;
    tmp = tetris;
    tetris = leftm(tetris);
    removeobj(t,cl,tmp);
    placeobj(t,cl,tetris);
    return tetris;
}
// Moves object right
obj rightm(obj tetris)
{
    if(tetris.a.x < sizex -1 && tetris.b.x < sizex -1 && tetris.c.x < sizex -1 && tetris.d.x < sizex -1)
    {
        tetris.a.x += 1;
        tetris.b.x += 1;
        tetris.c.x += 1;
        tetris.d.x += 1;
    }
    return tetris;
}
//Rightward cycle
obj right(int **t,char **cl, obj tetris)
{
    obj tmp;
    tmp = tetris;
    tetris = rightm(tetris);
    removeobj(t,cl,tmp);
    placeobj(t,cl,tetris);
    return tetris;
}
//Determines the case of collision
bool lcollide(int **t, obj tetris)
{
   obj nxt;
   nxt = leftm(tetris);
   if(nxt.a.x == -1 || nxt.d.x == -1 || nxt.c.x == -1 || nxt.a.x == -1)
   {
       return true;
   }
   else if(t[nxt.a.y][nxt.a.x] == 2 || t[nxt.b.y][nxt.b.x] == 2 || t[nxt.c.y][nxt.c.x] == 2 || t[nxt.d.y][nxt.d.x] == 2 )
   {
       return true;
   }
   return false;
}
bool rcollide(int **t, obj tetris)
{
   obj nxt;
   nxt = rightm(tetris);
   if(nxt.a.x == sizex || nxt.d.x == sizex || nxt.c.x == sizex || nxt.a.x == sizex)
   {
       return true;
   }
    else if(t[nxt.a.y][nxt.a.x] == 2 || t[nxt.b.y][nxt.b.x] == 2 || t[nxt.c.y][nxt.c.x] == 2 || t[nxt.d.y][nxt.d.x] == 2 )
   {
       return true;
   }
   return false;
}
bool dcollide(int **t, obj tetris)
{
   obj nxt;
   nxt = downm(tetris);
   if(nxt.a.y == sizey || nxt.d.y == sizey || nxt.c.y == sizey || nxt.a.y == sizey)
   {
       return true;
   }
   else if(t[nxt.a.y][nxt.a.x] == 2 || t[nxt.b.y][nxt.b.x] == 2 || t[nxt.c.y][nxt.c.x] == 2 || t[nxt.d.y][nxt.d.x] == 2 )
   {
       return true;
   }
   return false;
}
//Drops object
obj dropm(int **t, obj tetris)
{
    while(!dcollide(t,tetris) && tetris.a.y < sizey-1 && tetris.d.y < sizey-1)
    {
        tetris = downm(tetris);
    }
    return tetris;
}
//Moves prediction
obj predm(int **t, obj tetris,obj pred)
{
    removepred(t,pred);
    pred = dropm(t,tetris);
    placepred(t,pred);
    return pred;
}
//Dropmove cycle
obj drop(int **t,char **cl, obj tetris)
{
    obj tmp;
    tmp = tetris;
    tetris = dropm(t,tetris);
    removeobj(t,cl,tmp);
    placeobj(t,cl,tetris);
    return tetris;
}
//shifts blocks within object
obj shift(obj tetris)
{
    block tmp;
    tmp = tetris.a;
    tetris.a = tetris.d;
    tetris.d = tmp;
    tmp = tetris.b;
    tetris.b = tetris.c;
    tetris.c = tmp;
    return tetris;
}
//Upward left movment
block ulm(block a)
{
    a.x -= 1;
    a.y -= 1;
    return a;
}
//Upward right movement
block urm(block a)
{
    a.x += 1;
    a.y -= 1;
    return a;
}
//Downward left movement
block dlm(block a)
{
    a.x -= 1;
    a.y += 1;
    return a;
}
//Downward right movement
block drm(block a)
{
    a.x += 1;
    a.y += 1;
    return a;
}
//Rotates object left
obj lrotate(obj tetris)
{
    if('I' == tetris.e)
    {
        if(tetris.b.y < tetris.c.y)
        {
            tetris = shift(tetris);
        }
        if(tetris.b.y > tetris.c.y)
        {
            tetris.a = urm(tetris.a);
            tetris.c = dlm(tetris.c);
            tetris.d = dlm(dlm(tetris.d));
        }
        else if(tetris.b.y == tetris.c.y)
        {
            if(tetris.b.x > tetris.c.x)
            {
                tetris = shift(tetris);
            }
            if(tetris.b.x < tetris.c.x)
            {
                tetris.a = drm(tetris.a);
                tetris.c = ulm(tetris.c);
                tetris.d = ulm(ulm(tetris.d));
            }

        }
    }
    if(tetris.e == 'A')
    {
        if(tetris.b.y > tetris.c.y)
        {
            tetris.a = drm(tetris.a);
            tetris.c = dlm(tetris.c);
            tetris.d = ulm(tetris.d);
        }
        else if(tetris.b.x > tetris.c.x)
        {
            tetris.a = urm(tetris.a);
            tetris.c = drm(tetris.c);
            tetris.d = dlm(tetris.d);
        }
        else if(tetris.b.y < tetris.c.y)
        {
            tetris.a = ulm(tetris.a);
            tetris.c = urm(tetris.c);
            tetris.d = drm(tetris.d);
        }
        else if(tetris.b.x < tetris.c.x)
        {
            tetris.a = dlm(tetris.a);
            tetris.c = ulm(tetris.c);
            tetris.d = urm(tetris.d);
        }
    }
    if(tetris.e == 'L')
    {
        if(tetris.b.x < tetris.c.x)
        {
            tetris.a = drm(tetris.a);
            tetris.c = ulm(tetris.c);
            tetris.d.x -= 2;
        }
        else if(tetris.b.y > tetris.c.y)
        {
            tetris.a = urm(tetris.a);
            tetris.c = dlm(tetris.c);
            tetris.d.y += 2;
        }
        else if(tetris.b.x > tetris.c.x)
        {
            tetris.a = ulm(tetris.a);
            tetris.c = drm(tetris.c);
            tetris.d.x += 2;
        }
         else if(tetris.b.y < tetris.c.y)
        {
            tetris.a = dlm(tetris.a);
            tetris.c = urm(tetris.c);
            tetris.d.y -= 2;
        }
    }
    if(tetris.e == 'R')
    {
        if(tetris.b.x < tetris.c.x)
        {
            tetris.a.y += 2;
            tetris.b = drm(tetris.b);
            tetris.d = ulm(tetris.d);
        }
        else if(tetris.b.y > tetris.c.y)
        {
            tetris.a.x += 2;
            tetris.b = urm(tetris.b);
            tetris.d = dlm(tetris.d);
        }
        else if(tetris.b.x > tetris.c.x)
        {
            tetris.a.y -= 2;
            tetris.b = ulm(tetris.b);
            tetris.d = drm(tetris.d);
        }
        else if(tetris.b.y < tetris.c.y)
        {
            tetris.a.x -= 2;
            tetris.b = dlm(tetris.b);
            tetris.d = urm(tetris.d);
        }
    }
    if(tetris.e == 'Z')
    {
        if(tetris.b.y > tetris.c.y)
        {
            tetris = shift(tetris);
        }
        if(tetris.b.y < tetris.c.y)
        {
            tetris.a = drm(tetris.a);
            tetris.c = urm(tetris.c);
            tetris.d.y -= 2;
        }
        else{
            if(tetris.b.x > tetris.c.x)
        {
            tetris = shift(tetris);
        }
        if(tetris.b.x < tetris.c.x)
        {
            tetris.a = urm(tetris.a);
            tetris.c = ulm(tetris.c);
            tetris.d.x -= 2;
        }}
    }
    if(tetris.e == 'S')
    {
        if(tetris.b.y < tetris.c.y)
        {
            tetris = shift(tetris);
        }
        if(tetris.b.y > tetris.c.y)
        {
            tetris.a.x += 2;
            tetris.b = urm(tetris.b);
            tetris.d = ulm(tetris.d);
        }
        else{if(tetris.b.x < tetris.c.x)
        {
            tetris = shift(tetris);
        }
        if(tetris.b.x > tetris.c.x)
        {
            tetris.a.y -= 2;
            tetris.b = ulm(tetris.b);
            tetris.d = dlm(tetris.d);
        }}
    }
    return tetris;
}
//Leftward rotation cycle
obj lftr(int **t,char **cl, obj tetris)
{
    obj tmp;
    tmp = tetris;
    tetris = lrotate(tetris);
    removeobj(t,cl,tmp);
    placeobj(t,cl,tetris);
    return tetris;
}
//Determines collision for rotation
bool rotcol(int **t, obj tetris)
{
   obj nxt;
   nxt = lrotate(tetris);
   if(nxt.a.y > sizey-1 || nxt.b.y > sizey-1 || nxt.c.y > sizey-1 || nxt.d.y > sizey-1)
   {
       return true;
   }
   if(nxt.a.y < 0 || nxt.b.y < 0 || nxt.c.y < 0 || nxt.d.y < 0)
   {
       return true;
   }
   else if(nxt.a.x > sizex-1 || nxt.b.x > sizex-1 || nxt.c.x > sizex-1 || nxt.d.x > sizex-1)
   {
       return true;
   }
   else if(nxt.a.x < 0 || nxt.b.x < 0 || nxt.c.x < 0 || nxt.d.x < 0)
   {
       return true;
   }
   else if(t[nxt.a.y][nxt.a.x] == 2 || t[nxt.b.y][nxt.b.x] == 2 || t[nxt.c.y][nxt.c.x] == 2 || t[nxt.d.y][nxt.d.x] == 2 )
   {
       return true;
   }
   return false;
}
