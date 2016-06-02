#ifndef LIB_H
#define LIB_H
#include <ctime>
#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include "gl/glut.h"

const double pi = 3.1415926535897932384626433832795028841971;
const double gravity = 45.2;
const double air_friction = 0.47;
const double ball_mass = 0.453592;
const double robot_force = 70.0;
const double max_angle_finger = 30.0;
const double max_angle_hand = 90.0;
const double max_angle_elbow = 100.0;
const double max_angle = 80.0;
const int screenWidth = 800, screenHeight = 600;
const float worldWidth = 800, worldHeight = 600, degreeSegement = 40.0;
const GLdouble cameraSensitivity = 0.04;
const unsigned int enemyHitPoints = 2, robotHitPoints = 10;
#endif // !LIB_H