#ifndef LIB_H
#define LIB_H

#include <windows.h>
#include <gl/Gl.h>
#include <gl/glu.h>
#include "gl/glut.h"

#include <math.h>
#include <time.h>

#define PI 3.14159265
#define GRAVITY 254.8
#define BULLET_VELOCITY 500.0
#define TARGET_VELOCITY 220.0

#define DEBUG_ENABLE_BULLET true
#define DEBUG_ENABLE_TARGET true
#define DEBUG_ENABLE_BULLET_PATH true

struct GLintPoint2D {
	GLint x, y;
};

struct GLfloatPoint2D {
	GLfloat x, y;
};
#endif
