@echo off
setlocal enabledelayedexpansion
rem 准备执行
 
rem set userdomain
 
rem 设置文件所在目录
set src_dir=E:\test1
set des_dir=E:\test2
 
rem filename用于存放目标文件名
set filename=""
 
cd /d %src_dir%
for /f %%a in ('dir /o-d /tc /b ') do (
    echo 文件完整信息: %%a
    set filename=%%~na%%~xa
    echo 文件名: !filename!, 最新创建时间： %%~ta
    if not !filename! == ""  (
        goto iconv
    )
 
)
 
:iconv
echo %filename%
echo f|xcopy %filename% %des_dir%\%userdomain%-1-1 /y
 
rem 执行完毕
rem pause