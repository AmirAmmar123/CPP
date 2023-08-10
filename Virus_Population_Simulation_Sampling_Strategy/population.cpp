//
// Created by merom on 12/16/2022.
//

#include <iostream>
#include "population.h"

void Population::setTarget(const Virus &virus) {
    target = Virus(virus);
}

void Population::setBestVersion(const Virus &virus) {
    bestVersionSoFar = Virus(virus);
}

Population::Population(int size, int innerp): sizeOfPopulation(size),innerPrim(innerp),virusVector(new Virus[sizeOfPopulation]){

}

Population::~Population() {
    delete [] virusVector;
}

const Virus &Population::operator[](int index) const {
    if(index < 0 || index >= sizeOfPopulation){
        std::cerr << "Invalid index " << index << "In size of " << sizeOfPopulation << '\n';
    }
    return virusVector[index];
}

Virus &Population::operator[](int index) {
    return virusVector[index];
}

std::ostream &operator<<(std::ostream &os, const Population &population) {
    int size = population.getPopulationSize();
    for (int i = 0 ; i < size ; ++i) {
        os << population[i];
    }
    return os;
}


void Population::operator++(int) {
//    mergeSort(this->virusVector,0, this->sizeOfPopulation-1);

    for (int i = 1 ;  i < sizeOfPopulation ; ++i) {
        insertionSort(virusVector, i);
    }






}

void Population::insertionSort(Virus * viruses, int i ){
    Virus  sort = viruses[i];
    while(i > 0 && viruses[i - 1].getMistake() > (sort.getMistake())){
        viruses[i]  = viruses[i - 1];
        i--;
    }
    viruses[i] = sort;

}


//void  Population::mergeSort(Virus *Population, int l, int r) {
//    if(l < r){
//        int m = l+(r-l)/2;
//        mergeSort(Population,l,m);
//        mergeSort(Population,r,m);
//        merge(Population,l,m,r);
//    }
//}

//void Population::merge(Virus *Population, int l, int m, int r) {
//    int i ,j ,k;
//    int arr1 = m - l +1;
//    int arr2 = r - m ;
//    Virus left[arr1] ;
//    Virus right[arr2];
//    for(int f = 0 ; f < arr1 ; ++f){
//        left[f] = Population[l+f];
//    }
//    for (int s = 0 ; s < arr2 ; ++s){
//        right[s] = Population[m+1+s];
//    }
//
//    i = j = 0;
//    k = l ;
//
//    while(i < arr1 && j < arr2){
//        if(left[i].getMistake() > right[j].getMistake()){
//            Population[k] = left[i];
//            ++i;
//        }
//        else {
//            Population[k]= right[j];
//            ++j;
//        }
//        ++k;
//    }
//
//    while(i<arr1){
//        Population[k] = left[i];
//        ++i;++k;
//    }
//    while(j<arr2){
//        Population[k] = right[j];
//        ++j;++k;
//    }
//
//}



void Population::operator*() const {
    for (int i = 0; i < sizeOfPopulation; ++i) {
        virusVector[i].innerPrim(innerPrim, target);
    }
}

Population::Population() {
    this->sizeOfPopulation = 0;
    this->virusVector = nullptr;
    this->innerPrim = 0;

}

Population::Population(const Population &otherPopulation) {
    this->sizeOfPopulation = otherPopulation.sizeOfPopulation;
    this->innerPrim = otherPopulation.innerPrim;
    delete [] virusVector;
    this->virusVector = new Virus[otherPopulation.sizeOfPopulation];
    for (int i = 0; i < otherPopulation.sizeOfPopulation; ++i) {
        virusVector[i] = otherPopulation.virusVector[i];
    }

}

Population::Population(Population &&otherPopulation)  noexcept {
    this->virusVector = otherPopulation.virusVector;
    otherPopulation.virusVector = nullptr;
    this->sizeOfPopulation = otherPopulation.sizeOfPopulation;
    this->innerPrim = otherPopulation.innerPrim;
}

Population &Population::operator=(const Population &otherPopulation) {
    if(this == &otherPopulation) return *this;
    this->innerPrim = otherPopulation.innerPrim;
    this->sizeOfPopulation = otherPopulation.sizeOfPopulation;
    if(virusVector == nullptr) virusVector = new Virus[sizeOfPopulation];
    for (int i = 0; i < sizeOfPopulation; ++i) {
        virusVector[i] = otherPopulation.virusVector[i];
    }
    return *this;
}


Population &Population::operator=(Population &&otherPopulation) noexcept {
    if(this == &otherPopulation) return *this;
    this->innerPrim = otherPopulation.innerPrim;
    this->sizeOfPopulation = otherPopulation.sizeOfPopulation;
    delete [] virusVector;
    virusVector = otherPopulation.virusVector;
    otherPopulation.virusVector = nullptr;
    return *this;
}

