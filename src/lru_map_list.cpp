#include <iostream>
#include "lru_map_list.hpp"

template<typename K, typename V, size_t C>
bool LRUCache::LRUCache_map_list<K,V,C>::insert(const K& key, const V& value) {
    if (this->cache.count(key)) {
        return false;
    }
    if (this->entries.size() == C) {
        this->cache.erase(this->entries.back().key);
        this->entries.pop_back();
    }
    this->entries.emplace_front(CacheEntry<K,V>{ .key =  key, .value =  value });
    this->cache.emplace(key, this->entries.begin());
    return true;
}

template<typename K, typename V, size_t C>
std::optional<V> LRUCache::LRUCache_map_list<K,V,C>::get(const K& key) {
    auto entry = this->cache.find(key);
    if(entry == this->cache.end()) {
        return {};
    }
    this->entries.splice(this->entries.begin(), this->entries, entry->second);
    return entry->second->value;
}

template<typename K, typename V, size_t C>
void LRUCache::LRUCache_map_list<K,V,C>::erase(const K& k) {
    auto entry = this->cache.find(k);
    if(entry == this->cache.end()) {
        return;
    }
    this->entries.erase(entry->second);
    this->cache.erase(entry);
}

