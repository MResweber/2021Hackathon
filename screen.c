//Input and Output

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#include "screen.h"
#include "game.h"
#include "text.h"

#define MAP_SIZE_X 150
#define MAP_SIZE_Y 50
#define WINDOW_X 75     // should alwats be odd
#define WINDOW_Y 25 

int turnCount = 0;

// The main argument works by switching between states. Each screen handles any input or output
// within the function, but if it needs to change which screen it is on then it just returns
// the char corresponding to the screen it wants.
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
        
        case 'v': 
            state = victoryScreen();
            break;

        case 'e':
            exit(0);

        default:
            break;
        }
    }
}

// Initializes color pairs used by program
void createColors(){
    init_color(COLOR_GREEN, 0, 300, 0);
    init_pair(1, COLOR_BLACK, COLOR_BLACK); // Unused
    init_pair(2, COLOR_BLACK, COLOR_WHITE); // Highlight
    init_pair(3, COLOR_GREEN, COLOR_GREEN); // Undergrowth
    init_pair(4, COLOR_BLUE, COLOR_BLUE);   // Water
    init_pair(5, COLOR_WHITE, COLOR_BLACK); // Adventurer
    init_pair(6, COLOR_RED, COLOR_BLACK);   // non-highfived wizards and dragons
    init_pair(7, COLOR_CYAN, COLOR_BLACK);  // highfived wizards
}

// Initalizes setting for curses
void initScreen(){
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    start_color();
    createColors();
    keypad(stdscr, TRUE);
}

// The first screen the user sees. New game starts a new game, help shows a bad tutorial, 
// and exit leaves the program.
char startScreen(){
    int current = 0;
    int input = 0;
    while (1) {
    
        clear();
        mvprintw (0, 0, "The Forest of Iliath");
        mvprintw (2, 0, "New Game");
        mvprintw (3, 0, "Help");
        mvprintw (4, 0, "Exit");
        mvprintw (6, 0, "Use either arrow keys or num pad to move and either z or 5 to select.");

        attron(COLOR_PAIR(2));
        if(current == 0) mvprintw (2, 0, "New Game");
        else if(current == 1) mvprintw (3, 0, "Help");
        else if (current == 2) mvprintw (4, 0, "Exit");
        attroff(COLOR_PAIR(2));

        refresh();

        input = getch();
        if(input == '2' || input == KEY_DOWN) { // Move selection
            current++;
            if (current > 2) current = 0;
        }
        if(input == '8'|| input == KEY_UP) {    // Move selection
            current--;
            if (current < 0) current = 2;
        }
        if(input == '5' || input == 'z') {      // Select
            if (current == 0) return 'n';       // New game
            if (current == 1) return 'h';       // Help
            if (current == 2) {                 // Exit program
                endwin();
                return 'e';
            }
        }
    }
}

// Introduces the game, back returns to menu and play starts the game proper
char creatorScreen(){
    WINDOW *cWin;
    cWin = newwin(WINDOW_Y, WINDOW_X, 0, 0);
    int input;
    int current = 0;
    while (1) {
        wclear(cWin);
        mvwprintw(cWin, 0, 0, INTRO);
        mvwprintw(cWin, 6, 0, "Back");
        mvwprintw(cWin, 6, 5, "Play");

        // Highlight selected option
        wattron(cWin, COLOR_PAIR(2));
        if(current == 0) mvwprintw(cWin, 6, 0, "Back");
        else mvwprintw(cWin, 6, 5, "Play");
        wattroff(cWin, COLOR_PAIR(2));

        wrefresh(cWin);

        input = wgetch(cWin);
        if(input == '5' && current == 0) {      // Return to startmenu
            delwin(cWin);
            return 's';
        }
        else if(input == '5' && current == 1) { // Start game proper
            initGame(MAP_SIZE_X, MAP_SIZE_Y);
            delwin(cWin);
            return 'g';
        }
        // Change selection
        else if((input == '4' || input == '6') && current == 0) current = 1;
        else if((input == '4' || input == '6') && current == 1) current = 0;
    }
    
}

// Provides a tutorial on how to play
char helpScreen(){
    WINDOW *hWin;
    hWin = newwin(WINDOW_Y, WINDOW_X, 0, 0);
    int input;
    while (1) {
        wclear(hWin);
        mvwprintw(hWin, 0, 0, TUTORIAL);
        wrefresh(hWin);

        input = wgetch(hWin);
        if(input == '5' || input == 'z') { // Return to start
            delwin(hWin);
            return 's';
        }
    }
    
}

