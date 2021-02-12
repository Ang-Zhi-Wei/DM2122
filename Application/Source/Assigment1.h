#ifndef ASSIGMENT1_H
#define ASSIGMENT1_H
#include "Scene.h"
#include "Mtx44.h"
#include "Application.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
class Assigment1 : public Scene
{
public:
	Assigment1();
	~Assigment1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	enum GEOMETRY_TYPE
	{
		GEO_AXES = 0,
		BodyRed = 1,
		BodyBrown = 2,
		BodyYellow = 3,
		BodySilver = 4,
		BodyWheat = 5,
		BodyBlack = 6,
		Eye = 7,
		BodyWhite = 8,
		Arm = 9,
		Leg = 10,
		Torus = 11,
		HatCone = 12,
		Platform = 13,
		HalfCube = 14,
		Orb = 15,
		GEO_LIGHTBALL = 16,
		RedRings = 17,
		GiantSphere=18,
		Particlespell,
		circlejump,
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
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_NUMLIGHTS,
		U_LIGHTENABLED,
		U_TOTAL,
	};
private:
	Camera2 camera;
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
	MS modelStack, viewStack, projectionStack;
	Light light[1];
	float LSPEED;
	void RenderMesh(Mesh* mesh, bool enableLight);
	bool movement;
	bool jump;
	bool spell;
	bool rotate;
	float translatex;
	float translatey;
	float translatez;
	float rotatelegs;
	float rotatearms;
	float rotatehands;
	float increaserotation;
	float temp;
	bool doublejump;
	int switchrotate;
	bool switchtranslatey;
	int phase;
	float scalering[6];
	float scalesphere;
	//spell particle effect
	float spellparticlex[200];
	float spellparticley[200];
	float spellparticlez[200];
	float spellparticleylimit[200];
	//jump particle effect
	float jumpparticley[20];
	float jumpparticlez[20];
	float circlex;
	float circley;
	float circlez;
};

#endif