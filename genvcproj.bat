@echo off
echo 2015/1/27 created by Huaxiang.

set dd=%~dp0
echo dd=%dd%

rem set PATH=C:\Qt\Qt5.4.0\5.4\msvc2013_opengl\bin;%PATH%

set PATH=D:\compiledQt5.4.0\bin;%PATH%

cd /D %dd%
qmake -r -tp vc blackboard.pro

pause
@echo on