//
// Created by merom on 6/11/2023.
//

#ifndef HOMEWORK3_AGENT_H
#define HOMEWORK3_AGENT_H

#include "../SimObject.h"
#include "../MovingObject.h"
#define eps .2

enum class STATUS{DEAD,STOPPED,MOVING, ONCOURSE};

class Agent : public SimObject, private MovableObject{

public:
    /* ctr's and dtr's */
    Agent(const std::string &name, const Point & coordinates, int power_units = 0, double speed = 0);
    ~ Agent() override = default;

    /* fun's */
    virtual void  move_to( const Point & x_y,const std::string & site, double speed);

    /* assign move_to_target_location with location and update status to "Heading on course <destination position>"*/
    void position(const Point & coordinates);


    /* Halt agent activity, and location_targets update status for stopped    */
    void halt();


    bool isDead();

    int getPowerUnits() const;

    /* Private inheritance from MovableObject
    * Agent has a movable object*/
    using MovableObject::getLocation;
    using MovableObject::getSpeed;
    using MovableObject::setSpeed;
    using MovableObject::setLocation;
    using MovableObject::setDestination;
    using MovableObject::setCourse;
    using MovableObject::getCourse;
    using MovableObject::getDestination;


public:

    const Point  & getLocation() const override {
        return MovableObject::getLocation();
    }

    void update() override {

    }

    void move() {
        _status = STATUS::MOVING;
    }


    using Physics = struct Physics {
        double distance{};
        double time_passed{};
        double time{};
        bool done{};
        double x_start{};
        double y_start{};
        double x_finish{};
        double y_finish{};


    };


    virtual void reduce_units_by_one();

    virtual void increase_units_by_one();
protected:
    void calculateNextStep();
    void calculateNextStepOncourse();
protected:
    Physics _physics;
    STATUS _status;
    int _power_units ; // health for the peasant



};




#endif //HOMEWORK3_AGENT_H
