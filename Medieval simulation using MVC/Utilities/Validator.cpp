//
// Created by merom on 6/21/2023.
//
#include <regex>
#include <iostream>
#include "Validator.h"
#include "Tookenizer.h"

bool Validator::verifyFormatCastle(const std::string &input) {
    std::regex pattern(R"(^[\w]{1,16}, \(\d+\.\d+, \d+\.\d+\), \d+$)");
    return std::regex_match(input, pattern);
}

bool Validator::verifyFormatFarm(const std::string &input) {
    std::regex pattern(R"(^[\w]{1,16}, \(\d+\.\d+, \d+\.\d+\), \d+, \d+$)");
    return std::regex_match(input, pattern);
}

immutable Validator::isLineMappedToEnum(const std::string &line) {


    std::regex regexCreateThugPeasant(

            R"(^create\s+(\w+)\s+(Thug|Peasant)\s+\((\d+(?:\.\d+)?),\s*(\d+(?:\.\d+)?)\))",
            std::regex_constants::icase
    );

    std::regex regexCreateKnight(
            R"(^create\s+(\w+)\s+Knight\s+(\w{1,16}))",
            std::regex_constants::icase
    );

    std::regex regexCourse(
            R"(^(\w+)\s+course\s+(\d+)(?:\s+(\d+))?)",
            std::regex_constants::icase
    );

    std::regex regexDestination(
            R"(^(\w+)\s+destination\s+(\w{1,16}))",
            std::regex_constants::icase
    );

    std::regex regexGo(
            R"(^go)",
            std::regex_constants::icase
    );

    std::regex regexStatus(
            R"(^status)",
            std::regex_constants::icase
    );

    std::regex regexExist(
            R"(^exit)",
            std::regex_constants::icase
    );

    std::regex regexStop(
            R"(^"^stop\\s+\\w+$")",
            std::regex_constants::icase
    );

    std::string input;
    std::regex regexPosition(
            R"((\w+)\s+position\s+\((-?\d+(?:\.\d+)?),\s*(-?\d+(?:\.\d+)?)\)(?:\s+(-?\d+(?:\.\d+)?))?)",
            std::regex_constants::icase
    );

    std::regex regexWork(
            R"(([\w\s]{1,16})\s+(\w+)\s+(\w+)\s+start working)",
            std::regex_constants::icase
            );

    std::regex regexAttack(
            R"(([\w]{1,16})\s+attack\s+([\w]{1,16}))",
            std::regex_constants::icase
            );

    std::regex regexShow(
        R"(^show)",
        std::regex_constants::icase
    );

    std::regex regexPan(
            R"(^pan\s+\((\d+(?:\.\d+)?),\s*(\d+(?:\.\d+)?)\))", // Updated regex for "pan" command with coordinates.
            std::regex_constants::icase
    );

    std::regex zoomRegex(R"(^zoom\s+([0-9]*[.])?[0-9]+)",
                         std::regex_constants::icase
    );


    std::regex regexSize(
            R"(^size\s+(\d{1,2}))",
            std::regex_constants::icase
    );

    std::regex regexDefault(
        R"(^default)",
        std::regex_constants::icase
    );


    std::smatch matches;


    // Command detection using regex matching
    if (std::regex_match(line, matches, regexCreateThugPeasant)) {
        /* Handle 'create' command for Thug/Peasant
          Extract information from regex matches
          Return corresponding enum and parsed values
          */
        std::string name = matches[1].str();
        std::string type = matches[2].str();
        double x = std::stod(matches[3].str());
        double y = std::stod(matches[4].str());
        return {Commands::CREATE, name, type, "", {x,y}, 0, 0 };

    } else if (std::regex_match(line, matches, regexCreateKnight)) {
        /* Handle 'create' command for Knight
         * Extract information from regex matches
         * Return corresponding enum and parsed values
         * */
        std::string name = matches[1].str();
        std::string site = matches[2].str();
        return {Commands::CREATE,name, "Knight", site,{0,0},0,0};

    } else if (std::regex_match(line, matches, regexCourse)) {
        /* Handle 'course' command
         * Extract information from regex matches
         * Return corresponding enum and parsed values
        */
        std::string name = matches[1].str();
        float degree = std::stof(matches[2].str());
        float speed = std::stof(matches[3].str());
        return {Commands::COURSE,name,"","",{0,0},degree,speed};

    } else if (std::regex_match(line, matches, regexDestination)) {
        /* Handle 'destination' command
         * Extract information from regex matches
         * Return corresponding enum and parsed values
         * */
        std::string name = matches[1].str();
        std::string site = matches[2].str();
        return {Commands::DESTINATION,name,"",site,{0,0},0,0};

    } else if (std::regex_match(line, matches, regexGo)) {
        // Handle 'go' command
        // Return corresponding enum and default values
        return {Commands::GO,"","","",{0,0},0,0};

    } else if (std::regex_match(line, matches, regexStatus)) {
        // Handle 'status' command
        // Return corresponding enum and default values
        return {Commands::STATUS,"","","",{0,0},0,0};

    }else if( std::regex_match(line, matches, regexExist)){
        // Handle 'exit' command
        // Return corresponding enum and default values
        return {Commands::EXIT,"","","",{0,0},0,0};

    }else if(std::regex_match(line, matches, regexStop)){
        // Handle 'stop' command
        // Extract information from regex matches
        // Return corresponding enum and parsed values
        std::string name = matches[1].str();
        return {Commands::STOP,name,"","",{0,0},0,0};

    }else if( std::regex_match(line, matches, regexPosition) ){
        // Handle 'position' command
        // Extract information from regex matches
        // Return corresponding enum and parsed values
        std::string name = matches[1];
        double x = std::stod(matches[2]);
        double y = std::stod(matches[3]);
        double speed = 0.0; // Default speed if not provided

        if (matches.size() >= 5) {

            speed = std::stod(matches[4]);

        }
        return {Commands::POSITION, name, "","",{x,y},0,speed};

    }else if(std::regex_match(line,matches,regexWork)){
        // Handle 'work' command
        // Extract information from regex matches
        // Return corresponding enum and parsed values
        std::string name = matches[1].str();
        std::string source = matches[2].str();
        std::string destination = matches[3].str();
        return {Commands::STARTWORKING, name,source,destination,{0,0},0,0 };

    }else if(std::regex_match(line,matches,regexAttack)){
        // Handle 'attack' command
        // Extract information from regex matches
        // Return corresponding enum and parsed values
        std::string attacker = matches[1].str();
        std::string target = matches[2].str();
        return{Commands::ATTACK,attacker,target, "",{0,0},0,0};

    }else if (std::regex_match(line, matches, regexShow)) {
        // Handle 'show' command
        // Return corresponding enum and default values
        return {Commands::SHOW, "", "", "", {0, 0}, 0, 0};
    } else if (std::regex_match(line, matches, regexPan)) {
        // Handle the valid "pan" command with coordinates (xCoord, yCoord).
        // You can use the 'xCoord' and 'yCoord' variables here to perform panning logic.

        for( const auto & val : matches){
            std::cout << val << std::endl;
        }
        double xCoord = std::stod(matches[1].str());
        double yCoord = std::stod(matches[2].str());
        return {Commands::PAN, "", "", "", {xCoord, yCoord}, 0, 0};
    } else if (std::regex_match(line, matches, zoomRegex)) {
        // Handle the valid "zoom" command with a positive zoom value.
        // You can use the 'zoomValue' variable here to perform zooming logic.
         std::size_t k =  matches[0].str().find(' ') ;
         double zoomValue = stod(matches[0].str().substr(k));
        if (zoomValue > 0) {
            return {Commands::ZOOM, "", "", "", {0, 0}, 0, zoomValue};
        }
    } else if (std::regex_match(line, matches, regexSize)) {
        // Handle the valid "size" command with size in the valid range.
        // You can use the 'size' variable here to update the size accordingly.
        int size = std::stoi(matches[1].str());
        if (size >= 6 && size <= 30) {
            return {Commands::SIZE, "", "", "", {0, 0}, 0, double(size)};
        }
    } else if (std::regex_match(line, matches, regexDefault)) {
        // Handle 'default' command
        // Return corresponding enum and default valuess
        return {Commands::DEFAULT, "", "", "", {0, 0}, 0, 0};
    }
    //std::tuple<Commands, name, type, site_name, location,degree, speed>;

    throw Validator("Command or format is not valid: " + line);

}
