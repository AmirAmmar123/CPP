//
// Created by merom on 5/24/2023.
//
#include <fstream>
#include "Factory.h"
bool Factory::_isnewFile = false;
std::string Factory::_currentFileName;
std::set<std::string> Factory::_allFiles;


void Factory::init_graphs() {

    std::size_t size = _tokens->size();
    std::size_t i = 0 ;
    int line = 1;
    // Check if there are at least 4 tokens available

    if( (i + 4 ) <= size ){

       try {

            Validator::isValidName( (*_tokens)[i]); // Validate the first token as a name
            Validator::isValidDateTimeFormat((*_tokens)[i+1]); // Validate the second token as a date-time format
            line++;
            Validator::isValidName((*_tokens)[i+2]); // Validate the third token as a name
            Validator::isValidDateTimeFormat((*_tokens)[i+3]); // Validate the fourth token as a date-time format
            Validator::isValidWeight((*_tokens)[4]);


        }catch ( Validator::PortCityNameError & ){
                throw Validator::InvalidFileInput(line,_currentFileName);
        }catch (Validator::DateTimeError &){
                throw Validator::InvalidFileInput(line,_currentFileName);
        }catch ( Validator::InvalidLegalWeight &){
                throw Validator::InvalidFileInput(line,_currentFileName);
        }


        // Create edges using the vertices and time duration
                                                 /*(departure       arrival)*/
        _g_t->addEdge((*_tokens)[i],(int)Chrono((*_tokens)[i+1],(*_tokens)[i+3]), (*_tokens)[i+2],true,
                      (*_tokens)[i+1]);

//        _g_c->addEdge((*_tokens)[i],std::stoi((*_tokens)[4]), (*_tokens)[i+2], true,(*_tokens)[i+1]);





        std::vector<std::string> cities;
        std::vector<std::string> dateTime;
        std::vector<std::string> weight;

        auto begin = (*_tokens).begin();
        begin+=2;

        // Extract cities from tokens
        if(begin != (*_tokens).end()){
            std::copy_if(begin, (*_tokens).end(), std::back_inserter(cities),[step1 = 0](const auto & val) mutable { return step1++%4 == 0;});
        }else{
            throw Validator::NullPtr(__LINE__,__FILE__);
        }

        begin = (*_tokens).begin();
        begin+=5;

        // Extract date-time values from tokens
        if(begin != (*_tokens).end()){
            std::copy_if(begin, (*_tokens).end(), std::back_inserter(dateTime),[step1 = 0](const auto & val) mutable { return step1++%2 == 0;});
        }else{
            throw Validator::NullPtr(__LINE__,__FILE__);
        }

        begin = (*_tokens).begin();
        begin+=4;

        // Extract weight values from tokens
        if(begin != (*_tokens).end()){
            std::copy_if(begin, (*_tokens).end(), std::back_inserter(weight),[step1 = 0](const auto & val) mutable { return step1++%4 == 0;});
        }else{
            throw Validator::NullPtr(__LINE__,__FILE__);
        }

        // Validate each city, date-time, and weight value
        std::for_each(cities.begin(),cities.end(),[line = 2 ](const auto &val) mutable
        {
            try{
                Validator::isValidName(val);
                ++line;
            }catch(const Validator::PortCityNameError &e ){
                throw Validator::InvalidFileInput(line, _currentFileName);
            }

        });


        try{
            Validator::isValidDateTimeFormat(*dateTime.begin());
        }catch(const Validator::DateTimeError &){

            throw Validator::InvalidFileInput(line, _currentFileName);

        }


        int counter = 0;
        line = 3;
        for(  auto  val = dateTime.begin()+1 ; val != dateTime.end(); ++val)
        {
            try {
                Validator::isValidDateTimeFormat(*val);
                if( ++counter % 2 == 0)line++;
            }catch(const Validator::DateTimeError &){

                throw Validator::InvalidFileInput(line, _currentFileName);

            }
        };

        std::for_each(weight.begin(),weight.end(),[line = 2](const auto &val) mutable
        {
            try {
                Validator::isValidWeight(val);
                line++;
            }catch(const Validator::InvalidLegalWeight &e) {

                throw Validator::InvalidFileInput(line, _currentFileName);

            }

        });

        // Create edges using the extracted values
        auto copydateTime = dateTime;
        copydateTime.insert(copydateTime.begin(),(*_tokens)[i+3]);
        for(std::size_t c = 1 , w = 1, dt = 0 ; w < weight.size() ; c++, w++, dt+=2){
                _g_t->addEdge(cities[c-1],(int)Chrono(dateTime[dt],dateTime[dt+1]),cities[c], false,copydateTime[dt],copydateTime[dt+1]);
//                _g_c->addEdge((*_tokens)[i],std::stoi(weight[w]), cities[c], false,dateTime[dt],dateTime[dt+1]);
        }

        for(std::size_t c = 0 , w = 0, dt = 0 ; w < weight.size() ; c++, w++, dt+=2){
            _g_c->addEdge((*_tokens)[i],std::stoi(weight[w]), cities[c], false,copydateTime[dt],copydateTime[dt+1]);
        }

        _tokens->clear();
    }else{
        throw Validator::InvalidInput(__LINE__,__FILE__);
    }




}


