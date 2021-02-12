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
	view = (target - position).Normalized();
	right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	yaw = 0;
	boundX1 = -35;
	boundX2 = 40;
	boundZ1 = -280;
	boundZ2 = 280;
	AxeYaw = 0;
	AxePosition = target + view;
	AxePosition = target + right;
	Skullposition = target;
}

void CameraSP2::Update(double dt)
{
	static const float CAMERA_SPEED = 0.5f;
	static const float ZOOM_SPEED = 20.f;
	static const float rotational_speed = 45.0f;
	if (Application::IsKeyPressed('W'))
	{
		position += view * CAMERA_SPEED;
		target += view * CAMERA_SPEED;
		if (!((position.x > boundX1 && position.x < boundX2) && (position.z > boundZ1 && position.z < boundZ2))) {
			position -= view * CAMERA_SPEED;
			target -= view * CAMERA_SPEED;
		}
	}
	if (Application::IsKeyPressed('A'))
	{
		yaw = rotational_speed * static_cast<float>(dt);
		AxeYaw += rotational_speed * static_cast<float>(dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
	}
	if (Application::IsKeyPressed('S'))
	{
	
		position -= view * CAMERA_SPEED;
		target -= view * CAMERA_SPEED;
		if (!((position.x > boundX1 && position.x < boundX2) && (position.z > boundZ1 && position.z < boundZ2))) {
			position += view * CAMERA_SPEED;
			target += view * CAMERA_SPEED;
		}
	}
	if (Application::IsKeyPressed('D'))
	{
		yaw = -rotational_speed * static_cast<float>(dt);
		AxeYaw -= rotational_speed * static_cast<float>(dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;

	}
	view = (target - position).Normalized();
	right = view.Cross(up);
	up = defaultUp = right.Cross(view).Normalized();
	Mtx44 scaleview;
	scaleview.SetToScale(5, 1, 5);
	Mtx44 scaleright;
	scaleright.SetToScale(1.5, 1, 1.5);
	AxePosition = target + (scaleview*view)+(scaleright*right);
	Skullposition = target +(scaleview*view);
}

void CameraSP2::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

void CameraSP2::SetBounds(float X1, float X2, float Z1, float Z2)
{
	boundX1 = X1;
	boundX2 = X2;
	boundZ1 = Z1;
	boundZ2 = Z2;
}






