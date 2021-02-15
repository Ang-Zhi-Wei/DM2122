#include "CameraSP2.h"
#include "Application.h"
#include "Mtx44.h"

CameraSP2::CameraSP2()
{
}

CameraSP2::~CameraSP2()
{
}

void CameraSP2::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	defaultview=view = (target - position).Normalized();
	right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	viewTarget = (0,0,0);
	rawTarget = pos;
	Application::SetCursorPos(960, 540);
	offsetX = 0;
	boundX1 = 0;
	boundX2 = 300;
	boundZ1 = 0;
	boundZ2 = 300;
}

void CameraSP2::Update(double dt)
{
	static const float CAMERA_SPEED = 10.f;
	static const float ZOOM_SPEED = 20.f;
	//static const float rotational_speed = 45.0f;
	
	static const float viewY = 0.9f;
	if (mousePosX > 1900)
	{
		Application::SetCursorPos(960, mousePosY);
		offsetX += 940;
	}
	else if (mousePosX < 20)
	{
		Application::SetCursorPos(960, mousePosY);
		offsetX -= 940;
		//something i added
	}

	Application::GetCursorPos(&mousePosX, &mousePosY);
	viewTarget.x = -1 * sin(Math::DegreeToRadian((mousePosX + offsetX) * (3.0f / 16)));
	viewTarget.z = cos(Math::DegreeToRadian((mousePosX + offsetX) * (3.0f / 16)));
	viewTarget.y = viewY * cos(Math::DegreeToRadian((mousePosY) * (1.0f / 6)));
	target = rawTarget + viewTarget;
	view = (target - position).Normalized();
	
	up = defaultUp;
	right = view.Cross(up);
	up = right.Cross(view).Normalized();

	if (Application::IsKeyPressed('W'))
	{
		
		position.x += view.x * CAMERA_SPEED * dt;
		position.z += view.z * CAMERA_SPEED * dt;
		rawTarget.x += view.x * CAMERA_SPEED * dt;
		rawTarget.z += view.z * CAMERA_SPEED * dt;
		if ((position.x < boundX1) || (position.x > boundX2)||(position.z < boundZ1) || (position.z > boundZ2)) {
			position.x -= view.x * CAMERA_SPEED * dt;
			position.z -= view.z * CAMERA_SPEED * dt;
			rawTarget.x -= view.x * CAMERA_SPEED * dt;
			rawTarget.z -= view.z * CAMERA_SPEED * dt;
		}
		target = rawTarget + viewTarget;
	}
	if (Application::IsKeyPressed('A'))
	{
		position.x -= right.x * CAMERA_SPEED * dt;
		position.z -= right.z * CAMERA_SPEED * dt;
		rawTarget.x -= right.x * CAMERA_SPEED * dt;
		rawTarget.z -= right.z * CAMERA_SPEED * dt;
		if ((position.x < boundX1) || (position.x > boundX2) || (position.z < boundZ1) || (position.z > boundZ2)) {
			position.x += right.x * CAMERA_SPEED * dt;
			position.z += right.z * CAMERA_SPEED * dt;
			rawTarget.x += right.x * CAMERA_SPEED * dt;
			rawTarget.z += right.z * CAMERA_SPEED * dt;
		}
		target = rawTarget + viewTarget;
	}
	if (Application::IsKeyPressed('S'))
	{
		position.x -= view.x * CAMERA_SPEED * dt;
		position.z -= view.z * CAMERA_SPEED * dt;
		rawTarget.x -= view.x * CAMERA_SPEED * dt;
		rawTarget.z -= view.z * CAMERA_SPEED * dt;
		if ((position.x < boundX1) || (position.x > boundX2) || (position.z < boundZ1) || (position.z > boundZ2)) {
			position.x += view.x * CAMERA_SPEED * dt;
			position.z += view.z * CAMERA_SPEED * dt;
			rawTarget.x += view.x * CAMERA_SPEED * dt;
			rawTarget.z += view.z * CAMERA_SPEED * dt;
		}
		target = rawTarget + viewTarget;
	}
	if (Application::IsKeyPressed('D'))
	{
		position.x += right.x * CAMERA_SPEED * dt;
		position.z += right.z * CAMERA_SPEED * dt;
		rawTarget.x += right.x * CAMERA_SPEED * dt;
		rawTarget.z += right.z * CAMERA_SPEED * dt;
		if ((position.x < boundX1) || (position.x > boundX2) || (position.z < boundZ1) || (position.z > boundZ2)) {
			position.x -= right.x * CAMERA_SPEED * dt;
			position.z -= right.z * CAMERA_SPEED * dt;
			rawTarget.x -= right.x * CAMERA_SPEED * dt;
			rawTarget.z -= right.z * CAMERA_SPEED * dt;
		}
		target = rawTarget + viewTarget;
	}

	
}

void CameraSP2::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}
//param X1 smaller than x2,z1 smaller than z2
void CameraSP2::SetBounds(float X1, float X2, float Z1, float Z2)
{
	boundX1 = X1;
	boundX2 = X2;
	boundZ1 = Z1;
	boundZ2 = Z2;
}






