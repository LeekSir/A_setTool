@echo off
setlocal enabledelayedexpansion
rem 准备执行
 
rem set userdomain 
 
rem 设置文件所在目录
set src_dir=..\LOG\PASS
set des_dir=.\log
:E:\qt_code\8.SKO.W618U.1_638BU\A_setTool_air\log
 
rem filename用于存放目标文件名
set filename=""
 
:cd /d %src_dir%
cd ..\..\LOG\PASS
:cd %1\PASS
for /f %%a in ('dir /o-d /tc /b ') do (
    echo FILE all info: %%a
    set filename=%%~na%%~xa
    echo filename: !filename!
	echo new creat time: %%~ta
    if not !filename! == ""  (
        goto iconv
    )
 
)
 
:iconv
echo %filename%
:echo f|xcopy %filename% %des_dir%\correct.log /y

copy %filename% ..\..\A_setTool_air\log

rem 执行完毕
rem pause