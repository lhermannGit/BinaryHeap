/*
Binary Heap implementation using generics.
ToDo:
	Find fastest way to search for an item.
	Comparison Function vs overloaded ">" and "<" operator functionality
*/

#ifndef _BINARYHEAP
#define _BINARYHEAP

#include <vector>
#include <math.h>
#include <stdio.h>

enum sort_order{
	MAX = 0,
	MIN = 1
};

template <typename T>
class BinaryHeap
{
private:
	std::vector<T> m_heap;
	bool (BinaryHeap<T>::*cmp_func)(T const&,T const&);

	void heapifyDown(size_t pos);
	void heapifyUp(size_t pos);

//	int getParent(int pos);
//	int getChildren(int pos);

	bool greaterThan(T const& elem1, T const& elem2){ return elem1 > elem2; };
	bool lesserThan(T const& elem1, T const& elem2){ return elem1 < elem2; };

	int findLinear(T elem);
	
public:
	BinaryHeap(int order = MIN);
	BinaryHeap(bool (*f)(T const& elem1, T const& elem2));
	//virtual ~BinaryHeap();

	T pop();

	void push(T const& elem);
	
	bool isEmpty(){ return m_heap.empty() };

	int find(const T elem);
};

template <typename T>
BinaryHeap<T>::BinaryHeap(bool (*f)(T const&,T const&)){
	cmp_func = f;
};

template <typename T>
BinaryHeap<T>::BinaryHeap(int order = MIN){
	switch (order){
		case MAX: cmp_func = &BinaryHeap<T>::greaterThan;
			break;
		case MIN: cmp_func = &BinaryHeap<T>::lesserThan;
			break;
	}
};

template <typename T>
T BinaryHeap<T>::pop(){
	T result = m_heap.front();
	m_heap[0] = m_heap.back();
	m_heap.pop_back();
	if (m_heap.size() > 0)
		heapifyDown(0);
	return result;
}

template <typename T>
void BinaryHeap<T>::push(T const& elem){
	m_heap.push_back(elem);
	heapifyUp(m_heap.size()-1);
}

template <typename T>
void BinaryHeap<T>::heapifyDown(size_t pos){
	size_t tpos;
	while (true) {
		tpos = pos;
		if (2 * pos + 2 <= m_heap.size() - 1) {
			if ((this->*cmp_func)(m_heap[2 * pos + 1],
					m_heap[pos]))
					tpos = 2 * pos + 1;
			if ((this->*cmp_func)(m_heap[2 * pos + 2],
						m_heap[tpos]))
					tpos = 2 * pos + 2;
		} else if (2 * pos + 1 <= m_heap.size() - 1) {
			if ((this->*cmp_func)(m_heap[2 * pos + 1],
						m_heap[pos]))
					tpos = 2 * pos + 1;
		}
		if (pos != tpos) {
			T temp = m_heap[pos];
			m_heap[pos] = m_heap[tpos];
			m_heap[tpos] = temp;
		} else
			return;
	}
}

template <typename T>
void BinaryHeap<T>::heapifyUp(size_t pos){
	while (pos > 0) {
		size_t newpos = (size_t) floor((pos - 1) / 2);
		if ((this->*cmp_func)(m_heap[pos], m_heap[newpos])) {
			T temp = m_heap[pos];
			m_heap[pos] = m_heap[newpos];
			m_heap[newpos] = temp;
			pos = newpos;
		} else {
			return;
		}
	}
}



#endif