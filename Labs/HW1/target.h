#ifndef TARGET_H
#define TARGET_H
#include "bullet.h"

class Target {
	private:
		double centerX;
		double centerY;
		double xFactor;
		double yFactor;
		double theta;
		bool moving;

	public:
		const double RADIUS = 3.0;

		void draw();
		void setX(double);
		void setY(double);
		void flipVelocityX();
		void flipVelocityY();
		void toggleMovement();
		void checkCollision(const Bullet&);
		void calculatePosition();
		bool isMoving();
		double getX() const;
		double getY() const;

		Target();
		Target operator=(const Target&);
};
#endif