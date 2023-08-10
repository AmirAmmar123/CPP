//
// Created by merom on 11/17/2022.
//

#ifndef TEMP5_OBSERVATION_H
#define TEMP5_OBSERVATION_H

#include <ostream>
#include <iostream>
#include <cstring>

class Observation {
public:
    Observation();
    virtual ~Observation();

    friend std::ostream &operator<<(std::ostream &os, const Observation &observation);
    void setVector(double *vec, bool exist);
    void setVector(double *vec);

    const char *getName() const;

    void setName(const char * n);

    static float * mean;
    static int dim;
    static int maxObservation ;

    double getVectorIndex(int i) const;


private:


    char name[16]{};
    double * vector;


};



#endif //TEMP5_OBSERVATION_H
