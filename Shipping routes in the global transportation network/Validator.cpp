//
// Created by merom on 5/19/2023.
//

#include "Validator.h"

bool Validator::isLeapYear(int year) {
    // Check if the year is a leap year
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}



void Validator::isValidTime(const std::string &hours, const std::string &minutes) {
    int h = std::stoi(hours);
    int m = std::stoi(minutes);

    // Check if the hours are between 0 and 24
    if( ( h < 0 || h > 24) )throw Validator::DateTimeError("Hours must be between 0 and 24");

    // Check if the minutes are between 0 and 60
    if( (m < 0 || m > 60) ) throw Validator::DateTimeError("Minutes must be between 0 and 60");
}



void Validator::isValidDate(const std::string &day, const std::string &month, const std::string &year ) {
    // Check if the year is valid (2023)
    if (year != "2023") {
        throw Validator::DateTimeError("Year not valid");
    }

    // Check if the month is valid
    int monthValue = std::stoi(month);
    if (monthValue < 1 || monthValue > 12) {
        throw Validator::DateTimeError("Month not valid");
    }

    // Check if the day is valid for the given month
    int dayValue = std::stoi(day);
    int daysInMonth;
    switch (monthValue) {
        case 2: // February
            daysInMonth = isLeapYear(std::stoi(year)) ? 29 : 28;
            break;
        case 4: // April
        case 6: // June
        case 9: // September
        case 11: // November
            daysInMonth = 30;
            break;
        default:
            daysInMonth = 31;
            break;
    }

    if (dayValue < 1 || dayValue > daysInMonth) {
        throw Validator::DateTimeError("Day not valid");
    }


}


void Validator::isValidName(const std::string& name) {
    // Check if the name length exceeds 16 characters
    if(name.length() > 16) { throw Validator::PortCityNameError("Name is bigger than 16 characters"); }

    // Check if the name contains only alphabetic characters and spaces
    std::for_each(name.begin(), name.end(),[](const char & c){if(!std::isalpha(c) && c!=' '){ throw Validator::PortCityNameError("Invalid port name") ;} });
}

void Validator::isValidDateTimeFormat(const std::string &dateTimeString) {
    std::regex dateTimeRegex(R"(^\d{2}/\d{2} \d{2}:\d{2}$)");

    // Check if the date-time string matches the expected format
    if(!std::regex_match(dateTimeString, dateTimeRegex)){throw Validator::DateTimeError("Invalid format dd/mm HH:mm");}


    std::size_t spacePos = dateTimeString.find(' ');
    std::string dateString = dateTimeString.substr(0, spacePos);
    std::string timeString = dateTimeString.substr(spacePos + 1);

    // Validate the date
    std::size_t slashPos = dateString.find('/');
    std::string dayString = dateString.substr(0, slashPos);
    std::string monthString = dateString.substr(slashPos + 1);
    isValidDate(dateTimeString, monthString);


    // Validate the time
    std::size_t colonPos = timeString.find(':');
    std::string hourString = timeString.substr(0, colonPos);
    std::string minuteString = timeString.substr(colonPos + 1);
    isValidTime(hourString,minuteString);

}


void Validator::isValidWeight(const std::string &weight) {
    std::for_each(weight.begin(), weight.end(), [](const char & c){ if(!std::isdigit(c)) throw Validator::InvalidLegalWeight("Digit contains invalid characters");});
}



Validator::shared_pairs Validator::fileFormat(int argc , char * argv []) {

    // Check if the number of command-line arguments is less than 1
    // The first file is actually the executable file name so does not consider
    if(argc < 2){
        throw Validator::InvalidNumberOfArgs(argc - 1);

    }

    // Convert command-line arguments to a vector of strings
    std::vector<std::string> argv_vec(argv,argv + argc);


    int index_i = 0; // Counter for finding the index of "-i"
    int index_o = 0; // Counter for finding the index of "-o"
    bool found_i = false; // Flag to indicate if "-i" is found
    bool found_o = false; // Flag to indicate if "-o" is found

    // Loop through the command-line arguments
    std::for_each(argv_vec.begin(), argv_vec.end(), [&](const auto val){
        // Check if "-i" is found and count the index
        if(val != "-i" && !found_i ){
            ++index_i;
        }else{
            found_i = true;
        }

        // Check if "-o" is found and count the index
        if(val != "-o" && !found_o){
            ++index_o;
        }else{
            found_o = true;
        }
    });

    // Check if "-i" is not found at the expected index
    if(index_i != 1) throw Validator::ARGVformatError();

    // Check if "-o" is found, and if found, check if its index is within valid range
    if(found_o){
        if(index_o > (argv_vec.size() -2 ) ) throw Validator::ARGVformatError();
    }else{
        index_o = 0; //  Set index_o to 0 if "-o" is not found
    }

    // Return a pair of index_o and argv_vec
    return std::make_shared<Validator::pairs>(index_o,argv_vec);
}

Triple<rest::COMMAND,std::string, std::string>  Validator::validateCommand(const std::string &input) {

    std::regex load("^load.*");
    std::regex outbound$(".*,outbound$");
    std::regex inbound$(".*,inbound$");
    std::regex exit$("^exit$");
    std::regex balance(R"(.*,balance,\d{2}/\d{2} \d{2}:\d{2}$)");
    std::regex print("^print$");


    bool p1 = std::regex_match(input, load);
    bool p2 =  std::regex_match(input,outbound$);
    bool p3 = std::regex_match(input,inbound$);
    bool p4 = std::regex_match(input,exit$);
    bool p5 = std::regex_match(input,balance);
    bool p6 = std::regex_match(input,print);

    if(! ( p1 || p2 || p3 || p4 || p5 || p6) ) throw CommandNotFound();

    std::size_t pos;

    if(p1){
        pos = input.find(' ');
        return {rest::COMMAND::LOAD,input.substr(pos + 1),""};
    }

    if(p2){
        pos = input.find(',');
        return {rest::COMMAND::OUTBOUND,input.substr(0,pos),""};
    }

    if(p3){
        pos = input.find(',');
        return {rest::COMMAND::INBOUND,input.substr(0,pos),""};
    }

    if(p4){
        return {rest::COMMAND::EXIT,"",""};
    }

    if(p5){
        Delimiters delim(",");
        TokenIterator<decltype(input.begin()), Delimiters > tokenIteratorbegin(input.begin(),input.end(),delim),end;
        std::vector<std::string> tokens(tokenIteratorbegin,end);
        return {rest::COMMAND::BALANCE,tokens[0],tokens[2]};
    }

    return {rest::COMMAND::Print,"",""};


}


