#include "elma.h"
#include "cruise_control.h"

using namespace std;
using namespace elma;

void CruiseControl::init() {
    watch("desired speed", [this](Event& e) {
        _desired_speed = e.value();
    });
}

void CruiseControl::update() {
    update_speed();
    update_error();
    send_control_signal();
}

//void CruiseControl::set_kp(int kp) {
//    _kp = kp;
//}

void CruiseControl::update_speed() {
    if (channel("Velocity").nonempty()) {
        _speed = channel("Velocity").latest();
    }
}

void CruiseControl::send_control_signal() {
    channel("Throttle").send(control_signal());
}

void CruiseControl::update_error() {
    double previous_error = _error;
    _error = _desired_speed - _speed;
    _cummulative_error += _error;
    _differential_error = _error - previous_error;
}

double CruiseControl::control_signal() {
    return proportional_action() + integral_action() + derivative_action();
}

double CruiseControl::proportional_action() {
    return _kp * _error;
}

double CruiseControl::integral_action() {
    return _ki *_cummulative_error;
}

double CruiseControl::derivative_action() {
    return _kd * _differential_error;
}





