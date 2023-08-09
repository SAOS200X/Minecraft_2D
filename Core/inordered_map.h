#pragma once
#include "pch.h"

template<typename K,typename V>
struct m_Iterator {

	const K& first()  {
		return *ptr;
	}

	const V& second()  {
		return m_map.at(*ptr);
	}

	const unsigned int index() {
		return (ptr - order.begin());
	}

	m_Iterator& operator++()  {
		++ptr;
		return *this;
	}
	
	m_Iterator& operator*()  {
		return *this;
	}

	bool operator!=(const m_Iterator& right)  {
		return (ptr != right.ptr);
	}

protected:
	m_Iterator& m_begin()  {
		ptr = order.begin();
		return *this;
	}

	m_Iterator& m_end()  {
		ptr = order.end();
		return *this;
	}

	typename std::vector<K>::iterator ptr;
	
	std::map<K, V> m_map;
	std::vector<K> order;
};

template<typename K, typename V>
class inordered_map : public m_Iterator<K,V>
{
public:
/////////////////////////////////////////////// GET //////////////////////////////////////////////////

	m_Iterator<K,V>& begin()  {
		return this->m_begin();
	}

	m_Iterator<K,V>& end()  {
		return this->m_end();
	}

	V& front()  {
		return this->m_map[this->order.front()];
	}

	V& back()  {
		return this->m_map[this->order.back()];
	}

	V& at(const K& key)  {
		if (this->m_map.count(key))
			return this->m_map.at(key);
	}

	V& at(const K&& key)  {
		if (this->m_map.count(key))
			return this->m_map.at(key);
	}

	V& at(const unsigned int index)  {
		if (index < this->order.size())
			return this->m_map.at(this->order.at(index));
	}

	V& operator[](const unsigned int index)  {
		return this->m_map[this->order[index]];
	}

	V& operator[](const K&& key)  {
		return this->m_map[key];
	}

	V& operator[](const K& key)  {
		return this->m_map[key];
	}

	const unsigned int size()  {
		return this->order.size();
	}

	const unsigned int find(V&& value) {
		for (size_t i = 0; i < this->order.size(); i++) {
			if (this->m_map[this->order.at(i)] == value)
				return i;
		}
	}

	const unsigned int find2(V&& value) {
		for (auto i = this->order.begin(); i != this->order.end(); ++i) {
			if (this->m_map[*i] == value)
				return (i - this->order.begin());
		}
	}

	const bool contain(K&& key) {
		return this->m_map.count(key);
	}

	const bool contain(K& key) {
		return this->m_map.count(key);
	}

///////////////////////////////////////////////////// SET ////////////////////////////////////////////////////////
	void insert(K&& key, V&& value)  {
		this->m_map.insert({ key,value });
		this->order.push_back(key);
	}

	void insert(std::pair<K,V>&& pair) {
		this->m_map.insert(pair);
		this->order.push_back(pair.first);
	}

	template<typename ty1, typename...ty2>
	void emplace_back(ty1&& arg, ty2&&...args)  {
		this->m_map.emplace(arg, args...);
		this->order.emplace_back(arg);
	}

	void erase(const unsigned int index)  {
		if (index < this->order.size())
		{
			this->m_map.erase(this->order.at(index));
			this->order.erase(this->order.begin() + index);
		}
	}

	void erase(const K&& key)  {
		if (std::find(this->order.begin(), this->order.end(), key) != this->order.end())
		{
			this->m_map.erase(key);
			this->order.erase(std::find(this->order.begin(), this->order.end(), key));
		}
	}

	void erase(const K& key)  {
		if (std::find(this->order.begin(), this->order.end(), key) != this->order.end())
		{
			this->m_map.erase(key);
			this->order.erase(std::find(this->order.begin(), this->order.end(), key));
		}
	}

	void clear()
	{
		this->m_map.clear();
		this->order.clear();
		this->ptr = this->order.begin();
	}
};