#include "SceneSP2Room3.h"
#include "GL\glew.h"
#include <stdlib.h>
#include <time.h>
#include "shader.hpp"
#include "LoadTGA.h"
#include <sstream>

SceneSP2Room3::SceneSP2Room3()
{
	//if you see anything from here missing in init just copy and paste them 
	LSPEED = 10.F;
	interact = false;
	flashlight = false;
	flashlight_lifetime = 90;
	inLocker = false;
	exitGarage = false;
	showSideBox = true;
	SpeakTimer = 0;
	Qpressed = Qreleased = false;
	Epressed = Ereleased = false;
	Fpressed = Freleased = false;
	Apressed = Areleased = false;
	Dpressed = Dreleased = false;
	Rpressed = Rreleased = false;
	camBlinkOffSec = 0;
	camBlinkOnSec = 0;
	fps = 60;
	DS_classroom = CLOSED;
	DS_lounge = CLOSED;
	DS_school = OPEN;
	camBlinkOn = false;
	camBlinkOff = true;

	//@pause
	gamepaused = false;
	PKeypressed = PKeyreleased = false;
	//======
}

SceneSP2Room3::~SceneSP2Room3()
{
}


void SceneSP2Room3::Init()
{
	// Init VBO here
	glClearColor(0., 0., 0., 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//camera
	camera.Init(Vector3(0, 9, -5), Vector3(0, 9, -25), Vector3(0, 1, 0));
	//shaders
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	SpeakTimer = 0;
	//...
	
	//light 0
	m_parameters[U_LIGHT0_TYPE] =
		glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] =
		glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] =
		glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] =
		glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] =
		glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[U_LIGHT0_POSITION] =
		glGetUniformLocation(m_programID,
			"lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] =
		glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] =
		glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID,
		"lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID,
		"lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID,
		"lights[0].kQ");
	//light 1
	m_parameters[U_LIGHT1_TYPE] =
		glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] =
		glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] =
		glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] =
		glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] =
		glGetUniformLocation(m_programID, "lights[1].exponent");
	m_parameters[U_LIGHT1_POSITION] =
		glGetUniformLocation(m_programID,
			"lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] =
		glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] =
		glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID,
		"lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID,
		"lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID,
		"lights[1].kQ");

	//other lights
	m_parameters[U_LIGHT2_POWER] =
		glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT3_POWER] =
		glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[U_LIGHT4_POWER] =
		glGetUniformLocation(m_programID, "lights[4].power");
	m_parameters[U_LIGHT5_POWER] =
		glGetUniformLocation(m_programID, "lights[5].power");

	//num lights
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID,
		"numLights");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID,
		"MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID,
		"MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] =
		glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] =
		glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] =
		glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] =
		glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] =
		glGetUniformLocation(m_programID, "material.kShininess");

	m_parameters[U_LIGHTENABLED] =
		glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID,
		"MVP");
	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] =
		glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] =
		glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] =
		glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID,
		"textColor");
	Mtx44 projection;
	projection.SetToPerspective(46.f, 4.f / 3.f, 0.1f, 2000.f);
	projectionStack.LoadMatrix(projection);
	glUseProgram(m_programID);
	//mesh
	meshList[LightSphere] = MeshBuilder::Generatesphere("LightBall", 1, 1, 1, White);
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Reference", 1, 1, 1);
	//skybox texture
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front",1,1,White);
	meshList[GEO_FRONT]->textureID = LoadTGA("Night//front.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", 1, 1, White);
	meshList[GEO_BACK]->textureID = LoadTGA("Night//back.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", 1, 1, White);
	meshList[GEO_LEFT]->textureID = LoadTGA("Night//left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", 1, 1, White);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Night//right.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", 1, 1, White);
	meshList[GEO_TOP]->textureID = LoadTGA("Night//top.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", 1, 1, White);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Night//bottom.tga");
	
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Assigment2Images//Arial.tga");

	meshList[tire] = MeshBuilder::GenerateOBJ("Building", "OBJ//Tire.obj");
	meshList[tire]->textureID = LoadTGA("Assigment2Images//metalgate.tga");
	meshList[tire]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[shelves] = MeshBuilder::GenerateOBJ("Building", "OBJ//shelves.obj");
	meshList[shelves]->textureID = LoadTGA("Assigment2Images//shelves.tga");
	meshList[shelves]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[garagetable] = MeshBuilder::GenerateOBJ("Building", "OBJ//garagetable.obj");
	meshList[garagetable]->textureID = LoadTGA("Assigment2Images//garagetable.tga");
	meshList[garagetable]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[rustycar] = MeshBuilder::GenerateOBJ("Building", "OBJ//rustycar.obj");
	meshList[rustycar]->textureID = LoadTGA("Assigment2Images//cartexture.tga");
	meshList[rustycar]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[rustychair] = MeshBuilder::GenerateOBJ("Building", "OBJ//rustychair.obj");
	meshList[rustychair]->textureID = LoadTGA("Assigment2Images//foldedchair.tga");
	meshList[rustychair]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[barrels] = MeshBuilder::GenerateOBJ("Building", "OBJ//barrels.obj");
	meshList[barrels]->textureID = LoadTGA("Assigment2Images//barreltexture.tga");
	meshList[barrels]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);


	meshList[screwdriver] = MeshBuilder::GenerateOBJ("Building", "OBJ//screwdriver2.obj");
	meshList[screwdriver]->textureID = LoadTGA("Assigment2Images//screwdriver2.tga");
	meshList[screwdriver]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	
	//meshList[workbench] = MeshBuilder::GenerateOBJ("Building", "OBJ//Workbench.obj");
	////meshList[workbench]->textureID = LoadTGA("Assigment2Images//barreltexture.tga");
	//meshList[workbench]->material.kAmbient.Set(0.35, 0.35, 0.35);
	meshList[GEO_SKULL] = MeshBuilder::GenerateOBJ("skull", "OBJ//Skull.obj");
	meshList[GEO_SKULL]->material.kAmbient.Set(Gray);
	//Mysterious man
	meshList[GEO_MYSTERIOUSMAN] = MeshBuilder::GenerateOBJ("man npc", "OBJ//man1.obj");
	meshList[GEO_MYSTERIOUSMAN]->textureID = LoadTGA("Image//man1.tga");
	meshList[GEO_MYSTERIOUSMAN]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[wheelbarrow] = MeshBuilder::GenerateOBJ("Building", "OBJ//wheelbarrow.obj");
	meshList[wheelbarrow]->textureID = LoadTGA("Assigment2Images//wheelbarrow.tga");
	meshList[wheelbarrow]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[metalcabinet] = MeshBuilder::GenerateOBJ("Building", "OBJ//metalcabinet.obj");
	meshList[metalcabinet]->textureID = LoadTGA("Assigment2Images//cabinettexture.tga");
	meshList[metalcabinet]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[garagedoor] = MeshBuilder::GenerateOBJ("Building", "OBJ//garagedoor.obj");
	meshList[garagedoor]->textureID = LoadTGA("Assigment2Images//garagedoor.tga");
	meshList[garagedoor]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[BATTERY] = MeshBuilder::GenerateOBJ("Building", "OBJ//Battery.obj");
	meshList[BATTERY]->textureID = LoadTGA("Assigment2Images//batterytexture.tga");
	meshList[BATTERY]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	garageItems[0] = new Item("Screwdriver", Item::Screwdriver, Vector3(-22, 7.8, -95));
	garageItems[1] = new Item("Battery", Item::BATTERY, Vector3(-20, 7.5, -60));
	garageItems[2] = new Item("Battery", Item::BATTERY, Vector3(25, 0, -60));


	
	
	//other lights
	light[2].power = 0;
	light[3].power = 0;
	light[4].power = 0;
	light[5].power = 0;
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT4_POWER], light[4].power);
	glUniform1f(m_parameters[U_LIGHT5_POWER], light[5].power);


	//Set Material locations
	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT],
		m_parameters[U_MATERIAL_DIFFUSE],
		m_parameters[U_MATERIAL_SPECULAR],
		m_parameters[U_MATERIAL_SHININESS]);
	//number of lights
	glUniform1i(m_parameters[U_NUMLIGHTS], 6);

	//=============== UI stuff ===================
	//camcorder
	meshList[GEO_OVERLAY] = MeshBuilder::GenerateQuad2("vision", 80, 60, 0);
	meshList[GEO_OVERLAY2] = MeshBuilder::GenerateQuad2("camcorder", 80, 60, 0);
	meshList[GEO_OVERLAY2]->textureID = LoadTGA("Image//camcorder2.tga");
	meshList[GEO_REDDOT] = MeshBuilder::GenerateQuad2("dot", 1, 1, White);
	meshList[GEO_REDDOT]->textureID = LoadTGA("Image//redDot.tga");

	//pause menu
	meshList[GEO_PAUSEMENU] = MeshBuilder::GenerateQuad2("pause", 1, 1, 0);
	meshList[GEO_PAUSEMENU]->textureID = LoadTGA("Image//pause.tga");

	//player
	meshList[GEO_BAR] = MeshBuilder::GenerateQuad2("stamina bar", 1, 1, Yellow);
	meshList[GEO_BREATHINGBAR] = MeshBuilder::GenerateQuad2("stamina bar", 1, 1, Red);
	meshList[GEO_BATTERY] = MeshBuilder::GenerateQuad2("flashlight lifetime bar", 1, 1, White);
	meshList[GEO_STAMINA] = MeshBuilder::GenerateQuad2("UI usage", 1, 1, White);
	meshList[GEO_STAMINA]->textureID = LoadTGA("Assigment2Images//sprint.tga");
	meshList[GEO_LIVES] = MeshBuilder::GenerateQuad2("UI usage", 1, 1, White);
	meshList[GEO_LIVES]->textureID = LoadTGA("Assigment2Images//livesicon.tga");
	meshList[GEO_OVERLAY]->textureID = LoadTGA("Image//VISIONOFF.tga");
	meshList[GEO_WARNING1] = MeshBuilder::GenerateQuad2("warning overlay", 80, 60, 0);
	meshList[GEO_WARNING1]->textureID = LoadTGA("Image//pinktint.tga");
	meshList[GEO_WARNING2] = MeshBuilder::GenerateQuad2("warning overlay", 80, 60, 0);
	meshList[GEO_WARNING2]->textureID = LoadTGA("Image//redtint.tga");
	meshList[GEO_DEATH] = MeshBuilder::GenerateQuad2("death overlay", 80, 60, 0);
	meshList[GEO_DEATH]->textureID = LoadTGA("Image//death.tga");
	meshList[GEO_INVENTORY] = MeshBuilder::GenerateQuad2("inventory", 5, 1, White);
	meshList[GEO_INVENTORY]->textureID = LoadTGA("Image//inventory.tga");
	meshList[GEO_SELECT] = MeshBuilder::GenerateQuad2("highlight", 1, 1, White);
	meshList[GEO_SELECT]->textureID = LoadTGA("Image//highlight.tga");
	meshList[GEO_ITEMIMAGE0] = MeshBuilder::GenerateQuad2("item image", 1, 1, White);
	meshList[GEO_ITEMIMAGE1] = MeshBuilder::GenerateQuad2("item image", 1, 1, White);
	meshList[GEO_ITEMIMAGE2] = MeshBuilder::GenerateQuad2("item image", 1, 1, White);
	meshList[GEO_ITEMIMAGE3] = MeshBuilder::GenerateQuad2("item image", 1, 1, White);
	meshList[GEO_ITEMIMAGE4] = MeshBuilder::GenerateQuad2("item image", 1, 1, White);
	meshList[GEO_ITEMIMAGE5] = MeshBuilder::GenerateQuad2("item image", 1, 1, White);
	meshList[GEO_ITEMIMAGE6] = MeshBuilder::GenerateQuad2("item image", 1, 1, White);
	meshList[GEO_ITEMIMAGE7] = MeshBuilder::GenerateQuad2("item image", 1, 1, White);
	meshList[GEO_ITEMDISPLAY] = MeshBuilder::GenerateQuad2("item details popup", 1.5, 1, White);
	meshList[GEO_ITEMDISPLAY]->textureID = LoadTGA("Image//itemdisplay.tga");

	//@pause
	//pause menu
	meshList[GEO_PAUSEMENU] = MeshBuilder::GenerateQuad2("pause", 1, 1, 0);
	meshList[GEO_PAUSEMENU]->textureID = LoadTGA("Image//pause.tga");

	meshList[GEO_CHATBOX] = MeshBuilder::GenerateQuad2("chatbox", 30, 20, 0);
	meshList[GEO_CHATBOX]->textureID = LoadTGA("Assigment2Images//chatbox.tga");
	meshList[GEO_SIDEBOX] = MeshBuilder::GenerateQuad2("chatbox", 30, 20, 0);
	meshList[GEO_SIDEBOX]->textureID = LoadTGA("Assigment2Images//sidebox.tga");

	itemImage[0] = meshList[GEO_ITEMIMAGE0];
	itemImage[1] = meshList[GEO_ITEMIMAGE1];
	itemImage[2] = meshList[GEO_ITEMIMAGE2];
	itemImage[3] = meshList[GEO_ITEMIMAGE3];
	itemImage[4] = meshList[GEO_ITEMIMAGE4];
	itemImage[5] = meshList[GEO_ITEMIMAGE5];
	itemImage[6] = meshList[GEO_ITEMIMAGE6];
	itemImage[7] = meshList[GEO_ITEMIMAGE7];

	
	//init update stuff
	LSPEED = 10.F;
	flashlight = false;
	flashlight_lifetime = 90;
	inLocker = false;
	Qpressed = Qreleased = false;
	Epressed = Ereleased = false;
	Fpressed = Freleased = false;
	Apressed = Areleased = false;
	Dpressed = Dreleased = false;
	Rpressed = Rreleased = false;




	



	//doors
	school_door[0].mid.Set(-2.5, 5, 0);
	school_door[1].mid.Set(2.5, 5, 0);
	lounge_door[0].mid.Set(-10, 5, -47.5);
	lounge_door[1].mid.Set(-10, 5, -52.5);
	classroom_door[0].mid.Set(10, 5, -97.5);
	classroom_door[1].mid.Set(10, 5, -92.5);
	school_door[0].lengthx = 5;
	school_door[1].lengthx = 5;
	lounge_door[0].lengthz = 5;
	lounge_door[1].lengthz = 5;
	classroom_door[0].lengthz = 5;
	classroom_door[1].lengthz = 5;
	for (int i = 0; i < 6; i++)
	{
		all_doors[i]->lengthy = 10;
	}
	school_door[0].rotateY = -90;
	school_door[1].rotateY = 90;
	
	//chairs/table
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			classroom_tables[row * 5 + col].mid.Set(float(40 + row * 15), float(3), float(-80 + (col * 15)));
			classroom_tables[row * 5 + col].lengthx = 5; //not sure since obj
			classroom_tables[row * 5 + col].lengthz = 5; //not sure since obj
			//lengthy unset
			classroom_chairs[row * 5 + col].mid.Set(float(40 + row * 15 + 5), float(3), float(-80 + (col * 15)));
			classroom_chairs[row * 5 + col].lengthx = 5; //not sure since obj
			classroom_chairs[row * 5 + col].lengthz = 5; //not sure since obj
			//lengthy unset
		}
	}
	lounge_table.mid.Set(-105, 2.5, -30); //y value estimated
	lounge_table.lengthx = 10; //not sure since obj
	lounge_table.lengthz = 20; //not sure since obj
	//lengthy unset


	//list of lockers
	Lockerlist.push_back(Locker());
	Lockerlist[0].setpos(Vector3(28.f, -0.2f, -80.f));
	Lockerlist[0].setyaw(180);
	//wall colliders
	//@collider
	Colliderlist.push_back(ColliderBox());
	Colliderlist[0].setlength(5, 25, 100);
	Colliderlist[0].Setposition(Vector3(30, 12, -50));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[1].setlength(5, 25, 100);
	Colliderlist[1].Setposition(Vector3(-30, 12, -50));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[2].setlength(100, 25, 5);
	Colliderlist[2].Setposition(Vector3(0, 12, -100));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[3].setlength(20, 30, 5);
	Colliderlist[3].Setposition(Vector3(-25, 12, 2));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[4].setlength(20, 30, 5);
	Colliderlist[4].Setposition(Vector3(25, 12, 2));
	//random objects colliders
	Colliderlist.push_back(ColliderBox());
	Colliderlist[5].setlength(5, 20, 7);
	Colliderlist[5].Setposition(Vector3(10, 0, -34));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[6].setlength(7, 20, 3);
	Colliderlist[6].Setposition(Vector3(-20, 0, -95));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[7].setlength(4.5, 20,12.5);
	Colliderlist[7].Setposition(Vector3 (- 20, 4, -60));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[8].setlength(17, 20, 38);
	Colliderlist[8].Setposition(Vector3(0, 1.5, -50));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[9].setlength(12, 20, 13);
	Colliderlist[9].Setposition(Vector3(-25.f, 1.2f, -22.f));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[10].setlength(12, 20, 12.5);
	Colliderlist[10].Setposition(Vector3(25.f, 0.8f, -30.f));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[11].setlength(10, 20, 19);
	Colliderlist[11].Setposition(Vector3(26, 4, -47));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[12].setlength(11.5, 20, 5.5);
	Colliderlist[12].Setposition(Vector3(25, 8, -94.5));
	//Locker collider
	Colliderlist.push_back(ColliderBox());
	Colliderlist[13].setlength(3.9, 10, 4.3);
	Colliderlist[13].Setposition(Vector3(Lockerlist[0].getpos()));
	//Garage door collider
	Colliderlist.push_back(ColliderBox());
	Colliderlist[14].setlength(30, 10, 5);
	Colliderlist[14].Setposition(Vector3(0, 2.1, 2));
	//colliderbox for checking any collider(just one)
	meshList[Colliderbox] = MeshBuilder::GenerateColliderBox("Box", Colliderlist[14].getxlength(), Colliderlist[14].getylength(), Colliderlist[14].getzlength());

	//terrain
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad2("floor/ceiling", 1, 1, White);
	meshList[GEO_QUAD]->textureID = LoadTGA("Assigment2Images//garage.tga");//this one was in render cousing memory leak
	meshList[GEO_WALL] = MeshBuilder::GenerateCubeT("walls", 1, 1, 1, 0, 0, 1, 1, Color(1.f, 0.1f, 0.1f));
	meshList[GEO_WALL]->textureID = LoadTGA("Assigment2Images//garage.tga");
	meshList[GEO_LEFTDOOR] = MeshBuilder::GenerateCubeT("door", 1, 1, 1, 0, 0, 1, 1, White);
	meshList[GEO_LEFTDOOR]->textureID = LoadTGA("Image//schooldoorleft.tga");
	meshList[GEO_RIGHTDOOR] = MeshBuilder::GenerateCubeT("door", 1, 1, 1, 0, 0, 1, 1, White);
	meshList[GEO_RIGHTDOOR]->textureID = LoadTGA("Image//schooldoorright.tga");
	
	

	//Locker mesh
	meshList[locker] = MeshBuilder::GenerateOBJ("Locker", "OBJ//locker.obj");
	meshList[locker]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[locker]->textureID = LoadTGA("Assigment2Images//locker.tga");
	//list of colliders
	camera.setchecker(Colliderlist);
	
	//Set boundary here
	camera.SetBounds(-415, 415, -365, 360);

	ghost = new Ghost;
	inventory = new Inventory;

	//camblink
	camBlinkOffSec = 0;
	camBlinkOnSec = 0;
	camBlinkOn = false;
	camBlinkOff = true;
	//door state
	DS_classroom = CLOSED;
	DS_lounge = CLOSED;
	DS_school = OPEN;



	//trap mesh
	meshList[GEO_BEARTRAP] = MeshBuilder::GenerateOBJ("Beartrap", "OBJ//BearTrap.obj");
	meshList[GEO_BEARTRAP]->textureID = LoadTGA("Assigment2Images//BearTrap.tga");
	meshList[GEO_BEARTRAP]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	//trap list
	traplist.push_back(trap(trap::beartrap, Vector3(10, 0, -10)));
	traplist.push_back(trap(trap::beartrap, Vector3(-25, 0, -65)));
}

