 CC = gcc
CFLAGS = -Wall -Wextra
TARGET = snake.exe
OBJS = main.o game_core.o user_system.o scene_manager.o menu_ui.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c snake.h
	$(CC) $(CFLAGS) -c main.c

game_core.o: game_core.c snake.h
	$(CC) $(CFLAGS) -c game_core.c

user_system.o: user_system.c snake.h
	$(CC) $(CFLAGS) -c user_system.c

scene_manager.o: scene_manager.c snake.h
	$(CC) $(CFLAGS) -c scene_manager.c

menu_ui.o: menu_ui.c snake.h
	$(CC) $(CFLAGS) -c menu_ui.c

clean:
	del *.o $(TARGET) 2>nul || true

.PHONY: all clean
