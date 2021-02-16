#include "Locker.h"

Locker::Locker()
{
	Position = (0, 0, 0);
	hidden = false;
}

void Locker::setpos(Vector3 Position)
{
	this->Position = Position;
}

Vector3 Locker::getpos()
{
	return Position;
}



bool Locker::status(Vector3 Point,Vector3 cameraview,bool fpressed)
{
	bool condition1;//length is less than 20(can change this anytime)
	bool condition2;//Player facing the locker(can change the value)
	bool condition3=fpressed;//F button is pressed
	float tempy = 4.5;
	Position.y += tempy;
	Vector3 A = Point - Position;
	Vector3 B = cameraview;
	if (A.Length()<20)
	{
		condition1 = true;
	}
	else {
		condition1 = false;
	}
	if (Math::RadianToDegree(acos(A.Dot(B)/(A.Length()*B.Length())))<20) {
		condition2 = true;
	}
	else {
		condition2 = false;
	}
	Position.y -= tempy;
	return(condition1 && condition2 && condition3);
}

void Locker::Sethidden(bool hidden)
{
	this->hidden = hidden;
}

bool Locker::gethidden()
{
	return hidden;
}