void SceneSP2Room3::Set(Scene* scene)
{
	inventory = scene->inventory;
	ghost = scene->ghost;
	flashlight = scene->flashlight;
	screwDriverFound = scene->screwDriverFound;
	hammerFound = scene->hammerFound;
	wrenchFound = scene->wrenchFound;
	SparkplugFound = scene->SparkplugFound;
	ObjectivePhase = scene->ObjectivePhase;
	flashlight_lifetime = scene->flashlight_lifetime;
	if (flashlight)
	{
		light[1].power = 2;
		meshList[GEO_OVERLAY]->textureID = LoadTGA("Image//VISIONON.tga");
	}
	else
	{
		light[1].power = 0;
		meshList[GEO_OVERLAY]->textureID = LoadTGA("Image//VISIONOFF.tga");
	}
	//other lights
	light[2].power = 0;
	light[3].power = 0;
	light[4].power = 0;
	light[5].power = 0;
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT4_POWER], light[4].power);
	glUniform1f(m_parameters[U_LIGHT5_POWER], light[5].power);

	//inventory item image
	for (int i = 0; i < 8; i++)
	{
		itemImage[i] = scene->itemImage[i];
	}
}

void SceneSP2Room3::SetBackground()
{
	if (!Background) {
		Background = createIrrKlangDevice();
		Background->play2D("Sound\\Background\\529750__banzai-bonsai__looping-horror-groaning.wav", true);
		
	}
	if (!Effect) {
		Effect = createIrrKlangDevice();
		Effect->play2D("Sound\\Effects\\58453__sinatra314__footsteps-fast-on-pavement-loop.wav", true);
	
	}
	if (!Jumpscare) {
		Jumpscare = createIrrKlangDevice();
	}
	if (!Heartbeat) {
		Heartbeat = createIrrKlangDevice();
		Heartbeat->play2D("Sound\\Effects\\485076__inspectorj__heartbeat-regular-single-01-01-loop.wav", true);
	}
	Heartbeat->setSoundVolume(0.f);
	Background->setSoundVolume(0.25f);//Volume control
	Effect->setSoundVolume(0.f);
	
}

