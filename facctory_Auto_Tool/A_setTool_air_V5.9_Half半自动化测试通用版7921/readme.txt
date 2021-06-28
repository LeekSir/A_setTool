修改点：
1、增加一路蓝牙校准CHAIN1
2、修复了校准loss_value未及时清零问题
3、修复校准pass后重复fail的情况，按大于1的进行重新校准，不大于1的不做校准

5.8
取消 "按大于1的进行重新校准，不大于1的不做校准"的功能

5.9
修改了WT_WRITE_EFUSE 到 WT_WRITE_EFUSE_FREE，修复7921新产测不识别wirte_efuse问题