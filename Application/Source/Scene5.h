#ifndef SCENE_5_H
#define SCENE_5_H
#include "Scene.h"
#include "Mtx44.h"
#include "Application.h"
#include "Camera.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
class Scene5 : public Scene
{
public:
	Scene5();
	~Scene5();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	enum GEOMETRY_TYPE
	{
		GEO_AXES = 0,
		Sun=1,
		Planet1=2,
		Planet2=3,
		Planet3=4,
		Planet4=5,
		Planet5=6,
		Ring=7,
		Moon=8,
		Planet6=9,
		Moon2=10,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};
private:
	Camera camera;
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Mesh* meshList[NUM_GEOMETRY];
	//Mtx44 translate, rotate, scale;
	//Mtx44 model;
	//Mtx44 view;
	//Mtx44 projection;
	//Mtx44 MVP;
	float rotateAngle;
	double translateX;
	double translateY;
	float scaleAll;
	MS modelStack, viewStack, projectionStack;
};

#endif