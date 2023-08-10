//
// Created by merom on 11/29/2022.
//

#include "Alchemize.h"


Alchemize::Alchemize(int size):dim(size),remain(dim*dim),squars(new Squar * [dim]), RedTurn(true), blue_score(0), red_score(0){

    for (int i = 0; i < dim; ++i) {
        squars[i] = new Squar[dim];
    }

}

std::ostream &operator<<(std::ostream &os, const Alchemize &alchemize) {

    os << alchemize.REDName << alchemize.red_score <<'\t' << alchemize.BLUEName << alchemize.blue_score << '\n';
    for (int i = 0; i < alchemize.dim; ++i) {
        for (int j = 0; j < alchemize.dim; ++j) {
            os << alchemize.squars[i][j]<< '\t';
        }
        os << '\n';

    }

    return os;
}




bool Alchemize::is_legal_move(int i, int j) const {

    if( !(( (i) >= 0) && ( (j) >= 0)  && ( (i) < dim) && ( (j) < dim)) ) return false;
    return true;
}

Alchemize::~Alchemize() {
    for (int i = 0; i < dim; ++i) {
         delete [] squars[i];
    }
    delete [] squars;
}


bool Alchemize::ADD(int i, int j) {


    if(RedTurn && remain != 0){
        squars[i-1][j-1].setR();
        remain--;
    }else if(!RedTurn && remain != 0){
        squars[i-1][j-1].setB();
        remain--;
    }

    int row;
    int col;
    for (int k = -2; k < 1; ++k) {
        for (int l = -2; l < 1; ++l) {
          row=k + i;
          col=l + j;
            if(!is_legal_move(row, col) || ( (row == i -1) && (col == j -1)) ){
                continue;
            }else{
                   if(RedTurn){
                       if(squars[row][col].getCurrentSituation() == 'O'){
                           if(squars[row][col].blueWasHere()){
                               squars[row][col].setr();
                               remain--;
                               Alchemize::red_score++;
                           }else{
                               if(squars[row][col].redWasHere()){
                                   squars[row][col].setX();
                                   remain--;
                               }else{
                                   squars[row][col].setRedWasHere();
                               }
                           }
                       }
                       else if(squars[row][col].getCurrentSituation() == 'r'){
                           squars[row][col].setX();
                           (Alchemize::red_score == 0)?Alchemize::red_score:Alchemize::red_score--;
                       }
                       else if(squars[row][col].getCurrentSituation() == 'b'){
                           squars[row][col].setX();
                           (Alchemize::blue_score == 0)?Alchemize::blue_score: Alchemize::blue_score--;

                       }
                   }else{
                       if(squars[row][col].getCurrentSituation() == 'O'){
                           if(squars[row][col].redWasHere()){
                               squars[row][col].setb();
                               remain--;
                               Alchemize::blue_score++;
                           }else{
                               if(squars[row][col].blueWasHere()){
                                   squars[row][col].setX();
                                   remain--;
                               }else{
                                   squars[row][col].setBlueWasHere();
                               }
                           }
                       }
                       else if(squars[row][col].getCurrentSituation() == 'r'){
                           squars[row][col].setX();
                           Alchemize::red_score--;
                       }
                       else if(squars[row][col].getCurrentSituation() == 'b'){
                           squars[row][col].setX();
                           Alchemize::blue_score--;
                       }
                   }
               }
            }
        }
    RedTurn = !RedTurn;
    return true;
}

bool Alchemize::validInput(int i, int j) const {
    if( !(( (i-1) >= 0) && ( (j-1) >= 0)  && ( (i-1) < dim) && ( (j-1) < dim)) ) return false;
    if(squars[i-1][j-1].getCurrentSituation() != 'O') return false;
    return true;
}
