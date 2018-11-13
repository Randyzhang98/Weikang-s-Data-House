#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <algorithm>
#include <cmath>
#include <list>
#include <iostream>
#include "priority_queue.h"


// OVERVIEW: A specialized version of the 'heap' ADT implemented as a 
//           Fibonacci heap.
template<typename TYPE, typename COMP = std::less<TYPE> >
class fib_heap: public priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  // EFFECTS: Construct an empty heap with an optional comparison functor.
  //          See test_heap.cpp for more details on functor.
  // MODIFIES: this
  // RUNTIME: O(1)
  fib_heap(COMP comp = COMP());

  // EFFECTS: Deconstruct the heap with no memory leak.
  // MODIFIES: this
  // RUNTIME: O(n)
  ~fib_heap();
  
  // EFFECTS: Add a new element to the heap.
  // MODIFIES: this
  // RUNTIME: O(1)
  virtual void enqueue(const TYPE &val);

  // EFFECTS: Remove and return the smallest element from the heap.
  // REQUIRES: The heap is not empty.
  // MODIFIES: this
  // RUNTIME: Amortized O(log(n))
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
  // Note: compare is a functor object
  COMP compare;

private:
  // Add any additional member functions or data you require here.
  // You may want to define a strcut/class to represent nodes in the heap and a
  // pointer to the min node in the heap.
  struct node_t
  {
    TYPE value;
    unsigned degree = 0;
    std::list<node_t*> children;
  };
  typename std::list<node_t*>::iterator min;
  std::list<node_t*> root;
  const double phi = 1.618;
  unsigned n = 0;
  void destructor(node_t *target);
  void consolidate();
  void Fib_Heap_Link(decltype(min) &target, decltype(min) &source);
};

// Add the definitions of the member functions here. Please refer to
// binary_heap.h for the syntax.

template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP> :: fib_heap(COMP comp) {
  compare = comp;
  n = 0;
  min = root.end();
}

template<typename TYPE, typename COMP>
fib_heap<TYPE, COMP> :: ~fib_heap() 
{
  for (auto p = root.begin(); p != root.end(); p++)
  {
    destructor(*p);
  }
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> :: destructor(node_t *target)
{
  if (target->children.empty()) delete target;
  else 
  {
    for (auto p = target->children.begin(); p != target->children.end(); p++)
    {
      destructor(*p);
    }
    delete target;
  }
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> :: enqueue(const TYPE &val) 
{
  node_t* input = new node_t;
  input->degree = 0;
  input->value = std::move(val);
  root.emplace_front(input);
  if (min == root.end())
  {
    min = root.begin();
  }
  else if (compare(val, (*min)->value)) min = root.begin();
  n++;
}

template<typename TYPE, typename COMP>
TYPE fib_heap<TYPE, COMP> :: dequeue_min() 
{
  TYPE result = (*min)->value;
  decltype(min) z = min;
  if (z != root.end())
  {
    n--;
    
    root.splice(root.begin(), std::move((*z)->children));

    delete *z;
    min = root.erase(min);
    if (n == 0) min = root.end();
    else consolidate();
  }
  return result;
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> :: consolidate()
{
  unsigned N = n;
  N = (unsigned) log(N) / log(phi);
  std::vector<typename std::list<node_t*>::iterator> A(N+2, root.end());
  typename std::list<node_t*>::iterator new_temp;
  for (auto p = root.begin(); p != root.end(); p = new_temp )
  {
    auto x = p;
    unsigned d = (*x)->degree;
    
    new_temp = std::next(p,1);
    while (A[d] != root.end())
    {
      auto y = A[d];
      if (compare( (*y)->value, (*x)->value) ) swap(x,y);
      Fib_Heap_Link(x,y);
      A[d] = root.end();
      d++;
      if (d >= N+1) break;
    }
    A[d] = x;
  }
  min = root.end();
  for (unsigned i = 0; i < N+2; i++)
  {
      if (A[i] != root.end())
      {
        if (min == root.end()) min = A[i];
        else if (compare((*A[i])->value, (*min)->value)) min = A[i];
      }
    }
}

template<typename TYPE, typename COMP>
void fib_heap<TYPE, COMP> :: Fib_Heap_Link(decltype(min) &target, decltype(min) &source)
{
  node_t *t = *source;
  root.erase(source);
  (*target)->children.emplace_front(std::move(t));
  ((*target)->degree)++;
}


template<typename TYPE, typename COMP>
const TYPE &fib_heap<TYPE, COMP>::get_min() const 
{
    return (*min)->value;
}

template<typename TYPE, typename COMP>
unsigned int fib_heap<TYPE, COMP>::size() const 
{
    return this->n;
}

template<typename TYPE, typename COMP>
bool fib_heap<TYPE, COMP>::empty() const {
    return (this->n == 0);
}

#endif //FIB_HEAP_H
