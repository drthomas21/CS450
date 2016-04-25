#ifndef TARGET_H
#define TARGET_H

class Target {
	private:
		double centerX;
		double centerY;
		double velocityX;
		double velocityY;
		bool moving;

	public:
		void draw();
		void setX(double);
		void setY(double);
		void flipVelocityX();
		void flipVelocityY();
		void toggleMovement();
		bool isMoving();
		double getX();
		double getY();

		Target();
		Target operator=(const Target&);
};
#endif