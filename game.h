typedef struct {
    int xPos;
    int yPos;
    int hiFive;
} character;
void initGame(int x, int y);
unsigned char **getMap();
void getPos(int c, int *info);
char *getTile(unsigned char value, int info[]);
char *movec(int c, int x, int y);
void placeCharacter(int c);
int getHiFived (int c);
void createMap(int xMax, int yMax);
void addTiles(unsigned char type, int chance);
void runChars();