#include <iostream>
#include "population.h"
#include "Virus.h"
#include "FileManger.h"
#include "List.h"

/**
 * Check if all the mistakes are all the same
 * @param population
 * @return
 */
bool allTheSameMistake(const Population &population);

/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char * argv[]) {

    if( argc != 3  ){
        std::cerr << "Usage: run the program with <init file name> <location file name>" << '\n';
        exit(1);
    }

    int generations;
    std::cin >> generations;

    int dim = 0;
    int innerPrim  = 0;
    Virus target;
    target = ConfigFile(argv, target, dim, innerPrim);


    int populationSize = 0;
    Population virusPopulation;
    virusPopulation = FirstGenFile(argv, virusPopulation, populationSize, innerPrim, target, dim);
    virusPopulation.setBestVersion(Virus(1));


    unsigned  int counter = 0;
    float lowestmistake = 1;
    float highestmistake;
    float bestVersionMistake ;
    bool updateOnce = false;


    while( ( counter < generations) && ( lowestmistake != 0 ) ){
        if(!updateOnce){

        }
        virusPopulation++;
        /**
         * Throw the virus with the highest mistake
         */
        bestVersionMistake = virusPopulation.getBestVersion().getMistake();
        highestmistake = virusPopulation[populationSize-1].getMistake();
        lowestmistake = virusPopulation[0].getMistake();

        Virus * loser =  &virusPopulation[populationSize-1];
        Virus * winner =  &virusPopulation[0];

        if(lowestmistake < highestmistake){

            loser->updateVersion( *winner);

        }
        if(lowestmistake < bestVersionMistake){

            virusPopulation.setBestVersion(*winner);

        }else if(allTheSameMistake(virusPopulation) && ! updateOnce){
            loser->updateVersion( *winner) ;
            updateOnce = true ;
        }


        virusPopulation.operator*();
        counter++;
    }

    virusPopulation++;
    std::cout << virusPopulation << '\n';
    std::cout << virusPopulation.getBestVersion() ;
    return 0;
}



bool allTheSameMistake(const Population &population){
    float mistake = population[0].getMistake();
    for (int i = 1; i < population.getPopulationSize(); ++i) {
        if(population[i].getMistake() != mistake) {
            return false;
        }
    }
    return true;
}