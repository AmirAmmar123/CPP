//
// Created by merom on 6/21/2023.
//
#include "Farm.h"

registerInFactory2<Structure,Farm> farm("Farm");

Farm::Farm(const string &farm_name, const Point &p, int init_crate, int rate) : Structure(farm_name, p,init_crate), _rate(rate){}

Farm *Farm::createInstance(const string &farm_name, const Point &p, int init_crate, int rate) {
    return new Farm(farm_name, p, init_crate, rate);
}

void Farm::broadcast_current_state() {
    Point p = getLocation();
    p.x/=10;
    p.y/=10;
    std::cout << "Farm " << getName() << " at position " << p << ", Inventory: " << _invy_crate << std::endl;
}

