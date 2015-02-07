#pragma once

#include "common.h"
#include "vector.h"
#include "list.h"


namespace algo {

template<typename T>
class vector_stack: private vector<T> {
public:
	vector_stack() = default;
	vector_stack(const vector_stack<T>& v) = default;
	vector_stack(vector_stack<T>&& v) = default;
	~vector_stack() = default;
	vector_stack<T>& operator=(const vector_stack<T>& v) = default;
	vector_stack<T>& operator=(vector_stack<T>&& v) = default;

	bool empty() const {
		return vector<T>::empty();
	}

	size_t size() const {
		return vector<T>::size();
	}

	void push(const T& val) {
		vector<T>::push_back(val);
	}

	T pop() {
		T res = std::move(vector<T>::back());
		vector<T>::pop_back();
		return res;
	}

	const T& peek() const {
		return vector<T>::back();
	}
};

template<typename T>
class list_stack: private list<T> {
public:
	list_stack() = default;
	list_stack(const list_stack<T>& v) = default;
	list_stack(list_stack<T>&& v) = default;
	~list_stack() = default;
	list_stack<T>& operator=(const list_stack<T>& v) = default;
	list_stack<T>& operator=(list_stack<T>&& v) = default;

	bool empty() const {
		return list<T>::empty();
	}

	size_t size() const {
		return list<T>::size();
	}

	void push(const T& val) {
		list<T>::push_front(val);
	}

	T pop() {
		return list<T>::pop_front();
	}

	const T& peek() const {
		return list<T>::front();
	}
};

template<typename T>
class dlist_stack: private dlist<T> {
public:
	dlist_stack() = default;
	dlist_stack(const dlist_stack<T>& v) = default;
	dlist_stack(dlist_stack<T>&& v) = default;
	~dlist_stack() = default;
	dlist_stack<T>& operator=(const dlist_stack<T>& v) = default;
	dlist_stack<T>& operator=(dlist_stack<T>&& v) = default;

	bool empty() const {
		return dlist<T>::empty();
	}

	size_t size() const {
		return dlist<T>::size();
	}

	void push(const T& val) {
		dlist<T>::push_front(val);
	}

	T pop() {
		return dlist<T>::pop_front();
	}

	const T& peek() const {
		return dlist<T>::front();
	}
};

}