void SceneSP2Room3::Update(double dt)
{
	//mouse cursor show/hide
	//Application::hidemousecursor(true);
	if (camera.movement) {
		Effect->setSoundVolume(0.5f);
	}
	else {
		Effect->setSoundVolume(0.f);
	}
	//sounds when ghost get too close
	if (ghost->kill == false && ghost->state == Ghost::SPIN) {
		ghost->kill = true;
		Heartbeat->setSoundVolume(0.f);
		Jumpscare->play2D("Sound\\Jumpscares\\523984__brothermster__jumpscare-sound.wav", false);
		Jumpscare->setSoundVolume(1.f);
	}
	else if (ghost->kill == false && ghost->distance < 50) {
		Heartbeat->setSoundVolume(1.0f);
		Background->setSoundVolume(0.f);
	}
	else if (ghost->kill == false && (ghost->distance < 100 || ghost->state == Ghost::CHASING)) {
		Heartbeat->setSoundVolume(0.5f);
		Background->setSoundVolume(0.f);
	}
	else if(ghost->kill == false ){
		Heartbeat->setSoundVolume(0.f);
		Background->setSoundVolume(0.5f);
	}

	double SPEECH_LENGTH_FAST = 2;
	double SPEECH_LENGTH_SHORT = 3;
	double SPEECH_LENGTH_MEDIUM = 5;
	double SPEECH_LENGTH_LONG = 8;
	//key input
	if (Application::IsKeyPressed('1')) {
		glEnable(GL_CULL_FACE);
	}
	else if (Application::IsKeyPressed('2')) {
		glDisable(GL_CULL_FACE);
	}
	else if (Application::IsKeyPressed('3')) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (Application::IsKeyPressed('4')) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (!Application::IsKeyPressed('Q'))
	{
		Qreleased = true;
		Qpressed = false;
	}
	else
	{
		if (Qreleased)
		{
			Qpressed = true;

		}
		Qreleased = false;
	}
	if (!Application::IsKeyPressed('F'))
	{
		Freleased = true;
		Fpressed = false;

		
	}
	else
	{
		if (Freleased)
		{
			Fpressed = true;
			
		}
		
		Freleased = false;
	}

	//items - batteries
	pickUpItem = false;
	for (int i = 0; i < 3; i++)
	{
		if (garageItems[i] != nullptr)
		{
			if (camera.position.z > garageItems[i]->pos.z - 10 && camera.position.z < garageItems[i]->pos.z + 10
				&& camera.position.x > garageItems[i]->pos.x - 10 && camera.position.x < garageItems[i]->pos.x + 10)
			{
				pickUpItem = true;
				if (Fpressed)
				{
					PickUpItem(garageItems[i]);
					Fpressed = false;
					garageItems[i] = nullptr;
				}
			}
		}
	}


	if (nearExit == true && Fpressed == true)
	{
		exitGarage = true;
		Fpressed = false;
	}


	if (!Application::IsKeyPressed('E'))
	{
		Ereleased = true;
		Epressed = false;
	}
	else
	{
		if (Ereleased)
		{
			Epressed = true;
		}
		Ereleased = false;
	}
	if (!Application::IsKeyPressed('A'))
	{
		Areleased = true;
		Apressed = false;
	}
	else
	{
		if (Areleased)
		{
			Apressed = true;

		}
		Areleased = false;
	}
	if (!Application::IsKeyPressed('D'))
	{
		Dreleased = true;
		Dpressed = false;
	}
	else
	{
		if (Dreleased)
		{
			Dpressed = true;

		}
		Dreleased = false;
	}
	if (!Application::IsKeyPressed('R'))
	{
		Rreleased = true;
		Rpressed = false;
	}
	else
	{
		if (Rreleased)
		{
			Rpressed = true;

		}
		Rreleased = false;
	}

	if (campos_z > -8 && campos_x > -14 && campos_x < 14)
	{
		nearExit = true;
	}
	else {
		nearExit = false;
		showChatbox = false;
	}


	

	if (exitGarage == true && nearExit == true)
	{
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_Main);
		exitGarage = false;
	}
	

	//fps
	fps = 1.f / float(dt);
	//camera
	camera.Update(dt);
	camera.can_move = true;
	//light
	light[0].position.Set(camera.position.x, camera.position.y, camera.position.z);
	light[1].position.Set(camera.position.x, camera.position.y, camera.position.z);
	light[1].spotDirection = -1 * camera.view;
	
	//camera dot blink logic (not the best, but works)
	if (camBlinkOff && camBlinkOffSec >= 0.5)
	{
		camBlinkOn = true;
		camBlinkOff = false;
		camBlinkOffSec = 0;
	}
	if (camBlinkOn)
	{
		camBlinkOnSec += dt;
	}
	if (camBlinkOff)
	{
		camBlinkOffSec += dt;
	}
	if (camBlinkOn && camBlinkOnSec >= 0.5)
	{
		camBlinkOff = true;
		camBlinkOn = false;
		camBlinkOnSec = 0;
	}
	//toggle flashlight on/off

	if (Qpressed)
	{
		Qpressed = false;
		//updates if flashlight status changes
		if (flashlight)
		{
			flashlight = false;
			light[1].power = 0;
			meshList[GEO_OVERLAY]->textureID = LoadTGA("Image//VISIONOFF.tga");
		}
		else if (flashlight_lifetime > 0 && !inLocker)
		{
			flashlight = true;
			light[1].power = 2;
			meshList[GEO_OVERLAY]->textureID = LoadTGA("Image//VISIONON.tga");
		}

		glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	}


	//inventory
	if (Epressed)
	{
		inventory->open = !inventory->open;
		Epressed = false;
	}
	if (inventory->open)
	{
		camera.can_move = false;
		if (Apressed)
		{
			inventory->selected--;
			if (inventory->selected == -1)
			{
				inventory->selected = 7;
			}
			Apressed = false;
		}
		else if (Dpressed)
		{
			inventory->selected++;
			inventory->selected %= 8;
			Dpressed = false;
		}
		else if (Rpressed)
		{
			if (inventory->items[inventory->selected] != nullptr)
			{
				UseItem(inventory->items[inventory->selected]->type);
			}
			//else warning that no item selected?
			Rpressed = false;
		}
	}

	//inventory
	if (Epressed)
	{
		inventory->open = !inventory->open;
		Epressed = false;
	}
	if (inventory->open)
	{
		camera.can_move = false;
		if (Apressed)
		{
			inventory->selected--;
			if (inventory->selected == -1)
			{
				inventory->selected = 7;
			}
			Apressed = false;
		}
		else if (Dpressed)
		{
			inventory->selected++;
			inventory->selected %= 8;
			Dpressed = false;
		}
		else if (Rpressed)
		{
			if (inventory->items[inventory->selected] != nullptr)
			{
				UseItem(inventory->items[inventory->selected]->type);
			}
			//else warning that no item selected?
			Rpressed = false;
		}
	}

	//@pause
	//pause key pressed/released (using p for now, maybe change to esc? // copy over to others)
	if (!Application::IsKeyPressed(VK_ESCAPE))
	{
		PKeyreleased = true;
		PKeypressed = false;
	}
	else
	{
		if (PKeyreleased)
		{
			PKeypressed = true;

		}
		PKeyreleased = false;
	}
	//================================================================

	//@pause
	if (PKeypressed)
	{
		PKeypressed = false;
		gamepaused = true;
		Application::GetCursorPos(&Mousetempx, &Mousetempy);
		Application::pause(true);
	}

	if (flashlight)
	{
		if (flashlight_lifetime >= 0)
		{
			flashlight_lifetime -= float(dt);
		}
		else
		{
			flashlight = false;
			light[1].power = 0;
			meshList[GEO_OVERLAY]->textureID = LoadTGA("Image//VISIONOFF.tga");
			glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
		}
	}

	//switch (SpeakPhase)
	//{
	//	//default
	//case 0:
	//	showChatbox = false;
	//	SpeakTimer = 0;
	//case 14:
	//	SpeakTimer += dt;
	//	if (SpeakTimer > SPEECH_LENGTH_SHORT) {
	//		SpeakTimer = 0;
	//		SpeakPhase = 0;
	//	}
	//}

	campos_x = camera.position.x;
	campos_y = camera.position.y;
	campos_z = camera.position.z;


	//INTERACTION CHECKS
	interact = false;
	Vector3 origin(0, 5, 0);
	//doors
	switch (DS_school)
	{
	case OPEN:
		//doors close on their own
		/*if ((camera.position - origin).Length() >= 20)
		{
			DS_school = CLOSING;
		}
		if (camera.position.x <= 5 && camera.position.x >= -5 && camera.position.z <= -1 && camera.position.z >= -10)
		{
			interact = true;
			interact_message = "Exit School";
			if (Fpressed)
			{
				Fpressed = false;
				Application::setscene(Scene_Main);
			}
		}
		break;
	case CLOSED:
		if (camera.position.x <= 5 && camera.position.x >= -5 && camera.position.z <= -1 && camera.position.z >= -10)
		{
			interact = true;
			interact_message = "Exit School";
			if (Fpressed)
			{
				Fpressed = false;
				DS_school = OPENING;
			}
		}*/
		break;
	case OPENING:
		school_door[0].rotateY -= 20 * float(dt);
		school_door[1].rotateY += 20 * float(dt);
		if (school_door[1].rotateY >= 90)
		{
			Application::setscene(Scene_Main);
		}
		break;
	case CLOSING:
		school_door[0].rotateY += float(20 * dt);
		school_door[1].rotateY -= float(20 * dt);
		if (school_door[1].rotateY <= 0)
		{
			DS_school = CLOSED;
		}
		break;
	}

	origin.Set(10, 5, -95);
	switch (DS_classroom)
	{
	case OPEN:
		//doors close on their own
		if ((camera.position - origin).Length() >= 20)
		{
			DS_classroom = CLOSING;
		}
		if (camera.position.x <= 15 && camera.position.x >= 5 && camera.position.z <= -90 && camera.position.z >= -100)
		{
			interact = true;
			interact_message = "Close Door";
			if (Fpressed)
			{
				Fpressed = false;
				DS_classroom = CLOSING;

				
			}
		}
		break;
	case CLOSED:
		if (camera.position.x <= 15 && camera.position.x >= 5 && camera.position.z <= -90 && camera.position.z >= -100)
		{
			interact = true;
			interact_message = "Open Door";
			if (Fpressed)
			{
				Fpressed = false;
				DS_classroom = OPENING;
				
			}
		}
		break;
	case OPENING:
		classroom_door[0].rotateY += 20 * float(dt);
		classroom_door[1].rotateY -= 20 * float(dt);
		if (classroom_door[0].rotateY >= 90)
		{
			classroom_door[0].rotateY = 90;
			DS_classroom = OPEN;
		}
		break;
	case CLOSING:
		classroom_door[0].rotateY -= 20 * float(dt);
		classroom_door[1].rotateY += 20 * float(dt);
	
		if (classroom_door[0].rotateY <= 0)
		{
			classroom_door[0].rotateY = 0;
			DS_classroom = CLOSED;
		}
		break;
	}

	origin.Set(-10, 5, -50);
	switch (DS_lounge)
	{
	case OPEN:
		//doors close on their own
		if ((camera.position - origin).Length() >= 20)
		{
			DS_lounge = CLOSING;
		}
		if (camera.position.x <= 5 && camera.position.x >= -10 && camera.position.z <= -45 && camera.position.z >= -55)
		{
			interact = true;
			interact_message = "Close Door";
			if (Fpressed)
			{
				Fpressed = false;
				DS_lounge = CLOSING;
			}
		}
		break;
	case CLOSED:
		if (camera.position.x <= 5 && camera.position.x >= -10 && camera.position.z <= -45 && camera.position.z >= -55)
		{
			interact = true;
			interact_message = "Open Door";
			if (Fpressed)
			{
				Fpressed = false;
				DS_lounge = OPENING;
			}
		}
		break;
	case OPENING:
		lounge_door[0].rotateY += 20 * float(dt);
		lounge_door[1].rotateY -= 20 * float(dt);
		if (lounge_door[0].rotateY >= 90)
		{
			lounge_door[0].rotateY = 90;
			DS_lounge = OPEN;
		}
		break;
	case CLOSING:
		lounge_door[0].rotateY -= float(20 * dt);
		lounge_door[1].rotateY += float(20 * dt);
		if (lounge_door[0].rotateY <= 0)
		{
			lounge_door[0].rotateY = 0;
			DS_lounge = CLOSED;
		}
		break;
	}
	//ghost
	switch (ghost->state)
	{
	case Ghost::NORMAL:
		ghost->facing = camera.position - ghost->pos;
		ghost->facing.y = 0;
		ghost->distance = ghost->facing.Length();
		ghost->facing.Normalize();
		ghost->UpdateMovement(dt);

		if (ghost->distance <= 50)
		{
			ghost->state = Ghost::CHASING;
			ghost->speed = 25;
		}
		break;
	case Ghost::CHASING:
		ghost->facing = camera.position - ghost->pos;
		ghost->facing.y = 0;
		ghost->distance = ghost->facing.Length();
		ghost->facing.Normalize();
		ghost->UpdateMovement(dt);
		if (ghost->distance <= 7 && inLocker)
		{

			ghost->state = Ghost::TOLOCKER;
			ghost->waitTime = 3;
		}
		else if (ghost->distance <= 7)
		{
			camera.lockedTarget.Set(ghost->pos.x, ghost->pos.y + 15, ghost->pos.z);
			camera.newTarget = camera.target;
			ghost->state = Ghost::SPIN;
		}
		break;
	case Ghost::TOLOCKER:
		ghost->facing = Lockerlist[ghost->lockerIndex].getfront() - ghost->pos;
		ghost->facing.y = 0;
		ghost->facing.Normalize();
		while (Colliderlist[13 + ghost->lockerIndex].iscollide(ghost->pos + 5 * ghost->facing))
		{
			//change facing
			ghost->facing += (ghost->facing.Cross(ghost->up).Normalized()) * 1 * dt;
			ghost->facing.y = 0;
			ghost->facing.Normalize();
		}

		ghost->UpdateMovement(dt);
		ghost->rawPos = ghost->pos;
		ghost->rawPos.y = 0;
		if ((ghost->rawPos - Lockerlist[ghost->lockerIndex].getfront()).Length() <= 0.5)
		{
			ghost->facing = camera.position - ghost->pos;
			ghost->facing.y = 0;
			ghost->facing.Normalize();
			ghost->state = Ghost::WAITING;
		}
		break;
	case Ghost::WAITING:
		ghost->waitTime -= float(dt);
		ghost->UpdateRotation(dt);
		if (ghost->waitTime <= 0)
		{
			ghost->state = Ghost::SPEEDRUN;
			ghost->speed = 250;
		}
		break;
	case Ghost::SPEEDRUN:
		ghost->facing = ghost->pos - camera.position;
		ghost->facing.y = 0;
		ghost->distance = ghost->facing.Length();
		ghost->facing.Normalize();
		ghost->UpdateMovement(dt);
		if (ghost->distance > 500 || !inLocker)
		{
			ghost->state = Ghost::NORMAL;
			ghost->speed = 5;
		}
		break;
	case Ghost::SPIN:
		camera.can_move = false;


		camera.newTarget += (camera.lockedTarget - camera.target).Normalized() * 10 * dt;
		camera.target = camera.newTarget;
		camera.view = (camera.target - camera.position).Normalized();

		camera.up = camera.defaultUp;
		camera.right = camera.view.Cross(camera.up).Normalized();
		camera.up = camera.right.Cross(camera.view).Normalized();

		if ((camera.lockedTarget - camera.target).Length() < 0.1)
		{
			camera.target = camera.lockedTarget;
			ghost->state = Ghost::DEATH;
		}

		break;
	case Ghost::DEATH:
		camera.can_move = false;

		camera.target = camera.lockedTarget;
		camera.view = (camera.target - camera.position).Normalized();

		camera.up = camera.defaultUp;
		camera.right = camera.view.Cross(camera.up).Normalized();
		camera.up = camera.right.Cross(camera.view).Normalized();

		break;
	default:
		break;

	}
	//Locker
	for (int i = 0; i < signed(Lockerlist.size()); i++) {
		if (Lockerlist[i].gethidden() == true) {
			if (Fpressed) {
				Lockerlist[i].Sethidden(false);
				camera.teleport(Lockerlist[i].getfront());
				glEnable(GL_CULL_FACE);
				inLocker = false;
			}
			else if (suffocationScale <= 0) {
				Lockerlist[i].Sethidden(false);
				camera.teleport(Lockerlist[i].getfront());
				glEnable(GL_CULL_FACE);
				inLocker = false;
			}
		}
		if (Lockerlist[i].status(camera.position, -1*camera.view, Fpressed)) {
			if (Lockerlist[i].gethidden() == false) {
				Lockerlist[i].Sethidden(true);
				ghost->lockerIndex = i;
				flashlight = false;
				camera.teleport(Lockerlist[i].getpos());
				camera.facefrontlocker(Lockerlist[i].getdirection());
				glDisable(GL_CULL_FACE);//To see the inside of the locker
				inLocker = true;
				Fpressed = false;
			}
		}
	}
	if (inLocker == true)
	{

		suffocationScale -= (float)(suffocationScaleDir * dt / 7) * camera.playerStamina;
		suffocationTranslate -= (float)(suffocationTranslateDir * dt / 7) * camera.playerStamina;
		if (suffocationScale <= 0)
		{
			suffocationScaleDir = 0;
		}
		if (suffocationTranslate <= 0)
		{
			suffocationTranslateDir = 0;
		}
	}
	if (inLocker == false)
	{
		suffocationScale = 15;
		suffocationTranslate = 14;
		suffocationScaleDir = 1;
		suffocationTranslateDir = 1;
	}
	//trap detection
	bool detected = false;
	for (int i = 0; i < signed(traplist.size()); i++) {
		switch (traplist[i].TRAPTYPE) {
		case trap::beartrap:
			if (traplist[i].nearby(camera.position)) {
				detected = true;
				
			}
			break;
		}
	}
	if (detected) {
		camera.Setslow(true);
	}
	else {
		camera.Setslow(false);
	}

	//switch scenes button for now
	if (Application::IsKeyPressed('5')) {
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_Menu);
	}
	if (Application::IsKeyPressed('6')) {
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_Main);
	}
	if (Application::IsKeyPressed('7')) {
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_1);
	}
	if (Application::IsKeyPressed('8')) {
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_2);
	}
	if (Application::IsKeyPressed('0')) {
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_4);
	}

	
}

