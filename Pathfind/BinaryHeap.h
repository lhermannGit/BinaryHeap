/*
Binary Heap implementation using generics.
ToDo:
    Externally linking elem position to data or iterate over the array for an update?
*/

#ifndef _BINARYHEAP
#define _BINARYHEAP

#include <vector>
#include <math.h>
#include "Defines.h"

enum Order { MIN, MAX };

template <typename T>
class BinaryHeap
{
private:
	std::vector<T*> _heap;
	bool (*cmp_func)(T const&,T const&);

	void heapifyDown(uint pos);
	void heapifyUp(uint pos);

    static bool min(T const& elem1, T const& elem2){ return elem1 < elem2; };
    static bool max(T const& elem1, T const& elem2){ return elem1 > elem2; };
public:
    BinaryHeap(bool (*f)(T const& elem1, T const& elem2));
    BinaryHeap(Order order = MIN);
	//virtual ~BinaryHeap();

	const T* pop();

	void push(T& elem);
	void push(std::vector<T>& vector);

    void clear(){ _heap.clear(); }; 
	
	bool isEmpty() const { return _heap.empty() == nullptr; };
};

template <typename T>
BinaryHeap<T>::BinaryHeap(bool (*f)(T const&,T const&)){
	cmp_func = f;
	_heap.push_back(nullptr);
};

template <typename T>
BinaryHeap<T>::BinaryHeap(Order order){
	switch (order){
        case MIN:
            cmp_func = min;
            break;
        case MAX:
            cmp_func = max;
            break;
    }

	_heap.push_back(nullptr);
};

template <typename T>
const T* BinaryHeap<T>::pop(){
	const T* result = _heap[1];
	_heap[1] = _heap.back();
	_heap.pop_back();
	if (_heap.size() > 1)
		heapifyDown(1);
	return result;
}

template <typename T>
void BinaryHeap<T>::push(T& elem){
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
		if (2 * pos + 1 <= _heap.size() - 1) {
			if (cmp_func(*_heap[2 * pos],
					*_heap[pos]))
					tpos = 2 * pos;
			if (cmp_func(*_heap[2 * pos + 1],
						*_heap[tpos]))
					tpos = 2 * pos + 1;
		} else if (2 * pos <= _heap.size() - 1) {
			if (cmp_func(*_heap[2 * pos],
					*_heap[pos]))
					tpos = 2 * pos;
		}
		if (pos != tpos) {
			T* temp = _heap[pos];
			_heap[pos] = _heap[tpos];
			_heap[tpos] = temp;
			pos = tpos;
		} else
            return;
	}
}

template <typename T>
void BinaryHeap<T>::heapifyUp(uint pos){
	while (pos > 1) {
		uint newpos = (uint) floor(pos / 2);
		if (cmp_func(*_heap[pos], *_heap[newpos])) {
			T* temp = _heap[pos];
			_heap[pos] = _heap[newpos];
			_heap[newpos] = temp;
			pos = newpos;
		} else 
            return;
	}
}


#endif