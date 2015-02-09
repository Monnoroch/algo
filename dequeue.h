#pragma once

#include "common.h"
#include "dlist.h"


namespace algo {

template<typename T>
class dequeue: public dlist<T> {
	using B = dlist<T>;
public:
	dequeue() = default;
	dequeue(const dequeue& v) = default;
	dequeue(dequeue&& v) = default;
	~dequeue() = default;
	dequeue& operator=(const dequeue& v) = default;
	dequeue& operator=(dequeue&& v) = default;

	bool empty() const {
		return B::empty();
	}

	size_t size() const {
		return B::size();
	}

	void push_front(const T& val) {
		B::push_front(val);
	}

	T pop_front() {
		return B::pop_front();
	}

	const T& peek_front() const {
		return B::front();
	}

	void push_back(const T& val) {
		B::push_back(val);
	}

	T pop_back() {
		return B::pop_back();
	}

	const T& peek_back() const {
		return B::back();
	}
};

}
