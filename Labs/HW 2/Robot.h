#ifndef ROBOT_H
#define ROBOT_H

#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include "gl/glut.h"
#include "Ball.h"
#define PI 3.141592653589793
#define ROBOT_FORCE 20.0
#define GRAVITY 9.8
#define MAX_ANGLE_FINGER 30.0
#define MAX_ANGLE_HAND 45.0
#define MAX_ANGLE_ELBOW 100.0
#define MAX_ANGLE 80.0

class Robot {
private:
	Ball ball;
	GLdouble rotate;
	double angleShoulder;
	double angleArm;
	double angleHand;
	double angleFinger;
	bool isActived;
	bool isWireframe;
	bool isAnimating;
	long long time;
	GLdouble lengthUpperArm;
	GLdouble lengthLowerArm;
	GLdouble lengthFingerSegment;
	unsigned int numOfFingers;
	GLdouble x;
	GLdouble y;
	GLdouble z;
public:
	void setX(GLdouble);
	void setY(GLdouble);
	void setZ(GLdouble);
	void setRotate(GLdouble);
	void setUpperArmLength(GLdouble);
	void setLowerArmLength(GLdouble);
	void setFingerSegmentLength(GLdouble);
	void setShoulderAngle(double);
	void setArmAngle(double);
	void setHandAngle(double);
	void setFingerAngle(double);
	void setNumberOfFingers(unsigned int);

	void toggleActivation();
	void toggleWireframe();
	void startAnimation();
	void stopAnimation();
	void reset();

	GLdouble getX() const;
	GLdouble getY() const;
	GLdouble getZ() const;
	GLdouble getRotate() const;
	GLdouble getUpperArmLength() const;
	GLdouble getLowerArmLength() const;
	GLdouble getFingerSegmentLength() const;
	double getShoulderAngle() const;
	double getArmAngle() const;
	double getHandAngle() const;
	double getFingerAngle() const;
	unsigned int getNumberOfFingers() const;

	void draw();
	void animate();

	Robot();
};
#endif