// This is the screen that the game is played on. 
char gameScreen(){
    char *msg = "";
    turnCount = 0;
    int numWiz = 3;
    WINDOW *gWin;
    gWin = newwin(WINDOW_Y, WINDOW_X, 0, 0);
    WINDOW *tWin;
    tWin = newwin(WINDOW_Y+5, WINDOW_X, WINDOW_Y+1, 0);

    // Loops until user quits or game is complete
    while(1){
        // creating some variables for the screen
        unsigned char **map = getMap();
        int playerPos[2];
        getPos(0, playerPos);
        int top = 0, bottom = WINDOW_Y, left = 0, right = WINDOW_X;
        int topDif = 0, bottomDif = 0, leftDif = 0, rightDif = 0;

        // Calculates borders of the screen and the offset if needed
        int yIncrement = (WINDOW_Y - 1) / 2;
        top = playerPos[1] - yIncrement;
        if(top < 0) {
            topDif = top;
            top = 0;
        }
        bottom = playerPos[1] + yIncrement;
        if(bottom > MAP_SIZE_Y) {
            bottomDif = bottom - MAP_SIZE_Y;
            bottom = MAP_SIZE_Y;
        }

        int xIncrement = (WINDOW_X - 1) / 2;
        left = playerPos[0] - xIncrement;
        if(left < 0) {
            leftDif = left;
            left = 0;
        }
        right = playerPos[0] + xIncrement;
        if(right > MAP_SIZE_X) {
            rightDif = right - MAP_SIZE_X;
            right = MAP_SIZE_X;
        }

        // Corrects the borders
        top -= bottomDif;
        bottom -= topDif;
        left -= rightDif;
        right -= leftDif;

        wclear(gWin);

        // Print map within border
        for(int y = top; y < bottom; y++) {
            for(int x = left; x < right; x++){
                int color[2];
                char *tile = getTile(map[y][x], color);
                wattron(gWin, COLOR_PAIR(color[0]));
                mvwprintw(gWin, y-top, x-left, tile);
                wattroff(gWin, COLOR_PAIR(color[0]));
            }
        }

        //Place Player Token
        int playerTokenx = xIncrement+leftDif+rightDif;
        int playerTokeny = yIncrement+topDif+bottomDif;
        wattron(gWin, COLOR_PAIR(5));
        mvwprintw(gWin, playerTokeny, playerTokenx, "@");
        wattroff(gWin, COLOR_PAIR(5));

        //Place Wizards if visible
        for (int i = 1; i < 4; i++){
            int wizardPos[2];
            getPos(i, wizardPos);
            if(wizardPos[0] - left >= 0 && wizardPos[0] - right < right &&
                    wizardPos[1] - top >= 0 && wizardPos[1] - bottom <bottom) {
                if (getHiFived(i)) {
                    wattron(gWin, COLOR_PAIR(7));
                    mvwprintw(gWin, wizardPos[1]-top, wizardPos[0]-left, "W");
                    wattroff(gWin, COLOR_PAIR(7));
                }
                else {
                    wattron(gWin, COLOR_PAIR(6));
                    mvwprintw(gWin, wizardPos[1]-top, wizardPos[0]-left, "W");
                    wattroff(gWin, COLOR_PAIR(6));
                }
            }
        }

        //Place Dragon if Visible
        int draPos[2];
        getPos(4, draPos);
        if(draPos[0] - left >= 0 && draPos[0] - right < right &&
                draPos[1] - top >= 0 && draPos[1] - bottom < bottom) {
                    wattron(gWin, COLOR_PAIR(6));
                    mvwprintw(gWin, draPos[1]-top, draPos[0]-left, "D");
                    wattroff(gWin, COLOR_PAIR(6));
            }


        wrefresh(gWin);

        // Bottom info bar
        wclear(tWin);
        char str[5];
        mvwprintw(tWin, 0, 0, msg);

        mvwprintw(tWin, 1, 0, "Number of Wizards: ");
        sprintf(str, "%d", numWiz);
        wprintw(tWin, str);


        mvwprintw(tWin, 2, 0, "Turn Count: ");
        sprintf(str, "%d", turnCount);
        wprintw(tWin, str);
        
        wrefresh(tWin);

        // Handles user input
        msg = "";
        int input = wgetch(gWin);
        if (input == '5') {
            delwin(gWin);
            return 's';
        }
        else if (input == '2') msg = movec(0, 0, 1);   // down
        else if (input == '3') msg = movec(0, 1, 1);   // down right
        else if (input == '1') msg = movec(0, -1, 1);  // down left
        else if (input == '8') msg = movec(0, 0, -1);  // up
        else if (input == '9') msg = movec(0, 1, -1);  // up right
        else if (input == '7') msg = movec(0, -1, -1); // up left
        else if (input == '6') msg = movec(0, 1, 0);   // right
        else if (input == '4') msg = movec(0, -1, 0);  // left
        turnCount++;
        if(strcmp(msg, "You High Five the Wizard") == 0) numWiz--;
        if(strcmp(msg, "You High Five the Dragon") == 0) return 'v';
        if (numWiz == 0) {
            placeCharacter(4);
            numWiz = 1;
        }
    }
}

// Short victory screen
char victoryScreen(){
    WINDOW *vWin;
    vWin = newwin(WINDOW_Y, WINDOW_X, 0, 0);
    int input;
    while (1) {
        wclear(vWin);
        mvwprintw(vWin, 0, 0, VICTORY);

        char str[5];
        mvwprintw(vWin, 2, 0, "Final Turn Count: ");
        sprintf(str, "%d", turnCount);
        wprintw(vWin, str);
        wrefresh(vWin);

        input = wgetch(vWin);
        if(input == '5' || input == 'z') {
            delwin(vWin);
            return 's';
        }
    }
    
}