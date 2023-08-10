//
// Created by merom on 5/26/2023.
//

#ifndef HOMEWORK2_DEADLINE_04_06_23_GRAPHLOADER_H
#define HOMEWORK2_DEADLINE_04_06_23_GRAPHLOADER_H
#include <utility>

#include "Factory.h"
#include "Validator.h"

/*
 *
 * */
using input_files = std::vector<std::string>;
class GraphLoader{
public:
    explicit GraphLoader(Validator::shared_pairs p):
    _pair(std::move(p))
    ,_has_out_file(_pair->first)
    , _in_files(_pair->second)
    ,_factory_ptr(std::make_unique<Factory>())
    {
        load_graph();
    };


    GraphLoader & operator << (std::string & filename){
        *_factory_ptr << filename;
        return *this;
    }

    [[nodiscard]] const auto & getFactory() const {return _factory_ptr;}

    bool hasOutFile() const {return _has_out_file;}

    const std::string & outfile() const {return _in_files.back();}

private:
    Validator::shared_pairs _pair;   // Shared pointer to a pair of values from Validator
    bool _has_out_file;              // Flag indicating whether an output file is present
    input_files & _in_files;         // Reference to the input file names
    std::unique_ptr<Factory> _factory_ptr;   // Unique pointer to a Factory object for graph loading
    void load_graph();   // Private member function to load the graph based on input files
};
#endif //HOMEWORK2_DEADLINE_04_06_23_GRAPHLOADER_H
