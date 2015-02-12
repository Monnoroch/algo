#include "test.h"
#include "pair.h"
#include "vector.h"
#include "vector_view.h"
#include "list.h"
#include "dlist.h"
#include "heap.h"
#include "limited_heap.h"
#include "search_tree.h"

#include "stack.h"
#include "queue.h"
#include "dequeue.h"

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
	vector<int> vec;
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

	vector<int> vec1 = vec;
	assert(vec1.size() == vec.size());
	assert(vec1[7] == vec[7]);
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
		lst.push_front(i);
	}

	assert(lst.size() == N + 1);
	assert(lst[0] == N);
	assert(lst[27] == N - 27);
	assert(lst.front() == N);

	for (size_t i = 0; i < D; ++i) {
		lst.pop_front();
	}

	assert(lst.size() == N - D + 1);
	assert(lst.front() == N - D);

	list<int> lst1 = lst;
	assert(lst1.size() == lst.size());
	assert(lst1[7] == lst[7]);
}

static void dlist_test() {
	dlist<int> que;
	assert(que.empty());

	que.push_front(19);
	que.push_front(20);
	que.push_back(21);
	que.push_back(22);

	assert(que.pop_front() == 20);
	assert(que.pop_front() == 19);
	assert(que.pop_front() == 21);
	assert(que.pop_back() == 22);
	assert(que.empty());

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

	for (size_t i = 0; i < D; ++i) {
		lst.pop_front();
	}

	assert(lst.size() == N - D - D + 1);
	assert(lst.front() == D);

	dlist<int> lst1 = lst;
	assert(lst1.size() == lst.size());
	assert(lst1[7] == lst[7]);
}

static void heap_test() {
	const auto N = 1000;
	heap<int> h;
	for (size_t i = 0; i <= N; ++i) {
		h.push(i);
	}

	heap<int> h1 = h;
	assert(h1.size() == h.size());
	assert(h1.max() == h.max());

	for (size_t i = 0; i <= N; ++i) {
		assert(h.pop_max() == N - i);
	}

	struct data {
		data() = default;
		data(int v_) : v(v_) {}
 		int v{0};
	};

	heap_map<int, data> hd;
	for (size_t i = 0; i <= N; ++i) {
		hd.push(i, N - i);
	}
	for (size_t i = 0; i <= N; ++i) {
		auto max = hd.pop_max();
		assert(max.first == N - i);
		assert(max.second.v == i);
	}
}

static void limited_heap_test() {
	const auto N = 1000;
	const auto cnt = 200;
	limited_heap<int> h(cnt);
	for (size_t i = 0; i <= N; ++i) {
		h.push(i);
	}
	assert(h.size() == cnt);
	assert(h.max() == cnt - 1);

	limited_heap<int> h1 = h;
	assert(h1.size() == h.size());
	assert(h1.max() == h.max());

	for (size_t i = 0; i < cnt; ++i) {
		assert(h.pop_max() == cnt - i - 1);
	}

	struct data {
		data() = default;
		data(int v_) : v(v_) {}
		int v{0};
	};

	limited_heap<pair<int, data>> hd(cnt);
	for (size_t i = 0; i <= N; ++i) {
		hd.push(i, N - i);
	}
	for (size_t i = 0; i < cnt; ++i) {
		auto max = hd.pop_max();
		assert(max.first == cnt - i - 1);
		assert(max.second.v == N - (cnt - i - 1));
	}
}

static void search_tree_test() {
	const auto N = 1000;
	const auto K = 100;
	binary_tree<int> tree;
	assert(tree.empty());
	assert(tree.find(10) == nullptr);
	assert(tree.min() == nullptr);

	auto min = N + 1;
	auto max = 0;
	auto len = N;
	auto len2 = N;

	vector<int> set;

	vector<int> to_rem;
	const auto v = [&]() {
		for (size_t i = 0; i < N; ++i) {
			const auto v = rand() % N;
			if (v > max) {
				max = v;
			}
			if (v < min) {
				min = v;
			}

			if (i < K || i >= N - K) {
				to_rem.push_back(v);
			}

			if (!tree.insert(v)) {
				--len;
				--len2;
			}
			else {
				set.push_back(v);
			}
		}
		return 0;
	}();

	quick_sort(set);

	assert(tree.size() == len);
	assert(*tree.min() == min);
	assert(*tree.max() == max);

	for (size_t i = 0; i < to_rem.size(); ++i) {
		if (tree.remove(to_rem[i])) {
			--len2;
			int * val = nullptr;
			while ((val = binary_search(set, to_rem[i])) != nullptr) {
				set.remove(val - &set[0]);
			}
		}
	}

	const auto min2 = set.front();
	const auto max2 = set.back();

	assert(tree.size() == len2);
	assert(*tree.min() == min2);
	assert(*tree.max() == max2);
}

