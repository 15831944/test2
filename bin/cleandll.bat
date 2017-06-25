@echo off

del dd.exe /f /q

set S1=%cd%

cd..
set S2=%cd%

del *.ncb  /f /q

cd %S2%\dd
del *.aps  /f /q
del *.user /f /q

cd %S2%\temp\Compile
if exist "dd" (rmdir /Q /S dd)

cd %S2%\temp\Link
if exist "dd" (rmdir /Q /S dd)