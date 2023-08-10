//
// Created by merom on 5/24/2023.
//

#ifndef HOMEWORK2_DEADLINE_04_06_23_GRAPH_H
#define HOMEWORK2_DEADLINE_04_06_23_GRAPH_H

#include <fstream>
#include "Vertex.h"
#include "Edge.h"
#include "Factory.h"
/**

    @brief The Graph class represents a graph data structure.
    It provides functionality for adding edges to the graph and performing depth-first search (DFS) traversal on the graph.
    The class template parameter Edge represents the type of the edges in the graph.
    The class contains a private member variable _graph_id that stores the identifier of the graph.
    The addEdge() method is used to add an edge to the graph, given the source vertex, weight, and destination vertex.
    The vertices() method returns a reference to the collection of vertices in the graph.
    The getConstVertex() method returns a shared pointer to a constant vertex object with the specified identifier.
    The DFS() method performs a depth-first search traversal on the graph.
    */

/**

    @brief Adds an edge to the graph.
    This method adds an edge to the graph, given the source vertex, weight, and destination vertex.
    @param src The identifier of the source vertex.
    @param weight The weight of the edge.
    @param des The identifier of the destination vertex.
    */

/**

    @brief Constructs a Graph object with the specified graph identifier.
    This constructor initializes the graph with the provided identifier.
    @param val The identifier of the graph.
    */

/**

    @brief Returns a reference to the collection of vertices in the graph.
    This method returns a reference to the collection of vertices in the graph.
    @return A reference to the collection of vertices in the graph.
    */

/**

    @brief Returns a shared pointer to a constant vertex object with the specified identifier.
    This method returns a shared pointer to a constant vertex object with the specified identifier.
    @param v The identifier of the vertex.
    @return A shared pointer to a constant vertex object.
    */

/**

    @brief Performs a depth-first search (DFS) traversal on the graph.
    This method performs a depth-first search (DFS) traversal on the graph.
    */


template<class Edge>
using vertex = Vertex<Edge>;
using edge = Edge<int>;

template<class Edge>
using shared_vertex = std::shared_ptr<Vertex<Edge>>;

class Graph{
public:
    void addEdge(std::string & src, int weight, std::string & des, bool issource = false , const std::string& data1 = "", const std::string& data2 = "");
    explicit Graph(std::string && val):_graph_id(std::move(val)){}
    [[nodiscard]] const std::vector<shared_vertex<edge>>  &  vertices() const {return vertices_;}
    [[nodiscard]] shared_vertex<edge> getConstVertex( const std::string & v) const;
    void DFS(const std::string &fo );

private:
    std::string _graph_id;
    std::vector<shared_vertex<edge>> vertices_;
    static std::ofstream ofs;
    [[nodiscard]] bool hasVertex(const std::string & vertex)  const;
    shared_vertex<edge>  getVertex( const std::string & v);
    void DFS(Vertex<edge> * v);
};


#endif //HOMEWORK2_DEADLINE_04_06_23_GRAPH_H
