//
// Created by merom on 5/19/2023.
//

#ifndef HOMEWORK2_DEADLINE_04_06_23_VALIDATOR_H
#define HOMEWORK2_DEADLINE_04_06_23_VALIDATOR_H
#include <string>
#include <iostream>
#include <iostream>
#include <chrono>
#include <regex>
#include <iomanip>
#include <sstream>
#include "CommandMapper.h"
#include "Triple.h"
#include "Tookenizer.h"

/**

    @brief The Validator class provides utility methods for data validation and exception constructors for specific validation errors.
    The class contains static methods for validating various aspects of data used in the application, such as names, weights, date and time formats, and file formats.
    It also includes a method to validate a command input and return the corresponding command, node, and additional arguments.
    The class encapsulates the validation logic and allows these checks to be performed without the need to create an instance of the class.
    Additionally, the class includes exception constructors that create custom exceptions for specific validation errors. These exceptions can be thrown to handle exceptional conditions during the validation process.
    Overall, the Validator class plays a crucial role in ensuring the correctness and integrity of data used within the application, providing a centralized and reusable set of validation functions.
*/

class Validator{
public:
    /*
  * Exception constructors
  * */
    struct PortCityNameError : std::exception{
        explicit PortCityNameError(const std::string& what){std::cerr << what << std::endl;};
    };

    struct DateTimeError : std::exception{
        explicit DateTimeError(const std::string& what){std::cerr << what << std::endl;};
    };

    struct InvalidLegalWeight : std::exception{
        explicit InvalidLegalWeight(const std::string& what){std::cerr << what << std::endl;};
    };

    struct InvalidFileInput : std::exception{
        explicit InvalidFileInput(int i, const std::string& fileName){std::cerr << "Invalid input in file " << fileName << " at line " << i << std::endl;}
    };

    struct InvalidInput : std::exception{
        explicit InvalidInput(int i, const std::string& fileName){std::cerr << "Invalid input at line " << i  << " file name " << fileName << std::endl;}
    };


    struct NullPtr: std::exception{
        explicit NullPtr(int line, const char filename[94]){std::cerr << "NULL object at line "
                                                                     << line << "File name " << filename << std::endl;}
    };

    struct InvalidNumberOfArgs : public std::exception{
        explicit InvalidNumberOfArgs(int argc){
            std::cerr << "Number of arguments: " << argc << " is less than the minimum requirements 1" << std::endl;}
    };

    struct ARGVformatError : public std::exception{
        ARGVformatError(){
            std::cerr << "argv format error" << std::endl;
        }
    };

    struct FileFailedToOpen : public std::exception{
        explicit FileFailedToOpen(const std::string & filename){std::cerr << "File " << filename << " Failed to open" << std::endl;}
    };

    struct ERRORopeningReading : public  std::exception{
        explicit ERRORopeningReading( const std::string & filename){ std::cerr << "ERROR opening/reading the specified file." << std::endl;}

    };

    struct CommandNotFound : public  std::exception{
        explicit CommandNotFound(){std::cerr <<"USAGE: 'load' <file> *or*\n"
                                                                          "<node>,'inbound' *or*\n"
                                                                          "<node>,'outbound' *or*\n"
                                                                          "<node>,'balance',dd/mm HH:mm *or*\n"
                                                                          "'print' *or*\n"
                                                                          "'exit' *to terminate*\n\n";}
    };



public:
    using pairs = std::pair<int, std::vector<std::string>>;
    using shared_pairs = std::shared_ptr<pairs>;

    static void isValidName(const std::string& name);
    static void isValidWeight(const std::string& weight);
    static void isValidDateTimeFormat(const std::string& dateTimeString);
    static shared_pairs fileFormat(int argc , char * argv []);
    static Triple<rest::COMMAND,std::string, std::string>  validateCommand(const std::string & input);
private:
    static void isValidDate(const std::string& day, const std::string& month, const std::string& year = "2023");
    static void isValidTime(const std::string& hours, const std::string& minutes);
    static bool isLeapYear(int year) ;


};


#endif //HOMEWORK2_DEADLINE_04_06_23_VALIDATOR_H