template<typename ST>
static void stack_test() {
	ST stack;
	assert(stack.empty());

	stack.push(19);
	stack.push(20);

	ST stack1 = stack;
	assert(stack1.size() == stack.size());
	assert(stack1.peek() == stack.peek());

	assert(!stack.empty());
	assert(stack.size() == 2);
	assert(stack.peek() == 20);
	assert(stack.pop() == 20);
	assert(stack.pop() == 19);
	assert(stack.empty());

}

static void stack_test() {
	stack_test<stack<int, vector>>();
	stack_test<list_stack<int>>();
	stack_test<dlist_stack<int>>();
}

static void queue_test() {
	queue<int> que;
	assert(que.empty());

	que.push_back(20);
	que.push_back(19);
	que.push_back(21);
	que.push_back(22);

	queue<int> que1 = que;
	assert(que1.size() == que.size());
	assert(que1.peek_front() == que.peek_front());

	assert(!que.empty());
	assert(que.size() == 4);
	assert(que.peek_front() == 20);
	assert(que.pop_front() == 20);
	assert(que.pop_front() == 19);
	assert(que.pop_front() == 21);
	assert(que.pop_front() == 22);
	assert(que.empty());
}

static void dequeue_test() {
	dequeue<int> que;
	assert(que.empty());

	que.push_front(19);
	que.push_front(20);
	que.push_back(21);
	que.push_back(22);

	dequeue<int> que1 = que;
	assert(que1.size() == que.size());
	assert(que1.peek_front() == que.peek_front());

	assert(!que.empty());
	assert(que.size() == 4);
	assert(que.peek_front() == 20);
	assert(que.peek_back() == 22);
	assert(que.pop_front() == 20);
	assert(que.pop_front() == 19);
	assert(que.pop_front() == 21);
	assert(que.pop_back() == 22);
	assert(que.empty());
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
	vector<T> correct;
	{
		auto tmp = vec;
		selection_sort(tmp);
		assert(check_sorted(tmp));
		correct = tmp;
	}
	{
		auto tmp = vec;
		insertion_sort(tmp);
		assert(check_sorted(tmp));
		assert(tmp == correct);
	}
	{
		auto tmp = vec;
		bubble_sort(tmp);
		assert(check_sorted(tmp));
		assert(tmp == correct);
	}
	{
		auto tmp = vec;
		merge_sort(tmp);
		assert(check_sorted(tmp));
		assert(tmp == correct);
	}
	{
		auto tmp = vec;
		copy_quick_sort(tmp);
		assert(check_sorted(tmp));
		assert(tmp == correct);
	}
	{
		auto tmp = vec;
		copy_quick_sort(tmp, middle_pivot_strategy<int>);
		assert(check_sorted(tmp));
		assert(tmp == correct);
	}
	{
		auto tmp = vec;
		quick_sort(tmp);
		assert(check_sorted(tmp));
		assert(tmp == correct);
	}
	{
		auto tmp = vec;
		quick_sort(tmp, middle_pivot_strategy<int>);
		assert(check_sorted(tmp));
		assert(tmp == correct);
	}
	{
		auto tmp = vec;
		heap_sort(tmp);
		assert(check_sorted(tmp));
		assert(tmp == correct);
	}
	{
		auto tmp = vec;
		counting_sort(tmp);
		assert(check_sorted(tmp));
		assert(tmp == correct);
	}
	{
		auto tmp = vec;
		lsd_radix_sort(tmp);
		assert(check_sorted(tmp));
		assert(tmp == correct);
	}
	{
		auto tmp = vec;
		lsd_radix_sort<T, 2>(tmp);
		assert(check_sorted(tmp));
		assert(tmp == correct);
	}
	{
		auto tmp = vec;
		msd_radix_sort(tmp);
		assert(check_sorted(tmp));
		assert(tmp == correct);
	}
	{
		auto tmp = vec;
		msd_radix_sort<T, 2>(tmp);
		assert(check_sorted(tmp));
		assert(tmp == correct);
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
	{
		vector<int> vec;
		for (size_t i = 0; i <= N; ++i) {
			vec.push_back(rand() % 1000);
		}
		sort_test(vec);
	}
	{
		vector<int> vec;
		vec.push_back(796);
		vec.push_back(723);
		vec.push_back(618);
		vec.push_back(245);
		vec.push_back(846);
		vec.push_back(451);
		vec.push_back(921);
		vec.push_back(555);
		vec.push_back(379);
		vec.push_back(488);
		vec.push_back(764);
		vec.push_back(228);
		vec.push_back(841);
		vec.push_back(350);
		vec.push_back(193);
		vec.push_back(500);
		vec.push_back(34);
		vec.push_back(764);
		sort_test(vec);
	}
}

void tests() {
	// datastructures
	vector_test();
	vector_view_test();
	dlist_test();
	list_test();
	heap_test();
	limited_heap_test();
	search_tree_test();

	// interfaces
	stack_test();
	queue_test();
	dequeue_test();

	// algorithms
	search_test();
	sort_test();
}

}
