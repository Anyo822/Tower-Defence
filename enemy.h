#pragma once
#include <SFML\Graphics.hpp>
#include <list>
#include <vector>
#include "Leepathfinder.h"

using namespace sf;


class Animation{
public:
    Animation(int x, int y, int width, int height, int gap, int nFrames, std::unique_ptr<Cache>& cache, std::string key);
    Animation();
    void ApplyToSprite( sf::Sprite& s, float enemywidth, float enemyheight);
    void Update( float dt );
private:
    void Advance();
private:
    int framecount;
    static constexpr float holdTime = 0.1f;
    Texture texture;
    std::vector<sf::IntRect> frames;
    int iFrame = 0;
    float timeElapsed = 0.0f;
};

class Enemy{
public:
    Enemy(float x, float y, float enemy_width, float enemy_height, int gap, int nFrames, std::unique_ptr<Cache>& cache, std::string key);
    Enemy();
    void Draw(RenderWindow &rw);
    void SetPosition(const Vector2f &Pos);
    void SetVelocity();
    void Update(float dt, std::unique_ptr<Map>& atlas);
    void SetDirection();
    void GetPath(LeePathfinder &EnemyPathcalc);
public:
    list<pair<int, int>> Enemy_Path;
private:
    static constexpr float speed = 75.0f;
    float enemywidth, enemyheight;
    Vector2f startpos;
    Vector2f pos;
    Vector2f vel = {0.0f,0.0f};
    Vector2f dir = {0.0f,0.0f};
    
    Sprite Enemy_Sprite;
    Animation walk;
};


//Enemy prototypes:
//Enemy Foe1(20.0f, 30.0f, 50.0f, 56.0f, "boss_manaman_processed.png", 0, 6);
//Enemy Foe2(16.0f, 28.0f, 67.0f, 80.0f, "boss_treatdrake.png", 40, 8);
//Enemy Foe3(34.0f, 48.0f, 51.0f, 59.0f, "f4_desolater.png", 62, 8);
//Enemy Foe4(25.0f, 79.0f, 71.0f, 36.0f, "f4_fallenaspect.png", 95, 7);