#include "Validator.h"
#include "CommandLine.h"
/**

    @file main.cpp
    @brief This file contains the main function of the project.
    The project is made by Amir Ammar from the computer science faculty of Tel-Hai.
    It focuses on Global Supply Chains.
    The main function is responsible for executing the program and handling exceptions.
    It enters a while loop and continuously listens for user input through the CommandLine class.
    If the user enters the "exit" command, the loop breaks and the program terminates.
    The main function catches various exceptions that may occur during program execution:
        DateTimeError: Exception thrown when there is an error with date and time format.
        InvalidLegalWeight: Exception thrown when an invalid legal weight is encountered.
        PortCityNameError: Exception thrown when there is an error with port or city names.
        InvalidNumberOfArgs: Exception thrown when the number of command line arguments is invalid.
        CommandNotFound: Exception thrown when an invalid command is entered.
        ERRORopeningReading: Exception thrown when there is an error with opening or reading a file.
        All other exceptions: General catch-all for any other exceptions that may occur.
    In case of an exception, the program exits with a non-zero status code.
    The main function returns 0 to indicate successful execution of the program.
    */
int main(int argc, char * argv []){
    try{
          auto & cmd =  CommandLine::getInstance(Validator::fileFormat(argc,argv));
        while(true){
            try {
                if(cmd.listen(std::cin) == "exit")break;
            }catch( Validator::DateTimeError & ){
                exit(1);
            }catch(Validator::InvalidLegalWeight &){
                exit(1);
            }catch(Validator::PortCityNameError &){
                exit(1);
            }catch(Validator::InvalidNumberOfArgs &) {
                exit(1);
            }catch(Validator::CommandNotFound &){

            }catch(Validator::ERRORopeningReading &){

            }catch(...){
                std::cerr << "Error: occurred" << std::endl;
            }
        }

    }catch( Validator::DateTimeError & ){
        exit(1);
    }catch(Validator::InvalidLegalWeight &){
        exit(1);
    }catch(Validator::PortCityNameError &){
        exit(1);
    }catch(Validator::InvalidNumberOfArgs &) {
        exit(1);
    }
    return 0;
}
