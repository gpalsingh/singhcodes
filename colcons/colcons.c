#include<stdarg.h>

#define __max_colx__ getmaxx()
#define __max_coly__ getmaxy()

int __colx__ = 0;
int __coly__ = 0;

void resetColoredConsole(){
    cleardevice();
    __coly__ = 0;
    __colx__ = 0;
}

void Enter(){
    __colx__ = 0;
    __coly__ += textwidth("k");
    
    if( __coly__ >= __max_coly__ ){
        resetColoredConsole(); //easier than redrawing
    }
}

void moveCursor(){
    __colx__ += textheight("k");
    
    //can't draw too far to the right
    if( __colx__ >= __max_colx__ ){
        Enter();
    }
    
}

void putcolChar( char c ){
    static char t[2] = {' ', '\0'};  //avoided calls to sprintf
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

char* intToString( int a ){
    static char t[20], sign=' ';
    int i, j;
    
    if(a < 0){
        sign = '-';
        a *= -1;
    }
    
    for(i=19; (i>=0) && (a>0); i--, a/=10){
        t[i] = '0'+ (a%10);
    }   
    
    if(sign=='-'){
        t[0] = sign;
        j = 1;
    }else{
        j = 0;
    }
    
    i++;
    
    for(; (i<20) && (j<20); i++, j++){
        t[j] = t[i];
    }
    t[j] = '\0';
    
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
                sprintf(temp, "%f", va_arg(li, double));
                putString( temp );
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
