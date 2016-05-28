#include "Robot.h"
#include "lib.h"
#include <math.h>
#include <iostream>

GLdouble _theta1, _theta2, acceleration, t1, t2;

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

	while (this->rotate < 0) {
		this->rotate += 360.0;
	}

	while (this->rotate > 360.0) {
		this->rotate -= 360.0;
	}
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
	if (this->angleShoulder < -max_angle) {
		this->angleShoulder = -max_angle;
	} else if (this->angleShoulder > max_angle) {
		this->angleShoulder = max_angle;
	}
	std::cout << "Shoulder: " << this->angleShoulder << std::endl;
}
void Robot::setArmAngle(double n) {
	if (!this->isActived) return;
	this->angleArm += n;
	if (this->angleArm < -max_angle_elbow) {
		this->angleArm = -max_angle_elbow;
	} else if (this->angleArm > max_angle_elbow) {
		this->angleArm = max_angle_elbow;
	}
	std::cout << "Elbow: " << this->angleArm << std::endl;
}
void Robot::setHandAngle(double n) {
	if (!this->isActived) return;
	this->angleHand += n;
	if (this->angleHand < -max_angle_hand) {
		this->angleHand = -max_angle_hand;
	} else if (this->angleHand > max_angle_hand) {
		this->angleHand = max_angle_hand;
	}
	std::cout << "Hand: " << this->angleHand << std::endl;
}
void Robot::setFingerAngle(double n) {
	if (!this->isActived) return;
	this->angleFinger += n;
	if (this->angleFinger < -max_angle_finger) {
		this->angleFinger = -max_angle_finger;
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

void Robot::toggleAnimation() {
	if (this->isAnimating) {
		this->stopAnimation();
	} else {
		this->startAnimation();
	}
}

void Robot::startAnimation() {
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	this->isAnimating = true;
	this->time = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL);

	this->angleFinger = -max_angle_finger;
	if (this->angleArm == 0 && this->angleShoulder == 0) {
		this->angleHand = 0;
	}
	else if (this->angleArm <= 0 && this->angleShoulder <= 0) {
		this->angleHand = max_angle_hand;
	}
	else if (this->angleArm >= 0 && this->angleShoulder >= 0) {
		this->angleHand = -max_angle_hand;
	}
	else if (abs(this->angleArm) < abs(this->angleShoulder)) {
		this->angleHand = max_angle_hand;
	}
	else if (abs(this->angleArm) > (this->angleShoulder)) {
		this->angleHand = -max_angle_hand;
	}

	_theta1 = this->angleArm;
	_theta2 = this->angleShoulder;

	acceleration = (robot_force - this->ball.getForce()) / this->ball.getMass();

	t1 =
		pow(abs((
		(2.0 * pi * this->lengthLowerArm * 0.25)
			- (2.0 * pi * this->lengthLowerArm * (90.0 + this->angleArm) / 360.0))
			/ acceleration), 0.5);
	t2 =
		pow(abs((
		(2.0 * pi * this->lengthUpperArm * 0.25)
			- (2.0 * pi * this->lengthUpperArm * (90.0 + this->angleShoulder) / 360.0))
			/ acceleration), 0.5);

	this->ball.reset();
	this->ball.showBall();
}

void Robot::stopAnimation() {
	this->isAnimating = false;

	this->ball.setVelocity(2.0 * acceleration * (t1 > t2 ? t1 : t2));
	this->ball.setTheta((180 + this->angleShoulder + this->angleArm) * (pi / 180.0));
	this->ball.setRotated(this->rotate * (pi / 180.0));
	this->ball.startAnimation();
}

void Robot::reset() {
	this->angleArm = 0;
	this->angleFinger = 0;
	this->angleHand = 0;
	this->angleShoulder = 0;
	this->rotate = 0;

	this->isActived = false;
	this->isAnimating = false;
	this->isWireframe = false;
	this->ball.reset();
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
GLdouble Robot::getShoulderAngle() const {
	return this->angleShoulder;
}
GLdouble Robot::getArmAngle() const {
	return this->angleArm;
}
GLdouble Robot::getHandAngle() const {
	return this->angleHand;
}
GLdouble Robot::getFingerAngle() const {
	return this->angleFinger;
}
unsigned int Robot::getNumberOfFingers() const {
	return this->numOfFingers;
}

void Robot::draw() {
	//Draw Ball
	GLdouble x =
		this->lengthUpperArm * cos((90.0 + this->angleShoulder) * (pi / 180.0)) +
		this->lengthLowerArm * cos((90.0 + this->angleShoulder + this->angleArm) * (pi / 180.0)) +
		3.5 * cos((90.0 + this->angleShoulder + this->angleArm + this->angleHand) * (pi / 180.0));
	x *= cos(this->rotate);
	x += this->getX();

	GLdouble y = 
		3.0 + this->lengthUpperArm * sin((90.0 + this->angleShoulder) * (pi / 180.0)) + 
		this->lengthLowerArm * sin((90.0 + this->angleShoulder + this->angleArm) * (pi / 180.0)) + 
		3.5 * sin((90.0 + this->angleShoulder + this->angleArm + this->angleHand) * (pi / 180.0)) + 
		this->getY();

	GLdouble z = 
		this->lengthUpperArm * cos((90.0 + this->angleShoulder) * (pi / 180.0)) +
		this->lengthLowerArm * cos((90.0 + this->angleShoulder + this->angleArm) * (pi / 180.0)) +
		3.5 * cos((90.0 + this->angleShoulder + this->angleArm + this->angleHand) * (pi / 180.0));
	z *= sin(this->rotate);
	z += this->getZ();

	glPushMatrix();
	if (this->isAnimating) {
		this->ball.setX(x);
		this->ball.setY(y);
		this->ball.setZ(z);
		//glRotated(this->rotate, 0, 1, 0);
	}
	this->ball.draw(this->isWireframe);
	glPopMatrix();

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

	GLdouble velocity = 0;

	if (this->angleHand == 0) {
		this->ball.setVelocity(0.0);
		this->isAnimating = 0;
	} else {
		FILETIME ft;
		GetSystemTimeAsFileTime(&ft);

		long long diff = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL) - this->time; //nanoseconds
		double time = static_cast<double>(static_cast<long double>(diff) / static_cast<long double>(10000000.0)); //seconds

		if (time <= t1 && t1 != 0) {
			this->angleArm = _theta1 * (1.0 - time / t1);
		} else if (time > t1 && this->angleArm != 0.0) {
			this->angleArm = 0;
		}
		
		if(time <= t2 && t2 != 0) {
			this->angleShoulder = _theta2 * (1.0 - time / t2);
		} else if(time > t2 && this->angleShoulder != 0.0) {
			this->angleShoulder = 0;
		}

		if (time > t1 && time > t2) {
			this->stopAnimation();			
		} 
	}
}

Robot::Robot():x(0),y(0),z(0),angleShoulder(0),angleArm(0),angleHand(0),angleFinger(0),lengthFingerSegment(3.0),lengthUpperArm(12.0),lengthLowerArm(9.0),rotate(0), numOfFingers(5) { 
	this->ball.setRadius(2.2);
	this->ball.setBoundryHeight((this->lengthUpperArm + this->lengthUpperArm + this->lengthFingerSegment *2.0) * 1.10);
	this->ball.setBoundryWidth((this->lengthUpperArm + this->lengthUpperArm + this->lengthFingerSegment *2.0) * 1.10);
}