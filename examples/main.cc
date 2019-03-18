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
    Driver driver("Steve");
    Channel throttle("Throttle");
    Channel velocity("Velocity");

    m.schedule(car, 100_ms)
    .schedule(cc, 100_ms)
    .schedule(driver, 15_s)
    .add_channel(throttle)
    .add_channel(velocity)
    .init()
    .run(120_s);

}
