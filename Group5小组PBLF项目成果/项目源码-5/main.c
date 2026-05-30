 #include "snake.h"

// ȫ�ֱ������壨������ʵ�ʷ����ڴ棩
char cGameScene[HEIGHT][WIDTH];
char cUserName[NAME_SIZE];
int iTotalScore = 0;
int iLastScore = 0;
int iTotalTimes = 0;
int iDifficulty = 1;
int iRefreshTimes[4] = { 50, 25, 10, 1 };
int iGameOver = 0;
int iFoodSpawned = 0;
char cControl = RIGHT;
Snake *head = NULL, *tail = NULL;
Food food;
Obstacle obstacles[MAX_OBT];

int main(void) {
    srand((unsigned int)time(0));
    enterUsername();
    
    while (1) {
        startMenu();
        clearScreen();
        initGame();
        gameLoop();
        gameOver();
        clearScreen();
    }
    
    return 0;
}