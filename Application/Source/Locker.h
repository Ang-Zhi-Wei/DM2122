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
private:
	Vector3 Position;
	bool hidden;
};

