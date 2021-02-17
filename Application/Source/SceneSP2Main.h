#ifndef SCENESceneSP2Main_H
#define SCENESceneSP2Main_H
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
#include "Locker.h"
#include <string>
class SceneSP2Main : public Scene
{
public:
	SceneSP2Main();
	~SceneSP2Main();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	int SpeakPhase;
	double SpeakTimer;
	int ObjectivePhase;

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

		//ground mesh
		Ground_Mesh,
		GEO_PATH,

		//models
		GEO_WATER,
		GEO_LIGHTBULB,
		GEO_SPAWN,


		//objs
		GEO_BUILDING,
		GEO_ROAD,
		GEO_TREES,
		GEO_FOUNTAIN,
		Ruins,
		locker,
		GEO_LAMP,
		GEO_TRUCK,

		//npc objs
		GEO_MYSTERIOUSMAN,

		//colliderbox 
		Colliderbox,
		Fountain,

		//UI tings
		GEO_TEXT,
		GEO_OVERLAY, //vision
		GEO_OVERLAY2, //Camcorder
		GEO_BAR, //stamina
		GEO_STAMINA,
		GEO_CHATBOX,

		//paths
		GEO_CENTRE,
		
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
		//light 2

		U_LIGHT2_POSITION,
		U_LIGHT2_COLOR,
		U_LIGHT2_POWER,
		U_LIGHT2_KC,
		U_LIGHT2_KL,
		U_LIGHT2_KQ,
		U_LIGHT2_TYPE,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT2_COSINNER,
		U_LIGHT2_EXPONENT,

		//light 3
		U_LIGHT3_POSITION,
		U_LIGHT3_COLOR,
		U_LIGHT3_POWER,
		U_LIGHT3_KC,
		U_LIGHT3_KL,
		U_LIGHT3_KQ,
		U_LIGHT3_TYPE,
		U_LIGHT3_SPOTDIRECTION,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT3_COSINNER,
		U_LIGHT3_EXPONENT,
		
		U_TOTAL,

	};

private:

	int lockernum;
	float rotate_Man;

	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Mesh* meshList[NUM_GEOMETRY];
	
	MS modelStack, viewStack, projectionStack;
	Light light[4];
	CameraSP2 camera;
	float LSPEED;
	float fps;
	bool Fpressed, Freleased;
	bool Epressed, Ereleased;
	bool Qpressed, Qreleased;
	struct Item
	{

	};

	struct Inventory
	{
		Item* selected;
		Item* inventory[10];
	};

	struct Ghost
	{
		enum GHOST_STATE
		{
			NORMAL,
			CHASING,
			WAITING,
			SPEEDRUN
		};
		int state;
		Vector3 pos;
		Vector3 facing; //ghost direction
		float speed; //TBC normal - 5, chasing - 25, speedrunning away - 50; //player is 20 normal and 40 sprinting
		float distance;
		float waitTime;
		float rotateY;

		Ghost()
		{
			speed = 5;
			pos = (0, 0, 0); //TBC
			rotateY = 0;
			state = NORMAL;
			waitTime = 5;
		}
		
		void UpdateMovement(double dt)
		{
			float newangle = Math::RadianToDegree(atan(facing.x / facing.z)); //facing is vector that player/char shud be facing
																				//newangle is angle of rotation for playerr/char based on the vector

			//since tan inverse returns basic angle, gotta set the angle myself
			if (newangle == 0 && facing.z < 0)
			{
				newangle = 180;
			}
			else if (newangle < 0 && facing.x >= 0 && facing.z <= 0)
			{
				newangle = newangle + 180;
			}
			else if (newangle > 0 && facing.x <= 0 && facing.z <= 0)
			{
				newangle = newangle - 180;
			}

			//if angle exceeds one cycle, bring it back to within 0 to 360 cycle
			if (rotateY > 360)
			{
				rotateY -= 360;
			}
			if (rotateY < 0)
			{
				rotateY += 360;
			}
			if (newangle > 360)
			{
				newangle -= 360;
			}
			if (newangle < 0)
			{
				newangle += 360;
			}

			//int/float offset for checking
			if (abs(newangle - rotateY) < 5)
			{
				rotateY = newangle;
			}

			//update rotate angle(in render) to face/turn towards direction player is walking in
			int dir = (newangle - rotateY) / abs(newangle - rotateY);
			if ((int)rotateY != newangle)
			{
				if (abs(newangle - rotateY) > 180) //so that it rotates ACW/CW the shortest path 
				{
					dir *= -1;
				}
				rotateY += float(dir * 200 * dt);
			}
			else
			{
				pos += facing * speed * dt;
			}
		}
	};

	//game related vars
	bool flashlight;
	bool inLocker;
	bool showChatbox;

	bool camBlinkOn;
	bool camBlinkOff;
	bool switchtga1;
	bool switchtga2;
	double camBlinkOnSec;
	double camBlinkOffSec;

	float campos_x;
	float campos_y;
	float campos_z;

	int Interact_Num;
	bool canTalk_man;

	Ghost ghost;
	Vector3 temp;
	void RenderSkybox();
	std::vector<ColliderBox>Colliderlist;
	std::vector<Locker>Lockerlist;
	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey);
};

#endif