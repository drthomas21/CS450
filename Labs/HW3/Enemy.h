#ifndef ENEMY_H
#define ENEMY_H

#ifndef LIB_H
#include "lib.h"
#endif

class Enemy {
private:
	unsigned int hitCount;
	GLdouble rotated;
	GLdouble x;
	GLdouble y;
	GLdouble z;

	void applySkinMaterial();
	void applyFaceMaterial();

public:
	GLdouble getX();
	GLdouble getY();
	GLdouble getZ();
	GLdouble getFootSize();
	GLdouble getBodyLength();
	GLdouble getHeadSize();
	GLdouble getRotated();

	bool isAlive();

	void setX(GLdouble);
	void setY(GLdouble);
	void setZ(GLdouble);
	void setRotated(GLdouble);
	void wasHit();
	void reset();
	void animate(int);
	void draw();

	Enemy();
};
#endif