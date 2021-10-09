#include "cache_entry.hpp"
#include <list>
#include <unordered_map>
#include <optional>

#ifndef __LRU_MAP_LIST_CACHE_H__
#define __LRU_MAP_LIST_CACHE_H__

namespace LRUCache {
    template<typename K, typename V, size_t N>
    class LRUCache_map_list : public LRUCache::LRU_Cache_Base<K,V> {
        static_assert(N > 0);
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

        virtual void reset() noexcept;
        virtual void insert(const K& key, const V& value);
        virtual std::optional<V> get(const K& key);
        virtual void erase(const K& key);
        virtual void clear() noexcept;
    };
}

#endif // __LRU_MAP_LIST_CACHE_H__
