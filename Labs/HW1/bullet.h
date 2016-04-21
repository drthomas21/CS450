#ifndef BULLET_H
#define BULLET_H

class Bullet {
	double centerX;
	double centerY;

	void draw();
	void setX(double);
	void setY(double);
	double getX();
	double getY();

	Bullet();
	Bullet operator=(const Bullet&);
};
#endif