#ifndef PORTS_HPP
#define PORTS_HPP

#include "lemlib/api.hpp"

using namespace pros;
using namespace lemlib;

extern MotorGroup left_dt;    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
extern MotorGroup right_dt;  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
extern IMU imu;
extern Drivetrain dt_combo;
extern ControllerSettings pid_straight_cont;
extern ControllerSettings pid_turn_cont;
extern OdomSensors sensors;
extern Chassis dt;
extern Motor intake;
extern Motor pto;
extern ADIDigitalOut pto_piston;
extern bool doinker_status;
extern ADIDigitalOut doinker;
extern bool mogo_status;
extern ADIDigitalOut mogo;

#endif