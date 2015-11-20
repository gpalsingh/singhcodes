#include<stdarg.h>

#define __max_colx__ getmaxx()
#define __max_coly__ getmaxy()

int __colx__ = 0;
int __coly__ = 0;

void putcolChar( char c );

void resetColoredConsole(){
    cleardevice();
    __coly__ = 0;
    __colx__ = 0;
}

void Enter(){
    putcolChar('\0');
    __colx__ = 0;
    __coly__ += textwidth("k");
    
    if( __coly__ >= __max_coly__ ){
        resetColoredConsole(); //easier than redrawing
    }
}

void moveCursor(){
    __colx__ += textheight("k");
    
    //can't draw too far to the right
    if( __colx__ == __max_colx__-3 ){
        Enter();
    }
    
}

void putcolChar( char c ){
    static char t[2] = {' ', '\0'}; 
    t[0] = c;
    outtextxy(__colx__, __coly__, t);
    moveCursor();
}

void putString( char* st ){
    int i;

    for(i=0; st[i]!='\0'; i++){
        putcolChar( st[i] );
    }
}

char* doubleToString( int a ){
    static char t[50], sign=' ';
    int i,j;
    double mantissa = a%1;
    
    if(a < 0){
        sign = '-';
        a *= 1.0;
    }
    
    a -= mantissa;
    
    for(i=49; a>1; i--, a/=10.0){
        t[i] = '0' + (int)(a%10);
    }
    
    if(sign == '-'){
        t[0] = sign;
        j = 1;
    }else{
        j = 0;
    }
    
    for(++i; i<50; i++, j++){
        t[j] = t[i];
    }
    
    t[j] = '.';
    
    for(++j, i=0; i<4; i++, j++){
        mantissa *= 10.0;
        t[j] = (int)mantissa;
        mantissa = mantissa % 1;
    }
    
    t[j] = '\0';
    
    return t;
}

char* intToString( int a ){
    static char t[20], sign=' ';
    int i, j;
    
    //save sign
    if(a < 0){
        sign = '-';
        a *= -1;
    }
    
    //store in reverse order
    for(i=19; (i>=0) && (a>0); i--, a/=10){
        t[i] = '0'+ (a%10);
    }   
    
    //put sign
    if(sign=='-'){
        t[0] = sign;
        j = 1;
    }else{
        j = 0;
    }
    
    //put number in front
    for(++i; (i<20) && (j<20); i++, j++){
        t[j] = t[i];
    }
    //make a valid string
    t[j] = '\0';
    
    //done :)
    return t;
}

void colprintf(char *fmt, ...){
    va_list li;
    int i, dcolor;
    
    int t;
    char *temp;
    
    dcolor = getcolor();    //save default colour's value
    
    va_start(li, fmt);  
    
    for(i=0; fmt[i]!='\0'; i++){
        if(fmt[i]!='%'){    
            //normal character
            putcolChar( fmt[i] );  
            continue;
        }
        //we found a format specifier
        //increment i to get it
        i += 1;
        
        //make sure string is correctly formatted
        if(fmt[i] == '\0'){
            break;
        }
        
        switch(fmt[i]){
            case 'c':   //character
                putcolChar( va_arg(li, int) );
                break;
                
            case 'd':   //integer
                putString( intToString(va_arg(li, int)) );
                break;
                
            case 'f':   //float, similar to above
                putString( doubleToString(va_arg(li, double)) );
                break;
                
            case 's':   //string
                putString( va_arg(li, char*) );
                break;
                
            case 'Z':   //a color argument
                setcolor( va_arg(li, int) ); 
                break;
                
            default:
                //do nothing
                break;
        }
        
    }
    
    //cleanup code
    putcolChar('\0');
    setcolor(dcolor);
    va_end(li);
    return;
}
