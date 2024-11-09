#include "stdio.h"
#include "vex.h"
#include <math.h>
#include <iostream>
#include <odometry.h>

/*
	 ██████╗   ██████╗    ██████╗   ███╗   ███╗  ███████╗  ████████╗  ███████╗  ██████╗   ██╗   ██╗
	██╔═══██╗  ██╔══██╗  ██╔═══██╗  ████╗ ████║  ██╔════╝  ╚══██╔══╝  ██╔════╝  ██╔══██╗  ╚██╗ ██╔╝
	██║   ██║  ██║  ██║  ██║   ██║  ██╔████╔██║  █████╗       ██║     █████╗    ██████╔╝   ╚████╔╝
	██║   ██║  ██║  ██║  ██║   ██║  ██║╚██╔╝██║  ██╔══╝       ██║     ██╔══╝    ██╔══██╗    ╚██╔╝
	╚██████╔╝  ██████╔╝  ╚██████╔╝  ██║ ╚═╝ ██║  ███████╗     ██║     ███████╗  ██║  ██║     ██║
	 ╚═════╝   ╚═════╝    ╚═════╝   ╚═╝     ╚═╝  ╚══════╝     ╚═╝     ╚══════╝  ╚═╝  ╚═╝     ╚═╝

*/

point robot = point(0, 0);

#include <string>

int drivePID(float target, float accuracy = 1);
int PIDturn(float target, float accuracy = 1);

void point::print()
{
	std::cout << x << "," << y << std::endl;
}

float round(float var)
{
	float value = (int)(var * 100 + .5);
	return (float)value / 100;
}

bool point::equals(point p1)
{
	if ((round(this->x) == round(p1.x)) and (round(this->y) == round(p1.y)))
	{
		return true;
	}
	return false;
}


/**
 * @brief odometry
 */
int odometery()
{
	rightFwd.resetPosition();
	leftFwd.resetPosition();
	gyro4.resetHeading();

	double prevHeading = gyro4.rotation();

	double deltaHeading = 0; // change in heading
	double Heading = M_PI;
	double distFromCenterL = 6;
	double distFromCenterB = 5;
	double lRad = 1.625;
	double rRad = 1.625; // radius of tracking wheel
	double bRad = 1.625; // radius of tracking wheel

	// radius of tracking wheel
	double lEncoder = 0; // declaring encoder variable left
	double rEncoder = 0; // declaring encoder variable right
	double bEncoder = 0; // declaring encoder variable right

	double distL = 0; // distance left encoder has traveled
	double distR = 0; // distance right encoder has traveled
	double distB = 0;

	double prevLE = lEncoder; // create previous encoder value left
	double prevRE = rEncoder; // create previous encoder value right
	double prevBE = bEncoder; // create previous encoder value right

	double averageHeading; //
	double deltaX;
	double deltaY;
	// gyro4.datarate(10);


	rightFwd.resetPosition();
	leftFwd.resetPosition();
	rightFwd.setPosition(0, degrees);
	leftFwd.setPosition(0, degrees);
	
	while (true)
	{
		lEncoder = leftFwd.position(degrees) * 3 / 4;
		rEncoder = rightFwd.position(degrees) * 3 / 4;
		// bEncoder = RotationB.position(degrees);
		//  convert encoder distance into distance traveled
		distL = ((lEncoder - prevLE) * M_PI / 180) * lRad;
		distR = ((rEncoder - prevRE) * M_PI / 180) * rRad;
		distB = ((bEncoder - prevBE) * M_PI / 180) * bRad;
		// convert encoder distance into disntance traveled

		prevLE = lEncoder; // create previous encoder value left
		prevRE = rEncoder; // create previous encoder value right
		prevBE = bEncoder;

		Heading = ((gyro4.rotation() * M_PI / 180));
		Heading = fmod(Heading, 2 * M_PI);
		deltaHeading = Heading - prevHeading; // calculate change in heading

		prevHeading = Heading;

		if (deltaHeading == 0 || true)
		{
			deltaX = distB;
			if (rightFwd.installed() && leftFwd.installed())
				deltaY = (distL + distR) / 2;
		}
		else
		{
			deltaX = 2 * sin(deltaHeading / 2) * ((distB / deltaHeading) + distFromCenterB);
			deltaY = 2 * sin(deltaHeading / 2) * ((distR / deltaHeading) - distFromCenterL);
		}

		averageHeading = prevHeading + (deltaHeading / 2);

		robot.x += (deltaY * sin(averageHeading)) + (deltaX * cos(averageHeading));
		robot.y += (deltaY * cos(averageHeading)) - (deltaX * sin(averageHeading));

		if (deltaX not_eq 0 || deltaY not_eq 0)
		{
			//    std::cout <<robot.x << "," <<robot.y << std::endl;
		}

		this_thread::sleep_for(10);
	}
	return 1;
}