void SceneSP2Room3::PauseUpdate()
{
	//@pause
	Application::hidemousecursor(false);

	if (!Application::IsKeyPressed(VK_ESCAPE))
	{
		PKeyreleased = true;
		PKeypressed = false;
	}
	else
	{
		if (PKeyreleased)
		{
			PKeypressed = true;

		}
		PKeyreleased = false;
	}

	if (PKeypressed)
	{
		PKeypressed = false;
		gamepaused = false;
		Application::hidemousecursor(true);
		Application::SetCursorPos(Mousetempx, Mousetempy);
		Application::pause(false);
	}

	//get mouse positional coords
	Application::GetCursorPos(&Mousex, &Mousey);
	MposX = Mousex / 80;
	MposY = Mousey / 60;
	//get mouse input

	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
		std::cout << "posX:" << MposX << " , posY:" << MposY << std::endl;

		if (MposX > 10.8 && MposX < 13.3 && MposY >5.7 && MposY < 6.5)
		{
			std::cout << "Cont Hit!" << std::endl;
			Application::hidemousecursor(true);
			Application::SetCursorPos(Mousetempx, Mousetempy);
			Application::pause(false);
			gamepaused = false;
		}
		else if (MposX > 10.8 && MposX < 13.3 && MposY >7.6 && MposY < 8.6)
		{
			std::cout << "qMenu Hit!" << std::endl;
			gamepaused = false;
			Application::pause(false);
			Background->setSoundVolume(0.f);
			Effect->setSoundVolume(0.f);
			Jumpscare->setSoundVolume(0.f);
			Heartbeat->setSoundVolume(0.f);
			Application::setscene(Scene_Menu);
		}
		else if (MposX > 11.3 && MposX < 12.7 && MposY >9.6 && MposY < 10.6)
		{
			std::cout << "quit Hit!" << std::endl;
			Application::quit(true);
		}
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;
	}
}

