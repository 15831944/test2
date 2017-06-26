@echo off

set s1=%~dp0%
if exist "*.ncb"	(del /a /q /f "*.ncb")
if exist "*.suo"	(del /a /q /f "*.suo")	

cd %s1%\dd
if exist "*.aps"	(del /a /q /f "*.aps")
if exist "*.user"	(del /a /q /f "*.user")	

cd %s1%\bin
if exist "dd.exe"	(del /a /q /f "dd.exe")

cd %s1%\temp\Compile
if exist "dd" 		(rmdir /Q /S dd)

cd %s1%\temp\Link
if exist "dd" 		(rmdir /Q /S dd)