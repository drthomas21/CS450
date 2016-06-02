#ifndef ROOM_H
#define ROOM_H

#include <time.h>
#include <chrono>
#ifndef LIB_H
#include "lib.h"
#endif
#include "Point3.h"
#include "Vector3.h"

#include "Robot.h"
#include "Enemy.h"
#include "camera.h"

class Room {
private:
	std::chrono::system_clock::time_point time;
	std::chrono::system_clock::time_point timeSegment;
	size_t enemyCount;
	GLdouble width;
	GLdouble height;
	GLdouble depth;
	GLdouble cameraX;
	GLdouble cameraY;
	GLdouble cameraZ;
	GLdouble cameraOffsetX;
	GLdouble cameraOffsetY;
	Enemy *enemies;
	Robot robot;
	Camera camera;

	void moveEnemy(Enemy*, GLdouble);
	void faceRobot(Enemy*);
	bool isSpotClear(GLdouble, GLdouble, Enemy*);
	bool isSpotClear(GLdouble, GLdouble, Robot*);
public:
	GLdouble getWidth();
	GLdouble getHeight();
	GLdouble getDepth();
	Enemy* getEnemy(size_t);
	Robot* getRobot();
	Camera* getCamera();

	unsigned long getTime();

	void setWidth(GLdouble);
	void setHeight(GLdouble);
	void setDepth(GLdouble);
	void shiftRobotLeft();
	void shiftRobotRight();
	void updateCamera(GLdouble, GLdouble);
	void updateCamera();

	void draw();
	void animate();

	Room();
	~Room();
};
#endif