//
// Created by merom on 12/17/2022.
//

#ifndef HOME_WORK_4_DIEDLINE_29_12_2022_FILEMANGER_H
#define HOME_WORK_4_DIEDLINE_29_12_2022_FILEMANGER_H
#include "population.h"
#include <sstream>
#include "List.h"



/**
 * Manage the configfile.dat
 * @param argv
 * @param target
 * @param dim
 * @param innerPrim
 * @return Virus object
 */
Virus & ConfigFile(char * argv[], Virus & target, int & dim, int & innerPrim);

/**
 * Manage firstgeneration.dat file
 * @param argv
 * @param population
 * @param populationSize
 * @param innerPrim
 * @param target
 * @param dim
 * @return Population object
 */
Population & FirstGenFile(char * argv[], Population & population , int &populationSize, int innerPrim, Virus & target,  int dim);

#endif //HOME_WORK_4_DIEDLINE_29_12_2022_FILEMANGER_H
