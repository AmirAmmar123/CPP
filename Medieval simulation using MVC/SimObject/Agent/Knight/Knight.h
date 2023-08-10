//
// Created by merom on 6/11/2023.
//

#ifndef HOMEWORK3_KNIGHT_H
#define HOMEWORK3_KNIGHT_H

#include "../Agent.h"
#include <map>


class Knight : public Agent{
public:
    /*Knight ctr's with const speed 10 km/h*/
    Knight(const std::string & name, const Point & xy );

    static Knight * createInstance(const std::string & name, const Point & xy );
    ~Knight() override;

    void move_to(const Point &x_y, const std::string & site , double speed) override;

    void  course(double degrees);

    void autoPilotCommand(const Point &x_y, const std::string & site);
public:
    const Point &getLocation() const override;

    void update() override;

    void broadcast_current_state() override;

    void setAutoPilot(){ autopilot = true;}

    void cancelAutoPilot(){ autopilot = false;}

    bool getPilotMode() const {return autopilot;}

    bool & getPhysicsDone(){return _physics.done;}

    const std::string & getSpoonCastle()const{return knight_spoon_castle;}

    void setSpoonCast(const std::string & castle){ knight_spoon_castle = castle;}

    const std::string & getCityDestination() const {return city_destination;}


private:
    bool autopilot;
    std::string knight_spoon_castle;
    std::string city_destination;

};
#endif //HOMEWORK3_KNIGHT_H
