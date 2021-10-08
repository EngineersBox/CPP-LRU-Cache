#include "lru_array.h"

// Based on an implementation by Unai Landa

constexpr unsigned NIBBLE_SHIFT_TO_DWORD = 0xffffffff;

template<class K, class V, std::size_t N>
 inline void LRUCache::LRU_array<K,V,N>::reset() {
    this->index = 0;
}

template<class K, class V, std::size_t N>
inline bool LRUCache::LRU_array<K,V,N>::find(const K &key, V &value) {
    unsigned nibbleOffset = NIBBLE_SHIFT_TO_DWORD;
    unsigned idx = this->index;
    LRUCache::LRU_array<K,V,N>::CacheSlot *currentEntryPtr = (cache - 1);
    while (idx) {
        const unsigned hit = idx & 0xf;
        nibbleOffset <<= 4;
        if (currentEntryPtr[hit].key == key) {
            this->index = (index & nibbleOffset) | ((index << 4) & (~nibbleOffset)) | hit;
            value = currentEntryPtr[hit].value;
            return true;
        }
        idx >>= 4;
    }
    return false;
}

template<class K, class V, std::size_t N>
inline void LRUCache::LRU_array<K,V,N>::insert(const K &key, const V &value) {
    LRUCache::LRU_array<K,V,N>::CacheSlot *currentEntryPtr = this->cache - 1;
    unsigned hit = this->index >> 28;
    if (!hit) {
        hit = 1;
        unsigned idx = this->index;
        while (idx & 0xf) { idx >>= 4, ++hit; }
    }
    currentEntryPtr[hit].key = key;
    currentEntryPtr[hit].value = value;
    this->index = (index << 4) | hit;
}