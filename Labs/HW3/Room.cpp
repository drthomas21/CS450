#include "Room.h"
#include <cmath>
#include <iostream>

GLdouble shiftAmount = 5.0, wallThickness = 1.0, cameraOffsetX = 1, cameraOffsetY = 1, cameraOffsetZ = 1;

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

void Room::moveEnemies(GLdouble amount) {
	for (size_t i = 0; i < this->enemyCount; i++) {
		GLdouble distanceX = this->enemies[i].getX() - this->robot.getX();
		GLdouble distanceZ = this->enemies[i].getZ() - this->robot.getZ();
		if (distanceX != 0 && distanceZ != 0) {
			double theta = atan(distanceZ / distanceX);
			this->enemies[i].setX(this->enemies[i].getX() - (this->enemies[i].getX() < 0 ? amount * -1 : amount) * cos(theta));
			this->enemies[i].setZ(this->enemies[i].getZ() - (this->enemies[i].getZ() < 0 ? amount * -1 : amount) * sin(theta));
		} else {
			if (distanceX == 0) {
				this->enemies[i].setZ(this->enemies[i].getZ() - (this->enemies[i].getZ() < 0 ? amount * -1 : amount));
			} else if(distanceZ == 0){
				this->enemies[i].setX(this->enemies[i].getX() - (this->enemies[i].getX() < 0 ? amount * -1 : amount));
			} else {
				//TODO: attack robot
			}
		}
	}
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
		this->robot.setX(this->robot.getX() - shiftAmount);
		this->robot.setZ(this->robot.getZ() + shiftAmount);
	} else {
		this->robot.setX(-this->width + this->robot.getBaseRadius() + wallThickness);
		this->robot.setZ(this->depth - this->robot.getBaseRadius() - wallThickness);
	}
}
void Room::shiftRobotRight() {
	GLdouble adjustment = pow(shiftAmount * shiftAmount * 2.0, 0.5) * (this->robot.getX() > 0 ? 1 : -1);
	if (this->robot.getX() + this->robot.getBaseRadius() + shiftAmount < this->width && this->robot.getZ() - this->robot.getBaseRadius() - shiftAmount > -this->depth) {
		this->robot.setX(this->robot.getX() + shiftAmount);
		this->robot.setZ(this->robot.getZ() - shiftAmount);
	} else {
		this->robot.setX(this->width - this->robot.getBaseRadius() - wallThickness);
		this->robot.setZ(-this->depth + this->robot.getBaseRadius() + wallThickness);
	}
}

void Room::updateCamera(GLdouble x, GLdouble y) {
	cameraOffsetX = x;
	cameraOffsetY = y + 0.25;
	this->robot.setRotate(-1.25 * 180.0 * cameraOffsetX);
	//this->updateCamera();
}

void Room::updateCamera() {
	Point3 lookAtRobot(this->robot.getX(), this->robot.getY(), this->robot.getZ());
	Point3 positionCamera(this->robot.getX() + 75.0 * cos(1.25 * pi * cameraOffsetX), this->robot.getY() + 90.0 * cameraOffsetY, this->robot.getZ() + 75.0 * sin(1.25 * pi * cameraOffsetX));
	Vector3 upVector(0, 1, 0);

	this->camera.set(positionCamera, lookAtRobot, upVector);
}

void Room::animate() {
	typedef std::chrono::duration<int, std::milli> milliseconds_type;
	std::chrono::system_clock::time_point _time = std::chrono::system_clock::now();
	milliseconds_type diff(std::chrono::duration_cast<milliseconds_type>(_time - this->time));
	double shiftedAmount = shiftAmount * (1000 / diff.count());

	for (size_t i = 0; i < this->enemyCount; i++) {
		this->faceRobot(&this->enemies[i]);
		//this->enemies[i].animate(diff.count());
	}
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

	//Draw enemies
	for (size_t i = 0; i < this->enemyCount; i++) {
		this->enemies[i].draw();
	}
}

void Room::faceRobot(Enemy *enemy) {
	GLdouble det = pow(pow(enemy->getX() - this->robot.getX(), 2.0) + pow(enemy->getZ() - this->robot.getZ(), 2.0), 0.5);
	det = det == 0 ? 1 : det;
	GLdouble theta = acos((enemy->getX() - this->robot.getX()) / det) + pi;
	enemy->setRotated(theta * 180.0 / pi);
}

Room::Room() :width(300.0), height(300.0), depth(300.0), enemyCount(5), cameraX(25), cameraY(15), cameraZ(25) {
	std::srand(std::time(NULL));

	//Time Config
	this->time = std::chrono::system_clock::now();

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
			if (distance > 1) {
				break;
			}

			for (size_t t = 0; t < i; t++) {
				distance = pow(pow(this->enemies[t].getX() - this->robot.getX(), 2.0) + pow(this->enemies[t].getZ() - this->robot.getZ(), 2.0), 0.5) - this->robot.getBaseRadius() - this->enemies[t].getFootSize();
				if (distance > 1) {
					break;
				}
			}

		}		
	}
	
	//Robot Config
	this->robot.setX(0);
	this->robot.setY(0);
	this->robot.setZ(0);

	//Camera Config
};

Room::~Room() {
	delete[] this->enemies;
}