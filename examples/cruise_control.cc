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
    _previous_error = _error;
    _error = _desired_speed - _speed;
}

double CruiseControl::control_signal() {
    return proportional_action() + integral_action() + derivative_action();
}

double CruiseControl::proportional_action() {
    return _kp * _error;
}

double CruiseControl::integral_action() {
    return _ki *_error_integral;
}

void CruiseControl::integrate_error() {
    _error_integral += _error * delta() / 1000;
}

double CruiseControl::derivative_action() {
    return _kd * error_derivative();
}

double CruiseControl::error_derivative() {
    return (_error - _previous_error) * (delta() / 1000);
}



