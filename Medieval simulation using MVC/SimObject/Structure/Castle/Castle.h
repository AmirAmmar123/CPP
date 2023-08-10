//
// Created by merom on 6/11/2023.
//

#ifndef HOMEWORK3_CASTLE_H
#define HOMEWORK3_CASTLE_H
#include "../Structure.h"
#include "../../../Factory/Structure_factory/factory.h"

class Castle : public Structure{
public:

    Castle(const std::string & castle_name , const Point & p, int init_crate, int rate = 0);

    static Castle * createInstance(const std::string & castle_name , const Point & p, int init_crate, int rate);


    void broadcast_current_state() override;

    const Point &getLocation() const override {
        return Structure::getLocation();
    }


    void update() override {
        /*done nothing*/
    }

};
#endif //HOMEWORK3_CASTLE_H
