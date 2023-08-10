//
// Created by merom on 5/24/2023.
//
#include "Graph.h"
std::ofstream Graph::ofs;

void Graph::addEdge(std::string & source, int weight, std::string & destination, bool issource , const std::string& data1, const std::string& data2 ) {

    bool has_sour = hasVertex(source);
    bool has_dest = hasVertex(destination);

    auto  src = getVertex(source);
    auto des = getVertex(destination);


    if(has_sour && has_dest && !Factory::isNewFile()){
        auto  & edges  = src->edges();
        auto begin = edges.begin();

        while( begin != edges.end() ){
            if((((*begin).getDestination()->getId()) == (des->getId() ) )){
                // Calculate the average weight and update the existing edge
                int avg = (weight + (*begin).getWeight()) /2;
                (begin)->setWeight(avg);
                return;
            }
            begin++;
        }

    }

    if(!has_sour){
        vertices_.push_back(std::make_shared<Vertex<Edge<int>>>(source,issource));
    }
    if(!has_dest){
        vertices_.push_back(std::make_shared<Vertex<Edge<int>>>(destination)); // Add the destination vertex if it doesn't exist
    }
    
    src = getVertex(source);
    des = getVertex(destination);

   src->addEdge(
            src,
            weight,
            des,data1,data2);

}

bool Graph::hasVertex(const std::string & vertex) const {
    // Check if any vertex in the vector matches the given vertex
    return std::any_of(vertices_.begin(), vertices_.end(),[&](const auto & ver){
        return ver->getId() == vertex;
    });
}

shared_vertex<edge> Graph::getVertex( const std::string & v) {
    // Find the vertex in the vector and return a pointer to it
    for(const auto & vertex : vertices_){
        if(vertex->getId() == v){
            return  vertex;
        }
    }
   return nullptr;

}

shared_vertex<edge>  Graph::getConstVertex(const std::string &v) const {
    // Find the vertex in the vector and return a pointer to it
    for(const auto & vertex : vertices_){
        if(vertex->getId() == v){
            return  vertex;
        }
    }
    return nullptr;
}

void Graph::DFS(Vertex<edge> * v) {
    v->visited();
    for( const auto & vertex : v->constEdges()){
        Graph::ofs << vertex.getSource()->getId() << '\t' << vertex.getWeight() << '\t' << vertex.getDestination()->getId() << std::endl;
        if(!vertex.getDestination()->isVisited()){
            DFS(vertex.getDestination());
        }

    }
}

void Graph::DFS(const std::string &fo) {
    Graph::ofs.open(fo,std::ios::app);
    if(Graph::ofs.is_open()){
        Graph::ofs << "DFS Graph: " << _graph_id << std::endl;

        for(auto & vertice : vertices_){
            if(!vertice->isVisited()){
                DFS(vertice.get());
            }
        }
        Graph::ofs << std::endl;
        Graph::ofs.close();

        std::for_each(vertices_.begin(), vertices_.end(),[](const auto & val){
            val->notVisited();
        });

    }else{
        throw Validator::FileFailedToOpen(fo);
    }




}



