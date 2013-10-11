/*
Binary Heap implementation using generics.
ToDo:
	Find fastest way to search for an item.
	Comparison Function vs overloaded ">" and "<" operator functionality
	TEST
*/

#ifndef _BINARYHEAP
#define _BINARYHEAP

#include <vector>
#include <math.h>
#include "Defines.h"

template <typename T>
class BinaryHeap
{
private:
	std::vector<const T*> _heap;
	bool (*cmp_func)(T const&,T const&);

	void heapifyDown(uint pos);
	void heapifyUp(uint pos);

public:
	BinaryHeap(bool (*f)(T const& elem1, T const& elem2));
	//virtual ~BinaryHeap();

	const T* pop();

	void push(const T& elem);
	void push(std::vector<T>& vector);
	
	bool isEmpty() const { return _heap.empty() };
};

template <typename T>
BinaryHeap<T>::BinaryHeap(bool (*f)(T const&,T const&)){
	cmp_func = f;
};

template <typename T>
const T* BinaryHeap<T>::pop(){
	const T* result = _heap.front();
	_heap[0] = _heap.back();
	_heap.pop_back();
	if (_heap.size() > 0)
		heapifyDown(0);
	return result;
}

template <typename T>
void BinaryHeap<T>::push(const T& elem){
	_heap.push_back(&elem);
	heapifyUp(_heap.size()-1);
}

template <typename T>
void BinaryHeap<T>::push(std::vector<T>& vector){
	for (auto& elem: vector)
		push(elem);
}

template <typename T>
void BinaryHeap<T>::heapifyDown(uint pos){
	uint tpos;
	while (true) {
		tpos = pos;
		if (2 * pos + 2 <= _heap.size() - 1) {
			if (cmp_func(*_heap[2 * pos + 1],
					*_heap[pos]))
					tpos = 2 * pos + 1;
			if (cmp_func(*_heap[2 * pos + 2],
						*_heap[tpos]))
					tpos = 2 * pos + 2;
		} else if (2 * pos + 1 <= _heap.size() - 1) {
			if (cmp_func(*_heap[2 * pos + 1],
					*_heap[pos]))
					tpos = 2 * pos + 1;
		}
		if (pos != tpos) {
			const T* temp = _heap[pos];
			_heap[pos] = _heap[tpos];
			_heap[tpos] = temp;
		} else
			return;
	}
}

template <typename T>
void BinaryHeap<T>::heapifyUp(uint pos){
	while (pos > 0) {
		uint newpos = (uint) floor((pos - 1) / 2);
		if (cmp_func(*_heap[pos], *_heap[newpos])) {
			const T* temp = _heap[pos];
			_heap[pos] = _heap[newpos];
			_heap[newpos] = temp;
			pos = newpos;
		} else {
			return;
		}
	}
}



#endif