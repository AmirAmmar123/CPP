//
// Created by merom on 6/11/2023.
//

#ifndef HOMEWORK3_THUG_H
#define HOMEWORK3_THUG_H
#include "../Agent.h"
#include "../Peasent/Peasant.h"
class Thug : public Agent{


public:
    /*
     * init power units of the thug as 5 units
     *
     * */
    Thug(const std::string & name, const Point & xy): Agent(name, xy){
        _status = STATUS::STOPPED;
    };
    static Thug * createInstance(const std::string & name, const Point & xy);
    ~Thug() override;

    const Point &getLocation() const override;

    void update() override;

    void broadcast_current_state() override;

    /*speed of the thug is set{ speed : 0 <= speed <= 30}*/
    void course(double degree, double speed);

    void destination(const Point & point, float speed) ;

    void move_to(const Point &x_y, const std::string & site , double speed) override;

    /* attack a peasant if:
     *    1: the farmer is within one k'm radius from thug
     *    2: the power units of the thug are greater than farmer power unit
     *    3: there is no Knight in 2.5 k'm radius around the thug
     * */

    /*
     *  Agent Peasant cases:
     *    1: successful attack on the peasant:
     *        a: causing him losing one unit power => health --
     *        b: causing him to lose all crates
     *        c: change status from moving to Stopped
     *    2: unsuccessful attacks:
     *        the peasant continues with command regularly like nothing happened
     *
     *  Agent Thug cases:
     *        a: whether it's a successful attack or not halt (status = STOPPED!!!)
     *        b: successful attack =>  power_units+=1
     *        c: unsuccessful attack =>  power_units-=1
     *
     *  Both Agents cases:
     *       a: if health/power_units == 0 then status is DEAD!!!
     *
     *  Agent Knight:
     *      not around do nothing
     * */

    void attack(Peasant * peasant);

    void reduce_units_by_one() override;

    void increase_units_by_one() override;

private:
    /* set{ _pow_units : _pow_units in [5, 20] }*/
};
#endif //HOMEWORK3_THUG_H
