#include "Room.h"
#include <cmath>
#include <iostream>

GLdouble shiftAmount = 5.0, wallThickness = 1.0;

GLdouble Room::getWidth() {
	return this->width;
}
GLdouble Room::getHeight() {
	return this->height;
}
GLdouble Room::getDepth() {
	return this->depth;
}
Enemy* Room::getEnemy(size_t idx) {
	if (idx < this->enemyCount) {
		return &this->enemies[idx];
	}
	return nullptr;
}
Robot* Room::getRobot() {
	return &this->robot;
}
Camera* Room::getCamera() {
	return &this->camera;
}

bool Room::isSpotClear(GLdouble x, GLdouble z, Enemy* target) {
	bool isClear = true;
	for (size_t i = 0; i < this->enemyCount && isClear; i++) {
		if (&this->enemies[i] == target) continue;

		GLdouble distance = pow(pow(x - this->enemies[i].getX(), 2.0) +  pow(z - this->enemies[i].getZ(), 2.0), 0.5) - 2.0 * target->getFootSize();
		if (distance <= 0) {
			isClear = false;
		}
	}

	return isClear;
}

bool Room::isSpotClear(GLdouble x, GLdouble z, Robot* target) {
	bool isClear = true;
	for (size_t i = 0; i < this->enemyCount && isClear; i++) {
		GLdouble distance = pow(pow(x - this->enemies[i].getX(), 2.0) + pow(z - this->enemies[i].getZ(), 2.0), 0.5) - target->getBaseRadius() - this->enemies[i].getFootSize();

		if(distance <= 0) {
			isClear = false;
		}
	}

	return isClear;
}

void Room::moveEnemy(Enemy* enemy, GLdouble amount) {
	Vector3 vect(enemy->getX() - this->robot.getX(), 0, enemy->getZ() - this->robot.getZ());
	GLdouble distance = pow(pow(vect.x, 2.0) + pow(vect.z, 2.0), 0.5);
	vect.normalize();
	if (distance > this->robot.getBaseRadius() + enemy->getFootSize() && vect.z != 0 && vect.x != 0) {
		GLdouble theta = atan(-vect.z / vect.x);
		if (vect.x < 0) {
			theta += pi;
		}

		GLdouble _amountX = cos(theta), _amountZ = sin(theta);
		GLdouble x = enemy->getX() - amount * _amountX, y = enemy->getZ() + amount * _amountZ;
		if (this->isSpotClear(x, y, enemy)) {
			enemy->setX(enemy->getX() - amount * _amountX);
			enemy->setZ(enemy->getZ() + amount * _amountZ);
		}		
	} else {
		if (vect.x == 0) {
			enemy->setZ(distance - amount);
		}
		else if (vect.z == 0) {
			enemy->setX(distance + amount);
		}
		else {
			//TODO: attack robot
		}
	}
}

unsigned long Room::getTime() {
	typedef std::chrono::duration<unsigned long, std::milli> milliseconds_type;
	std::chrono::system_clock::time_point _time = std::chrono::system_clock::now();
	milliseconds_type diff(std::chrono::duration_cast<milliseconds_type>(_time - this->time));
	return diff.count();
}

void Room::setWidth(GLdouble n) {
	this->width = n;
}
void Room::setHeight(GLdouble n) {
	this->height = n;
}
void Room::setDepth(GLdouble n) {
	this->depth = n;
}

