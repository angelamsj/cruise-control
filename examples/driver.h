#ifndef _DRIVER_H
#define _DRIVER_H

#include <elma.h>

class Driver : public elma::Process {

    public:

    Driver(std::string name) : Process(name) {}

    void init();
    void start() {}
    void update();
    void stop() {} 

    private:

    double _desired_speed;

    void update_desired_speed();
    void send_desired_speed(); 

};

#endif