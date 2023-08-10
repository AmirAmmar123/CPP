//
// Created by merom on 11/17/2022.
//

#include "Observation.h"

int Observation::dim = 0;
float * Observation::mean = nullptr;
int  Observation::maxObservation = 0;




Observation::~Observation() {
    delete [] vector;
}


std::ostream &operator<<(std::ostream &os, const Observation &observation) {
    os << observation.name << " = [" ;
    for (int i = 0; i < Observation::dim ; ++i) {
        os << ' ' << observation.vector[i] ;
    }
    os << ']' << std::endl;
    return os;
}


void Observation::setVector(double *vec) {
    Observation::vector = vec;
}

Observation::Observation() : vector(nullptr) {
}

const char *Observation::getName() const {
    return name;
}

void Observation::setName(const char *n) {
    strcpy(Observation::name, n);
}

void Observation::setVector(double *vec, bool exist) {
    if(exist){
        delete [] vector;
        this->vector = vec;
    }
}

double Observation::getVectorIndex(int i) const {
    return vector[i];
}
