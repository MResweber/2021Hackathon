#include <stdlib.h>
#include <stdio.h>

#include "game.h"

unsigned char **map;
character **pc;
int mapX;
int mapY;

// Creates game world
void initGame(int x, int y) {
    mapX = x;
    mapY = y;
    createMap(mapX, mapY);
    pc = malloc(sizeof(character) * 5);
    placeCharacter(0);                  // Places player
    for (int i = 1; i < 4; i++) {       // Places wizards
        placeCharacter(i);
    }
    pc[4] = malloc(sizeof(character));  // Hide Dragon
    pc[4]->hiFive = 0;
    pc[4]->xPos = -10;
    pc[4]->yPos = -10;
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
    if (value == 0) {       //Empty Space
        info[0] = 1;  //color
        info[1] = 0;  //passable
        return " ";   //Symbol
    }
    else if (value == 1) {  //Open Ground
        info[0] = 1;
        info[1] = 1;
        return " ";
    }
    else if (value == 2) {  //UnderGrowth
        info[0] = 3;
        info[1] = 0;
        return " ";
    }
    else if (value == 3) {  //Water
        info[0] = 4;
        info[1] = 0;
        return " ";
    }
    return "";
}

// Causes character at c to move bt x and y.
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

    // Run into a Wizard
    for (int i = 1; i < 4; i++) {
        int wizPos[2];
        getPos(i, wizPos);
        if (pc[c]->xPos+x == wizPos[0] && pc[c]->yPos+y == wizPos[1]){
            if(!pc[i]->hiFive) {
                pc[i]->hiFive = 1;
                return "You High Five the Wizard";
            }
            else return "You High Five the Wizard Again";
        } 
    }
    
    // Run into Dragon
    if (pc[c]->xPos+x == pc[4]->xPos && pc[c]->yPos+y == pc[4]->yPos){
        return "You High Five the Dragon";
    }
    pc[c]->xPos+=x;
    pc[c]->yPos+=y;
    return "";
}

// Places character randomly into game world
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

// creates the map
void createMap(int xMax, int yMax) {
    map = malloc(sizeof(unsigned char *) * yMax);
    for(int y = 0; y < yMax; y++) {
        map[y] = malloc(sizeof(unsigned char) * xMax);
        for(int x = 0; x < xMax; x++) {
            map[y][x] = 1; //Open Ground
        }
    }
    addTiles(3, 5); //add water
    addTiles(2, 6); //add undergrowth
}

// Adds tiles of type to map. new tiles cannot replace tiles already placed only open ground.
void addTiles(unsigned char type, int chance) {
    // Add tiles randomly around the map
    for (int y = 0; y < mapY; y++) {
        for(int x = 0; x < mapX; x++) {
            if (rand() % 10 < chance && map[y][x] == 1) map[y][x] = type;
        }
    }

    // Changes so tile cluster together
    for (int i = 0; i < 10; i++) {
        for (int y = 0; y < mapY; y++) {
            for(int x = 0; x < mapX; x++) {
                int count = 0;
                if (x != 0 && map[y][x-1]  == type) count++; 
                if (x != mapX-1 && map[y][x+1]  == type) count++; 
                if (y != 0 && map[y-1][x]  == type) count++; 
                if (y != mapY-1 && map[y+1][x]  == type) count++; 
                
                if (x != 0 && y != 0 && map[y-1][x-1]  == type) count++;
                if (x != 0 && y != mapY-1 && map[y+1][x-1]  == type) count++;
                if (x != mapX-1 && y != 0 && map[y-1][x+1]  == type) count++;
                if (x != mapX-1 && y != mapY-1 && map[y+1][x+1]  == type) count++;

                if (count < 4 && map[y][x] == type) map[y][x] = 1;
                if (count > 5 && map[y][x] == 1) map[y][x] = type;
            }
        }
    }
}