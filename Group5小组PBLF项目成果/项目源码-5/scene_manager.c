 #include "snake.h"

void initGame() {
    // 隐藏光标
    CONSOLE_CURSOR_INFO info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    // 初始化场景（含边框）
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT-1 || j == 0 || j == WIDTH-1) {
                cGameScene[i][j] = '#';
            } else {
                cGameScene[i][j] = ' ';
            }
        }
    }

    // 创建蛇（2节）
    head = (Snake*)malloc(sizeof(Snake));
    head->x = WIDTH / 2;
    head->y = HEIGHT / 2;
    head->next = (Snake*)malloc(sizeof(Snake));
    head->next->x = head->x - 1;
    head->next->y = head->y;
    head->next->next = NULL;
    tail = head->next;

    cGameScene[head->y][head->x] = '@';
    cGameScene[tail->y][tail->x] = 'O';

    // 障碍物（困难及以上）
    if (iDifficulty >= 3) {
        obstacles[0].x = 10; obstacles[0].y = 5;
        obstacles[1].x = 10; obstacles[1].y = HEIGHT - 6;
        obstacles[2].x = WIDTH - 12; obstacles[2].y = 5;
        obstacles[3].x = WIDTH - 12; obstacles[3].y = HEIGHT - 6;

        for (int idx = 0; idx < MAX_OBT; idx++) {
            for (int dy = 0; dy < 2; dy++) {
                for (int dx = 0; dx < 2; dx++) {
                    int nx = obstacles[idx].x + dx;
                    int ny = obstacles[idx].y + dy;
                    if (nx > 0 && nx < WIDTH-1 && ny > 0 && ny < HEIGHT-1) {
                        cGameScene[ny][nx] = '#';
                    }
                }
            }
        }
    }

    refreshScreen(); // 首次绘制完整画面
}

void refreshScreen() {
    // 绘制整个场景（含可能被污染的边框）
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            gotoxy(j, i);
            putchar(cGameScene[i][j]);
        }
    }

    // 强制重绘边框（确保可见）
    for (int j = 0; j < WIDTH; j++) {
        gotoxy(j, 0);
        putchar('#');
        gotoxy(j, HEIGHT - 1);
        putchar('#');
    }
    for (int i = 0; i < HEIGHT; i++) {
        gotoxy(0, i);
        putchar('#');
        gotoxy(WIDTH - 1, i);
        putchar('#');
    }

    // 显示得分
    gotoxy(WIDTH + 2, HEIGHT / 2);
    printf("得分：%d", iTotalScore);
}

void gameOver() {
    clearScreen();
    printf("====================================================\n\n\n\n");
    printf("                      GAME OVER                     \n\n");
    printf("                  得分：%4d\n\n\n", iTotalScore);
    printf("====================================================\n");

    if (iTotalScore > iLastScore) {
        updateScoreBoard();
        iLastScore = iTotalScore;
    }
    printf("                    按任意键返回菜单\n");
    _getch();
    iTotalScore = 0;
    iFoodSpawned = 0;

    // 释放蛇内存
    Snake *p = head;
    while (p) {
        Snake *t = p;
        p = p->next;
        free(t);
    }
    head = tail = NULL;
}
