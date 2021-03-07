#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#include "mapFactory.h"
#include "game.h"

#define MAP_SIZE_X 1000
#define MAP_SIZE_Y 500
#define WINDOW_X 100
#define WINDOW_Y 25

void createColors(){
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
}

void initScreen(){
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    start_color();
    createColors();
    keypad(stdscr, TRUE);
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

        attron(COLOR_PAIR(2));
        if(current == 0) mvprintw (2, 0, "New Game");
        else if(current == 1) mvprintw (3, 0, "Help");
        else if (current == 2) mvprintw (4, 0, "Exit");
        attroff(COLOR_PAIR(2));

        refresh();

        input = getch();
        if(input == '2' || input == KEY_DOWN) {
            current++;
            if (current > 2) current = 0;
        }
        if(input == '8'|| input == KEY_UP) {
            current--;
            if (current < 0) current = 2;
        }
        if(input == '5' || input == KEY_ENTER) {
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
    WINDOW *cWin;
    cWin = newwin(WINDOW_Y, WINDOW_X, 0, 0);
    int input;
    int current = 0;
    while (1) {
        wclear(cWin);
        mvwprintw(cWin, 0, 0, "TODO Creator Screen");
        mvwprintw(cWin, 2, 0, "Back");
        mvwprintw(cWin, 2, 5, "Play");

        wattron(cWin, COLOR_PAIR(2));
        if(current == 0) mvwprintw(cWin, 2, 0, "Back");
        else mvwprintw(cWin, 2, 5, "Play");
        wattroff(cWin, COLOR_PAIR(2));

        wrefresh(cWin);

        input = wgetch(cWin);
        if(input == '5' && current == 0) {
            delwin(cWin);
            return 's';
        }
        else if(input == '5' && current == 1) {
            player *p = malloc(sizeof(player));
            p->hp = 10;
            p->sta = 10;
            initGame(p, MAP_SIZE_X, MAP_SIZE_Y);
            delwin(cWin);
            return 'g';
        }
        else if((input == '4' || input == '6') && current == 0) current = 1;
        else if((input == '4' || input == '6') && current == 1) current = 0;
    }
    
}

char helpScreen(){
    WINDOW *hWin;
    hWin = newwin(WINDOW_Y, WINDOW_X, 0, 0);
    int input;
    while (1) {
        wclear(hWin);
        mvwprintw(hWin, 0, 0, "TODO Tutorial");
        wrefresh(hWin);

        input = wgetch(hWin);
        if(input == '5') {
            delwin(hWin);
            return 's';
        }
    }
    
}

char gameScreen(){
    while(1){
        WINDOW *gWin;
        gWin = newwin(WINDOW_Y, WINDOW_X, 0, 0);
        unsigned char **map = getMap();
        int *playerPos = getPlayerPos();
        wclear(gWin);

        for(int y = 0; y < MAP_SIZE_Y; y++) {
            for(int x = 0; x < MAP_SIZE_X; x++){
                int color[2];
                char *tile = getTile(map[y][x], color);
                wattron(gWin, COLOR_PAIR(color[0]));
                mvwprintw(gWin, y, x, tile);
                wattroff(gWin, COLOR_PAIR(color[0]));
            }
        }
        mvwprintw(gWin, playerPos[1], playerPos[0], "@");
        wrefresh(gWin);

        int input = wgetch(gWin);
        if (input == '5') {
            delwin(gWin);
            return 's';
        }
        else if (input == '2') pMove(0, 1);   // down
        else if (input == '3') pMove(1, 1);   // down right
        else if (input == '1') pMove(-1, 1);  // down left
        else if (input == '8') pMove(0, -1);  // up
        else if (input == '9') pMove(1, -1);  // up right
        else if (input == '7') pMove(-1, -1); // up left
        else if (input == '6') pMove(1, 0);   // right
        else if (input == '4') pMove(-1, 0);  // left
    }
}