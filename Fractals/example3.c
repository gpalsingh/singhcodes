#include <graphics.h>
#include "turtle.c"

void fractalLine(turtle* t, int len, int iters){
    int part;
    
    part = len/3;
    
    if(iters <=1 ){
        makeLine(t, part);
    
        turnLeft(t, 90);
        makeLine(t, part);
        
        turnRight(t, 90);
        makeLine(t, part);
        
        turnRight(t, 90);
        makeLine(t, part);
        
        turnLeft(t, 90);
        makeLine(t, part);
        
        return;
    }
    
    //uncomment both lines to move inwards instead
    //mirrorTurtle(t);
    
    mirrorTurtle(t);
    fractalLine(t, part, iters-1);
    mirrorTurtle(t);
    
    turnLeft(t, 90);
    fractalLine(t, part, iters-1);
    
    turnRight(t, 90);
    mirrorTurtle(t);
    fractalLine(t, part, iters-1);
    mirrorTurtle(t);
    
    turnRight(t, 90);
    fractalLine(t, part, iters-1);
    
    turnLeft(t, 90);
    mirrorTurtle(t);
    fractalLine(t, part, iters-1);
    mirrorTurtle(t);
    
    //mirrorTurtle(t);
}

void main(){
    turtle pica;
    int gd=DETECT, gm;
    
    initgraph(&gd, &gm, NULL);
    
    pica.angle = 0;
    pica.side = 1;
    
    setcolor(GREEN);
    setbkcolor(WHITE);
    moveto(200, 100);
    setlinestyle(SOLID_LINE, 0, 2);
    
    
    //experiment here
    //change second argument to change length
    //need powers of three to avoid mishaps when making 
    //multiple fractals
    //change last paramter to define recursion depth
    fractalLine(&pica, pow(3,5), 4);
    /*turnRight(&pica, 90);
    fractalLine(&pica, pow(3,5), 4);
    turnRight(&pica, 90);
    fractalLine(&pica, pow(3,5), 4);
    turnRight(&pica, 90);
    fractalLine(&pica, pow(3,5), 4);*/
    
    delay(1000*10);
    closegraph();
}
