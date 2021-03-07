#include <stdlib.h>
#include <stdio.h>

#include "mapFactory.h"
#include "game.h"

unsigned char **map;
player *pc;
int playerx;
int playery;
int mapX;
int mapY;

void initGame(player *p, int x, int y) {
    mapX = x;
    mapY = y;
    pc = p;
    map = createMap(mapX, mapY);
    playerx = 10;
    playery = 10;
}

unsigned char **getMap () {
    return map;
}

int *getPlayerPos(){ 
    int *temp = malloc(sizeof(int) * 2);
    temp[0] = playerx;
    temp[1] = playery;
    return temp;
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

void pMove (int x, int y){
    if(playery + y > mapY-1) return;
    if(playery + y < 0) return;
    if(playerx + x > mapX-1) return;
    if(playerx + x < 0) return;
    int info[2];
    getTile(map[playery+y][playerx+x], info);
    if(!info[1]) return;
    playerx+=x;
    playery+=y;
}