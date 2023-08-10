//
// Created by merom on 6/21/2023.
//

#ifndef HOMEWORK3_VALIDATOR_H
#define HOMEWORK3_VALIDATOR_H

#include <exception>
#include <string>
#include "Geometry.h"
#include <tuple>

using name = std::string;
using type = std::string;
using location = Point;
using degree = double;
using speed = double;
using site_name = std::string;
enum class Commands {EXIT,CREATE, COURSE, DESTINATION, GO, STATUS,ATTACK,STOP, POSITION, STARTWORKING,
        DEFAULT, SIZE, ZOOM, PAN, SHOW};
using immutable = std::tuple<Commands,name, type,site_name, location,degree, speed>;

class Validator : public std::exception{
public:

    explicit Validator(const char* message): _message(message) {}
    Validator(const Validator& e) noexcept{ _message=e._message;}
    explicit Validator(std::string message): _message(std::move(message)) {}
    const char* what() const noexcept override {return _message.c_str();}
    static bool verifyFormatCastle(const std::string& input);
    static bool verifyFormatFarm(const std::string& input);
    static immutable isLineMappedToEnum(const std::string& line);

private:

    std::string _message;
};
#endif //HOMEWORK3_VALIDATOR_H
