#include "Camera.h"
#include <cmath>
int phi = 10;
int theta = 10;
#define PI 3.14159265
#define Rad PI/180
int R = 10;
/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera::Camera()
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera::~Camera()
{
}

/******************************************************************************/
/*!
\brief
Initialize camera

\param pos - position of camera
\param target - where the camera is looking at
\param up - up vector of camera
*/
/******************************************************************************/
void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;

}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera::Reset()
{
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera::Update(double dt)
{
	////up
	//if (Application::IsKeyPressed('I')) {
	//	phi += 1.f;
	//}
	////left
	//if (Application::IsKeyPressed('J')) {
	//	theta -= 1.f;
	//}
	////down
	//if (Application::IsKeyPressed('K')) {
	//	phi -= 1.f;
	//}
	////right
	//if (Application::IsKeyPressed('L')) {
	//	theta += 1.f;
	//}
	////Zoom in
	//if (Application::IsKeyPressed('N')) {
	//	if (R > 1) {
	//		R -= 1.f;
	//	}
	//	
	//}
	////Zoom out
	//if (Application::IsKeyPressed('M')) {
	//	R += 1.f;
	//}
	//this->position.x = R * cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));
	//this->position.y = R * sin(Math::DegreeToRadian(phi));
	//this->position.z = R * cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));
	//	
}