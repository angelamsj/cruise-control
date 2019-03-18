#include <iostream>
#include "elma.h"
#include "car.h"

using namespace std;

void Car::start() {
    _velocity = 0;
    _force = 0;
}

void Car::update() {
    update_force();
    update_velocity();
    send_velocity();
    print_time_velocity();
}

void Car::stop() {
    _velocity = 0;
    _force = 0;
} 

void Car::update_force() {
    if (channel("Throttle").nonempty()) {
        _force = channel("Throttle").latest();
    }
}

void Car::update_velocity() {
    _velocity += (delta() / 1000) * (-_k * _velocity + _force) / _mass;
}

void Car::send_velocity() {
    channel("Velocity").send(_velocity);
}

void Car::print_time_velocity() {
    cout << "time: " << milli_time() << " ms, ";
    cout << "velocity: " << _velocity << " m/s." << endl;
}