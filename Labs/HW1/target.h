#ifndef TARGET_H
#define TARGET_H
#include "bullet.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

class Target {
	private:
		struct timeval time;
		double centerX;
		double centerY;
		double xFactor;
		double yFactor;
		double theta;
		bool moving;
		bool isConfigured;

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
