#pragma once

#include "common.h"


namespace algo {

template<typename K, typename V>
struct pair {
	pair() = default;
	pair(const pair&) = default;
	pair(pair&&) = default;
	~pair() = default;
	pair& operator=(const pair&) = default;
	pair& operator=(pair&&) = default;

	pair(const K& k, const V& v) : first(k), second(v) {}

	bool operator==(const pair& r) const {
		return first == r.first;
	}

	bool operator!=(const pair& r) const {
		return !(*this == r);
	}

	bool operator<(const pair& r) const {
		return first < r.first;
	}

	bool operator<=(const pair& r) const {
		return first <= r.first;
	}

	bool operator>(const pair& r) const {
		return first > r.first;
	}

	bool operator>=(const pair& r) const {
		return first >= r.first;
	}

	K first{};
	V second{};
};

}
