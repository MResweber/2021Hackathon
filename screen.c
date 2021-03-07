#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "mapFactory.h"
#include "game.h"

#define MAP_SIZE 20

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
        if(input == '2') {
            current++;
            if (current > 2) current = 0;
        }
        if(input == '8') {
            current--;
            if (current < 0) current = 2;
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
    WINDOW *cWin;
    cWin = newwin(50, 50, 0, 0);
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
            initGame(p, MAP_SIZE, MAP_SIZE);
            delwin(cWin);
            return 'g';
        }
        else if((input == '4' || input == '6') && current == 0) current = 1;
        else if((input == '4' || input == '6') && current == 1) current = 0;
    }
    
}

char helpScreen(){
    WINDOW *hWin;
    hWin = newwin(50, 50, 0, 0);
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
        gWin = newwin(50, 50, 0, 0);
        char ***map = getMap();
        wclear(gWin);

        for(int y = 0; y < MAP_SIZE; y++) {
            for(int x = 0; x < MAP_SIZE; x++){
                int color = atoi(&map[y][x][1]);
                wattron(gWin, COLOR_PAIR(color));
                mvwprintw(gWin, y, x, &map[y][x][0]);
                wattroff(gWin, COLOR_PAIR(color));
            }
        }
        int *playerPos = getPlayerPos();
        mvwprintw(gWin, playerPos[1], playerPos[0], "@");
        wrefresh(gWin);

        int input = wgetch(gWin);
        if (input == '5') {
            delwin(gWin);
            return 's';
        }
    }
}