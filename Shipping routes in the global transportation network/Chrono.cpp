//
// Created by merom on 5/24/2023.
//

#include "Chrono.h"

std::chrono::time_point<std::chrono::system_clock> Chrono::parseDateTime(const std::string &dateTimeString) {
    Validator::isValidDateTimeFormat(dateTimeString); // Validate the format of the date-time string
    std::istringstream iss(dateTimeString);
    std::tm timeStruct = {}; // Initialize a time structure

    // Parse the date-time string and store it in the time structure
    iss >> std::get_time(&timeStruct, "%d/%m %H:%M");

    timeStruct.tm_year = 2023 - 1900; // Set the year to 2023 (subtract 1900)

    std::time_t time = std::mktime(&timeStruct); // Convert the time structure to a time_t value
    return std::chrono::system_clock::from_time_t(time); // Convert the time_t value to a system_clock::time_point
}


Chrono::Chrono(const std::string &dateTimeString1, const std::string &dateTimeString2) {
    // Calculate the duration between the parsed date-time values
    std::chrono::duration<double> duration  =  parseDateTime(dateTimeString2) - parseDateTime(dateTimeString1);

    // Convert the duration to minutes and store the count
    _minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count();
}
