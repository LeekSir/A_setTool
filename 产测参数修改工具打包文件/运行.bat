@echo off
IF "%PROCESSOR_ARCHITECTURE%"=="x86" (set bit=32) ELSE (set bit=64)

:echo Notice: do NOT restart your computer before installation finished
echo 正在打开软件。。。。。。


echo 进入对应目录
start .\A_setTool_%bit%bit\Factory_set.exe

echo 程序已经运行。
exit
