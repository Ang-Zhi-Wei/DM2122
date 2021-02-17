#include "SceneSP2Main.h"
#include "GL\glew.h"
#include <stdlib.h>
#include <time.h>
#include "shader.hpp"
#include "LoadTGA.h"
#include <sstream>

SceneSP2Main::SceneSP2Main()
{
}

SceneSP2Main::~SceneSP2Main()
{
}


void SceneSP2Main::Init()
{
	camBlinkOn = true;
	camBlinkOff = false;
	SpeakPhase = 0;
	SpeakTimer = 0;
	ObjectivePhase = 0;

	// Init VBO here
	glClearColor(0.5, 0.5, 0.5, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//camera
	camera.Init(Vector3(0, 5, 270), Vector3(0, 5, 250), Vector3(0, 1,
		0));
	//shaders
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	//...
	//hide cursor
	Application::hidemousecursor();
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
	meshList[GEO_LIGHTBULB] = MeshBuilder::Generatesphere("LightBall", 1, 1, 1, Yellow);
	meshList[GEO_LIGHTBULB]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_LIGHTBULB]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_LIGHTBULB]->material.kShininess = 1.f;
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
	//building
	meshList[GEO_BUILDING] = MeshBuilder::GenerateOBJ("Building", "OBJ//simplebuilding.obj");
	meshList[GEO_BUILDING]->textureID = LoadTGA("Assigment2Images//buildingtexture.tga");
	meshList[GEO_BUILDING]->material.kAmbient.Set(0.35, 0.35, 0.35);
	meshList[GEO_ROAD] = MeshBuilder::GenerateOBJ("Building", "OBJ//road.obj");
	meshList[GEO_ROAD]->textureID = LoadTGA("Assigment2Images//road.tga");
	meshList[GEO_ROAD]->material.kAmbient.Set(0.35, 0.35, 0.35);
	meshList[GEO_TREES] = MeshBuilder::GenerateOBJ("Building", "OBJ//pine2.obj");
	meshList[GEO_TREES]->textureID = LoadTGA("Assigment2Images//pine2.tga");
	meshList[GEO_TREES]->material.kAmbient.Set(0.35, 0.35, 0.35);
	meshList[GEO_FOUNTAIN] = MeshBuilder::GenerateOBJ("Building", "OBJ//fountain.obj");
	meshList[GEO_FOUNTAIN]->textureID = LoadTGA("Assigment2Images//fountaintexture.tga");
	meshList[GEO_FOUNTAIN]->material.kAmbient.Set(0.35, 0.35, 0.35);
	meshList[GEO_WATER] = MeshBuilder::Generatesphere("Building",30,30,30,5);
	meshList[GEO_WATER]->textureID = LoadTGA("Assigment2Images//water.tga");
	meshList[GEO_WATER]->material.kAmbient.Set(0.35, 0.35, 0.35);
	meshList[GEO_SPAWN] = MeshBuilder::Generatesphere("spawn", 30, 30, 30,5);
	meshList[GEO_SPAWN]->textureID = LoadTGA("Assigment2Images//cement.tga");
	meshList[GEO_SPAWN]->material.kAmbient.Set(0.35, 0.35, 0.35);
	meshList[GEO_PATH] = MeshBuilder::GenerateQuad("spawn", 1,1, White);
	meshList[GEO_PATH]->textureID = LoadTGA("Assigment2Images//pavement.tga");
	meshList[GEO_PATH]->material.kAmbient.Set(0.35, 0.35, 0.35);
	meshList[GEO_LAMP] = MeshBuilder::GenerateOBJ("Building", "OBJ//lamppost.obj");
	meshList[GEO_LAMP]->textureID = LoadTGA("Assigment2Images//metal.tga");
	meshList[GEO_LAMP]->material.kAmbient.Set(0.35, 0.35, 0.35);
	//meshList[GEO_BUILDING]->material.kAmbient.Set(0.35, 0.35, 0.35);

	//paths and deco
	meshList[Ground_Mesh] = MeshBuilder::GenerateQuadRepeat("Hell", 1, 1, White);
	//meshList[Ground_Mesh]->textureID = LoadTGA("Assigment2Images//GroundMesh.tga");
	meshList[Ground_Mesh]->textureID = LoadTGA("Image//PathTexture.tga");
	meshList[Ground_Mesh]->material.kAmbient.Set(0,0.20,0.13);
	

	//truck
	meshList[GEO_TRUCK] = MeshBuilder::GenerateOBJ("truck", "OBJ//truck.obj");
	meshList[GEO_TRUCK]->textureID = LoadTGA("Image//Silver.tga");
	meshList[GEO_TRUCK]->material.kAmbient.Set(0.35, 0.35, 0.35);

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
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1,&light[0].color.r);
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
	light[1].power = 2;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(7));
	light[1].cosInner = cos(Math::DegreeToRadian(1));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, -1.f, 0.f);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1,&light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);
	
	light[2].type = Light::LIGHT_SPOT;
	light[2].position.Set(40, 30, -34);
	light[2].color.Set(Yellow);
	light[2].power = 2;
	light[2].kC = 1.f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(35));
	light[2].cosInner = cos(Math::DegreeToRadian(20));
	light[2].exponent = 3.f;
	light[2].spotDirection.Set(0.f, 1.f, 0.f);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1,&light[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[2].kQ);
	glUniform1i(m_parameters[U_LIGHT2_TYPE], light[2].type);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], light[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], light[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[2].exponent);

	light[3].type = Light::LIGHT_SPOT;
	light[3].position.Set(-40, 30, -34);
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
	

	//Set Material locations
	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT],
		m_parameters[U_MATERIAL_DIFFUSE],
		m_parameters[U_MATERIAL_SPECULAR],
		m_parameters[U_MATERIAL_SHININESS]);
	//number of lights
	glUniform1i(m_parameters[U_NUMLIGHTS], 4);

	//ruins
	meshList[Ruins] = MeshBuilder::GenerateOBJ("Ruins", "OBJ//Ruin.obj");
	meshList[Ruins]->textureID = LoadTGA("Assigment2Images//RuinTexture.tga");
	meshList[Ruins]->material.kAmbient.Set(0.35, 0.35, 0.35);
	//UI

	meshList[GEO_OVERLAY] = MeshBuilder::GenerateQuad2("vision", 80, 60, 0);
	meshList[GEO_OVERLAY2] = MeshBuilder::GenerateQuad2("camcorder", 80, 60, 0);
	meshList[GEO_BAR] = MeshBuilder::GenerateQuad2("UI usage", 1, 1, Yellow);
	meshList[GEO_STAMINA] = MeshBuilder::GenerateQuad2("UI usage", 1, 1, White);
	meshList[GEO_STAMINA]->textureID = LoadTGA("Assigment2Images//sprint.tga");
	meshList[GEO_OVERLAY2]->textureID = LoadTGA("Image//camcorder.tga");
	meshList[GEO_OVERLAY]->textureID = LoadTGA("Image//VISIONON.tga");
	




	//init update stuff
	LSPEED = 10.F;
	flashlight = true;
	Qpressed = Qreleased = false;
	Epressed = Ereleased = false;
	Fpressed = Freleased = false;
	//collidertest
	Colliderlist.push_back(ColliderBox());
	Colliderlist[0].setlength(42, 20, 97);
	Colliderlist[0].Setposition(Vector3(0, 5, -227));
	//colliderbox for checking any collider(just one)
	meshList[Colliderbox] = MeshBuilder::GenerateColliderBox("Box", Colliderlist[0].getxlength(), Colliderlist[0].getylength(), Colliderlist[0].getzlength());
	//list of colliders
	camera.setchecker(Colliderlist);
	//Locker test
	meshList[locker] = MeshBuilder::GenerateOBJ("Locker", "OBJ//locker.obj");
	meshList[locker]->material.kAmbient.Set(0.35, 0.35, 0.35);
	meshList[locker]->textureID = LoadTGA("Assigment2Images//locker.tga");
	//list of lockers
	Lockerlist.push_back(Locker());
	Lockerlist[0].setpos(Vector3(0, -4.5, 0));
	//Set boundary here
	camera.SetBounds(-415, 415, -365, 360);
	//loadtga should only call when necessary
	switchtga1 = false;
	switchtga2 = false;
}

