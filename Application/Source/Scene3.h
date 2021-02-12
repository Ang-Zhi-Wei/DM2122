#ifndef SCENE_3_H
#define SCENE_3_H
#include "Scene.h"
#include "Mtx44.h"
class Scene3 : public Scene
{
public:
	Scene3();
	~Scene3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		GEO_TRIANGLE_2=1,
		GEO_TRIANGLE_3=2,
		GEO_TRIANGLE_4=3,
		GEO_TRIANGLE_5=4,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};
	enum Diagonal_Direction {
		up_left=0,
		up_right=1,
		down_left=2,
		down_right=3,
		direction_num
	};
private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;
	float rotateAngle;
	double translateX[15];
	double translateY[15];
	float scaleAll;
	int direction;
	float thunder;
};

#endif