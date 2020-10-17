echo 移动正常文件出来。
:move ..\..\WT_SETUP\WT_BT_LIMIT.txt 	..\WT_SETUP_TEMP\
move ..\..\WT_SETUP\WT_DUT_MIMO.txt 	..\WT_SETUP_TEMP\
move ..\..\WT_SETUP\WT_FLOW.txt 		..\WT_SETUP_TEMP\
:move ..\..\WT_SETUP\WT_TESTER.txt 		..\WT_SETUP_TEMP\
move ..\..\WT_SETUP\WT_WIFI_LIMIT.txt 	..\WT_SETUP_TEMP\

echo 拷贝校准文件进去。
:copy ..\WT_SETUP_CORRECT\WT_BT_LIMIT.txt 	..\..\WT_SETUP
copy ..\WT_SETUP_CORRECT\WT_DUT_MIMO.txt 	..\..\WT_SETUP
copy ..\WT_SETUP_CORRECT\WT_FLOW.txt 		..\..\WT_SETUP
:copy ..\WT_SETUP_CORRECT\WT_TESTER.txt 		..\..\WT_SETUP
copy ..\WT_SETUP_CORRECT\WT_WIFI_LIMIT.txt 	..\..\WT_SETUP

echo 备份金板数据文件

del /s /Q ..\log
copy ..\standard.txt 	..\log\standard.txt


echo 修改EEPROM文件为正常bin
move ..\..\EEPROM_Rename.bin ..\..\EEPROM_7668.bin
