#include <iostream>
#include <chrono>
#include "elma.h"
#include "car.h"
#include "driver.h"
#include "cruise_control.h"

//! \file

using namespace std::chrono;
using namespace elma;

int main() {

    Manager m;
    Car car("Car");
    CruiseControl cc("Control");
    cc.set_kp(100);
    cc.set_ki(2);
    cc.set_kd(0.5);
    Driver driver("Steve");
    Channel throttle("Throttle");
    Channel velocity("Velocity");

    m.schedule(car, 250_ms)
    .schedule(cc, 250_ms)
    .schedule(driver, 30_s)
    .add_channel(throttle)
    .add_channel(velocity)
    .init()
    .run(150_s);

}
