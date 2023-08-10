//
// Created by merom on 6/17/2023.
//

#ifndef HOMEWORK3_MOVINGOBJECT_H
#define HOMEWORK3_MOVINGOBJECT_H
#include <string>
#include <tuple>
#include <utility>
#include "../Utilities/Geometry.h"

struct Point;

class MovableObject {
public:

    MovableObject()=default;
    ~MovableObject()=default;
    MovableObject(Point  location, Point destination,double speed,double course);
    MovableObject(const MovableObject & rhs)=default;
    MovableObject & operator=(const MovableObject & rhs)=default;


public:
    double getSpeed() const ;
    void setSpeed(double speed);

    double getCourse() const ;
    void setCourse(double course);

    const Point &getDestination() const;

    void setDestination(const Point &destination);

    void setLocation(const Point &location);

    const Point &getLocation() const;



protected:
    Point _location;
    Point _destanation;
    double _speed{};
    double _course{};
};
#endif //HOMEWORK3_MOVINGOBJECT_H
