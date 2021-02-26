#ifndef SCENESceneSP2Room1_H
#define SCENESceneSP2Room1_H
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
#include <string>
class SceneSP2Room1 : public Scene
{
public:
	SceneSP2Room1();
	~SceneSP2Room1();

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
		LightSphere,

		//skybox
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_TOPHALFWALL,
		GEO_WALL,
		GEO_CEILING,
		GEO_FLOOR,
		KITCHENFLOOR,
		GEO_RIGHTDOOR,
		SOFA,
		TELEVISION,
		TV_STAND,
		WOODENTABLE,
		BOOKSHELF,
		SHELVES,
		KITCHENSINK,
		STOVE,
		FRIDGE,
		BED,
		DRESSER,
		WRENCH,


		//ground mesh
		Ground_Mesh,

		//objs
		Colliderbox,
		locker,
		GEO_BEARTRAP,
		//ghost
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
		GEO_BAR2,
		SUFFOCATION,
		GEO_STAMINA,
		GEO_PLAYGROUND,
		GEO_LIVES,
		GEO_CHATBOX,
		GEO_SIDEBOX,
		BATTERY,
		

		//puzzle items
		leverbase,
		leverhandle,
		painting,
		flow,
		water,
		safe,
		key,


		//@pause
		GEO_PAUSEMENU,

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
		//Jumpscares
		GEO_JUMPSCARE1,	
		
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
	

	
	struct trap {
		enum traptype {
			beartrap,
		};
		int TRAPTYPE;
		Vector3 TrapPosition;
		trap() {
			TRAPTYPE = beartrap;
			TrapPosition = Vector3(0, 0, 0);
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
	void RenderSkybox();
	//void RenderMegumin();
	//void RenderDeadTree(int x, int z,float rotate);
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Mesh* meshList[NUM_GEOMETRY];
	

	MS modelStack, viewStack, projectionStack;
	Light light[6];
	CameraSP2 camera;
	
	Item* houseItems[6];
	float LSPEED;
	float fps;
	bool camBlinkOn;
	bool camBlinkOff;
	bool pickUpBattery;
	double camBlinkOnSec;
	double camBlinkOffSec;
	bool inLocker;
	bool nearKey;
	bool nearWrench;
	bool interact;

	std::string interact_message;
//	Mesh* itemImage[8];

	DOOR_STATE DS_MAIN, DS_HALL, DS_LIVING, DS_CONNECTING;
	float rotateY[4]; //0-main, 1-hall, 2-living room, 3- connecting room door

	//Jumpscare stuff
	int jumpscareEntrance1;
	double jumpscareTimer1;
	double jumpscareTimerReset1;
	bool jumpscareActive1;
	bool jumpscareTimerActive1;

	int jumpscareEntrance2;
	double jumpscareTimer2;
	double jumpscareTimerReset2;
	bool jumpscareActive2;
	bool jumpscareTimerActive2;

	int jumpscareEntrance3;
	double jumpscareTimer3;
	double jumpscareTimerReset3;
	bool jumpscareActive3;
	bool jumpscareTimerActive3;

	int jumpscareEntrance4;
	double jumpscareTimer4;
	double jumpscareTimerReset4;
	bool jumpscareActive4;
	bool jumpscareTimerActive4;


	//In locker stuff
	float suffocationTranslate;
	float suffocationTranslateDir;
	float suffocationScale;
	float suffocationScaleDir;

	bool Fpressed, Freleased;
	bool Epressed, Ereleased;
	bool Qpressed, Qreleased;
	bool Apressed, Areleased;
	bool Dpressed, Dreleased;
	bool Rpressed, Rreleased;

	//@pause 
	bool PKeypressed, PKeyreleased;
	bool gamepaused;
	double Mousex, Mousey;
	double MposX, MposY;
	double Mousetempx, Mousetempy;

	float campos_x;
	float campos_y;
	float campos_z;
	bool exitHouse;
	bool nearExit;
	bool showChatbox;
	bool showSideBox;

	//puzzle animation factors and logic
	float rotate_painting;
	float rotate_lever;
	float move_safe;
	float movewater;
	float residepause;
	bool keyspawn;

	enum leverPulled
	{
		yes,
		no,
		pulling,
	};
	leverPulled leverIsPulled;

	enum WaterState
	{
		flowing,
		reside,
		resided,
		notused,
		keycollected,
	};
	WaterState waterstate;

	bool isUnlocked[2];
	enum DoorUnlocked
	{
		kitchen,
		bedroom
	};

	std::vector<ColliderBox>Colliderlist;
	std::vector<Locker>Lockerlist;
	std::vector<trap>traplist;
	Vector3 temp;
	bool PickUpItem(Item* item); //shud be called only in one frame, delete item after pick up
	void UseItem(int itemtype); //rmb to edit this function as u add items
	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, int limit);
	void RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey);
	void RenderPuzzleItems();
};
#endif