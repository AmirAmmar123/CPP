//
// Created by merom on 6/17/2023.
//
#include "../../../Factory/agent_factory/factory.h"
#include "Thug.h"

registerInFactory<Agent,Thug> AgentThug("Thug");
Thug::~Thug() = default;


Thug *Thug::createInstance(const std::string &name, const Point  & xy) {
        return new Thug(name, xy);
}

const Point &Thug::getLocation() const {
    return Agent::getLocation();
}

void Thug::update() {

}

void Thug::broadcast_current_state() {
    Point p(getLocation());
    p.x /= 10;
    p.y /= 10;
    switch (_status){
        case STATUS::STOPPED:
            std::cout << "Thug " << getName() << " at " << p << ", Stopped" << std::endl;
            break;
        case STATUS::ONCOURSE:
            std::cout << "Thug " << getName() << " at "<< p << ", Heading on course"<< getCourse() << " deg, speed " << getSpeed() << "km/h" << std::endl;
            break;
        case STATUS::DEAD:
            std::cout << "Thug " << getName() << " at " <<  p << ", Dead" << std::endl;
            break;
        case STATUS::MOVING:
            break;
    }
}

void Thug::course(double degree, double speed) {
    if(speed >= 0 && speed <= 30){
        _status = STATUS::ONCOURSE;
        setCourse(degree);
        setSpeed(speed);
    }else{
        throw Validator("speed most between 0 and 30\n");
    }
}

void Thug::destination(const Point &point, float speed) {

}

void Thug::attack(Peasant *peasant) {

}

void Thug::move_to(const Point &x_y, const string &site, double speed) {
    if(speed == 0){
        setDestination(x_y);
        setSpeed(speed);
        _status = STATUS::MOVING;
        return;
    }
    Agent::move_to(x_y, site, speed);
}

void Thug::reduce_units_by_one() {
    --_power_units;
    Agent::reduce_units_by_one();
}

void Thug::increase_units_by_one() {
    ++_power_units;
    Agent::increase_units_by_one();
}


