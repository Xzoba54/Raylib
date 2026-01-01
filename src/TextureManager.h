#pragma once

#include "raylib.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include "Register.h"

class TextureManager{
public:
    TextureManager() = delete;
    
    static Texture2D& LoadTexture(const std::string& name, const char* path){
        auto it = textures.find(name);
        if(it != textures.end()){
            std::cout << "Texture [" << name << "] has been already loaded!\n";

            return it->second;
        }

        textures[name] = ::LoadTexture(path);
        return textures[name];
    }

    static Texture2D& LoadTexture(const GroundID& id, const char* path){
        auto it = groundTextures.find(id);
        if(it != groundTextures.end()){
            std::cout << "Ground texture [" << static_cast<int>(id) << "] has been already loaded!\n";

            return it->second;
        }

        groundTextures[id] = ::LoadTexture(path);
        return groundTextures[id];
    }

    static Texture2D& GetTexture(const std::string& name) {
        auto it = textures.find(name);
        if(it == textures.end()){
            std::cout << "Texture " << "[" << name << "] not found!\n";
        }

        return it->second;
    }

    static Texture2D& GetTexture(const GroundID& id) {
        auto it = groundTextures.find(id);
        if(it == groundTextures.end()){
            std::cout << "Ground texture " << "[" << static_cast<int>(id) << "] not found!\n";
        }

        return it->second;
    }

private:
    static std::unordered_map<std::string, Texture2D> textures;
    static std::unordered_map<GroundID, Texture2D> groundTextures;
};