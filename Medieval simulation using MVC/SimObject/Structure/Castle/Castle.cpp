//
// Created by merom on 6/21/2023.
//
#include "Castle.h"
registerInFactory2<Structure,Castle> castle("Castle");

Castle::Castle(const std::string &castle_name, const Point &p, int init_crate, int rate): Structure(castle_name, p,init_crate){}

Castle *Castle::createInstance(const string &castle_name, const Point &p, int init_crate, int rate) {
    return new Castle(castle_name, {p}, init_crate);
}

void Castle::broadcast_current_state() {
    {
        Point p = getLocation();
        p.x/=10;
        p.y/=10;
        std::cout << "Castle " << getName() << " at position " << p << ", Inventory: " << _invy_crate << std::endl;
    }
}

