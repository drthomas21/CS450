#include "Robot.h"
#include <math.h>
#include <iostream>

GLdouble _theta1, _theta2;

void Robot::setX(GLdouble n) {
	this->x += n;
}
void Robot::setY(GLdouble n) {
	this->y += n;
}
void Robot::setZ(GLdouble n) {
	this->z += n;
}
void Robot::setRotate(GLdouble n) {
	if (!this->isActived) return;
	this->rotate += n;
}
void Robot::setLowerArmLength(GLdouble n) {
	this->lengthLowerArm = n;
}
void Robot::setUpperArmLength(GLdouble n) {
	this->lengthUpperArm = n;
}
void Robot::setFingerSegmentLength(GLdouble n) {
	this->lengthFingerSegment = n;
}
void Robot::setShoulderAngle(double n) {
	if (!this->isActived) return;
	this->angleShoulder += n;
	if (this->angleShoulder < -MAX_ANGLE) {
		this->angleShoulder = -MAX_ANGLE;
	} else if (this->angleShoulder > MAX_ANGLE) {
		this->angleShoulder = MAX_ANGLE;
	}
	std::cout << "Shoulder: " << this->angleShoulder << std::endl;
}
void Robot::setArmAngle(double n) {
	if (!this->isActived) return;
	this->angleArm += n;
	if (this->angleArm < -MAX_ANGLE_ELBOW) {
		this->angleArm = -MAX_ANGLE_ELBOW;
	} else if (this->angleArm > MAX_ANGLE_ELBOW) {
		this->angleArm = MAX_ANGLE_ELBOW;
	}
	std::cout << "Elbow: " << this->angleArm << std::endl;
}
void Robot::setHandAngle(double n) {
	if (!this->isActived) return;
	this->angleHand += n;
	if (this->angleHand < -MAX_ANGLE_HAND) {
		this->angleHand = -MAX_ANGLE_HAND;
	} else if (this->angleHand > MAX_ANGLE_HAND) {
		this->angleHand = MAX_ANGLE_HAND;
	}
	std::cout << "Hand: " << this->angleHand << std::endl;
}
void Robot::setFingerAngle(double n) {
	if (!this->isActived) return;
	this->angleFinger += n;
	if (this->angleFinger < -MAX_ANGLE_FINGER) {
		this->angleFinger = -MAX_ANGLE_FINGER;
	} else if (this->angleFinger > 0) {
		this->angleFinger = 0;
	}
	std::cout << "Finger: " << this->angleFinger << std::endl;
}
void Robot::setNumberOfFingers(unsigned int n) {
	this->numOfFingers = n;
}

void Robot::toggleActivation() {
	this->isActived = !this->isActived;
}

void Robot::toggleWireframe() {
	this->isWireframe = !this->isWireframe;
}

void Robot::startAnimation() {
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	this->isAnimating = true;
	this->time = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL);

	this->angleFinger = -MAX_ANGLE_FINGER;
	if (this->angleArm == 0 && this->angleShoulder == 0) {
		this->angleHand = 0;
	}
	else if (this->angleArm <= 0 && this->angleShoulder <= 0) {
		this->angleHand = MAX_ANGLE_HAND;
	}
	else if (this->angleArm >= 0 && this->angleShoulder >= 0) {
		this->angleHand = -MAX_ANGLE_HAND;
	}
	else if (abs(this->angleArm) < abs(this->angleShoulder)) {
		this->angleHand = MAX_ANGLE_HAND;
	}
	else if (abs(this->angleArm) > (this->angleShoulder)) {
		this->angleHand = -MAX_ANGLE_HAND;
	}

	_theta1 = this->angleArm;
	_theta2 = this->angleShoulder;

	this->ball.reset();
	this->ball.showBall();
}

void Robot::stopAnimation() {
	this->isAnimating = false;
}

void Robot::reset() {
	if (this->isAnimating) {
		this->angleArm = 0;
		this->angleFinger = 0;
		this->angleHand = 0;
		this->angleShoulder = 0;
		this->rotate = 0;
	}

	this->isActived = false;
	this->isAnimating = false;
	this->isWireframe = false;
	this->ball.hideBall();
}

