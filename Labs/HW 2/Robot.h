#ifndef ROBOT_H
#define ROBOT_H

#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include "gl/glut.h"
#include "Ball.h"

class Robot {
private:
	Ball ball;
	GLdouble rotate;
	GLdouble angleShoulder;
	GLdouble angleArm;
	GLdouble angleHand;
	GLdouble angleFinger;
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
	void toggleAnimation();
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
	GLdouble getShoulderAngle() const;
	GLdouble getArmAngle() const;
	GLdouble getHandAngle() const;
	GLdouble getFingerAngle() const;
	unsigned int getNumberOfFingers() const;

	void draw();
	void animate();

	Robot();
};
#endif