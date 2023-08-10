#include <iostream>
#include "Observation.h"
#include "lib.h"

int main(int argc, char ** argv) {

    man();

    if(argc > 3 ){ std::cout << "Invalid arguments <int> <int>.\n" << std::endl;}




    Observation::dim  = std::stoi(argv[1]);
    Observation::maxObservation = std::stoi(argv[2]);



    bool exit = false;

    char name[16];

    int totalObservationsAdded = 0;
    int allocated = 10;
    (allocated > Observation::maxObservation)? allocated = Observation::maxObservation : allocated ;
    auto * all_obs = new  Observation[allocated];

    int answer = 0;


    while(!exit){
        std::cin >> answer;
        switch (answer) {
            case ADD:{
                if( (totalObservationsAdded >= Observation::maxObservation) ) {std::cerr << "Invalid observation." << std::endl; break;}
                getName(name);
                if(!getValues(all_obs, name, totalObservationsAdded, allocated)){
                    std::cerr << "Invalid observation." << std::endl;break;}
                break;
            }
            case PRINT:{
                getName(name);
                if(totalObservationsAdded == 0){
                    std:std::cerr << "Invalid or nonexistent observation.\n";
                    break;
                }
                getNameToPrint(name, all_obs, totalObservationsAdded);
                break;
            }
            case MEAN:{
                if(totalObservationsAdded == 0) {std::cerr<<"Empty calculator.\n";break;}
                (Observation::mean == nullptr)? Observation::mean = new float[Observation::dim]: Observation::mean ;
                calculatorMean( all_obs, totalObservationsAdded);
                break;

            }
            case COVMATRIX:{
                if(totalObservationsAdded == 0) {std::cerr<<"Empty calculator.\n";break;}
                if(Observation::mean == nullptr){std::cerr<<"Empty calculator.\n";break;}
                calculatorCovMatrix(all_obs, totalObservationsAdded);
                break;
            }
            case EXIT:{
                exit = true;
                break;
            }
            default:
                std::cerr << "Invalid option\n";
                break;

        }
    }
    delete [] Observation::mean;
    delete [] all_obs;
    return 0;
}
