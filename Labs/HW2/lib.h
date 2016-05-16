#ifndef LIB_H
#define LIB_H

#ifdef _WIN32
	#include <windows.h>
	#include <gl/Gl.h>
	#include <gl/glu.h>
	#include "gl/glut.h"
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#endif

#define PI 3.14
#endif