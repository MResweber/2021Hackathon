typedef struct {
    int hp;
    int sta;
} player;
void initGame(player *p, int x, int y);
unsigned char **getMap();
int *getPlayerPos();
char *getTile(unsigned char value, int info[]);
void pMove (int x, int y);