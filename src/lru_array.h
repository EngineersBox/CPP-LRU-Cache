#include "cache_entry.hpp"
#include <array>

#ifndef __LRU_ARRAY_CACHE_H__
#define __LRU_ARRAY_CACHE_H__

namespace LRUCache {
    template<class K, class V, std::size_t N>
    class LRU_array {
    private:
        unsigned index;
        LRUCache::CacheEntry<K,V> cache[N];

    public:
        LRU_array() : index(0) {}

        void reset();
        bool find(const K &key, V &value);
        void insert(const K &key, const V &value);
    };
}

#endif // __LRU_ARRAY_CACHE_H__
