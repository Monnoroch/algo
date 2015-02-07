#pragma once

#include <memory>

#include "common.h"


namespace algo {

template<typename T>
class list {
public:
	using type = T;

	struct node {
		friend class list;
		node() = default;
		node(const node&) = delete;
		node(node&&) = default;
		~node() = default;
		node& operator=(const node&) = delete;
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

	void push_front(const T& val) {
		head = std::make_unique<node>(val, std::move(head));
		++len;
	}

	T pop_front() {
		assert(len != 0);
		auto tmp = std::move(head);
		head = std::move(tmp->next);
		--len;
		return tmp->val;
	}

	void push_front(list<T> v) {
		push_front(std::move(v));
	}

	void push_front(list<T>&& v) {
		if (v.empty()) {
			return;
		}

		if (empty()) {
			head = std::move(v.head);
			len = std::move(v.len);
			return;
		}

		auto end = v.head;
		while (end->next != nullptr) {
			end = end->next;
		}

		end->next = std::move(head);
		head = std::move(v.head);
		len += v.len;
	}

	bool empty() const {
		return head == nullptr;
	}

	size_t size() const {
		return len;
	}

	void swap(list<T>& r) {
		std::swap(head, r.head);
		std::swap(len, r.len);
	}

	const T& front() const {
		return head->val;
	}

	T& front() {
		return head->val;
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
	void set(const list<T>& r) {
		if (r.empty()) {
			return;
		}
		add_back(r.head);
	}

	void add_back(const std::unique_ptr<node>& node) {
		if (node == nullptr) {
			return;
		}
		add_back(node->next);
		push_front(node->val);
	}

	std::unique_ptr<node> head{};
	size_t len{0};
};

}
