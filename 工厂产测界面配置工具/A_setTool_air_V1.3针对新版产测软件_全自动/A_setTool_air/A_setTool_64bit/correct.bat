@echo off

cd ..\..\
"WLAN Console.exe" -p %1

:cd ..\..\ && "WLAN Console.exe" /c STARTTEST %1

echo 程序已经运行。
:exit

