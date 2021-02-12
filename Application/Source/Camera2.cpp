#include "Camera2.h"
#include "Application.h"
#include "Mtx44.h"

Camera2::Camera2()
{
}

Camera2::~Camera2()
{
}

void Camera2::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	Temp.x = 0;
	Temp.y = 0;
	Temp.z = 0;
	jump = false;
	spell = false;
	yaw = 0;
	horizontalrotation = 0;
}

void Camera2::Update(double dt)
{
	static const float CAMERA_SPEED = 45.f;
	static const float ZOOM_SPEED = 20.f;
	if (Application::IsKeyPressed('A'))
	{
		yaw = -CAMERA_SPEED * static_cast<float>(dt);
		Mtx44 rotation;
		horizontalrotation += -CAMERA_SPEED * static_cast<float>(dt);
		rotation.SetToRotation(yaw, 0, 1, 0);
		defaultPosition = rotation * defaultPosition;
		position = defaultPosition + Temp;
		up = rotation * up;
		
	}
	if (Application::IsKeyPressed('D'))
	{
		yaw = CAMERA_SPEED * static_cast<float>(dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		horizontalrotation -= -CAMERA_SPEED * static_cast<float>(dt);
		defaultPosition = rotation * defaultPosition;
		position = defaultPosition+Temp;
		up = rotation * up;
	}
	if (Application::IsKeyPressed('W'))
	{
		float pitch = -CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		defaultPosition = rotation * defaultPosition;
		position = defaultPosition+Temp;
	}
	if (Application::IsKeyPressed('S'))
	{
		float pitch = CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		defaultPosition = rotation * defaultPosition;
		position = defaultPosition+Temp;
	}
	//movement
	if (spell == false && jump==false && doublejump==false) {
		if (horizontalrotation<22.5 && horizontalrotation>-22.5) {
			if (Application::IsKeyPressed('I')) {
				target.z += float(1.5f * dt);
				position.z += float(1.5f * dt);
				Temp.z += float(1.5f * dt);
			}
			if (Application::IsKeyPressed('K')) {
				target.z -= float(1.5f * dt);
				position.z -= float(1.5f * dt);
				Temp.z -= float(1.5f * dt);
			}
			if (Application::IsKeyPressed('J')) {
				target.x += float(1.5f * dt);
				position.x += float(1.5f * dt);
				Temp.x += float(1.5f * dt);
			}
			if (Application::IsKeyPressed('L')) {
				target.x -= float(1.5f * dt);
				position.x -= float(1.5f * dt);
				Temp.x -= float(1.5f * dt);
			}
		}
		else if (horizontalrotation > -67.5 && horizontalrotation < -22.5) {
			if (Application::IsKeyPressed('I') && Application::IsKeyPressed('J')) {
				target.z += float(1.5f * dt);
				position.z += float(1.5f * dt);
				Temp.z += float(1.5f * dt);
			}
			else if (Application::IsKeyPressed('I') && Application::IsKeyPressed('L')) {
				target.x -= float(1.5f * dt);
				position.x -= float(1.5f * dt);
				Temp.x -= float(1.5f * dt);
			}
			else if (Application::IsKeyPressed('K') && Application::IsKeyPressed('J')) {
				target.x += float(1.5f * dt);
				position.x += float(1.5f * dt);
				Temp.x += float(1.5f * dt);
			}
			else if (Application::IsKeyPressed('K') && Application::IsKeyPressed('L')) {
				target.z -= float(1.5f * dt);
				position.z -= float(1.5f * dt);
				Temp.z -= float(1.5f * dt);
			}
			else if (Application::IsKeyPressed('I')) {
				target.z += float(1.5f * dt);
				position.z += float(1.5f * dt);
				Temp.z += float(1.5f * dt);
				target.x -= float(1.5f * dt);
				position.x -= float(1.5f * dt);
				Temp.x -= float(1.5f * dt);
			}
			else if (Application::IsKeyPressed('J')) {
				target.z += float(1.5f * dt);
				position.z += float(1.5f * dt);
				Temp.z += float(1.5f * dt);
				target.x += float(1.5f * dt);
				position.x += float(1.5f * dt);
				Temp.x += float(1.5f * dt);
			}
			else if (Application::IsKeyPressed('K')) {
				target.z -= float(1.5f * dt);
				position.z -= float(1.5f * dt);
				Temp.z -= float(1.5f * dt);
				target.x += float(1.5f * dt);
				position.x += float(1.5f * dt);
				Temp.x += float(1.5f * dt);
			}
			else if (Application::IsKeyPressed('L')) {
				target.z -= float(1.5f * dt);
				position.z -= float(1.5f * dt);
				Temp.z -= float(1.5f * dt);
				target.x -= float(1.5f * dt);
				position.x -= float(1.5f * dt);
				Temp.x -= float(1.5f * dt);
			}
		}
		else if (horizontalrotation > -112.5 && horizontalrotation < -67.5) {
			if (Application::IsKeyPressed('J')) {
				target.z += float(1.5f * dt);
				position.z += float(1.5f * dt);
				Temp.z += float(1.5f * dt);
			}
			if (Application::IsKeyPressed('L')) {
				target.z -= float(1.5f * dt);
				position.z -= float(1.5f * dt);
				Temp.z -= float(1.5f * dt);
			}
			if (Application::IsKeyPressed('K')) {
				target.x += float(1.5f * dt);
				position.x += float(1.5f * dt);
				Temp.x += float(1.5f * dt);
			}
			if (Application::IsKeyPressed('I')) {
				target.x -= float(1.5f * dt);
				position.x -= float(1.5f * dt);
				Temp.x -= float(1.5f * dt);
			}
		}
		else if (horizontalrotation > -157.5 && horizontalrotation < -112.5) {
			if (Application::IsKeyPressed('K') && Application::IsKeyPressed('J')) {
				target.z += float(1.5f * dt);
				position.z += float(1.5f * dt);
				Temp.z += float(1.5f * dt);
			}
			else if (Application::IsKeyPressed('I') && Application::IsKeyPressed('J')) {
				target.x -= float(1.5f * dt);
				position.x -= float(1.5f * dt);
				Temp.x -= float(1.5f * dt);
			}
			else if (Application::IsKeyPressed('K') && Application::IsKeyPressed('L')) {
				target.x += float(1.5f * dt);
				position.x += float(1.5f * dt);
				Temp.x += float(1.5f * dt);
			}
			else if (Application::IsKeyPressed('I') && Application::IsKeyPressed('L')) {
				target.z -= float(1.5f * dt);
				position.z -= float(1.5f * dt);
				Temp.z -= float(1.5f * dt);
			}
			else if (Application::IsKeyPressed('J')) {
				target.z += float(1.5f * dt);
				position.z += float(1.5f * dt);
				Temp.z += float(1.5f * dt);
				target.x -= float(1.5f * dt);
				position.x -= float(1.5f * dt);
				Temp.x -= float(1.5f * dt);
			}
			else if (Application::IsKeyPressed('K')) {
				target.z += float(1.5f * dt);
				position.z += float(1.5f * dt);
				Temp.z += float(1.5f * dt);
				target.x += float(1.5f * dt);
				position.x += float(1.5f * dt);
				Temp.x += float(1.5f * dt);
			}
			else if (Application::IsKeyPressed('L')) {
				target.z -= float(1.5f * dt);
				position.z -= float(1.5f * dt);
				Temp.z -= float(1.5f * dt);
				target.x += float(1.5f * dt);
				position.x += float(1.5f * dt);
				Temp.x += float(1.5f * dt);
			}
			else if (Application::IsKeyPressed('I')) {
				target.z -= float(1.5f * dt);
				position.z -= float(1.5f * dt);
				Temp.z -= float(1.5f * dt);
				target.x -= float(1.5f * dt);
				position.x -= float(1.5f * dt);
				Temp.x -= float(1.5f * dt);
			}
		}
		else if ((horizontalrotation > 157.5 && horizontalrotation <= 180) || (horizontalrotation > -157.5 && horizontalrotation <= -180)) {
			if (Application::IsKeyPressed('K')) {
				target.z += float(1.5f * dt);
				position.z += float(1.5f * dt);
				Temp.z += float(1.5f * dt);
			}
			if (Application::IsKeyPressed('I')) {
				target.z -= float(1.5f * dt);
				position.z -= float(1.5f * dt);
				Temp.z -= float(1.5f * dt);
			}
			if (Application::IsKeyPressed('L')) {
				target.x += float(1.5f * dt);
				position.x += float(1.5f * dt);
				Temp.x += float(1.5f * dt);
			}
			if (Application::IsKeyPressed('J')) {
				target.x -= float(1.5f * dt);
				position.x -= float(1.5f * dt);
				Temp.x -= float(1.5f * dt);
			}
		}
		else if (horizontalrotation > 112.5 && horizontalrotation < 157.5) {
		if (Application::IsKeyPressed('K') && Application::IsKeyPressed('L')) {
			target.z += float(1.5f * dt);
			position.z += float(1.5f * dt);
			Temp.z += float(1.5f * dt);
		}
		else if (Application::IsKeyPressed('K') && Application::IsKeyPressed('J')) {
			target.x -= float(1.5f * dt);
			position.x -= float(1.5f * dt);
			Temp.x -= float(1.5f * dt);
		}
		else if (Application::IsKeyPressed('I') && Application::IsKeyPressed('L')) {
			target.x += float(1.5f * dt);
			position.x += float(1.5f * dt);
			Temp.x += float(1.5f * dt);
		}
		else if (Application::IsKeyPressed('I') && Application::IsKeyPressed('J')) {
			target.z -= float(1.5f * dt);
			position.z -= float(1.5f * dt);
			Temp.z -= float(1.5f * dt);
		}
		else if (Application::IsKeyPressed('K')) {
			target.z += float(1.5f * dt);
			position.z += float(1.5f * dt);
			Temp.z += float(1.5f * dt);
			target.x -= float(1.5f * dt);
			position.x -= float(1.5f * dt);
			Temp.x -= float(1.5f * dt);
		}
		else if (Application::IsKeyPressed('L')) {
			target.z += float(1.5f * dt);
			position.z += float(1.5f * dt);
			Temp.z += float(1.5f * dt);
			target.x += float(1.5f * dt);
			position.x += float(1.5f * dt);
			Temp.x += float(1.5f * dt);
		}
		else if (Application::IsKeyPressed('I')) {
			target.z -= float(1.5f * dt);
			position.z -= float(1.5f * dt);
			Temp.z -= float(1.5f * dt);
			target.x += float(1.5f * dt);
			position.x += float(1.5f * dt);
			Temp.x += float(1.5f * dt);
		}
		else if (Application::IsKeyPressed('J')) {
			target.z -= float(1.5f * dt);
			position.z -= float(1.5f * dt);
			Temp.z -= float(1.5f * dt);
			target.x -= float(1.5f * dt);
			position.x -= float(1.5f * dt);
			Temp.x -= float(1.5f * dt);
		}
	}
		else if (horizontalrotation > 67.5 && horizontalrotation < 112.5) {
		if (Application::IsKeyPressed('L')) {
			target.z += float(1.5f * dt);
			position.z += float(1.5f * dt);
			Temp.z += float(1.5f * dt);
		}
		if (Application::IsKeyPressed('J')) {
			target.z -= float(1.5f * dt);
			position.z -= float(1.5f * dt);
			Temp.z -= float(1.5f * dt);
		}
		if (Application::IsKeyPressed('I')) {
			target.x += float(1.5f * dt);
			position.x += float(1.5f * dt);
			Temp.x += float(1.5f * dt);
		}
		if (Application::IsKeyPressed('K')) {
			target.x -= float(1.5f * dt);
			position.x -= float(1.5f * dt);
			Temp.x -= float(1.5f * dt);
		}
	}
		else if (horizontalrotation > 22.5 && horizontalrotation < 67.5) {
		if (Application::IsKeyPressed('I') && Application::IsKeyPressed('L')) {
			target.z += float(1.5f * dt);
			position.z += float(1.5f * dt);
			Temp.z += float(1.5f * dt);
		}
		else if (Application::IsKeyPressed('K') && Application::IsKeyPressed('L')) {
			target.x -= float(1.5f * dt);
			position.x -= float(1.5f * dt);
			Temp.x -= float(1.5f * dt);
		}
		else if (Application::IsKeyPressed('I') && Application::IsKeyPressed('J')) {
			target.x += float(1.5f * dt);
			position.x += float(1.5f * dt);
			Temp.x += float(1.5f * dt);
		}
		else if (Application::IsKeyPressed('K') && Application::IsKeyPressed('J')) {
			target.z -= float(1.5f * dt);
			position.z -= float(1.5f * dt);
			Temp.z -= float(1.5f * dt);
		}
		else if (Application::IsKeyPressed('L')) {
			target.z += float(1.5f * dt);
			position.z += float(1.5f * dt);
			Temp.z += float(1.5f * dt);
			target.x -= float(1.5f * dt);
			position.x -= float(1.5f * dt);
			Temp.x -= float(1.5f * dt);
		}
		else if (Application::IsKeyPressed('I')) {
			target.z += float(1.5f * dt);
			position.z += float(1.5f * dt);
			Temp.z += float(1.5f * dt);
			target.x += float(1.5f * dt);
			position.x += float(1.5f * dt);
			Temp.x += float(1.5f * dt);
		}
		else if (Application::IsKeyPressed('J')) {
			target.z -= float(1.5f * dt);
			position.z -= float(1.5f * dt);
			Temp.z -= float(1.5f * dt);
			target.x += float(1.5f * dt);
			position.x += float(1.5f * dt);
			Temp.x += float(1.5f * dt);
		}
		else if (Application::IsKeyPressed('K')) {
			target.z -= float(1.5f * dt);
			position.z -= float(1.5f * dt);
			Temp.z -= float(1.5f * dt);
			target.x -= float(1.5f * dt);
			position.x -= float(1.5f * dt);
			Temp.x -= float(1.5f * dt);
		}
	}
}
	//Zoom
	if (Application::IsKeyPressed('N'))
	{
		Vector3 view = target - position;
		if (view.Length() > 5) //Prevent the camera from touching the origin
		{
			view.Normalize();
			defaultPosition += view * ZOOM_SPEED * dt;
			position = defaultPosition + Temp;
		}
	}
	if (Application::IsKeyPressed('M'))
	{
		Vector3 view = (target - position).Normalized();
		defaultPosition -= view * ZOOM_SPEED * dt;
		position = defaultPosition + Temp;
	}
	if (Application::IsKeyPressed('R'))
	{
		Reset();
	}
	if (horizontalrotation > 180) {
		horizontalrotation = -179;
	}
	else if (horizontalrotation < -180) {
		horizontalrotation = 179;
	}
}

void Camera2::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	Temp.x = 0;
	Temp.y = 0;
	Temp.z = 0;
}

void Camera2::AnimationStatus(bool jump, bool spell,bool doublejump)
{
	this->jump = jump;
	this->spell = spell;
	this->doublejump = doublejump;
}






