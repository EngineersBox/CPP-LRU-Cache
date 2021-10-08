#include "lru_array.cpp"
#include "lru_map_list.cpp"
#include <iostream>
#include <random>
#include <cassert>
#include <sstream>

inline int randInRange(const int startInc, const int endExc) {
    std::random_device rd;
    std::mt19937 gen(rd());
    const std::uniform_int_distribution<> distribution(startInc, endExc + 1);
    return distribution(gen);
}

template<typename K, typename V, size_t C>
std::string joinEntries(const LRUCache::LRUCache_map_list<K,V,C>& values, const std::string& delimiter) {
    std::ostringstream returnString;
    for (auto entry = values.begin(); entry != values.end(); ++entry){
        returnString << entry->key << " => " << entry->value;
        if (entry != values.end()) {
            returnString << delimiter;
        }
    }
    return returnString.str();
}

int main() {
    LRUCache::LRU_array<int,int,8> lru;

    lru.reset();

    int runs  = 1000;
    int range = 256;
    int hits  = 0;
    for(int i = runs - 1; i >= 0; --i) {
        int key = randInRange(0, range);
        int val = -1;
        if (!lru.find(key,val)) {
            std::cout << "Key " << key << " not found, inserting" << std::endl;
            lru.insert(key, key);
        } else {
            std::cout << "Key " << key << " found" << std::endl;
            assert(key == val);
            ++hits;
        }
    }
    std::cout << "Total hits: " << hits << std::endl;

    LRUCache::LRUCache_map_list<std::string, double, 3> cache;

    cache.insert("London", 8.4);
    cache.insert("Toronto", 2.5);
    cache.insert("Sydney", 5.2);
    std::cout << joinEntries<std::string, double>(cache, ", ") << std::endl;
    std::cout << "London => " << cache.get("London").value_or(-1) << std::endl;
    std::cout << joinEntries<std::string, double>(cache, ", ") << std::endl;
    cache.insert("Tokyo", 9.4);
    std::cout << joinEntries<std::string, double>(cache, ", ") << std::endl;

    return 0;
}