#pragma once
#include "Vertex.h"
struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	Light() {
		type = LIGHT_POINT;
		position = {
			0.5,0.5,0.5
		};
		color = {
			1,1,1
		};
		power = 1.f;
		kC = 1;
		kL = 0.01f;
		kQ = 0.001f;
		cosCutoff = cos(Math::DegreeToRadian(7));
		cosInner = cos(Math::DegreeToRadian(1));
		exponent = 3.f;
	}
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	int type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;

};
