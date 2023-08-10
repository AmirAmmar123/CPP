//
// Created by merom on 12/17/2022.
//

#include "FileManger.h"
#include <fstream>
#include <iostream>


Virus & ConfigFile(char * argv[], Virus & target, int & dim, int & innerPrim){

    std::string line;
    std::ifstream configFile(argv[1], std::ios_base::in);
    std::stringstream arr;

    if(configFile.is_open()){
        int i=0;
        while(!configFile.eof()){
            std::getline(configFile, line);
            switch (i) {
                case 0:
                    dim = std::stoi(line);
                    i++;
                    break;
                case 1:
                    innerPrim = std::stoi(line);
                    i++;
                    break;
                case 2:
                    arr << line;
                    i++;
                    break;
                default:
                    break;
            }
        }
    }


    configFile.close();
    const char * name = "target";
    target.setName(name);
    target.setDim(dim);
    target.setDNACode(arr);




    return target;

}
Population & FirstGenFile(char * argv[], Population & population,  int &populationSize,  int innerPrim , Virus & target, int dim){
    std::string line;
    std::ifstream firstgeneration(argv[2], std::ios_base::in);


    if(firstgeneration.is_open()){
        std::getline(firstgeneration, line);
        populationSize = std::stoi(line);
    }


    population = Population(populationSize,innerPrim);

    int i = 0;
    population.setTarget(target);
    while(!firstgeneration.eof() && i < populationSize ){
        char virusName[8];
        std::getline(firstgeneration, line);
        std::stringstream ss(line);
        ss >> virusName;
        population[i] = Virus(virusName, dim, ss,target);
        i++;
    }
    firstgeneration.close();


    return population;
}

