//Linked list for Graphs
#include <cstddef>
#include <iostream>

//List elements contain some data and point to next element in the list
template<class T>
struct node {

  node<T>* next;
  T data;
  T data2;

};

template<class T>
class Linkedlist {

  node<T>* first;
  node<T>* last;

public:
  Linkedlist<T>() {
    first = NULL;
    last = NULL;
  }

//To access members of a structure, use the dot operator.
//To access members of a structure through a pointer, use the arrow operator.
  void add(T data) {
    if (!first) {
      first = new node<T>;
      first->data = data;
      first->next = NULL;
      last = first;
    }
    else {
      node<T>* new_element = new node<T>;
      new_element->data = data;
      new_element->next = NULL;
      last->next = new_element;
      last = new_element;
    }
  }

  //Add list element corresponding to edge (data2 = edge weight)
  void add(T data, T data2) {
    node<T>* new_element = new node<T>;
    new_element->data = data;
    new_element->data2 = data2;
    new_element->next = NULL;
    last->next = new_element;
    last = new_element;
  }

  node<T>* get_first() {
    return first;
  }

  node<T>* get_last() {
    return last;
  }

  T get(int index) {
    if (index == 0) {
      return first->data;
    }
    else {
      node<T>* current = first;
      for (int i = 0; i < index; i++) {
        current = current->next;
      }
      return current->data;
    }
  }

  void remove(int index) {
    if (index == 0) {
      first = NULL;
      last = NULL;
    }
    else {
      node<T>* current = first;
      for (int i = 0; i < index-1; i++) {
        current = current->next;
      }
      current->next = current->next->next;
    }
  }
};
/*
int main() {
  Linkedlist<int> list;
  int item = 1;
  list.add(item);
  list.add(5);
  list.add(2);
  std::cout << list.get(0) << "\n";
  std::cout << list.get(1) << "\n";
  std::cout << list.get(2) << "\n";
  list.remove(1);
  std::cout << list.get(0) << "\n";
  std::cout << list.get(1) << "\n";
  std::cout << list.get(2) << "\n";
}*/
