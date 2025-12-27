@echo off
g++ src/*.cpp -o build/main.exe -Ilibs/raylib/include -Llibs/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
start build/main.exe