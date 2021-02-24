#include "Locker.h"

Locker::Locker()
{
	Position = (0.f, 0.f, 0.f);
	direction = (0, 0, 5);
	hidden = false;
	yaw = 0;
}

void Locker::setpos(Vector3 PositionVector)
{
	Position = PositionVector;
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

void Locker::Sethidden(bool hiddentype)
{
	hidden = hiddentype;
}

bool Locker::gethidden()
{
	return hidden;
}

void Locker::setyaw(float yaw)
{
	Mtx44 rotation;
	rotation.SetToRotation(yaw, 0, 1, 0);
	direction = rotation * direction;
	this->yaw = yaw;
}

float Locker::getyaw()
{
	return yaw;
}

Vector3 Locker::getdirection()
{
	return direction;
}

Vector3 Locker::getfront()
{
	return (front=Position+direction);
}



