#include "map.h"

Map::Map(String File, std::unique_ptr<Cache>& cache){
    Map_Texture.loadFromImage(*cache->get("Map_Image"));
    Map_Sprite.setTexture(Map_Texture);

    foot_Texture.loadFromImage(*cache->get("Map_Image"));
    foot_Sprite.setTexture(foot_Texture);

    Texture temp;
    temp.loadFromImage(*cache->get("animation1"));
    animation_texture.push_back(temp);
    temp.loadFromImage(*cache->get("animation2"));
    animation_texture.push_back(temp);
};

void Map::Draw(RenderWindow &rw){
    for(int i = 0; i < Map_W; i++){
        for(int j = 0; j < Map_H; j++){
            if(Tiles[i][j] == 1)
                {Map_Sprite.setTextureRect(IntRect(0,1*64,64,64)); Map_Sprite.setScale(tile / 64, tile / 64);}
            if(Tiles[i][j] == 2)
                {Map_Sprite.setTextureRect(IntRect(9*64,2*64,64,64)); Map_Sprite.setScale(tile / 64, tile / 64);}
            if(Tiles[i][j] == 3)
                {Map_Sprite.setTextureRect(IntRect(8*64,2*64,64,64)); Map_Sprite.setScale(tile / 64, tile / 64);}
            if(Tiles[i][j] == 4)
                {Map_Sprite.setTextureRect(IntRect(0,4*64,64,64)); Map_Sprite.setScale(tile / 64, tile / 64);}
            if(Tiles[i][j] == 0)
                {Map_Sprite.setTextureRect(IntRect(0,2*64,64,64)); Map_Sprite.setScale(tile / 64, tile / 64);}
            Map_Sprite.setPosition(j*tile,i*tile);
            rw.draw(Map_Sprite);
            if(Foot_Tiles[i][j] == 1){
                foot_Sprite.setPosition(j*tile,i*tile);
                foot_Sprite.setTextureRect(IntRect(1*64,2*64,64,64));
                foot_Sprite.setScale(tile / 64, tile / 64);
                rw.draw(foot_Sprite);
            }
        }
    }
};

void Map::Read(){
    std::ifstream binfile;
    binfile.open("D:\\Projects\\Programming\\Praktica\\Lab04\\read.txt", std::ios::binary);
    while (!binfile.eof()){
        for(int i = 0; i < Map_W; i++){
            for(int j = 0; j < Map_H; j++){
                binfile.read((char*)&Tiles[i][j], sizeof(Tiles[i][j]));
            }
        }
    }
    binfile.close();
};

void Map::Write(){
    std::ofstream binfile;
    binfile.open ("D:\\Projects\\Programming\\Praktica\\Lab04\\write.txt", std::ios::binary);
    for(int i = 0; i < Map_W; i++){
        for(int j = 0; j < Map_H; j++){
            binfile.write((char*)&Tiles[i][j], sizeof(Tiles[i][j]));
        }
    }
    binfile.close();
};

void Map::CountEffective(std::list<std::pair<int, int>> &EnemyPath1, std::list<std::pair<int, int>> &EnemyPath2, std::list<std::pair<int, int>> &EnemyPath3){
    int q = 0;
    int count = 0;
    for(int i = 0; i < Map_H; i++){
        for(int j = 0; j < Map_W; j++){
            if(Tiles[i][j] == 4){
                for(int k = -Radius; k <= Radius; k++){
                    for(int kk = -Radius; kk <= Radius; kk++){
                        if((abs(k) + abs(kk) <= Radius) && (Tiles[i + k][j + kk] == 0)){
                                count++;
                                // now search for coincidences with enemy path
                                std::pair<int,int> xy;
                                xy.first = j + kk;
                                xy.second = i + k;
                                auto finder1 = std::find(std::begin(EnemyPath1), std::end(EnemyPath1), xy);
                                auto finder2 = std::find(std::begin(EnemyPath2), std::end(EnemyPath2), xy);
                                auto finder3 = std::find(std::begin(EnemyPath3), std::end(EnemyPath3), xy);
                                if (finder1 != std::end(EnemyPath1))
                                    count++;
                                if (finder2 != std::end(EnemyPath2))
                                    count++;
                                if (finder3 != std::end(EnemyPath3))
                                    count++;
                        }
                    }
                }
                effective_array[q].value = count;
                effective_array[q].y = i;
                effective_array[q].x = j;
                count = 0;
                q++;
            }
        }  
    }
};

void Map::SortEffective(){
    //gnome sort
    int i = 0;
    while(i < Towers) {
        if(i == 0 || effective_array[i - 1].value <= effective_array[i].value) ++i;
        else {
            Effective Temp = effective_array[i];
            effective_array[i] = effective_array[i - 1];
            effective_array[i - 1] = Temp;
            --i;
        }
    }
};

void Map::Animation_Draw(RenderWindow &rw){
    for (int i = Towers - 1; i >= Towers - 10; i--){
        animation_sprite.setTexture(animation_texture[currentTexture]);
        animation_sprite.setTextureRect(IntRect(0, 0, 64, 64));
        animation_sprite.setScale(tile / 64, tile / 64);
        animation_sprite.setPosition(effective_array[i].x * tile, effective_array[i].y * tile);
        rw.draw(animation_sprite);
    }
};

void Map::Animation_Update(float dt){
    totalTime += dt;

    if (totalTime >= switchTime){
        totalTime -= switchTime;
        currentTexture++;

        if(currentTexture >= textureCount){
            currentTexture = 0;
        }
    }
};