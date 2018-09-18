#include "cache.h"

Cache::Cache(int cacheSize)
{
    cache_size = cacheSize;
}

sf::Image* Cache::get(std::string key)
{
    auto it = item_map.find(key);
    item_list.splice(item_list.begin(), item_list, it->second);
    sf::Image* ptr = &(it->second->second);
    return ptr;
}

void Cache::put(std::string key, std::string path)
{   
    sf::Image value;
    value.loadFromFile(path);
    auto it = item_map.find(key);
    if(it != item_map.end())
    {
        item_list.erase(it->second);
        item_map.erase(it);
    }
    item_list.push_front(std::make_pair(key, value));
    item_map.insert(std::make_pair(key, item_list.begin()));
    clean();
}

void Cache::clean()
{
    while(item_map.size() > cache_size)
    {
        auto it = item_list.end();
        it--;
        item_map.erase(it->first);
        item_list.pop_back();        
    }
}