GLdouble Robot::getX() const {
	return this->x;
}
GLdouble Robot::getY() const {
	return this->y;
}
GLdouble Robot::getZ() const {
	return this->z;
}
GLdouble Robot::getRotate() const {
	return this->rotate;
}
GLdouble Robot::getLowerArmLength() const {
	return this->lengthLowerArm;
}
GLdouble Robot::getUpperArmLength() const {
	return this->lengthUpperArm;
}
GLdouble Robot::getFingerSegmentLength() const {
	return this->lengthFingerSegment;
}
double Robot::getShoulderAngle() const {
	return this->angleShoulder;
}
double Robot::getArmAngle() const {
	return this->angleArm;
}
double Robot::getHandAngle() const {
	return this->angleHand;
}
double Robot::getFingerAngle() const {
	return this->angleFinger;
}
unsigned int Robot::getNumberOfFingers() const {
	return this->numOfFingers;
}

void Robot::draw() {
	//Draw Ball
	GLdouble x = (this->lengthUpperArm + 0.0) * cos((90.0 + this->angleShoulder) * (PI / 180.0)) + this->lengthLowerArm * cos((90.0 + this->angleShoulder + this->angleArm) * (PI / 180.0)) + 3.0 * cos((90.0 + this->angleShoulder + this->angleArm + this->angleHand) * (PI / 180.0)) + this->getX();
	GLdouble y = (this->lengthUpperArm + 3.0) * sin((90.0 + this->angleShoulder) * (PI / 180.0)) + this->lengthLowerArm * sin((90.0 + this->angleShoulder + this->angleArm) * (PI / 180.0)) + 3.0 * sin((90.0 + this->angleShoulder + this->angleArm + this->angleHand) * (PI / 180.0)) + this->getY();
	GLdouble z = this->getZ();
	if (this->isAnimating) {
		this->ball.setX(x);
		this->ball.setY(y);
		this->ball.setZ(z);
	}
	this->ball.draw(this->isWireframe,this->rotate);

	glColor3d(0.4, 0.4, 0.4);
	glTranslated(this->x, this->y, this->z);
	//Draw Base
	glPushMatrix();
		glTranslated(0, 0, 0);
		glScaled(1.0, 0.1, 1.0);
		if (this->isWireframe) {
			glutWireSphere(15.0, 20, 20);
		} else {
			glutSolidSphere(15.0, 20, 20);
		}
	glPopMatrix();

	glPushMatrix();
		glRotated(this->rotate, 0, 1, 0);

		//Draw shoulder joint
		glPushMatrix();
			glTranslated(0, 3.0, 0);
			if (this->isWireframe) {
				glutWireSphere(4.0, 20, 20);
			} else {
				glutSolidSphere(4.0, 20, 20);
			}

			//Draw upper arm
			glRotated(this->angleShoulder, 0, 0, 1);
			GLdouble shifted = this->lengthUpperArm / 2.0;
			glPushMatrix();
				glTranslated(0, shifted, 1.25);
				glScaled(1.25, shifted, 0.5);
				if (this->isWireframe) {
					glutWireCube(2);
				} else {
					glutSolidCube(2);
				}
			glPopMatrix();

			glPushMatrix();
				glTranslated(0, shifted, -1.25);
				glScaled(1.25, shifted, 0.5);
				if (this->isWireframe) {
					glutWireCube(2);
				}
				else {
					glutSolidCube(2);
				}
			glPopMatrix();

			//Draw elbow
			glPushMatrix();
				glTranslated(0, this->lengthUpperArm, 0);
				if (this->isWireframe) {
					glutWireSphere(2.5, 10, 10);
				} else {
					glutSolidSphere(2.5, 10, 10);
				}

				//Draw upper arm
				glRotated(this->angleArm, 0, 0, 1);
				shifted = this->lengthLowerArm / 2.0;
				glPushMatrix();
					glTranslated(0, shifted, 0);
					glScaled(1.25, shifted, 0.5);
					if (this->isWireframe) {
						glutWireCube(2);
					} else {
						glutSolidCube(2);
					}
				glPopMatrix();

				//Draw wrist
				glPushMatrix();
					glTranslated(0, this->lengthLowerArm, 0);
					glRotated(this->angleHand, 0, 0, 1);

					//Draw hand
					if (this->isWireframe) {
						glutWireSphere(1.75, 10, 10);
					}
					else {
						glutSolidSphere(1.75, 10, 10);
					}

					glPushMatrix();
						glTranslated(1.9, 0, 0);
						if (this->isActived) {
							glColor3d(1, 0, 0);							
						} else {
							glColor3d(0, 0, 1);
						}
						glutSolidSphere(0.5, 5, 5);
					glPopMatrix();

					glPushMatrix();
						glTranslated(-1.9, 0, 0);
						if (this->isActived) {
							glColor3d(1, 0, 0);
						} else {
							glColor3d(0, 0, 1);
						}
						glutSolidSphere(0.5, 5, 5);
					glPopMatrix();

					glPushMatrix();
						glTranslated(0, 0, 1.9);
						if (this->isActived) {
							glColor3d(1, 0, 0);
						}
						else {
							glColor3d(0, 0, 1);
						}
						glutSolidSphere(0.5, 5, 5);
					glPopMatrix();

					glPushMatrix();
						glTranslated(0, 0, -1.9);
						if (this->isActived) {
							glColor3d(1, 0, 0);
						}
						else {
							glColor3d(0, 0, 1);
						}
						glutSolidSphere(0.5, 5, 5);
					glPopMatrix();
	
					glColor3d(0.4, 0.4, 0.4);
					//Draw fingers
					GLdouble fingerRotation = 360.0 / this->numOfFingers;
					shifted = this->lengthLowerArm / 2.0;
					GLdouble radius = 0.85;
					
					for (unsigned int f = 0; f < this->numOfFingers; f++) {
						glPushMatrix();
							glRotated(fingerRotation * (double)f, 0, 1, 0);
							glTranslated(radius, 0, 0);
							glRotated(this->angleFinger, 0, 0, 1);

							//Upper finger segement
							glPushMatrix();	
								glTranslated(0, shifted / 2.0, 0);
								glScaled(1, shifted, 1);

								if (this->isWireframe) {
									glutWireCube(0.5);
								}
								else {
									glutSolidCube(0.5);
								}
							glPopMatrix();

							glTranslated(0, 3.0*shifted / 4.0, 0);

							//Draw fingerSegment joint
							glPushMatrix();								
								if (this->isWireframe) {
									glutWireSphere(0.5, 5, 5);
								}
								else {
									glutSolidSphere(0.5, 5, 5);
								}
							glPopMatrix();

							//Draw lower finger segment
							glPushMatrix();
								glTranslated(0.75 * this->angleFinger / 30.0, shifted / 4.0, 0);
								glRotated(-this->angleFinger, 0, 0, 1);
								glScaled(1, shifted, 1);								
								if (this->isWireframe) {
									glutWireCube(0.5);
								}
								else {
									glutSolidCube(0.5);
								}
							glPopMatrix();
						glPopMatrix();
					}
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
void Robot::animate() {
	this->ball.animate();
	if (!this->isAnimating) return;

	bool tossLeft = true;
	GLdouble acceleration = 0;
	GLdouble velocity = 0;

	if (this->angleHand == 0) {
		this->ball.setVelocity(0.0);
		this->isAnimating = 0;
	} else {
		GLdouble t1 = 0;
		GLdouble t2 = 0;

		FILETIME ft;
		GetSystemTimeAsFileTime(&ft);

		long long diff = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL) - this->time; //nanoseconds
		double time = static_cast<double>(static_cast<long double>(diff) / static_cast<long double>(10000000.0)); //seconds

		acceleration = (ROBOT_FORCE - this->ball.getForce()) / this->ball.getMass();
		t1 = 
		pow(((
			(2.0 * 2.0 * PI * this->lengthLowerArm * 0.25) 
			- (2.0 * PI * this->lengthLowerArm * this->angleArm / 360.0)) 
			/ acceleration), 0.5);
		t2 = 
		pow(((
			(2.0 * 2.0 * PI * this->lengthUpperArm * 0.25)
			- (2.0 * PI * this->lengthUpperArm * this->angleArm / 360.0))
			/ acceleration), 0.5);

		if (time <= t1) {
			this->angleArm = _theta1 * (t1 - time);
		}
		
		if(time <= t2) {
			this->angleShoulder = _theta2 * (t2 - time);
		}

		if (time > t1 && time > t2) {
			this->isAnimating = false;

			this->ball.setVelocity(pow(2.0 * acceleration *
				((2.0 * 2.0 * PI * this->lengthLowerArm * 0.25) - (2.0 * PI * this->lengthLowerArm * this->angleArm / 360.0)
					+ (2.0 * 2.0 * PI * this->lengthUpperArm * 0.25) - (2.0 * PI * this->lengthUpperArm * this->angleArm / 360.0))
				, 0.5));
			this->ball.setTheta(PI);

			this->ball.startAnimation();
		} else {
		
		}
	}
}

Robot::Robot():x(0),y(0),z(0),angleShoulder(0),angleArm(0),angleHand(0),angleFinger(0),lengthFingerSegment(3.0),lengthUpperArm(12.0),lengthLowerArm(9.0),rotate(0), numOfFingers(5) { 
	this->ball.setRadius(2.2);
}