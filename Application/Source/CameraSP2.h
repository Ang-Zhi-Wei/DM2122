#ifndef CAMERA_SP2_H
#define CAMERA_SP2_H

#include "Camera.h"
#include "ColliderBox.h"
#include "Locker.h"
#include <vector>

class CameraSP2 : public Camera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 view;
	Vector3 right;
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 defaultview;
	Vector3 rawTarget, viewTarget;
	Vector3 newTarget, lockedTarget;

	std::vector<ColliderBox>Checker;

	double mousePosX, mousePosY;
	double offsetX;
	double playerStamina, cooldown;
	
   
	float boundX1;
	float boundX2;
	float boundZ1;
	float boundZ2;
	bool can_move;
	bool slowed;
	bool movement;
	CameraSP2();
	~CameraSP2();
	

	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();
	void setchecker(std::vector<ColliderBox>Checker);
	void SetBounds(float X1, float X2, float Z1, float Z2);
	void teleport(Vector3 position);
	void Setslow(bool slow);
	void facefrontlocker(Vector3 lockerview);
};

#endif