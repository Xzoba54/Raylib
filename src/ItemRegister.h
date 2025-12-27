#pragma once

#include "Register.h"
#include <string>

struct ItemDef{
    ContentID id;
    std::string textureName;    
};

class ItemRegistry{
public:
    static void Init();

    static const ItemDef& Get(ContentID id);
private:
    static ItemDef items[(int)ContentID::COUNT];
};