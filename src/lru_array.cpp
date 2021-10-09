#include "lru_array.h"

// Based on an implementation by Unai Landa

constexpr unsigned NIBBLE_SHIFT_TO_DWORD = 0xffffffff;

template<typename K, typename V, size_t N>
inline LRUCache::LRU_array<K,V,N>::~LRU_array() {
    this->clear();
}

template<typename K, typename V, size_t N>
inline void LRUCache::LRU_array<K,V,N>::reset() noexcept {
    this->index = 0;
}

template<typename K, typename V, size_t N>
inline LRUCache::CacheEntry<K,V>* LRUCache::LRU_array<K,V,N>::find(const K& key) {
    unsigned nibbleOffset = NIBBLE_SHIFT_TO_DWORD;
    unsigned idx = this->index;
    LRUCache::CacheEntry<K,V> **currentEntryPtr = this->cache - 1;
    while (idx) {
        const unsigned hit = idx & 0xf;
        nibbleOffset <<= 4;
        if (currentEntryPtr[hit]->key == key) {
            this->index = (index & nibbleOffset) | ((index << 4) & (~nibbleOffset)) | hit;
            return currentEntryPtr[hit];
        }
        idx >>= 4;
    }
    return nullptr;
}

template<typename K, typename V, size_t N>
std::optional<V> LRUCache::LRU_array<K,V,N>::get(const K &key) {
    LRUCache::CacheEntry<K,V> *elementPtr = this->find(key);
    if (elementPtr == nullptr) {
        return {};
    }
    return elementPtr->value;
}

template<typename K, typename V, size_t N>
void LRUCache::LRU_array<K,V,N>::insert(const K &key, const V &value) {
    LRUCache::CacheEntry<K,V> **currentEntryPtr = this->cache - 1;
    unsigned hit = this->index >> 28;
    if (!hit) {
        hit = 1;
        unsigned idx = this->index;
        while (idx & 0xf) { idx >>= 4, ++hit; }
    }
    currentEntryPtr[hit] = new LRUCache::CacheEntry<K,V>{ .key = key, .value = value};
    this->index = (index << 4) | hit;
}

template<typename K, typename V, size_t C>
void LRUCache::LRU_array<K,V,C>::erase(const K& key) {
    LRUCache::CacheEntry<K,V> *elementPtr = this->find(key);
    delete elementPtr;
}

template<typename K, typename V, size_t N>
inline void LRUCache::LRU_array<K,V,N>::clear() noexcept {
    std::fill_n(this->cache, N, nullptr);
}