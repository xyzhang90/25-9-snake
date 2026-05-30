 #include "snake.h"

int ifGameOver() {
    // 撞墙
    if (head->x <= 0 || head->x >= WIDTH-1 || head->y <= 0 || head->y >= HEIGHT-1)
        return 1;

    // 撞障碍
    if (iDifficulty >= 3) {
        for (int i = 0; i < MAX_OBT; i++) {
            for (int dy = 0; dy < 2; dy++) {
                for (int dx = 0; dx < 2; dx++) {
                    if (head->x == obstacles[i].x + dx && head->y == obstacles[i].y + dy)
                        return 1;
                }
            }
        }
    }

    // 撞自己
    Snake *p = head->next;
    while (p) {
        if (head->x == p->x && head->y == p->y)
            return 1;
        p = p->next;
    }
    return 0;
}

void spawnFood() {
    int valid;
    do {
        valid = 1;
        food.x = randint(1, WIDTH - 2);
        food.y = randint(1, HEIGHT - 2);
        food.score = iDifficulty;

        // 检查是否在蛇身上
        Snake *p = head;
        while (p) {
            if (p->x == food.x && p->y == food.y) {
                valid = 0;
                break;
            }
            p = p->next;
        }
        if (!valid) continue;

        // 检查是否在障碍上
        if (iDifficulty >= 3) {
            for (int i = 0; i < MAX_OBT; i++) {
                if (food.x >= obstacles[i].x && food.x < obstacles[i].x + 2 &&
                    food.y >= obstacles[i].y && food.y < obstacles[i].y + 2) {
                    valid = 0;
                    break;
                }
            }
        }
    } while (!valid);

    cGameScene[food.y][food.x] = '*';
    iFoodSpawned = 1;
}

void gameLoop() {
    cControl = RIGHT;
    if (!iFoodSpawned) spawnFood();
    
    // 初始绘制蛇身
    Snake *p = head;
    int isFirst = 1;
    while (p) {
        gotoxy(p->x, p->y);
        putchar(isFirst ? '@' : 'O');
        isFirst = 0;
        p = p->next;
    }
    
    // 绘制食物
    gotoxy(food.x, food.y);
    putchar('*');

    while (!ifGameOver()) {
        Sleep(iRefreshTimes[iDifficulty - 1]);

        if (_kbhit()) {
            char key = tolower(_getch());
            if ((key == UP && cControl != DOWN) ||
                (key == DOWN && cControl != UP) ||
                (key == LEFT && cControl != RIGHT) ||
                (key == RIGHT && cControl != LEFT)) {
                cControl = key;
            }
        }

        // 保存尾部位置用于清理
        int tailX = tail->x, tailY = tail->y;
        
        // 移动蛇头
        int newX = head->x, newY = head->y;
        switch (cControl) {
            case UP:    newY--; break;
            case DOWN:  newY++; break;
            case LEFT:  newX--; break;
            case RIGHT: newX++; break;
        }
        
        // 创建新头节点
        Snake *newHead = (Snake*)malloc(sizeof(Snake));
        newHead->x = newX;
        newHead->y = newY;
        newHead->next = head;
        head = newHead;
        
        // 检查是否吃到食物
        if (newX == food.x && newY == food.y) {
            iTotalScore += food.score;
            iFoodSpawned = 0;
            // 吃到食物不删除尾部，蛇变长
        } else {
            // 没吃到食物，删除尾部
            Snake *prev = head;
            while (prev->next != tail) prev = prev->next;
            
            // 清除尾部显示
            gotoxy(tail->x, tail->y);
            putchar(' ');
            
            free(tail);
            tail = prev;
            tail->next = NULL;
        }
        
        // 绘制新蛇头
        gotoxy(head->x, head->y);
        putchar('@');
        
        // 更新第二节为身体
        if (head->next) {
            gotoxy(head->next->x, head->next->y);
            putchar('O');
        }
        
        // 生成新食物
        if (!iFoodSpawned) {
            spawnFood();
            gotoxy(food.x, food.y);
            putchar('*');
        }
        
        // 更新分数显示
        gotoxy(WIDTH + 2, HEIGHT / 2);
        printf("得分：%d", iTotalScore);
        
        fflush(stdout);
    }
}
