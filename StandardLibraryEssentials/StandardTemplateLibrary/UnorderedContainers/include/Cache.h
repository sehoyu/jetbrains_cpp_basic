#ifndef CPPBASICS_CACHE_H
#define CPPBASICS_CACHE_H
#include <iostream>
#include <string>
#include <list>
#include <unordered_map>

class LRUCache {
public:
    LRUCache(std::size_t capacity);
    std::string get(const std::string& key);
    void put(const std::string& key, const std::string& value);

private:
    std::size_t capacity;
    /* TODO */
};

#endif //CPPBASICS_CACHE_H