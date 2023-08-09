#pragma once
#include "pch.h"

template<typename K, typename V>
struct m_Iterator {
	template<typename k, typename v>
	friend class inordered_map;

	const K& first() {
		return *ptr;
	}

	const V& second() {
		return m_map.at(*ptr);
	}

	const unsigned int index() {
		return (ptr - order.begin());
	}

	m_Iterator& operator++() {
		++ptr;
		return *this;
	}

	m_Iterator& operator*() {
		return *this;
	}

	bool operator!=(const m_Iterator& right) {
		return (ptr != right.ptr);
	}

private:
	m_Iterator& m_begin() {
		ptr = order.begin();
		return *this;
	}

	m_Iterator& m_end() {
		ptr = order.end();
		return *this;
	}

	typename std::vector<K>::iterator ptr;

	std::map<K, V> m_map;
	std::vector<K> order;
};



template<typename K, typename V>
class inordered_map
{
private:
	m_Iterator<K, V> it;
public:
	/////////////////////////////////////////////// GET //////////////////////////////////////////////////

	m_Iterator<K, V>& begin() {
		return it.m_begin();
	}

	m_Iterator<K, V>& end() {
		return it.m_end();
	}

	V& front() {
		return it.m_map[it.order.front()];
	}

	V& back() {
		return it.m_map[it.order.back()];
	}

	V& at(const K& key) {
		if (it.m_map.count(key))
			return it.m_map.at(key);
	}

	V& at(const K&& key) {
		if (it.m_map.count(key))
			return it.m_map.at(key);
	}

	V& at(const unsigned int index) {
		if (index < it.order.size())
			return it.m_map.at(it.order.at(index));
	}

	V& operator[](const unsigned int index) {
		return it.m_map[it.order[index]];
	}

	V& operator[](const K&& key) {
		return it.m_map[key];
	}

	V& operator[](const K& key) {
		return it.m_map[key];
	}

	const unsigned int size() {
		return it.order.size();
	}

	const unsigned int find(V&& value) {
		for (size_t i = 0; i < it.order.size(); i++) {
			if (it.m_map[it.order.at(i)] == value)
				return i;
		}
	}

	const unsigned int find2(V&& value) {
		for (auto i = it.order.begin(); i != it.order.end(); ++i) {
			if (it.m_map[*i] == value)
				return (i - it.order.begin());
		}
	}

	const bool contain(K&& key) {
		return it.m_map.count(key);
	}

	const bool contain(K& key) {
		return it.m_map.count(key);
	}

	///////////////////////////////////////////////////// SET ////////////////////////////////////////////////////////
	void insert(K&& key, V&& value) {
		it.m_map.insert({ key,value });
		it.order.push_back(key);
	}

	void insert(std::pair<K, V>&& pair) {
		it.m_map.insert(pair);
		it.order.push_back(pair.first);
	}

	template<typename ty1, typename...ty2>
	void emplace_back(ty1&& arg, ty2&&...args) {
		it.m_map.emplace(arg, args...);
		it.order.emplace_back(arg);
	}

	void erase(const unsigned int index) {
		if (index < it.order.size())
		{
			it.m_map.erase(it.order.at(index));
			it.order.erase(it.order.begin() + index);
		}
	}

	void erase(const K&& key) {
		if (std::find(it.order.begin(), it.order.end(), key) != it.order.end())
		{
			it.m_map.erase(key);
			it.order.erase(std::find(it.order.begin(), it.order.end(), key));
		}
	}

	void erase(const K& key) {
		if (std::find(it.order.begin(), it.order.end(), key) != it.order.end())
		{
			it.m_map.erase(key);
			it.order.erase(std::find(it.order.begin(), it.order.end(), key));
		}
	}

	void clear()
	{
		it.m_map.clear();
		it.order.clear();
		it.ptr = it.order.begin();
	}
};