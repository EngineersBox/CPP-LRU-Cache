#include "lru.h"
#include "lru.cpp"
#include <iostream>
#include <random>
#include <cassert>

inline int randInRange(const int startInc, const int endExc) {
    std::random_device rd;
    std::mt19937 gen(rd());
    const std::uniform_int_distribution<> distribution(startInc, endExc + 1);
    return distribution(gen);
}

int main() {
    LRUCache::LRU<int,int,8> lru;

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
}