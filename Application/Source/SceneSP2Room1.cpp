#include "SceneSP2Room1.h"
#include "GL\glew.h"
#include <stdlib.h>
#include <time.h>
#include "shader.hpp"
#include "LoadTGA.h"
#include <sstream>
#include "irrKlang.h"

using namespace irrklang;

SceneSP2Room1::SceneSP2Room1()
{
	//if you see anything from here missing in init just copy and paste them 
	camBlinkOn = true;
	camBlinkOff = false;
	camBlinkOffSec = 0;
	camBlinkOnSec = 0;
	showSideBox = true;
	LSPEED = 10.F;
	flashlight = false;
	flashlight_lifetime = 90;
	Qpressed = Qreleased = false;
	Epressed = Ereleased = false;
	Fpressed = Freleased = false;
	Apressed = Areleased = false;
	Dpressed = Dreleased = false;
	Rpressed = Rreleased = false;
	jumpscareTimerReset1 = jumpscareTimer1 = 7.f;
	jumpscareEntrance1 = 0;
	jumpscareActive1 = false;
	jumpscareTimerActive1 = false;
	jumpscareTimerReset2 = jumpscareTimer2 = 7.f;
	jumpscareEntrance2 = 0;
	jumpscareActive2 = false;
	jumpscareTimerActive2 = false;
	jumpscareTimerReset3 = jumpscareTimer3 = 7.f;
	jumpscareEntrance3 = 0;
	jumpscareActive3 = false;
	jumpscareTimerActive3 = false;
	jumpscareTimerReset4 = jumpscareTimer4 = 7.f;
	jumpscareEntrance4 = 0;
	jumpscareActive4 = false;
	jumpscareTimerActive4 = false;
	inLocker = false;
	suffocationScale = 15;
	suffocationScaleDir = 1;
	suffocationTranslate = 15;
	suffocationTranslateDir = 1;
	fps = 60;
	itemImage[0] = meshList[GEO_ITEMIMAGE0];
	itemImage[1] = meshList[GEO_ITEMIMAGE1];
	itemImage[2] = meshList[GEO_ITEMIMAGE2];
	itemImage[3] = meshList[GEO_ITEMIMAGE3];
	itemImage[4] = meshList[GEO_ITEMIMAGE4];
	itemImage[5] = meshList[GEO_ITEMIMAGE5];
	itemImage[6] = meshList[GEO_ITEMIMAGE6];
	itemImage[7] = meshList[GEO_ITEMIMAGE7];

	//@pause
	gamepaused = false;
	PKeypressed = PKeyreleased = false;
	//======
}

SceneSP2Room1::~SceneSP2Room1()
{
	
}