void SceneSP2Room3::Render()
{

	
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y,
		camera.position.z, camera.target.x, camera.target.y,
		camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();
	Mtx44 MVP = projectionStack.Top() * viewStack.Top() *
		modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	//light
	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_POINT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

	}
	if (light[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else if (light[1].type == Light::LIGHT_POINT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);

	}
	//colliderbox for checking
	//@collider
	/*modelStack.PushMatrix();
	modelStack.Translate(Colliderlist[14].getPosition().x, Colliderlist[14].getPosition().y, Colliderlist[14].getPosition().z);
	RenderMesh(meshList[Colliderbox], false);
	modelStack.PopMatrix();*/

	//skybox
	//RenderSkybox();
	//trap rendering
	for (int i = 0; i < signed(traplist.size()); i++) {
		switch (traplist[i].TRAPTYPE) {
		case trap::beartrap:
			modelStack.PushMatrix();
			modelStack.Translate(traplist[i].TrapPosition.x, traplist[i].TrapPosition.y, traplist[i].TrapPosition.z);
			modelStack.Scale(0.5, 0.5, 0.5);
			RenderMesh(meshList[GEO_BEARTRAP], true);
			modelStack.PopMatrix();
			break;
		}
	}
	
	
	


	//all doors
	//schoolleft
	
	modelStack.PushMatrix();
	modelStack.Translate(30, 12, -50);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(25, 1, 100);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-30, 12, -50);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(25, 1, 100);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider
	
	modelStack.PushMatrix();
	modelStack.Translate(0, 12, -100);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 2, 130);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-25, 12,2);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 2, 20);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(25, 12, 2);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 2, 20);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider



	//school floor
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -50);
	modelStack.Scale(165, 1, 100);
	modelStack.Rotate(-90, 1, 0, 0);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();
	//school ceiling
	modelStack.PushMatrix();
	modelStack.Translate(0, 25, -50);
	modelStack.Scale(165, 1, 100);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();
	//longtable in faculty lounge
	//@obj
	modelStack.PushMatrix();
	modelStack.Translate(10, 0, -35);
	modelStack.Scale(0.4f, 0.4f, 0.4f);
	RenderMesh(meshList[tire], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-20, 0, -95);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.08f, 0.08f, 0.08f);
	RenderMesh(meshList[shelves], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-20, 4, -60);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(6,6,6);
	RenderMesh(meshList[garagetable], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(0, 1.5,-50);
	modelStack.Scale(0.13f, 0.13f, 0.13f);
	RenderMesh(meshList[rustycar], true);
	modelStack.PopMatrix();//Added collider
	
	modelStack.PushMatrix();
	modelStack.Translate(-22.f, 1.2f, -25.f);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(0.1f, 0.1f, 0.1f);
	RenderMesh(meshList[rustychair], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(25.f, 0.8f, -30.f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(0.05f, 0.05f, 0.05f);
	RenderMesh(meshList[barrels], true);
	modelStack.PopMatrix();//Added collider


	//modelStack.PushMatrix();
	//modelStack.Translate(25, 0.8, -30);
	//modelStack.Rotate(90, 0, 1, 0);
	//modelStack.Scale(2, 2, 2);
	//RenderMesh(meshList[workbench], true);
	//modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(30, 4, -40);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(19, 19, 19);
	RenderMesh(meshList[wheelbarrow], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(25, 8, -95);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[metalcabinet], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(0, 2.1, 1);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(0.1, 0.12, 0.155);
	RenderMesh(meshList[garagedoor], true);
	modelStack.PopMatrix();

	if (garageItems[0] != nullptr)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-22, 7.8, -95);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(0.27, 0.27, 0.27);
		RenderMesh(meshList[screwdriver], true);
		modelStack.PopMatrix();
	}


	//batteries
	if (garageItems[1] != nullptr) {
		modelStack.PushMatrix();
		modelStack.Translate(-20, 7.5, -60);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(0.03, 0.03, 0.03);
		RenderMesh(meshList[BATTERY], true);
		modelStack.PopMatrix();
	}

	if (garageItems[2] != nullptr) {
		modelStack.PushMatrix();
		modelStack.Translate(25, 0, -60);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(0.06, 0.06, 0.06);
		RenderMesh(meshList[BATTERY], true);
		modelStack.PopMatrix();
	}

	//ghost
	modelStack.PushMatrix();
	modelStack.Translate(ghost->pos.x, ghost->pos.y, ghost->pos.z);
	modelStack.Rotate(-20, ghost->axis.x, 0, ghost->axis.z);
	modelStack.Rotate(ghost->rotateY - 90, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0, -3, 0);
	modelStack.Scale(4.2f, 4.2f, 4.2f);
	RenderMesh(meshList[GEO_MYSTERIOUSMAN], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0.5, 10, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.5, 0.5, 0.5);
	RenderMesh(meshList[GEO_SKULL], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	//lockers
	for (int i = 0; i < signed(Lockerlist.size()); i++) {
		modelStack.PushMatrix();
		modelStack.Translate(Lockerlist[i].getpos().x, Lockerlist[i].getpos().y, Lockerlist[i].getpos().z);
		modelStack.Rotate(Lockerlist[i].getyaw(), 0, 1, 0);
		modelStack.Scale(0.2f, 0.2f, 0.2f);
		RenderMesh(meshList[locker], true);
		modelStack.PopMatrix();
	}
	modelStack.PushMatrix();
	std::stringstream posx;
	posx.precision(4);
	posx << "X:" << campos_x;
	RenderTextOnScreen(meshList[GEO_TEXT], posx.str(), Color(1, 0, 0), 4, 30, 6);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	std::stringstream posz;
	posz.precision(4);
	posz << "Z:" << campos_z;
	RenderTextOnScreen(meshList[GEO_TEXT], posz.str(), Color(1, 0, 0), 4, 30, 10);
	modelStack.PopMatrix();




	//if (garageItems[0] == nullptr && SpeakPhase != 0)
	//{
	//	SpeakPhase = 14;
	//}

	if (showChatbox == true) {
		RenderMeshOnScreen(meshList[GEO_CHATBOX], 40.f, 10.f, 2.f, 0.7f);
	}

	if (pickUpItem)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press F to pick up", Color(0.f, 1.f, 1.f), 4.f, 20.f, 5.f);
	}
	
	if (nearExit == true) {
		showChatbox = true;
		RenderTextOnScreen(meshList[GEO_TEXT], "Press F to Exit", Color(0.f, 0.f, 1.f), 4.f, 10.f, 1.8f);
	}

	//inventory

	//UI OVERLAY

	//Vision vignette
	RenderMeshOnScreen(meshList[GEO_OVERLAY], 40, 30, 1, 1);
	//warning overlay
	if (ghost->state == Ghost::DEATH)
	{
		RenderMeshOnScreen(meshList[GEO_DEATH], 40, 30, 1, 1);
	}
	else if (ghost->state == Ghost::CHASING)
	{
		RenderMeshOnScreen(meshList[GEO_WARNING2], 40, 30, 1, 1);
	}
	else if (ghost->distance <= 100)
	{
		RenderMeshOnScreen(meshList[GEO_WARNING1], 40, 30, 1, 1);
	}
	//camera dot
	if (camBlinkOn) {
		RenderMeshOnScreen(meshList[GEO_REDDOT], 73.5, 52.5, 2.5, 3.5);
	}
	//camcorder
	RenderMeshOnScreen(meshList[GEO_OVERLAY2], 40, 30, 1, 1);
	//breathing icon
	//stamina bar
	RenderMeshOnScreen(meshList[GEO_BAR], 14 - (5 - float(camera.playerStamina) * 0.25f), 52, float(camera.playerStamina) * 0.5f, 1);

	//stamina icon
	RenderMeshOnScreen(meshList[GEO_STAMINA], 6, 52, 2, 2);
	//battery bar
	RenderMeshOnScreen(meshList[GEO_BATTERY], 4.6f + (4.5f - flashlight_lifetime * 0.025f), 6.35f, flashlight_lifetime * 0.05f, 2.1);
	
	if (showSideBox == true) {
		RenderMeshOnScreen(meshList[GEO_SIDEBOX], 10.f, 32.f, 1.f, 2.7f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Objectives:", Color(0.f, 1.f, 0.f), 3.f, 1.f, 11.9f);
	}
	switch (ObjectivePhase)
	{
	case 0:
		if (showSideBox == true) {
			RenderTextOnScreen(meshList[GEO_TEXT], "", Color(1.f, 1.f, 0.f), 2.f, 0.8f, 7.9f);
			break;
		}
	case 1:
		if (showSideBox == true) {
			RenderTextOnScreen(meshList[GEO_TEXT], "Talk to the man at the fountain", Color(1.f, 1.f, 0.f), 2.5f, 1.2f, 11.7f);
			break;
		}
	case 2:
		if (showSideBox == true) {
			modelStack.PushMatrix();
			std::stringstream screwdriver;
			screwdriver << "Screwdriver:" << screwDriverFound;
			RenderTextOnScreen(meshList[GEO_TEXT], screwdriver.str(), Color(1, 1, 0), 2.5f, 1.2f, 12.8f);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			std::stringstream hammer;
			hammer << "Hammer:" << hammerFound;
			RenderTextOnScreen(meshList[GEO_TEXT], hammer.str(), Color(1, 1, 0), 2.5f, 1.2f, 11.6f);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			std::stringstream wrench;
			wrench << "Wrench:" << wrenchFound;
			RenderTextOnScreen(meshList[GEO_TEXT], wrench.str(), Color(1, 1, 0), 2.5f, 1.2f, 10.4f);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			std::stringstream sparkplug;
			sparkplug << "Sparkplug:" << SparkplugFound;
			RenderTextOnScreen(meshList[GEO_TEXT], sparkplug.str(), Color(1, 1, 0), 2.5f, 1.2f, 8.8f);
			modelStack.PopMatrix();

			break;
		}
	}
	//switch (SpeakPhase)
	//{
	//case 0:
	//	RenderTextOnScreen(meshList[GEO_TEXT], "", Color(0, 0, 0), 4, 10, 1.8f);
	//	break;
	//case 14:
	//	RenderTextOnScreen(meshList[GEO_TEXT], "Got the screwdriver..", Color(0.f, 0.f, 0.f), 4.f, 10.f, 1.8f);
	//	break;
	//}
	//inventory
	if (inventory->open)
	{
		RenderMeshOnScreen(meshList[GEO_INVENTORY], 40, 8, 7, 7);

		for (int i = 0; i < 8; i++)
		{
			if (inventory->items[i] != nullptr)
			{
				//item icon in inventory
				RenderMeshOnScreen(itemImage[i], float(25.9 + i * double(4)), 7.9f, 3.5f, 3.5f);
				//number of item if more than 1
				if (inventory->items[i]->count > 1)
				{
					RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(inventory->items[i]->count), Color(1.f, 1.f, 1.f), 2.f, float(33.8 + i * 5), 3.f);
				}
			}
		}

		RenderMeshOnScreen(meshList[GEO_SELECT], float(25.9 + inventory->selected * double(4)), 7.9f, 4.f, 4.f);
		if (inventory->items[inventory->selected] != nullptr)
		{
			RenderMeshOnScreen(meshList[GEO_ITEMDISPLAY], 55, 17, 10, 10);
			RenderTextOnScreen(meshList[GEO_TEXT], inventory->items[inventory->selected]->name, Color(0, 0, 0), 3, 40, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], inventory->items[inventory->selected]->description, Color(0, 0, 0), 2, 60, 8, 35);
		}

	}
	if (inLocker == true)
	{
		RenderMeshOnScreen(meshList[GEO_BAR], 14 - (4.75 - float(suffocationTranslate) * 0.25f), 50, float(suffocationScale) * 0.5f, 1);
	}
	//@pause
	//pause menu, place all the way at the bottom in render
	if (gamepaused)
		RenderMeshOnScreen(meshList[GEO_PAUSEMENU], 40, 30, 35, 54);
}

