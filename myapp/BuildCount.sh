echo off 
set /p var= <version.txt 
set /a var= %var%+1 
echo %var% >version.txt
break >version.h
echo #define VERSION_MAJOR 1 >>version.h
echo #define VERSION_MINOR 7 >>version.h
echo #define VERSION_PATCH 21 >>version.h
echo #define VERSION_CODE 9 >>version.h
echo #define VERSION_BUILD %var% >>version.h
echo %var%
