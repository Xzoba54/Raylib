#include "ItemRegister.h"

ItemDef ItemRegistry::items[(int)ContentID::COUNT];

    void ItemRegistry::Init(){
        items[(int)ContentID::Pickaxe] = {ContentID::Pickaxe, "PICKAXE"};
        items[(int)ContentID::Chest] = {ContentID::Chest, "CHEST"};
    }

const ItemDef &ItemRegistry::Get(ContentID id){
    return items[int(id)];
}
