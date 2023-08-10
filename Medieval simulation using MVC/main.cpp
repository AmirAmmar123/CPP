//
// Created by merom on 6/10/2023.
//
#include <iostream>
#include <regex>
#include "Utilities/Validator.h"
#include "Controller/Controller.h"


int main(int argc, char* argv[]){

    try{
        Controller controller(argc, argv);
        controller.startGame();
    }catch (Validator& e){
        cerr << e.what() << endl;
        exit(1);
    }
    return 0;
}

//int main() {
//    std::string input;
//    std::regex regexPattern(
//            R"((\w+)\s+position\s+\((-?\d+(?:\.\d+)?),\s*(-?\d+(?:\.\d+)?)\)(?:\s+(-?\d+(?:\.\d+)?))?)",
//            std::regex_constants::icase
//    );
//
//    std::cout << "Enter a string to verify: ";
//    std::getline(std::cin, input);
//
//    std::smatch match;
//    if (std::regex_search(input, match, regexPattern)) {
//        std::cout << "Format is valid." << std::endl;
//
//        // Extract the name, x, y, and speed values
//        std::string name = match[1];
//        double x = std::stod(match[2]);
//        double y = std::stod(match[3]);
//        double speed = 0.0; // Default speed if not provided
//
//        if (match.size() >= 5) {
//            speed = std::stod(match[4]);
//        }
//
//        std::cout << "Name: " << name << std::endl;
//        std::cout << "Position: x = " << x << ", y = " << y << std::endl;
//        std::cout << "Speed: " << speed << std::endl;
//    } else {
//        std::cout << "Format is not valid." << std::endl;
//    }
//
//    return 0;
//}