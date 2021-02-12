#ifndef SCENE_Light_H
#define SCENE_Light_H
#include "Scene.h"
#include "Mtx44.h"
#include "Application.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
class SceneLight : public Scene
{
public:
	SceneLight();
	~SceneLight();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	enum GEOMETRY_TYPE
	{
		GEO_AXES = 0,
		Sphere = 1,
		LightSphere=2,
		Quad=3,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_TOTAL,

	};
private:
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
	Light light[1];
	Camera2 camera;
	void RenderMesh(Mesh* mesh, bool enableLight);
	float LSPEED;
};

#endif