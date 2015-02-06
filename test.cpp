#include "test.h"
#include "vector.h"
#include "vector_view.h"
#include "list.h"
#include "dlist.h"
#include "heap.h"
#include "pair.h"
#include "search.h"
#include "sort.h"

#include <iostream>


namespace algo {

static void vector_test() {
	vector<int> v;
	assert(v.size() == 0);

	v.push_back(10);
	v.push_back(1);
	v.push_back(2);
	assert(v.size() == 3);
	assert(v[0] == 10);
	assert(v[1] == 1);
	assert(v[2] == 2);

	vector<int> v1(5, 7);
	assert(v1.size() == 5);
	assert(v1[3] == 7);

	v1.insert(8, 3);
	assert(v1.size() == 6);
	assert(v1[3] == 8);
	assert(v1[4] == 7);

	v1.clear();
	assert(v1.size() == 0);

	const auto N = 1000;
	const auto D = 100;
	list<int> vec;
	for (size_t i = 0; i <= N; ++i) {
		vec.push_back(i);
	}

	assert(vec.size() == N + 1);
	assert(vec[0] == 0);
	assert(vec[27] == 27);
	assert(vec.back() == N);

	for (size_t i = 0; i < D; ++i) {
		vec.pop_back();
	}

	assert(vec.size() == N - D + 1);
	assert(vec.back() == N - D);
}

static void vector_view_test() {
	const auto N = 1000;
	vector<int> vec;
	for (size_t i = 0; i <= N; ++i) {
		vec.push_back(N - i);
	}
	assert(vec.size() == N + 1);

	auto view = vec.view(100, 200);
	assert(view.size() == 100);
	assert(view[0] == vec[100]);
	assert(view[view.size() - 1] == vec[200 - 1]);
}

static void list_test() {
	const auto N = 1000;
	const auto D = 100;
	list<int> lst;
	for (size_t i = 0; i <= N; ++i) {
		lst.push_back(i);
	}

	assert(lst.size() == N + 1);
	assert(lst[0] == 0);
	assert(lst[27] == 27);
	assert(lst.back() == N);

	for (size_t i = 0; i < D; ++i) {
		lst.pop_back();
	}

	assert(lst.size() == N - D + 1);
	assert(lst.back() == N - D);
}

static void dlist_test() {
	const auto N = 1000;
	const auto D = 100;
	dlist<int> lst;
	for (size_t i = 0; i <= N; ++i) {
		lst.push_back(i);
	}

	assert(lst.size() == N + 1);
	assert(lst[0] == 0);
	assert(lst[27] == 27);
	assert(lst.back() == N);

	for (size_t i = 0; i < D; ++i) {
		lst.pop_back();
	}

	assert(lst.size() == N - D + 1);
	assert(lst.back() == N - D);
}

static void heap_test() {
	const auto N = 1000;
	heap<int> h;
	for (size_t i = 0; i <= N; ++i) {
		h.push(i);
	}
	for (size_t i = 0; i <= N; ++i) {
		assert(h.pop_max() == N - i);
	}

	struct data {
		data() = default;
		data(int v_) : v(v_) {}
 		int v{0};
	};

	heap<pair<int, data>> hd;
	for (size_t i = 0; i <= N; ++i) {
		hd.push(i, N - i);
	}
	for (size_t i = 0; i <= N; ++i) {
		auto max = hd.pop_max();
		assert(max.first == N - i);
		assert(max.second.v == i);
	}
}

static void search_test() {
	const auto N = 1000;
	{

		vector<int> vec;
		for (size_t i = 0; i <= N; ++i) {
			vec.push_back(i);
		}
		assert(linear_search(vec, 44) == &vec[44]);
		assert(linear_search(vec, 2000) == nullptr);
		assert(binary_search(vec, 44) == &vec[44]);
		assert(binary_search(vec, 2000) == nullptr);
	}
	{
		vector<int> vec;
		for (size_t i = 0; i <= N; ++i) {
			vec.push_back(N - i);
		}
		assert(linear_search(vec, 44) == &vec[N - 44]);
		assert(linear_search(vec, 2000) == nullptr);
	}

}

template<typename T>
static void sort_test(const vector<T>& vec, bool sorted = false) {
	assert(sorted == check_sorted(vec));
	{
		auto tmp = vec;
		selection_sort(tmp);
		assert(check_sorted(tmp));
	}
	{
		auto tmp = vec;
		insertion_sort(tmp);
		assert(check_sorted(tmp));
	}
	{
		auto tmp = vec;
		bubble_sort(tmp);
		assert(check_sorted(tmp));
	}
	{
		auto tmp = vec;
		merge_sort(tmp);
		assert(check_sorted(tmp));
	}
	{
		auto tmp = vec;
		quick_sort(tmp);
		assert(check_sorted(tmp));
	}
	{
		auto tmp = vec;
		quick_sort(tmp, middle_pivot_strategy<int>);
		assert(check_sorted(tmp));
	}
	{
		auto tmp = vec;
		nocopy_quick_sort(tmp);
		assert(check_sorted(tmp));
	}
	{
		auto tmp = vec;
		nocopy_quick_sort(tmp, middle_pivot_strategy<int>);
		assert(check_sorted(tmp));
	}
	{
		auto tmp = vec;
		heap_sort(tmp);
		assert(check_sorted(tmp));
	}
}

static void sort_test() {
	const auto N = 1000;
	{

		vector<int> vec;
		for (size_t i = 0; i <= N; ++i) {
			vec.push_back(i);
		}
		sort_test(vec, true);
	}
	{
		vector<int> vec;
		for (size_t i = 0; i <= N; ++i) {
			vec.push_back(N - i);
		}
		sort_test(vec);
	}
}

void tests() {
	vector_test();
	vector_view_test();
	dlist_test();
	list_test();
	heap_test();
	search_test();
	sort_test();
}

}
