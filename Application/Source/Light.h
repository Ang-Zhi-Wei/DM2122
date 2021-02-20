#pragma once
#include "Vertex.h"
struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	Light() {
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
	}
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;

};
