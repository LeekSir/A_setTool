echo 移动setup全部文件出来。

del /s /Q ..\..\WT_SETUP

xcopy  ..\WT_SETUP_EASY_DAMAGE\* ..\..\WT_SETUP /s/e/y

move ..\..\EEPROM_Rename.bin ..\..\EEPROM_7668.bin

echo 备份金板数据文件

copy ..\standard.txt 	..\log\standard.txt

