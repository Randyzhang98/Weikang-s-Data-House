#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <algorithm>
#include "priority_queue.h"

// OVERVIEW: A specialized version of the 'heap' ADT implemented as a binary
//           heap.
template<typename TYPE, typename COMP = std::less<TYPE> >
class binary_heap: public priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  // EFFECTS: Construct an empty heap with an optional comparison functor.
  //          See test_heap.cpp for more details on functor.
  // MODIFIES: this
  // RUNTIME: O(1)
  binary_heap(COMP comp = COMP());

  // EFFECTS: Add a new element to the heap.
  // MODIFIES: this
  // RUNTIME: O(log(n))
  virtual void enqueue(const TYPE &val);

  // EFFECTS: Remove and return the smallest element from the heap.
  // REQUIRES: The heap is not empty.
  // MODIFIES: this
  // RUNTIME: O(log(n))
  virtual TYPE dequeue_min();

  // EFFECTS: Return the smallest element of the heap.
  // REQUIRES: The heap is not empty.
  // RUNTIME: O(1)
  virtual const TYPE &get_min() const;

  // EFFECTS: Get the number of elements in the heap.
  // RUNTIME: O(1)
  virtual size_type size() const;

  // EFFECTS: Return true if the heap is empty.
  // RUNTIME: O(1)
  virtual bool empty() const;

private:
  // Note: This vector *must* be used in your heap implementation.
  std::vector<TYPE> data;
  // Note: compare is a functor object
  COMP compare;

private:
  // Add any additional member functions or data you require here.
};

template<typename TYPE, typename COMP>
binary_heap<TYPE, COMP> :: binary_heap(COMP comp) {
    compare = comp;
    data.push_back(TYPE());
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP> :: enqueue(const TYPE &val) {
    data.push_back(std::move(val));
    unsigned i = size();
    while(i > 1 && compare(data[i],data[i / 2]))
    {
        std::swap(data[i],data[i / 2]);
        i = i / 2;
    }
}

template<typename TYPE, typename COMP>
TYPE binary_heap<TYPE, COMP> :: dequeue_min() {
    if (empty()) return data[0];
    unsigned n = size();
    std::swap(data[1],data[n]);
    TYPE re = data[n];
    data.pop_back();
    n = size();
    size_type i = 1;
    size_type j = i * 2;
    while (j <= n)
    {
        if (j < n && compare(data[j + 1], data[j])) j++;
        if (compare(data[j], data[i])) 
        {
            std::swap(data[j], data[i]);
            i = j;
            j = i * 2;
        }
        else break;
    }
    return re;
}

template<typename TYPE, typename COMP>
const TYPE &binary_heap<TYPE, COMP> :: get_min() const {
    if (empty()) return data[0];
    else return data[1];
}

template<typename TYPE, typename COMP>
bool binary_heap<TYPE, COMP> :: empty() const {
    return (size() == 0);
}

template<typename TYPE, typename COMP>
unsigned binary_heap<TYPE, COMP> :: size() const { 
    return data.size() - 1;
}

#endif //BINARY_HEAP_H
