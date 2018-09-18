#include "map.h"
#include "enemy.h"

//Animation
Animation::Animation(int x, int y,int width, int height, int gap, int nFrames, std::unique_ptr<Cache>& cache, std::string key){
    texture.loadFromImage(*cache->get(key));
    framecount = nFrames;
    for( int i = nFrames - 1; i >= 0; i--){
        frames.push_back({x, y + i * height + i*gap, width, height});
    };
};

Animation::Animation(){};

void Animation::ApplyToSprite( sf::Sprite& s, float enemywidth, float enemyheight){
    s.setTexture( texture );
    s.setTextureRect( frames[iFrame]);
    s.setScale( 1*tile / enemywidth, 1*tile / enemyheight);
    //s.setScale( 1.5, 1.5);
};

void Animation::Update( float dt ){
    timeElapsed += dt;
    while( timeElapsed >= holdTime)
    {
        timeElapsed -= holdTime;
        Advance();
    }
};

void Animation::Advance(){
    if( ++iFrame >= framecount)
    {
        iFrame = 0;
    }
};

//enemy
Enemy::Enemy(float x, float y, float enemy_width, float enemy_height, int gap, int nFrames, std::unique_ptr<Cache>& cache, std::string key)
    : 
    walk(x, y, enemy_width, enemy_height, gap, nFrames, cache, key){
    //(20, 30, 50, 56) <-- for manaman
    enemywidth = enemy_width;
    enemyheight = enemy_height;
};

Enemy::Enemy():walk(){};

void Enemy::Draw(RenderWindow &rw){
    rw.draw(Enemy_Sprite);
};

void Enemy::SetPosition(const Vector2f &Pos){
    startpos = Pos;
    pos = Pos;
};

void Enemy::SetVelocity(){
    vel = dir * speed;
};

void Enemy::Update(float dt, std::unique_ptr<Map>& atlas){
    pos += vel * dt;
    walk.Update( dt );
    walk.ApplyToSprite( Enemy_Sprite, enemywidth, enemyheight );
    Enemy_Sprite.setPosition(pos);
    if((int(pos.x) % int(tile)) == 0 && (int(pos.y) % int(tile)) == 0)
        atlas->Foot_Tiles[int(pos.y) / int(tile)][int(pos.x) / int(tile)] = 1;
};

void Enemy::SetDirection(){
    dir = {0.0f,0.0f};
    if(!Enemy_Path.empty()){
        pair<int, int> next = Enemy_Path.front();
        if (int(pos.x) < int(next.first*tile))
            dir.x += 1.0f;
        if (int(pos.x) == int(next.first*tile))
            dir.x = 0.0f;
        if (int(pos.x) > int(next.first*tile))
            dir.x -= 1.0f;
        if (int(pos.y) < int(next.second*tile))
            dir.y += 1.0f;
        if (int(pos.y) == int(next.second*tile))
            dir.y = 0.0f;
        if (int(pos.y) > int(next.second*tile))
            dir.y -= 1.0f;
        if ((int(pos.x) == int(next.first*tile)) && (int(pos.y) == int(next.second*tile)))
            Enemy_Path.pop_front();
    };
};

void Enemy::GetPath(LeePathfinder &EnemyPathcalc){
    vector<pair<int, int>> *enemy = EnemyPathcalc.CalculatePath();
    for (auto i = enemy->end()-1; i != enemy->begin()-1; i--){
    pair<int,int> value = *i;
	Enemy_Path.push_back(value);
	}
};