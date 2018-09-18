#include <SFML\Graphics.hpp>
#include <fstream>
#include <iostream>
#include <list>
#include "map.h"
#include "LeePathfinder.h"
#include "enemy.h"
#include "cache.h"



int main()
{   
    sf::RenderWindow window(sf::VideoMode(resolution, resolution), "Lab04");

    Cache* cache_ptr = new Cache(100000);
    std::unique_ptr<Cache> cache(cache_ptr);
    cache->put("Map_Image", "master-tileset.png");
    cache->put("animation1", "animation1.png");
    cache->put("animation2", "animation2.png");
    cache->put("manaman", "boss_manaman_processed.png");
    cache->put("treatdrake", "boss_treatdrake.png");
    cache->put("desolater", "f4_desolater.png");

    Map* atlas_ptr = new Map("master-tileset.png", cache);
    std::unique_ptr<Map> atlas(atlas_ptr);// = std::make_unique<Map>("master-tileset.png");
    
    Enemy* foe_ptr = new Enemy[3];
    std::unique_ptr<Enemy[]> Foe(foe_ptr);// = std::make_unique<Enemy[]>(3);
    Foe[0] = Enemy(20.0f, 30.0f, 50.0f, 56.0f, 0, 6, cache, "manaman");
    Foe[1] = Enemy(16.0f, 28.0f, 67.0f, 80.0f, 40, 8, cache, "treatdrake");
    Foe[2] = Enemy(34.0f, 48.0f, 51.0f, 59.0f, 62, 8, cache, "desolater");

    Foe[0].SetPosition({tile*0,tile*5});
    Foe[1].SetPosition({tile*8,tile*0});
    Foe[2].SetPosition({tile*18,tile*2});
   
    LeePathfinder enemyPath1(atlas, Map_W, Map_H, 5, 0, 16, 18);
    LeePathfinder enemyPath2(atlas, Map_W, Map_H, 0, 8, 16, 18);
    LeePathfinder enemyPath3(atlas, Map_W, Map_H, 2, 18, 16, 18);
	Foe[0].GetPath(enemyPath1);
    Foe[1].GetPath(enemyPath2);
    Foe[2].GetPath(enemyPath3);
    
    atlas->CountEffective(Foe[0].Enemy_Path, Foe[1].Enemy_Path, Foe[2].Enemy_Path);
    atlas->SortEffective();
    Clock clock;

    while (window.isOpen())
    {   
        float dt = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();
        }

        Foe[0].SetDirection();
        Foe[1].SetDirection();
        Foe[2].SetDirection();
        
        Foe[0].SetVelocity();
        Foe[1].SetVelocity();
        Foe[2].SetVelocity();

        window.clear();
        
        Foe[0].Update(dt, atlas);
        Foe[1].Update(dt, atlas);
        Foe[2].Update(dt, atlas);
        atlas->Animation_Update(dt);

        atlas->Draw(window);
        atlas->Animation_Draw(window);
        Foe[0].Draw(window);
        Foe[1].Draw(window);   
        Foe[2].Draw(window);   

        window.display();
    }

    return 0;
}
/*
v idk.0 old path calculation:
list<pair<int, int>> Enemy_Path2;
    vector<pair<int, int>> *enemy2 = Enemy2.CalculatePath();
    for (auto i = enemy2->end()-1; i != enemy2->begin()-1; i--){
		pair<int,int> value = *i;
        Enemy_Path2.push_back(value);
	}

v3.0

for (auto i = Enemy_Path1.begin(); i !=Enemy_Path1.end(); i++)
	{
		cout << i->second<< "  " << i->first << endl;
	}
cout << "next path" << "\n";
for (auto i = Enemy_Path2.begin(); i !=Enemy_Path2.end(); i++)
	{
		cout << i->second<< "  " << i->first << endl;
	}
cout << "next path" << "\n";
for (auto i = Enemy_Path3.begin(); i !=Enemy_Path3.end(); i++)
	{
		cout << i->second<< "  " << i->first << endl;
	}
    system("pause");


//list<pair<int, int>> *Enemy_Path2 = Enemy2.CalculatePath();

v2.0

for (int i = Enemy_Path1->size()-1; i > 0 ; i--)
	{
		cout << (*Enemy_Path1)[i].second<< "  " << (*Enemy_Path1)[i].first << endl;
	}
cout << "next path" << "\n";
for (int i = Enemy_Path2->size()-1; i > 0 ; i--)
	{
		cout << (*Enemy_Path2)[i].second<< "  " << (*Enemy_Path2)[i].first << endl;
	}
cout << "next path" << "\n";
for (int i = Enemy_Path3->size()-1; i > 0 ; i--)
	{
		cout << (*Enemy_Path3)[i].second<< "  " << (*Enemy_Path3)[i].first << endl;
	}
    system("pause");

v1.0
LeePathfinder c(*atlas.Tiles, Map_W, Map_H, 0, 8, 16, 18);
	vector<pair<int, int>> *a = c.CalculatePath();
    
    for (int i = 0; i < a->size(); i++)
	{
		cout << (*a)[i].second<< "  " << (*a)[i].first << endl;
	}

//lee(atlas.Tiles, 8, 0, 18, 16);

*/