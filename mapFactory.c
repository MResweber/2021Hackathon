#include <stdio.h>
#include <stdlib.h>

#include "mapFactory.h"

unsigned char **createMap(int xMax, int yMax) {
    unsigned char **map = malloc(sizeof(unsigned char *) * yMax);
    for(int y = 0; y < yMax; y++) {
        map[y] = malloc(sizeof(unsigned char) * xMax);
        for(int x = 0; x < xMax; x++) {
            if(x == 0 || y == 0 || x == xMax -1 || y == yMax - 1) {
                map[y][x] = 0; //Wall
            }
            else {
                map[y][x] = 1; //Floor
            }
        }
    }
    return map;
}