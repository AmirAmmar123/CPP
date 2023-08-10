//
// Created by merom on 5/26/2023.
//
#include <fstream>
#include "GraphLoader.h"
#include "Tookenizer.h"

const Delimiters delim(",\n\r");
using vec_tokens = std::vector<std::string>;

void GraphLoader::load_graph() {
    int go_back = 0;

    if(_has_out_file){
       go_back = 2; // Adjust the index to skip output file-related processing
    }

    for (std::size_t i = 2; i < _in_files.size() - go_back; ++i) {

        std::ifstream in(_in_files[i]);
        if(!in.is_open()) throw Validator::FileFailedToOpen( _in_files[i] );

        _factory_ptr->setCurrentFileName(_in_files[i]);


        std::istreambuf_iterator<char> inputIterator(in);
        std::istreambuf_iterator<char> endIterator;

        TokenIterator<std::istreambuf_iterator<char>, Delimiters>
                wordIter(inputIterator,endIterator, delim), end;

        // Tokenize the input file content and store the tokens in the Factory object
        std::vector<std::string>vec(wordIter,end);
        _factory_ptr->get_tokens()->reserve(std::distance(vec.begin(),vec.end()));
        *_factory_ptr->get_tokens() = std::move(vec);


        in.close();

        // Perform additional operations using the Factory object -> init graph
        (++ (* _factory_ptr) );
      Factory::addFile(_factory_ptr->getCurrentFile());

    }



}


