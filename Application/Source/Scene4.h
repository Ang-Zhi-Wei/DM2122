#ifndef SCENE_4_H
#define SCENE_4_H
#include "Scene.h"
#include "Mtx44.h"
#include "Application.h"
#include "Camera.h"
#include "Mesh.h"
#include "MeshBuilder.h"
class Scene4 : public Scene
{
public:
	Scene4();
	~Scene4();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	enum GEOMETRY_TYPE
	{
		GEO_AXES = 0,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_RING,
		GEO_HEMISPHERE,
		GEO_SPHERE,
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
	Camera camera;
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Mesh* meshList[NUM_GEOMETRY];
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