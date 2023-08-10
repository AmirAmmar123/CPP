//
// Created by merom on 6/17/2023.
//
#include "../../../Factory/agent_factory/factory.h"
#include "Knight.h"

registerInFactory<Agent,Knight> AgentKnight("Knight");

Knight::~Knight() = default;
Knight::Knight(const string &name, const Point &xy) : Agent(name, xy, 100, 10), autopilot(true){
    _status = STATUS::MOVING;
    _physics.done = true;

}

Knight *Knight::createInstance(const std::string &name,const Point & xy  ) {
    return new Knight(name, xy);
}


void Knight::broadcast_current_state() {
    Point p(getLocation());
    p.x /= 10;
    p.y /= 10;
    switch (_status){
        case STATUS::STOPPED:
            std::cout << "Knight " << getName() << " at " << p << ", Stopped" << std::endl;
            break;
        case STATUS::MOVING:
            std::cout << "Knight " << getName() << " at " << p << ", Heading to " << city_destination << std::endl;
            break;
        case STATUS::ONCOURSE:
            std::cout << "Knight " << getName() << " at " << p << ", Heading on course"<< getCourse() << " deg, speed " << getSpeed() << "km/h" << std::endl;
            break;
        case STATUS::DEAD:
            /* Knight can't die */
            break;
    }
}



const Point &Knight::getLocation() const {
    return Agent::getLocation();
}


/*
 *  double time{};
    double time_passed{};
    double time_remaind{};
    double distance{};
    double current_x{};
    double current_y{};
    bool done{};
 * */
void Knight::update() {
        /*Knight is moving on command pilot mode or on a command
         *he can */
        if(_status == STATUS::MOVING && !_physics.done){
            _physics.time_passed++;
             /*
              fractional time = time_passed/time
              interpolate x = x_start * (fractional_time ) * (x_finish - x_start)
              interpolate y = y_start * (fractional_time ) * (y_finish - y_start)
             */
             if(_physics.time_passed/_physics.time >= 1){
                 _physics.done = true;
                 /* the next step is going to be inside the site so we set the current location to be the destination*/
                 setLocation(getDestination());
                 /*once the knight is done, set Stopped again
                  * he will receive command by the autopilot
                  * */
                 halt();
                 return;
             }else{
                 calculateNextStep();
                 return;
             }
        }else if(_status == STATUS::STOPPED){
            _physics.done = true; //
            setAutoPilot(); // once knight is stopped, step for one hour, next move as an autopilot
            return;
        }else if (_status == STATUS::ONCOURSE){
            calculateNextStepOncourse();
            return;
        }


}



/*
 *
 * using Physics = struct Physics {
    double time{};
    double time_passed{};
    double time_remaind{};
    double distance{};
    double current_x{};
    double current_y{};
    double x_start{};
    double y_start{};
    double x_finish{};
    double y_finish{};
};
 * Knight getting a command to move by user
 * */
void Knight::move_to(const Point &x_y,const std::string & site, double speed) {
    if(speed == 0) {halt(); return;} // if speed is 0, in other words, stop
    cancelAutoPilot(); // cancel the autopilot mode, so once knight is updated he will not be ordered to go to the closest place by controller
    auto & current_location = getLocation();

    setDestination(x_y);

    Cartesian_vector cart_vec;
    cart_vec.delta_x = current_location.x - x_y.x;
    cart_vec.delta_y = current_location.y - x_y.y;
    Polar_vector polar(cart_vec);

    /* in moving object will be updated to radians;
     * however, this is not critical for the next steps down by the knight*/
    setCourse(to_degrees(polar.theta));
    Agent::move_to(x_y,site,getSpeed());


    city_destination = site;
    _physics.distance = polar.r;
    _physics.time = _physics.distance/getSpeed();
    _physics.x_start = getLocation().x;
    _physics.y_start = getLocation().y;
    _physics.done = false; // the knight is moving some location, it will be canceled
    _physics.x_finish = x_y.x;
    _physics.y_finish = x_y.y;
}

/*
* Knight getting a command to move by him self
* */
void Knight::autoPilotCommand(const Point &x_y, const string &site) {
    setAutoPilot();
    auto & current_location = getLocation();
    setDestination(x_y);
    Cartesian_vector cart_vec;
    cart_vec.delta_x = current_location.x - x_y.x;
    cart_vec.delta_y = current_location.y - x_y.y;
    Polar_vector polar(cart_vec);

    /* in moving object will be updated to radians */
    setCourse(to_degrees(polar.theta));
    Agent::move_to(x_y,site,getSpeed());

    city_destination = site;
    _physics.distance = polar.r;
    _physics.time = _physics.distance/getSpeed();
    _physics.x_start = getLocation().x;
    _physics.y_start = getLocation().y;
    _physics.done = false;
    _physics.x_finish = x_y.x;
    _physics.y_finish = x_y.y;

}


void Knight::course(degree degrees) {
    _status = STATUS::ONCOURSE;
    setCourse(degrees);
}





