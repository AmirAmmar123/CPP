//
// Created by merom on 5/26/2023.
//

#ifndef HOMEWORK2_DEADLINE_04_06_23_COMMANDLINE_H
#define HOMEWORK2_DEADLINE_04_06_23_COMMANDLINE_H

#include "GraphLoader.h"
#include "Validator.h"
#include "CommandMapper.h"

/**

    @brief The CommandLine class represents a command line interface for the application.
    It provides functionality for interacting with the user through the command line.
    The class follows the Singleton design pattern to ensure that only one instance of the command line interface exists.
    The getInstance() method is used to obtain the instance of the CommandLine class.
    The copy constructor, assignment operator, move constructor, and move assignment operator are all deleted to prevent multiple instances from being created.
    The listen() method listens for user input from the specified input stream (default is std::cin) and returns the user's input as a string.
    The class also contains a private member variable _loader, which is a unique pointer to a GraphLoader object responsible for loading and managing graphs.
    Overall, the CommandLine class provides an interface for interacting with the user through the command line and managing the loading of graphs in the application.
    */

/**

    @brief Returns the instance of the CommandLine class.
    This method follows the Singleton design pattern and ensures that only one instance of the CommandLine class exists.
    @param p A shared pointer to a pair object containing the necessary parameters for initializing the CommandLine instance.
    @return A reference to the CommandLine instance.
    */

/**

    @brief Listens for user input and returns the input as a string.
    This method reads user input from the specified input stream (default is std::cin) and returns the input as a string.
    @param stream The input stream to read user input from.
    @return The user's input as a string.
*/

class CommandLine{
public:
    static CommandLine & getInstance(const Validator::shared_pairs& p);
    CommandLine(const CommandLine&) = delete;
    CommandLine& operator= (const CommandLine&) = delete;
    CommandLine(const CommandLine&&) = delete;
    CommandLine& operator= (const CommandLine&&) = delete;
    std::string listen(std::istream& stream = std::cin);
private:
    std::unique_ptr<GraphLoader> _loader;
    static std::unique_ptr<CommandLine> _commandLine;
    explicit CommandLine(const Validator::shared_pairs & p):_loader(std::make_unique<GraphLoader>(p)){}
    CommandLine(){};
};



#endif //HOMEWORK2_DEADLINE_04_06_23_COMMANDLINE_H
