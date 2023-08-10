
//
// Created by merom on 5/24/2023.
//

#ifndef HOMEWORK2_DEADLINE_04_06_23_CHRONO_H
#define HOMEWORK2_DEADLINE_04_06_23_CHRONO_H
#include "Validator.h"
/**

    @brief The Chrono class provides utility methods for working with time durations and parsing date-time strings.
    The class allows the calculation of time durations between two date-time strings in minutes.
    It also provides a static method to parse a date-time string and convert it to a std::chrono::time_point object.
    The class includes an implicit conversion operator that allows converting an instance of Chrono to an integer representing the time duration in minutes.
    Overall, the Chrono class simplifies working with time durations and date-time parsing, making it easier to perform time-related calculations in the application.
    */

/**

    @brief Constructs a Chrono object with the given two date-time strings.
    @param dateTimeString1 The first date-time string.
    @param dateTimeString2 The second date-time string.
    */

/**

    @brief Parses a date-time string and returns a std::chrono::time_point object.
    @param dateTimeString The date-time string to parse.
    @return A std::chrono::time_point object representing the parsed date-time.
    */

/**

    @brief Implicit conversion operator that converts a Chrono object to an integer representing the time duration in minutes.
    @return The time duration in minutes as an integer.
 */

class Chrono{
public:
    Chrono(const std::string& dateTimeString1 , const std::string& dateTimeString2 = "01/01 00:00");

    static std::chrono::time_point<std::chrono::system_clock> parseDateTime(const std::string& dateTimeString);

     operator int() const{
        return (int)(_minutes);
    }

private:
    long long  _minutes ;

};
#endif //HOMEWORK2_DEADLINE_04_06_23_CHRONO_H