void SceneSP2Room3::Exit()
{
	// Cleanup VBO here
	for (int i = 0; i < 3; i++)
	{
		if (garageItems[i] != nullptr)
		{
			delete garageItems[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneSP2Room3::RenderSkybox()
{
	//scale, translate, rotate
	modelStack.PushMatrix();
	modelStack.Translate(0+camera.position.x, 0+camera.position.y, 2.0f+camera.position.z);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0+camera.position.x, 0+camera.position.y, -2.0f+camera.position.z);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(2.0f+camera.position.x, 0+camera.position.y, 0+camera.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-2.0f+camera.position.x, 0+camera.position.y, 0+camera.position.z);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0+camera.position.x,-3.0f+camera.position.y, 0+camera.position.z);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0+camera.position.x, 2.0f+camera.position.y, 0+camera.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}


bool SceneSP2Room3::PickUpItem(Item* item)
{
	//picking up item into inventory
	for (int i = 0; i < 8; i++)
	{
		if (inventory->items[i] != nullptr)
		{
			if (inventory->items[i]->name == item->name)
			{
				inventory->items[i]->count++;
				return true;
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (inventory->items[i] == nullptr)
		{
			inventory->items[i] = item;
			itemImage[i]->textureID = LoadTGA(item->image);
			return true;
		}
	}
	return false;
}

void SceneSP2Room3::UseItem(int itemname)
{
	switch (itemname)
	{
	case Item::BATTERY:
		
		flashlight_lifetime = 90;

		//for each item, if use condition is true and item is used pls rmb to set inventory item ptr to nullptr aka copy paste this if else
		if (inventory->items[inventory->selected]->count > 1)
		{
			inventory->items[inventory->selected]->count--;
		}
		else
		{
			delete inventory->items[inventory->selected];
			inventory->items[inventory->selected] = nullptr;
		}
		
		//else warning message?
		break;
	case Item::FLOWER:
		break;
	}
}

void SceneSP2Room3::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() *
		modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE,
		&modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose =
			modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1,
			GL_FALSE, &modelView_inverse_transpose.a[0]);
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1,
			&mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1,
			&mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1,
			&mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS],
			mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	//Texture
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render(); //this line should only be called once
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SceneSP2Room3::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.5f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);

}

