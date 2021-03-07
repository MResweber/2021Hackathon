typedef struct {
    int hp;
    int sta;
} player;
void initGame(player *p, int x, int y);
char ***getMap();
int *getPlayerPos();