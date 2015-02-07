#pragma once

#include <memory>

#include "common.h"


namespace algo {

template<typename T>
class dlist {
public:
	using type = T;

	struct node {
		friend class dlist;
		node() = default;
		node(const node&) = delete;
		node(node&&) = default;
		~node() = default;
		node& operator=(const node&) = delete;
		node& operator=(node&&) = default;

		node(const T& v) : val(v) {}
		node(const T& v, std::unique_ptr<node> n) : val(v), next(std::move(n)) {}
		node(const T& v, std::unique_ptr<node> n, node * p) : val(v), next(std::move(n)), prev(p) {}

	private:
		T val{};
		std::unique_ptr<node> next{};
		node * prev{nullptr};
	};

	dlist() = default;

	dlist(const dlist& r) {
		set(r);
	}

	dlist(dlist&&) = default;
	~dlist() = default;

	dlist& operator=(const dlist& r) {
		head = nullptr;
		set(r);
	}

	dlist& operator=(dlist&&) = default;

	void push_front(const T& val) {
		head = std::make_unique<node>(val, std::move(head));
		++len;
	}

	T pop_front() {
		assert(len != 0);
		auto tmp = std::move(head);
		head = std::move(tmp->next);
		--len;
		if (len == 0) {
			last = nullptr;
		}
		return tmp->val;
	}

	void push_front(dlist<T> v) {
		push_front(std::move(v));
	}

	void push_front(dlist<T>&& v) {
		if (v.empty()) {
			return;
		}

		if (empty()) {
			head = std::move(v.head);
			last = std::move(v.last);
			len = std::move(v.len);
			return;
		}

		v.last->next = std::move(head);
		head = std::move(v.head);
		len += v.len;
	}

	const T& front() const {
		return head->val;
	}

	T& front() {
		return head->val;
	}

	void push_back(const T& val) {
		if (head == nullptr) {
			push_back_empty(val);
		}
		else {
			push_back_nonempty(val);
		}
	}

	void push_back(dlist<T> v) {
		push_back(std::move(v));
	}

	void push_back(dlist<T>&& v) {
		if (head == nullptr) {
			head = std::move(v.head);
			last = std::move(v.last);
			len = std::move(v.len);
			return;
		}
		if (v.last == nullptr) {
			return;
		}
		last->next = std::move(v.head);
		last = v.last;
		len += v.len;
	}

	T pop_back() {
		auto res = std::move(last->val);
		last->prev->next = nullptr;
		last = last->prev;
		--len;
		return res;
	}

	void insert(const T& v) {

	}

	bool empty() const {
		return head == nullptr;
	}

	size_t size() const {
		return len;
	}

	void swap(dlist<T>& r) {
		std::swap(head, r.head);
		std::swap(last, r.last);
		std::swap(len, r.len);
	}

	const T& back() const {
		return last->val;
	}

	T& back() {
		return last->val;
	}

	const T& operator[](size_t n) const {
		assert(n < len);
		const auto * tmp = head.get();
		while (tmp != nullptr) {
			if (n == 0) {
				return tmp->val;
			}
			tmp = tmp->next;
			--n;
		}
		assert(false);
	}

	T& operator[](size_t n) {
		assert(n < len);
		auto * tmp = head.get();
		while (tmp != nullptr) {
			if (n == 0) {
				return tmp->val;
			}
			tmp = tmp->next.get();
			--n;
		}
		assert(false);
	}

private:
	void push_back_empty(const T& val) {
		head = std::make_unique<node>(val);
		last = head.get();
		++len;
	}

	void push_back_nonempty(const T& val) {
		last->next = std::make_unique<node>(val);
		last->next->prev = last;
		last = last->next.get();
		++len;
	}

	void set(const dlist<T>& r) {
		if (r.empty()) {
			return;
		}

		const auto * tmp = r.head.get();
		push_back_empty(tmp->val);
		tmp = tmp->next.get();
		while (tmp != nullptr) {
			push_back_nonempty(tmp->val);
			tmp = tmp->next.get();
		}
	}

	std::unique_ptr<node> head{};
	node * last{nullptr};
	size_t len{0};
};

}
