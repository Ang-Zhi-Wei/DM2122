#include "SceneSP2Main.h"
#include "GL\glew.h"
#include <stdlib.h>
#include <time.h>
#include "shader.hpp"
#include "LoadTGA.h"
#include <sstream>
#include <iostream>


using namespace irrklang;

SceneSP2Main::SceneSP2Main()
{
	//if you see anything from here missing in init just copy and paste them 
	camBlinkOn = true;
	camBlinkOff = false;
	showChatbox = true;
	showSideBox = true;
	SpeakPhase = 1;
	SpeakTimer = 0;
	SparkplugFound = 0;
	hammerFound = 0;
	wrenchFound = 0;
	screwDriverFound = 0;
	Interact_Num = 0;
	manAppear = true;
	nearBattery,nearBattery1,nearBattery2, nearBattery3, nearBattery4 = false;
	canTalk_man = true;
	rotate_Man = 90;
	ObjectivePhase = 0;
	is_talking = false;
	LSPEED = 10.F;
	flashlight = false;
	flashlight_lifetime = 90;
	inLocker = false;
	NearGarage = false;
	enterBuilding = false;
	Qpressed = Qreleased = false;
	Epressed = Ereleased = false;
	Fpressed = Freleased = false;
	Apressed = Areleased = false;
	Dpressed = Dreleased = false;
	Rpressed = Rreleased = false;
	PKeypressed = PKeyreleased = false;
	Application::GetCursorPos(&Mousex, &Mousey);
	MposX = Mousex / 80;
	MposY = Mousey / 60;
	campos_x = camera.position.x;
	campos_y = camera.position.y;
	campos_z = camera.position.z;
	fps = 60;
	camBlinkOffSec = 0;
	camBlinkOnSec = 0;
	gamepaused = false;
	itemImage[0] = meshList[GEO_ITEMIMAGE0];
	itemImage[1] = meshList[GEO_ITEMIMAGE1];
	itemImage[2] = meshList[GEO_ITEMIMAGE2];
	itemImage[3] = meshList[GEO_ITEMIMAGE3];
	itemImage[4] = meshList[GEO_ITEMIMAGE4];
	itemImage[5] = meshList[GEO_ITEMIMAGE5];
	itemImage[6] = meshList[GEO_ITEMIMAGE6];
	itemImage[7] = meshList[GEO_ITEMIMAGE7];
}

SceneSP2Main::~SceneSP2Main()
{
}


