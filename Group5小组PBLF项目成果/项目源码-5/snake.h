 #ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

// 宏定义
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define PAUSE ' '
#define WIDTH 40
#define HEIGHT 20
#define NAME_SIZE 128
#define MAX_PLAYER 1024
#define MAX_OBT 4

// 结构体定义
typedef struct Snake {
    int x;
    int y;
    struct Snake *next;
} Snake;

typedef struct food {
    int x;
    int y;
    int score;
} Food;

typedef struct playerInfo {
    char name[NAME_SIZE];
    int high_score;
    int play_times;
} Player;

typedef struct obstacle {
    int x;
    int y;
} Obstacle;

// 全局变量声明（extern表示在其他文件中定义）
extern char cGameScene[HEIGHT][WIDTH];
extern char cUserName[NAME_SIZE];
extern int iTotalScore;
extern int iLastScore;
extern int iTotalTimes;
extern int iDifficulty;
extern int iRefreshTimes[4];
extern int iGameOver;
extern int iFoodSpawned;
extern char cControl;
extern Snake *head, *tail;
extern Food food;
extern Obstacle obstacles[MAX_OBT];

// 工具函数声明
void gotoxy(int x, int y);
void clearScreen(void);
int randint(int min, int max);

// 用户系统函数声明
void enterUsername(void);
void updateScoreBoard(void);
void myInfo(void);

// 游戏核心函数声明
void initGame(void);
void refreshScreen(void);
int ifGameOver(void);
void spawnFood(void);
void gameLoop(void);
void gameOver(void);

// 菜单界面函数声明
void startMenu(void);
void chooseDifficulty(void);
void displayScoreBoard(void);

#endif // SNAKE_H
