#pragma once

#include "common.h"
#include "vector.h"
#include "heap.h"


namespace algo {

template<typename T>
T * linear_search(vector<T>& vec, const T& val) {
	for (size_t i = 0; i < vec.size(); ++i) {
		if (vec[i] == val) {
			return &vec[i];
		}
	}
	return nullptr;
}

template<typename T>
T * binary_search(vector_view<T> vec, const T& val) {
	if (vec.empty()) {
		return nullptr;
	}

	const auto middle = vec.size() / 2;
	if (val == vec[middle]) {
		return &vec[middle];
	}
	else if (val > vec[middle]) {
		return binary_search(vec.view(middle + 1), val);
	}
	return binary_search(vec.view(0, middle), val);
}

template<typename T>
T * binary_search(vector<T>& vec, const T& val) {
	// assert(check_sorted(vec));
	return binary_search(vec.view(), val);
}

}
