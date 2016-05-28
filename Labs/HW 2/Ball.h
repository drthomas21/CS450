#ifndef BALL_H
#define BALL_H

#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include "gl/glut.h"

class Ball {
private:
	GLdouble x;
	GLdouble y;
	GLdouble z;
	GLdouble boundryHeight;
	GLdouble boundryWidth;
	GLdouble radius;
	GLdouble rotated;
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
	void setRotated(GLdouble);
	void setTheta(GLdouble);
	void setVelocity(GLdouble);
	void setBoundryHeight(GLdouble);
	void setBoundryWidth(GLdouble);

	void showBall();
	void hideBall();
	void startAnimation();
	void stopAnimation();
	void reset();

	GLdouble getX();
	GLdouble getY();
	GLdouble getZ();
	GLdouble getRadius();
	GLdouble getRotated();
	GLdouble getTheta();
	GLdouble getVelocity();
	GLdouble getForce();
	GLdouble getMass();

	void animate();
	void draw(bool);

	Ball();
};

#endif