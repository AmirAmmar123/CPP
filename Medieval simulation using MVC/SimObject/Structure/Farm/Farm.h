//
// Created by merom on 6/11/2023.
//

#ifndef HOMEWORK3_FARM_H
#define HOMEWORK3_FARM_H

#include "../../Structure/Structure.h"
#include "../../../Factory/Structure_factory/factory.h"

class Farm : public Structure{

public:
    Farm(const std::string & farm_name , const Point & p, int init_crate, int rate);

    static Farm * createInstance(const std::string & farm_name , const Point & p, int init_crate, int rate);

    void broadcast_current_state() override;

    void update() override {
        _invy_crate+=_rate;
    }


private:
    int _rate;

};



#endif //HOMEWORK3_FARM_H
