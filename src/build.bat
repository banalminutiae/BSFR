@echo off

IF NOT EXIST ..\build\ mkdir ..\build
pushd ..\build\
cl -nologo -O2 -W3 -FC -Z7 -EHsc -D_CRT_SECURE_NO_WARNINGS -IC:\SDL\include -LC:\SDL\lib\x86 /Qvec-report:2 ..\src\main.cpp -lSDL2main -lSDL2
popd

