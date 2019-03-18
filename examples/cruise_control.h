#ifndef _CRUISE_CONTROL_H
#define _CRUISE_CONTROL_H

#include <elma.h>

class CruiseControl : public elma::Process {

    public:

    CruiseControl(std::string name) : Process(name) {}

    void init();
    void start() {}
    void update();
    void stop() {}

    //void set_kp(int kp);

    private:
    
    double _speed = 0.0;
    double _desired_speed = 0.0;
    const double _kp = 314.15;
    //std::vector<double> _v;

    void update_speed();
    void send_control_signal();
    int calculate_error(); 
    int calculate_control_signal();

};

#endif