#ifndef __LRU_CACHE_CONCEPT_H__
#define __LRU_CACHE_CONCEPT_H__

#include <optional>

namespace LRUCache {
    template<typename K, typename V>
    class LRU_Cache_Base {
    public:
        virtual ~LRU_Cache_Base() = default;
        virtual void reset() noexcept = 0;
        virtual void insert(const K& key, const V& value) = 0;
        virtual std::optional<V> get(const K& key) = 0;
        virtual void erase(const K& k)  = 0;
        virtual void clear() noexcept = 0;
    };
}

#endif //__LRU_CACHE_CONCEPT_H__
