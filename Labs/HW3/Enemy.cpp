#include "Enemy.h"
#include <iostream>

GLdouble footSize = 7, bodySize = 5, bodyLength = 3.5, headSize = 9;
GLdouble Enemy::getX() {
	return this->x;
}
GLdouble Enemy::getY() {
	return this->y;
}
GLdouble Enemy::getZ() {
	return this->z;
}
GLdouble Enemy::getRotated() {
	return this->rotated;
}

GLdouble Enemy::getFootSize() {
	return footSize;
}
GLdouble Enemy::getBodyLength() {
	return bodyLength;
}
GLdouble Enemy::getHeadSize() {
	return headSize;
}

void Enemy::applySkinMaterial() {
	GLfloat mat[4], ambr, ambg, ambb, difr, difg, difb, specr, specg, specb, shine;
	ambr = 0.2, ambg = 0.55, ambb = 0.15;
	difr = 0.3, difg = 0.6, difb = 0.2;
	specr = 0.574597, specg = 0.774597, specb = 0.474597;
	shine = 0.6;
	mat[0] = ambr;
	mat[1] = ambg;
	mat[2] = ambb;
	mat[3] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	mat[0] = difr;
	mat[1] = difg;
	mat[2] = difb;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	mat[0] = specr;
	mat[1] = specg;
	mat[2] = specb;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
	glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
}

void Enemy::applyFaceMaterial() {
	GLfloat mat[4], ambr, ambg, ambb, difr, difg, difb, specr, specg, specb, shine;
	ambr = 0.02, ambg = 0.02, ambb = 0.02;
	difr = 0.01, difg = 0.01, difb = 0.01;
	specr = 0.04, specg = 0.04, specb = 0.04;
	shine = 0.078125;
	mat[0] = ambr;
	mat[1] = ambg;
	mat[2] = ambb;
	mat[3] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	mat[0] = difr;
	mat[1] = difg;
	mat[2] = difb;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	mat[0] = specr;
	mat[1] = specg;
	mat[2] = specb;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
	glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
}

void Enemy::setX(GLdouble n) {
	this->x = n;
}
void Enemy::setY(GLdouble n) {
	this->y = n;
}
void Enemy::setZ(GLdouble n) {
	this->z = n;
}
void Enemy::setRotated(GLdouble n) {
	this->rotated = n;
}
void Enemy::animate(int time) {

}
void Enemy::draw() {
	glPushMatrix();
		this->applySkinMaterial();

		glTranslated(this->x, this->y, this->z);		
		glRotated(this->rotated, 0, 1, 0);

		//Draw Feet
		glPushMatrix();
			glTranslated(0, 0, footSize * 0.75);
			glutSolidCube(footSize);
		glPopMatrix();

		glPushMatrix();
			glTranslated(0, 0, footSize * -0.75);
			glutSolidCube(footSize);
		glPopMatrix();

		//Draw body
		glTranslated(0, footSize / 2.0, 0);

		glPushMatrix();
			glScaled(1, bodyLength, 1);
			glTranslated(0, bodyLength / 2.0, 0);
			
			glutSolidCube(bodySize);
		glPopMatrix();

		//Draw head
		glTranslated(0, bodyLength * 4.0 , 0);

		glutSolidCube(headSize);

		//Draw face
		glTranslated(headSize / 2.0, 0, 0);

		this->applyFaceMaterial();
		glPushMatrix();
			glTranslated(0, headSize / 4.0, headSize / 4.0);
			glutSolidCube(0.5);
		glPopMatrix();

		glPushMatrix();
			glTranslated(0, headSize / 4.0, -headSize / 4.0);
			glutSolidCube(0.5);
		glPopMatrix();

		glPushMatrix();
			glScaled(1, 1, headSize / 1.0);
			glutSolidCube(0.5);
		glPopMatrix();
	glPopMatrix();
}

Enemy::Enemy() :x(0), y(0), z(0), rotated(0) {}