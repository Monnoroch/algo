#pragma once

#include "common.h"
#include "vector.h"
#include "list.h"


namespace algo {

template<typename T, template<typename> class C>
class stack: public C<T> {
	using B = C<T>;
	using self = stack<T, C>;
public:
	stack() = default;
	stack(const self& v) = default;
	stack(self&& v) = default;
	~stack() = default;
	self& operator=(const self& v) = default;
	self& operator=(self&& v) = default;

	bool empty() const {
		return B::empty();
	}

	size_t size() const {
		return B::size();
	}

	void push(const T& val) {
		B::push_front(val);
	}

	T pop() {
		return B::pop_front();
	}

	const T& peek() const {
		return B::front();
	}
};

template<typename T>
class stack<T, vector>: private vector<T> {
	using B = vector<T>;
	using self = stack<T, vector>;
public:
	stack() = default;
	stack(const self& v) = default;
	stack(self&& v) = default;
	~stack() = default;
	self& operator=(const self& v) = default;
	self& operator=(self&& v) = default;

	bool empty() const {
		return B::empty();
	}

	size_t size() const {
		return B::size();
	}

	void push(const T& val) {
		B::push_back(val);
	}

	T pop() {
		T res = std::move(B::back());
		B::pop_back();
		return res;
	}

	const T& peek() const {
		return B::back();
	}
};

template<typename T>
using vector_stack = stack<T, vector>;

template<typename T>
using list_stack = stack<T, list>;

template<typename T>
using dlist_stack = stack<T, dlist>;

}
