//
// Created by merom on 11/17/2022.
//

#include "lib.h"
#include <cstring>
#include <sstream>
#include <limits>


void man(){

    std::cout << "[1] New observation\n"
              << "[2] Print observation\n"
              << "[3] Expected value vector\n"
              << "[4] Covariance matrix\n"
              << "[5] Exit\n";

}

bool getName(char name []){

    std::cout << "Enter observation name:";
    std::cin >> name ;
    std::cout << std::endl;
    return true;

}

bool getValues( Observation allObs [], char name [], int & all_obs_size, int & allocated){
    if(all_obs_size >= Observation::maxObservation - 1) return false;
    std::cout << "Enter observation values:";
    std::string s;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin,s);
    std::stringstream  ss(s);
    std::cout << '\n';

    double val = 0;
    int count = 0;

    auto * values = new double [Observation::dim];

    while(ss >>  val ){
        count ++;
        if( (count > Observation::dim)  ) {
        delete [] values;
        return false;
        }
        values[count - 1] = val;
    }
    if( (count < Observation::dim)  ) {
        delete [] values;
        return false;
    }

    int index = ObsExist(name, allObs, all_obs_size);

    if( (index >= 0 )){
        bool exist = true;
        allObs[index].setVector(values, exist);
        return true;
    }


    if(all_obs_size == allocated && all_obs_size != Observation::maxObservation){
        allocated += 10;
        (allocated > Observation::maxObservation)? allocated = Observation::maxObservation : allocated;
        auto * observations = new Observation[allocated];
        for (int i = 0; i < all_obs_size; ++i) {
            observations[i] = allObs[i];
        }
        delete [] allObs;
        allObs = observations;
    }

    allObs[all_obs_size].setName(name);
    allObs[all_obs_size].setVector(values);
    all_obs_size++;

    return true;



}

int ObsExist(char name [], Observation allObs [], const int & all_obs_size ){
    if (all_obs_size == 0 ) return -1;
    for (int i = 0; i < all_obs_size; ++i) {
        if(strcmp(allObs[i].getName(), name) == 0){
            return i;
        }
    }
    return -1;
}


void getNameToPrint(char name [], Observation allObs [], const int & all_obs_size ){
    int index = ObsExist(name, allObs, all_obs_size);
    if (index >= 0){
        std::cout << allObs[index];
    }else{
        std:std::cerr << "Invalid or nonexistent observation.\n";
        return;
    }
}
void calculatorMean(Observation allObs [], const int & total_added){
    std::cout << "mean = [";
    float val = 0;
    for (int j = 0; j < Observation::dim; ++j) {
        for (int k = 0; k < total_added; ++k) {
            val +=(float) allObs[k].getVectorIndex(j);
        }
        std::cout << ' ' << (float) (val/(float) total_added) ;
        Observation::mean[j] = (float) (val /(float) total_added);
        val = 0;
    }
    std::cout << "]\n";
}

void calculatorCovMatrix(  Observation allObs [], const int & total_added){
    int length;
    (total_added > 1)? length = (total_added - 1) : length = (total_added) ;

    std::cout << "cov = [\n";


    for (int i = 0; i < Observation::dim; ++i) {
        for (int j = 0; j < Observation::dim; ++j) {
            float val = 0;
            for (int k = 0; k < total_added; ++k) {
                val += float((float )((float)allObs[k].getVectorIndex(i) - (float )Observation::mean[i]) *
                             (float )((float)allObs[k].getVectorIndex(j) - (float)Observation::mean[j]));
            }
            std::cout << ' ' << (float )val/(float )length ;

        }
        std::cout  << '\n';
    }
    std::cout << "]";
}

