//
// Created by merom on 6/11/2023.
//

#ifndef HOMEWORK3_MODEL_H
#define HOMEWORK3_MODEL_H
#endif //HOMEWORK3_MODEL_H
#include "../SimObject/Agent/Thug/Thug.h"
#include "../SimObject/Agent/Knight/Knight.h"
#include "../SimObject/Agent/Peasent/Peasant.h"
#include "../SimObject/Structure/Castle/Castle.h"
#include "../SimObject/Structure/Farm//Farm.h"
#include "algorithm"
#include <memory>
#include <vector>

class Model;
using SingeltonModel = std::unique_ptr<Model>;

using sharedSimObject = std::shared_ptr<SimObject>;
using sharedPeasant = std::shared_ptr<Peasant>;
using sharedKnight = std::shared_ptr<Knight>;
using sharedThug = std::shared_ptr<Thug>;
using sharedCastle = std::shared_ptr<Castle>;
using sharedFarm = std::shared_ptr<Farm>;

using PeasentList = std::vector<sharedPeasant>;
using KnightList = std::vector<sharedKnight>;
using ThugsList = std::vector<sharedThug>;
using CastlesList = std::vector<sharedCastle>;
using FarmsList = std::vector<sharedFarm>;
using SimObectsList = std::vector<sharedSimObject>;




/*Singleton Model*/

class Model{

public:

/**/
    static Model & getInstance() ;



// services member functions
// prevent copy/move construction and assignment
    Model(const Model&) = delete;
    Model& operator= (const Model&) = delete;
    Model(const Model&&) = delete;
    Model& operator= (const Model&&) = delete;
/*************************************************/

    /*Agent list getters*/
    KnightList &  getKnights();
    PeasentList &  getPeasants();
    ThugsList &  getThugs();

    /*Structure list getters*/
    FarmsList &  getFarms();
    const CastlesList & getCastles();



    /*Agent getters*/
     sharedKnight getKnight(const std::string & name);
     sharedPeasant getPeasant(const std::string & name);
     sharedThug getThug(const std::string & name);

    /*Struct getters*/
    sharedCastle getCastle(const std::string & name);
    sharedFarm getFarm(const std::string & name);

    /*add Agent*/
    void add(sharedKnight);
    void add(sharedPeasant);
    void add(sharedThug);

    /*add Structure*/
    void add(sharedCastle);
    void add(sharedFarm);


    const unsigned int & getTime() const;

    bool find_if_exist(const std::string & name) ;
    void update();
    void broadcast();








private:
    static SingeltonModel _model_inst;
    PeasentList _peasentsList;
    KnightList _knightsList;
    ThugsList _thugsList;
    CastlesList _castlesList;
    FarmsList _farmsList;
    unsigned int _time;
    Model():_time(0){};

};

