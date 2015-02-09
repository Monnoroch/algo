#pragma once

#include <limits>

#include "common.h"
#include "vector.h"
#include "pair.h"


namespace algo {

template<typename T>
class heap {
public:
	using type = T;

	heap() = default;
	heap(const heap&) = default;
	heap(heap&&) = default;
	~heap() = default;
	heap& operator=(const heap&) = default;
	heap& operator=(heap&&) = default;

	explicit heap(const vector_view<T>& v) : data(v) {
		for (int i = v.size() / 2; i >= 0; --i) {
			heapify(i);
		}
	}

	explicit heap(const vector<T>& v) : heap(v.view()) {}

	T pop_max() {
		assert(!empty());
		auto res = std::move(data[0]);
		if (data.size() != 1) {
			data[0] = std::move(data.back());
		}
		data.pop_back();
		if (!empty()) {
			heapify(0);
		}
		return res;
	}

	const T& max() const {
		assert(!empty());
		return data[0];
	}

	void push(const T& key) {
		data.push_back(key);
		auto n = data.size() - 1;
		while (n > 0 && data[parent(n)] < data[n]) {
			std::swap(data[n], data[parent(n)]);
			n = parent(n);
		}
	}

	bool empty() const {
		return data.empty();
	}

	void swap(heap& h) {
		using std::swap;
		swap(data, h.data);
	}

	size_t size() const {
		return data.size();
	}

private:
	void heapify(size_t i) {
		auto l = left(i);
		auto r = right(i);
		auto largest = i;
		if (l < size() && data[l] > data[largest]) {
			largest = l;
		}
		if (r < size() && data[r] > data[largest]) {
			largest = r;
		}

		if (largest != i) {
			std::swap(data[i], data[largest]);
			heapify(largest);
		}
	}

	int parent(size_t n) const {
		return (static_cast<int>(n) - 1) / 2;
	}

	size_t left(size_t n) {
		return 2 * n + 1;
	}

	size_t right(size_t n) {
		return left(n) + 1;
	}

	vector<T> data{};
};


template<typename K, typename V>
class heap<pair<K, V>> {
	using T = pair<K, V>;
public:
	void push(const K& key, const V& value) {
		push(pair<K, V>(key, value));
	}

	// code from here is the exact copy of a generic heap template.
public:
	using type = T;

	heap() = default;
	heap(const heap&) = default;
	heap(heap&&) = default;
	~heap() = default;
	heap& operator=(const heap&) = default;
	heap& operator=(heap&&) = default;

	explicit heap(const vector_view<T>& v) : data(v) {
		for (int i = v.size() / 2; i >= 0; --i) {
			heapify(i);
		}
	}

	explicit heap(const vector<T>& v) : heap(v.view()) {}

	T pop_max() {
		assert(!empty());
		auto res = std::move(data[0]);
		if (data.size() != 1) {
			data[0] = std::move(data.back());
		}
		data.pop_back();
		if (!empty()) {
			heapify(0);
		}
		return res;
	}

	const T& max() const {
		assert(!empty());
		return data[0];
	}

	void push(const T& key) {
		data.push_back(key);
		auto n = data.size() - 1;
		while (n > 0 && data[parent(n)] < data[n]) {
			std::swap(data[n], data[parent(n)]);
			n = parent(n);
		}
	}

	bool empty() const {
		return data.empty();
	}

	void swap(heap& h) {
		std::swap(data, h.data);
	}

	size_t size() const {
		return data.size();
	}

private:
	void heapify(size_t i) {
		auto l = left(i);
		auto r = right(i);
		auto largest = i;
		if (l < size() && data[l] > data[largest]) {
			largest = l;
		}
		if (r < size() && data[r] > data[largest]) {
			largest = r;
		}

		if (largest != i) {
			std::swap(data[i], data[largest]);
			heapify(largest);
		}
	}

	int parent(size_t n) const {
		return (static_cast<int>(n) - 1) / 2;
	}

	size_t left(size_t n) {
		return 2 * n + 1;
	}

	size_t right(size_t n) {
		return left(n) + 1;
	}

	vector<T> data{};
};

}
