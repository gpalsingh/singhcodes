#include <graphics.h>
#include "turtle.c"

void kochLine(turtle* t, int len, int iters){
    int part;
    
    part = len/3;
    
    if(iters <=1 ){
        makeLine(t, part);
        
        turnLeft(t, 60);
        makeLine(t, part);
        
        turnRight(t, 120);
        makeLine(t, part);
        
        turnLeft(t, 60);
        makeLine(t, part);
        
        return;
    }
    
    kochLine(t, part, iters-1);
        
    turnLeft(t, 60);
    kochLine(t, part, iters-1);
    
    turnRight(t, 120);
    kochLine(t, part, iters-1);
    
    turnLeft(t, 60);
    kochLine(t, part, iters-1);
}

void main(){
    turtle pica;
    int gd=DETECT, gm;
    
    initgraph(&gd, &gm, NULL);
    
    pica.angle = 0;
    pica.side = 1;
    
    //setcolor(RED);
    //setbkcolor(YELLOW);
    moveto(getmaxx()/2 - 100, 200);
    setlinestyle(SOLID_LINE, 0, 2);
    
    //experiment here
    //change pow(3, x) to change length
    //need powers of three to avoid mishaps when making 
    //multiple fractals
    //change last paramter to define recursion depth
    kochLine(&pica, pow(3,5), 4);
    turnRight(&pica, 90+30);
    kochLine(&pica, pow(3,5), 4);
    turnRight(&pica, 90+30);
    kochLine(&pica, pow(3,5), 4);
    
    delay(1000*10);
    closegraph();
}
