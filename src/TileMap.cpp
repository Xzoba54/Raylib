#include "TileMap.h"

TileMap::TileMap(){
    this->hoverRec = {0, 0, static_cast<float>(TILESIZE), static_cast<float>(TILESIZE)};
}

void TileMap::SetObject(int x, int y, ContentID objectID){
    if(!IsValidPosition(x, y)) return;
    if(HasObject(x, y)) return;

    std::shared_ptr<Object> object = ObjectRegistry::Create(objectID);
    objects[object->GetID()] = object;
    tiles[y][x]->SetObject(object);
}

void TileMap::RemoveObject(int x, int y){
    tiles[y][x]->SetObject(nullptr);
}

Vector2 TileMap::GetSize() const{
    return {static_cast<float>(width), static_cast<float>(height)};
}

bool TileMap::HasObject(int x, int y) const{
    if(!IsValidPosition(x, y))return false;

    return tiles[y][x]->GetObject() != nullptr;
}

bool TileMap::IsValidPosition(int x, int y) const{
    return (x >= 0 && x < width && y >= 0 && y < height);
}

void TileMap::Serialize(std::vector<uint8_t> &out) const{
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            uint8_t ground = static_cast<uint8_t>(tiles[y][x]->GetGroundID());
            out.push_back(ground);
        }
    }
}

void TileMap::Deserialize(int width, int height, std::vector<uint8_t> data){
    this->width = width;
    this->height = height;

    tiles.clear();
    tiles.resize(height, std::vector<std::shared_ptr<Tile>>(width));

    int i =  0;
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            GroundID groundID = static_cast<GroundID>(data[i]);
            tiles[y][x] = std::make_shared<Tile>(x * TILESIZE, y * TILESIZE, groundID);
            i++;
        }
    }
}

std::shared_ptr<Object> TileMap::GetObject(int x, int y) const{
    if(!IsValidPosition(x, y)) return nullptr;
    if(!HasObject(x, y)) return nullptr;

    return tiles[y][x]->GetObject();
}

ContentID TileMap::GetObjectType(int x, int y) const{
    if(!IsValidPosition(x, y)) return ContentID::None;
    if(!HasObject(x, y)) return ContentID::None;

    return tiles[y][x]->GetType();
}

void TileMap::LoadMapFromFile(){
    stream.open("save.txt", std::ios::in);
    if(!stream.is_open()){
        std::cout << "Failed to open a save file\n";
    }

    stream >> this->width >> this->height;

    tiles.clear();
    tiles.resize(height, std::vector<std::shared_ptr<Tile>>(width));

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            int id;
            stream >> id;
            GroundID groundID = static_cast<GroundID>(id);

            tiles[y][x] = std::make_shared<Tile>(x * TILESIZE, y * TILESIZE, groundID);
        }
    }

    int n;
    stream >> n;
    while(n--){
        int id, x, y;
        stream >> id >> x >> y;

        this->SetObject(x, y, ContentID(id));
    }
    stream.close();
}

void TileMap::Update(const Vector2 &mousePos){
    if(!IsWindowFocused()) return;

    hoverRec.x = int(mousePos.x) / TILESIZE;
    hoverRec.y = int(mousePos.y) / TILESIZE;
}

void TileMap::RenderObjectAt(int x, int y){
    tiles[y][x]->RenderObject();
}

void TileMap::RenderObjectsExcept(std::vector<std::pair<int, int>> except){
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            auto it = std::find(except.begin(), except.end(), std::make_pair(x, y));
            if(it != except.end()) continue;

            tiles[y][x]->RenderObject();
        }
    }
}

void TileMap::RenderGround(){
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            tiles[y][x]->Render();

            if(x == hoverRec.x && y == hoverRec.y){
                this->hoverRec.x = x * TILESIZE;
                this->hoverRec.y = y * TILESIZE;

                DrawRectangleLinesEx(hoverRec, 1.0f, YELLOW);
            }
        }
    }
}