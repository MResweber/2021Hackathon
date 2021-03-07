#include <stdio.h>
#include <stdlib.h>

#include "screen.h"

int main(int argc, char** argv) {
    char state = 's';
    initScreen();

    while(1) {
        switch (state){
        case 's':
            state = startScreen();
            break;
        
        case 'n': 
            state = creatorScreen();
            break;
        
        case 'h': 
            state = helpScreen();
            break;
        
        case 'g': 
            state = gameScreen();
            break;

        case 'e':
            exit(0);

        default:
            break;
        }
    }
}