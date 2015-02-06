#pragma once

#include <memory>

#include "common.h"


namespace algo {

template<typename T>
class list {
public:
	struct node {
		friend class list;
		node() = default;
		node(const node&) = default;
		node(node&&) = default;
		~node() = default;
		node& operator=(const node&) = default;
		node& operator=(node&&) = default;

		node(const T& v) : val(v) {}
		node(const T& v, std::unique_ptr<node> n) : val(v), next(std::move(n)) {}

	private:
		T val{};
		std::unique_ptr<node> next{};
	};

	list() = default;

	list(const list& r) {
		set(r);
	}

	list(list&&) = default;
	~list() = default;

	list& operator=(const list& r) {
		head = nullptr;
		set(r);
	}

	list& operator=(list&&) = default;

	void push_back(const T& val) {
		if (head == nullptr) {
			push_back_empty(val);
		}
		else {
			push_back_nonempty(val);
		}
	}

	void push_back(list<T> v) {
		push_back(std::move(v));
	}

	void push_back(list<T>&& v) {
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
		fix_last(); // because it's single-linked
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

	void swap(list<T>& r) {
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
	void fix_last() {
		auto * tmp = head.get();
		while (tmp != nullptr) {
			if (tmp->next.get() == last) {
				last = tmp;
				tmp->next = nullptr;
				return;
			}
			tmp = tmp->next.get();
		}
		assert(false);
	}

	void push_back_empty(const T& val) {
		head = std::make_unique<node>(val);
		last = head.get();
		++len;
	}

	void push_back_nonempty(const T& val) {
		last->next = std::make_unique<node>(val);
		last = last->next.get();
		++len;
	}

	void set(const list<T>& r) {
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
