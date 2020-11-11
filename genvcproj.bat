@echo off
echo 2015/1/27 created by Huaxiang.

set dd=%~dp0
echo dd=%dd%

set PATH=C:\Qt\Qt5.5.1\5.5\msvc2013\bin;%PATH%

cd /D %dd%
qmake -r -tp vc blackboard.pro

pause
@echo on