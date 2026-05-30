@echo off 
chcp 936 
mode con cols=80 lines=40 
title 贪吃蛇游�?
if not exist snake.exe (echo 请先运行 build.bat && pause && exit) 
snake.exe 
pause 