void SceneSP2Room3::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 200, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	//Change this line inside for loop
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(0.5f + i * 0.5f, 0.5f, 0);
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}

	//Add these code just before glEnable(GL_DEPTH_TEST);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);

}

void SceneSP2Room3::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, int limit)
{
		if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 200, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	//Change this line inside for loop
	std::string toPrint;
	if (signed(text.length()) > limit)
	{
		toPrint = text.substr(0, limit);
		for (unsigned i = 0; i < toPrint.length(); ++i)
		{
			Mtx44 characterSpacing;
			characterSpacing.SetToTranslation(0.5f + i * 0.5f, 0.5f, 0);
			Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

			mesh->Render((unsigned)text[i] * 6, 6);
		}
		RenderTextOnScreen(meshList[GEO_TEXT], text.substr(limit, text.length()), color, size, x, y - 1, limit);
	}
	else
	{
		toPrint = text;
		for (unsigned i = 0; i < toPrint.length(); ++i)
		{
			Mtx44 characterSpacing;
			characterSpacing.SetToTranslation(0.5f + i * 0.5f, 0.5f, 0);
			Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

			mesh->Render((unsigned)text[i] * 6, 6);
		}
	}
	

	//Add these code just before glEnable(GL_DEPTH_TEST);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneSP2Room3::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI  
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	//to do: scale and translate accordingly
	modelStack.Translate(x, y, 0);
	modelStack.Scale(sizex, sizey, 1);
	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}




