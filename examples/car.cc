#include <iostream>
#include <cmath>
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
    print_time_force_velocity();
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
    _velocity += (delta() / 1000) * (_force - distrubance_forces()) / _mass;
}

void Car::send_velocity() {
    channel("Velocity").send(_velocity);
}

void Car::print_time_force_velocity() {
    cout << "t: " << milli_time() << " ms, \t";
    cout << "f: " << _force << " N, \t";
    cout << "v: " << _velocity << " m/s." << endl;
}

int Car::sgn() {
    if (_velocity < 0) {
        return -1;
    } else if (_velocity > 0) {
        return 1;
    } else {
        return 0;
    }
}

double Car::rolling_friction_force() {
    return car_weight() * ROLLING_FRICCTION_COEFFICIENT * sgn();
}

double Car::car_weight() {
    return _mass * GRAVITATIONAL_CONSTANT;
}

double Car::distrubance_forces() {
    return force_due_to_gravity() + rolling_friction_force() + aerodynamic_drag_force();
}

double Car::aerodynamic_drag_force() {
    double velocity_sq = _velocity * _velocity;
    return 0.5 * AIR_DENSITY * AERODYNAMIC_DRAG_COEFFICIENT * _frontal_area * velocity_sq;
}

double Car::force_due_to_gravity() {
    return car_weight() * sin(_slope * PI / 180.0);
}