//
// Created by merom on 5/24/2023.
//

#ifndef HOMEWORK2_DEADLINE_04_06_23_EDGE_H
#define HOMEWORK2_DEADLINE_04_06_23_EDGE_H
#include "Validator.h"
#include <memory>
#include <vector>
#include "Vertex.h"


template < class Edge>
using shared_vertex = std::shared_ptr<Vertex<Edge>>;

template<typename Weight>
class Edge {
public:
    template< template<class T>  class Vertex >
    Edge(shared_vertex<Vertex<Weight>> source , Weight w, shared_vertex<Vertex<Weight>> des , const std::string &data1, const std::string &data2 ):
    data_(data1,data2),
    source_(source),
    w_(w),
    destination_(des) {}

public:
    Vertex<Edge> * getSource() const {
        return source_.get();
    }

    Vertex<Edge> * getDestination() const {
        return destination_.get();
    }

    std::tuple<std::string , std::string> & getData(){return data_;}
    [[nodiscard]] const std::tuple<std::string , std::string> & getData()const{return data_;}
    const Weight & getWeight()const { return w_;}

    void setWeight(const Weight & w) { w_ = w; }


private:
  using arrival = std::string;
  using departure = std::string;
  std::tuple<arrival , departure> data_;
  shared_vertex<Edge<Weight>> source_;
  Weight w_;
  shared_vertex<Edge<Weight>> destination_;

};

#endif //HOMEWORK2_DEADLINE_04_06_23_EDGE_H