void Room::shiftRobotLeft() {
	if (this->robot.getX() - this->robot.getBaseRadius() - shiftAmount > -this->width && this->robot.getZ() + this->robot.getBaseRadius() + shiftAmount < this->depth) {
		GLdouble x = this->robot.getX() - shiftAmount, y = this->robot.getZ() + shiftAmount;
		if (this->isSpotClear(x, y, &this->robot)) {
			this->robot.setX(x);
			this->robot.setZ(y);
		}		
	} else {
		this->robot.setX(-this->width + this->robot.getBaseRadius() + wallThickness);
		this->robot.setZ(this->depth - this->robot.getBaseRadius() - wallThickness);
	}
}
void Room::shiftRobotRight() {
	GLdouble adjustment = pow(shiftAmount * shiftAmount * 2.0, 0.5) * (this->robot.getX() > 0 ? 1 : -1);
	if (this->robot.getX() + this->robot.getBaseRadius() + shiftAmount < this->width && this->robot.getZ() - this->robot.getBaseRadius() - shiftAmount > -this->depth) {
		GLdouble x = this->robot.getX() + shiftAmount, y = this->robot.getZ() - shiftAmount;
		if (this->isSpotClear(x, y, &this->robot)) {
			this->robot.setX(x);
			this->robot.setZ(y);
		}
	} else {
		this->robot.setX(this->width - this->robot.getBaseRadius() - wallThickness);
		this->robot.setZ(-this->depth + this->robot.getBaseRadius() + wallThickness);
	}
}

void Room::updateCamera(GLdouble x, GLdouble y) {
	this->cameraOffsetX = x * cameraSensitivity;
	this->cameraOffsetY = y * cameraSensitivity;
	if (this->cameraOffsetY < 0.25) this->cameraOffsetY = 0.25;

	this->robot.setRotate(-this->cameraOffsetX * 180.0 / pi);
}

void Room::updateCamera() {
	Point3 lookAtRobot(this->robot.getX(), this->robot.getY(), this->robot.getZ());
	Point3 positionCamera(this->robot.getX() + 75.0 * cos(this->cameraOffsetX), this->robot.getY() + 90.0 * this->cameraOffsetY, this->robot.getZ() + 75.0 * sin(this->cameraOffsetX));
	Vector3 upVector(0, 1, 0);

	this->camera.set(positionCamera, lookAtRobot, upVector);
}

void Room::animate() {
	typedef std::chrono::duration<unsigned long, std::milli> milliseconds_type;
	std::chrono::system_clock::time_point _time = std::chrono::system_clock::now();
	milliseconds_type diff(std::chrono::duration_cast<milliseconds_type>(_time - this->timeSegment));
	double shiftedAmount = shiftAmount * ((double)diff.count() / 10000.0) * 5.0;

	this->robot.animate(this->getTime());
	for (size_t i = 0; i < this->enemyCount; i++) {
		if (this->enemies[i].isAlive()) {
			this->faceRobot(&this->enemies[i]);
			this->moveEnemy(&this->enemies[i], shiftedAmount);
			//this->enemies[i].animate(this->getTime());
		}
	}

	//Check Collision Between Hand and Enemy
	Vector3 robotHand(
		this->robot.getX() +  (
			this->robot.getUpperArmLength() * cos((90.0 + this->robot.getShoulderAngle()) * (pi / 180.0)) +
			this->robot.getLowerArmLength() * cos((90.0 + this->robot.getShoulderAngle() + this->robot.getArmAngle()) * (pi / 180.0)) +
			3.5 * cos((90.0 + this->robot.getShoulderAngle() + this->robot.getArmAngle() + this->robot.getHandAngle()) * (pi / 180.0))
		),

		this->robot.getY() + (
			3.0 + this->robot.getUpperArmLength() * sin((90.0 + this->robot.getShoulderAngle()) * (pi / 180.0)) +
			this->robot.getLowerArmLength() * sin((90.0 + this->robot.getShoulderAngle() + this->robot.getArmAngle()) * (pi / 180.0)) +
			3.5 * sin((90.0 + this->robot.getShoulderAngle() + this->robot.getArmAngle() + this->robot.getHandAngle()) * (pi / 180.0))
		),

		this->robot.getZ() + (
			this->robot.getUpperArmLength() * cos((90.0 + this->robot.getShoulderAngle()) * (pi / 180.0)) +
			this->robot.getLowerArmLength() * cos((90.0 + this->robot.getShoulderAngle() + this->robot.getArmAngle()) * (pi / 180.0)) +
			3.5 * cos((90.0 + this->robot.getShoulderAngle() + this->robot.getArmAngle() + this->robot.getHandAngle()) * (pi / 180.0))
		)
	);
	glPushMatrix();
		glTranslated(robotHand.x, robotHand.y, robotHand.z);
		glutWireSphere(20.0, 20, 20);
	glPopMatrix();
	this->timeSegment = std::chrono::system_clock::now();
}