Factory &Factory::operator << ( std::string &fileName) {


     Delimiters delim(",\n");
    _currentFileName = fileName;

    std::ifstream in(_currentFileName);
    if(!in.is_open()) throw Validator::ERRORopeningReading(_currentFileName );

    std::istreambuf_iterator<char> inputIterator(in);
    std::istreambuf_iterator<char> endIterator;

    TokenIterator<std::istreambuf_iterator<char>, Delimiters>
            wordIter(inputIterator,endIterator, delim), end;

    std::vector<std::string>vec(wordIter,end);
    _tokens->reserve(std::distance(vec.begin(),vec.end()));
    *_tokens=(std::move(vec));


    init_graphs();
    Factory::addFile(fileName);
    std::cout << "Update was successful." << std::endl;
    return *this;
}

void Factory::outbound(const std::string &vertex) const {
    auto val = _g_t->getConstVertex(vertex);
    if(val){
        if(!val->constEdges().empty()){
            std::for_each(val->constEdges().begin(), val->constEdges().end(),[](const auto edge){
                std::cout << edge.getDestination()->getId() <<',' << edge.getWeight() << std::endl;
            });
        }else{
              std::cout <<  vertex << " :no outbound ports"<< std::endl;
            }
    }else{
            std::cerr <<  vertex << " does not exist in the database." << std::endl;
    }

 }

void Factory::inbound(const std::string &vertex) const {
    auto val = _g_t->getConstVertex(vertex);
    if(val){
        if(val && val->getInDegree() != 0){
            for(const  auto & _v : _g_t->vertices()){
                if(_v->getId() != val->getId()){
                    for( const auto  & _e : _v->edges()){
                        if( _e.getDestination()->getId() == val->getId()){
                            std::cout << _e.getSource()->getId() <<',' << _e.getWeight() << std::endl;
                        }
                    }
                }
            }
        }else{
            std::cout <<  vertex << " :no inbound ports"<< std::endl;
        }
    }else{
        std::cerr <<  vertex << " does not exist in the database." << std::endl;
    }

}

void Factory::DFS(const std::string & fo) {
    _g_t->DFS(fo);
    _g_c->DFS(fo);

}

void Factory::balance(const std::string &vertex, const std::string &weight) {
     auto v = _g_t->getConstVertex(vertex);
     auto v2 = _g_c->getConstVertex(vertex);
     if( (!v) || (!v2) ){std::cerr <<  vertex << " does not exist in the database." << std::endl; return;}
    std::cout <<  process_time_containers(v,v2,weight) << std::endl;
}

int Factory::process_time_containers(const shared_vertex<Edge<int>>& v_t, const shared_vertex<Edge<int>>& v_c, const std::string &date) {

    std::string earliest;
    int sum_containers = 0;

    /*
     * check if vertex is a root vertex
     * */

    auto begin = v_t->edges().begin();
    auto end = v_t->constEdges().end();

    if(v_t->isreoot()){

        /*Find the earliest time and calculate chronicle time relative to the earliest departure time*/
        if(begin != end){
            earliest = std::get<0>(begin->getData()); // departure time from the source
            begin+=1;
            sum_containers += begin->getWeight();

            while(begin != end){
                auto temp = std::get<0>(begin->getData());
                if(temp < earliest){
                    earliest = temp;
                }
            }

        }

        /*calculate chronicle time relative to the earliest departure time from the root*/
        int eval = Chrono(earliest, date);
        if(eval < 0){ return 0;}

        return -std::accumulate(v_c->edges().begin(), v_c->edges().end(), 0, [](int currentSum, const auto &val) {
            return currentSum += val.getWeight();
        });

    }

    /*
     * Find all the edges inbound and outbound from vertex
     *
        std::cout << "outbound" << std::endl;
        Factory::outbound(v_t->getId());
     * */

    /*Find all the edges arrive to vertex in the graph of the time*/


    for(const auto & vc : _g_c->vertices()){
        for(const auto & edge_c : vc->constEdges()){
            if(edge_c.getDestination()->getId() == v_c->getId()){
                if((std::get<0>(edge_c.getData()) <= date) && (date <= std::get<1>(edge_c.getData()))) {
                                 sum_containers += edge_c.getWeight();
                }
            }
        }
    }


    return sum_containers;
}

