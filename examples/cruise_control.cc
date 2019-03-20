#include "elma.h"
#include "cruise_control.h"
#include <mgl2/mgl.h> 
#include <iostream>

using namespace std;
using namespace elma;

void CruiseControl::init() {
    watch("desired speed", [this](Event& e) {
        _desired_speed = e.value();
    });
}

void CruiseControl::update() {
    double velocity = read_velocity();
    update_speed(velocity);
    log_velocity(velocity);
    update_error();
    double control = control_signal();
    send_control_signal(control);
    log_control_signal(control);
    _time.push_back(milli_time());
}

void CruiseControl::stop() {
    //cout << "Control samples = " << _control_signal_log.size();
    //cout << " Velociy samples = " << _velocity_log.size();
    //cout << " Time samples = " << _time.size() << endl;
    plot();
}

void CruiseControl::set_kp(double kp) {
    _kp = kp;
}

void CruiseControl::set_ki(double ki) {
    _ki = ki;
}

void CruiseControl::set_kd(double kd) {
    _kd = kd;
}

void CruiseControl::update_speed(double velocity) {
    _speed = velocity;
}

double CruiseControl::read_velocity() {
    double velocity = 0;
    if (channel("Velocity").nonempty()) {
        velocity = channel("Velocity").latest();
    }
    return velocity;
}

void CruiseControl::log_velocity(double velocity) {
    _velocity_log.push_back(velocity);
}

void CruiseControl::send_control_signal(double control) {
    channel("Throttle").send(control);
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

void CruiseControl::log_control_signal(double control) {
    _control_signal_log.push_back(control);
}

void CruiseControl::print_control_log() {
    for (double control : _control_signal_log) {
        cout << control << endl;
    }
}

void CruiseControl::plot_control(mglGraph plot) {
    mglData control_data;
    control_data.Set(_control_signal_log);
    plot.SubPlot(2,1,0);
    plot.Title("Control signal");
    plot.SetRanges(0,150,-2500,6000);
    plot.Axis();
    plot.Label('x', "Time [s]", 0);
    plot.Label('y', "Force [N]", 0);
    plot.Plot(control_data);
}

void CruiseControl::plot_velocity(mglGraph plot) {
    mglData velocity_data;
    velocity_data.Set(_velocity_log);
    plot.SubPlot(2,1,1);
    plot.Title("Velocity");
    plot.SetRanges(0,150,0,80);
    plot.Axis();
    plot.Label('x', "Time [s]", 0);
    plot.Label('y', "Velocity [m/s]", 0);
    plot.Plot(velocity_data);
}

void CruiseControl::plot() {
    mglGraph plot(0,1400,750);
    //mglData time_span;
    //time_span.Set(_time);
    plot_control(plot);
    plot_velocity(plot);  
    plot.WritePNG("CruiseControl.png");
}






