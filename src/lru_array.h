#include "cache_entry.hpp"
#include "lru_cache_base.hpp"
#include <array>
#include <optional>

#ifndef __LRU_ARRAY_CACHE_H__
#define __LRU_ARRAY_CACHE_H__

namespace LRUCache {
    template<typename K, typename V, size_t N>
    class LRU_array : public LRUCache::LRU_Cache_Base<K,V> {
    private:
        unsigned index = 0;
        LRUCache::CacheEntry<K,V>* cache[N];
        LRUCache::CacheEntry<K,V>* find(const K& key);
    public:
        LRU_array() = default;
        virtual ~LRU_array();

        using iterator = typename LRUCache::CacheEntry<K, V>*;
        using const_iterator = typename LRUCache::CacheEntry<K, V>*;
        iterator begin() noexcept {
            return std::begin(this->cache);
        }
        iterator end() noexcept {
            return std::end(this->cache);
        }
        const_iterator begin() const noexcept {
            return std::begin(this->cache);
        }
        const_iterator end() const noexcept {
            return std::end(this->cache);
        }

        virtual void reset() noexcept;
        virtual void insert(const K& key, const V& value);
        virtual std::optional<V> get(const K& key);
        virtual void erase(const K& k);
        virtual void clear() noexcept;
    };
}

#endif // __LRU_ARRAY_CACHE_H__
