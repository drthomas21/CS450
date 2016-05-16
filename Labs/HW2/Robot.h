#ifndef ROBOT_H
#define ROBOT_H

#include <gl/GLU.h>

class Robot {
private:
	GLdouble rotate;
	double angleShoulder;
	double angleArm;
	double angleHand;
	double angleFinger;
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