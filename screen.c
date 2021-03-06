#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

#define NUM_OF_OPTIONS 2

void initScreen(){
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
}

char startScreen(){
    int current = 0;
    int input = 0;
    while (1) {
    
        clear();
        mvprintw (0, 0, "Delver");
        mvprintw (2, 0, "New Game");
        mvprintw (3, 0, "Help");
        mvprintw (4, 0, "Exit");
        switch (current){
        case 0:
            mvprintw (2, 0, "->New Game");
            break;
    
        case 1:
            mvprintw (3, 0, "->Help");
            break;
    
        case 2:
            mvprintw (4, 0, "->Exit");
            break;
    
        default:
            break;
        }
        refresh();

        input = getch();
        if(input == '2') {
            current++;
            if (current > NUM_OF_OPTIONS) current = 0;
        }
        if(input == '8') {
            current--;
            if (current < 0) current = NUM_OF_OPTIONS;
        }
        if(input == '5') {
            if (current == 0) return 'n';
            if (current == 1) return 'h';
            if (current == 2) {
                endwin();
                return 'e';
            }
        }
    }
}

char creatorScreen(){
    int input;
    while (1) {
        clear();
        mvprintw(0, 0, "TODO");

        input = getch();
        if(input == '5') return 's';
    }
    
}

char helpScreen(){
    int input;
    while (1) {
        clear();
        mvprintw(0, 0, "TODO");

        input = getch();
        if(input == '5') return 's';
    }
    
}