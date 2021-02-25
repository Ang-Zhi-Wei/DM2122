#ifndef SCENESceneSP2Loading_H
#define SCENESceneSP2Loading_H
#include "Scene.h"
#include "Mtx44.h"
#include "Application.h"
#include "Camera4.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
#include "ColliderBox.h"
#include <vector>
#include "Locker.h"
class SceneSP2Loading : public Scene
{
public:
	SceneSP2Loading();
	~SceneSP2Loading();
	
	bool menuScreen;

	virtual void Init();
	virtual void Update(double dt);
	virtual void PauseUpdate();
	virtual void Render();
	virtual void Exit();
	virtual void Set(Scene* scene);
	virtual void SetBackground();


	enum GEOMETRY_TYPE
	{
		GEO_AXES,

		//UI tings
		GEO_TEXT,
		LOADING,
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
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_LIGHTENABLED,



		U_TOTAL,
	};

private:

	int ButtonNum;


	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;
	Light light[1];
	Camera4 camera;
	//mouse positions
	double Mousex, Mousey;
	double MposX, MposY;


	void UseItem(int itemtype);
	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey);
};

#endif