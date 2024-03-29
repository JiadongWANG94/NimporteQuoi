/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include <iostream>

#include "graph_algorithms.hpp"
#include "directed_graph.hpp"
#include "log.hpp"
#include "test.hpp"

REGISTER_TEST(test) {
    DirectedGraph<int> graph;
    graph.Init("");
    graph.AddVertex(1);
    graph.AddVertex(2);
    graph.AddVertex(3);
    graph.AddVertex(4);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(3, 4);
    graph.AddEdge(2, 4);

    LINFO(test) << "number of vertexes : " << graph.GetVertexes().size();
    LINFO(test) << "has vertex 1 : " << graph.HasVertex(1);
    LINFO(test) << "has vertex 2 : " << graph.HasVertex(2);

    LINFO(test) << "(DFS) has route from 1 to 2 : " << DFSearch(graph, 1, 2);
    LINFO(test) << "(DFS) has route from 2 to 4 : " << DFSearch(graph, 2, 4);
    LINFO(test) << "(DFS) has route from 1 to 4 : " << DFSearch(graph, 1, 4);
    LINFO(test) << "(DFS) has route from 2 to 1 : " << DFSearch(graph, 2, 1);

    LINFO(test) << "(BFS) has route from 1 to 2 : " << BFSearch(graph, 1, 2);
    LINFO(test) << "(BFS) has route from 2 to 4 : " << BFSearch(graph, 2, 4);
    LINFO(test) << "(BFS) has route from 1 to 4 : " << BFSearch(graph, 1, 4);
    LINFO(test) << "(BFS) has route from 2 to 1 : " << BFSearch(graph, 2, 1);
    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}
