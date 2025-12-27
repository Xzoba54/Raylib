#pragma once

#include "raylib.h"
#include <unordered_map>
#include <string>
#include <iostream>

class TextureManager{
public:
    TextureManager() = delete;
    
    static Texture2D& LoadTexture(const std::string& name, const std::string& path){
        auto it = textures.find(name);
        if(it != textures.end()){
            std::cout << "Texture [" << name << "] has been already loaded!\n";

            return it->second;
        }

        textures[name] = ::LoadTexture(path.c_str());
        return textures[name];
    }

    static Texture2D& GetTexture(const std::string& name) {
        auto it = textures.find(name);
        if(it == textures.end()){
            std::cout << "Texture " << "[" << name << "] not found!\n";
        }

        return it->second;
    }
private:
    static std::unordered_map<std::string, Texture2D> textures;
};