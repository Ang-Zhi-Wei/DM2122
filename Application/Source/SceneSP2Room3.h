#ifndef SCENESceneSP2Room3_H
#define SCENESceneSP2Room3_H
#include "Scene.h"
#include "Mtx44.h"
#include "Application.h"
#include "Camera4.h"
#include "CameraSP2.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
#include "ColliderBox.h"
#include <vector>
class SceneSP2Room3 : public Scene
{
public:
	SceneSP2Room3();
	~SceneSP2Room3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void PauseUpdate(double dt);
	virtual void Render();
	virtual void Exit();
	virtual void Set(Scene* scene);
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		LightSphere,

		//skybox
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		//terrain
		GEO_TOPHALFWALL,
		GEO_WALL,
		GEO_QUAD,
		GEO_TABLE,
		GEO_LONGTABLE,
		GEO_CHAIR,
		GEO_LEFTDOOR,
		GEO_RIGHTDOOR,

		//colliderbox 
		Colliderbox,
		
		//locker
		locker,
		tire,
		shelves,
		garagetable,
		rustycar,
		rustychair,
		barrels,
		rolldoor,

		//UI tings
		GEO_TEXT,
		GEO_OVERLAY, //vision
		GEO_OVERLAY2, //Camcorder
		GEO_BAR, //stamina

		//trap
		GEO_BEARTRAP,
		
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
		//light 0
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		//light 1
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		
		U_TOTAL,

	};
	enum DOOR_STATE
	{
		OPEN,
		CLOSED,
		OPENING,
		CLOSING
	};


private:



	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Mesh* meshList[NUM_GEOMETRY];

	
	MS modelStack, viewStack, projectionStack;
	Light light[2];
	CameraSP2 camera;
	float LSPEED;
	float fps;
	bool Fpressed, Freleased;
	bool Epressed, Ereleased;
	bool Qpressed, Qreleased;
	bool Apressed, Areleased;
	bool Dpressed, Dreleased;
	bool Rpressed, Rreleased;
	struct Wall
	{
		Vector3 mid;
		float lengthx, lengthy, lengthz;
		//bool xy; //plane
		Wall()
		{
			lengthx = lengthz = 0.5;
		}
	};
	struct Door : Wall
	{
		float rotateY;
	};

	

	
	struct trap {
		enum traptype {
			beartrap,
		};
		int TRAPTYPE;
		Vector3 TrapPosition;
		trap() {
			TRAPTYPE = beartrap;
			TrapPosition = (0, 0, 0);
		}
		trap(int TRAPTYPE, Vector3 TrapPosition) {
			this->TRAPTYPE = TRAPTYPE;
			this->TrapPosition = TrapPosition;
		}
		bool nearby(Vector3 CameraPosition) {
			//calculating based on xz plane
			CameraPosition.y = 0;
			Vector3 temp = TrapPosition;
			temp.y = 0;
			Vector3 distance = temp - CameraPosition;
			return(distance.Length() < 2);
		}
	};

	//game related vars
	bool inLocker;

	Wall school_walls[6];  //0 front top, 1 front left, 2 front right, 3 back, 4 left, 5 right
							
	Wall lounge_walls[3]; //top, left, right
	Wall classroom_walls[2]; //top, wall
	Wall classroom_tables[20];
	Wall classroom_chairs[20];
	Wall lounge_table;

	const int wall_count = 11;
	Wall* all_walls[11] = { &school_walls[0], &lounge_walls[0], &classroom_walls[0], &school_walls[1], &school_walls[2], &school_walls[3], &school_walls[4], &school_walls[5],
					  &lounge_walls[1], &lounge_walls[2], &classroom_walls[1]};

	Door school_door[2];
	Door classroom_door[2];
	Door lounge_door[2];
	Door* all_doors[6] = { &school_door[0], &school_door[1], 
							&lounge_door[1], &classroom_door[0],
							&classroom_door[1],&lounge_door[0]};

	

	DOOR_STATE DS_school, DS_classroom, DS_lounge;
	bool interact;
	std::string interact_message;

	void RenderSkybox();
	std::vector<ColliderBox>Colliderlist;
	std::vector<Locker>Lockerlist;
	std::vector<trap>traplist;
	Vector3 temp;
	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey);
	bool switchtga1;
	bool switchtga2;
	bool camBlinkOn;
	bool camBlinkOff;
	double camBlinkOnSec;
	double camBlinkOffSec;
};

#endif