void Room::draw() {
	//Update camera
	this->updateCamera();

	//Left
	glPushMatrix();
	glTranslated(-this->width, this->height / 2.0, 0);
	glScaled(1, this->height, this->depth*2.0);
	glutWireCube(wallThickness);
	glPopMatrix();

	//Right
	glPushMatrix();
	glTranslated(this->width, this->height / 2.0, 0);
	glScaled(1, this->height, this->depth*2.0);
	glutWireCube(wallThickness);
	glPopMatrix();

	//Front
	glPushMatrix();
	glTranslated(0, this->height / 2.0, this->depth);
	glScaled(this->width*2.0, this->height, 1);
	glutWireCube(wallThickness);
	glPopMatrix();

	//Back
	glPushMatrix();
	glTranslated(0, this->height / 2.0, -this->depth);
	glScaled(this->width*2.0, this->height, 1);
	glutWireCube(wallThickness);
	glPopMatrix();

	//Draw robot
	this->robot.draw();

	//Guidance Rail
	glBegin(GL_LINES);
	glVertex3d(-this->width, 0, this->width);
	glVertex3d(this->width, 0, -this->width);
	glEnd();

	//Draw enemies
	for (size_t i = 0; i < this->enemyCount; i++) {
		if (this->enemies[i].isAlive()) {
			this->enemies[i].draw();
		}		
	}
}

void Room::faceRobot(Enemy *enemy) {
	Vector3 vect(enemy->getX() - this->robot.getX(), enemy->getY() - this->robot.getY(), enemy->getZ() - this->robot.getZ());
	vect.normalize();
	GLdouble theta = atan(-vect.z / vect.x);
	if (vect.x < 0) {
		theta += pi;
	}
	enemy->setRotated(theta * 180.0 / pi);
}

Room::Room() :width(600.0), height(300.0), depth(600.0), enemyCount(5), cameraX(25), cameraY(15), cameraZ(25), cameraOffsetX(0), cameraOffsetY(0.25) {
	std::srand(std::time(NULL));

	//Time Config
	this->time = std::chrono::system_clock::now();
	this->timeSegment = std::chrono::system_clock::now();

	//Enemies Config
	if (this->enemies == nullptr) {
		this->enemies = new Enemy[this->enemyCount];
	}

	for (size_t i = 0; i < this->enemyCount; i++) {
		this->enemies[i] = Enemy();
		while (true) {
			this->enemies[i].setX(rand() % (int)this->width - rand() % (int)this->width);
			this->enemies[i].setZ(rand() % (int)this->width - rand() % (int)this->width);
			this->enemies[i].setY(0);

			GLdouble distance;
			//Distance to robot hand
			distance = pow(pow(this->enemies[i].getX() - this->robot.getX(), 2.0) + pow(this->enemies[i].getZ() - this->robot.getZ(), 2.0),0.5) - this->robot.getBaseRadius() - this->enemies[i].getFootSize();
			if (distance > 50) {
				break;
			}

			for (size_t t = 0; t < i; t++) {
				distance = pow(pow(this->enemies[t].getX() - this->robot.getX(), 2.0) + pow(this->enemies[t].getZ() - this->robot.getZ(), 2.0), 0.5) - this->robot.getBaseRadius() - this->enemies[t].getFootSize();
				if (distance > 20) {
					break;
				}
			}

		}		
	}
	
	//Robot Config
	this->robot.setX(0);
	this->robot.setY(0);
	this->robot.setZ(0);
	//this->robot.setLowerArmLength(18.0);
	//this->robot.setUpperArmLength(25.0);

	//Camera Config
};

Room::~Room() {
	delete[] this->enemies;
}