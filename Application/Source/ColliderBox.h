#pragma once
#include "Vector3.h"
class ColliderBox
{
public:
	ColliderBox();
	
	bool iscollide(Vector3 cameraposition);
	void Setposition(Vector3 Position);
	void setlength(double xlength,double ylength,double zlength);
	Vector3 getPosition();
	double getxlength();
	double getylength();
	double getzlength();
private:
	double xlength;
	double ylength;
	double zlength;
	Vector3 Position;
};

