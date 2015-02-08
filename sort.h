#pragma once

#include "common.h"
#include "vector.h"
#include "heap.h"


namespace algo {

template<typename T>
bool check_sorted(const vector<T>& v) {
	for (size_t i = 1; i < v.size(); ++i) {
		if (v[i] < v[i - 1]) {
			return false;
		}
	}
	return true;
}

template<typename T>
void selection_sort(vector<T>& v) {
	const auto size = v.size();
	for (size_t i = 0; i < size; ++i) {
		auto min_pos = i;
		for (size_t j = i + 1; j < size; ++j) {
			if (v[j] < v[min_pos]) {
				min_pos = j;
			}
		}
		if (i != min_pos) {
			std::swap(v[i], v[min_pos]);
		}
	}
}

template<typename T>
void insertion_sort(vector<T>& v) {
	const auto size = v.size();
	for (size_t i = 1; i < size; ++i) {
		auto cur = std::move(v[i]);
		auto to_pos = static_cast<int>(i) - 1;
		while (to_pos >= 0 && v[to_pos] > cur) {
			v[to_pos + 1] = std::move(v[to_pos]);
			--to_pos;
		}

		++to_pos;
		if (i != to_pos) {
			v[to_pos] = std::move(cur);
		}
	}
}

template<typename T>
void bubble_sort(vector<T>& v) {
	const auto size = v.size();
	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < size - i - 1; ++j) {
			if (v[j] > v[j + 1]) {
				std::swap(v[j], v[j + 1]);
			}
		}
	}
}

template<typename T>
void merge(vector_view<T> l, vector_view<T> r) {
	const auto size = l.size() + r.size();
	vector<T> vec(size, 0);
	size_t lidx = 0, ridx = 0;
	for (size_t idx = 0; idx < size; ++idx) {
		if (lidx >= l.size() || (ridx < r.size() && r[ridx] < l[lidx])) {
			vec[idx] = r[ridx];
			++ridx;
		} else {
			vec[idx] = l[lidx];
			++lidx;
		}
	}
	for (size_t idx = 0; idx < l.size(); ++idx) {
		l[idx] = vec[idx];
	}
	for (size_t idx = 0; idx < r.size(); ++idx) {
		r[idx] = vec[l.size() + idx];
	}
}

template<typename T>
void merge_sort(vector_view<T> v) {
	if (v.size() <= 1) {
		return;
	}

	const auto middle = v.size() / 2;
	auto left = v.view(0, middle);
	auto right = v.view(middle);
	merge_sort(left);
	merge_sort(right);
	merge(left, right);
}

template<typename T>
void merge_sort(vector<T>& v) {
	merge_sort(v.view());
}

template<typename T>
T middle_pivot_strategy(vector_view<T> v) {
	return v[v.size() / 2];
}

template<typename T>
T random_pivot_strategy(vector_view<T> v) {
	return v[rand() % v.size()];
}

template<typename T, typename PS>
void quick_sort(vector_view<T> v, PS&& ps) {
	if (v.size() <= 1) {
		return;
	}

	const auto pivot = ps(v);
	int i = 0;
	int j = static_cast<int>(v.size()) - 1;
	vector<T> left, right;
	size_t eq_cnt = 0;
	for (size_t i = 0; i < v.size(); ++i) {
		if (v[i] < pivot) {
			left.push_back(v[i]);
		}
		else if (v[i] > pivot) {
			right.push_back(v[i]);
		}
		else {
			++eq_cnt;
		}
	}

	if (left.size() != 0) {
		quick_sort(left, ps);
	}
	if (right.size() != 0) {
		quick_sort(right, ps);
	}

	for (size_t i = 0; i < left.size(); ++i) {
		v[i] = left[i];
	}
	for (size_t i = 0; i < eq_cnt; ++i) {
		v[left.size() + i] = pivot;
	}
	for (size_t i = 0; i < right.size(); ++i) {
		v[left.size() + eq_cnt + i] = right[i];
	}
}

template<typename T, typename PS>
void quick_sort(vector<T>& v, PS&& ps) {
	quick_sort(v.view(), std::forward<PS>(ps));
}

template<typename T>
void quick_sort(vector<T>& v) {
	quick_sort(v, random_pivot_strategy<T>);
}

template<typename T, typename PS>
void nocopy_quick_sort(vector_view<T> v, PS&& ps) {
	if (v.size() <= 1) {
		return;
	}

	const auto pivot = ps(v);
	int i = 0;
	int j = static_cast<int>(v.size()) - 1;
	while (i <= j) {
		while (v[i] < pivot) {
			++i;
		}
		while (v[j] > pivot) {
			--j;
		}
		if (i < j) {
			std::swap(v[i], v[j]);
		}
		if (i <= j) {
			++i;
			--j;
		}
	}

	if (i < v.size()) {
		quick_sort(v.view(i), ps);
	}

	if (j != 0) {
		quick_sort(v.view(0, j + 1), ps);
	}
}

template<typename T, typename PS>
void nocopy_quick_sort(vector<T>& v, PS&& ps) {
	nocopy_quick_sort(v.view(), std::forward<PS>(ps));
}

template<typename T>
void nocopy_quick_sort(vector<T>& v) {
	nocopy_quick_sort(v, random_pivot_strategy<T>);
}

template<typename T>
void heap_sort(vector<T>& v) {
	heap<T> h(v);
	for (int i = h.size() - 1; i >= 0; --i) {
		v[i] = h.pop_max();
	}
}

/// T can only be an integer type
template<typename T>
void counting_sort(vector<T>& v, T min, T max) {
	size_t counts[max - min + 1];
	for (size_t i = 0; i < max - min; ++i) {
		counts[i] = 0;
	}

	for (size_t i = 0; i < v.size(); ++i) {
		++counts[v[i] - min];
	}

	size_t total = 0;
	for (size_t i = 0; i <= max - min; ++i) {
		auto cnt = counts[i];
		counts[i] = total;
		total += cnt;
	}

	vector<T> out(v.size(), 0);
	for (size_t i = 0; i < v.size(); ++i) {
		auto key = v[i] - min;
		out[counts[key]] = v[i];
		++counts[key];
	}
	v = out;
}

/// T can only be an integer type
template<typename T>
void counting_sort(vector<T>& v) {
	auto min = v[0];
	auto max = v[0];
	for (size_t i = 1; i < v.size(); ++i) {
		if (v[i] > max) {
			max = v[i];
		}
		else if (v[i] < min) {
			min = v[i];
		}
	}
	return counting_sort(v, min, max);
}

/// T can only be an integer type
template<typename T, size_t Base = 10>
void radix_sort(vector<T>& v, T max) {
	for (size_t num = 1; num <= max; num *= Base) {
		vector<T> buckets[Base];
		for (size_t i = 0; i < v.size(); ++i) {
			const auto& val = v[i];
			buckets[(val / num) % Base].push_back(val);
		}

		size_t cnt = 0;
		for (size_t i = 0; i < Base; ++i) {
			const auto& bucket = buckets[i];
			for (size_t k = 0; k < bucket.size(); ++k) {
				v[cnt] = bucket[k];
				++cnt;
			}
		}
	}
}

/// T can only be an integer type
template<typename T, size_t Base = 10>
void radix_sort(vector<T>& v) {
	auto max = v[0];
	for (size_t i = 1; i < v.size(); ++i) {
		if (v[i] > max) {
			max = v[i];
		}
	}
	return radix_sort(v, max);
}

}
