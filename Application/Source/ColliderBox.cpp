#include "ColliderBox.h"

ColliderBox::ColliderBox()
{
	//default length
	xlength = 3;
	ylength = 3;
	zlength = 3;
	active = true;
}




bool ColliderBox::iscollide(Vector3 cameraposition)
{
	if ((cameraposition.x > (-xlength / 2)+Position.x && cameraposition.x < (xlength / 2)+Position.x) && ((cameraposition.z > (-zlength / 2)+Position.z && cameraposition.z < (zlength / 2)+Position.z))) {
		return true;
	}
	else {
		return false;
	}
}

void ColliderBox::Setposition(Vector3 Position)
{
	this->Position = Position;
}

void ColliderBox::setlength(double xlength, double ylength, double zlength)
{
	this->xlength = xlength;
	this->ylength = ylength;
	this->zlength = zlength;
}

Vector3 ColliderBox::getPosition()
{
	return Position;
}

double ColliderBox::getxlength()
{
	return xlength;
}

double ColliderBox::getylength()
{
	return ylength;
}

double ColliderBox::getzlength()
{
	return zlength;
}

void ColliderBox::setactive(bool active)
{
	this->active = active;
}

bool ColliderBox::getactive()
{
	return active;
}
