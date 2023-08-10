//
// Created by merom on 6/17/2023.
//
#include <utility>

#include "../../../Factory/agent_factory/factory.h"
#include "Peasant.h"
registerInFactory<Agent,Peasant> AgentPeasant("Peasant");

Peasant *Peasant::createInstance(const std::string &name,const Point & xy  ) {
    return new Peasant(name, xy);
}


Peasant::~Peasant() = default;


const Point &Peasant::getLocation() const {
    return Agent::getLocation();
}

void Peasant::update() {
    if(_status != STATUS::DEAD && _status != STATUS::STOPPED ){
        /* if peasant has not reached*/
        if(!_state_machine.reached_farm || !_state_machine.load){

            !_state_machine.load?_physics.time_passed++:_physics.time_passed;

            if( (_physics.time_passed/_physics.time >= 1 ) && !_state_machine.reached_farm ){
                /* assign location as the farm we arrived to*/

                setLocation(getDestination());
                _state_machine.reached_farm = true;

                /*reset time*/
                _physics.time_passed = 0;

                return;

            }
            else if(_state_machine.reached_farm &&  !_state_machine.load){
                /* load crated from farm 5 crates maximum if exist*/
                load();
                _state_machine.load = true; /* assign state_machine->load as true */

                Point current_location = getLocation();

                /* assign a new destination which is the castle */
                setDestination(_destinaionCastle->getLocation());

                /* do the physics equation again*/

                Cartesian_vector cart_vec;
                cart_vec.delta_x = current_location.x - getDestination().x;
                cart_vec.delta_y = current_location.y - getDestination().y;

                Polar_vector polar(cart_vec);

                _physics.distance = polar.r;
                _physics.time = _physics.distance/getSpeed();
                _physics.x_start = getLocation().x;
                _physics.y_start = getLocation().y;
                _physics.x_finish = getDestination().x;
                _physics.y_finish = getDestination().y;
                return;

            }else{
                calculateNextStep();
                return;
            }
        }else if(!_state_machine.reached_castle || !_state_machine.unload){

            !_state_machine.unload?_physics.time_passed++:_physics.time_passed;

            if(_physics.time_passed/_physics.time >= 1 && !_state_machine.reached_castle){

                setLocation(getDestination());
                _state_machine.reached_castle = true;
                return;

            }else if(_state_machine.reached_castle && !_state_machine.unload){
                unload();
                _state_machine.unload = true;
                halt();
                return;
            }else{
                calculateNextStep();
            }
        }
    }
}

void Peasant::broadcast_current_state() {
    Point p(getLocation());
    p.x /= 10;
    p.y /= 10;
   switch (_status){
       case STATUS::DEAD:
           std::cout << "Peasant " << getName() << " at " << p << ", Dead" << std::endl;
           break;
       case STATUS::STOPPED:
           std::cout << "Peasant " << getName() << " at " << p << ", Stopped" << std::endl;
           break;
       case STATUS::MOVING:
           std::cout << "Peasant " << getName() << " at " << p << ", Heading to ";
           if(  !_state_machine.reached_farm && !_state_machine.reached_castle){ std::cout << _sourceFarm->getName() << std::endl;break;}
           if( _state_machine.reached_farm && !_state_machine.reached_castle) {std::cout << _destinaionCastle->getName() << std::endl;break;}
       case STATUS::ONCOURSE:
           /*Does not support*/
           break;
   }
}


void Peasant::load() {
    inventory = _sourceFarm->withdraw(5);
}

void Peasant::unload() {
    _destinaionCastle->deposit(inventory);
    inventory = 0;
}

void Peasant::push_job(shared_ptr<Farm> farm, shared_ptr<Castle> castle) {
    _state_machine = {false,false,false,false};

    _sourceFarm = std::move(farm);
    _destinaionCastle = std::move(castle);

    auto & current_location = getLocation();
    setDestination(_sourceFarm->getLocation()); // at the beginning, the destination is to reach the farm

    Cartesian_vector cart_vec;
    cart_vec.delta_x = current_location.x - getDestination().x;
    cart_vec.delta_y = current_location.y - getDestination().y;

    Polar_vector polar(cart_vec); // not necessary, but I love math :P

    /*I love physics, so let's use physics to calculate location at any given time*/
    _physics.distance = polar.r;
    _physics.time = _physics.distance/getSpeed();
    _physics.x_start = getLocation().x;
    _physics.y_start = getLocation().y;
    _physics.x_finish = getDestination().x;
    _physics.y_finish = getDestination().y;
}

void Peasant::reduce_units_by_one() {
    if(!isDead()){
        --_power_units;
        Agent::reduce_units_by_one();
    }

}

void Peasant::increase_units_by_one() {
    ++_power_units;
    Agent::increase_units_by_one();
}

