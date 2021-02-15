#ifndef CAMERA_SP2_H
#define CAMERA_SP2_H

#include "Camera.h"
#include "ColliderBox.h"
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
	ColliderBox Checker;
	double mousePosX, mousePosY;
	double offsetX, offsetY;
	Vector3 forwardVector;
	void setchecker(ColliderBox Checker);
    float yaw;
	float boundX1;
	float boundX2;
	float boundZ1;
	float boundZ2;
	//Values for axe
	float AxeYaw;
	Vector3 AxePosition;
	Vector3 Skullposition;
	bool collisionstatus;
	CameraSP2();
	~CameraSP2();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();
	void SetBounds(float X1, float X2, float Z1, float Z2);
};

#endif