void turnToPoint(point target) {
	float targetAngle = atan2(target.y - robot.y, target.x - robot.x);
	targetAngle = fmod(targetAngle, 2 * M_PI); // Normalize the angle

	float currentAngle = fmod(gyro4.rotation() * M_PI / 180, 2 * M_PI);
	float angleDifference = targetAngle - currentAngle;

	// Normalize the angle difference to be within -PI to PI
	if (angleDifference > M_PI) {
		angleDifference -= 2 * M_PI;
	} else if (angleDifference < -M_PI) {
		angleDifference += 2 * M_PI;
	}

	PIDturn(angleDifference * 180 / M_PI); // Convert radians to degrees for PIDturn
}

void driveToPoint(point target) {
	const float positionTolerance = 1.0; // Tolerance for reaching the target point
	const float angleTolerance = 0.1; // Tolerance for reaching the target angle in radians

	while (true) {
		// Calculate the distance to the target point
		float deltaX = target.x - robot.x;
		float deltaY = target.y - robot.y;
		float distanceToTarget = sqrt(deltaX * deltaX + deltaY * deltaY);

		// Calculate the target angle
		float targetAngle = atan2(deltaY, deltaX);
		targetAngle = fmod(targetAngle, 2 * M_PI); // Normalize the angle

		// Get the current angle
		float currentAngle = fmod(gyro4.rotation() * M_PI / 180, 2 * M_PI);
		float angleDifference = targetAngle - currentAngle;

		if (angleDifference > M_PI) {
			angleDifference -= 2 * M_PI;
		} else if (angleDifference < -M_PI) {
			angleDifference += 2 * M_PI;
		}

		// If the robot is in position, stop
		if (distanceToTarget < positionTolerance) {
			break;
		}

		// Turn to the target angle
		PIDturn(angleDifference * 180 / M_PI); // Convert radians to degrees for PIDturn

		// Drive forward to the target point
		drivePID(distanceToTarget);

		this_thread::sleep_for(10);
	}
}

void arcTurn(float distance, float radius, float speed) {
	const float wheelBase = 12.0; // Distance between the left and right wheels of the robot in inches
	const float circumference = 2 * M_PI * radius;
	const float angleToTurn = (distance / circumference) * 360; // Angle to turn in degrees

	// Calculate the target angle for the arc turn
	float targetAngle = fmod(gyro4.rotation() + angleToTurn, 360);

	// Calculate the distance each wheel needs to travel
	float innerWheelDistance = (radius - (wheelBase / 2)) * (angleToTurn * M_PI / 180);
	float outerWheelDistance = (radius + (wheelBase / 2)) * (angleToTurn * M_PI / 180);

	// Calculate the speed ratio between the inner and outer wheels
	float speedRatio = innerWheelDistance / outerWheelDistance;

	// Set the speed for the outer wheel
	float outerWheelSpeed = speed; // Set the speed for the outer wheel

	// Set the speed for the inner wheel based on the speed ratio
	float innerWheelSpeed = outerWheelSpeed * speedRatio;

	// Reset the motor positions
	rightFwd.resetPosition();
	leftFwd.resetPosition();

	// Start the arc turn
	while (true) {
		float currentAngle = fmod(gyro4.rotation(), 360);
		float angleDifference = targetAngle - currentAngle;

		// Normalize the angle difference to be within -180 to 180
		if (angleDifference > 180) {
			angleDifference -= 360;
		} else if (angleDifference < -180) {
			angleDifference += 360;
		}

		// If the robot has turned the desired angle, stop
		if (fabs(angleDifference) < 1) {
			break;
		}

		// Set the motor speeds for the arc turn
		leftFwd.spin(forward, innerWheelSpeed, percent);
		rightFwd.spin(forward, outerWheelSpeed, percent);

		// Small delay to prevent overloading the CPU
		this_thread::sleep_for(10);
	}

	// Stop the motors
	leftFwd.stop();
	rightFwd.stop();
}

