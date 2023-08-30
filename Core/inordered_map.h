#pragma once
#include "pch.h"

template<typename K, typename V>
struct m_Iterator {

	inline const K& first() { return *ptr; }

	inline const V& second() { return value.at(ptr - key.begin()); }

	inline const size_t index() { return (ptr - key.begin()); }

	inline m_Iterator& operator+(const size_t index) { ptr += index; return *this; }

	inline m_Iterator& operator-(const size_t index) { ptr -= index; return *this; }

	inline m_Iterator& operator++() { ++ptr; return *this; }

	inline m_Iterator& operator*() { return *this; }

	inline bool operator!=(const m_Iterator& right) { return (ptr != right.ptr); }

protected:
	m_Iterator& m_begin() {
		ptr = key.begin();
		return *this;
	}

	m_Iterator& m_end() {
		ptr = key.end();
		return *this;
	}

	typename std::vector<K>::iterator ptr;

	std::vector<K> key;
	std::vector<V> value;
};

template<typename K, typename V>
class inordered_map : public m_Iterator<K, V>
{
public:
	/////////////////////////////////////////////// GET //////////////////////////////////////////////////

	inline m_Iterator<K, V>& begin() { return this->m_begin(); }

	inline m_Iterator<K, V>& end() { return this->m_end(); }

	inline V& front() { return this->value.front(); }

	inline V& back() { return this->value.back(); }

	inline V& at(const K& key) { return (this->value.at(std::find(this->key.begin(), this->key.end(), key) - this->key.begin())); }

	inline V& at(const size_t& index) { return this->value.at(index); }

	inline V& operator[](const size_t& index) { return this->value[index]; }

	inline V& operator[](const K& key) { return (this->value[std::find(this->key.begin(), this->key.end(), key) - this->key.begin()]); }

	inline const size_t size() { return this->key.size(); }

	const size_t find(const V& value) {
		return (std::find(this->value.begin(), this->value.end(), value) - this->value.begin());
	}

	const size_t find(const K& key) {
		return (std::find(this->key.begin(), this->key.end(), key) - this->key.begin());
	}

	const bool contain(const K& key) {
		return (std::find(this->key.begin(), this->key.end(), key) != this->key.end());
	}

	///////////////////////////////////////////////////// SET ////////////////////////////////////////////////////////
	void insert(const K& key, const V& value) {
		this->key.push_back(key);
		this->value.push_back(key);
	}

	void insert(const std::pair<K, V>& pair) {
		this->key.push_back(pair.first);
		this->value.push_back(pair.second);
	}

	template<typename...ty1, typename...ty2>
	void emplace_back(const std::tuple<ty1...>& arg1, const std::tuple<ty2...>& arg2) {
		std::apply([=](auto...args) {this->key.emplace_back(args...); }, arg1);
		std::apply([=](auto...args) {this->value.emplace_back(args...); }, arg2);
	}

	void erase(const size_t index) {
		this->key.erase(this->key.begin() + index);
		this->value.erase(this->value.begin() + index);
	}

	void erase(const K& key) {
		const unsigned int index = (std::find(this->key.begin(), this->key.end(), key) - this->key.begin());
		this->key.erase(this->key.begin() + index);
		this->value.erase(this->value.begin() + index);
	}

	void clear()
	{
		this->key.clear();
		this->value.clear();
		this->ptr = this->key.begin();
	}
};