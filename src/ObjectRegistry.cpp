#include "ObjectRegistry.h"
#include "Wall.h"
#include "Chest.h"

ObjectDef ObjectRegistry::objects[(int)ContentID::COUNT];

void ObjectRegistry::Init(){
    objects[(int)ContentID::Chest] = {ContentID::Chest, "CHEST", [](){ return std::make_shared<Chest>(); }};
    objects[(int)ContentID::Wall] = {ContentID::Wall, "WALL", [](){ return std::make_shared<Wall>(); }};
}

const std::shared_ptr<Object> ObjectRegistry::Create(ContentID id){
    return objects[(int)id].createFunction();
}

const std::shared_ptr<Object> ObjectRegistry::Create(int id){
    return objects[id].createFunction();
}

const bool ObjectRegistry::Exists(ContentID id){
    return id > ContentID::None && id < ContentID::COUNT && objects[(int)id].createFunction != nullptr;
}

const bool ObjectRegistry::IsPlaceable(ContentID id){
    return ObjectRegistry::Exists(id);
}
