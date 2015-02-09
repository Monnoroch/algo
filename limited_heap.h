#pragma once

#include <limits>

#include "common.h"
#include "vector.h"
#include "pair.h"
#include "heap.h"


namespace algo {

/// the heap with only N minimal elements
template<typename T>
class limited_heap {
public:
	using type = T;

	limited_heap() = delete;
	limited_heap(const limited_heap&) = default;
	limited_heap(limited_heap&&) = default;
	~limited_heap() = default;
	limited_heap& operator=(const limited_heap&) = default;
	limited_heap& operator=(limited_heap&&) = default;

	explicit limited_heap(size_t n) : N(n) {}
	explicit limited_heap(size_t n, const vector_view<T>& v) : N(n), data(v) {}
	explicit limited_heap(const vector<T>& v) : limited_heap(v.view()) {}

	T pop_max() {
		return data.pop_max();
	}

	const T& max() const {
		return data.max();
	}

	bool push(const T& key) {
		if (size() < max_size()) {
			data.push(key);
			return true;
		}

		if (key > max()) {
			return false;
		}

		pop_max();
		data.push(key);
		return true;
	}

	bool empty() const {
		return data.empty();
	}

	size_t size() const {
		return data.size();
	}

	size_t max_size() const {
		return N;
	}

	size_t set_max_size(size_t n) {
		while (size() > n) {
			(void) pop_max();
		}
		N = n;
	}

	void swap(limited_heap& r) {
		using std::swap;
		swap(N, r.N);
		swap(data, r.data);
	}

private:
	size_t N{0};
	heap<T> data{};
};


template<typename K, typename V>
class limited_heap<pair<K, V>> {
	using T = pair<K, V>;
public:
	void push(const K& key, const V& value) {
		push(pair<K, V>(key, value));
	}

	// code from here is the exact copy of a generic heap template.
public:
	using type = T;

	limited_heap() = delete;
	limited_heap(const limited_heap&) = default;
	limited_heap(limited_heap&&) = default;
	~limited_heap() = default;
	limited_heap& operator=(const limited_heap&) = default;
	limited_heap& operator=(limited_heap&&) = default;

	explicit limited_heap(size_t n) : N(n) {}
	explicit limited_heap(size_t n, const vector_view<T>& v) : N(n), data(v) {}
	explicit limited_heap(const vector<T>& v) : limited_heap(v.view()) {}

	T pop_max() {
		return data.pop_max();
	}

	const T& max() const {
		return data.max();
	}

	bool push(const T& key) {
		if (size() < max_size()) {
			data.push(key);
			return true;
		}

		if (key > max()) {
			return false;
		}

		pop_max();
		data.push(key);
		return true;
	}

	bool empty() const {
		return data.empty();
	}

	void swap(limited_heap& h) {
		std::swap(data, h.data);
		std::swap(N, h.N);
	}

	size_t size() const {
		return data.size();
	}

	size_t max_size() const {
		return N;
	}

	size_t set_max_size(size_t n) {
		while (size() > n) {
			(void) pop_max();
		}
		N = n;
	}

private:
	size_t N{0};
	heap<T> data{};
};

}
