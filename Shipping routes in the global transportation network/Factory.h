//
// Created by merom on 5/24/2023.
//

#ifndef HOMEWORK2_DEADLINE_04_06_23_FACTORY_H
#define HOMEWORK2_DEADLINE_04_06_23_FACTORY_H
#include <utility>
#include "Graph.h"
#include "Validator.h"
#include "Chrono.h"
#include "Edge.h"
#include <numeric>
#include <set>


/**

    @brief The Factory class is responsible for creating and managing Graph objects.
    It provides functionality for creating and initializing Graph objects for different purposes.
    The class contains private member variables for a unique_ptr to a Graph object for time (_g_t),
    a unique_ptr to a Graph object for containers (_g_c), a unique_ptr to a vector of strings (_tokens),
    the current filename (_currentFileName), a flag indicating if the current file is new (_isnewFile),
    and a set of all files (_allFiles).
    The constructor initializes the Factory object by creating the Graph objects for time and containers,
    as well as the vector of strings for tokens.
    The operator++ overloading function is used to perform initialization tasks on the graphs.
    The setCurrentFileName static function sets the current filename and checks if it is already in the set of all files.
    The operator<< overloading function is not specified in the code provided.
    The outbound and inbound functions perform operations on the graph related to outbound and inbound vertices, respectively.
    The addFile static function adds a file to the set of all files.
    The getCurrentFile static function returns the current filename.
    The isNewFile static function checks if the current file is new.
    The DFS function performs a depth-first search on the graph.
    The get_tokens function returns a reference to the vector of tokens.
    The init_graphs function initializes the graphs (time and containers).
    */

class  Graph ;

class Factory{
public:
    explicit Factory():    _g_t(std::make_unique<Graph>("time")),  // Create a unique_ptr to a Graph object for time
                           _g_c(std::make_unique<Graph>("containers")),  // Create a unique_ptr to a Graph object for containers
                           _tokens(std::make_unique<std::vector<std::string>>())  // Create a unique_ptr to a vector of strings
    {
        // Constructor implementation
    };

    Factory & operator ++(){

         init_graphs(); // Initialize the graphs (time and containers)

        return *this;
    }

    static void setCurrentFileName(std::string & filename){
        _isnewFile =  _allFiles.find(filename) != _allFiles.end();// Check if the filename is already in the set of all files
        _currentFileName = std::move(filename);  // Set the current filename
    }

    Factory & operator << ( std::string & fileName);

    void outbound(const std::string & vertex)const; // Perform outbound operations on the graph

    void inbound(const std::string& vertex) const;  // Perform inbound operations on the graph

    void balance(const std::string & vertex,const std::string &weight);

    static void addFile(const std::string& file){_allFiles.insert(file);} // Add a file to the set of all files

    static const std::string & getCurrentFile() {return _currentFileName;} // Get the current filename

    static bool isNewFile() { return _isnewFile ;}  // Check if the current file is a new file

    void DFS(const std::string &fo ); // Perform depth-first search on the graph

    int process_time_containers(const shared_vertex<Edge<int>>& v_t, const shared_vertex<Edge<int>>& v_c, const std::string &date);

public:
    std::unique_ptr<std::vector<std::string>> & get_tokens() { return _tokens; }
private:
    std::unique_ptr<Graph> _g_t;  // Unique_ptr to a Graph object for time
    std::unique_ptr<Graph> _g_c;  // Unique_ptr to a Graph object for containers
    static std::string _currentFileName;  // Current filename
    std::unique_ptr<std::vector<std::string>> _tokens;  // Unique_ptr to a vector of tokens
    static bool _isnewFile;  // Flag indicating if the current file is new
    static std::set<std::string> _allFiles;  // Set of all files

    void init_graphs();  // Initialize the graphs (time and containers)
};
#endif //HOMEWORK2_DEADLINE_04_06_23_FACTORY_H
