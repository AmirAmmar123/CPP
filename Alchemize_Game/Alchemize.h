//
// Created by merom on 11/29/2022.
//

#ifndef HOME_WORK_3_DIEDLINE_10_12_2022_ALCHEMIZE_H
#define HOME_WORK_3_DIEDLINE_10_12_2022_ALCHEMIZE_H

#include <ostream>
#include "Square.h"
#include <iostream>
class Squar;

class Alchemize {

private:
    int dim;
    unsigned int remain;
    Squar **squars;
    bool RedTurn;
    unsigned int blue_score;
    unsigned int red_score;
public:
    explicit Alchemize(int size);
    ~ Alchemize();
    unsigned int getRemain()const{return remain;}
    const char * BLUEName = "Blue count: ";
    const char * REDName = "Red count: ";
    bool is_legal_move(int i, int j) const ;
    bool validInput(int i, int j)const;
    bool ADD(int i, int j);
    unsigned int getBlueScore()const{return blue_score;}
    unsigned int getRedScore()const{return red_score;}




    friend std::ostream &operator<<(std::ostream &os, const Alchemize &alchemize);

};
#endif //HOME_WORK_3_DIEDLINE_10_12_2022_ALCHEMIZE_H
