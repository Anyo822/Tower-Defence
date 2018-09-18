#pragma once

#include <SFML\Graphics.hpp>
#include <unordered_map>
#include <list>
#include <utility>


class Cache
{
public:
    Cache(int cacheSize);
    Cache(Cache const &) = delete;
	void operator=(Cache) = delete;
    sf::Image* get(std::string key);
    void put(std::string key, std::string path);    
private:
    void clean();
private:
    size_t cache_size;
    std::list <std::pair<std::string, sf::Image>> item_list;
    std::unordered_map<std::string, decltype(item_list.begin())> item_map;
};