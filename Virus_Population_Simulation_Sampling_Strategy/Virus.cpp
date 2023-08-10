//
// Created by merom on 12/16/2022.
//

#include <cstring>
#include "Virus.h"
#include <string>
#include <sstream>
#include <valarray>
#include <iostream>

int Virus::val = 1;
int * Virus::currentVersion = &val;



Virus::Virus(const char * name, int size,  std::stringstream &ss, const Virus & target):dim(size){
    std::strcpy(this->name, name);
    dnacode = new int[dim];
    int * begin = dnacode;
    int i = 0;
    while( (ss >> *dnacode)) {i++;dnacode++;}
    if((i > dim) || (i < dim) ){
        std::cerr << "Invalid input." << std::endl;
        exit(1);
    }
    dnacode = begin;

    const int * targetDNA = target.dnacode;
    float similarity = 0;

    for (int j = 0; j < dim; j++) {
        (dnacode[j] == targetDNA[j])?similarity++:similarity;
    }

    mistake = 1 - ( similarity/(float)dim);
    version = 0;
}


Virus::Virus(const Virus &otherVirus):dim(otherVirus.dim) {

    strcpy(name, otherVirus.name);
    const int * otherVirusDNACode = otherVirus.getDNACode();
    dnacode = (this->dnacode == nullptr)?new int [dim]: dnacode;
    for (int i = 0; i < dim; ++i) {
        dnacode[i] = otherVirusDNACode[i];
    }
    mistake = otherVirus.getMistake();
    version = otherVirus.getVersion();
}



Virus::Virus(Virus &&otherV)  noexcept {
    dim = otherV.dim;
    strcpy(name, otherV.name);
    dnacode = otherV.dnacode;
    otherV.dnacode = nullptr;
    mistake = otherV.mistake;
    version = otherV.version;
}



Virus::Virus() {
    dim = 0;
    dnacode = nullptr;
    mistake = 0;
    version = 0;
}

Virus &Virus::operator=(const Virus &otherVirus) {
    if(this == &otherVirus) return *this;

    this->dim = otherVirus.dim;
    std::strcpy(this->name, otherVirus.name);
    if(dnacode==nullptr)dnacode = new int [this->dim];
    const int * otherVirusDNAchain = otherVirus.dnacode;

    if( otherVirusDNAchain != nullptr){
        for (int i = 0; i <dim; i++){
            int k  = otherVirusDNAchain[i];
            dnacode[i] = k;
        }
    }

    this->mistake = otherVirus.mistake;
    this->version = otherVirus.version;

    return *this;
}


Virus &Virus::operator=(Virus &&otherVirus) noexcept {
    if(this == &otherVirus) return *this;
    delete [] dnacode;
    dnacode = otherVirus.dnacode;
    otherVirus.dnacode = nullptr;
    strcpy(name, otherVirus.name);
    mistake = otherVirus.mistake;
    version = otherVirus.version;
    dim = otherVirus.dim;
    return *this;
}








Virus::~Virus(){
    delete[] dnacode;
}


int *Virus::getDNACode() const {
    return dnacode;
}

float Virus::getMistake() const {
    return mistake;
}

int Virus::getDim() const {
    return dim;
}

void Virus::UpdateName(const Virus & superior) {
    strcpy(name, superior.getName());
}

const char *Virus::getName() const {
    return name;
}

void Virus::updateVersion(Virus & otherVirus) {
    UpdateName(otherVirus);
    version = (*currentVersion);
    val +=1;
    for (int i = 0; i < dim; ++i) {
        this->dnacode[i] = otherVirus.dnacode[i];
    }
}




void Virus::setDNACode(std::stringstream &ss) {
    int i = 0;
    if(dnacode == nullptr) {
        if(dim != 0){
            dnacode = new int[dim];
            int * begin = dnacode;
            while( (ss >> *dnacode) ) {i++;dnacode++;}
            if(i > dim){
                std::cerr << "Invalid input." << std::endl;
                exit(1);

            }
            dnacode = begin;
        }
    }else{
        int * begin = dnacode;
        while( (ss >> *dnacode) ) {i++;dnacode++;}
        if(i > dim){
            std::cerr << "Invalid input." << std::endl;
            exit(1);

        }
        dnacode = begin;
    }
}

void Virus::innerPrim(int prim, const Virus & target) {
    int lb = 0;
    int ub = dim-1;
    for (int i = 0; i < prim; ++i) {

        int j = ( std::rand()%(ub - lb + 1) ) + lb ;
        int k = ( std::rand()%(ub - lb + 1) ) + lb;
        int temp =  dnacode[k];
        dnacode[k] = dnacode[j];
        dnacode[j] = temp;
    }

    const int * targetDNA = target.getDNACode();
    float similarity = 0;

    for (int j = 0; j < dim; j++) {
        (dnacode[j] == targetDNA[j])?similarity++:similarity;
    }

    mistake = 1 - ( similarity/static_cast<float>(dim));

}

std::ostream &operator<<(std::ostream &os, const Virus &virus) {
    os <<  virus.name ;
    if(virus.getVersion() == 0) {
        os << '\t' ;
    }else{
        os << '_' << virus.version << '\t';
    }
    for (int i = 0; i < virus.dim; ++i) {
        os << virus.dnacode[i] << ' ';
    }
    os<<'\n';
    return os;
}

Virus::Virus(const int & i) {
   if(i == 1){
       dim = 0;
       dnacode = nullptr;
       mistake = 1.0;
       version = 0;
   }
}
