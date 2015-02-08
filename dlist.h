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
		if (empty()) {
			push_first(val);
		}
		else {
			head = std::make_unique<node>(val, std::move(head));
			head->next->prev = head.get();
			++len;
		}
	}

	T pop_front() {
		assert(len != 0);
		auto tmp = std::move(head);
		--len;
		if (len == 0) {
			last = nullptr;
			return tmp->val;
		}

		head = std::move(tmp->next);
		head->prev = nullptr;
		return tmp->val;
	}

	const T& front() const {
		return head->val;
	}

	T& front() {
		return head->val;
	}

	void push_back(const T& val) {
		if (empty()) {
			push_first(val);
		}
		else {
			push_back_nonempty(val);
		}
	}

	void push_back(dlist v) {
		push_back(std::move(v));
	}

	void push_back(dlist&& v) {
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
		assert(len != 0);
		if (len == 1) {
			auto tmp = std::move(head);
			last = nullptr;
			len = 0;
			return tmp->val;
		}

		auto tmp = std::move(last->prev->next);
		last = last->prev;
		--len;
		return tmp->val;
	}

	bool empty() const {
		return head == nullptr;
	}

	size_t size() const {
		return len;
	}

	void swap(dlist& r) {
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
	void push_first(const T& val) {
		head = std::make_unique<node>(val);
		last = head.get();
		++len;
	}

	void push_back_nonempty(const T& val) {
		last->next = std::make_unique<node>(val, nullptr, last);
		last = last->next.get();
		++len;
	}

	void set(const dlist& r) {
		if (r.empty()) {
			return;
		}

		const auto * tmp = r.head.get();
		push_first(tmp->val);
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
