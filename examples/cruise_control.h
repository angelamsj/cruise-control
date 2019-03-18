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
    double _error_integral = 0.0;
    double _previous_error = 0.0;
    const double _kp = 700;
    const double _ki = 50;
    const double _kd = 12.5;


    //std::vector<double> _v;

    void update_speed();
    void send_control_signal();
    void update_error(); 
    double control_signal();
    double proportional_action();
    double integral_action();
    void integrate_error();
    double derivative_action();
    double error_derivative();

};

#endif