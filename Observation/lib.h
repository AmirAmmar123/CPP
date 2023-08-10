//
// Created by merom on 11/17/2022.
//

#ifndef TEMP5_LIB_H
#define TEMP5_LIB_H
#include <iostream>
#include "Observation.h"

void man();
enum OPTION{ADD=1, PRINT, MEAN, COVMATRIX, EXIT};
bool getName(char name[]);
bool getValues(Observation allObs [], char name [], int & all_obs_size, int & allocated);
void getNameToPrint(char name [], Observation allObs [], const int & all_obs_size );
int  ObsExist(char name [], Observation allObs [], const int & all_obs_size );
void calculatorMean(Observation allObs [], const int & total_added);
void calculatorCovMatrix(Observation allObs [], const int & total_added);
#endif //TEMP5_LIB_H
