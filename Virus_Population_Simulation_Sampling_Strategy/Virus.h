//
// Created by merom on 12/16/2022.
//

#ifndef HOME_WORK_4_DIEDLINE_29_12_2022_VIRUS_H
#define HOME_WORK_4_DIEDLINE_29_12_2022_VIRUS_H
#include <string>
#include <cstring>
#include <ostream>
#include "List.h"
class Virus {

private:
    int dim;
    char name[8]{};
    int * dnacode{};
    float mistake{};
    int version{};

    static int * currentVersion;
    static int val ;

public:

    /**
     * OverLoaded Constructors
     * @param  name, size, ss, target
     */
    Virus(const char * name , int size, std::stringstream &ss, const Virus & target);

    explicit Virus(const int & i);

    /**
     * default constructor
     */
    Virus();


    /**
     * Big five
     */

    Virus(const Virus & otherVirus);
    Virus(Virus&& otherV) noexcept ;
    Virus& operator=(const Virus & otherVirus) ;
    Virus& operator=(Virus&& otherVirus)noexcept;
    ~Virus();



    /**
     * get the the DNA code series
     * @return
     */
    int *getDNACode() const;
    
    /**
     * get the name of the virus
     * @return 
     */
    const char * getName()const;

    /**
     * get the mistake
     * @return
     */
    float getMistake() const;

    /**
     * get the version
     * @return
     */
    int getVersion()const {return version ;};

    /**
     * get dimendion of the vector
     * @return
     */
    int getDim() const;
    
    /**
     * get the virus mutation;
     * @return
     */
     int getMutation()const;

    /**
     * update the vector with the biggest mistake by the victor with the lowest mistake
     * update version;
     * @param superior
     */
    void UpdateName(const Virus & superior);

    /**
     * update the virus version;
     * @param otherVirus
     */
    void updateVersion(Virus & otherVirus);



    /**
     * set name for virus
     * @param n
     */
     inline void setName( const char * n){strcpy(name,n);};

    /**
    * set dim for virus
    * @param d
    */
     inline void setDim(int d){dim = d;};

    /**
    * set DNACode for virus
    * @param ss
    */
     void setDNACode(std::stringstream &ss);

    /**
    * make n permutation
    * @param prim
    */
     void innerPrim(int prim, const Virus & target);

    /**
    * overload outstream operator
    * @param os, virus
    * @return
    */
    friend std::ostream &operator<<(std::ostream &os, const Virus &virus);

};


#endif //HOME_WORK_4_DIEDLINE_29_12_2022_VIRUS_H
