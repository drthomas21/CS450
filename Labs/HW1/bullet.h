#ifndef BULLET_H
#define BULLET_H

class Bullet {
	private:
		double centerX;
		double centerY;
		double theta;
		bool fired;
		long long time;
		long long _time;
		double groundLevel;

	public:
		void draw();
		void setX(double);
		void setY(double);
		void setTheta(double);
		void setGroundLevel(double);
		void fireBullet();
		void hitTarget();
		void incrTime();
		bool wasFired();
		double getX();
		double getY();

		Bullet();
		Bullet operator=(const Bullet&);
};
#endif