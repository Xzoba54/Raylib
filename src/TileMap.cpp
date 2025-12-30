#include "TileMap.h"

void TileMap::Render()
{
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

void TileMap::RenderBelowPlayer(int playerY){
    for(int y = playerY; y < height; y++){
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

void TileMap::RenderGround(){
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            tiles[y][x]->Render();
        }
    }
}

void TileMap::RenderTile(int x, int y){
    tiles[y][x]->RenderObject();
}

void TileMap::Update(const Vector2 &mousePos)
{
    if(IsWindowFocused()){
        hoverRec.x = int(mousePos.x) / TILESIZE;
        hoverRec.y = int(mousePos.y) / TILESIZE;
    }
}

void TileMap::Init(){
    this->hoverRec = {0, 0, (float)TILESIZE, (float)TILESIZE};

    this->LoadMapFromFile();
}

void TileMap::SetObject(int x, int y, ContentID objectID){
    if(!IsValidPosition(x, y)) return;
    if(HasObject(x, y)) return;

    std::shared_ptr<Object> object = ObjectRegistry::Create(objectID);
    std::shared_ptr<Tile> tile = tiles[y][x];

    tile->SetObject(object);
}

void TileMap::RemoveObject(int x, int y){
    tiles[y][x]->SetObject(nullptr);
}

bool TileMap::HasObject(int x, int y) const
{
    if(!IsValidPosition(x, y)){
        return false;
    }

    return tiles[y][x]->GetObject() != nullptr;
}

bool TileMap::IsValidPosition(int x, int y) const
{
    return (x >= 0 && x < width && y >= 0 && y < height);
}

std::shared_ptr<Object> TileMap::GetObject(int x, int y) const{
    if(!IsValidPosition(x, y)){
        return nullptr;
    }
    if(!HasObject(x, y)){
        return nullptr;
    }

    std::shared_ptr<Object> object = tiles[y][x]->GetObject();

    return object;
}

ContentID TileMap::GetObjectID(int x, int y) const{
    if(!IsValidPosition(x, y)){
        return ContentID::None;
    }
    if(!HasObject(x, y)){
        return ContentID::None;
    }

    return tiles[y][x]->GetObjectID();
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
            int texID;
            stream >> texID;

            tiles[y][x] = std::make_shared<Tile>(x * TILESIZE, y * TILESIZE, TextureManager::GetTexture(IDToNames[texID]));
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