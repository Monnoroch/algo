#pragma once

#include "common.h"
#include "vector_view.h"


namespace algo {

template<typename T>
class vector {
public:
	using type = T;

	vector() = default;

	vector(const vector& v) {
		cp(v);
	}

	vector(vector&& v) {
		mv(std::move(v));
	}

	~vector() {
		drop();
	}

	vector& operator=(const vector& v) {
		drop();
		cp(v);
	}

	vector& operator=(vector&& v) {
		mv(std::move(v));
	}

	vector(size_t l, const T& val) : cap(l), len(l), arr(new T[cap]) {
		for (size_t i = 0; i < len; ++i) {
			arr[i] = val;
		}
	}

	explicit vector(vector_view<T> v) : cap(v.get_vector().capacity()), len(v.size()), arr(new T[cap]) {
		for (size_t i = 0; i < len; ++i) {
			arr[i] = v[i];
		}
	}

	const T& operator[](size_t n) const {
		assert(n < len);
		return arr[n];
	}

	T& operator[](size_t n) {
		assert(n < len);
		return arr[n];
	}

	size_t size() const {
		return len;
	}

	size_t capacity() const {
		return cap;
	}

	void push_back(const T& val) {
		enlarge();
		arr[len] = val;
		++len;
	}

	const T& back() const {
		assert(!empty());
		return arr[len - 1];
	}

	T& back()  {
		assert(!empty());
		return arr[len - 1];
	}

	const T& front() const {
		assert(!empty());
		return arr[0];
	}

	T& front()  {
		assert(!empty());
		return arr[0];
	}

	void pop_back() {
		arr[len - 1] = T{}; // delete
		--len;
	}

	void reserve(size_t s) {
		if (s <= cap) {
			return;
		}

		auto * new_arr = new T[s];
		for (size_t i = 0; i < len; ++i) {
			new_arr[i] = std::move(arr[i]);
		}
		drop();
		arr = new_arr;
		cap = s;
	}

	void insert(const T& val, size_t pos) {
		enlarge();
		for (size_t i = len - 1; i >= pos; --i) {
			arr[i + 1] = std::move(arr[i]);
		}
		arr[pos] = val;
		++len;
	}

	void remove(size_t pos) {
		for (size_t i = pos; i < len; ++i) {
			arr[i] = arr[i + 1];
		}
		--len;
	}

	void clear() {
		for (size_t i = 0; i < len; ++i) {
			arr[i] = T{};
		}
		len = 0;
	}

	vector_view<T> view(size_t from, size_t to) {
		return vector_view<T>(*this, from, to);
	}

	vector_view<T> view(size_t from = 0) {
		return view(from, size());
	}

	const vector_view<T> view(size_t from, size_t to) const {
		return vector_view<T>(*this, from, to);
	}

	const vector_view<T> view(size_t from = 0) const {
		return view(from, size());
	}

	bool empty() const {
		return len == 0;
	}

	void swap(vector& v) {
		using std::swap;
		swap(len, v.len);
		swap(cap, v.cap);
		swap(arr, v.arr);
	}

	bool operator==(const vector& r) const {
		if (len != r.len) {
			return false;
		}
		for (size_t i = 0; i < len; ++i) {
			if (arr[i] != r.arr[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(const vector& r) const {
		return !(*this == r);
	}

private:
	void drop() {
		delete [] arr;
	}

	void cp(const vector& v) {
		len = v.len;
		cap = v.cap;
		arr = new T[cap];
		for (size_t i = 0; i < len; ++i) {
			arr[i] = v.arr[i];
		}
	}

	void mv(vector&& v) {
		std::swap(len, v.len);
		std::swap(cap, v.cap);
		std::swap(arr, v.arr);
	}

	void enlarge() {
		if (len >= cap) {
			reserve(cap == 0 ? 1 : cap * 2);
		}
	}

	size_t len{0};
	size_t cap{0};
	T * arr{nullptr};
};

}
