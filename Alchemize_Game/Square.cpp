//
// Created by merom on 11/29/2022.
//

#include "Square.h"

Squar::Squar():blue_was_here(false), red_was_here(false), current_square_situation('O')
{}

std::ostream &operator<<(std::ostream &os, const Squar &square) {
    os << square.current_square_situation;
    return os;
}



