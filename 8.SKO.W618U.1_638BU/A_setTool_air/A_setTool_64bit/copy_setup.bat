echo 移动setup全部文件出来。

del /s /Q ..\..\WT_SETUP_EASY_DAMAGE

xcopy ..\..\WT_SETUP\* ..\WT_SETUP_EASY_DAMAGE\ /s/e/y

