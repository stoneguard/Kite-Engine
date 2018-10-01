@echo off
mkdir build

cd ./build

cmake -G"Visual Studio 14 2015 Win64" ..
rem cmake -DCMAKE_BUILD_TYPE=Debug -G"Visual Studio 14 2015 Win64" ..
rem cmake -DCMAKE_BUILD_TYPE=Release -G"Visual Studio 14 2015 Win64" ..

pause