#ifndef TARGET_H
#define TARGET_H

class Target {
	double centerX;
	double centerY;

	void draw();
	void setX(double);
	void setY(double);
	double getX();
	double getY();

	Target();
	Target operator=(const Target&);
};
#endif