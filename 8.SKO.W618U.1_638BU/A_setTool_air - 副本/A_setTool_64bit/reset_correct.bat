echo 移动正常文件回去。
move ..\WT_SETUP_TEMP\WT_BT_LIMIT.txt 			..\..\WT_SETUP
move ..\WT_SETUP_TEMP\WT_DUT_MIMO.txt 			..\..\WT_SETUP
move ..\WT_SETUP_TEMP\WT_FLOW.txt 				..\..\WT_SETUP
:move ..\WT_SETUP_TEMP\WT_TESTER.txt 			..\..\WT_SETUP
move ..\WT_SETUP_TEMP\WT_WIFI_LIMIT.txt 		..\..\WT_SETUP


echo 恢复金板数据。

:del /s /Q ..\log
:move ..\log\WT_WIFI_LIMIT.txt 		..\..\WT_SETUP