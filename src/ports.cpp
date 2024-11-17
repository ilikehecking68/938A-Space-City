#include "ports.hpp"
using namespace pros;
using namespace lemlib;

MotorGroup left_dt({11, -12, -23});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
MotorGroup right_dt({-18, -19, 20});  // Creates a motor group with forwards port 5 and reversed ports 4 & 6

//Initializing Odom Sensors
IMU imu(15);
<<<<<<< HEAD
Rotation odom_side_sensor(16);
=======
Rotation odom_side_sensor(17);
>>>>>>> 9cf3fc6 (sfsafsadf)

//Config. Tracking Wheels
TrackingWheel odom_side(&odom_side_sensor, 2, 0, 1);
OdomSensors sensors(nullptr, nullptr, &odom_side, nullptr, &imu);

Drivetrain dt_combo(&left_dt, &right_dt, 12.8125, Omniwheel::NEW_325, 450, 2);

//i didnt tune this one
ControllerSettings pid_straight_cont(5, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);
//4, 29 (the last one that also worked)
ControllerSettings pid_turn_cont(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

Chassis dt(dt_combo, pid_straight_cont, pid_turn_cont, sensors);

Motor intake(21);
Motor pto(14);
ADIDigitalOut pto_piston(1, false);
bool doinker_status = false;
ADIDigitalOut doinker(3, doinker_status);
bool mogo_status = true;
ADIDigitalOut mogo(2, mogo_status);

//#include "ports.hpp"
//
//using namespace pros;
//using namespace lemlib;
//
//MotorGroup left_dt({-12, -11, 15});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
//MotorGroup right_dt({17, 20, -16});  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
//
////Initializing Odom Sensors
//IMU imu(13);
//Rotation odom_side_sensor(18);
//
////Config. Tracking Wheels
//TrackingWheel odom_side(&odom_side_sensor, 2, 0, 1);
//OdomSensors sensors(nullptr, nullptr, &odom_side, nullptr, &imu);
//
//Drivetrain dt_combo(&left_dt, &right_dt, 12.8125, Omniwheel::NEW_325, 450, 2);
//
//ControllerSettings pid_straight_cont(8, // proportional gain (kP)
//                                              0, // integral gain (kI)
//                                              5, // derivative gain (kD)
//                                              3, // anti windup
//                                              1, // small error range, in degrees
//                                              100, // small error range timeout, in milliseconds
//                                              3, // large error range, in degrees
//                                              500, // large error range timeout, in milliseconds
//                                              20 // maximum acceleration (slew)
//);
//
//ControllerSettings pid_turn_cont(2, // proportional gain (kP)
//                                              0, // integral gain (kI)
//                                              11, // derivative gain (kD)
//                                              3, // anti windup
//                                              1, // small error range, in degrees
//                                              100, // small error range timeout, in milliseconds
//                                              3, // large error range, in degrees
//                                              500, // large error range timeout, in milliseconds
//                                              0 // maximum acceleration (slew)
//);
//
//
//Chassis dt(dt_combo, pid_straight_cont, pid_turn_cont, sensors);
//
//Motor intake(21);
//Motor pto(14);
//ADIDigitalOut pto_piston(1, false);
//bool doinker_status = false;
//ADIDigitalOut doinker(3, doinker_status);
//bool mogo_status = true;
//ADIDigitalOut mogo(2, mogo_status);
