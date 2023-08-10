//
// Created by merom on 6/11/2023.
//

#ifndef HOMEWORK3_PEASANT_H
#define HOMEWORK3_PEASANT_H
#include "../Agent.h"
#include <queue>
#include "../../Structure/Farm/Farm.h"
#include "../../Structure/Castle/Castle.h"


class Peasant : public Agent{

public:
    /* each peasants move in a const speed of 5km/hr
     * each peasants have initial power of 5 units and max power 20
     * */

    Peasant(const std::string & name, const Point & xy  ): Agent(name, xy,10,5),_sourceFarm(nullptr),_destinaionCastle(nullptr),inventory(0){
        _status = STATUS::STOPPED; // by default Agent is Stopped
        _state_machine = {true, true, true, true};
    };

    static Peasant * createInstance(const std::string & name, const Point & xy  );
    ~Peasant() override;


public:
    const Point &getLocation() const override;

    void update() override;

    void push_job(shared_ptr<Farm> farm, shared_ptr<Castle> castle);

    void broadcast_current_state() override;

    /* peasant receives a command start_work with parameters
     * @param farm: string
     * @param a castle: string
     *
     * in the farm he will load crates for an hour, then later he will move
     * to the castle in order to offload the crates during one hour
     * if he has not received any command he will stay at the castle
     * peasant can't gold more than 5 crates, if there is no 5 crates in the farm
     * then carry the remaining crates*/


    bool checkIfJobFinished() const {return _state_machine.unload && _state_machine.reached_castle && _state_machine.load && _state_machine.reached_farm ;}
    /*  give a command simultaneously */
    /*
     * Does not support
     * functionality: position, course
     * */

    void load();

    void unload();


    using StateMachine = struct StateMachine{
        bool reached_castle = false;
        bool load = false;
        bool unload = false ;
        bool reached_farm = false;
    };

    void reduce_units_by_one() override;


    void increase_units_by_one() override;

    void set_invy_zero() {inventory = 0;}
private:
    std::shared_ptr<Farm> _sourceFarm;
    std::shared_ptr<Castle> _destinaionCastle ;
    StateMachine _state_machine;
    int inventory ;


};
#endif //HOMEWORK3_PEASANT_H
