#include "main.h"
#include "lemlib/api.hpp"
#include "easy_types.h"
#include "util.h"

using namespace pros;
using namespace lemlib;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */



void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

const ui32 straight_speed = 100;
const ui32 turn_speed = 100;
const ui32 straight_deadzone = 12;
const ui32 turn_deadzone = 12;
const ui32 accel_limit = 150;
const ui32 deccel_speed = 20;
#define straight_multiplier (straight_speed * 0.01)
#define turn_multiplier (turn_speed * 0.01)
#define deccel_multiplier (1 - deccel_speed * 0.01)
void opcontrol() {
	Controller controller(pros::E_CONTROLLER_MASTER);
	MotorGroup left_dt({-12, 11, -13});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	MotorGroup right_dt({19, -20, 9});  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
	Motor intake(18);
	Motor pto(21);
	ADIDigitalOut pto_piston(1, false);
	d64 t = 0;

	while (true) {
		i32 straight_joystick = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		i32 turn_joystick = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
		t = (fabs(straight_joystick) >= straight_deadzone || fabs(turn_joystick) >= turn_deadzone) ? LIMITED_ADDITION(t, 1, 222) : LIMITED_SUBTRACTION(t, 1, 0);
		i32 power_multiplier = pow(RANGE(t, 0, 222) / 222, 2);
		i32 straight_power =  power_multiplier * straight_joystick;
		i32 turn_power = power_multiplier * turn_joystick;
		right_dt.move( straight_multiplier * straight_power - turn_multiplier * turn_power);
		left_dt.move(straight_multiplier * straight_power + turn_multiplier * turn_power);
	}
}