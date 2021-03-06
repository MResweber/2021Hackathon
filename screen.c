#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>

#define NUM_OF_OPTIONS 2

void initScreen(){
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
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
            attron(COLOR_PAIR(1));
            mvprintw (2, 0, "New Game");
            attroff(COLOR_PAIR(1));
            break;
    
        case 1:
            attron(COLOR_PAIR(1));
            mvprintw (3, 0, "Help");
            attroff(COLOR_PAIR(1));
            break;
    
        case 2:
            attron(COLOR_PAIR(1));
            mvprintw (4, 0, "Exit");
            attroff(COLOR_PAIR(1));
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
    int current = 0;
    while (1) {
        clear();
        mvprintw(0, 0, "TODO Creator Screen");
        mvprintw(2, 0, "Back");
        mvprintw(2, 5, "Play");

        attron(COLOR_PAIR(1));
        if(current == 0) mvprintw(2, 0, "Back");
        else mvprintw(2, 5, "Play");
        attroff(COLOR_PAIR(1));

        input = getch();
        if(input == '5' && current == 0) return 's';
        else if(input == '5' && current == 1) return 'g';
        else if((input == '4' || input == '6') && current == 0) current = 1;
        else if((input == '4' || input == '6') && current == 1) current = 0;
    }
    
}

char helpScreen(){
    int input;
    while (1) {
        clear();
        mvprintw(0, 0, "TODO Tutorial");

        input = getch();
        if(input == '5') return 's';
    }
    
}