#ifndef _CAR_H
#define _CAR_H

#include <elma.h>

#define GRAVITATIONAL_CONSTANT 9.81 // m / s^2
#define ROLLING_FRICCTION_COEFFICIENT 0.01 
#define AIR_DENSITY 1.3 // kg / m^3
#define AERODYNAMIC_DRAG_COEFFICIENT 0.32
#define PI 3.14159265

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
    const double _frontal_area = 2.4; // Frontal area of the car in m^2
    const double _slope = 0.0; // Slope of the road in degrees

    void update_force();
    void update_velocity();
    void send_velocity();
    void print_time_force_velocity();  
    int sgn();
    double rolling_friction_force();
    double car_weight();    
    double distrubance_forces();
    double aerodynamic_drag_force();
    double force_due_to_gravity();
};

#endif