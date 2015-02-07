#pragma once

#include "common.h"


namespace algo {

template<typename T>
class vector;

template<typename T>
class vector_view {
public:
	vector_view() = delete;
	vector_view(const vector_view&) = default;
	vector_view(vector_view&&) = default;
	~vector_view() = default;
	vector_view& operator=(const vector_view& v) = delete;
	vector_view& operator=(vector_view&& v) = delete;

	vector_view(vector<T>& v, size_t f, size_t t) : vec(v), from(f), to(t) {
		assert(from <= v.size());
		assert(to <= v.size());
	}

	vector_view(vector<T>& v, size_t f = 0) : vector_view(v, f, v.size()) {}

	vector_view(const vector<T>& v, size_t f, size_t t) : vec(const_cast<vector<T>&>(v)), from(f), to(t) {
		assert(from <= v.size());
		assert(to <= v.size());
	}

	vector_view(const vector<T>& v, size_t f = 0) : vector_view(v, f, v.size()) {}

	size_t size() const {
		return to - from;
	}

	const T& operator[](size_t n) const {
		return vec[from + n];
	}

	T& operator[](size_t n) {
		return vec[from + n];
	}

	vector_view view(size_t f, size_t t) {
		return vector_view(vec, from + f, from + t);
	}

	vector_view view(size_t f = 0) {
		return view(f, size());
	}

	const vector_view view(size_t f, size_t t) const {
		return vector_view(vec, from + f, from + t);
	}

	const vector_view view(size_t f = 0) const {
		return view(f, size());
	}

	bool empty() const {
		return size() == 0;
	}

	const vector<T>& get_vector() const {
		return vec;
	}

private:
	vector<T>& vec;
	size_t from{0};
	size_t to{0};
};

}
