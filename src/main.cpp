// hiiiii
#include "main.h"
#include "lemlib/api.hpp"
#include "easy_types.h"
#include "util.h"
#include "ports.hpp"


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
	dt.calibrate();
	pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", dt.getPose().x); // x
            pros::lcd::print(1, "Y: %f", dt.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", dt.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", dt.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
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
 * operator control task wil12l be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

typedef int intake_dirs;
#define intake_off 0
#define intake_in 1
#define intake_out 2

ASSET(sig_red_right_txt);


#define t 999999
void autonomous(){
	// red left side
	// dt.setPose(-64.854, 8.535, 210);
	// pto_piston.set_value(true);
	// pto.move(-127);
	// mogo.set_value(false);
	// dt.moveToPose(-27.537, 21.355, 230, 2000, {false, 8});
	// pto.move(0);
	// mogo.set_value(true);
	// pto_piston.set_value(false);
	// pto.move(-127);
	// intake.move(-127);
	// dt.moveToPose(-22.042, 49.286, 30, 2000, {true, 8, 0.4});
	// dt.turnToPoint(-3.269, 43.334, 500);
	// dt.moveToPoint(-3.269, 43.334, 1000);
	// dt.moveToPose(-15.861, 56.612, 125, 1000, {false, 8});
	// dt.moveToPose(-3.727, 50.66, 180, 1000, {true, 8});
	// dt.moveToPose(-6.023, 18.102, 180, 3000, {true, 8, 1});

	// red right side
	// dt.setPose(-64.854, -29.011, 270);
	// mogo.set_value(false);
	// dt.moveToPose(-2.125, -45.495, 290, 3000, {false, 8});
	// mogo.set_value(true);
	// pto_piston.set_value(false);
	// pto.move(-127);
	// intake.move(-127);
	// dt.moveToPose(-25.311, -48.975, 250, 1000, {true, 8});
	// mogo.set_value(false);
	// dt.moveToPose(-24.119, -23.642, 160, 1000, {false, 8});
	// mogo.set_value(true);

	dt.setPose(0, 0, 0);
	dt.moveToPoint(12, 25, t, {.minSpeed = 80});
	//dt.moveToPoint(0, 25, t);
	//turn
}

void update_intake_dir(pros::Motor* intake, pros::Motor* pto, pros::ADIDigitalOut* pto_piston, intake_dirs dir){
	switch (dir){
		case intake_off:
			intake->move(0);
			pto->move(0);
			break;
		case intake_in:
			intake->move(-127);
			pto_piston->set_value(false);
			pto->move(-127);
			break;
		case intake_out:
			intake->move(127);
			pto_piston->set_value(false);
			pto->move(127);
			break;
	}
}


const ui32 straight_speed = 100;
const ui32 turn_speed = 62;
const ui32 straight_deadzone = 12;
const ui32 turn_deadzone = 12;
#define straight_multiplier (straight_speed * 0.01)
#define turn_multiplier (turn_speed * 0.01)
void opcontrol() {
	Controller controller(E_CONTROLLER_MASTER);
	intake_dirs idir = intake_off;
	int controllerText = 0;
	pto.set_brake_mode(MOTOR_BRAKE_HOLD);
	while (true) {
		i32 straight_joystick = controller.get_analog(ANALOG_LEFT_Y);
		i32 turn_joystick = controller.get_analog(ANALOG_RIGHT_X);
		dt.arcade(straight_multiplier * straight_joystick, turn_multiplier * turn_joystick);

		//intake
		if (controller.get_digital_new_press(DIGITAL_R2) && controller.get_digital_new_press(DIGITAL_R1)){
			pto_piston.set_value(false);
		} else if (controller.get_digital_new_press(DIGITAL_L1) || controller.get_digital_new_press(DIGITAL_L2)){
			pto_piston.set_value(true);
		}
		if (controller.get_digital(DIGITAL_R2)){
			intake.move(-127);
			pto.move(-127);
		} else if (controller.get_digital(DIGITAL_R1)){
			intake.move(127);
			pto.move(127);
		} else {
			intake.move(0);
			pto.move(0);
		}
		//doinker
		if (controller.get_digital_new_press(DIGITAL_A)){
			doinker_status = !doinker_status;
			doinker.set_value(doinker_status);
		}
		//mogo
		if (controller.get_digital_new_press(DIGITAL_B)){
			mogo_status = !mogo_status;
			mogo.set_value(mogo_status);
		}
		//arm
		if (controller.get_digital(DIGITAL_L1)){
			pto.move(127);
		} else if (controller.get_digital(DIGITAL_L2)){
			pto.move(-127);
		} else {
			pto.move(0);
		}
		if (controller.get_digital_new_press(DIGITAL_L1) || controller.get_digital_new_press(DIGITAL_L2)){
			pto_piston.set_value(true);
		}

		/*if (controllerText == 3) {
			lemlib::Pose current = dt.getPose();
			std::string currentString = "X: " + std::to_string((int)current.x) + " Y: " + std::to_string((int)current.y);
			printf(currentString.c_str());
			controller.print(0, 1, currentString.c_str());
			controllerText = 0;
		}
		controllerText += 1;*/
		pros::delay(20);
	}


}

//#include "main.h"
//#include "lemlib/api.hpp"
//#include "easy_types.h"
//#include "util.h"
//#include "ports.hpp"
//
//
///**
// * A callback function for LLEMU's center button.
// *
// * When this callback is fired, it will toggle line 2 of the LCD text between
// * "I was pressed!" and nothing.
// */
//
//
//
//void on_center_button() {
//	static bool pressed = false;
//	pressed = !pressed;
//	if (pressed) {
//		pros::lcd::set_text(2, "I was pressed!");
//	} else {
//		pros::lcd::clear_line(2);
//	}
//}
//
///**
// * Runs initialization code. This occurs as soon as the program is started.
// *
// * All other competition modes are blocked by initialize; it is recommended
// * to keep execution time for this mode under a few seconds.
// */
//void initialize() {
//	pros::lcd::initialize();
//	pros::lcd::set_text(1, "Hello PROS User!");
//	dt.calibrate();
//	pros::Task screenTask([&]() {
//		lemlib::Pose pose(0, 0, 0);
//		while (true) {
//			pros::lcd::print(0, "x: %f", dt.getPose().x);
//			pros::lcd::print(1, "Y: %f", dt.getPose().y);
//			pros::delay(50);
//		}
//	});
//	pros::lcd::register_btn1_cb(on_center_button);
//}
//
///**
// * Runs while the robot is in the disabled state of Field Management System or
// * the VEX Competition Switch, following either autonomous or opcontrol. When
// * the robot is enabled, this task will exit.
// */
//void disabled() {}
//
///**
// * Runs after initialize(), and before autonomous when connected to the Field
// * Management System or the VEX Competition Switch. This is intended for
// * competition-specific initialization routines, such as an autonomous selector
// * on the LCD.
// *
// * This task will exit when the robot is enabled and autonomous or opcontrol
// * starts.
// */
//void competition_initialize() {}
//
//
//
///**
// * Runs the user autonomous code. This function will be started in its own task
// * with the default priority and stack size whenever the robot is enabled via
// * the Field Management System or the VEX Competition Switch in the autonomous
// * mode. Alternatively, this function may be called in initialize or opcontrol
// * for non-competition testing purposes.
// *
// * If the robot is disabled or communications is lost, the autonomous task
// * will be stopped. Re-enabling the robot will restart the task, not re-start it
// * from where it left off.
// */
//
//
///**
// * Runs the operator control code. This function will be started in its own task
// * with the default priority and stack size whenever the robot is enabled via
// * the Field Management System or the VEX Competition Switch in the operator
// * control mode.
// *
// * If no competition control is connected, this function will run immediately
// * following initialize().
// *
// * If the robot is disabled or communications is lost, the
// * operator control task will be stopped. Re-enabling the robot will restart the
// * task, not resume it from where it left off.
// */
//
//typedef int intake_dirs;
//#define intake_off 0
//#define intake_in 1
//#define intake_out 2
//
//void autonomous(){
//	dt.setPose(0, 0, 0);
//	//dt.turnToPoint(0, -10000, 1000);
//	dt.moveToPoint(0, 48, 99999);
//}
//
//
//void update_intake_dir(pros::Motor* intake, pros::Motor* pto, pros::ADIDigitalOut* pto_piston, intake_dirs dir){
//	switch (dir){
//		case intake_off:
//			intake->move(0);
//			pto->move(0);
//			break;
//		case intake_in:
//			intake->move(-127);
//			pto_piston->set_value(false);
//			pto->move(-127);
//			break;
//		case intake_out:
//			intake->move(127);
//			pto_piston->set_value(false);
//			pto->move(127);
//			break;
//	}
//}
//
//
//const ui32 straight_speed = 100;
//const ui32 turn_speed = 62;
//const ui32 straight_deadzone = 12;
//const ui32 turn_deadzone = 12;
//#define straight_multiplier (straight_speed * 0.01)
//#define turn_multiplier (turn_speed * 0.01)
//void opcontrol() {
//	Controller controller(E_CONTROLLER_MASTER);
//	intake_dirs idir = intake_off;
//	int controllerText = 0;
//	while (true) {
//		i32 straight_joystick = controller.get_analog(ANALOG_LEFT_Y);
//		i32 turn_joystick = controller.get_analog(ANALOG_RIGHT_X);
//		dt.arcade(straight_multiplier * straight_joystick, turn_multiplier * turn_joystick);
//		if (controller.get_digital_new_press(DIGITAL_R2)){
//			if (idir == intake_in){
//				idir = intake_off;
//			} else {
//				idir = intake_in;
//			}
//		}
//		if (controller.get_digital_new_press(DIGITAL_R1)){
//			if (idir == intake_out){
//				idir = intake_off;
//			} else {
//				idir = intake_out;
//			}
//		}
//		update_intake_dir(&intake, &pto, &pto_piston, idir);
//		if (controller.get_digital_new_press(DIGITAL_A)){
//			doinker_status = !doinker_status;
//			doinker.set_value(doinker_status);
//		}
//		if (controller.get_digital_new_press(DIGITAL_B)){
//			mogo_status = !mogo_status;
//			mogo.set_value(mogo_status);
//		}
//		if (controller.get_digital(DIGITAL_L1)){
//			pto.move(127);
//		} else if (controller.get_digital(DIGITAL_L2)){
//			pto.move(-127);
//		} else {
//			pto.move(0);
//		}
//		if (controller.get_digital_new_press(DIGITAL_L1) || controller.get_digital_new_press(DIGITAL_L2)){
//			pto_piston.set_value(true);
//		}
//
//		if (controllerText == 3) {
//			lemlib::Pose current = dt.getPose();
//			std::string currentString = "X: " + std::to_string((int)current.x) + " Y: " + std::to_string((int)current.y);
//			printf(currentString.c_str());
//			controller.print(0, 1, currentString.c_str());
//			controllerText = 0;
//		}
//		controllerText += 1;
//		pros::delay(20);
//	}
//
//
//}
//*/