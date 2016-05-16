#ifndef BALL_H
#define BALL_H

#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include "gl/glut.h"
#define PI 3.141592653589793
#define GRAVITY 9.8
#define AIR_FRICTION 0.47
#define BALL_MASS 0.453592

class Ball {
private:
	GLdouble x;
	GLdouble y;
	GLdouble z;
	double radius;
	double theta;
	double velocity;
	bool isAnimating;
	bool isShown;
	long long time;
public:
	void setX(GLdouble);
	void setY(GLdouble);
	void setZ(GLdouble);
	void setRadius(GLdouble);
	void setTheta(GLdouble);
	void setVelocity(GLdouble);

	void showBall();
	void hideBall();
	void startAnimation();
	void stopAnimation();
	void reset();

	GLdouble getX();
	GLdouble getY();
	GLdouble getZ();
	GLdouble getRadius();
	GLdouble getTheta();
	GLdouble getVelocity();
	GLdouble getForce();
	GLdouble getMass();

	void animate();
	void draw(bool, GLdouble);

	Ball();
};

#endif