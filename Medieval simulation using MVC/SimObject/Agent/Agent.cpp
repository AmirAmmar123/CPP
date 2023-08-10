
// Created by merom on 6/17/2023.
//
#include "Agent.h"

void Agent::halt() {
    if(!isDead() ){
        _status = STATUS::STOPPED;
    }
}





Agent::Agent(const std::string &name, const Point & coordinates, int power_units, double speed)
        : SimObject(name), MovableObject({coordinates.x * 10, coordinates.y * 10},{0,0},speed,0), _status(STATUS::MOVING), _power_units(power_units) {}


void Agent::move_to(const Point &x_y,const std::string & site, double speed) {
    if(!isDead()){
        position(x_y);
        if(!site.empty()){
            _status = STATUS::MOVING;
            return;
        }{
            _status = STATUS::ONCOURSE;
            return;
        }
    }else{
        throw Validator("Agent " + getName() + "is died\n");
    }
}

void Agent::position(const Point &coordinates) {
    setDestination(coordinates);
}


bool Agent::isDead() {
    return (STATUS::DEAD == _status);
}

void Agent::calculateNextStep() {
    double fractional_time = _physics.time_passed/_physics.time;
    double  x = getLocation().x;
    double y = getLocation().y;
    x = _physics.x_start +  fractional_time * (_physics.x_finish - _physics.x_start);
    y = _physics.y_start + fractional_time * (_physics.y_finish - _physics.y_start);
    /* set the current location to be the new one arrived so far*/
    setLocation( {x,y});
}

void Agent::calculateNextStepOncourse() {
    double radius = Agent::getSpeed(); // the radius is the distance/time=hours (speed)
    Polar_vector  polar;
    polar.r = radius;
    polar.theta = to_radians(Agent::getCourse());
    Cartesian_vector cartesian(polar);
    setLocation({cartesian.delta_x, cartesian.delta_y}); // new location
}

void Agent::reduce_units_by_one() {
    if(_power_units == 0){
        _status = STATUS::DEAD;
    }
}

void Agent::increase_units_by_one() {

}

int Agent::getPowerUnits() const {
    return _power_units;
}



