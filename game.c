#include <stdlib.h>
#include <stdio.h>

#include "mapFactory.h"
#include "game.h"

unsigned char **map;
character **pc;
int mapX;
int mapY;

void initGame(int x, int y) {
    mapX = x;
    mapY = y;
    map = createMap(mapX, mapY);
    pc = malloc(sizeof(character) * 5);
    placeCharacter(0);
    for (int i = 1; i < 4; i++) {
        placeCharacter(i);
    }
}

unsigned char **getMap () {
    return map;
}

int getHiFived (int c) {
    return pc[c]->hiFive;
}

void getPos(int c, int *info){ 
    info[0] = pc[c]->xPos;
    info[1] = pc[c]->yPos;
}

char *getTile(unsigned char value, int info[]) {
    if (value == 0) { //Empty Space
        info[0] = 1;  //color
        info[1] = 0;  //passable
        return " ";   //Symbol
    }
    else if (value == 1) { //Open Ground
        info[0] = 5;
        info[1] = 1;
        return " ";
    }
    else if (value == 2) { //UnderGrowth
        info[0] = 3;
        info[1] = 0;
        return " ";
    }
    else if (value == 3) { //Water
        info[0] = 4;
        info[1] = 0;
        return " ";
    }
    return "";
}

char  *movec (int c, int x, int y){
    if(pc[c]->yPos + y > mapY-1) return "You are on the edge of the map";
    if(pc[c]->yPos + y < 0) return "You are on the edge of the map";
    if(pc[c]->xPos + x > mapX-1) return "You are on the edge of the map";
    if(pc[c]->xPos + x < 0) return "You are on the edge of the map";

    int info[2];
    getTile(map[pc[c]->yPos+y][pc[c]->xPos+x], info);

    if(!info[1] && map[pc[c]->yPos+y][pc[c]->xPos+x] != 2) return "You can't swim";
    else if (!info[1]) {
        map[pc[c]->yPos+y][pc[c]->xPos+x] = 1;
        return "You cut through the undergrowth";
    }
    pc[c]->xPos+=x;
    pc[c]->yPos+=y;
    return "";
}

void placeCharacter(int c) {
    int placed = 0;
    while (!placed) {
        int x = rand() % mapX;
        int y = rand() % mapY;
        if (map[y][x] == 1) {
            pc[c] = malloc(sizeof(character));
            pc[c]->xPos = x;
            pc[c]->xPos = y;
            pc[c]->hiFive = 0;
            placed = 1;
        }
    }
}