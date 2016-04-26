#ifndef BULLET_H
#define BULLET_H
#include <vector>
#include "lib.h"

class Bullet {
	private:
		std::vector<GLfloatPoint2D> bulletVector;
		double centerX;
		double _centerX;
		double centerY;
		double _centerY;
		double theta;
		double velocity;
		bool fired;
		long long time;
		long long _time;
		double groundLevel;

	public:
		const double RADIUS = 1.25;

		void draw();
		void setX(double);
		void setY(double);
		void setVelocity(double);
		void setTheta(double);
		void setGroundLevel(double);
		void fireBullet();
		void hitTarget();
		void incrTime();
		bool wasFired();
		double getX() const;
		double getY() const;
		double getVelocity() const;
		double getTheta() const;
		double getEllapseTime() const;

		Bullet();
};
#endif