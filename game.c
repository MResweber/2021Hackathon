#include <stdlib.h>
#include <stdio.h>

#include "mapFactory.h"
#include "game.h"

char ***map;
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

char ***getMap () {
    return map;
}

int *getPlayerPos(){ 
    int *temp = malloc(sizeof(int) * 2);
    temp[0] = playerx;
    temp[1] = playery;
    return temp;
}