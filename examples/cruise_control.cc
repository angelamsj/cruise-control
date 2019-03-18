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
    channel("Throttle").send(calculate_control_signal());
}

int CruiseControl::calculate_error() {
    return _desired_speed - _speed;
}

int CruiseControl::calculate_control_signal() {
    return _kp * calculate_error();
}