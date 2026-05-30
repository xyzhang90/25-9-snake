 #include "snake.h"

void startMenu() {
    int iSelect;
    clearScreen();
    printf("====================================================\n");
    printf("#                                                  #\n");
    printf("#               贪吃蛇 Version Alpha               #\n");
    printf("#                                                  #\n");
    printf("#                1. 开始游戏                       #\n");
    printf("#                2. 查看排行榜                     #\n");
    printf("#                3. 查看我的信息                   #\n");
    printf("#                4. 切换账号                       #\n");
    printf("#                5. 退出游戏                       #\n");
    printf("#                                                  #\n");
    printf("====================================================\n");
    printf("                  选择：");
    scanf("%d", &iSelect);
    getchar();

    if (iSelect == 1) {
        chooseDifficulty();
        iTotalTimes++;
    } else if (iSelect == 2) {
        displayScoreBoard();
        printf("                    按任意键返回菜单\n");
        _getch();
        startMenu();
    } else if (iSelect == 3) {
        myInfo();
        printf("                    按任意键返回菜单\n");
        _getch();
        startMenu();
    } else if (iSelect == 5) {
        printf("\t\t感谢游玩！正在保存数据...\n");
        updateScoreBoard();
        Sleep(500);
        exit(0);
    } else if (iSelect == 4) {
        updateScoreBoard();
        enterUsername();
        startMenu();
    } else {
        startMenu();
    }
}

void chooseDifficulty() {
    int iSelect;
    printf("           1. 简单  2. 普通  3. 困难  4. 地狱\n");
    printf("                  选择：");
    scanf("%d", &iSelect);
    getchar();
    if (iSelect >= 1 && iSelect <= 4) {
        iDifficulty = iSelect;
    } else {
        chooseDifficulty();
    }
}

void displayScoreBoard() {
    FILE *fp;
    char cName[NAME_SIZE];
    int iScore, iTimes;
    clearScreen();
    if ((fp = fopen("scoreBoard.txt", "r")) == NULL) {
        printf("\t\t暂无排行榜数据。\n");
        return;
    }
    printf("======================  排行榜  ====================\n");
    while (fscanf(fp, "%s %d %d", cName, &iScore, &iTimes) == 3) {
        printf("               %s : %d\n", cName, iScore);
    }
    printf("====================================================\n");
    fclose(fp);
}

// 工具函数也放在这里，或者单独一个tools.c文件
void gotoxy(int x, int y) {
    COORD pos = { x, y };
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}

void clearScreen(void) {
    system("cls");
}

int randint(int min, int max) {
    return rand() % (max - min + 1) + min;
}
