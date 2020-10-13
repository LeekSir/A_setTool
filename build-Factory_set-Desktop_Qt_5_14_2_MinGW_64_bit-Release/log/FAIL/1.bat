@echo off
cd /d E:\qt_code\8.SKO.W618U.1_638BU\LOG\FAIL
for /f "tokens=1-3*" %%a in ('dir /s /a-d/tc *.log ^| find ":"') do echo;%~dp0%%d ^| %%a %%b ^| %%d
pause