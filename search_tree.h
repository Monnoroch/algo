#pragma once

#include <memory>

#include "common.h"


namespace algo {

template<typename T>
class binary_tree {
	struct node {
		node() = delete;
		node(const node& r) : val(r.val), left(std::make_unique<node>(*r.left.get())), right(std::make_unique<node>(*r.right.get())) {}
		node(node&&) = default;
		~node() = default;

		node& operator=(const node& r) {
			val = r.val;
			left = std::make_unique<node>(*r.left.get());
			right = std::make_unique<node>(*r.right.get());
		}

		node& operator=(node&&) = default;

		node(const T& v, std::unique_ptr<node> l = nullptr, std::unique_ptr<node> r = nullptr) : val(v), left(std::move(l)), right(std::move(r)) {}

		size_t hight() const {
			const auto lh = binary_tree::hight(left);
			const auto rh = binary_tree::hight(right);
			return (lh > rh ? lh : rh) + 1;
		}

		bool is_leaf() const {
			return left == nullptr && right == nullptr;
		}

		node * min_node() {
			return left == nullptr ? this : left->min_node();
		}

		node * max_node() {
			return right == nullptr ? this : right->max_node();
		}

		T val;
		std::unique_ptr<node> left;
		std::unique_ptr<node> right;
	};
public:
	using type = T;

	binary_tree() = default;
	binary_tree(const binary_tree& r) : head(std::make_unique<node>(*r.head.get())), cnt(r.cnt) {}
	binary_tree(binary_tree&&) = default;
	~binary_tree() = default;

	binary_tree& operator=(const binary_tree& r) {
		cnt = r.cnt;
		head = std::make_unique<node>(*r.head.get());
	}

	binary_tree& operator=(binary_tree&&) = default;

	size_t size() const {
		return cnt;
	}

	bool empty() const {
		return cnt == 0;
	}

	size_t hight() const {
		return hight(head);
	}

	void swap(binary_tree& r) {
		using std::swap;
		swap(head, r.head);
		swap(cnt, r.cnt);
	}

	bool insert(const T& val) {
		if (empty()) {
			head = std::make_unique<node>(val);
			++cnt;
			return true;
		}

		auto * tmp = head.get();
		while (true) {
			if (tmp->val == val) {
				return false;
			}
			if (val < tmp->val) {
				auto * l = tmp->left.get();
				if (l == nullptr) {
					tmp->left = std::make_unique<node>(val);
					break;
				}
				tmp = l;
			}
			else {
				auto * r = tmp->right.get();
				if (r == nullptr) {
					tmp->right = std::make_unique<node>(val);
					break;
				}
				tmp = r;
			}
		}
		++cnt;
		return true;
	}

	T * find(const T& val) {
		if (empty()) {
			return nullptr;
		}

		auto * tmp = head.get();
		while (true) {
			if (tmp->val == val) {
				return &tmp->val;
			}
			auto * next = val < tmp->val ? tmp->left.get() : tmp->right.get();
			if (next == nullptr) {
				return nullptr;
			}
			tmp = next;
		}
	}

	bool remove(const T& val) {
		if (empty()) {
			return false;
		}

		node * last = nullptr;
		auto * tmp = head.get();
		bool was_left = false;
		while (true) {
			if (tmp->val == val) {
				auto& n = last == nullptr ? head : (was_left ? last->left : last->right);
				if (tmp->left == nullptr) {
					n = std::move(tmp->right); // might be nullptr
				}
				else if (tmp->right == nullptr) {
					n = std::move(tmp->left);
				}
				else {
					const auto lh = hight(tmp->left);
					const auto rh = hight(tmp->right);
					if (lh > rh) {
						tmp->left->max_node()->right = std::move(tmp->right);
						n = std::move(tmp->left);
					}
					else {
						tmp->right->min_node()->left = std::move(tmp->left);
						n = std::move(tmp->right);
					}
				}
				--cnt;
				return true;
			}

			auto * next = val < tmp->val ? tmp->left.get() : tmp->right.get();
			if (next == nullptr) {
				return false;
			}
			last = tmp;
			tmp = next;
			was_left = last->left.get() == tmp;
		}
	}

	T * min() {
		return head == nullptr ? nullptr : &head->min_node()->val;
	}

	const T * min() const {
		return head == nullptr ? nullptr : &head->min_node()->val;
	}

	T * max() {
		return head == nullptr ? nullptr : &head->max_node()->val;
	}

	const T * max() const {
		return head == nullptr ? nullptr : &head->max_node()->val;
	}

private:
	static size_t hight(const std::unique_ptr<node>& n) {
		return n == nullptr ? 0 : n->hight();
	}

	std::unique_ptr<node> head{};
	size_t cnt{0};
};

}
