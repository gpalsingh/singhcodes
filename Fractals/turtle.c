#include <math.h>

struct T{
    double angle;
    int side;
};

typedef struct T turtle;

double toRadians( double angle ){   //sin() needs radians
    return (angle * M_PI) / 180.0;
}

double setAngle( turtle* t, double angle ){
    t->angle = angle;
}

double turnLeft( turtle* t, double angle ){
    double new_angle;
    
    new_angle = t->side * angle;
    
    setAngle(t, t->angle - toRadians(new_angle));
}

double turnRight( turtle* t, double angle ){
    turnLeft(t, -angle);
}

void makeLine( turtle* t, int len ){
    int x,y;
    
    x = len * cos(t->angle);
    y = len * sin(t->angle);
    
    linerel(x,y);
}

void mirrorTurtle( turtle* t ){
    t->side *= -1;
}
