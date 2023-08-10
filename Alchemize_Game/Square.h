//
// Created by merom on 11/29/2022.
//

#ifndef HOME_WORK_3_DIEDLINE_10_12_2022_SquarE_H
#define HOME_WORK_3_DIEDLINE_10_12_2022_SquarE_H

#include <ostream>


class Squar{
private:
    bool blue_was_here;
    bool red_was_here ;
    char current_square_situation;


public:
    friend std::ostream &operator<<(std::ostream &os, const Squar &Square);
    Squar();
    char getCurrentSituation()const{return current_square_situation;}
    inline void setX(){current_square_situation = 'X';}
    inline void setR(){current_square_situation = 'R';}
    inline void setB(){current_square_situation = 'B';}
    inline void setr(){current_square_situation = 'r';}
    inline void setb(){current_square_situation = 'b';}
    inline bool blueWasHere() const { return blue_was_here ;}
    inline bool redWasHere() const {return red_was_here;}
    inline void setBlueWasHere(){blue_was_here = true;}
    inline void setRedWasHere(){red_was_here = true;}


};


#endif //HOME_WORK_3_DIEDLINE_10_12_2022_SquarE_H
