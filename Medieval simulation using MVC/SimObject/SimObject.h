//
// Created by merom on 6/10/2023.
//

#ifndef HOMEWORK3_SIMOBJECT_H
#define HOMEWORK3_SIMOBJECT_H
#include <string>
#include <utility>
#include "../Utilities/Geometry.h"
#include "../Utilities/Validator.h"


class SimObject {

public:
    /*fun's*/
    const std::string & getName() const { return _name;}
    virtual const Point  & getLocation() const = 0;
    virtual void  update() = 0;
    virtual void broadcast_current_state() = 0;


    /*ctr's and dtr's */
    explicit SimObject(std::string  name):_name(std::move(name)){};
    SimObject(const SimObject& rhs) = default;
    SimObject(SimObject&& rhs) = default;

    virtual ~SimObject() = 0;


private:
std::string _name;
};
#endif //HOMEWORK3_SIMOBJECT_H
