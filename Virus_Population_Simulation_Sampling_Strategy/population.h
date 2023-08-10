//
// Created by merom on 12/16/2022.
//

#ifndef HOME_WORK_4_DIEDLINE_29_12_2022_POPULATION_H
#define HOME_WORK_4_DIEDLINE_29_12_2022_POPULATION_H
#include "Virus.h"
#include "List.h"

class Population {

private:
    Virus bestVersionSoFar;
    Virus target;
    int sizeOfPopulation;
    int innerPrim;
    Virus *virusVector{};


    /**
     * Merge Sort algorithm
     * @param Population
     * @param l
     * @param r
     */

//    void static  mergeSort(Virus * Population, int l , int r);

    /**
   * Merge algorithm
   * @param Population
   * @param l
   * @param m
   * @param r
   */
//    void static merge(Virus * Population, int l, int m, int r);

    /**
     * Insertion sort
     * @param viruses
     * @param i
     */
    static void insertionSort(Virus * viruses , int i  );




public:
    /**
     * big five
     *
     */
    Population(const Population & otherPopulation);
    Population(Population && otherPopulation) noexcept ;
    Population &operator=(const Population & otherPopulation);
    Population &operator=(Population && otherPopulation) noexcept ;
    Population();

    ~Population();


    /**
     * get the virus population
     * @return
     */
    Virus * getPopulation()const{return virusVector;}


    /**
     *
     * @param size
     * @param innerPrim
     */
    explicit Population(int size, int innerPrim);



    /**
     * Over load [] operator
     * @param index
     * @return
     */
    Virus & operator[](int index);
    const Virus & operator[](int index) const;

    /**
     * static function to set the target virus
     * @param virus
     */
    void setTarget(const Virus & virus);

    /**
     * set the best version during the generation
     * @param virus
     */
    void setBestVersion(const Virus &virus);

    Virus & getBestVersion(){return bestVersionSoFar;};

    /**
     * return the size of the population
     * @return
     */

    int getPopulationSize() const { return sizeOfPopulation; };

    /**
     * overload outstream operator
     * @param os, population
     * @return
     */
    friend std::ostream& operator<<(std::ostream& os, const Population& population);


    /**
     * Overload for operator ++
     * postfix Object++
     */
      void  operator ++( int );

    /**
     * Overload for operator *
     * postfix Object*
     */
    void  operator *() const;



};


#endif //HOME_WORK_4_DIEDLINE_29_12_2022_POPULATION_H
