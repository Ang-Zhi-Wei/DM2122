#ifndef SCENESceneSP2Room2_H
#define SCENESceneSP2Room2_H
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
class SceneSP2Room2 : public Scene
{
public:
	SceneSP2Room2();
	~SceneSP2Room2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void PauseUpdate();
	virtual void Render();
	virtual void Exit();
	virtual void Set(Scene* scene);
	virtual void SetBackground();

	//struct Item
	//{
	//	enum ITEM_TYPE
	//	{
	//		BATTERY,
	//		ITEM2,
	//		ITEM3,
	//		//add more depending on whta u need, don forget set in Set function
	//	};
	//	//Vector3 pos; //only if u plan to reuse struct for rendering
	//	const char* image; //image of item in inventory
	//	int count;
	//	ITEM_TYPE type; //type of item (for reusability e.g 100 batteries; easier setting)
	//	std::string name;  //Name that shows up in item display; can also be used to differentiate btw objects of same type but different, eg both keys but unlock diff doors, type = key but name different
	//	std::string description; //Short description of item that shows up in item display

	//	Item()
	//	{
	//		count = 1;
	//	}
	//	void Set(std::string name, ITEM_TYPE type)
	//	{
	//		//this->pos = pos; //if used for rendering uncomment, otherwise can remove pos from function arguments
	//		this->type = type;
	//		this->name = name;
	//		switch (type)
	//		{
	//		case BATTERY:
	//			this->description = "Use to refill flashlight batteries aaaaaa idk";
	//			this->image = "Image//fountaintexture.tga";
	//			//set image and description
	//			break;
	//		case ITEM2:
	//			this->description = "TESTESTTESTETSESTESTESTETST>--|-o";
	//			this->image = "Image//man1.tga";
	//			break;
	//		}
	//	}
	//};
	//struct Inventory
	//{
	//	int selected;
	//	Item* items[8];
	//	bool open;

	//	Inventory()
	//	{
	//		for (int i = 0; i < 8; i++)
	//		{
	//			items[i] = nullptr;
	//		}
	//		open = false;
	//		selected = 0;
	//	}
	//};
	//struct Ghost
	//{
	//	enum GHOST_STATE
	//	{
	//		NORMAL,
	//		CHASING,
	//		WAITING,
	//		SPEEDRUN
	//	};
	//	int state;
	//	Vector3 pos;
	//	Vector3 facing; //ghost direction
	//	float speed; //TBC normal - 5, chasing - 25, speedrunning away - 50; //player is 20 normal and 40 sprinting
	//	float distance;
	//	float waitTime;
	//	float rotateY;

	//	Ghost()
	//	{
	//		speed = 5;
	//		pos = (0, 0, 0); //TBC
	//		rotateY = 0;
	//		state = NORMAL;
	//		waitTime = 5;
	//	}

	//	void UpdateMovement(double dt)
	//	{
	//		float newangle = Math::RadianToDegree(atan(facing.x / facing.z)); //facing is vector that player/char shud be facing
	//																			//newangle is angle of rotation for playerr/char based on the vector

	//		//since tan inverse returns basic angle, gotta set the angle myself
	//		if (newangle == 0 && facing.z < 0)
	//		{
	//			newangle = 180;
	//		}
	//		else if (newangle < 0 && facing.x >= 0 && facing.z <= 0)
	//		{
	//			newangle = newangle + 180;
	//		}
	//		else if (newangle > 0 && facing.x <= 0 && facing.z <= 0)
	//		{
	//			newangle = newangle - 180;
	//		}

	//		//if angle exceeds one cycle, bring it back to within 0 to 360 cycle
	//		if (rotateY > 360)
	//		{
	//			rotateY -= 360;
	//		}
	//		if (rotateY < 0)
	//		{
	//			rotateY += 360;
	//		}
	//		if (newangle > 360)
	//		{
	//			newangle -= 360;
	//		}
	//		if (newangle < 0)
	//		{
	//			newangle += 360;
	//		}

	//		//int/float offset for checking
	//		if (abs(newangle - rotateY) < 5)
	//		{
	//			rotateY = newangle;
	//		}

