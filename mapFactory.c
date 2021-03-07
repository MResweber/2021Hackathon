#include <stdio.h>
#include <stdlib.h>

#include "mapFactory.h"

char ***createMap(int xMax, int yMax) {
    char ***map = (char ***)malloc(sizeof(char *) * yMax);
    for(int y = 0; y < yMax; y++) {
        map[y] = (char **)malloc(sizeof(char) * 20);
        for(int x = 0; x < xMax; x++) {
            if(x == 0 || y == 0) {
                map[y][x] = malloc(sizeof(char) * 3);
                map[y][x][0] = 'X'; //character
                map[y][x][1] = '2'; //color
                map[y][x][2] = '0';   //passable
            }
            else {
                map[y][x] = malloc(sizeof(char) * 3);
                map[y][x][0] = '.';
                map[y][x][1] = '2';
                map[y][x][2] = '1';
            }
        }
    }
    return map;
}