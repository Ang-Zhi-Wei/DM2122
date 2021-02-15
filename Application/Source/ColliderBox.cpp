#include "ColliderBox.h"

ColliderBox::ColliderBox()
{
	xlength = 3;
	ylength = 3;
	zlength = 3;
}



bool ColliderBox::iscollide(Vector3 cameraposition)
{
	return false;
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