	//		//update rotate angle(in render) to face/turn towards direction player is walking in
	//		int dir = (newangle - rotateY) / abs(newangle - rotateY);
	//		if ((int)rotateY != (int)newangle)
	//		{
	//			if (abs(newangle - rotateY) > 180) //so that it rotates ACW/CW the shortest path 
	//			{
	//				dir *= -1;
	//			}
	//			rotateY += float(dir * 20 * dt);
	//		}
	//		else
	//		{
	//			pos += facing * speed * dt;
	//		}
	//	}
	//};
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
		GEO_WALL1,
		GEO_WALL2,
		GEO_WALL3,
		GEO_QUAD,
		GEO_TABLE,
		GEO_LONGTABLE,
		GEO_CHAIR,
		GEO_LEFTDOOR,
		GEO_RIGHTDOOR,
		GEO_PODIUM,
		GEO_PIGEONHOLE,




		//colliderbox 
		Colliderbox,
		
		//locker
		locker,


		//game tings
		GEO_SKULL,
		GEO_MYSTERIOUSMAN,

		//UI tings
		GEO_TEXT,
		GEO_OVERLAY, //vision
		GEO_OVERLAY2, //Camcorder
		GEO_WARNING1,
		GEO_WARNING2,
		GEO_DEATH,
		GEO_REDDOT, // Camcorder dot
		GEO_BAR, //stamina
		GEO_BREATHINGBAR, // breathing
		GEO_STAMINA,
		GEO_PLAYGROUND,
		GEO_LIVES,
		GEO_CHATBOX,
		GEO_SIDEBOX,

		GEO_INVENTORY,
		GEO_BATTERY,
		GEO_SELECT,

		GEO_ITEMDISPLAY,
		GEO_ITEMIMAGE0,
		GEO_ITEMIMAGE1,
		GEO_ITEMIMAGE2,
		GEO_ITEMIMAGE3,
		GEO_ITEMIMAGE4,
		GEO_ITEMIMAGE5,
		GEO_ITEMIMAGE6,
		GEO_ITEMIMAGE7,

		GEO_JUMPSCARE1,

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
	
		//light 2
		U_LIGHT2_POWER,
		//light 3
		U_LIGHT3_POWER,
		//light 4
		U_LIGHT4_POWER,
		//light 5
		U_LIGHT5_POWER,
	
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
	Light light[6];
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
			lengthx =lengthy =lengthz = 0.5;
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
			TrapPosition = (0.f, 0.f, 0.f);
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
			return(distance.Length() < 3);
		}
	};

	//Jumpscare
	bool jumpscareTimerActive1;
	double jumpscareTimer1;
	int jumpscareCounter1;
	bool jumpscareActive1;
	bool jumpscareTimerActive2;
	double jumpscareTimer2;
	int jumpscare2Counter;
	bool jumpscare2Pass;
	bool jumpscare2ActiveZone;
	bool jumpscareActive2;

	float campos_x;
	float campos_y;
	float campos_z;
	bool exitSchool;
	bool nearExit;
	bool showChatbox;


	//game related vars
	bool inLocker;

	Wall school_walls[6];  //0 front top, 1 front left, 2 front right, 3 back, 4 left, 5 right
							
	Wall lounge_walls[3]; //top, left, right
	Wall classroom_walls[2]; //top, wall
	Wall classroom_tables[20];
	Wall classroom_chairs[20];
	Wall lounge_table;
	Wall podium;

	const int wall_count = 11;
	Wall* all_walls[11] = { &school_walls[0], &lounge_walls[0], &classroom_walls[0], 
		&school_walls[1], &school_walls[2], &school_walls[4], &school_walls[5],&classroom_walls[1],
					  &lounge_walls[1], &lounge_walls[2],  
		&school_walls[3]};

	Door school_door[2];
	Door classroom_door[2];
	Door lounge_door[2];
	Door* all_doors[6] = { &school_door[0], &school_door[1], 
							&lounge_door[1], &classroom_door[0],
							&classroom_door[1],&lounge_door[0]};

	

	int DS_school, DS_classroom, DS_lounge;
	bool interact;
	std::string interact_message;
	//Mesh* itemImage[8];

	void RenderSkybox();
	std::vector<ColliderBox>Colliderlist;
	std::vector<Locker>Lockerlist;
	std::vector<trap>traplist;
	Vector3 temp;
	bool PickUpItem(Item* item); //shud be called only in one frame, 
	void UseItem(int itemtype); //rmb to edit this function as u add items
	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, int limit);
	void RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey);
	bool camBlinkOn;
	bool camBlinkOff;
	double camBlinkOnSec;
	double camBlinkOffSec;
};

#endif