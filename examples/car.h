#ifndef _CAR_H
#define _CAR_H

#include <elma.h>

class Car : public elma::Process {

    public:

    Car(std::string name) : elma::Process(name) {}

    void init() {}    
    void start();
    void update();
    void stop(); 

    private:
    
    double _velocity;
    double _force;
    const double _mass = 1000; // Weight of the car in kg
    // TO-DO
    const double _k = 0.02; // ??? 

    void update_force();
    void update_velocity();
    void send_velocity();
    void print_time_velocity();
};

#endif