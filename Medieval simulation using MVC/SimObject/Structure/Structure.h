//
// Created by merom on 6/10/2023.
//

#ifndef HOMEWORK3_STRUCTURE_H
#define HOMEWORK3_STRUCTURE_H
#include "../SimObject.h"

class Structure : public SimObject {
protected:
    Structure(const std::string &name, const Point & p,int initial_inventory = 0): SimObject(name),_p(p.x*10,p.y*10),_invy_crate(initial_inventory){}
public:
    const Point &getLocation() const override {
        return _p;
    }

public:
    int  withdraw(int amount){
        if(_invy_crate >= amount ) {
            _invy_crate -= amount;
            return amount;
        }
        else if(amount <= _invy_crate && _invy_crate > 0){
            int temp = _invy_crate;
            _invy_crate = 0;
            return  temp ;
        }
        else{  // (_invy_crate == 0 || amount < 0)
            if(_invy_crate == 0){
                std::cout << "crates are empty"<< std::endl;
                return  0;
            }
        }
        return -1;
    }

    void  deposit(int crates){
        if(crates > 0){_invy_crate += crates;}
        else{throw Validator("Negative number of crates " + std::to_string(crates));}
    }

protected:
    const Point _p;
    int _invy_crate{};


};
#endif //HOMEWORK3_STRUCTURE_H
