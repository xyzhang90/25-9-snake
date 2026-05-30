 #include "snake.h"

void enterUsername() {
    int iSelect;
    char cSearchName[NAME_SIZE], cName[NAME_SIZE];
    FILE *fp;
    int iScore, iTimes;
    int iFound = 0;

    clearScreen();
    printf("====================================================\n");
    printf("#                                                  #\n");
    printf("#                  1. 新建账号                     #\n");
    printf("#                  2. 读取存档                     #\n");
    printf("#                                                  #\n");
    printf("====================================================\n");
    printf("                  选择：");

    scanf("%d", &iSelect);
    getchar();

    if (iSelect == 1) {
        clearScreen();
        printf("\t\t请输入用户名：");
        fgets(cUserName, sizeof(cUserName), stdin);
        cUserName[strcspn(cUserName, "\n")] = 0;
    } else if (iSelect == 2) {
        clearScreen();
        if ((fp = fopen("scoreBoard.txt", "r")) == NULL) {
            printf("\t\t存档文件不存在，创建新账号。\n");
            strcpy(cUserName, "玩家");
            _getch();
            return;
        }
        printf("\t\t请输入用户名：");
        fgets(cSearchName, sizeof(cSearchName), stdin);
        cSearchName[strcspn(cSearchName, "\n")] = 0;

        while (fscanf(fp, "%s %d %d", cName, &iScore, &iTimes) == 3) {
            if (strcmp(cSearchName, cName) == 0) {
                iFound = 1;
                strcpy(cUserName, cSearchName);
                iLastScore = iScore;
                iTotalTimes = iTimes;
                printf("\t\t找到存档：%s，历史最高分：%d，游戏次数：%d\n", cUserName, iLastScore, iTotalTimes);
                break;
            }
        }
        fclose(fp);
        if (!iFound) {
            printf("\t\t未找到该用户名，请确认输入是否正确。\n");
            _getch();
            enterUsername();
        }
    } else {
        enterUsername();
    }
}

void updateScoreBoard() {
    FILE *fp;
    Player players[MAX_PLAYER];
    int count = 0, found = 0;

    if ((fp = fopen("scoreBoard.txt", "r")) != NULL) {
        while (fscanf(fp, "%s %d %d", players[count].name,
                      &players[count].high_score,
                      &players[count].play_times) == 3) {
            if (strcmp(players[count].name, cUserName) == 0) {
                found = 1;
                if (iTotalScore > players[count].high_score)
                    players[count].high_score = iTotalScore;
                players[count].play_times = iTotalTimes;
            }
            count++;
        }
        fclose(fp);
    }

    if (!found) {
        strcpy(players[count].name, cUserName);
        players[count].high_score = iTotalScore;
        players[count].play_times = iTotalTimes;
        count++;
    }

    // 冒泡排序（高分在前）
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - 1 - i; j++)
            if (players[j].high_score < players[j+1].high_score) {
                Player t = players[j];
                players[j] = players[j+1];
                players[j+1] = t;
            }

    fp = fopen("scoreBoard.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %d %d\n", players[i].name,
                players[i].high_score,
                players[i].play_times);
    }
    fclose(fp);
}

void myInfo() {
    FILE *fp;
    char cName[NAME_SIZE];
    int iScore, iTimes;
    int found = 0;
    clearScreen();
    if ((fp = fopen("scoreBoard.txt", "r")) == NULL) {
        printf("\t\t暂无存档信息。\n");
        return;
    }
    while (fscanf(fp, "%s %d %d", cName, &iScore, &iTimes) == 3) {
        if (strcmp(cName, cUserName) == 0) {
            found = 1;
            printf("\t\t用户：%s\n", cUserName);
            printf("\t\t历史最高分：%d\n", iScore);
            printf("\t\t游戏次数：%d\n", iTimes);
            break;
        }
    }
    fclose(fp);
    if (!found) {
        printf("\t\t用户：%s\n", cUserName);
        printf("\t\t当前得分：%d\n", iTotalScore);
        printf("\t\t游戏次数：%d\n", iTotalTimes);
    }
}
