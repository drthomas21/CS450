#ifndef ROOM_H
#define ROOM_H

#include <time.h>
#include <chrono>
#include "lib.h"
#include "Point3.h"
#include "Vector3.h"

#include "Robot.h"
#include "Enemy.h"
#include "camera.h"

class Room {
private:
	std::chrono::system_clock::time_point time;
	size_t enemyCount;
	GLdouble width;
	GLdouble height;
	GLdouble depth;
	GLdouble cameraX;
	GLdouble cameraY;
	GLdouble cameraZ;
	Enemy *enemies;
	Robot robot;
	Camera camera;

	void moveEnemies(GLdouble);
	void faceRobot(Enemy*);

public:
	GLdouble getWidth();
	GLdouble getHeight();
	GLdouble getDepth();
	Enemy* getEnemy(size_t);
	Robot* getRobot();
	Camera* getCamera();

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