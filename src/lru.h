#include <array>

#ifndef __LRU_CACHE_H__
#define __LRU_CACHE_H__

namespace LRUCache {
    template<class K, class V, std::size_t N>
    class LRU {
    public:
        struct CacheSlot {
            K key;
            V value;
        };

    private:
        unsigned index;
        CacheSlot cache[N];

    public:
        LRU() : index(0) {}

        void reset();
        bool find(const K &key, V &value);
        void insert(const K &key, const V &value);
    };
}

#endif // __LRU_CACHE_H__
