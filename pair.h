#pragma once

#include "common.h"


namespace algo {

template<typename K, typename V>
struct pair {
	pair() = default;
	pair(const pair<K, V>&) = default;
	pair(pair<K, V>&&) = default;
	~pair() = default;
	pair<K, V>& operator=(const pair<K, V>&) = default;
	pair<K, V>& operator=(pair<K, V>&&) = default;

	pair(const K& k, const V& v) : first(k), second(v) {}

	bool operator==(const pair<K, V>& r) const {
		return first == r.first;
	}

	bool operator!=(const pair<K, V>& r) const {
		return !(*this == r);
	}

	bool operator<(const pair<K, V>& r) const {
		return first < r.first;
	}

	bool operator<=(const pair<K, V>& r) const {
		return first <= r.first;
	}

	bool operator>(const pair<K, V>& r) const {
		return first > r.first;
	}

	bool operator>=(const pair<K, V>& r) const {
		return first >= r.first;
	}

	K first{};
	V second{};
};

}
