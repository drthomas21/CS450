#ifndef ROBOT_H
#define ROBOT_H

#ifndef LIB_H
#include "lib.h"
#endif

class Robot {
private:
	GLdouble rotate;
	GLdouble angleShoulder;
	GLdouble angleArm;
	GLdouble angleHand;
	GLdouble angleFinger;
	bool isActived;
	bool isWireframe;
	bool isAnimating;
	GLdouble lengthUpperArm;
	GLdouble lengthLowerArm;
	GLdouble lengthFingerSegment;
	unsigned int numOfFingers;
	unsigned long time;
	GLdouble x;
	GLdouble y;
	GLdouble z;

	void applySkinMaterial();
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

	void doAttack(unsigned int, unsigned long);
	void toggleActivation();
	void toggleWireframe();
	void toggleAnimation();
	void startAnimation();
	void stopAnimation();
	void reset();

	GLdouble getX() const;
	GLdouble getY() const;
	GLdouble getZ() const;
	GLdouble getBaseRadius() const;
	GLdouble getRotate() const;
	GLdouble getUpperArmLength() const;
	GLdouble getLowerArmLength() const;
	GLdouble getFingerSegmentLength() const;
	GLdouble getShoulderAngle() const;
	GLdouble getArmAngle() const;
	GLdouble getHandAngle() const;
	GLdouble getFingerAngle() const;
	unsigned int getNumberOfFingers() const;

	void draw();
	void animate(unsigned long);

	Robot();
};
#endif