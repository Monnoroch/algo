#pragma once

#include "common.h"


namespace algo {

template<typename T>
class vector;

template<typename T>
class vector_view {
public:
	vector_view() = delete;
	vector_view(vector<T>& v, size_t f, size_t t) : vec(v), from(f), to(t) {
		assert(from <= v.size());
		assert(to <= v.size());
	}

	vector_view(vector<T>& v, size_t f = 0) : vector_view(v, f, v.size()) {}
	vector_view(const vector_view<T>&) = default;
	vector_view(vector_view<T>&&) = default;

	size_t size() const {
		return to - from;
	}

	const T& operator[](size_t n) const {
		return vec[from + n];
	}

	T& operator[](size_t n) {
		return vec[from + n];
	}

	vector_view<T> view(size_t f, size_t t) {
		return vector_view<T>(vec, from + f, from + t);
	}

	vector_view<T> view(size_t f = 0) {
		return view(f, size());
	}

	vector_view<const T> view(size_t f, size_t t) const {
		return vector_view<const T>(vec, from + f, from + t);
	}

	vector_view<const T> view(size_t f = 0) const {
		return view(f, size());
	}

private:
	vector<T>& vec;
	size_t from{0};
	size_t to{0};
};

}
