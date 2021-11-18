#include <cstdint>

#include <array>
#include <functional>
#include <forward_list>

#include <exception>

template<typename K, typename V>
struct HashEntry {
	K key;
	V value;
};

template<typename K, typename V, std::size_t N>
class HashTable {
	std::array<
		std::forward_list<HashEntry<K, V>>, N
	> table;
	std::hash<K> hasher;

	std::size_t hash(std::size_t value) const {
		return value % N;
	}
public:
	HashTable(): hasher{std::hash<K>()} { }

	void insert(const K& key, const V& value) {
		std::size_t hash_ = hash(key);
		table[hash_].push_front(
			HashEntry<K, V>{key, std::move(value)}
		);
	}

	bool remove(const K& key) {
		std::size_t hash_ = hash(key);
		auto& bucket = table[hash_];

		auto previous = bucket.before_begin();
		for(auto it = bucket.begin(); it != bucket.end(); ++previous, ++it) {
			if((*it).key == key) {
				return bucket.erase_after(previous) != bucket.end();
			}
		}
		return false;
	}

	const V& lookup(const K& key) const {
		std::size_t hash_ = hash(key);
		for(const auto& entry: table[hash_]) {
			if(entry.key == key) {
				return entry.value;
			}
		}
		throw std::out_of_range{"Not found"};
	}

	V& lookup(const K& key) {
		std::size_t hash_ = hash(key);
		for(auto& entry: table[hash_]) {
			if(entry.key == key) {
				return entry.value;
			}
		}
		throw std::out_of_range{"Not found"};
	}

	bool exists(const K& key) {
		std::size_t hash_ = hash(key);
		return !table[hash_].empty();
	}
};
