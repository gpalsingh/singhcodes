#include <graphics.h>
#include "turtle.c"

void sierpinski(turtle* t, int len, int iters){
    int part;
    
    part = len/3;
    
    if(iters <=1 ){
        turnLeft(t, 60);
        makeLine(t, part);
        
        turnRight(t, 60);
        makeLine(t, part);
        
        turnRight(t, 60);
        makeLine(t, part);
        
        turnLeft(t, 60);
        return;
    }
    
    turnLeft(t, 60);
    mirrorTurtle(t);
    sierpinski(t, part, iters-1);
    mirrorTurtle(t);
    
    turnRight(t, 60);
    sierpinski(t, part, iters-1);
    
    turnRight(t, 60);
    mirrorTurtle(t);
    sierpinski(t, part, iters-1);
    mirrorTurtle(t);
    
    turnLeft(t, 60);
}

void main(){
    turtle pica;
    int gd=DETECT, gm;
    
    initgraph(&gd, &gm, NULL);
    
    pica.angle = 0;
    pica.side = 1;
    
    setcolor(BLUE);
    setbkcolor(WHITE);
    moveto(getmaxx()/2 - 150, 360);
    setlinestyle(SOLID_LINE, 0, 2);
    
    //experiment here
    //change second argument to change length
    //need powers of three to avoid mishaps when making 
    //multiple fractals
    //change last paramter to define recursion depth
    sierpinski(&pica, 3800, 6);
    
    delay(1000*10);
    closegraph();
}
