#include "Graph.cpp"
#include <iostream>
#include <limits>

void explore(Graph graph, int vertex, int dfs_data[][2], int& clock) {
  if (dfs_data[vertex][0] == (std::numeric_limits<int>::max())) {
    dfs_data[vertex][0] = clock;
    clock++;
    //get linked list of vertex we are exploring
    Linkedlist<int> vertex_list = graph.get_vertex_list(vertex);
    node<int>* vertex_list_node = vertex_list.get_first();
    while (vertex_list_node->next != NULL) {
      vertex_list_node = vertex_list_node->next;
      explore(graph, vertex_list_node->data, dfs_data, clock);
    }
    dfs_data[vertex][1] = clock;
    clock++;
  }
}



std::vector<int> dfs(Graph graph, int start_vertex, int end_vertex) {
  int num_verticies = graph.get_num_verticies();
  int dfs_data[num_verticies][2]; //for each vertex we have a start and finish time, 3rd spot is for edge weight
  for (int i = 0; i < num_verticies; i++ ) {
    dfs_data[i][0] = std::numeric_limits<int>::max();
    dfs_data[i][1] = std::numeric_limits<int>::max();
  }
  int clock = 1;
  dfs_data[start_vertex][0] = clock;
  clock++;
  Linkedlist<int> vertex_list = graph.get_vertex_list(start_vertex);
  node<int>* vertex_list_node = vertex_list.get_first();
  while (vertex_list_node->next != NULL) {
    vertex_list_node = vertex_list_node->next;
    explore(graph, vertex_list_node->data, dfs_data, clock);
  }
  dfs_data[start_vertex][1] = clock;

  for (int i = 0; i < num_verticies; i++) {
    std::cout << "Vertex: " << i << ", Start time: " << dfs_data[i][0] << ", Finish time: " << dfs_data[i][1] << "\n";
  }
  std::cout << "runs \n";
  //return path from start to end_vertex
  //path if start clock < T start clock and end clock > T end clock
  std::vector<int> path;
  for (int j = 0; j < graph.get_num_verticies(); j++) {
    if ((dfs_data[j][0] <= dfs_data[end_vertex][0]) && (dfs_data[j][1] >= dfs_data[end_vertex][1])) {
      path.push_back(j);
    }
  }
  std::cout <<"Size of path after dfs: "<< path.size() << "\n";
  //not efficient, improve later!!!
  std::vector<int> sorted_path;

  while (path.size() != 0) {
    int smallest = std::numeric_limits<int>::max();
    int smallest_pos = std::numeric_limits<int>::max(); //position of smallest element
    for (int i = 0; i < path.size(); i++) {
      if (dfs_data[path[i]][0] < smallest) {
        smallest = dfs_data[path[i]][0];
        smallest_pos = i;
      }
    }
    std::cout << "\n";
    sorted_path.push_back(path[smallest_pos]);
    path.erase(path.begin() + smallest_pos);
  }

  for (int i = 0; i < sorted_path.size(); i++) {
    std::cout << "Path vertex " << i << " = " << sorted_path[i] << "\n";
  }
  std::cout << "runs \n" << std::flush;

  //get smallest weight on this path
  //efficiency can be improved
  if (sorted_path.size() != 0) { //dont run if there isnt a path
    int smallest_weight = std::numeric_limits<int>::max();
    for (int i = 0; i < sorted_path.size() - 1; i++) {
      Linkedlist<int> vertex = graph.get_vertex_list(sorted_path[i]);
      node<int>* vertex_node = vertex.get_first()->next;
      while ((vertex_node->data) != sorted_path[i+1]){
        vertex_node = vertex_node->next;
      }
      if (vertex_node->data2 < smallest_weight) {
        smallest_weight = vertex_node->data2;
      }
    }
    std::cout << "smallest weight: " << smallest_weight << "\n";
    sorted_path.push_back(smallest_weight); // last element of the path stores weight;
  }

  return sorted_path;
}


/*
int main() {
  Graph my_graph(5); //create graph with verticies 0, 1, 2, 3, 4
  my_graph.print_graph();
  std::cout << "\n\n";
  //add edges to make a house graph
  my_graph.add_edge(0, 1);
  my_graph.add_edge(1, 2);
  my_graph.add_edge(2, 3, 5);
  my_graph.add_edge(3, 4, 1);
  my_graph.add_edge(4, 1);
  my_graph.add_edge(0, 4);
  my_graph.print_graph();
  std::cout << "\n\n";
  my_graph.remove_edge(4, 1);
  my_graph.print_graph();

  dfs(my_graph, 0);
}*/
