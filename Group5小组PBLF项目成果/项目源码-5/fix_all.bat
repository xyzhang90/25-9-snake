@echo off
echo 贪吃蛇游戏一键修复工具
echo =========================
echo.

:: 1. 显示文件扩展名
echo [1] 检查文件扩展名...
assoc .c
assoc .bat
echo.

:: 2. 重命名 menu_uic 为 menu_ui.c（如果存在）
if exist menu_uic (
    echo [2] 发现 menu_uic，正在重命名为 menu_ui.c...
    ren menu_uic menu_ui.c
    echo 重命名完成！
) else (
    echo [2] menu_ui.c 文件已存在
)
echo.

:: 3. 创建必要的批处理文件
echo [3] 创建批处理文件...

:: config.bat
echo @echo off > config.bat
echo chcp 936 >> config.bat
echo mode con cols=80 lines=40 >> config.bat
echo title 贪吃蛇游戏 >> config.bat

:: build.bat
echo @echo off > build.bat
echo echo 编译贪吃蛇游戏... >> build.bat
echo chcp 936 >> build.bat
echo gcc main.c game_core.c user_system.c scene_manager.c menu_ui.c -o snake.exe >> build.bat
echo if exist snake.exe (echo 编译成功！) else (echo 编译失败！) >> build.bat
echo pause >> build.bat

:: run.bat
echo @echo off > run.bat
echo chcp 936 >> run.bat
echo mode con cols=80 lines=40 >> run.bat
echo title 贪吃蛇游戏 >> run.bat
echo if not exist snake.exe (echo 请先运行 build.bat ^&^& pause ^&^& exit) >> run.bat
echo snake.exe >> run.bat
echo pause >> run.bat

echo 文件创建完成！
echo.

:: 4. 显示当前文件列表
echo [4] 当前文件夹内容：
dir *.c *.h *.bat *.exe

echo.
echo 现在请：
echo 1. 双击运行 build.bat 编译游戏
echo 2. 双击运行 run.bat 启动游戏
echo.
pause