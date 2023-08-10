//
// Created by merom on 5/26/2023.
//
#include "CommandLine.h"
#include "Tookenizer.h"

std::unique_ptr<CommandLine> CommandLine::_commandLine = nullptr;

std::string CommandLine::listen(std::istream & stream) {

    std::string command;
    std::getline(stream,command);
    auto c = Validator::validateCommand(command);

    switch (c._first){

        case rest::COMMAND::EXIT :{
            return "exit";
        }

        case rest::COMMAND::INBOUND:{
            _loader->getFactory()->inbound(c._second);
            break;
        }

        case rest::COMMAND::LOAD:{
            *_loader << c._second;
            break;
        }


        case rest::COMMAND::OUTBOUND:{
            _loader->getFactory()->outbound(c._second);
            break;
        }

        case rest::COMMAND::BALANCE: {
            _loader->getFactory()->balance(c._second, c._third);
            break;
        }

        case rest::COMMAND::Print : {
            _loader->getFactory()->DFS((_loader->hasOutFile())?_loader->outfile():"output.dat");
            break;
        }

    }
    return "";
}


CommandLine &CommandLine::getInstance(const Validator::shared_pairs& p) {
    if(_commandLine == nullptr) {
        _commandLine = std::unique_ptr<CommandLine>(new CommandLine(p));
    }
    return *_commandLine;
}


