#include "../include/Cache.h"

LRUCache::LRUCache(std::size_t capacity) : capacity(capacity) {}

std::string LRUCache::get(const std::string& key) {
    /* TODO */
}

void LRUCache::put(const std::string& key, const std::string& value) {
    /* TODO */
}

int main() {
    LRUCache cache(4);
    cache.put("1", "one");
    cache.put("2", "two");
    cache.put("3", "three");
    cache.put("4", "four");
    std::cout << cache.get("1") << '\n'; // one
    cache.put("5", "five");
    std::cout << cache.get("2") << '\n'; // Key: <2> not found!
    return 0;
}