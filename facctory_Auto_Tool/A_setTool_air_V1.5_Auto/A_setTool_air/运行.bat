@echo off
IF "%PROCESSOR_ARCHITECTURE%"=="x86" (set bit=32) ELSE (set bit=64)

:echo Notice: do NOT restart your computer before installation finished
echo ���ڴ����������������


echo �����ӦĿ¼
cd .\A_setTool_%bit%bit\
start Factory_set.exe

echo �����Ѿ����С�
exit
