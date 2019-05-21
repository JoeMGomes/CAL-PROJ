/*
 * MutablePriorityQueue.h
 * A simple implementation of mutable priority queues, required by Dijkstra algorithm.
 * Modificado para projeto de Concepção de Algoritmos por José Gomes
 *
 * Created on: 17/03/2018
 *      Author: Jo�o Pascoal Faria
 */

#ifndef SRC_MUTABLEPRIORITYQUEUEPoint_H_
#define SRC_MUTABLEPRIORITYQUEUEPoint_H_

#include <vector>
#include "Point.h"

using namespace std;

/**
 * class T must have: (i) accessible field int queueIndex; (ii) operator< defined.
 */

/**
 * @brief      List of mutable priorities.
 */
class MutablePriorityQueue {
	vector<Point *> H;
	void heapifyUp(unsigned i);
	void heapifyDown(unsigned i);
	inline void set(unsigned i, Point * x);
public:
	MutablePriorityQueue();
	void insert(Point * x);
	Point * extractMin();
	void decreaseKey(Point * x);
	bool empty();
};

// Index calculations
#define parent(i) ((i) >> 1)  /* i / 2 */
#define leftChild(i) ((i) << 1)  /* i * 2 */

/**
 * @brief      Constructs the object.
 */
MutablePriorityQueue::MutablePriorityQueue() {
	H.push_back(NULL);
	// indices will be used starting in 1
	// to facilitate parent/child calculations
}

/**
 * @brief      { function_description }
 *
 * @return     { description_of_the_return_value }
 */
bool MutablePriorityQueue::empty() {
	return H.size() == 1;
}

/**
 * @brief      { function_description }
 *
 * @return     { description_of_the_return_value }
 */
Point* MutablePriorityQueue::extractMin() {
	auto x = H[1];
	x->queueIndex = 0;
	H[1] = H.back();
	H.pop_back();
	if ( ! empty())
		heapifyDown(1);
	return x;
}

/**
 * @brief      { function_description }
 *
 * @param      x     { parameter_description }
 */
void MutablePriorityQueue::insert(Point *x) {
	H.push_back(x);
	heapifyUp(H.size()-1);
}

/**
 * @brief      { function_description }
 *
 * @param[in]  i     { parameter_description }
 */
void MutablePriorityQueue::heapifyUp(unsigned i) {
	auto x = H[i];
	while (i > 1 && *x < *H[parent(i)]) {
		set(i, H[parent(i)]);
		i = parent(i);
	}
	set(i, x);
}

/**
 * @brief      { function_description }
 *
 * @param      x     { parameter_description }
 */
void MutablePriorityQueue::decreaseKey(Point *x) {
	heapifyUp(x->queueIndex);
}

/**
 * @brief      { function_description }
 *
 * @param[in]  i     { parameter_description }
 */
void MutablePriorityQueue::heapifyDown(unsigned i) {
	auto x = H[i];
	while (true) {
		unsigned k = leftChild(i);
		if (k >= H.size())
			break;
		if (k+1 < H.size()  && *H[k+1] < *H[k])
			k++; // right child of i
		if ( ! (*H[k] < *x) )
			break;
		set(i, H[k]);
		i = k;
	}
	set(i, x);
}

/**
 * @brief      { function_description }
 *
 * @param[in]  i     { parameter_description }
 * @param      x     { parameter_description }
 */
void MutablePriorityQueue::set(unsigned i, Point * x) {
	H[i] = x;
	x->queueIndex = i;
}

#endif /* SRC_MUTABLEPRIORITYQUEUE_H_ */