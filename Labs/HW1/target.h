#ifndef TARGET_H
#define TARGET_H
#include "bullet.h"

class Target {
	private:
		long long time;
		long long _time;
		double centerX;
		double _centerX;
		double centerY;
		double _centerY;
		double xFactor;
		double yFactor;
		double velocityX;
		double velocityY;
		double theta;
		bool moving;
		bool isConfigured;

	public:
		const double RADIUS = 3.0;

		void draw();
		void setX(double);
		void setY(double);
		void setVelocity(double);
		void flipVelocityX();
		void flipVelocityY();
		void toggleMovement();
		void checkCollision(Bullet&);
		void calculatePosition();
		bool isMoving();
		double getX() const;
		double getY() const;
		double getVelocity() const;

		Target();
};
#endif
