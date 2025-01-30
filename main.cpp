
#include "main.h"
#include "autons.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"


  // left motor group
pros::MotorGroup left_motor_group({-1, 2, -3}, pros::MotorGears::blue);
// right motor group
pros::MotorGroup right_motor_group({20, -5, 4}, pros::MotorGears::blue);

// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              13.5, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              600, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

// imu
pros::Imu imu(19);


// odometry settings //inertial sensor
lemlib::OdomSensors sensors(imu);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain,
                        lateral_controller,
                        angular_controller,
                        sensors);

// initialize function. Runs on program startup
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(20);
pros::adi::DigitalOut piston1('H'); // Replace 'A' with the port of the first piston
pros::adi::DigitalOut piston2('H'); // Replace 'B' with the port of the second piston
pros::adi::DigitalOut doinker('C'); // Replace 'C' with the port of the doinker piston
             piston1.set_value(false);
             piston2.set_value(false);
             doinker.set_value(false);

             
}
        });
    
};

pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Controller master(pros::E_CONTROLLER_MASTER);
void opcontrol() {
    // loop forever
    while (true) {
        // get left y and right x positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int leftX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

        // move the robot
        // prioritize steering slightly
        chassis.arcade(leftY, leftX, false, 0.75);

        // delay to save resources
        pros::delay(25);



// input curve for throttle input during driver control TUNE THIS WITH TESTING
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control TUNE THIS WITH TESTING
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain,
                        lateral_controller,
                        angular_controller,
                        sensors,
                        &steer_curve,
                        &throttle_curve

);



        


//PISTONS


if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    pros::adi::DigitalOut piston1('H');
    pros::adi::DigitalOut piston2('H');
            piston1.set_value(true); // Extend piston 1
            piston2.set_value(true); // Extend piston 2
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            pros::adi::DigitalOut piston1('H');
    pros::adi::DigitalOut piston2('H');
            piston1.set_value(false); // Retract piston 1
            piston2.set_value(false); // Retract piston 2
        }

        // Control for 1-piston doinker mechanism

        pros::adi::DigitalOut doinker('C');
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            doinker.set_value(true); // Extend the doinker
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            doinker.set_value(false); // Retract the doinker
        }




{
pros::Motor intakeMotor(1); // intake port 1
// Intake forward when Button R1 is pressed
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            intakeMotor.move(127); // Full power forward
        }
        // Intake reverse when Button R2 is pressed
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            intakeMotor.move(-127); // Full power reverse
        }
        // Stop intake when no button is pressed
        else {
            intakeMotor.move(0); // Stop the motor
        }

        pros::delay(20); // Delay to prevent CPU overload
    }
    
}

}


//autonomous selector  add autons routines here
//have to put void autonomous (replace with autonomous function name) () {
	//selector.run_auton();
//}
rd::Selector selector({
    {"Best auton", bestauton},
    {"Simple auton", simpleauton},
    {"Good auton", good},
});






