#pragma once
#include "Vector3.h"
enum CubeVertices {
	v1,
	v2,
	v3,
	v4,
	v5,
	v6,
	v7,
	v8,
	num_of_vertices
};
struct Position
{
	float x, y, z;
	Position(float x = 0, float y = 0, float z = 0) {
		Set(x, y,
			z);
	}
	void Set(float x, float y, float z) {
		this->x = x; this->y = y;
		this->z = z;
	}
	void Set(int vertices) {
		switch (vertices) {
		case v1:
			x = -0.5;
			y = 0.5;
			z = 0.5;
			break;
		case v2:
			x = 0.5;
			y = 0.5;
			z = 0.5;
			break;
		case v3:
			x = -0.5;
			y = -0.5;
			z = 0.5;
			break;
		case v4:
			x = 0.5;
			y = -0.5;
			z = 0.5;
			break;
		case v5:
			x = -0.5;
			y = 0.5;
			z = -0.5;
			break;
		case v6:
			x = 0.5;
			y = 0.5;
			z = -0.5;
			break;
		case v7:
			x = -0.5;
			y = -0.5;
			z = -0.5;
			break;
		case v8:
			x = 0.5;
			y = -0.5;
			z = -0.5;
			break;
		}
	}
};
enum ColorType {
	Red,
	Blue,
	Pink,
	Orange,
	Purple,
	Yellow,
	Green,
	Gray,
	Brown,
	Silver,
    Wheat,
	Black,
	Crimson,
	White,
	Num_color
};
struct Normal {
	float x, y, z;
};
struct TexCoord
{
	float u, v;
	TexCoord(float u = 0, float v = 0) { Set(u, v); }
	void Set(float u, float v) { this->u = u; this->v = v; }
};
struct Color
{
	float r, g, b;
	Color(float r = 1, float g = 1, float b = 1) { Set(r, g, b); }
	void Set(float rvalue, float gvalue, float bvalue) {
		r = rvalue; g = gvalue;
		b = bvalue;
	}
	void Set(int color) {
		switch (color) {
		case Red:
			r = 1.0f;
			g = 0.f;
			b = 0.f;
			break;
		case Blue:
			r = 0.f;
			g = 1.f;
			b = 1.f;
			break;
		case Pink:
			r = 1.000f;
			g = 0.753f;
			b = 0.796f;
			break;
		case Orange:
			r = 1.000f;
			g = 0.647f;
			b = 0.f;
			break;
		case Purple:
			r = 0.502f;
			g = 0.f;
			b = 0.502f;
			break;
		case Yellow:
			r = 1.f;
			g = 1.f;
			b = 0.f;
			break;
		case Green:
			r = 0.000f;
			g = 0.502f;
			b = 0.000f;
			break;
		case Gray:
			r = 0.412f;
			g = 0.412f;
			b = 0.412f;
			break;
		case Brown:
			r = 0.545f;
			g = 0.271f;
			b = 0.075f;
			break;
		case Silver:
			r = 0.753f;
			g = 0.753f;
			b = 0.753f;
			break;
		case Wheat:
			r = 0.961f;
			g = 0.871f;
			b = 0.702f;
			break;
		case Black:
			r = 0.f;
			g = 0.f;
			b = 0.f;
			break;
		case Crimson:
			r = 0.863f;
			g = 0.078f;
			b = 0.235f;
			break;
		case White:
			r = 1.f;
			g = 1.f;
			b = 1.f;
			break;
		}
	}
};
struct Vertex
{
	Position pos;
	Color color;
	Vector3 normal;
	TexCoord texCoord;
};
