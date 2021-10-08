#ifndef __LRU_CACHE_ENTRY_H__
#define __LRU_CACHE_ENTRY_H__

namespace LRUCache {
    template<class K, class V>
    struct CacheEntry {
        K key;
        V value;
    };
}

#endif // __LRU_CACHE_ENTRY_H__
