#pragma once

#include "common.h"
#include "dlist.h"


namespace algo {

template<typename T>
class queue: public dlist<T> {
	using B = dlist<T>;
public:
	queue() = default;
	queue(const queue& v) = default;
	queue(queue&& v) = default;
	~queue() = default;
	queue& operator=(const queue& v) = default;
	queue& operator=(queue&& v) = default;

	bool empty() const {
		return B::empty();
	}

	size_t size() const {
		return B::size();
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
};

}
