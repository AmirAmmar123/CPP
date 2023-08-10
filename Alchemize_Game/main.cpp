#include <iostream>
#include "Alchemize.h"
int main(int argc, char * argv[]) {

    if(argc > 2 || (argv == nullptr) || (argc < 2) ){
        std::cerr  << "Invalid run arguments; run the game with board size.\n";
        return 1;
    }
    char * c =  argv[1];
    char digit = c[0];

    int dg = digit - 48;

    Alchemize alchemize(dg);
    std::cout << alchemize ;

    while(alchemize.getRemain()!=0){
        std::cout << "R:\n";
        int i, j;
        std::cin>>i>>j;
        while(!alchemize.validInput(i,j)){
            std::cerr << "Invalid row/col index or non free cell\n";
            std::cout << "R:\n";
            std::cin>>i>>j;
        }
        alchemize.ADD(i,j);
        std::cout << alchemize;
        if(alchemize.getRemain() == 0)break;
        std::cout << "B:\n";
        std::cin>>i>>j;
        if(alchemize.getRemain() == 0)break;
        while(!alchemize.validInput(i,j)){
            std::cerr << "Invalid row/col index or non free cell\n";
            std::cout << "B:\n";
            std::cin>>i>>j;
        }
        alchemize.ADD(i,j);
        std::cout << alchemize;


    }
    unsigned int blueScore = alchemize.getBlueScore();
    unsigned int redScore = alchemize.getRedScore();

    if( blueScore == redScore){
        std::cout << "The game ended with a tie\n";
        return 0;
    }
    (blueScore > redScore)?std::cout<<"Blue won\n": std::cout<<"Red won\n";

    return 0;
}
