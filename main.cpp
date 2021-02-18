#include <iostream>
#include <vector>
#include <cstddef>
//#include "Graph.cpp" DFS already includes graph
#include "DFS.cpp"

void compute_residual_graph(Graph res_graph, std::vector<int> path) {
  int flow_amount = path.back();//capacity of smalled edge in path
  std::cout << "runs2\n";

  std::cout << "\n\n";
  res_graph.print_graph();
  std::cout << "\n\n";

  //residual for each edge
  for (int i = 0; i < (path.size()-2); i++) {//second last element is sink, last element in flow amount
    std::cout << "path i: " << path[i] <<" runs2.0\n";
    Linkedlist<int> vertex_linkedlist = res_graph.get_vertex_list(path[i]);
    std::cout << "runs2.01\n";
    node<int>* edge = vertex_linkedlist.get_first()->next; //first element of the list is our vertex
    std::cout << "runs2.02\n";
    //std::cout << edge->data << "\n";
    std::cout <<" runs2.1\n";
    while ((edge->data) != path[i + 1]) {
      std::cout << "runs2.12\n";
      edge = edge->next;
      std::cout << "runs2.2\n";
    }
    std::cout << "runs3\n";
    edge->data2 = edge->data2 - flow_amount;
    std::cout << "final edge data: " << edge->data2 << "\n";

    //remove edge if no more flow is possible
    if (edge->data2 == 0) {
      res_graph.remove_directed_edge(path[i], (edge->data));
    }

    //add backwards edge for residial graph
    res_graph.add_directed_edge(edge->data, path[i], flow_amount);
  }
}

void ford_fulkerson(Graph graph, Graph residual_graph, int source, int sink) {
  //Graph residual_graph = graph; //make a copy to compute residual
  std::vector<int> path;
  path = dfs(graph, source, sink);
  std::cout << "runs\n";
  while (path.size() != 0) { //size = 0 if sink is unreachable
    compute_residual_graph(residual_graph, path);
    path = dfs(residual_graph, source, sink);
    std::cout << "path length = " << path.size() << "\n";
    std::cout << "runs\n";
  }
  std::cout << "final part\n\n";
  residual_graph.print_graph();
  //compute total flow = out flow from source = in flow in residual graph
  int total_flow = 0;
  for (int i = 0; i < residual_graph.get_num_verticies(); i++) {
    Linkedlist<int> edgelist = residual_graph.get_vertex_list(i);
    node<int>* edge = edgelist.get_first();
    while (edge->next != NULL) {
      edge = edge->next;
      if (edge->data == source) {
        total_flow += edge->data2;
      }
    }
  }
  std::cout << "flow: " << total_flow << "\n";
}

int main () {
  Graph my_graph(8); //create graph with verticies 0, 1, 2, 3, 4
  std::cout << "\n\n";
  my_graph.add_directed_edge(0, 1, 1);
  my_graph.add_directed_edge(0, 2, 1);
  my_graph.add_directed_edge(0, 3, 1);
  my_graph.add_directed_edge(1, 4, 1);
  my_graph.add_directed_edge(2, 4, 1);
  my_graph.add_directed_edge(2, 5, 1);
  my_graph.add_directed_edge(3, 5, 1);
  my_graph.add_directed_edge(4, 7, 1);
  my_graph.add_directed_edge(5, 7, 1);
  my_graph.add_directed_edge(6, 7, 1);

  my_graph.print_graph();

  Graph residual_graph(8); //create graph with verticies 0, 1, 2, 3, 4
  std::cout << "\n\n";
  residual_graph.add_directed_edge(0, 1, 1);
  residual_graph.add_directed_edge(0, 2, 1);
  residual_graph.add_directed_edge(0, 3, 1);
  residual_graph.add_directed_edge(1, 4, 1);
  residual_graph.add_directed_edge(2, 4, 1);
  residual_graph.add_directed_edge(2, 5, 1);
  residual_graph.add_directed_edge(3, 5, 1);
  residual_graph.add_directed_edge(4, 7, 1);
  residual_graph.add_directed_edge(5, 7, 1);
  residual_graph.add_directed_edge(6, 7, 1);

  std::vector<int> my_path;
  //my_path = dfs(my_graph, 0, 7);
  //for (int i = 0; i < my_path.size()-1; i++) {
  //  std::cout << my_path[i];
 // }

  ford_fulkerson(my_graph, residual_graph, 0, 7);

}

/*other Graphs

my_graph.add_directed_edge(0, 1, 1);
my_graph.add_directed_edge(0, 2, 1);
my_graph.add_directed_edge(0, 3, 1);
my_graph.add_directed_edge(1, 4, 1);
my_graph.add_directed_edge(2, 4, 1);
my_graph.add_directed_edge(2, 5, 1);
my_graph.add_directed_edge(3, 5, 1);
my_graph.add_directed_edge(4, 7, 1);
my_graph.add_directed_edge(5, 7, 1);
my_graph.add_directed_edge(6, 7, 1);

residual_graph.add_directed_edge(0, 1, 2);
residual_graph.add_directed_edge(0, 2, 1);
residual_graph.add_directed_edge(1, 2, 3);
residual_graph.add_directed_edge(1, 3, 1);
residual_graph.add_directed_edge(2, 3, 2);

Graph my_graph(19); //create graph with verticies 0, 1, 2, 3, 4
std::cout << "\n\n";
my_graph.add_directed_edge(0, 11, 1);
my_graph.add_directed_edge(0, 14, 1);
my_graph.add_directed_edge(0, 16, 1);
my_graph.add_directed_edge(1, 9, 1);
my_graph.add_directed_edge(1, 10, 1);
my_graph.add_directed_edge(2, 15, 1);
my_graph.add_directed_edge(3, 9, 1);
my_graph.add_directed_edge(4, 9, 1);
my_graph.add_directed_edge(5, 12, 1);
my_graph.add_directed_edge(6, 12, 1);
my_graph.add_directed_edge(7, 13, 1);
my_graph.add_directed_edge(8, 10, 1);
my_graph.add_directed_edge(8, 13, 1);
my_graph.add_directed_edge(8, 14, 1);
my_graph.add_directed_edge(17, 0, 1);
my_graph.add_directed_edge(17, 1, 1);
my_graph.add_directed_edge(17, 2, 1);
my_graph.add_directed_edge(17, 3, 1);
my_graph.add_directed_edge(17, 4, 1);
my_graph.add_directed_edge(17, 5, 1);
my_graph.add_directed_edge(17, 6, 1);
my_graph.add_directed_edge(17, 7, 1);
my_graph.add_directed_edge(17, 8, 1);
my_graph.add_directed_edge(9, 18, 1);
my_graph.add_directed_edge(10, 18, 1);
my_graph.add_directed_edge(11, 18, 1);
my_graph.add_directed_edge(12, 18, 1);
my_graph.add_directed_edge(13, 18, 1);
my_graph.add_directed_edge(14, 18, 1);
my_graph.add_directed_edge(15, 18, 1);
my_graph.add_directed_edge(16, 18, 1);

*/
