#include <stdio.h>
#include <stdlib.h>

#include "mapFactory.h"

// Tile Nums:
// 0 = Empty Space
// 1 = Open Ground
// 2 = Undergrowth
// 3 = Water

unsigned char **createMap(int xMax, int yMax) {
    unsigned char **map = malloc(sizeof(unsigned char *) * yMax);
    for(int y = 0; y < yMax; y++) {
        map[y] = malloc(sizeof(unsigned char) * xMax);
        for(int x = 0; x < xMax; x++) {
            map[y][x] = 1; //Open Ground
        }
    }
    addTiles(3, 1, 5, xMax, yMax, map); //add water
    addTiles(2, 1, 6, xMax, yMax, map); //add undergrowth
    return map;
}

void addTiles(unsigned char type, unsigned char rtype, int chance, int xMax, int yMax, unsigned char **map) {
    for (int y = 0; y < yMax; y++) {
        for(int x = 0; x < xMax; x++) {
            if (rand() % 10 < chance && map[y][x] == 1) map[y][x] = type;
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int y = 0; y < yMax; y++) {
            for(int x = 0; x < xMax; x++) {
                int count = 0;
                if (x != 0 && map[y][x-1]  == type) count++; 
                if (x != xMax-1 && map[y][x+1]  == type) count++; 
                if (y != 0 && map[y-1][x]  == type) count++; 
                if (y != yMax-1 && map[y+1][x]  == type) count++; 
                
                if (x != 0 && y != 0 && map[y-1][x-1]  == type) count++;
                if (x != 0 && y != yMax-1 && map[y+1][x-1]  == type) count++;
                if (x != xMax-1 && y != 0 && map[y-1][x+1]  == type) count++;
                if (x != xMax-1 && y != yMax-1 && map[y+1][x+1]  == type) count++;

                if (count < 4 && map[y][x] == type) map[y][x] = rtype;
                if (count > 5 && map[y][x] == 1) map[y][x] = type;
            }
        }
    }
}