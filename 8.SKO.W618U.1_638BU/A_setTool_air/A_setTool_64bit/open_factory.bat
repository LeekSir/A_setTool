:"WLAN Console.exe" STARTTEST 1
:/c STARTTEST 1
:"WLAN Console.exe"
:choice /t 5 /d y /n >nul  
cd ../../ && "SKO.W618U.1_638BU.exe"

:C:\Windows\system32\taskkill.exe /f /im "WLAN Facility.exe"

