#ifndef CAMERA_H
#define CAMERA_H

#ifndef POINT3_H
#include "Point3.h"
#endif
#ifndef VECTOR3_H
#include "Vector3.h"
#endif

class Camera {
private:
	Point3 eye;
	Vector3 u, v, n;
	double viewAngle, aspect, nearDist, farDist; // view volume shape
	void setModelViewMatrix(); // tell OpenGL where the camera is	

public:
	Camera(); // default constructor
	~Camera();
	void set(Point3, Point3, Vector3); // like gluLookAt()	
	void slide(float, float, float); // slide it	
	void roll(float); // roll it

	void pitch(float); // increase pitch
	void yaw(float); // yaw it
	void setShape(float, float, float, float);
};

#endif
