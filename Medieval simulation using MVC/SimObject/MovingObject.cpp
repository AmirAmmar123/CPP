//
// Created by merom on 6/21/2023.
//
#include "MovingObject.h"


MovableObject::MovableObject(Point location, Point destination, double speed, double course)
:_location(location),_destanation(destination),_speed(speed),_course(course){}

double MovableObject::getSpeed() const {
    return _speed;
}

void MovableObject::setSpeed(double speed) {_speed = speed;}

double MovableObject::getCourse() const {return to_degrees(_course);}

void MovableObject::setCourse(double course) {_course = to_radians(course);}

const Point &MovableObject::getDestination() const {return _destanation;}

void MovableObject::setDestination(const Point &destination){_destanation = destination;}

void MovableObject::setLocation(const Point &location) { _location = location;}

const Point &MovableObject::getLocation() const{return _location;}