void SceneSP2Room1::Init()
{
	camBlinkOn = true;
	camBlinkOff = false;
	camBlinkOffSec = 0;
	camBlinkOnSec = 0;
	// Init VBO here
	glClearColor(0.5, 0.5, 0.5, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//camera
	camera.Init(Vector3(-30, 9, -340), Vector3(0, 9, 250), Vector3(0, 1,
		0));
	//shaders
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
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
	meshList[LightSphere] = MeshBuilder::Generatesphere("LightBall", 1, 1, 1, Yellow);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Reference", 1, 1, 1);
	//skybox texture
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", 1, 1, White);
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

	//meshList[GEO_BUILDING]->material.kAmbient.Set(0.35, 0.35, 0.35);

	//paths and deco
	meshList[Ground_Mesh] = MeshBuilder::GenerateQuadRepeat("Hell", 1, 1, White);
	//terrain
	meshList[GEO_WALL] = MeshBuilder::GenerateCubeT("walls", 1, 1, 1, 0, 0, 1, 1, Color(1.f, 0.1f, 0.1f));
	meshList[GEO_WALL]->textureID = LoadTGA("Assigment2Images//housewall.tga");
	meshList[GEO_TOPHALFWALL] = MeshBuilder::GenerateCubeT("walls", 1, 1, 1, 0, 1.0f / 22, 0.6, 1, Color(1.f, 0.1f, 0.1f));
	meshList[GEO_TOPHALFWALL]->textureID = LoadTGA("Assigment2Images//housewall.tga");
	meshList[GEO_CEILING] = MeshBuilder::GenerateCubeT("Ceiling", 1, 1, 1, 0, 0, 1, 1, Color(1.f, 0.1f, 0.1f));
	meshList[GEO_CEILING]->textureID = LoadTGA("Assigment2Images//housewall.tga");
	meshList[GEO_FLOOR] = MeshBuilder::GenerateCubeT("Floors", 1, 1, 1, 0, 0, 1, 1, Color(1.f, 0.1f, 0.1f));
	meshList[GEO_FLOOR]->textureID = LoadTGA("Image//ConcreteFloor.tga");
	//meshList[Ground_Mesh]->textureID = LoadTGA("Assigment2Images//GroundMesh.tga");
	meshList[GEO_RIGHTDOOR] = MeshBuilder::GenerateCubeT("door", 1, 1, 1, 0, 0, 1, 1, White);
	meshList[GEO_RIGHTDOOR]->textureID = LoadTGA("Image//schooldoorright.tga");
	//ghost
	meshList[GEO_SKULL] = MeshBuilder::GenerateOBJ("skull", "OBJ//Skull.obj");
	meshList[GEO_SKULL]->material.kAmbient.Set(Gray);
	meshList[GEO_MYSTERIOUSMAN] = MeshBuilder::GenerateOBJ("man npc", "OBJ//man1.obj");
	meshList[GEO_MYSTERIOUSMAN]->textureID = LoadTGA("Image//man1.tga");
	meshList[GEO_MYSTERIOUSMAN]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[SOFA] = MeshBuilder::GenerateOBJ("man npc", "OBJ//sofa2.obj");
	meshList[SOFA]->textureID = LoadTGA("Assigment2Images//sofa2.tga");
	meshList[SOFA]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[TELEVISION] = MeshBuilder::GenerateOBJ("man npc", "OBJ//Tele.obj");
	meshList[TELEVISION]->textureID = LoadTGA("Assigment2Images//tvtexture.tga");
	meshList[TELEVISION]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[TV_STAND] = MeshBuilder::GenerateOBJ("man npc", "OBJ//tvstand.obj");
	meshList[TV_STAND]->textureID = LoadTGA("Assigment2Images//tvstandtexture.tga");
	meshList[TV_STAND]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[SHELVES] = MeshBuilder::GenerateOBJ("man npc", "OBJ//bookshelf.obj");
	meshList[SHELVES]->textureID = LoadTGA("Assigment2Images//shelf.tga");
	meshList[SHELVES]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	


	//Text
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Assigment2images//Arial.tga");
	//light 0
	//light[0].type = Light::LIGHT_POINT;
	//light[0].position.Set(0, 7, 270);
	//light[0].color.Set(White);
	//light[0].power = 0; //Tbc
	//light[0].kC = 1.f;
	//light[0].kL = 0.01f;
	//light[0].kQ = 0.001f;
	//light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	//light[0].cosInner = cos(Math::DegreeToRadian(30));
	//light[0].exponent = 3.f;
	//light[0].spotDirection.Set(0.f, 1.f, 0.f);
	//glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	//glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	//glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	//glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	//glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	//glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	//glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	//glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	//glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);
	//light 1
	/*light[1].type = Light::LIGHT_SPOT;
	light[1].position.Set(0, 5, 270);
	light[1].color.Set(White);
	light[1].power = 2;
	light[1].kC = 1.0f;
	light[1].kL = 0.9f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(7));
	light[1].cosInner = cos(Math::DegreeToRadian(1));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, -1.f, 0.f);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);*/


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


	//camcorder
	meshList[GEO_OVERLAY] = MeshBuilder::GenerateQuad2("vision", 80, 60, 0);
	meshList[GEO_OVERLAY2] = MeshBuilder::GenerateQuad2("camcorder", 80, 60, 0);
	meshList[GEO_OVERLAY2]->textureID = LoadTGA("Image//camcorder2.tga");
	meshList[GEO_REDDOT] = MeshBuilder::GenerateQuad2("dot", 1, 1, White);
	meshList[GEO_REDDOT]->textureID = LoadTGA("Image//redDot.tga");
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
	meshList[GEO_JUMPSCARE1] = MeshBuilder::GenerateQuad2("Jumpscare1", 1, 1, 0);
	meshList[GEO_JUMPSCARE1]->textureID = LoadTGA("Image//skulljumpscare.tga");


	meshList[BATTERY] = MeshBuilder::GenerateOBJ("Building", "OBJ//Battery.obj");
	meshList[BATTERY]->textureID = LoadTGA("Assigment2Images//batterytexture.tga");
	meshList[BATTERY]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	//@pause
	//pause menu
	meshList[GEO_PAUSEMENU] = MeshBuilder::GenerateQuad2("pause", 1, 1, 0);
	meshList[GEO_PAUSEMENU]->textureID = LoadTGA("Image//pause.tga");

	itemImage[0] = meshList[GEO_ITEMIMAGE0];
	itemImage[1] = meshList[GEO_ITEMIMAGE1];
	itemImage[2] = meshList[GEO_ITEMIMAGE2];
	itemImage[3] = meshList[GEO_ITEMIMAGE3];
	itemImage[4] = meshList[GEO_ITEMIMAGE4];
	itemImage[5] = meshList[GEO_ITEMIMAGE5];
	itemImage[6] = meshList[GEO_ITEMIMAGE6];
	itemImage[7] = meshList[GEO_ITEMIMAGE7];


	houseItems[0] = new Item("battery", Item::BATTERY, Vector3(-22, 7.8, -95));
	houseItems[1] = new Item("battery", Item::BATTERY, Vector3(35, 1, -435));
	houseItems[2] = new Item("battery", Item::BATTERY, Vector3(52, 1, -496));

	//UI
	meshList[GEO_CHATBOX] = MeshBuilder::GenerateQuad2("chatbox", 30, 20, 0);
	meshList[GEO_CHATBOX]->textureID = LoadTGA("Assigment2Images//chatbox.tga");
	meshList[GEO_SIDEBOX] = MeshBuilder::GenerateQuad2("chatbox", 30, 20, 0);
	meshList[GEO_SIDEBOX]->textureID = LoadTGA("Assigment2Images//sidebox.tga");

	//init update stuff
	LSPEED = 10.F;
	flashlight = false;
	flashlight_lifetime = 90;
	Qpressed = Qreleased = false;
	Epressed = Ereleased = false;
	Fpressed = Freleased = false;
	DS_MAIN = OPEN;
	DS_LIVING = DS_HALL = DS_CONNECTING = CLOSED;
	rotateY[0] = 90;
	rotateY[1] = 0;
	rotateY[2] = 0;
	rotateY[3] = 0;
	//jumpscare
	jumpscareTimerReset1 = jumpscareTimer1 = 7.f;
	jumpscareEntrance1 = 0;
	jumpscareActive1 = false;
	jumpscareTimerActive1 = false;

	////Jumpscare 2
	//jumpscareTimerReset2 = jumpscareTimer2 = 7.f;
	//jumpscareEntrance2 = 0;
	//jumpscareActive2 = false;
	//jumpscareTimerActive2 = false;

	////Jumpscare 3
	//jumpscareTimerReset3 = jumpscareTimer3 = 7.f;
	//jumpscareEntrance3 = 0;
	//jumpscareActive3 = false;
	//jumpscareTimerActive3 = false;

	////Jumpscare 4
	//jumpscareTimerReset4 = jumpscareTimer4 = 7.f;
	//jumpscareEntrance4 = 0;
	//jumpscareActive4 = false;
	//jumpscareTimerActive4 = false;
	//lockers
	Lockerlist.push_back(Locker());
	Lockerlist[0].setpos(Vector3(-32.5, 0, -480));
	Lockerlist.push_back(Locker());
	Lockerlist[1].setpos(Vector3(66, 0, -445));
	Lockerlist[1].setyaw(180);
	//wall colliders
	Colliderlist.push_back(ColliderBox());
	Colliderlist[0].setlength(5, 15, 3);
	Colliderlist[0].Setposition(Vector3(-32, 7.5, -330));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[1].setlength(15, 20, 3);
	Colliderlist[1].Setposition(Vector3(-22, 10, -330));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[2].setlength(3, 20, 100);
	Colliderlist[2].Setposition(Vector3(-34.5, 10, -380));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[3].setlength(3, 20, 100);
	Colliderlist[3].Setposition(Vector3(-14.5, 10, -380));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[4].setlength(3, 20, 75);
	Colliderlist[4].Setposition(Vector3(-34.5, 10, -467.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[5].setlength(3, 20, 75);
	Colliderlist[5].Setposition(Vector3(40.5, 10, -467.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[6].setlength(70, 20, 3);
	Colliderlist[6].Setposition(Vector3(5.5, 10, -430));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[7].setlength(70, 20, 3);
	Colliderlist[7].Setposition(Vector3(0.5, 10, -505));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[8].setlength(3, 20, 30);
	Colliderlist[8].Setposition(Vector3(28, 10, -520));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[9].setlength(3, 20, 30);
	Colliderlist[9].Setposition(Vector3(68, 10, -520));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[10].setlength(40, 20, 3);
	Colliderlist[10].Setposition(Vector3(48, 10, -535));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[11].setlength(22, 20, 3);
	Colliderlist[11].Setposition(Vector3(52, 10, -505));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[12].setlength(3, 20, 75);
	Colliderlist[12].Setposition(Vector3(47.5, 10, -467.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[13].setlength(3, 20, 75);
	Colliderlist[13].Setposition(Vector3(68, 10, -467.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[14].setlength(25, 20, 3);
	Colliderlist[14].Setposition(Vector3(58, 10, -430));
	//Locker colliders
	Colliderlist.push_back(ColliderBox());
	Colliderlist[15].setlength(3.9, 10, 4.3);
	Colliderlist[15].Setposition(Lockerlist[0].getpos());
	Colliderlist.push_back(ColliderBox());
	Colliderlist[16].setlength(3.9, 10, 4.3);
	Colliderlist[16].Setposition(Lockerlist[1].getpos());
	//door colliders
	//@collider
	Colliderlist.push_back(ColliderBox());
	Colliderlist[17].setlength(5, 15, 3);
	Colliderlist[17].Setposition(Vector3(-32, 7.5, -430));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[18].setlength(5, 15, 3);
	Colliderlist[18].Setposition(Vector3(38, 7.5, -505));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[19].setlength(5, 15, 3);
	Colliderlist[19].Setposition(Vector3(65.5, 7.5, -505));
	//colliderbox for checking any collider(just one)
	meshList[Colliderbox] = MeshBuilder::GenerateColliderBox("Box", Colliderlist[19].getxlength(), Colliderlist[19].getylength(), Colliderlist[19].getzlength());
	//list of colliders
	camera.setchecker(Colliderlist);
	//Locker Mesh
	meshList[locker] = MeshBuilder::GenerateOBJ("Locker", "OBJ//locker.obj");
	meshList[locker]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[locker]->textureID = LoadTGA("Assigment2Images//locker.tga");

	//Set boundary here
	camera.SetBounds(-415, 415, -1500, 360);
	//trap mesh
	meshList[GEO_BEARTRAP] = MeshBuilder::GenerateOBJ("Beartrap", "OBJ//BearTrap.obj");
	meshList[GEO_BEARTRAP]->textureID = LoadTGA("Assigment2Images//BearTrap.tga");
	meshList[GEO_BEARTRAP]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	//trap list
	traplist.push_back(trap(trap::beartrap, Vector3(-31.5, 0.5, -450)));
	traplist.push_back(trap(trap::beartrap, Vector3(39.5, 0.5, -510))); 
	traplist.push_back(trap(trap::beartrap, Vector3(55.5, 0.5, -470)));
}

void SceneSP2Room1::Set(Scene* scene)
{
	inventory = scene->inventory;
	ghost = scene->ghost;
	screwDriverFound = scene->screwDriverFound;
	hammerFound = scene->hammerFound;
	wrenchFound = scene->wrenchFound;
	SparkplugFound = scene->SparkplugFound;
	flashlight = scene->flashlight;
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

	camera.position.Set(-30, 9, -340);
	camera.rawTarget = camera.position;


	//inventory item image
	for (int i = 0; i < 8; i++)
	{
		itemImage[i] = scene->itemImage[i];
	}

}

void SceneSP2Room1::SetBackground()
{
	if (!Jumpscare) {
		Jumpscare = createIrrKlangDevice();
	}
	if (!Background) {
		Background = createIrrKlangDevice();
		Background->play2D("Sound\\Background\\529750__banzai-bonsai__looping-horror-groaning.wav", true);
		
	}
	if (!Effect) {
		Effect = createIrrKlangDevice();
		Effect->play2D("Sound\\Effects\\58453__sinatra314__footsteps-fast-on-pavement-loop.wav", true);
	}
	if (!Heartbeat) {
		Heartbeat = createIrrKlangDevice();
		Heartbeat->play2D("Sound\\Effects\\485076__inspectorj__heartbeat-regular-single-01-01-loop.wav", true);
	}
	Heartbeat->setSoundVolume(0.f);
	Background->setSoundVolume(0.25f);//Volume control
	Effect->setSoundVolume(0.f);
	
}

void SceneSP2Room1::Update(double dt)
{
	// mouse cursor show / hide
	Application::hidemousecursor(true);
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
	else if(ghost->kill == false){
		Heartbeat->setSoundVolume(0.f);
		Background->setSoundVolume(0.5f);
	}
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
	pickUpBattery = false;
	for (int i = 0; i < 3; i++)
	{
		if (houseItems[i] != nullptr)
		{
			if (camera.position.z > houseItems[i]->pos.z - 10 && camera.position.z < houseItems[i]->pos.z + 10
				&& camera.position.x > houseItems[i]->pos.x - 10 && camera.position.x > houseItems[i]->pos.x - 10)
			{
				pickUpBattery = true;
				if (Fpressed)
				{
					PickUpItem(houseItems[i]);
					Fpressed = false;
					houseItems[i] = nullptr;
				}
			}
		}
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
		if (Lockerlist[i].status(camera.position, -1 * camera.view, Fpressed)) {
			if (Lockerlist[i].gethidden() == false) {
				Lockerlist[i].Sethidden(true);
				ghost->lockerIndex = i;
				flashlight = false;
				camera.teleport(Lockerlist[i].getpos());
				glDisable(GL_CULL_FACE);//To see the inside of the locker
				inLocker = true;
				Fpressed = false;
			}
		}

	}
	if (inLocker == true)
	{

		suffocationScale -= (float)(suffocationScaleDir * dt /7) * camera.playerStamina;
		suffocationTranslate -= (float)(suffocationTranslateDir * dt/ 7) * camera.playerStamina;
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

	interact = false;
	Vector3 origin(-32, 7.5, -330);
	switch (DS_MAIN)
	{
	case OPEN:
		//doors close on their own
		if ((camera.position - origin).Length() >= 20)
		{
			DS_MAIN = CLOSING;
		}
		if (camera.position.z <= -325 && camera.position.z >= -335 && camera.position.x <= -29.5 && camera.position.x >= -34.5)
		{
			nearExit = true;
			if (Fpressed)
			{
				Fpressed = false;
				Background->setSoundVolume(0.f);
				Effect->setSoundVolume(0.f);
				Jumpscare->setSoundVolume(0.f);
				Heartbeat->setSoundVolume(0.f);
				Application::setscene(Scene_Main);
			}
		}
		else {
			nearExit = false;
			showChatbox = false;
		}
		break;
	case CLOSED:
		if (camera.position.z <= -325 && camera.position.z >= -335 && camera.position.x <= -29.5 && camera.position.x >= -34.5)
		{
			nearExit = true;
			if (Fpressed)
			{
				Fpressed = false;
				DS_MAIN = OPENING;
			}
		}
		else {
			nearExit = false;
			showChatbox = false;
		}
		break;
	case OPENING:
		rotateY[0] += float(20 * dt);
		if (rotateY[0] >= 90)
		{
			Background->setSoundVolume(0.f);
			Effect->setSoundVolume(0.f);
			Jumpscare->setSoundVolume(0.f);
			Heartbeat->setSoundVolume(0.f);
			Application::setscene(Scene_Main);
		}
		break;
	case CLOSING:
		rotateY[0] -= 20 * float(dt);
		if (rotateY[0] <= 0)
		{
			DS_MAIN = CLOSED;
		}
		break;
	}

	origin.Set(-32, 7.5, -430);
	switch (DS_HALL)
	{
	case OPEN:
		//doors close on their own
		if ((camera.position - origin).Length() >= 20)
		{
			DS_HALL = CLOSING;
			Colliderlist[17].setactive(true);
			camera.setchecker(Colliderlist);
		}
		if (camera.position.z <= -425 && camera.position.z >= -435 && camera.position.x >= -34.5 && camera.position.x <= -29.5)
		{
			interact = true;
			interact_message = "Close Door";
			if (Fpressed)
			{
				Fpressed = false;
				DS_HALL = CLOSING;
				Colliderlist[17].setactive(true);
				camera.setchecker(Colliderlist);
			}
		}
		break;
	case CLOSED:
		if (camera.position.z <= -425 && camera.position.z >= -435 && camera.position.x >= -34.5 && camera.position.x <= -29.5)
		{
			interact = true;
			interact_message = "Open Door";
			if (Fpressed)
			{
				Fpressed = false;
				DS_HALL = OPENING;
				Colliderlist[17].setactive(false);
				camera.setchecker(Colliderlist);
			}
		}
		break;
	case OPENING:
		rotateY[1] += 20 * float(dt);
		if (rotateY[1] >= 90)
		{
			rotateY[1] = 90;
			DS_HALL = OPEN;
		}
		break;
	case CLOSING:
		rotateY[1] -= 20 * float(dt);

		if (rotateY[1] <= 0)
		{
			rotateY[1] = 0;
			DS_HALL = CLOSED;
		}
		break;
	}

	origin.Set(38, 7.5, -505);
	switch (DS_LIVING)
	{
	case OPEN:
		//doors close on their own
		if ((camera.position - origin).Length() >= 20)
		{
			DS_LIVING = CLOSING;
			Colliderlist[18].setactive(true);
			camera.setchecker(Colliderlist);
	
		}
		if (camera.position.z <= -500 && camera.position.z >= -510 && camera.position.x >= 35.5 && camera.position.x <= 40.5)
		{
			interact = true;
			interact_message = "Close Door";
			if (Fpressed)
			{
				Fpressed = false;
				DS_LIVING = CLOSING;
				Colliderlist[18].setactive(true);
				camera.setchecker(Colliderlist);
			}
		}
		break;
	case CLOSED:
		if (camera.position.z <= -500 && camera.position.z >= -510 && camera.position.x >= 35.5 && camera.position.x <= 40.5)
		{
			interact = true;
			interact_message = "Open Door";
			if (Fpressed)
			{
				Fpressed = false;
				DS_LIVING = OPENING;
				Colliderlist[18].setactive(false);
				camera.setchecker(Colliderlist);
			}
		}
		break;
	case OPENING:
		rotateY[2] += 20 * float(dt);
		if (rotateY[2] >= 90)
		{
			rotateY[2] = 90;
			DS_LIVING = OPEN;
		}
		break;
	case CLOSING:
		rotateY[2] -= 20 * float(dt);
		
		if (rotateY[2] <= 0)
		{
			rotateY[2] = 0;
			DS_LIVING = CLOSED;
		}
		break;
	}

	origin.Set(65.5, 7.5, -505);
	switch (DS_CONNECTING)
	{
	case OPEN:
		//doors close on their own
		if ((camera.position - origin).Length() >= 20)
		{
			DS_CONNECTING = CLOSING;
			Colliderlist[19].setactive(true);
			camera.setchecker(Colliderlist);
		}
		if (camera.position.z <= -500 && camera.position.z >= -510 && camera.position.x >= 63 && camera.position.x <= 68)
		{
			interact = true;
			interact_message = "Close Door";
			if (Fpressed)
			{
				Fpressed = false;
				DS_CONNECTING = CLOSING;
				Colliderlist[19].setactive(true);
				camera.setchecker(Colliderlist);
			}
		}
		break;
	case CLOSED:
		if (camera.position.z <= -500 && camera.position.z >= -510 && camera.position.x >= 63 && camera.position.x <= 68)
		{
			interact = true;
			interact_message = "Open Door";
			if (Fpressed)
			{
				Fpressed = false;
				DS_CONNECTING = OPENING;
				Colliderlist[19].setactive(false);
				camera.setchecker(Colliderlist);
			}
		}
		break;
	case OPENING:
		rotateY[3] -= 20 * float(dt);
		if (rotateY[3] <= -90)
		{
			rotateY[3] = -90;
			DS_CONNECTING = OPEN;
		}
		break;
	case CLOSING:
		rotateY[3] += 20 * float(dt);

		if (rotateY[3] >= 0)
		{
			rotateY[3] = 0;
			DS_CONNECTING = CLOSED;
		}
		break;
	}

	/*if (campos_z > -337 && campos_x < -29)
	{
		nearExit = true;
	}
	else {
		nearExit = false;
		showChatbox = false;
	}

	if (exitHouse == true && nearExit == true)
	{
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_Main);
		exitHouse = false;
	}*/
	//fps
	fps = 1.f / float(dt);
	//camera
	camera.Update(dt);
	camera.can_move = true;
	//light
	light[0].position.Set(camera.position.x, camera.position.y, camera.position.z);
	light[1].position.Set(camera.position.x, camera.position.y, camera.position.z);
	light[1].spotDirection = -1 * camera.view;

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
		Application::pause(true);
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
		while (Colliderlist[15 + ghost->lockerIndex].iscollide(ghost->pos + 5 * ghost->facing))
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
			ghost->speed = 50;
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

	//Jumpscare, Entrance hallway
	if ((camera.position.y >= 0) && ((camera.position.x >= -35) && (camera.position.x <= 70)) && ((camera.position.z >= -530) && (camera.position.z <= -330)) && (inLocker == false))
	{
		jumpscareTimerActive1 = true;
	}
	else
	{
		jumpscareTimerActive1 = false;
		jumpscareActive1 = false;
	}
	if (jumpscareTimerActive1 == true)
		jumpscareTimer1 -= dt;
	
	if ((jumpscareTimer1 >= 0.5) && (jumpscareTimer1 <= jumpscareTimerReset1 - 0.2))
	{
		jumpscareActive1 = false;
	}
	if (jumpscareTimer1 <= 0)
	{
		Jumpscare->play2D("Sound\\Jumpscares\\Horror_Sound_Effects_For_Youtubers_-_No_Copyrighted_SFX_For_Video_Editing (mp3cut.net).wav", false);
		Jumpscare->setSoundVolume(1.f);
		jumpscareActive1 = true;
		jumpscareTimer1 = jumpscareTimerReset1 = rand() % 90 + double(45);
	}

	////Jumpscare, living room
	//if ((camera.position.y >= 0) && ((camera.position.x >= -35) && (camera.position.x <= 40)) && ((camera.position.z >= -505) && (camera.position.z <= -430)))
	//{
	//	jumpscareTimerActive2 = true;
	//}
	//else
	//{
	//	jumpscareTimerActive2 = false;
	//	jumpscareActive2 = false;
	//}
	//if (jumpscareTimerActive2 == true)
	//	jumpscareTimer2 -= dt;

	//if ((jumpscareTimer2 >= 0.5) && (jumpscareTimer2 <= jumpscareTimerReset2 - 0.2))
	//{
	//	jumpscareActive2 = false;
	//}
	//if (jumpscareTimer2 <= 0)
	//{
	//	Jumpscare->play2D("Sound\\Jumpscares\\Horror_Sound_Effects_For_Youtubers_-_No_Copyrighted_SFX_For_Video_Editing (mp3cut.net).wav", false);
	//	Jumpscare->setSoundVolume(1.f);
	//	jumpscareActive2 = true;
	//	jumpscareTimer2 = jumpscareTimerReset2 = double(rand() % 5 + double(5));
	//}



	////Jumpscare, Connecting room
	//if ((camera.position.y >= 0) && ((camera.position.x >= 28) && (camera.position.x <= 70)) && ((camera.position.z >= -535) && (camera.position.z <= -505)))
	//{
	//	jumpscareTimerActive3 = true;
	//}
	//else
	//{
	//	jumpscareTimerActive3 = false;
	//	jumpscareActive3 = false;
	//}
	//if (jumpscareTimerActive3 == true)
	//	jumpscareTimer3 -= dt;
	//if ((jumpscareTimer3 >= 0.5) && (jumpscareTimer3 <= jumpscareTimerReset3 - 0.2))
	//{
	//	jumpscareActive3 = false;
	//}
	//if (jumpscareTimer3 <= 0)
	//{
	//	Jumpscare->play2D("Sound\\Jumpscares\\Horror_Sound_Effects_For_Youtubers_-_No_Copyrighted_SFX_For_Video_Editing (mp3cut.net).wav", false);
	//	Jumpscare->setSoundVolume(1.f);
	//	jumpscareActive3 = true;	
	//	jumpscareTimer3 = jumpscareTimerReset3 = double(rand() % 5 + double(5));
	//}



	////Jumpscare, Final room
	//if ((camera.position.y >= 0) && ((camera.position.x >= 50)&& (camera.position.x <= 70)) && ((camera.position.z >= -505) && (camera.position.z <= -430)))
	//{
	//	jumpscareTimerActive4 = true;
	//}
	//else
	//{
	//	jumpscareTimerActive4 = false;
	//	jumpscareActive4 = false;
	//}
	//if (jumpscareTimerActive4 == true)
	//	jumpscareTimer4 -= dt;

	//if ((jumpscareTimer4 >= 0.5) && (jumpscareTimer4 <= jumpscareTimerReset4 - 0.2))
	//{
	//	jumpscareActive4 = false;
	//}
	//if (jumpscareTimer4 <= 0)
	//{
	//	Jumpscare->play2D("Sound\\Jumpscares\\Horror_Sound_Effects_For_Youtubers_-_No_Copyrighted_SFX_For_Video_Editing (mp3cut.net).wav", false);
	//	Jumpscare->setSoundVolume(1.f);
	//	jumpscareActive4 = true;
	//	jumpscareTimer4 = jumpscareTimerReset4 = rand() % 5 + double(5);
	//}
	
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
	if (Application::IsKeyPressed('8')) {
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_2);
	}
	if (Application::IsKeyPressed('9')) {
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_3);
	}
	if (Application::IsKeyPressed('0')) {
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_4);
	}

	campos_x = camera.position.x;
	campos_y = camera.position.y;
	campos_z = camera.position.z;
}

void SceneSP2Room1::PauseUpdate()
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

void SceneSP2Room1::Render()
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


	//skybox
	RenderSkybox();

	//Any one Collider,must make sure correct Colliderlist is entered;
	//@collider
	//modelStack.PushMatrix();
	//modelStack.Translate(Colliderlist[19].getPosition().x, Colliderlist[19].getPosition().y, Colliderlist[19].getPosition().z);
	//RenderMesh(meshList[Colliderbox], false);
	//modelStack.PopMatrix();

	
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

	modelStack.PushMatrix();
	modelStack.Translate(-24.5, 0, -600);
	
	//Main door

	modelStack.PushMatrix();
	modelStack.Translate(-7.5, 7.5, 270);

	modelStack.Translate(-2.5, 0, -0.25);
	modelStack.Rotate(rotateY[0], 0, 1, 0);
	modelStack.Translate(2.5, 0, 0.25);

	modelStack.Scale(5, 15, 0.5);
	RenderMesh(meshList[GEO_RIGHTDOOR], true);
	modelStack.PopMatrix();//Added collider

	//wall on door
	modelStack.PushMatrix();
	modelStack.Translate(-7.5, 20, 270);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_TOPHALFWALL], true);
	modelStack.PopMatrix();

	//Back wall
	modelStack.PushMatrix();
	modelStack.Translate(2.5, 10, 270);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(15, 1, 20);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider

	//Hall 1
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 220);
	modelStack.Scale(20, 1, 100);
	RenderMesh(meshList[GEO_FLOOR], true);
	modelStack.PopMatrix();

	//door
	modelStack.PushMatrix();
	modelStack.Translate(-7.5, 7.5, 170);
	
	modelStack.Translate(-2.5, 0, -0.25);
	modelStack.Rotate(rotateY[1], 0, 1, 0);
	modelStack.Translate(2.5, 0, 0.25);

	modelStack.Scale(5,15,0.5);
	RenderMesh(meshList[GEO_RIGHTDOOR], true);
	modelStack.PopMatrix();//Added collider

	//wall on door
	modelStack.PushMatrix();
	modelStack.Translate(-7.5, 20, 170);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_TOPHALFWALL], true);
	modelStack.PopMatrix();

	//Left wall
	modelStack.PushMatrix();
	modelStack.Translate(-10.5, 10, 220);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(20, 1, 100);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider

	//right wall
	modelStack.PushMatrix();
	modelStack.Translate(10, 10, 220);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(20, 1, 100);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider


	//Living room
	modelStack.PushMatrix();
	modelStack.Translate(27.5, 0, 132.5);
	modelStack.Scale(75, 1, 75);
	RenderMesh(meshList[GEO_FLOOR], true);
	modelStack.PopMatrix();

	//Door
	modelStack.PushMatrix();
	modelStack.Translate(62.5, 7.5, 95);
	modelStack.Translate(-2.5, 0, -0.25);
	modelStack.Rotate(rotateY[2], 0, 1, 0);
	modelStack.Translate(2.5, 0, 0.25);
	modelStack.Scale(5, 15, 0.5);
	RenderMesh(meshList[GEO_RIGHTDOOR], true);
	modelStack.PopMatrix();//Added collider

	//Door wall
	modelStack.PushMatrix();
	modelStack.Translate(62.25, 20, 95);
	modelStack.Scale(4.5, 10, 1);
	RenderMesh(meshList[GEO_TOPHALFWALL], true);
	modelStack.PopMatrix();

	//Left wall
	modelStack.PushMatrix();
	modelStack.Translate(-10, 10, 132.5);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(20, 1, 75);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider

	//Right wall
	modelStack.PushMatrix();
	modelStack.Translate(65, 10, 132.5);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(20, 1, 76);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider
	
	//Back wall
	modelStack.PushMatrix();
	modelStack.Translate(30, 10, 170);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(70, 1, 20);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider

	//Front wall
	modelStack.PushMatrix();
	modelStack.Translate(25, 10, 95);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(70, 1, 20);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider

	//Connecting room
	modelStack.PushMatrix();
	modelStack.Translate(72.5, 0, 80);
	modelStack.Scale(40, 1, 30);
	RenderMesh(meshList[GEO_FLOOR], true);
	modelStack.PopMatrix();

	//Door
	modelStack.PushMatrix();
	modelStack.Translate(90, 7.5, 95);

	modelStack.Translate(2.5, 0, 0.25);
	modelStack.Rotate(rotateY[3], 0, 1, 0);
	modelStack.Translate(-2.5, 0, -0.25);

	modelStack.Scale(5, 15, 0.5);
	RenderMesh(meshList[GEO_RIGHTDOOR], true);
	modelStack.PopMatrix();

	//Doorwall
	modelStack.PushMatrix();
	modelStack.Translate(90, 20, 95);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_TOPHALFWALL], true);
	modelStack.PopMatrix();
	
	//Right wall
	modelStack.PushMatrix();
	modelStack.Translate(52.5, 10, 80);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(20, 1, 30);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider

	//Left wall
	modelStack.PushMatrix();
	modelStack.Translate(93, 10, 80);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(20, 1, 30);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider
	
	//Front wall
	modelStack.PushMatrix();
	modelStack.Translate(72.5, 10, 65);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(40, 1, 20);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider

	//Back wall
	modelStack.PushMatrix();
	modelStack.Translate(76.5, 10, 95);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(22, 1, 20);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider



	//Hall 2
	modelStack.PushMatrix();
	modelStack.Translate(82.5, 0, 132.5);
	modelStack.Scale(20, 1, 75);
	RenderMesh(meshList[GEO_FLOOR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(72, 10, 132.5);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(20, 1, 75);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider
	
	modelStack.PushMatrix();
	modelStack.Translate(92.5, 10, 132.5);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(20, 1, 75);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(82.5, 10, 170);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(25, 1, 20);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();//Added collider


	modelStack.PushMatrix();
	modelStack.Translate(27.5, 20, 132.5);
	modelStack.Scale(300, 1, 300);
	RenderMesh(meshList[GEO_CEILING], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(10, 1, -480);
	modelStack.Scale(0.07, 0.07, 0.07);
	RenderMesh(meshList[SOFA], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(15, 9, -450);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[TELEVISION], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(10, 4, -450);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(0.03, 0.03, 0.03);
	RenderMesh(meshList[TV_STAND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 6, -500);
	modelStack.Scale(8, 8, 8);
	RenderMesh(meshList[SHELVES], true);
	modelStack.PopMatrix();




	//items
	for (int i = 0; i < 3; i++)
	{
		if (houseItems[i] != nullptr)
		{
			modelStack.PushMatrix();
			modelStack.Translate(houseItems[i]->pos.x, houseItems[i]->pos.y, houseItems[i]->pos.z);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(0.03, 0.03, 0.03);
			RenderMesh(meshList[BATTERY], true);
			modelStack.PopMatrix();
		}
	}

	//lockers
	for (int i = 0; i < signed(Lockerlist.size()); i++) {
		modelStack.PushMatrix();
		modelStack.Translate(Lockerlist[i].getpos().x, Lockerlist[i].getpos().y, Lockerlist[i].getpos().z);
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
	


	if (showChatbox == true) {
		RenderMeshOnScreen(meshList[GEO_CHATBOX], 40.f, 10.f, 2.f, 0.7f);
	}

	if (nearExit == true) {
		showChatbox = true;
		RenderTextOnScreen(meshList[GEO_TEXT], "Press F to Exit", Color(0.f, 0.f, 1.f), 4.f, 10.f, 1.8f);
	}
	//UI OVERLAY

	if (jumpscareActive1 == true)
	{
		RenderMeshOnScreen(meshList[GEO_JUMPSCARE1], 40, 30, 100, 100);
	}
	//Vision vignette
	RenderMeshOnScreen(meshList[GEO_OVERLAY], 40, 30, 1, 1);
	//warning overlay
	if (ghost->state == Ghost::DEATH)
	{
		RenderMeshOnScreen(meshList[GEO_DEATH], 40, 30, 1, 1);
	}
	else if (ghost->distance <= 50)
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

	if (pickUpBattery)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press F to pick up", Color(0.f, 1.f, 1.f), 4.f, 20.f, 5.f);
	}



	if (showSideBox == true) {
		RenderMeshOnScreen(meshList[GEO_SIDEBOX], 10.f, 32.f, 1.f, 2.7f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Objectives:", Color(0.f, 1.f, 0.f), 3.f, 1.f, 12.1f);
	}
	//objectives
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
	if (inLocker == true)
	{
		RenderMeshOnScreen(meshList[GEO_BAR], 14 - (4.75 - float(suffocationTranslate) * 0.25f), 50, float(suffocationScale) * 0.5f, 1);
	}
	//battery bar
	RenderMeshOnScreen(meshList[GEO_BATTERY], 4.6f + (4.5f - flashlight_lifetime * 0.025f), 6.35f, flashlight_lifetime * 0.05f, 2.1);
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
	//INTERACTIONS
	if (interact)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], interact_message, Color(1, 1, 0), 4, 22, 5);
	}


	//if (jumpscareActive2 == true)
	//{
	//	RenderMeshOnScreen(meshList[GEO_JUMPSCARE1], 40, 30, 100, 100);
	//}

	//if (jumpscareActive3 == true)
	//{
	//	RenderMeshOnScreen(meshList[GEO_JUMPSCARE1], 40, 30, 100, 100);
	//}

	//if (jumpscareActive4 == true)
	//{
	//	RenderMeshOnScreen(meshList[GEO_JUMPSCARE1], 40, 30, 100, 100);
	//}

	RenderTextOnScreen(meshList[GEO_TEXT], "X:" + std::to_string(camera.position.x), Color(0, 1, 0), 3, 35, 5);
	RenderTextOnScreen(meshList[GEO_TEXT], "Y:" + std::to_string(camera.position.y), Color(0, 1, 0), 3, 35, 4);
	RenderTextOnScreen(meshList[GEO_TEXT], "Z:" + std::to_string(camera.position.z), Color(0, 1, 0), 3, 35, 3);
	//RenderTextOnScreen(meshList[GEO_TEXT], "Jumpscare Timer1: " + std::to_string(jumpscareTimer1), Color(1, 1, 1), 3, 20, 5);
	//RenderTextOnScreen(meshList[GEO_TEXT], "Jumpscare Timer2: " + std::to_string(jumpscareTimer2), Color(1, 1, 1), 3, 20, 4);
	//RenderTextOnScreen(meshList[GEO_TEXT], "Jumpscare Timer3: " + std::to_string(jumpscareTimer3), Color(1, 1, 1), 3, 20, 3);
	//RenderTextOnScreen(meshList[GEO_TEXT], "Jumpscare Timer4: " + std::to_string(jumpscareTimer4), Color(1, 1, 1), 3, 20, 2);


	/*std::ostringstream test1;
	test1 << "camera view: " << camera.view;
	RenderTextOnScreen(meshList[GEO_TEXT], test1.str(), Color(0, 1, 0), 4, 0, 6);
	std::ostringstream test3;
	test3 << "light[1]spotdirec: " << light[1].spotDirection;
	RenderTextOnScreen(meshList[GEO_TEXT], test3.str(), Color(0, 1, 0), 4, 0, 3);*/
	//std::ostringstream test2;
	//test2 << "camera view: " << camera.view;
	//RenderTextOnScreen(meshList[GEO_TEXT], test2.str(), Color(0, 1, 0), 4, 0, 9);
	////checking
	//std::cout << camera.position.x << std::endl;
	//std::cout << camera.position.z << std::endl;

	//@pause
	//pause menu, place all the way at the bottom in render
	if (gamepaused)
		RenderMeshOnScreen(meshList[GEO_PAUSEMENU], 40, 30, 35, 54);
}

void SceneSP2Room1::Exit()
{
	// Cleanup VBO here

	for (int i = 0; i < 3; i++)
	{
		if (houseItems[i] != nullptr)
		{
			delete houseItems[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneSP2Room1::RenderSkybox()
{
	//scale, translate, rotate
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 0 + camera.position.y, 2.0f + camera.position.z);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 0 + camera.position.y, -2.0f + camera.position.z);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(2.0f + camera.position.x, 0 + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-2.0f + camera.position.x, 0 + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, -3.0f + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 2.0f + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2000, 2000, 2000);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}


//void SceneSP2Room1::RenderDeadTree(int x, int z,float rotate)
//{
//	modelStack.PushMatrix();
//	modelStack.Translate(x, -5, z);
//	modelStack.Rotate(rotate, 0, 0, 1);
//	modelStack.Scale(5, 5, 5);
//	RenderMesh(meshList[Deadtrees], true);
//	modelStack.PopMatrix();
//}

void SceneSP2Room1::RenderMesh(Mesh* mesh, bool enableLight)
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
void SceneSP2Room1::UseItem(int itemname)
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
	case Item::ITEM2:
		break;
	}
}

bool SceneSP2Room1::PickUpItem(Item* item)
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
void SceneSP2Room1::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneSP2Room1::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SceneSP2Room1::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, int limit)
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

void SceneSP2Room1::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey)
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