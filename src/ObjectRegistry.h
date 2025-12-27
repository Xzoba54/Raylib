#pragma once
#include <cstdint>
#include <string>
#include <functional>
#include <memory>
#include "Object.h"
#include "Register.h"

struct ObjectDef{
    ContentID id;
    std::string textureName;
    std::function<std::shared_ptr<Object>()> createFunction;
};

class ObjectRegistry{
public:
    static void Init();

    static const ObjectDef& Get(ContentID id){
        return objects[(int)id];
    }

    static const std::shared_ptr<Object> Create(ContentID id);
    static const std::shared_ptr<Object> Create(int id);

    static const bool Exists(ContentID id);

    static const bool IsPlaceable(ContentID id);
private:
    static ObjectDef objects[(int)ContentID::COUNT];
};