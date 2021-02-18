#include <iostream>
#include <vector>
#include <cstddef>
#include "LinkedList.cpp"

template<class T>
struct graph_node {

  graph_node<T>* next;
  T data;

};


//Undirected Graph
class Graph {
  std::vector<Linkedlist<int>> verticies;

public:
  Graph(int num_verticies) {
    for (int i = 0; i < num_verticies; i++) {
      Linkedlist<int> vertex;
      vertex.add(i);
      verticies.push_back(vertex);
    }
  }

  void add_edge(int v_i, int v_j) {
    verticies[v_i].add(v_j);
    verticies[v_j].add(v_i);
  }

  void add_directed_edge(int v_i, int v_j) {
    verticies[v_i].add(v_j);
  }

  void add_edge(int v_i, int v_j, int weight) {
    verticies[v_i].add(v_j, weight);
    verticies[v_j].add(v_i, weight);
  }

  //Also adds a back edge of 0 weight to use in algorithms
  //void add_dfs_edge(int v_i, int v_j, int weight) {
  //  verticies[v_i].add(v_j, weight);
  //  verticies[v_j].add(v_i, 0);
  //}

  void add_directed_edge(int v_i, int v_j, int weight) {
    verticies[v_i].add(v_j, weight);
  }

  void remove_directed_edge(int v_i, int v_j) {
    //remove edge from v_i linked list
    int counter = 0;
    Linkedlist<int> temp_list = verticies[v_i];
    node<int>* temp_node = temp_list.get_first();
    while ((temp_node->data != v_j) && (temp_node->next != NULL)) {
      temp_node = temp_node->next;
      counter += 1;
    }
    if (temp_list.get(counter) == v_j) {
      temp_list.remove(counter);
    }
  }

  void remove_edge(int v_i, int v_j) {
    //remove edge from v_i linked list
    int counter = 0;
    Linkedlist<int> temp_list = verticies[v_i];
    node<int>* temp_node = temp_list.get_first();
    while ((temp_node->data != v_j) && (temp_node->next != NULL)) {
      temp_node = temp_node->next;
      counter += 1;
    }
    if (temp_list.get(counter) == v_j) {
      temp_list.remove(counter);
    }

    //remove edge from v_j linked list
    counter = 0;
    temp_list = verticies[v_j];
    temp_node = temp_list.get_first();
    while ((temp_node->data != v_i) && (temp_node->next != NULL)) {
      temp_node = temp_node->next;
      counter += 1;
    }
    if (temp_list.get(counter) == v_i) {
      temp_list.remove(counter);
    }
  }

  Linkedlist<int> get_vertex_list(int vertex) {
    return verticies[vertex];
  }

  int get_num_verticies() {
    return verticies.size();
  }

  void print_graph() {
    for (int i = 0; i < verticies.size(); i++) {
      Linkedlist<int> temp_list = verticies[i];
      node<int>* temp_node;
      temp_node = temp_list.get_first();
      std::cout << temp_node->data << " ";
      while (temp_node->next != NULL) {
        temp_node = temp_node->next;
        std::cout << temp_node->data << " ";
      }
      std::cout << "\n";
    }
  }
};
/*
int main() {
  Graph my_graph(5); //create graph with verticies 0, 1, 2, 3, 4
  my_graph.print_graph();
  std::cout << "\n\n";
  my_graph.add_edge(0, 1);
  my_graph.add_edge(1, 2);
  my_graph.add_edge(2, 3);
  my_graph.add_edge(3, 4);
  my_graph.add_edge(4, 1);
  my_graph.add_edge(0, 4);
  my_graph.print_graph();
  std::cout << "\n\n";
  my_graph.remove_edge(4, 1);
  my_graph.print_graph();
}*/