void SceneSP2Main::Update(double dt)
{
	//camera dot blink logic (not the best, but works)
	if (camBlinkOff && camBlinkOffSec >= 0.5)
	{
		camBlinkOn = true;
		camBlinkOff = false;
		camBlinkOffSec = 0;
		switchtga1 = true;
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
		switchtga1 = true;
	}

	//speech phase case statements
	int SPEECH_LENGTH_SHORT = 3;
	int SPEECH_LENGTH_MEDIUM = 5;
	int SPEECH_LENGTH_LONG = 8;
	switch (SpeakPhase)
	{
		case 0:
			SpeakTimer += dt;
			if (SpeakTimer > SPEECH_LENGTH_SHORT) {
				SpeakPhase++;
				SpeakTimer = 0;
			}
			break;
		case 1:
			SpeakTimer += dt;
			if (SpeakTimer > SPEECH_LENGTH_SHORT) {
				SpeakPhase++;
				SpeakTimer = 0;
			}
			break;
		case 2:
			ObjectivePhase = 1;
			SpeakTimer = 0;
			break;
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
	if (Application::IsKeyPressed('Q'))
	{
		Qpressed = true;
		Qreleased = false;
	}
	else
	{
		if (Qpressed)
		{
			Qreleased = true;
			
		}
		Qpressed = false;
	}
	if (Application::IsKeyPressed('F'))
	{
		Fpressed = true;
		Freleased = false;
	}
	else
	{
		if (Fpressed)
		{
			Freleased = true;
		}
		Fpressed = false;
	}
	//Locker

	for (int i = 0; i < Lockerlist.size(); i++) {
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

	//fps
	fps = 1.f / dt;
	//camera
	camera.Update(dt);
	//light
	light[0].position.Set(camera.position.x, camera.position.y, camera.position.z);
	light[1].position.Set(camera.position.x, camera.position.y, camera.position.z);
	light[1].spotDirection = -1 * camera.view;
	
	//toggle flashlight on/off
	if (Qreleased)
	{
		flashlight = !flashlight;
		Qreleased = false;
		//updates if flashlight status changes
		if (flashlight)
		{
			light[1].power = 2;
			switchtga2 = true;
		}
		else
		{
			light[1].power = 0;
			switchtga2 = true;
		}
		glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	}

	//ghost
	
	switch (ghost.state)
	{
	case Ghost::NORMAL:
		ghost.facing = (camera.position - ghost.pos).Normalized();
		ghost.distance = (camera.position - ghost.pos).Length();
		ghost.UpdateMovement(dt);
		if (ghost.distance <= 20)
		{
			ghost.state = Ghost::CHASING;
			ghost.speed = 25;
		}
		break;
	case Ghost::CHASING:
		ghost.facing = (camera.position - ghost.pos).Normalized();
		ghost.distance = (camera.position - ghost.pos).Length();
		ghost.UpdateMovement(dt);
		if (ghost.distance <= 3 && inLocker)
		{
			ghost.state = Ghost::WAITING;
			ghost.waitTime = 5;
		}
		else if (ghost.distance <= 1)
		{
			//TBC
			//end game condition met, either that or HP - 1
		}
		break;
	case Ghost::WAITING:
		ghost.waitTime -= dt;
		if (ghost.waitTime <= 0)
		{
			ghost.state = Ghost::SPEEDRUN;
			ghost.speed = 50;
		}
		break;
	case Ghost::SPEEDRUN:
		ghost.facing = (ghost.pos - camera.position).Normalized();
		ghost.UpdateMovement(dt);
		if (ghost.distance > 300 || !inLocker)
		{
			ghost.state = Ghost::NORMAL;
			ghost.speed = 5;
		}
		break;

	}
	//vision vignette
	if (flashlight)
	{
		if (switchtga2 == true) {
			meshList[GEO_OVERLAY]->textureID = LoadTGA("Image//VISIONON.tga");
			switchtga2 = false;
		}
	}
	else
	{
		if (switchtga2 == true) {
			meshList[GEO_OVERLAY]->textureID = LoadTGA("Image//VISIONOFF.tga");
			switchtga2 = false;
		}

	}
	//camcorder
	if (camBlinkOn)
	{
		if (switchtga1) {
			meshList[GEO_OVERLAY2]->textureID = LoadTGA("Image//camcorder.tga");
			switchtga1 = false;
		}


	}
	else if (camBlinkOff)
	{
		if (switchtga1) {
			meshList[GEO_OVERLAY2]->textureID = LoadTGA("Image//camcorder2.tga");
			switchtga1 = false;
		}
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

	
	//skybox
	RenderSkybox();

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

	//ground Mesh
	modelStack.PushMatrix();
	modelStack.Translate(0, -4, 0);
	modelStack.Scale(900, 1, 900);
	RenderMesh(meshList[Ground_Mesh], true);
	modelStack.PopMatrix();
	//destroyed small building
	modelStack.PushMatrix();
	modelStack.Translate(0, -4, -230);
	modelStack.Scale(8, 8, 8);
	RenderMesh(meshList[Ruins], true);
	modelStack.PopMatrix();
	//Any one Collider,must make sure correct Colliderlist is entered;
	modelStack.PushMatrix();
	modelStack.Translate(Colliderlist[0].getPosition().x, Colliderlist[0].getPosition().y, Colliderlist[0].getPosition().z);
	RenderMesh(meshList[Colliderbox], false);
	modelStack.PopMatrix();


	//front
	modelStack.PushMatrix();
	modelStack.Translate(-520, 85, -480);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 90);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-340, 85, -480);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 90);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-160, 85, -480);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-10, 85, -480);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(160, 85, -480);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(330, 85, -480);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(490, 85, -480);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	

	//left

	modelStack.PushMatrix();
	modelStack.Translate(-550, 85, -340);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-550, 85, -170);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-550, 85, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-550, 85,170);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-550, 85, 330);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-550, 85, 500);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	


	//right

	modelStack.PushMatrix();
	modelStack.Translate(550, 85, -390);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(550, 85, -220);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(550, 85, -50);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(550, 85, 120);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(550, 85, 270);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(550, 85, 450);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();



	
	//back


	modelStack.PushMatrix();
	modelStack.Translate(-400, 85, 550);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-230, 85, 550);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-60, 85, 550);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(110, 85, 550);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(290, 85, 550);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(450, 85, 550);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();



	modelStack.PushMatrix();
	modelStack.Translate(0, -44, -340);
	modelStack.Scale(35, 35, 15);
	RenderMesh(meshList[GEO_ROAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -44, 340);
	modelStack.Scale(35, 35, 15);
	RenderMesh(meshList[GEO_ROAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(380, -44, 100);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(35, 35, 15);
	RenderMesh(meshList[GEO_ROAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-380, -44, 100);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(35, 35, 15);
	RenderMesh(meshList[GEO_ROAD], true);
	modelStack.PopMatrix();



	modelStack.PushMatrix();
	modelStack.Translate(-120, 5, -100);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(120, 5, 100);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-120, 5, 100);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(120, 5, -100);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_TREES], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, -4, -35);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_LAMP], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(-50, -4, -35);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_LAMP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-45, -4, -130);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_LAMP], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(45, -4, -130);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_LAMP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-45, -4, 130);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_LAMP], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(45, -4, 130);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_LAMP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -3, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.18, 0.18, 0.18);
	RenderMesh(meshList[GEO_FOUNTAIN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0,-1, 0);
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
	modelStack.Scale(330, 20, 50);
	RenderMesh(meshList[GEO_PATH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(180, 6, 0);
	modelStack.Scale(330, 20, 50);
	RenderMesh(meshList[GEO_PATH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 6, 120);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(330, 20, 50);
	RenderMesh(meshList[GEO_PATH], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 6, -120);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(330, 20, 50);
	RenderMesh(meshList[GEO_PATH], true);
	modelStack.PopMatrix();



	//lockers
	for (int i = 0; i < Lockerlist.size(); i++) {
		modelStack.PushMatrix();
		modelStack.Translate(Lockerlist[i].getpos().x, Lockerlist[i].getpos().y, Lockerlist[i].getpos().z);
		modelStack.Scale(0.2, 0.2, 0.2);
		RenderMesh(meshList[locker], true);
		modelStack.PopMatrix();
	}
	
	//vehicle
	modelStack.PushMatrix();
	modelStack.Translate(30, 4, 320);
	modelStack.Rotate(-20,0, 1,0);
	modelStack.Scale(8, 8, 8);
	RenderMesh(meshList[GEO_TRUCK], true);
	modelStack.PopMatrix();

	//UI OVERLAY

	//Vision vignette
	RenderMeshOnScreen(meshList[GEO_OVERLAY], 40, 30, 1, 1);
	//camcorder
	RenderMeshOnScreen(meshList[GEO_OVERLAY2], 40, 30, 1, 1);
	//stamina
	RenderMeshOnScreen(meshList[GEO_BAR], 14 - (5 - camera.playerStamina * 0.25), 52, camera.playerStamina * 0.5, 1);
	
	RenderMeshOnScreen(meshList[GEO_STAMINA],6, 52, 2, 2);

	//speeches
	switch (SpeakPhase)
	{
	case 0:
		RenderTextOnScreen(meshList[GEO_TEXT], "Look's like this is the place...", Color(1, 1, 0), 4, 10, 5);
		break;
	case 1:
		RenderTextOnScreen(meshList[GEO_TEXT], "I guess I better start looking around", Color(1, 1, 0), 4, 10, 5);
		break;
	case 2:
		RenderTextOnScreen(meshList[GEO_TEXT], "", Color(1, 1, 0), 4, 10, 5);
		break;
	}


	//objectives screen
	RenderTextOnScreen(meshList[GEO_TEXT], "Objectives:", Color(0, 1, 0), 4, 1, 10);
	//objectives
	switch (ObjectivePhase)
	{
	case 0:
		RenderTextOnScreen(meshList[GEO_TEXT], "", Color(1, 1, 0), 2, 1, 9);
		break;
	case 1:
		RenderTextOnScreen(meshList[GEO_TEXT], "Investigate the area", Color(1, 1, 0), 3, 3, 12);
		break;
	}



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
}

void SceneSP2Main::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneSP2Main::RenderSkybox()
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



//void SceneSP2Main::RenderDeadTree(int x, int z,float rotate)
//{
//	modelStack.PushMatrix();
//	modelStack.Translate(x, -5, z);
//	modelStack.Rotate(rotate, 0, 0, 1);
//	modelStack.Scale(5, 5, 5);
//	RenderMesh(meshList[Deadtrees], true);
//	modelStack.PopMatrix();
//}

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




