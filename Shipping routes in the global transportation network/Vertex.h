//
// Created by merom on 5/24/2023.
//

#ifndef HOMEWORK2_DEADLINE_04_06_23_VERTEX_H
#define HOMEWORK2_DEADLINE_04_06_23_VERTEX_H

#include "Validator.h"
#include <memory>
#include <utility>
#include <vector>

// Vertex class
template<class Edge>
class Vertex {
public:

    explicit Vertex(std::string  ID, bool source = false): _visited(false), _root(source), id_(std::move(ID)){}
    [[nodiscard]] int getInDegree() const {return inDegree_;};
    [[nodiscard]] int getOutDegree() const {return edges_.size();};
    void incrementInDeg(){inDegree_++;}

    using vertex = Vertex<Edge>;
    using sharedVertex = std::shared_ptr<vertex>;

    template<typename Weight>
    void addEdge(sharedVertex v1, Weight w , sharedVertex v2 , const std::string & data1 ,const std::string & data2);

    std::vector<Edge> & edges(){ return edges_; };

    const  std::vector<Edge> & constEdges() const {return edges_;}

    bool operator==(const Vertex<Edge>& v2);

    [[nodiscard]] const std::string & getId() const { return id_;}

    [[nodiscard]] bool isVisited()const{return _visited;}

    void visited(){_visited = true;}

    void notVisited(){_visited = false;};

    [[nodiscard]] bool isreoot() const {  return _root ;}
private:
    bool _visited;
    bool _root;
    std:: string id_;
    std::vector<Edge> edges_;
    int inDegree_{};
};


#include "Vertex_impl.h"
#endif //HOMEWORK2_DEADLINE_04_06_23_VERTEX_H
