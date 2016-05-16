#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

#ifdef _WIN32
#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include "gl/glut.h"
#elif __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/Gl.h>
#include <GLUT/GLUT.h>
#endif

class SpaceObject {
private:
	SpaceObject* parent;
	GLdouble x;
	GLdouble y;
	GLdouble z;
	GLdouble orbitRadiusX;
	GLdouble orbitRadiusY;
	GLdouble orbitRadiusZ;
	GLdouble orbitSpeed;
	GLdouble rotate;
	GLdouble rotateSpeed;
	GLdouble rotateVectorX;
	GLdouble rotateVectorY;
	GLdouble rotateVectorZ;
	GLdouble scale;
	GLdouble radius;
	GLint slices;
	GLint stacks;
	long long time;
	bool isAnimating;

public:
	~SpaceObject();
	SpaceObject();
	void operator=(SpaceObject&);

	void setX(GLdouble);
	void setY(GLdouble);
	void setZ(GLdouble);
	void setParent(SpaceObject*);
	void setRotate(GLdouble);
	void setRotateVectorX(GLdouble);
	void setRotateVectorY(GLdouble);
	void setRotateVectorZ(GLdouble);
	void setOrbitRadiusX(GLdouble);
	void setOrbitRadiusY(GLdouble);
	void setOrbitRadiusZ(GLdouble);
	void setOrbitSpeed(GLdouble);
	void setScale(GLdouble);
	void setRadius(GLdouble);
	void setSlices(GLint);
	void setStacks(GLint);
	GLdouble getX();
	GLdouble getY();
	GLdouble getZ();
	GLdouble getRotate();
	GLdouble getRotateVectorX();
	GLdouble getRotateVectorY();
	GLdouble getRotateVectorZ();
	GLdouble getOrbitRadiusX();
	GLdouble getOrbitRadiusY();
	GLdouble getOrbitRadiusZ();
	GLdouble getOrbitSpeed();
	GLdouble getScale();
	GLdouble getRadius();
	GLint getSlices();
	GLint getStacks();
	void animate();
	void toggleOrbit();
	void draw();
};
#endif