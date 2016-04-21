#ifndef TANK_H
#define TANK_H
class Tank {
	double centerX;
	double centerY;
	double turrentDegree;

	void draw();
	void setX(double);
	void setY(double);
	void setTurrentDegree(double degree);
	double getX();
	double getY();
	double getTurrentDegree();

	Tank();
	Tank operator=(const Tank&);
};
#endif