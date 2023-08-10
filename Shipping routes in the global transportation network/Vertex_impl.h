//
// Created by merom on 5/24/2023.
//

#ifndef HOMEWORK2_DEADLINE_04_06_23_VERTEX_IMPL_H
#define HOMEWORK2_DEADLINE_04_06_23_VERTEX_IMPL_H
#include "Vertex.h"

template<class Edge>
template<typename Weight>
void Vertex<Edge>::addEdge(sharedVertex v1, Weight w, sharedVertex v2, const std::string & data1, const std::string & data2) {
    v2->incrementInDeg();
    edges_.emplace_back(v1, w, v2,data1,data2);

}




template<class Edge>
bool Vertex<Edge>::operator==(const Vertex<Edge> &v2) {
    return id_ == v2.id_;
}


#endif //HOMEWORK2_DEADLINE_04_06_23_VERTEX_IMPL_H
