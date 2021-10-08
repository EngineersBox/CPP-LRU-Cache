#include <list>
#include <unordered_map>
#include <optional>

#ifndef __LRU_MAP_LIST_CACHE_H__
#define __LRU_MAP_LIST_CACHE_H__

namespace LRUCache {

    template<typename K, typename V>
    struct CacheEntry {
        const K key;
        const V value;
    };

    template<typename K, typename V, size_t C>
    class LRUCache_map_list {
        static_assert(C > 0);
    private:
        using CacheEntries = std::list<CacheEntry<K,V>>;
        CacheEntries entries;
        std::unordered_map<K, typename std::list<CacheEntry<K,V>>::iterator> cache;
    public:
        LRUCache_map_list() = default;

        using iterator = typename CacheEntries::iterator;
        using const_iterator = typename CacheEntries::const_iterator;
        iterator begin() noexcept {
            return this->entries.begin();
        }
        iterator end() noexcept {
            return this->entries.end();
        }
        const_iterator begin() const noexcept {
            return this->entries.begin();
        }
        const_iterator end() const noexcept {
            return this->entries.end();
        }

        bool insert(const K& k, const V& v);
        std::optional<V> get(const K& k);
        void erase(const K& k);
    };
}

#endif // __LRU_MAP_LIST_CACHE_H__
