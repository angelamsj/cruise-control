#ifndef _CRUISE_CONTROL_H
#define _CRUISE_CONTROL_H

#include <elma.h>
#include <mgl2/mgl.h> 

class CruiseControl : public elma::Process {

    public:

    CruiseControl(std::string name) : Process(name) {}

    void init();
    void start() {}
    void update();
    void stop();

    void set_kp(double kp);
    void set_ki(double ki);
    void set_kd(double kd);

    private:
    
    double _speed = 0.0;
    double _desired_speed = 0.0; 
    double _error = 0.0;
    double _cummulative_error = 0.0;
    double _differential_error = 0.0;
    double _kp;
    double _ki;
    double _kd;
    std::vector<double> _control_signal_log;
    std::vector<double> _velocity_log;
    std::vector<double> _time;

    void update_speed(double velocity);
    double read_velocity();
    void send_control_signal(double control);
    void update_error(); 
    double control_signal();
    double proportional_action();
    double integral_action();
    double derivative_action();
    void log_control_signal(double control);
    void log_velocity(double velocity);
    void print_control_log();
    void plot_control(mglGraph plot); 
    void plot_velocity(mglGraph plot);
    void plot();

};

#endif