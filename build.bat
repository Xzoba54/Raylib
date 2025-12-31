@echo off
g++ src/*.cpp -o build/main.exe -Ilibs/raylib/include -Ilibs/enet/include -Llibs/raylib/lib -Llibs/enet/lib -lraylib -lenet -lopengl32 -lgdi32 -lwinmm -lws2_32
start build/main.exe	