echo 移动setup全部文件出来。

del /s /Q ..\..\WT_SETUP

xcopy  ..\WT_SETUP_EASY_DAMAGE\* ..\..\WT_SETUP /s/e/y

