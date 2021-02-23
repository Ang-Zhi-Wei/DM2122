#pragma once
#include "Vector3.h"
#include <cmath>
#include "Mtx44.h"
class Locker
{
public:
	Locker();
	void setpos(Vector3 Position);
	Vector3 getpos();
	bool status(Vector3 Point,Vector3 cameraview,bool fpressed);
	void Sethidden(bool hidden);
	bool gethidden();
	void setyaw(float yaw);
	float getyaw();
	Vector3 getdirection();
	Vector3 getfront();
private:
	Vector3 Position;
	Vector3 direction;
	Vector3 front;
	float yaw;
	bool hidden;
};

