//
// Created by merom on 5/31/2023.
//

#ifndef HOMEWORK2_V2_DEADLINE_04_06_23_COMMANDMAPPER_H
#define HOMEWORK2_V2_DEADLINE_04_06_23_COMMANDMAPPER_H
#include <map>
#include <string>

/**

    @brief The namespace rest contains an enum class COMMAND representing different commands.
    The COMMAND enum class defines the following commands:
        LOAD: Represents the command to load a file to a graph.
        EXIT: Represents the command to exit the program.
        OUTBOUND: Represents the command to perform outbound operations on the graph.
        INBOUND: Represents the command to perform inbound operations on the graph.
        BALANCE: Represents the command to balance.
        Print: Represents the command to print(DFS).
    These commands can be used to specify different actions or operations in the program.
    The enum class provides a way to define a set of named constants, making the code more readable and maintainable.
    The rest namespace encapsulates these commands to avoid naming conflicts with other parts of the code.
    */


namespace rest{
    enum class  COMMAND{
        LOAD,
        EXIT,
        OUTBOUND,
        INBOUND,
        BALANCE,
        Print
    };
}

#endif //HOMEWORK2_V2_DEADLINE_04_06_23_COMMANDMAPPER_H