void SceneSP2Main::Init()
{
	camBlinkOffSec = 0;
	camBlinkOnSec = 0;
	camBlinkOn = true;
	camBlinkOff = false;
	showChatbox = true;
	showSideBox = true;
	SpeakPhase = 1;
	SpeakTimer = 0;
	Interact_Num = 0;
	canTalk_man = true;
	rotate_Man = 90;
	ObjectivePhase = 0;
	is_talking = false;
	// Init VBO here
	glClearColor(0.5, 0.5, 0.5, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//camera



	camera.Init(Vector3(0, 9, 270), Vector3(0, 9, 250), Vector3(0, 1, 0));

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
	//light 2
	m_parameters[U_LIGHT2_TYPE] =
		glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] =
		glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] =
		glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] =
		glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] =
		glGetUniformLocation(m_programID, "lights[2].exponent");
	m_parameters[U_LIGHT2_POSITION] =
		glGetUniformLocation(m_programID,
			"lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] =
		glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] =
		glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID,
		"lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID,
		"lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID,
		"lights[2].kQ");

	//light 3
	m_parameters[U_LIGHT3_TYPE] =
		glGetUniformLocation(m_programID, "lights[3].type");
	m_parameters[U_LIGHT3_SPOTDIRECTION] =
		glGetUniformLocation(m_programID, "lights[3].spotDirection");
	m_parameters[U_LIGHT3_COSCUTOFF] =
		glGetUniformLocation(m_programID, "lights[3].cosCutoff");
	m_parameters[U_LIGHT3_COSINNER] =
		glGetUniformLocation(m_programID, "lights[3].cosInner");
	m_parameters[U_LIGHT3_EXPONENT] =
		glGetUniformLocation(m_programID, "lights[3].exponent");
	m_parameters[U_LIGHT3_POSITION] =
		glGetUniformLocation(m_programID,
			"lights[3].position_cameraspace");
	m_parameters[U_LIGHT3_COLOR] =
		glGetUniformLocation(m_programID, "lights[3].color");
	m_parameters[U_LIGHT3_POWER] =
		glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID,
		"lights[3].kC");
	m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID,
		"lights[3].kL");
	m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID,
		"lights[3].kQ");

	//light 4 
	m_parameters[U_LIGHT4_TYPE] =
		glGetUniformLocation(m_programID, "lights[4].type");
	m_parameters[U_LIGHT4_SPOTDIRECTION] =
		glGetUniformLocation(m_programID, "lights[4].spotDirection");
	m_parameters[U_LIGHT4_COSCUTOFF] =
		glGetUniformLocation(m_programID, "lights[4].cosCutoff");
	m_parameters[U_LIGHT4_COSINNER] =
		glGetUniformLocation(m_programID, "lights[4].cosInner");
	m_parameters[U_LIGHT4_EXPONENT] =
		glGetUniformLocation(m_programID, "lights[4].exponent");
	m_parameters[U_LIGHT4_POSITION] =
		glGetUniformLocation(m_programID,
			"lights[4].position_cameraspace");
	m_parameters[U_LIGHT4_COLOR] =
		glGetUniformLocation(m_programID, "lights[4].color");
	m_parameters[U_LIGHT4_POWER] =
		glGetUniformLocation(m_programID, "lights[4].power");
	m_parameters[U_LIGHT4_KC] = glGetUniformLocation(m_programID,
		"lights[4].kC");
	m_parameters[U_LIGHT4_KL] = glGetUniformLocation(m_programID,
		"lights[4].kL");
	m_parameters[U_LIGHT4_KQ] = glGetUniformLocation(m_programID,
		"lights[4].kQ");

	//light 5
	m_parameters[U_LIGHT5_TYPE] =
		glGetUniformLocation(m_programID, "lights[5].type");
	m_parameters[U_LIGHT5_SPOTDIRECTION] =
		glGetUniformLocation(m_programID, "lights[5].spotDirection");
	m_parameters[U_LIGHT5_COSCUTOFF] =
		glGetUniformLocation(m_programID, "lights[5].cosCutoff");
	m_parameters[U_LIGHT5_COSINNER] =
		glGetUniformLocation(m_programID, "lights[5].cosInner");
	m_parameters[U_LIGHT5_EXPONENT] =
		glGetUniformLocation(m_programID, "lights[5].exponent");
	m_parameters[U_LIGHT5_POSITION] =
		glGetUniformLocation(m_programID,
			"lights[5].position_cameraspace");
	m_parameters[U_LIGHT5_COLOR] =
		glGetUniformLocation(m_programID, "lights[5].color");
	m_parameters[U_LIGHT5_POWER] =
		glGetUniformLocation(m_programID, "lights[5].power");
	m_parameters[U_LIGHT5_KC] = glGetUniformLocation(m_programID,
		"lights[5].kC");
	m_parameters[U_LIGHT4_KL] = glGetUniformLocation(m_programID,
		"lights[5].kL");
	m_parameters[U_LIGHT4_KQ] = glGetUniformLocation(m_programID,
		"lights[5].kQ");
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
	projection.SetToPerspective(46.f, 4.f / 3.f, 0.1f, 3000.f);
	projectionStack.LoadMatrix(projection);
	glUseProgram(m_programID);
	//mesh
	meshList[LightSphere] = MeshBuilder::Generatesphere("LightBall", 1, 1, 1, Yellow);
	meshList[GEO_LIGHTBULB] = MeshBuilder::Generatesphere("LightBall", 1, 1, 1, Yellow);
	meshList[GEO_LIGHTBULB]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_LIGHTBULB]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_LIGHTBULB]->material.kShininess = 1.f;
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
	//building
	meshList[GEO_BUILDING] = MeshBuilder::GenerateOBJ("Building", "OBJ//simplebuilding.obj");
	meshList[GEO_BUILDING]->textureID = LoadTGA("Assigment2Images//buildingtexture.tga");
	meshList[GEO_BUILDING]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[GEO_ROAD] = MeshBuilder::GenerateOBJ("Building", "OBJ//road.obj");
	meshList[GEO_ROAD]->textureID = LoadTGA("Assigment2Images//road.tga");
	meshList[GEO_ROAD]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[GEO_TREES] = MeshBuilder::GenerateOBJ("Building", "OBJ//pine2.obj");
	meshList[GEO_TREES]->textureID = LoadTGA("Assigment2Images//pine2.tga");
	meshList[GEO_TREES]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[GEO_FOUNTAIN] = MeshBuilder::GenerateOBJ("Building", "OBJ//fountain.obj");
	meshList[GEO_FOUNTAIN]->textureID = LoadTGA("Assigment2Images//fountaintexture.tga");
	meshList[GEO_FOUNTAIN]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[GEO_WATER] = MeshBuilder::Generatesphere("Building", 30, 30, 30, 5);
	meshList[GEO_WATER]->textureID = LoadTGA("Assigment2Images//water.tga");
	meshList[GEO_WATER]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[GEO_SPAWN] = MeshBuilder::Generatesphere("spawn", 30, 30, 30, 5);
	meshList[GEO_SPAWN]->textureID = LoadTGA("Assigment2Images//cement.tga");
	meshList[GEO_SPAWN]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[GEO_PATH] = MeshBuilder::GenerateQuad("spawn", 1, 1, White);
	meshList[GEO_PATH]->textureID = LoadTGA("Assigment2Images//pavement.tga");
	meshList[GEO_PATH]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[GEO_LAMP] = MeshBuilder::GenerateOBJ("Building", "OBJ//lamppost.obj");
	meshList[GEO_LAMP]->textureID = LoadTGA("Assigment2Images//metal.tga");
	meshList[GEO_LAMP]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[GEO_BENCH] = MeshBuilder::GenerateOBJ("Building", "OBJ//ParkBench.obj");
	meshList[GEO_BENCH]->textureID = LoadTGA("Assigment2Images//benchtexture.tga");
	meshList[GEO_BENCH]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("Building", "OBJ//benchtable.obj");
	meshList[GEO_TABLE]->textureID = LoadTGA("Assigment2Images//benchtexture2.tga");
	meshList[GEO_TABLE]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[GEO_FENCE] = MeshBuilder::GenerateOBJ("Building", "OBJ//wall.obj");
	meshList[GEO_FENCE]->textureID = LoadTGA("Assigment2Images//metalgate.tga");
	meshList[GEO_FENCE]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[GEO_GATE] = MeshBuilder::GenerateOBJ("Building", "OBJ//gate.obj");
	meshList[GEO_GATE]->textureID = LoadTGA("Assigment2Images//metalgate.tga");
	meshList[GEO_GATE]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[GEO_PAVEMENT] = MeshBuilder::GenerateQuad("pavement", 1, 1, White);
	meshList[GEO_PAVEMENT]->textureID = LoadTGA("Assigment2Images//pavement3.tga");
	meshList[GEO_PAVEMENT]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[Ground_Mesh2] = MeshBuilder::GenerateQuadRepeat("pavement", 1, 1, White);
	meshList[Ground_Mesh2]->textureID = LoadTGA("Assigment2Images//burnedground.tga");
	meshList[Ground_Mesh2]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[HAUNTEDSCHOOL] = MeshBuilder::GenerateOBJ("Building", "OBJ//school.obj");
	meshList[HAUNTEDSCHOOL]->textureID = LoadTGA("Assigment2Images//school.tga");
	meshList[HAUNTEDSCHOOL]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[HOUSE] = MeshBuilder::GenerateOBJ("Building", "OBJ//smallhouse.obj");
	meshList[HOUSE]->textureID = LoadTGA("Assigment2Images//smallhouse.tga");
	meshList[HOUSE]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[HOSPITAL] = MeshBuilder::GenerateOBJ("Building", "OBJ//hospital.obj");
	meshList[HOSPITAL]->textureID = LoadTGA("Assigment2Images//hospital.tga");
	meshList[HOSPITAL]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[GARAGE] = MeshBuilder::GenerateOBJ("Building", "OBJ//garage2.obj");
	meshList[GARAGE]->textureID = LoadTGA("Assigment2Images//garagetexture.tga");
	meshList[GARAGE]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[GARAGEDOOR] = MeshBuilder::GenerateOBJ("Building", "OBJ//garagedoor.obj");
	meshList[GARAGEDOOR]->textureID = LoadTGA("Assigment2Images//garagedoor.tga");
	meshList[GARAGEDOOR]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	//meshList[GEO_GHOST] = MeshBuilder::GenerateOBJ("ghost", "OBJ//Ghost03.obj");
	//meshList[GEO_GHOST]->textureID = LoadTGA("Image//ghostskin.tga");
	meshList[GEO_SKULL] = MeshBuilder::GenerateOBJ("skull", "OBJ//Skull.obj");
	meshList[GEO_SKULL]->material.kAmbient.Set(Gray);
	//Mysterious man
	meshList[GEO_MYSTERIOUSMAN] = MeshBuilder::GenerateOBJ("man npc", "OBJ//man1.obj");
	meshList[GEO_MYSTERIOUSMAN]->textureID = LoadTGA("Image//man1.tga");
	meshList[GEO_MYSTERIOUSMAN]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[GEO_SIGN] = MeshBuilder::GenerateOBJ("Wooden Signs", "OBJ//WoodenSignBlend.obj");
	meshList[GEO_SIGN]->textureID = LoadTGA("Image//BrownWood.tga");

	//meshList[GEO_BUILDING]->material.kAmbient.Set(0.35, 0.35, 0.35);

	meshList[BATTERY] = MeshBuilder::GenerateOBJ("Building", "OBJ//Battery.obj");
	meshList[BATTERY]->textureID = LoadTGA("Assigment2Images//batterytexture.tga");
	meshList[BATTERY]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	//paths and deco
	meshList[Ground_Mesh] = MeshBuilder::GenerateQuadRepeat("Hell", 1, 1, White);
	//meshList[Ground_Mesh]->textureID = LoadTGA("Assigment2Images//GroundMesh.tga");
	meshList[Ground_Mesh]->textureID = LoadTGA("Image//PathTexture.tga");
	meshList[Ground_Mesh]->material.kAmbient.Set(0.f, 0.20f, 0.13f);





	//truck
	meshList[GEO_TRUCK] = MeshBuilder::GenerateOBJ("truck", "OBJ//truck.obj");
	meshList[GEO_TRUCK]->textureID = LoadTGA("Image//Silver.tga");
	meshList[GEO_TRUCK]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	//Text
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Assigment2Images//Arial.tga");
	//light 0
	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(0, 7, 270);
	light[0].color.Set(White);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);
	//light 1
	light[1].type = Light::LIGHT_SPOT;
	light[1].position.Set(0, 5, 270);
	light[1].color.Set(White);
	light[1].power = 0;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
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
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

	light[2].type = Light::LIGHT_SPOT;
	light[2].position.Set(-40, 30, -34);
	light[2].color.Set(Yellow);
	light[2].power = 2;
	light[2].kC = 1.f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(35));
	light[2].cosInner = cos(Math::DegreeToRadian(20));
	light[2].exponent = 3.f;
	light[2].spotDirection.Set(0.f, 1.f, 0.f);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &light[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[2].kQ);
	glUniform1i(m_parameters[U_LIGHT2_TYPE], light[2].type);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], light[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], light[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[2].exponent);

	light[3].type = Light::LIGHT_SPOT;
	light[3].position.Set(40, 30, -34);
	light[3].color.Set(Yellow);
	light[3].power = 2;
	light[3].kC = 1.f;
	light[3].kL = 0.01f;
	light[3].kQ = 0.001f;
	light[3].cosCutoff = cos(Math::DegreeToRadian(35));
	light[3].cosInner = cos(Math::DegreeToRadian(20));
	light[3].exponent = 3.f;
	light[3].spotDirection.Set(0.f, 1.f, 0.f);
	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &light[3].color.r);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], light[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], light[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], light[3].kQ);
	glUniform1i(m_parameters[U_LIGHT3_TYPE], light[3].type);
	glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], light[3].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT3_COSINNER], light[3].cosInner);
	glUniform1f(m_parameters[U_LIGHT3_EXPONENT], light[3].exponent);



	//light 4 
	light[4].type = Light::LIGHT_SPOT;
	light[4].position.Set(35.5, 30, 131);
	light[4].color.Set(Yellow);
	light[4].power = 2;
	light[4].kC = 1.f;
	light[4].kL = 0.01f;
	light[4].kQ = 0.001f;
	light[4].cosCutoff = cos(Math::DegreeToRadian(35));
	light[4].cosInner = cos(Math::DegreeToRadian(20));
	light[4].exponent = 3.f;
	light[4].spotDirection.Set(0.f, 1.f, 0.f);
	glUniform3fv(m_parameters[U_LIGHT4_COLOR], 1, &light[4].color.r);
	glUniform1f(m_parameters[U_LIGHT4_POWER], light[4].power);
	glUniform1f(m_parameters[U_LIGHT4_KC], light[4].kC);
	glUniform1f(m_parameters[U_LIGHT4_KL], light[4].kL);
	glUniform1f(m_parameters[U_LIGHT4_KQ], light[4].kQ);
	glUniform1i(m_parameters[U_LIGHT4_TYPE], light[4].type);
	glUniform1f(m_parameters[U_LIGHT4_COSCUTOFF], light[4].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT4_COSINNER], light[4].cosInner);
	glUniform1f(m_parameters[U_LIGHT4_EXPONENT], light[4].exponent);

	//light 5
	light[5].type = Light::LIGHT_SPOT;
	light[5].position.Set(-35, 30, 131);
	light[5].color.Set(Yellow);
	light[5].power = 2;
	light[5].kC = 1.f;
	light[5].kL = 0.01f;
	light[5].kQ = 0.001f;
	light[5].cosCutoff = cos(Math::DegreeToRadian(35));
	light[5].cosInner = cos(Math::DegreeToRadian(20));
	light[5].exponent = 3.f;
	light[5].spotDirection.Set(0.f, 1.f, 0.f);
	glUniform3fv(m_parameters[U_LIGHT5_COLOR], 1, &light[5].color.r);
	glUniform1f(m_parameters[U_LIGHT5_POWER], light[5].power);
	glUniform1f(m_parameters[U_LIGHT5_KC], light[5].kC);
	glUniform1f(m_parameters[U_LIGHT5_KL], light[5].kL);
	glUniform1f(m_parameters[U_LIGHT5_KQ], light[5].kQ);
	glUniform1i(m_parameters[U_LIGHT5_TYPE], light[5].type);
	glUniform1f(m_parameters[U_LIGHT5_COSCUTOFF], light[5].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT5_COSINNER], light[5].cosInner);
	glUniform1f(m_parameters[U_LIGHT5_EXPONENT], light[5].exponent);


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
	//colliders

	//lamp colliders
	Colliderlist.push_back(ColliderBox());
	Colliderlist[0].setlength(5, 20, 5);
	Colliderlist[0].Setposition(Vector3(50, -4, -35));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[1].setlength(5, 20, 5);
	Colliderlist[1].Setposition(Vector3(-50, -4, -35));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[2].setlength(5, 20, 5);
	Colliderlist[2].Setposition(Vector3(-45, -4, -130));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[3].setlength(5, 20, 5);
	Colliderlist[3].Setposition(Vector3(45, -4, -130));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[4].setlength(5, 20, 5);
	Colliderlist[4].Setposition(Vector3(-45, -4, 130));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[5].setlength(5, 20, 5);
	Colliderlist[5].Setposition(Vector3(45, -4, 130));
	//fountain collider
	Colliderlist.push_back(ColliderBox());
	Colliderlist[6].setlength(33, 20, 30);
	Colliderlist[6].Setposition(Vector3(0, -3, 0));
	//truck collider
	Colliderlist.push_back(ColliderBox());
	Colliderlist[7].setlength(50, 20, 20);
	Colliderlist[7].Setposition(Vector3(35, 6, 357));
	//bench colliders
	Colliderlist.push_back(ColliderBox());
	Colliderlist[8].setlength(10, 20, 25);
	Colliderlist[8].Setposition(Vector3(-40, 5, -80));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[9].setlength(10, 20, 25);
	Colliderlist[9].Setposition(Vector3(-40, 5, -170));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[10].setlength(10, 20, 25);
	Colliderlist[10].Setposition(Vector3(40, 5, -80));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[11].setlength(10, 20, 25);
	Colliderlist[11].Setposition(Vector3(40, 5, -170));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[12].setlength(10, 20, 25);
	Colliderlist[12].Setposition(Vector3(-40, 5, 80));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[13].setlength(10, 20, 25);
	Colliderlist[13].Setposition(Vector3(-40, 5, 170));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[14].setlength(10, 20, 25);
	Colliderlist[14].Setposition(Vector3(40, 5, 80));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[15].setlength(10, 20, 25);
	Colliderlist[15].Setposition(Vector3(40, 5, 170));
	//Fence colliders
	//Front/Back Fence
	Colliderlist.push_back(ColliderBox());
	Colliderlist[16].setlength(52, 50, 10);
	Colliderlist[16].Setposition(Vector3(-50, -7, 295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[17].setlength(52, 50, 10);
	Colliderlist[17].Setposition(Vector3(-102, -7, 295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[18].setlength(52, 50, 10);
	Colliderlist[18].Setposition(Vector3(-153, -7, 295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[19].setlength(52, 50, 10);
	Colliderlist[19].Setposition(Vector3(-205, -7, 295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[20].setlength(52, 50, 10);
	Colliderlist[20].Setposition(Vector3(-257, -7, 295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[21].setlength(52, 50, 10);
	Colliderlist[21].Setposition(Vector3(-308, -7, 295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[22].setlength(52, 50, 10);
	Colliderlist[22].Setposition(Vector3(50, -7, 295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[23].setlength(52, 50, 10);
	Colliderlist[23].Setposition(Vector3(102, -7, 295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[24].setlength(52, 50, 10);
	Colliderlist[24].Setposition(Vector3(153, -7, 295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[25].setlength(52, 50, 10);
	Colliderlist[25].Setposition(Vector3(205, -7, 295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[26].setlength(52, 50, 10);
	Colliderlist[26].Setposition(Vector3(257, -7, 295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[27].setlength(52, 50, 10);
	Colliderlist[27].Setposition(Vector3(308, -7, 295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[28].setlength(52, 50, 10);
	Colliderlist[28].Setposition(Vector3(-50, -7, -295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[29].setlength(52, 50, 10);
	Colliderlist[29].Setposition(Vector3(-102, -7, -295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[30].setlength(52, 50, 10);
	Colliderlist[30].Setposition(Vector3(-153, -7, -295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[31].setlength(52, 50, 10);
	Colliderlist[31].Setposition(Vector3(-205, -7, -295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[32].setlength(52, 50, 10);
	Colliderlist[32].Setposition(Vector3(-257, -7, -295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[33].setlength(52, 50, 10);
	Colliderlist[33].Setposition(Vector3(-308, -7, -295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[34].setlength(52, 50, 10);
	Colliderlist[34].Setposition(Vector3(50, -7, -295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[35].setlength(52, 50, 10);
	Colliderlist[35].Setposition(Vector3(102, -7, -295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[36].setlength(52, 50, 10);
	Colliderlist[36].Setposition(Vector3(153, -7, -295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[37].setlength(52, 50, 10);
	Colliderlist[37].Setposition(Vector3(205, -7, -295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[38].setlength(52, 50, 10);
	Colliderlist[38].Setposition(Vector3(257, -7, -295));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[39].Setposition(Vector3(308, -7, -295));
	Colliderlist[39].setlength(52, 50, 10);
	//left/right fence
	//@fence
	Colliderlist.push_back(ColliderBox());
	Colliderlist[40].setlength(10, 50, 52);
	Colliderlist[40].Setposition(Vector3(-335, -7, 271));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[41].setlength(10, 50, 52);
	Colliderlist[41].Setposition(Vector3(-335, -7, 225));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[42].setlength(10, 50, 52);
	Colliderlist[42].Setposition(Vector3(-335, -7, 178));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[43].setlength(10, 50, 52);
	Colliderlist[43].Setposition(Vector3(-335, -7, 127));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[44].setlength(10, 50, 52);
	Colliderlist[44].Setposition(Vector3(-335, -7, 75));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[45].setlength(10, 50, 52);
	Colliderlist[45].Setposition(Vector3(-335, -7, 45.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[46].setlength(10, 50, 52);
	Colliderlist[46].Setposition(Vector3(-335, -7, -271));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[47].setlength(10, 50, 52);
	Colliderlist[47].Setposition(Vector3(-335, -7, -225));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[48].setlength(10, 50, 52);
	Colliderlist[48].Setposition(Vector3(-335, -7, -178));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[49].setlength(10, 50, 52);
	Colliderlist[49].Setposition(Vector3(-335, -7, -127));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[50].setlength(10, 50, 52);
	Colliderlist[50].Setposition(Vector3(-335, -7, -75));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[51].setlength(10, 50, 52);
	Colliderlist[51].Setposition(Vector3(-335, -7, -45.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[52].setlength(10, 50, 52);
	Colliderlist[52].Setposition(Vector3(335, -7, 271));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[53].setlength(10, 50, 52);
	Colliderlist[53].Setposition(Vector3(335, -7, 225));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[54].setlength(10, 50, 52);
	Colliderlist[54].Setposition(Vector3(335, -7, 178));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[55].setlength(10, 50, 52);
	Colliderlist[55].Setposition(Vector3(335, -7, 127));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[56].setlength(10, 50, 52);
	Colliderlist[56].Setposition(Vector3(335, -7, 75));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[57].setlength(10, 50, 52);
	Colliderlist[57].Setposition(Vector3(335, -7, 45.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[58].setlength(10, 50, 52);
	Colliderlist[58].Setposition(Vector3(335, -7, -271));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[59].setlength(10, 50, 52);
	Colliderlist[59].Setposition(Vector3(335, -7, -225));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[60].setlength(10, 50, 52);
	Colliderlist[60].Setposition(Vector3(335, -7, -178));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[61].setlength(10, 50, 52);
	Colliderlist[61].Setposition(Vector3(335, -7, -127));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[62].setlength(10, 50, 52);
	Colliderlist[62].Setposition(Vector3(335, -7, -75));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[63].setlength(10, 50, 52);
	Colliderlist[63].Setposition(Vector3(335, -7, -45.5));
	//Tree colliders
	Colliderlist.push_back(ColliderBox());
	Colliderlist[64].setlength(10, 20, 10);
	Colliderlist[64].Setposition(Vector3(60, 5, 280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[65].setlength(10, 20, 10);
	Colliderlist[65].Setposition(Vector3(120, 5, 280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[66].setlength(10, 20, 10);
	Colliderlist[66].Setposition(Vector3(180, 5, 280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[67].setlength(10, 20, 10);
	Colliderlist[67].Setposition(Vector3(250, 5, 280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[68].setlength(10, 20, 10);
	Colliderlist[68].Setposition(Vector3(320, 5, 280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[69].setlength(10, 20, 10);
	Colliderlist[69].Setposition(Vector3(-60, 5, 280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[70].setlength(10, 20, 10);
	Colliderlist[70].Setposition(Vector3(-120, 5, 280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[71].setlength(10, 20, 10);
	Colliderlist[71].Setposition(Vector3(-180, 5, 280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[72].setlength(10, 20, 10);
	Colliderlist[72].Setposition(Vector3(-250, 5, 280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[73].setlength(10, 20, 10);
	Colliderlist[73].Setposition(Vector3(-320, 5, 280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[74].setlength(10, 20, 10);
	Colliderlist[74].Setposition(Vector3(60, 5, -280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[75].setlength(10, 20, 10);
	Colliderlist[75].Setposition(Vector3(120, 5, -280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[76].setlength(10, 20, 10);
	Colliderlist[76].Setposition(Vector3(180, 5, -280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[77].setlength(10, 20, 10);
	Colliderlist[77].Setposition(Vector3(250, 5, -280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[78].setlength(10, 20, 10);
	Colliderlist[78].Setposition(Vector3(320, 5, -280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[79].setlength(10, 20, 10);
	Colliderlist[79].Setposition(Vector3(-60, 5, -280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[80].setlength(10, 20, 10);
	Colliderlist[80].Setposition(Vector3(-120, 5, -280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[81].setlength(10, 20, 10);
	Colliderlist[81].Setposition(Vector3(-180, 5, -280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[82].setlength(10, 20, 10);
	Colliderlist[82].Setposition(Vector3(-250, 5, -280));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[83].setlength(10, 20, 10);
	Colliderlist[83].Setposition(Vector3(310, 5, -230));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[84].setlength(10, 20, 10);
	Colliderlist[84].Setposition(Vector3(310, 5, -170));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[85].setlength(10, 20, 10);
	Colliderlist[85].Setposition(Vector3(310, 5, -110));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[86].setlength(10, 20, 10);
	Colliderlist[86].Setposition(Vector3(310, 5, -50));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[87].setlength(10, 20, 10);
	Colliderlist[87].Setposition(Vector3(310, 5, 230));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[88].setlength(10, 20, 10);
	Colliderlist[88].Setposition(Vector3(310, 5, 170));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[89].setlength(10, 20, 10);
	Colliderlist[89].Setposition(Vector3(310, 5, 110));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[90].setlength(10, 20, 10);
	Colliderlist[90].Setposition(Vector3(310, 5, 50));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[91].setlength(10, 20, 10);
	Colliderlist[91].Setposition(Vector3(-310, 5, -230));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[92].setlength(10, 20, 10);
	Colliderlist[92].Setposition(Vector3(-310, 5, -170));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[93].setlength(10, 20, 10);
	Colliderlist[93].Setposition(Vector3(-310, 5, -110));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[94].setlength(10, 20, 10);
	Colliderlist[94].Setposition(Vector3(-310, 5, -50));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[95].setlength(10, 20, 10);
	Colliderlist[95].Setposition(Vector3(-310, 5, 230));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[96].setlength(10, 20, 10);
	Colliderlist[96].Setposition(Vector3(-310, 5, 170));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[97].setlength(10, 20, 10);
	Colliderlist[97].Setposition(Vector3(-310, 5, 110));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[98].setlength(10, 20, 10);
	Colliderlist[98].Setposition(Vector3(-310, 5, 50));
	//Bench colliders
	Colliderlist.push_back(ColliderBox());
	Colliderlist[99].setlength(25, 20, 10);
	Colliderlist[99].Setposition(Vector3(110, 2, 30));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[100].setlength(25, 20, 10);
	Colliderlist[100].Setposition(Vector3(170, 2, 30));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[101].setlength(25, 20, 10);
	Colliderlist[101].Setposition(Vector3(110, 2, -30));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[102].setlength(25, 20, 10);
	Colliderlist[102].Setposition(Vector3(170, 2, -30));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[103].setlength(25, 20, 10);
	Colliderlist[103].Setposition(Vector3(-110, 2, 30));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[104].setlength(25, 20, 10);
	Colliderlist[104].Setposition(Vector3(-170, 2, 30));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[105].setlength(25, 20, 10);
	Colliderlist[105].Setposition(Vector3(-110, 2, -30));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[106].setlength(25, 20, 10);
	Colliderlist[106].Setposition(Vector3(-170, 2, -30));
	//Gate colliders
	Colliderlist.push_back(ColliderBox());
	Colliderlist[107].setlength(1, 20, 35);
	Colliderlist[107].Setposition(Vector3(-25, -4, 275));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[108].setlength(1, 20, 35);
	Colliderlist[108].Setposition(Vector3(25, -4, 275));
	//Table colliders same position add 1.5
	Colliderlist.push_back(ColliderBox());
	Colliderlist[109].setlength(28, 20, 23);
	Colliderlist[109].Setposition(Vector3(130, 8, 211.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[110].setlength(28, 20, 23);
	Colliderlist[110].Setposition(Vector3(220, 8, 211.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[111].setlength(28, 20, 23);
	Colliderlist[111].Setposition(Vector3(130, 8, 131.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[112].setlength(28, 20, 23);
	Colliderlist[112].Setposition(Vector3(220, 8, 131.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[113].setlength(28, 20, 23);
	Colliderlist[113].Setposition(Vector3(-130, 8, 211.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[114].setlength(28, 20, 23);
	Colliderlist[114].Setposition(Vector3(-220, 8, 211.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[115].setlength(28, 20, 23);
	Colliderlist[115].Setposition(Vector3(-130, 8, 131.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[116].setlength(28, 20, 23);
	Colliderlist[116].Setposition(Vector3(-220, 8, 131.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[117].setlength(28, 20, 23);
	Colliderlist[117].Setposition(Vector3(130, 8, -208.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[118].setlength(28, 20, 23);
	Colliderlist[118].Setposition(Vector3(220, 8, -208.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[119].setlength(28, 20, 23);
	Colliderlist[119].Setposition(Vector3(130, 8, -128.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[120].setlength(28, 20, 23);
	Colliderlist[120].Setposition(Vector3(220, 8, -128.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[121].setlength(28, 20, 23);
	Colliderlist[121].Setposition(Vector3(-130, 8, -208.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[122].setlength(28, 20, 23);
	Colliderlist[122].Setposition(Vector3(-220, 8, -208.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[123].setlength(28, 20, 23);
	Colliderlist[123].Setposition(Vector3(-130, 8, -128.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[124].setlength(28, 20, 23);
	Colliderlist[124].Setposition(Vector3(-220, 8, -128.5));
	//Main building colliders
	//@collider
	Colliderlist.push_back(ColliderBox());
	Colliderlist[125].setlength(107, 100, 100);
	Colliderlist[125].Setposition(Vector3(-0.5, -3, -470));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[126].setlength(30, 100, 30);
	Colliderlist[126].Setposition(Vector3(60, -3, -495));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[127].setlength(58, 100, 110);
	Colliderlist[127].Setposition(Vector3(-516, -2, 0));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[128].setlength(5, 100, 10);
	Colliderlist[128].Setposition(Vector3(-535, -2, -60));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[129].setlength(3, 100, 3);
	Colliderlist[129].Setposition(Vector3(-566, -2, 27));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[130].setlength(3, 100, 3);
	Colliderlist[130].Setposition(Vector3(-566, -2, -27));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[131].setlength(100, 100, 267);
	Colliderlist[131].Setposition(Vector3(533, -1, -17.60));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[132].setlength(5, 100, 5);
	Colliderlist[132].Setposition(Vector3(469, -1, -148.25));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[133].setlength(5, 100, 5);
	Colliderlist[133].Setposition(Vector3(469, -1, -107));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[134].setlength(5, 100, 5);
	Colliderlist[134].Setposition(Vector3(469, -1, -55.75));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[135].setlength(5, 100, 5);
	Colliderlist[135].Setposition(Vector3(469, -1, -3));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[136].setlength(5, 100, 5);
	Colliderlist[136].Setposition(Vector3(469, -1, 57.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[137].setlength(5, 100, 5);
	Colliderlist[137].Setposition(Vector3(469, -1, 113.5));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[138].setlength(70, 100, 105);
	Colliderlist[138].Setposition(Vector3(0, -4, 510));
	//colliderbox for checking any collider(just one)
	meshList[Colliderbox] = MeshBuilder::GenerateColliderBox("Box", Colliderlist[45].getxlength(), Colliderlist[45].getylength(), Colliderlist[45].getzlength());
	//list of colliders
	camera.setchecker(Colliderlist);


	//Locker test
	meshList[locker] = MeshBuilder::GenerateOBJ("Locker", "OBJ//locker.obj");
	meshList[locker]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[locker]->textureID = LoadTGA("Assigment2Images//locker.tga");
	//list of lockers
	//Lockerlist.push_back(Locker());
	//Lockerlist[0].setpos(Vector3(0, -4.5, 0));
	//Set boundary here
	//camera.SetBounds(-415, 415, -365, 360); original one
	camera.SetBounds(-715, 715, -715, 720);

	ghost = new Ghost;
	inventory = new Inventory;

	//test examples for item
	/*test.Set("item2testAAAA", Item::ITEM2);
	test2.Set("Battery", Item::BATTERY);
	battery.Set("Battery", Item::BATTERY);*/
	items[0] = new Item("battery", Item::BATTERY, (0, -3, 340));
	items[1] = new Item("battery", Item::BATTERY, (60, -3, 0));
	items[2] = new Item("battery", Item::BATTERY, (-60, -3, 100));
	items[3] = new Item("battery", Item::BATTERY, (-200, -3, -200));
	items[4] = new Item("battery", Item::BATTERY, (255, -3, -190));
//to be called only in one frame. placed under init just for testing first
	//PickUpItem(&test2); //to be called only in one frame.
	//PickUpItem(&battery);
	//PickUpItem(&test);
	//PickUpItem(&test2);
	//PickUpItem(&test2);
	
	//trap mesh
	meshList[GEO_BEARTRAP] = MeshBuilder::GenerateOBJ("Beartrap", "OBJ//BearTrap.obj");
	meshList[GEO_BEARTRAP]->textureID = LoadTGA("Assigment2Images//BearTrap.tga");
	meshList[GEO_BEARTRAP]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	//trap list

	
	
}


void SceneSP2Main::Set(Scene* scene)
{
	screwDriverFound = scene->screwDriverFound;
	hammerFound = scene->hammerFound;
	wrenchFound = scene->wrenchFound;
	SparkplugFound = scene->SparkplugFound;
	inventory = scene->inventory;
	if (ghost->state == Ghost::UNSPAWNED)
	{
		//ghost->pos.Set(0, 0, -1000);
		ghost->state = Ghost::NORMAL;
	}
	else
	{
		ghost = scene->ghost;
	}
	flashlight = scene->flashlight;
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
	light[2].power = 2;
	light[3].power = 2;
	light[4].power = 2;
	light[5].power = 2;
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

void SceneSP2Main::SetBackground() {
	//Background sound loop
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
		Heartbeat->play2D("Sound\\Effects\\485076__inspectorj__heartbeat-regular-single-01-01-loop.wav",true);
	}
	Heartbeat->setSoundVolume(0.f);
	Effect->setSoundVolume(0.f);
	Background->setSoundVolume(0.5f);//Volume control
}
void SceneSP2Main::Update(double dt)
{
	// mouse cursor show / hide
	//Application::hidemousecursor(true);
	if (camera.movement) {
		Effect->setSoundVolume(0.5f);
	}
	else {
		Effect->setSoundVolume(0.f);
	}
	
	
	//sounds when ghost get too close
	if (ghost->kill==false && ghost->state==Ghost::SPIN) {
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

	//interaction hitbox checker
	if (campos_x > -1 && campos_x < 1 && campos_z> 26 && campos_z < 30 && canTalk_man)
	{
		Interact_Num = 1;
		static bool ButtonState2 = false;
		if (!ButtonState2 && Application::IsKeyPressed('F'))
		{
			ButtonState2 = true;
		}
		else if (ButtonState2 && !Application::IsKeyPressed('F'))
		{
			ButtonState2 = false;
			std::cout << " F BUTTON UP" << std::endl;
			SpeakPhase = 3;
		}
	}
	else
	{
		Interact_Num = 0;
	}

	//speech phase case statements
	double SPEECH_LENGTH_FAST = 2;
	double SPEECH_LENGTH_SHORT = 3;
	double SPEECH_LENGTH_MEDIUM = 5;
	double SPEECH_LENGTH_LONG = 8;
	
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

	if (nearBattery == true && Fpressed == true)
	{
		PickUpItem(items[0]);
		nearBattery = false;
		Fpressed = false;
		items[0] = NULL;
		
	}

	if (nearBattery1 == true && Fpressed == true)
	{
		PickUpItem(items[1]);
		nearBattery1 = false;
		Fpressed = false;
		items[1] = NULL;

	}

	if (nearBattery2 == true && Fpressed == true)
	{
		PickUpItem(items[2]);
		nearBattery2 = false;
		Fpressed = false;
		items[2] = NULL;

	}

	if (nearBattery3 == true && Fpressed == true)
	{
		PickUpItem(items[3]);
		nearBattery3 = false;
		Fpressed = false;
		items[3] = NULL;

	}

	if (nearBattery4 == true && Fpressed == true)
	{
		PickUpItem(items[4]);
		nearBattery4 = false;
		Fpressed = false;
		items[4] = NULL;

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
				camera.teleport(temp);
				glEnable(GL_CULL_FACE);
				inLocker = false;
			}
		}
		if (Lockerlist[i].status(camera.position, -1 * camera.view, Fpressed)) {
			if (Lockerlist[i].gethidden() == false) {
				Lockerlist[i].Sethidden(true);
				temp.Set(camera.position.x, camera.position.y, camera.position.z);
				camera.teleport(Lockerlist[i].getpos());
				glDisable(GL_CULL_FACE);//To see the inside of the locker
				inLocker = true;
			}
		}

	}

	if (campos_z > 328 && campos_z < 350 && campos_x > -5 && campos_x < 5 && items[0] != nullptr )
	{
		nearBattery = true;
	}
	else {
		nearBattery = false;
	}


	if (campos_z < 15 && campos_z > 5  && campos_x > 53 && campos_x < 64 && items[1] != nullptr )
	{

		nearBattery1 = true;
	}
	else {
		nearBattery1 = false;
	}


	if (campos_z < 112 && campos_z > 100 && campos_x > -63 && campos_x < -53 && items[2] != nullptr)
	{

		nearBattery2 = true;
	}
	else {
		nearBattery2 = false;
	}

	if (campos_z < -186 && campos_z > -195 && campos_x > -187 && campos_x < -175 && items[3] != nullptr)
	{

		nearBattery3 = true;
	}
	else {
		nearBattery3 = false;
	}

	if (campos_z < -178 && campos_z > -190 && campos_x > 240 && campos_x < 255 && items[4] != nullptr)
	{

		nearBattery4 = true;
	}
	else {
		nearBattery4 = false;
	}
	


	if (campos_z > 430 && campos_x > -17 && campos_x < 17 && ObjectivePhase >= 2)
	{
		NearGarage = true;
	}
	else {
		NearGarage = false;
	}

	if (campos_z < -415 && campos_z > -420 && campos_x > -10 && campos_x < 10 && ObjectivePhase >= 2)
	{
		NearHouse = true;
	}
	else {
		NearHouse = false;
	}


	if (campos_x > 470 && campos_x < 480 && campos_z > -26 && campos_z < -13 && ObjectivePhase >= 2)
	{
		NearSchool = true;
	}
	else {
		NearSchool = false;
	}

	if (campos_x < -479 && campos_z > -44 && campos_z < -30 && ObjectivePhase >= 2)
	{
		NearHospital = true;
	}
	else {
		NearHospital = false;
	}
	if (Fpressed == true)
	{
		if (NearGarage == true || NearHouse == true || NearSchool == true || NearHospital == true)
		{
			enterBuilding = true;
			Fpressed = false;
			manAppear = false;
		}
	}

	if (enterBuilding == true && NearGarage == true)
	{

		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_3);
		enterBuilding = false;

	}

	else if (enterBuilding == true && NearHouse == true)
	{
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_1);
		enterBuilding = false;
	}


	else if (enterBuilding == true && NearSchool == true)
	{
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_2);
		enterBuilding = false;
	}

	else if (enterBuilding == true && NearHospital == true)
	{
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_4);
		enterBuilding = false;
	}

	//fps
	fps = 1.f / float(dt);
	//camera
	camera.Update(dt);
	camera.can_move = true;


	//check if talking (stops camera)
	if (is_talking)
		camera.can_move = false;
	else
		camera.can_move = true;


	switch (SpeakPhase)
	{
		//default
	case 0:
		if (NearGarage == false && NearHouse == false && NearSchool == false && NearHospital == false) {
			showChatbox = false;
			SpeakTimer = 0;
		}
		break;
		//starting phase
	case 1:
		showChatbox = true;
		SpeakTimer += dt;
		if (SpeakTimer > SPEECH_LENGTH_SHORT) {
			SpeakPhase++;
			SpeakTimer = 0;
		}
		break;
	case 2:
		SpeakTimer += dt;
		if (SpeakTimer > SPEECH_LENGTH_SHORT) {
			ObjectivePhase = 1;
			SpeakTimer = 0;
			SpeakPhase = 0;
		}
		break;


		//talking to man part
	case 3:
		is_talking = true;
		canTalk_man = false;
		showChatbox = true;
		SpeakTimer += dt;
		if (SpeakTimer > SPEECH_LENGTH_SHORT) {
			SpeakPhase++;
			SpeakTimer = 0;
		}
		break;
	case 4:
		//man turns around
		rotate_Man = -90;
		SpeakTimer += dt;
		if (SpeakTimer > SPEECH_LENGTH_SHORT) {
			SpeakTimer = 0;
			SpeakPhase++;
		}
		break;
	case 5:
		SpeakTimer += dt;
		if (SpeakTimer > SPEECH_LENGTH_SHORT) {
			SpeakTimer = 0;
			SpeakPhase++;
		}
		break;
	case 6:
		SpeakTimer += dt;
		if (SpeakTimer > SPEECH_LENGTH_MEDIUM) {
			SpeakTimer = 0;
			SpeakPhase++;
		}
		break;
	case 7:
		SpeakTimer += dt;
		if (SpeakTimer > SPEECH_LENGTH_SHORT) {
			SpeakTimer = 0;
			SpeakPhase++;
		}
		break;
	case 8:
		SpeakTimer += dt;
		if (SpeakTimer > SPEECH_LENGTH_FAST) {
			SpeakTimer = 0;
			SpeakPhase++;
		}
		break;
	case 9:
		SpeakTimer += dt;
		if (SpeakTimer > SPEECH_LENGTH_FAST) {
			SpeakTimer = 0;
			SpeakPhase++;
		}
		break;
	case 10:
		SpeakTimer += dt;
		if (SpeakTimer > SPEECH_LENGTH_MEDIUM) {
			SpeakTimer = 0;
			SpeakPhase++;
		}
		break;
	case 11:
		SpeakTimer += dt;
		if (SpeakTimer > SPEECH_LENGTH_FAST) {
			SpeakTimer = 0;
			SpeakPhase++;
		}
		break;

	case 12:
		SpeakTimer += dt;
		if (SpeakTimer > SPEECH_LENGTH_SHORT) {
			SpeakTimer = 0;
			SpeakPhase++;
		}
	case 13:
		SpeakTimer += dt;
		rotate_Man = 90;
		if (SpeakTimer > SPEECH_LENGTH_SHORT) {
			SpeakTimer = 0;
			is_talking = false;
			SpeakPhase = 0;
			ObjectivePhase = 2;
		}
		break;
	}
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
		else if (flashlight_lifetime > 0)
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
			ghost->waitTime = 5;
		}
		else if (ghost->distance <= 7)
		{
			camera.lockedTarget.Set(ghost->pos.x, ghost->pos.y + 15, ghost->pos.z);
			camera.newTarget = camera.target;
			ghost->state = Ghost::SPIN;
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


	if (PKeypressed)
	{
		PKeypressed = false;
		gamepaused = true;
		Application::hidemousecursor(false);
		Application::pause(true);
	}

	campos_x = camera.position.x;
	campos_y = camera.position.y;
	campos_z = camera.position.z;
	//switch scenes button for now
	if (Application::IsKeyPressed('5')) {
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_Menu);
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
}

void SceneSP2Main::PauseUpdate()
{
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

void SceneSP2Main::Render()
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
	{
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

		if (light[2].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(light[2].position.x, light[2].position.y, light[2].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightDirection_cameraspace.x);
		}
		else if (light[2].type == Light::LIGHT_SPOT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * light[2].position;
			glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * light[2].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT2_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
		}
		else if (light[2].type == Light::LIGHT_POINT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * light[2].position;
			glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);

		}

		if (light[3].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(light[3].position.x, light[3].position.y, light[3].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightDirection_cameraspace.x);
		}
		else if (light[3].type == Light::LIGHT_SPOT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * light[3].position;
			glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * light[3].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT3_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
		}
		else if (light[3].type == Light::LIGHT_POINT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * light[3].position;
			glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
		}

		if (light[4].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(light[4].position.x, light[4].position.y, light[4].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightDirection_cameraspace.x);
		}
		else if (light[4].type == Light::LIGHT_SPOT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * light[4].position;
			glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * light[4].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT4_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
		}
		else if (light[4].type == Light::LIGHT_POINT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * light[4].position;
			glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightPosition_cameraspace.x);
		}

		if (light[5].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(light[5].position.x, light[5].position.y, light[5].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[U_LIGHT5_POSITION], 1, &lightDirection_cameraspace.x);
		}
		else if (light[5].type == Light::LIGHT_SPOT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * light[5].position;
			glUniform3fv(m_parameters[U_LIGHT5_POSITION], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * light[5].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT5_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
		}
		else if (light[5].type == Light::LIGHT_POINT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * light[5].position;
			glUniform3fv(m_parameters[U_LIGHT5_POSITION], 1, &lightPosition_cameraspace.x);
		}
	}

	//skybox
	RenderSkybox();

	/*modelStack.PushMatrix();
	modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[LightSphere], false);
	modelStack.PopMatrix();*/

	modelStack.PushMatrix();
	modelStack.Translate(light[2].position.x, light[2].position.y, light[2].position.z);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[LightSphere], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[3].position.x, light[3].position.y, light[3].position.z);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[LightSphere], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[4].position.x, light[4].position.y, light[4].position.z);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[LightSphere], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[5].position.x, light[5].position.y, light[5].position.z);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[LightSphere], false);
	modelStack.PopMatrix();

	//ground Mesh
	modelStack.PushMatrix();
	modelStack.Translate(0, -4, 0);
	modelStack.Scale(2000, 1, 2000);
	RenderMesh(meshList[Ground_Mesh], true);
	modelStack.PopMatrix();

	//trap rendering
	for (int i = 0; i < signed(traplist.size()); i++) {
		switch (traplist[i].TRAPTYPE) {
		case trap::beartrap:
			modelStack.PushMatrix();
			modelStack.Translate(traplist[i].TrapPosition.x, traplist[i].TrapPosition.y, traplist[i].TrapPosition.z);
			RenderMesh(meshList[GEO_BEARTRAP], true);
			modelStack.PopMatrix();
			break;
		}
	}

	//colliderbox to check collider 
	//@collider
	/*modelStack.PushMatrix();
	modelStack.Translate(Colliderlist[45].getPosition().x, Colliderlist[45].getPosition().y, Colliderlist[45].getPosition().z);
	RenderMesh(meshList[Colliderbox], false);
	modelStack.PopMatrix();*/

	RenderBuilding();

	modelStack.PushMatrix();
	modelStack.Translate(0, 9, 270);
	modelStack.Scale(10, 10, 1);
	RenderMesh(meshList[GEO_SIGN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -15.5, -351);
	modelStack.Scale(25, 10, 15);
	RenderMesh(meshList[GEO_ROAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -15.5, 360);
	modelStack.Scale(25, 10, 15);
	RenderMesh(meshList[GEO_ROAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(390, -44, 14);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(24.7, 35, 15);
	RenderMesh(meshList[GEO_ROAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-390, -44, 14);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(24.7, 35, 15);
	RenderMesh(meshList[GEO_ROAD], true);
	modelStack.PopMatrix();



	modelStack.PushMatrix();
	modelStack.Translate(50, -4, -35);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_LAMP], true);
	modelStack.PopMatrix();//Added collider


	modelStack.PushMatrix();
	modelStack.Translate(-50, -4, -35);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_LAMP], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-45, -4, -130);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_LAMP], true);
	modelStack.PopMatrix();//Added collider


	modelStack.PushMatrix();
	modelStack.Translate(45, -4, -130);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_LAMP], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-45, -4, 130);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_LAMP], true);
	modelStack.PopMatrix();//Added collider


	modelStack.PushMatrix();
	modelStack.Translate(45, -4, 130);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_LAMP], true);
	modelStack.PopMatrix();//Added collider



	modelStack.PushMatrix();
	modelStack.Translate(0, -3, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.18f, 0.18f, 0.18f);
	RenderMesh(meshList[GEO_FOUNTAIN], true);
	modelStack.PopMatrix();//Added collider

	//modelStack.PushMatrix();
	//modelStack.Translate(0, -3, 0);
	//modelStack.Rotate(-90, 1, 0, 0);
	//modelStack.Scale(0.04, 0.04, 0.04);
	//RenderMesh(meshList[GEO_SCHOOL], true);
	//modelStack.PopMatrix();//Added collider

	

	modelStack.PushMatrix();
	modelStack.Translate(0, -3, -460);
	modelStack.Rotate(270, 1, 0, 0);
	modelStack.Scale(0.13f, 0.13f, 0.13f);
	RenderMesh(meshList[HOUSE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-520, -2, 0);
	modelStack.Scale(0.09f, 0.09f, 0.09f);
	RenderMesh(meshList[HOSPITAL], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(520, -1, 0);
	modelStack.Scale(0.12f, 0.12f, 0.12f);
	RenderMesh(meshList[HAUNTEDSCHOOL], true);
	modelStack.PopMatrix();//Added collider

	//@buildings
	modelStack.PushMatrix();
	modelStack.Translate(0, -4, 510);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(0.16, 0.16, 0.16);
	RenderMesh(meshList[GARAGE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 8, 465);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(0.15, 0.22, 0.27);
	RenderMesh(meshList[GARAGEDOOR], true);
	modelStack.PopMatrix();//Added collider

	RenderFence();

	RenderTrees();

	RenderBenches();

	if (manAppear == true) {
		modelStack.PushMatrix();
		modelStack.Translate(0, -3, 20);
		modelStack.Rotate(rotate_Man, 0, 1, 0);
		modelStack.Scale(4.2f, 4.2f, 4.2f);
		RenderMesh(meshList[GEO_MYSTERIOUSMAN], true);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(0, -1, 0);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(15, 1, 15);
	RenderMesh(meshList[GEO_WATER], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(0, -4, 0);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(50, 1, 50);
	RenderMesh(meshList[GEO_SPAWN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-180, 6, 0);
	modelStack.Scale(315, 20, 42);
	RenderMesh(meshList[GEO_PATH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(180, 6, 0);
	modelStack.Scale(315, 20, 50);
	RenderMesh(meshList[GEO_PATH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 6, 120);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(357, 20, 50);
	RenderMesh(meshList[GEO_PATH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 6, -120);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(357, 20, 50);
	RenderMesh(meshList[GEO_PATH], true);
	modelStack.PopMatrix();

	RenderTables();



	//lockers
	for (int i = 0; i < signed(Lockerlist.size()); i++) {
		modelStack.PushMatrix();
		modelStack.Translate(Lockerlist[i].getpos().x, Lockerlist[i].getpos().y, Lockerlist[i].getpos().z);
		modelStack.Scale(0.2f, 0.2f, 0.2f);
		RenderMesh(meshList[locker], true);
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

	//vehicle
	modelStack.PushMatrix();
	modelStack.Translate(30, 6, 355);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TRUCK], true);
	modelStack.PopMatrix();//Added collider

	if (items[0] != nullptr) {
		modelStack.PushMatrix();
		modelStack.Translate(0, -3, 340);
		modelStack.Scale(0.09, 0.09, 0.09);
		RenderMesh(meshList[BATTERY], true);
		modelStack.PopMatrix();
	}

	if (items[1] != nullptr) {
		modelStack.PushMatrix();
		modelStack.Translate(60, -3, 0);
		modelStack.Scale(0.09, 0.09, 0.09);
		RenderMesh(meshList[BATTERY], true);
		modelStack.PopMatrix();
	}

	if (items[2] != nullptr) {
		modelStack.PushMatrix();
		modelStack.Translate(-60, -3, 100);
		modelStack.Scale(0.09, 0.09, 0.09);
		RenderMesh(meshList[BATTERY], true);
		modelStack.PopMatrix();
	}

	if (items[3] != nullptr) {
		modelStack.PushMatrix();
		modelStack.Translate(-185, -3, -200);
		modelStack.Scale(0.09, 0.09, 0.09);
		RenderMesh(meshList[BATTERY], true);
		modelStack.PopMatrix();
	}

	if (items[4] != nullptr) {
		modelStack.PushMatrix();
		modelStack.Translate(255, -3, -190);
		modelStack.Scale(0.09, 0.09, 0.09);
		RenderMesh(meshList[BATTERY], true);
		modelStack.PopMatrix();
	}
	//modelStack.PushMatrix();
	//modelStack.Translate(30.f, -0.1f, 313.f);
	//modelStack.Scale(750, 8, 30);
	//RenderMesh(meshList[GEO_PAVEMENT], true);
	//modelStack.PopMatrix();

	//ground mesh 2

	modelStack.PushMatrix();
	modelStack.Translate(30.f, -2.8f, 530.f);
	modelStack.Scale(950, 1, 300);
	RenderMesh(meshList[Ground_Mesh2], true);
	modelStack.PopMatrix();




	modelStack.PushMatrix();
	modelStack.Translate(30.f, -0.1f, -312.f);
	modelStack.Scale(750, 8, 30);
	RenderMesh(meshList[GEO_PAVEMENT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(30.f, -2.8f, -540.f);
	modelStack.Scale(950, 1, 300);
	RenderMesh(meshList[Ground_Mesh2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-352, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(730, 8, 30);
	RenderMesh(meshList[GEO_PAVEMENT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-581, -2.8, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1360, 1, 300);
	RenderMesh(meshList[Ground_Mesh2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(352, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(730, 8, 30);
	RenderMesh(meshList[GEO_PAVEMENT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(562, -2.8, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1360, 1, 300);
	RenderMesh(meshList[Ground_Mesh2], true);
	modelStack.PopMatrix();



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

	


	if (nearBattery == true || nearBattery1 == true || nearBattery2 == true || nearBattery3 == true || nearBattery4 == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press F to pick up", Color(0.f, 1.f, 1.f), 4.f, 20.f, 5.f);
	}
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
					RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(inventory->items[i]->count), Color(1.f,1.f,1.f), 2.f, float(33.8 + i * 5), 3.f);
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

	

	if (showChatbox == true) {
		RenderMeshOnScreen(meshList[GEO_CHATBOX], 40.f, 10.f, 2.f, 0.7f);
	}
	//speeches
	switch (SpeakPhase)
	{
	case 0:
		RenderTextOnScreen(meshList[GEO_TEXT], "", Color(0, 0, 0), 4, 10, 1.8f);
		break;
		//starting phase
	case 1:
		RenderTextOnScreen(meshList[GEO_TEXT], "Look's like this is the place...", Color(0, 0, 1), 4, 10, 1.8f);
		break;
	case 2:
		RenderTextOnScreen(meshList[GEO_TEXT], "I guess I better start looking around", Color(0.f, 0.f, 1.f), 4.f, 10.f, 1.8f);
		break;

		//talking to man
	case 3:
		RenderTextOnScreen(meshList[GEO_TEXT], "Um...Excuse me sir?", Color(0.f, 0.f, 1.f), 4.f, 10.f, 1.8f);
		break;
	case 4:
		RenderTextOnScreen(meshList[GEO_TEXT], "Ah, Hello! I didn't notice you were behind me.", Color(0.f, 0.f, 0.f), 4.f, 10.f, 1.8f);
		break;
	case 5:
		RenderTextOnScreen(meshList[GEO_TEXT], "I didn't know people still come to this place...", Color(0.f, 0.f, 0.f), 4.f, 10.f, 1.8f);
		break;
	case 6:
		RenderTextOnScreen(meshList[GEO_TEXT], "I heard rumors about this place. Are they true sir?", Color(0.f, 0.f, 1.f), 4.f, 10.f, 1.8f);
		break;
	case 7:
		RenderTextOnScreen(meshList[GEO_TEXT], "You shouldn't be here.", Color(0.f, 0.f, 0.f), 4.f, 10.f, 1.8f);
		break;
	case 8:
		RenderTextOnScreen(meshList[GEO_TEXT], "My car broke down..", Color(0.f, 0.f, 1.f), 4.f, 10.f, 1.8f);
		break;
	case 9:
		RenderTextOnScreen(meshList[GEO_TEXT], "Is there any way i can fix it?", Color(0.f, 0.f, 1.f), 4.f, 10.f, 1.8f);
		break;
	case 10:
		RenderTextOnScreen(meshList[GEO_TEXT], "There are stuff lying around in the buildings.. ", Color(0.f, 0.f, 0.f), 4.f, 10.f, 1.8f);
		break;
	case 11:
		RenderTextOnScreen(meshList[GEO_TEXT], "But be  CAREFUL...", Color(0.f, 0.f, 0.f), 4.f, 10.f, 1.8f);
		break;
	case 12:
		RenderTextOnScreen(meshList[GEO_TEXT], "What? Why?", Color(0.f, 0.f, 1.f), 4.f, 10.f, 1.8f);
		break;
	case 13:
		RenderTextOnScreen(meshList[GEO_TEXT], "Something awaits you..", Color(0.f, 0.f, 0.f), 4.f, 10.f, 1.8f);
		break;
	}



	//interaction sentences
	switch (Interact_Num)
	{
	case 0:
		RenderTextOnScreen(meshList[GEO_TEXT], "", Color(1, 1, 0), 2, 1, 9);
		break;
	case 1:
		RenderTextOnScreen(meshList[GEO_TEXT], "Talk to man", Color(1, 1, 0), 4, 22, 5);
		break;
	}

	//camera position
	campos_x = camera.position.x;
	campos_y = camera.position.y;
	campos_z = camera.position.z;

	//objectives screen
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


	if (NearGarage == true || NearHouse == true || NearSchool == true || NearHospital == true) {
		showChatbox = true;
		RenderTextOnScreen(meshList[GEO_TEXT], "Press F to go inside?", Color(0.f, 0.f, 1.f), 4.f, 10.f, 1.8f);
	}
	
	//pause menu
	if (gamepaused)
		RenderMeshOnScreen(meshList[GEO_PAUSEMENU], 40, 30, 35, 54);

	/*std::ostringstream test1;
	test1 << "ghost state: " << ghost->state;
	RenderTextOnScreen(meshList[GEO_TEXT], test1.str(), Color(0, 1, 0), 4, 0, 6);*/
	/*std::ostringstream test3;
	test3 << "ghost facing: " << ghost->facing;
	RenderTextOnScreen(meshList[GEO_TEXT], test3.str(), Color(0, 1, 0), 4, 0, 3);
	std::ostringstream test2;
	test2 << "ghost state: " << ghost->state;
	RenderTextOnScreen(meshList[GEO_TEXT], test2.str(), Color(0, 1, 0), 4, 0, 9);*/
}

void SceneSP2Main::Exit()
{
	// Cleanup VBO here
	if (ghost != nullptr)
	{
		delete ghost;
		ghost = nullptr;
	}
	if (inventory != nullptr)
	{
		delete inventory;
		inventory = nullptr;
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneSP2Main::UseItem(int itemname)
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

bool SceneSP2Main::PickUpItem(Item* item)
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

void SceneSP2Main::RenderSkybox()
{
	//scale, translate, rotate
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 0 + camera.position.y, 3.0f + camera.position.z);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(3000, 3000, 3000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 0 + camera.position.y, -3.0f + camera.position.z);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(3000, 3000, 3000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(3.0f + camera.position.x, 0 + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(3000, 3000, 3000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-3.0f + camera.position.x, 0 + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(3000, 3000, 3000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, -3.0f + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(3000, 3000, 3000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 3.0f + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3000, 3000, 3000);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}




void SceneSP2Main::RenderMesh(Mesh* mesh, bool enableLight)
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

void SceneSP2Main::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneSP2Main::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SceneSP2Main::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, int limit)
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

void SceneSP2Main::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey)
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

void SceneSP2Main::RenderBuilding()
{
	//front
	modelStack.PushMatrix();
	modelStack.Translate(-690, 85, -750);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 90);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(-520, 85, -750);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 90);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-340, 85, -750);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 90);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-160, 85, -750);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-10, 85, -750);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(160, 85, -750);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(330, 85, -750);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(490, 85, -750);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(660, 85, -750);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();



	//
	modelStack.PushMatrix();
	modelStack.Translate(-750, 85, -690);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-750, 85, -510);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(-750, 85, -340);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-750, 85, -170);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-750, 85, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-750, 85, 170);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-750, 85, 330);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-750, 85, 500);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-750, 85, 670);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();




	//right


	modelStack.PushMatrix();
	modelStack.Translate(750, 85, -720);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(750, 85, -560);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(750, 85, -390);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(750, 85, -220);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(750, 85, -50);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(750, 85, 120);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(750, 85, 270);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(750, 85, 450);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(750, 85, 630);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();




	//back
	modelStack.PushMatrix();
	modelStack.Translate(-720, 85, 750);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-560, 85, 750);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(-400, 85, 750);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-230, 85, 750);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-60, 85, 750);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(110, 85, 750);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(290, 85, 750);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(450, 85, 750);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(620, 85, 750);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(820, 85, 750);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();
}

void SceneSP2Main::RenderBenches()
{
	modelStack.PushMatrix();
	modelStack.Translate(-40, 1, -80);
	modelStack.Scale(1.1f, 1.1f, 1.1f);
	RenderMesh(meshList[GEO_BENCH], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-40, 1, -170);
	modelStack.Scale(1.1f, 1.1f, 1.1f);
	RenderMesh(meshList[GEO_BENCH], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(40, 1, -80);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1.1f, 1.1f, 1.1f);
	RenderMesh(meshList[GEO_BENCH], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(40, 1, -170);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1.1f, 1.1f, 1.1f);
	RenderMesh(meshList[GEO_BENCH], true);
	modelStack.PopMatrix();//Added collider

	//

	modelStack.PushMatrix();
	modelStack.Translate(-40, 1, 80);
	modelStack.Scale(1.1f, 1.1f, 1.1f);
	RenderMesh(meshList[GEO_BENCH], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-40, 1, 170);
	modelStack.Scale(1.1f, 1.1f, 1.1f);
	RenderMesh(meshList[GEO_BENCH], true);
	modelStack.PopMatrix();//added collider

	modelStack.PushMatrix();
	modelStack.Translate(40, 1, 80);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1.1f, 1.1f, 1.1f);
	RenderMesh(meshList[GEO_BENCH], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(40, 1, 170);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1.1f, 1.1f, 1.1f);
	RenderMesh(meshList[GEO_BENCH], true);
	modelStack.PopMatrix();//Added collider

	//
	modelStack.PushMatrix();
	modelStack.Translate(110, 2, 30);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1.2f, 1.2f, 1.2f);
	RenderMesh(meshList[GEO_BENCH], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(170, 2, 30);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1.2f, 1.2f, 1.2f);
	RenderMesh(meshList[GEO_BENCH], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(110, 2, -30);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1.2f, 1.2f, 1.2f);
	RenderMesh(meshList[GEO_BENCH], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(170, 2, -30);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1.2f, 1.2f, 1.2f);
	RenderMesh(meshList[GEO_BENCH], true);
	modelStack.PopMatrix();//Added collider

	//

	modelStack.PushMatrix();
	modelStack.Translate(-110, 2, 30);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1.2f, 1.2f, 1.2f);
	RenderMesh(meshList[GEO_BENCH], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-170, 2, 30);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1.2f, 1.2f, 1.2f);
	RenderMesh(meshList[GEO_BENCH], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-110, 2, -30);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1.2f, 1.2f, 1.2f);
	RenderMesh(meshList[GEO_BENCH], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-170, 2, -30);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1.2f, 1.2f, 1.2f);
	RenderMesh(meshList[GEO_BENCH], true);
	modelStack.PopMatrix();//Added collider
}

void SceneSP2Main::RenderFence()
{
	
	//front left

	/*modelStack.PushMatrix();
	modelStack.Translate(-20, -4, 275);
	modelStack.Rotate(70, 0, 1, 0);
	modelStack.Scale(7, 7, 7);
	RenderMesh(meshList[GEO_ARCH], true);
	modelStack.PopMatrix();*/
	modelStack.PushMatrix();
	modelStack.Translate(-25, -4, 275);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(7, 7, 7);
	RenderMesh(meshList[GEO_GATE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(25, -4, 275);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(7, 7, 7);
	RenderMesh(meshList[GEO_GATE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-50, -7, 295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-102, -7, 295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-153, -7, 295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-205, -7, 295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-257, -7, 295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-308, -7, 295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider
	
	// front right
	modelStack.PushMatrix();
	modelStack.Translate(50, -7, 295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(102, -7, 295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(153, -7, 295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(205, -7, 295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(257, -7, 295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(308, -7, 295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	
	//left left
	modelStack.PushMatrix();
	modelStack.Translate(-335, -7, 271);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-335, -7, 225);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-335, -7, 178);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-335, -7, 127);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-335, -7, 75);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-335, -7, 35);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2.6f, 4.5f, 4.5f);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider
	
	//left right
	modelStack.PushMatrix();
	modelStack.Translate(-335, -7, -271);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-335, -7, -225);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-335, -7, -178);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-335, -7, -127);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-335, -7, -75);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-335, -7, -35);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2.6f, 4.5f, 4.5f);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	
	//right left
	modelStack.PushMatrix();
	modelStack.Translate(335, -7, 271);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(335, -7, 225);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(335, -7, 178);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(335, -7, 127);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(335, -7, 75);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(335, -7, 35);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2.6f, 4.5f, 4.5f);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider
	//right right
	modelStack.PushMatrix();
	modelStack.Translate(335, -7, -271);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(335, -7, -225);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(335, -7, -178);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(335, -7, -127);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(335, -7, -75);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(335, -7, -35);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2.6f, 4.5f, 4.5f);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	
	//back 
	modelStack.PushMatrix();
	modelStack.Translate(-50, -7, -295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-102, -7, -295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-153, -7, -295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-205, -7, -295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-257, -7, -295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-308, -7, -295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	//back right
	modelStack.PushMatrix();
	modelStack.Translate(50, -7, -295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(102, -7, -295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(153, -7, -295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(205, -7, -295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(257, -7, -295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(308, -7, -295);
	modelStack.Scale(4.5, 4.5, 4.5);
	RenderMesh(meshList[GEO_FENCE], true);
	modelStack.PopMatrix();//Added collider
}

void SceneSP2Main::RenderTables()
{

	modelStack.PushMatrix();
	modelStack.Translate(130, 8, 210);
	//modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(0.2f, 0.3f, 0.2f);
	RenderMesh(meshList[GEO_TABLE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(220, 8, 210);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2f, 0.3f, 0.2f);
	RenderMesh(meshList[GEO_TABLE], true);
	modelStack.PopMatrix();//Added collider


	modelStack.PushMatrix();
	modelStack.Translate(130, 8, 130);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2f, 0.3f, 0.2f);
	RenderMesh(meshList[GEO_TABLE], true);
	modelStack.PopMatrix();//Added collider
	
	modelStack.PushMatrix();
	modelStack.Translate(220, 8, 130);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2f, 0.3f, 0.2f);
	RenderMesh(meshList[GEO_TABLE], true);
	modelStack.PopMatrix();//Added collider
	
	//
	modelStack.PushMatrix();
	modelStack.Translate(-130, 8, 210);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2f, 0.3f, 0.2f);
	RenderMesh(meshList[GEO_TABLE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-220, 8, 210);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2f, 0.3f, 0.2f);
	RenderMesh(meshList[GEO_TABLE], true);
	modelStack.PopMatrix();//Added collider


	modelStack.PushMatrix();
	modelStack.Translate(-130, 8, 130);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2f, 0.3f, 0.2f);
	RenderMesh(meshList[GEO_TABLE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-220, 8, 130);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2f, 0.3f, 0.2f);
	RenderMesh(meshList[GEO_TABLE], true);
	modelStack.PopMatrix();//Added collider
	//front
	modelStack.PushMatrix();
	modelStack.Translate(130, 8, -210);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2f, 0.3f, 0.2f);
	RenderMesh(meshList[GEO_TABLE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(220, 8, -210);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2f, 0.3f, 0.2f);
	RenderMesh(meshList[GEO_TABLE], true);
	modelStack.PopMatrix();//Added collider


	modelStack.PushMatrix();
	modelStack.Translate(130, 8, -130);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2f, 0.3f, 0.2f);
	RenderMesh(meshList[GEO_TABLE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(220, 8, -130);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2f, 0.3f, 0.2f);
	RenderMesh(meshList[GEO_TABLE], true);
	modelStack.PopMatrix();//Added collider

	//
	modelStack.PushMatrix();
	modelStack.Translate(-130, 8, -210);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2f, 0.3f, 0.2f);
	RenderMesh(meshList[GEO_TABLE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-220, 8, -210);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2f, 0.3f, 0.2f);
	RenderMesh(meshList[GEO_TABLE], true);
	modelStack.PopMatrix();//Added collider


	modelStack.PushMatrix();
	modelStack.Translate(-130, 8, -130);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2f, 0.3f, 0.2f);
	RenderMesh(meshList[GEO_TABLE], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-220, 8, -130);
	//modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2f, 0.3f, 0.2f);
	RenderMesh(meshList[GEO_TABLE], true);
	modelStack.PopMatrix();//Added collider
}

void SceneSP2Main::RenderTrees()
{

	modelStack.PushMatrix();
	modelStack.Translate(60, 5, 280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(120, 5, 280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(180, 5, 280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(250, 5, 280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(320, 5, 280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	//left trees
	
	modelStack.PushMatrix();
	modelStack.Translate(-60, 5, 280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-120, 5, 280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-180, 5, 280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-250, 5, 280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-320, 5, 280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(60, 5, -280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(120, 5, -280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(180, 5, -280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(250, 5, -280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(320, 5, -280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	//left trees
	
	modelStack.PushMatrix();
	modelStack.Translate(-60, 5, -280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-120, 5, -280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-180, 5, -280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-250, 5, -280);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	//

	modelStack.PushMatrix();
	modelStack.Translate(310, 5, -230);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(310, 5, -170);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(310, 5, -110);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(310, 5, -50);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(310, 5, 230);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(310, 5, 170);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(310, 5, 110);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added colliders

	modelStack.PushMatrix();
	modelStack.Translate(310, 5, 50);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	//left
	modelStack.PushMatrix();
	modelStack.Translate(-310, 5, -230);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-310, 5, -170);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-310, 5, -110);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-310, 5, -50);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-310, 5, 230);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-310, 5, 170);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-310, 5, 110);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

	modelStack.PushMatrix();
	modelStack.Translate(-310, 5, 50);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();//Added collider

}

