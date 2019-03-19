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
    double _error = 0.0;
    double _cummulative_error = 0.0;
    double _differential_error = 0.0;
    const double _kp = 450;
    const double _ki = 45;
    const double _kd = 5;


    //std::vector<double> _v;

    void update_speed();
    void send_control_signal();
    void update_error(); 
    double control_signal();
    double proportional_action();
    double integral_action();
    double derivative_action();

};

#endif