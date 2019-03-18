#include "elma.h"
#include "driver.h"

using namespace elma;

void Driver::init() {
    _desired_speed = 50;
}

void Driver::update() {
    update_desired_speed();
    send_desired_speed();
}

void Driver::update_desired_speed() {
    if (_desired_speed == 50) {
        _desired_speed = 70;
    } else {
        _desired_speed = 50;       
    }
}

void Driver::send_desired_speed() {
    emit(Event("desired speed", _desired_speed));
}
 