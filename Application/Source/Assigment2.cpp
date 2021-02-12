#include "Assigment2.h"
#include "GL\glew.h"
#include <stdlib.h>
#include <time.h>
#include "shader.hpp"
#include "LoadTGA.h"
#include <stdlib.h>

Assigment2::Assigment2()
{
}

Assigment2::~Assigment2()
{
}


void Assigment2::Init()
{
	// Init VBO here
	glClearColor(0, 0, 0, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//camera
	camera.Init(Vector3(0, 0, 270), Vector3(0, 0, 250), Vector3(0, 1,
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
	projection.SetToPerspective(46.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);
	glUseProgram(m_programID);
	//mesh
	meshList[LightSphere] = MeshBuilder::Generatesphere("LightBall", 1, 1, 1, White);
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Reference", 1, 1, 1);
	//skybox texture
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front",1,1,White);
	meshList[GEO_FRONT]->textureID = LoadTGA("Assigment2Images//front.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", 1, 1, White);
	meshList[GEO_BACK]->textureID = LoadTGA("Assigment2Images//back.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", 1, 1, White);
	meshList[GEO_LEFT]->textureID = LoadTGA("Assigment2Images//left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", 1, 1, White);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Assigment2Images//right.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", 1, 1, White);
	meshList[GEO_TOP]->textureID = LoadTGA("Assigment2Images//top.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", 1, 1, White);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Assigment2Images//bottom.tga");
	meshList[Ground_Mesh] = MeshBuilder::GenerateQuadRepeat("Hell", 1, 1, White);
	meshList[Ground_Mesh]->textureID = LoadTGA("Assigment2Images//GroundMesh.tga");
	meshList[Ground_Mesh]->material.kAmbient.Set(0,0.20,0.13);
	//light 0
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 20, 0);
	light[0].color.Set(White);
	light[0].power = 0.2;
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
	light[1].type = Light::LIGHT_POINT;
	light[1].position.Set(7.75,0.5 , -175);
	light[1].color.Set(White);
	light[1].power = 1;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1,
		&light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);
	//light 2
	light[2].type = Light::LIGHT_POINT;
	light[2].position.Set(-21.75, 1, -86.25);
	light[2].color.Set(White);
	light[2].power = 1;
	light[2].kC = 1.f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(45));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 3.f;
	light[2].spotDirection.Set(0.f, 1.f, 0.f);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1,&light[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[2].kQ);
	glUniform1i(m_parameters[U_LIGHT2_TYPE], light[2].type);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], light[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], light[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[2].exponent);
	//light 3
	light[3].type = Light::LIGHT_POINT;
	light[3].position.Set(10.5, 0.6, 26.25);
	light[3].color.Set(White);
	light[3].power = 1;
	light[3].kC = 1.f;
	light[3].kL = 0.01f;
	light[3].kQ = 0.001f;
	light[3].cosCutoff = cos(Math::DegreeToRadian(45));
	light[3].cosInner = cos(Math::DegreeToRadian(30));
	light[3].exponent = 3.f;
	light[3].spotDirection.Set(0.f, 1.f, 0.f);
	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1,&light[3].color.r);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], light[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], light[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], light[3].kQ);
	glUniform1i(m_parameters[U_LIGHT3_TYPE], light[3].type);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], light[3].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT3_COSINNER], light[3].cosInner);
	glUniform1f(m_parameters[U_LIGHT3_EXPONENT], light[3].exponent);
	//Set Material locations
	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT],
		m_parameters[U_MATERIAL_DIFFUSE],
		m_parameters[U_MATERIAL_SPECULAR],
		m_parameters[U_MATERIAL_SHININESS]);
	//light 4
	light[4].type = Light::LIGHT_POINT;
	light[4].position.Set(17, -0.5, 131.5);
	light[4].color.Set(White);
	light[4].power = 1;
	light[4].kC = 1.f;
	light[4].kL = 0.01f;
	light[4].kQ = 0.001f;
	light[4].cosCutoff = cos(Math::DegreeToRadian(45));
	light[4].cosInner = cos(Math::DegreeToRadian(30));
	light[4].exponent = 3.f;
	light[4].spotDirection.Set(0.f, 1.f, 0.f);
	glUniform3fv(m_parameters[U_LIGHT4_COLOR], 1, &light[4].color.r);
	glUniform1f(m_parameters[U_LIGHT4_POWER], light[4].power);
	glUniform1f(m_parameters[U_LIGHT4_KC], light[4].kC);
	glUniform1f(m_parameters[U_LIGHT4_KL], light[4].kL);
	glUniform1f(m_parameters[U_LIGHT4_KQ], light[4].kQ);
	glUniform1i(m_parameters[U_LIGHT4_TYPE], light[4].type);
	glUniform1f(m_parameters[U_LIGHT4_POWER], light[4].power);
	glUniform1f(m_parameters[U_LIGHT4_COSCUTOFF], light[4].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT4_COSINNER], light[4].cosInner);
	glUniform1f(m_parameters[U_LIGHT4_EXPONENT], light[4].exponent);
	//Set Material locations
	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT],
		m_parameters[U_MATERIAL_DIFFUSE],
		m_parameters[U_MATERIAL_SPECULAR],
		m_parameters[U_MATERIAL_SHININESS]);
	//number of lights
	glUniform1i(m_parameters[U_NUMLIGHTS], 5);
	//Megumin
	//Red Cube
	meshList[BodyRed] = MeshBuilder::GenerateCube("Cube", 1, 1, 1, Red);
	meshList[BodyRed]->material.kAmbient.Set(Red);
	//Brown Cube
	meshList[BodyBrown] = MeshBuilder::GenerateCube("Cube", 1, 1, 1, Brown);
	meshList[BodyBrown]->material.kAmbient.Set(Brown);
	//Yellow Cube
	meshList[BodyYellow] = MeshBuilder::GenerateCube("Cube", 1, 1, 1, Yellow);
	meshList[BodyYellow]->material.kAmbient.Set(Yellow);
	//Silver Cube
	meshList[BodySilver] = MeshBuilder::GenerateCube("Cube", 1, 1, 1, Silver);
	meshList[BodySilver]->material.kAmbient.Set(Silver);
	//Wheat Cube
	meshList[BodyWheat] = MeshBuilder::GenerateCube("Cube", 1, 1, 1, Wheat);
	meshList[BodyWheat]->material.kAmbient.Set(Wheat);
	//Black Cube
	meshList[BodyBlack] = MeshBuilder::GenerateCube("Cube", 1, 1, 1, Black);
	meshList[BodyBlack]->material.kAmbient.Set(Black);
	//White Cube
	meshList[BodyWhite] = MeshBuilder::GenerateCube("Cube", 1, 1, 1, White);
	meshList[BodyWhite]->material.kAmbient.Set(White);
	//Arm
	meshList[Arm] = MeshBuilder::GenerateCylinder("Cylinder", 1, 1, 1, Crimson);
	meshList[Arm]->material.kAmbient.Set(Crimson);
	//Leg
	meshList[Leg] = MeshBuilder::GenerateCylinder("Cylinder", 1, 1, 1, Wheat);
	meshList[Leg]->material.kAmbient.Set(Wheat);
	//Torus
	meshList[Torus] = MeshBuilder::GenerateTorus("Torus", 36, 36, 1, 0.5, Black);
	meshList[Torus]->material.kAmbient.Set(Black);
	//Santa clause
	meshList[HatCone] = MeshBuilder::GenerateCone("Santa Clause", 1, 1, 1, Black);
	meshList[HatCone]->material.kAmbient.Set(Black);
	//HalfCube brown
	meshList[HalfCube] = MeshBuilder::GenerateHalfCube("Weapon part and hair", 1, 1, 1, Brown);
	meshList[HalfCube]->material.kAmbient.Set(Brown);
	//orb
	meshList[Orb] = MeshBuilder::Generatesphere("Orb", 1, 1, 1, Red);
	meshList[Orb]->material.kAmbient.Set(Red);
	meshList[Orb]->material.kShininess = 1.f;
	// Make sure you pass uniform parameters after glUseProgram()
	//Dead Tree
	meshList[Deadtrees] = MeshBuilder::GenerateOBJMTL("Dead Tree", "OBJ//DeadTree.obj", "MTL//DeadTree.mtl");
	meshList[Deadtrees]->material.kAmbient.Set(0.12,0.08,0.04);//as dark as possible
	//Skull cause i can't find ghost
	meshList[Skeleton] = MeshBuilder::GenerateOBJ("Skull", "OBJ//Skull.obj");
	meshList[Skeleton]->material.kAmbient.Set(Gray);
	//ruins
	meshList[Ruins] = MeshBuilder::GenerateOBJ("Ruins", "OBJ//Ruin.obj");
	meshList[Ruins]->textureID = LoadTGA("Assigment2Images//RuinTexture.tga");
	meshList[Ruins]->material.kAmbient.Set(0.35, 0.35, 0.35);
	//Axe
	meshList[Axe] = MeshBuilder::GenerateOBJ("Axe", "OBJ//Fire_Axe.obj");
	meshList[Axe]->textureID = LoadTGA("Assigment2Images//Fire_Axe.tga");
	//Text
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Assigment2Images//Arial.tga");
	//World Text
	meshList[World_Text] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[World_Text]->textureID = LoadTGA("Assigment2Images//Arial.tga");
	//Lamp
	meshList[Lamp] = MeshBuilder::GenerateOBJ("Lamp", "OBJ//Lamp.obj");
	meshList[Lamp]->material.kAmbient.Set(0.49,0.49,0.49);
	//Black screen of death
	meshList[FinalScreen] = MeshBuilder::GenerateQuad2("End", 16, 16, Black);
	//init update stuff
	LSPEED = 10.F;
	glitchcount = 0;
	skyboxglitch = false;
	instructiontext = false;
	translateAxe = -180;
	phase = 0;
	textduration = 0;
	TranslateSkullY = 2;
	floatup = false;
	takeaxe = false;
	meguminglitch = false;
	treestatus = false;
	swinganimation = false;
	swingforward = false;
	swingback = false;
	renderskull = true;
	meguminrotation = false;
	axerotation = 90;
	glitchphase = 0;
	delay = 0;
	rotatehead = 0;
	allglitch = false;
	rendermegumin = false;
	finalfloatdown=false;
	finalscreen = false;
	//world text starting position
	//text Z
	for (int i = 0; i < 30; i++) {
		movingtextZ[i] = 280;
	}
	//text y random
	for (int i = 0; i < 30; i++) {
		movingtextY[i] = rand()%21;
	}
	//text x random
	for (int i = 0; i < 30; i++) {
		movingtextX[i] = 40-(rand() % 65);
	}
	//text speed random
	for (int i = 0; i < 30; i++) {
		movingtextspeed[i] = rand() % 50 + 10;
	}
}

void Assigment2::Update(double dt)
{
	//moving oftake
	if (takeaxe == true) {
		for (int i = 0; i < 30; i++) {
			movingtextZ[i] -= movingtextspeed[i] * dt;
			if (movingtextZ[i] < -280) {
				movingtextZ[i] = 280;
			}
		}
	}
	rotateAngle += (float)(90 * dt);
	scaleAll += (float)(2 * dt);
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
	//FinalScreen Button events
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
	}
	//interation events
	static bool EButtonState = false;
	if (!EButtonState && Application::IsKeyPressed('E'))
	{
		EButtonState = true;
	}
	else if (EButtonState && !Application::IsKeyPressed('E'))
	{
		EButtonState = false;
	}
	//Texture changes
	switch (glitchphase) {
	case 0:
		//glitchingskybox condition
		if (camera.position.z < -40) {
			skyboxglitch = true;
			if (phase == 1) {
				phase = 2;
				textduration = 0;
			}
		}
		//change skybox temporary
		if (skyboxglitch == true) {
			glitchcount++;
			if (glitchcount > 160) {
				meshList[GEO_TOP]->textureID = LoadTGA("Night//Top.tga");
				meshList[GEO_BOTTOM]->textureID = LoadTGA("Night//Bottom.tga");
				meshList[GEO_LEFT]->textureID = LoadTGA("Night//Left.tga");
				meshList[GEO_RIGHT]->textureID = LoadTGA("Night//Right.tga");
				meshList[GEO_FRONT]->textureID = LoadTGA("Night//Front.tga");
				meshList[GEO_BACK]->textureID = LoadTGA("Night//Back.tga");
				meshList[Ground_Mesh]->textureID = LoadTGA("Assigment2Images//GroundMesh.tga");
				meshList[Ground_Mesh]->material.kAmbient.Set(0.00, 0.00, 0.00);
				treestatus = true;
				skyboxglitch = false;
				rendermegumin = true;
				glitchphase++;
			}
			//should only apply once
			else if (glitchcount == 1) {
				meshList[GEO_TOP]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
				meshList[GEO_BOTTOM]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
				meshList[GEO_LEFT]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
				meshList[GEO_RIGHT]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
				meshList[GEO_FRONT]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
				meshList[GEO_BACK]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
				meshList[Ground_Mesh]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
				meshList[Ground_Mesh]->material.kAmbient.Set(White);
			}
		}
		break;
	case 1:
		//megumin glitch conditions
		if (camera.position.z > 140 && takeaxe == true) {
			meguminglitch = true;
			if (phase == 9) {
				phase = 10;
				textduration = 0;
			}
		}
		//permanent megumin glitch;
		if (meguminglitch == true) {
			meshList[Ground_Mesh]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
			meshList[Ground_Mesh]->material.kAmbient.Set(White);
			meshList[BodyBlack]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
			meshList[BodyYellow]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
			meshList[BodyBrown]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
			meshList[BodyRed]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
			glitchphase++;
			meguminrotation = true;
		}
		break;
	case 2:
		//Change every possible texture except text
		if (allglitch == true) {
			meshList[GEO_TOP]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
			meshList[GEO_BOTTOM]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
			meshList[GEO_LEFT]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
			meshList[GEO_RIGHT]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
			meshList[GEO_FRONT]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
			meshList[GEO_BACK]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
			meshList[Ground_Mesh]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
			meshList[Deadtrees]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
			meshList[Deadtrees]->material.kAmbient.Set(White);
			meshList[Ruins]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
			meshList[Ruins]->material.kAmbient.Set(White);
			meshList[Skeleton]->textureID = LoadTGA("Glitch//GlitchingTextures.tga");
			meshList[Skeleton]->material.kAmbient.Set(White);
			glitchphase++;
		}
		break;
	case 3:
		//reset counter
		if (phase == 15) {
			glitchcount == 0;
			glitchphase++;
		}
		break;
	case 4:
		glitchcount++;
		//show Ending Screen once it reach
		if (glitchcount >= 600) {
			glitchphase++;
			finalscreen = true;
			textduration = 0;
			phase++;
		}
		break;
	}
	//megumin head rotation;
	if (meguminrotation == true) {
		rotatehead += 180.f * dt;
	}
	//skull float
	if (takeaxe == false && phase!=15) {
		if (floatup == false) {
			TranslateSkullY -= 1.f * dt;
			if (TranslateSkullY < 1) {
				floatup = true;
			}
		}
		else {
			TranslateSkullY += 1.f * dt;
			if (TranslateSkullY > 2) {
				floatup = false;
			}
		}
	}
	else if(takeaxe==true && phase!=15){
		TranslateSkullY += 10.f * dt;
		if (TranslateSkullY > 100) {
			TranslateSkullY = 100;
			renderskull = false;
		}
	}
	
	//axe movement
	//beggining
	if (phase >= 5 && phase <= 9) {
		if (translateAxe < -170) {
			translateAxe += 2.0f * dt;
		}
		else {
			translateAxe = -170;
		}
	}
	//Swinging animation
	if (swinganimation == true) {
		if (swingforward == true) {
			axerotation -= 360.f * dt;
			if (axerotation <= 0) {
				axerotation = 0;
				swingback = true;
				swingforward = false;
			}
		}
		if (swingback == true) {
			axerotation += 360.f * dt;
			if (axerotation >= 90) {
				axerotation = 90;
				swingback = false;
				swinganimation = false;
			}
		}
	}
	//Final(skull comes to your screen)
	if (phase == 15 && finalfloatdown==false) {
		TranslateSkullY = 5;
		finalfloatdown = true;
		renderskull = true;
	}
	if (finalfloatdown == true) {
		TranslateSkullY -= 2.0f * dt;
		if (TranslateSkullY <= 0.7) {
			TranslateSkullY = 0.7;
		}
	}
	//text counter timing thing
	switch (phase) {
	case 0:
		textduration++;
		if (textduration > 240) {
			phase++;
			textduration = 0;
		}
		break;
	case 1:
		textduration++;
		if (textduration >= 240) {
			textduration = 240;
		}
		break;
	case 2:
		textduration++;
		if (textduration > 80) {
			phase++;
			textduration = 0;
		}
		break;
	case 3:
		textduration++;
		if (textduration > 80) {
			phase++;
			textduration = 0;
		}
		break;
	case 4:
		textduration++;
		if (textduration >= 80) {
			textduration = 80;
		}
		break;
	case 5:
		textduration++;
		if (textduration > 160) {
			phase++;
			textduration = 0;
		}
		break;
	case 6:
		textduration++;
		if (textduration > 120) {
			phase++;
			textduration = 0;
		}
		break;
	case 7:
		textduration++;
		if (textduration > 120) {
			phase++;
			textduration = 0;
		}
		break;
	case 8:
		textduration++;
		if (textduration > 120) {
			phase++;
			textduration = 0;
		}
		break;
	case 9:
		textduration++;
		if (textduration >= 120) {
			textduration = 120;
		}
		break;
	case 10:
		textduration++;
		if (textduration > 240) {
			phase++;
			textduration = 0;
		}
		break;
	case 11:
		textduration++;
		if (textduration >= 240) {
			textduration = 240;
		}
		break;
	case 12:
		textduration++;
		if (textduration > 240) {
			phase++;
			textduration = 0;
		}
		break;
	case 13:
		textduration++;
		if (textduration > 240) {
			phase++;
			textduration = 0;
		}
		break;
	case 14:
		textduration++;
		if (textduration > 240) {
			phase++;
			textduration = 0;
		}
		break;
	case 15:
		textduration++;
		if (textduration >= 120) {
			textduration = 120;
		}
		break;
	case 16:
		textduration++;
		if (textduration >= 180) {
			textduration = 180;
		}
		break;
	}
	//Final Interaction(attacking megumin)
	if (takeaxe == true && phase==11) {
		if (bLButtonState==true && swinganimation == false) {
			swinganimation = true;
			swingforward = true;
		}
		if (textduration >= 240) {
			if ((camera.position.x > -5 && camera.position.x < 5) && (camera.position.z > 265 && camera.position.z < 270)) {
				instructiontext = true;
				if (bLButtonState == true && phase == 11) {
					rendermegumin = false;
					takeaxe = false;
					allglitch = true;
					phase++;
					textduration = 0;
				}
			}
			else {
				instructiontext = false;
			}
		}
	}
	//third interaction(Cutting Tree)
	else if (takeaxe == true) {
		delay++;
		if (delay > 10) {
			delay = 10;
		}
		if (delay == 10) {
			//swinging of axe
			if (bLButtonState == true && swinganimation==false) {
				swinganimation = true;
				swingforward = true;
			}
		}
		//Cutting of Tree
		if ((camera.position.x > -35 && camera.position.x < 40) && (camera.position.z > 20 && camera.position.z < 30)) {
			instructiontext = true;
			if (bLButtonState == true) {
				treestatus = false;
			}
			if (treestatus == false) {
				instructiontext = false;
			}
		}
		else {
			instructiontext = false;
		}
	}
	//Second Interaction(Taking Axe)
	else if (phase == 9 && textduration >= 120 && takeaxe == false) {
		if ((camera.position.x > 3 && camera.position.x < 8) && (camera.position.z > -165 && camera.position.z < -155)) {
			instructiontext = true;
			if (Application::IsKeyPressed('E')) {
				takeaxe = true;
			}
		}
		else {
			instructiontext = false;
		}
	}
	//First Interaction(Talking with skull)
	else if (phase==4 && textduration>=80) {
		if ((camera.position.x > -10 && camera.position.x < 10) && (camera.position.z > -165 && camera.position.z < -155)) {
			instructiontext = true;
			if (EButtonState == true) {
				phase++;
				textduration = 0;
			}
		}
		else {
			instructiontext = false;
		}
	}
	else {
		instructiontext = false;
	}
	//fps
	fps = 1.f / dt;
	//camera
	camera.Update(dt);
	
}

void Assigment2::Render()
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
	else if(light[0].type==Light::LIGHT_POINT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		
	}

	//axes
	/*modelStack.PushMatrix();
	RenderMesh(meshList[GEO_AXES], false);
	modelStack.PopMatrix();*/
	//for lamp light
	if (allglitch == false) {
		//light 1
		modelStack.PushMatrix();
		modelStack.Translate(light[1].position.x, light[1].position.y,
			light[1].position.z);
		modelStack.Scale(1.5, 1.5, 1.5);
		RenderMesh(meshList[LightSphere], false);
		modelStack.PopMatrix();
		//light 2
		modelStack.PushMatrix();
		modelStack.Translate(light[2].position.x, light[2].position.y,
			light[2].position.z);
		modelStack.Scale(1.5, 1.5, 1.5);
		RenderMesh(meshList[LightSphere], false);
		modelStack.PopMatrix();
		//light 3
		modelStack.PushMatrix();
		modelStack.Translate(light[3].position.x, light[3].position.y,
			light[3].position.z);
		modelStack.Scale(1.5, 1.5, 1.5);
		RenderMesh(meshList[LightSphere], false);
		modelStack.PopMatrix();
		//light 4
		modelStack.PushMatrix();
		modelStack.Translate(light[4].position.x, light[4].position.y,
			light[4].position.z);
		modelStack.Scale(1.5, 1.5, 1.5);
		RenderMesh(meshList[LightSphere], false);
		modelStack.PopMatrix();
	}
	//Megumin
	if (rendermegumin==true) {
		RenderMegumin();
	}
	
	//skybox
	RenderSkybox();
	//ground Mesh
	modelStack.PushMatrix();
	modelStack.Translate(0, -4, 0);
	modelStack.Scale(600, 1, 600);
	RenderMesh(meshList[Ground_Mesh], true);
	modelStack.PopMatrix();
	//destroyed small building
	modelStack.PushMatrix();
	modelStack.Translate(0, -4, -230);
	modelStack.Scale(8, 8, 8);
	RenderMesh(meshList[Ruins], true);
	modelStack.PopMatrix();
	//dead trees
	//row one
	RenderDeadTree(290, 290, 0);
	RenderDeadTree(260, 290, 0);
	RenderDeadTree(230, 290, 0);
	RenderDeadTree(200, 290, 0);
	RenderDeadTree(170, 290, 0);
	RenderDeadTree(140, 290, 0);
	RenderDeadTree(110, 290, 0);
	RenderDeadTree(80, 290, 0);
	//sub row of trees using x=50
	RenderDeadTree(50, 290, 0);
	RenderDeadTree(50, 260, 0);
	RenderDeadTree(50, 230, 0);
	RenderDeadTree(50, 200, 0);
	RenderDeadTree(50, 170, 0);
	RenderDeadTree(50, 140, 0);
	RenderDeadTree(50, 110, 0);
	RenderDeadTree(50, 80, 0);
	RenderDeadTree(50, 50, 0);
	RenderDeadTree(50, 20, 0);
	RenderDeadTree(50, -10, 0);
	RenderDeadTree(50, -40, 0);
	RenderDeadTree(50, -70, 0);
	RenderDeadTree(50, -100, 0);
	RenderDeadTree(50, -130, 0);
	RenderDeadTree(50, -170, 0);
	RenderDeadTree(50, -200, 0);
	RenderDeadTree(50, -230, 0);
	RenderDeadTree(50, -260, 0);
	RenderDeadTree(50, -290, 0);
	//continued row 1
	RenderDeadTree(20, 290, 0);
	RenderDeadTree(-10, 290, 0);
	//sub row of trees using x=-40
	RenderDeadTree(-40, 290, 0);
	RenderDeadTree(-40, 260, 0);
	RenderDeadTree(-40, 230, 0);
	RenderDeadTree(-40, 200, 0);
	RenderDeadTree(-40, 170, 0);
	RenderDeadTree(-40, 140, 0);
	RenderDeadTree(-40, 110, 0);
	RenderDeadTree(-40, 80, 0);
	RenderDeadTree(-40, 50, 0);
	RenderDeadTree(-40, 20, 0);
	RenderDeadTree(-40, -10, 0);
	RenderDeadTree(-40, -40, 0);
	RenderDeadTree(-40, -70, 0);
	RenderDeadTree(-40, -100, 0);
	RenderDeadTree(-40, -130, 0);
	RenderDeadTree(-40, -170, 0);
	RenderDeadTree(-40, -200, 0);
	RenderDeadTree(-40, -230, 0);
	RenderDeadTree(-40, -260, 0);
	RenderDeadTree(-40, -290, 0);
	//cotinued row 1
	RenderDeadTree(-70, 290, 0);
	RenderDeadTree(-100, 290, 0);
	RenderDeadTree(-130, 290, 0);
	RenderDeadTree(-170, 290, 0);
	RenderDeadTree(-200, 290, 0);
	RenderDeadTree(-230, 290, 0);
	RenderDeadTree(-260, 290, 0);
	RenderDeadTree(-290, 290, 0);
	//row 2
	RenderDeadTree(-290, 260, 0);
	RenderDeadTree(-290, 230, 0);
	RenderDeadTree(-290, 200, 0);
	RenderDeadTree(-290, 170, 0);
	RenderDeadTree(-290, 140, 0);
	RenderDeadTree(-290, 110, 0);
	RenderDeadTree(-290, 80, 0);
	RenderDeadTree(-290, 50, 0);
	RenderDeadTree(-290, 20, 0);
	RenderDeadTree(-290, -10, 0);
	RenderDeadTree(-290, -40, 0);
	RenderDeadTree(-290, -70, 0);
	RenderDeadTree(-290, -100, 0);
	RenderDeadTree(-290, -130, 0);
	RenderDeadTree(-290, -170, 0);
	RenderDeadTree(-290, -200, 0);
	RenderDeadTree(-290, -230, 0);
	RenderDeadTree(-290, -260, 0);
	RenderDeadTree(-290, -290, 0);
	//row 3
	RenderDeadTree(290, -290, 0);
	RenderDeadTree(260, -290, 0);
	RenderDeadTree(230, -290, 0);
	RenderDeadTree(200, -290, 0);
	RenderDeadTree(170, -290, 0);
	RenderDeadTree(140, -290, 0);
	RenderDeadTree(110, -290, 0);
	RenderDeadTree(80, -290, 0);
	RenderDeadTree(20, -290, 0);
	RenderDeadTree(-10, -290, 0);
	RenderDeadTree(-70, -290, 0);
	RenderDeadTree(-100, -290, 0);
	RenderDeadTree(-130, -290, 0);
	RenderDeadTree(-170, -290, 0);
	RenderDeadTree(-200, -290, 0);
	RenderDeadTree(-230, -290, 0);
	RenderDeadTree(-260, -290, 0);
	RenderDeadTree(-290, -290, 0);
	//row 4
	RenderDeadTree(290, 260, 0);
	RenderDeadTree(290, 230, 0);
	RenderDeadTree(290, 200, 0);
	RenderDeadTree(290, 170, 0);
	RenderDeadTree(290, 140, 0);
	RenderDeadTree(290, 110, 0);
	RenderDeadTree(290, 80, 0);
	RenderDeadTree(290, 50, 0);
	RenderDeadTree(290, 20, 0);
	RenderDeadTree(290, -10, 0);
	RenderDeadTree(290, -40, 0);
	RenderDeadTree(290, -70, 0);
	RenderDeadTree(290, -100, 0);
	RenderDeadTree(290, -130, 0);
	RenderDeadTree(290, -170, 0);
	RenderDeadTree(290, -200, 0);
	RenderDeadTree(290, -230, 0);
	RenderDeadTree(290, -260, 0);
	RenderDeadTree(290, -290, 0);
	//special tree
	if (treestatus==true) {
		RenderDeadTree(50, 50, 70);
		RenderDeadTree(-50, 50, -85);
		//boundary
		camera.SetBounds(-35, 40, -165, 30);
	}
	else {
		//boundary
		camera.SetBounds(-35, 40, -165, 270);
	}
	if (allglitch == false) {
		//Lamp 1
		modelStack.PushMatrix();
		modelStack.Translate(10, -3, -175);
		modelStack.Rotate(35, 0, 0, 1);
		RenderMesh(meshList[Lamp], true);
		modelStack.PopMatrix();
		//Lamp 2
		modelStack.PushMatrix();
		modelStack.Translate(-23, -3, -85);
		modelStack.Rotate(-25, 1, 0, 1);
		RenderMesh(meshList[Lamp], true);
		modelStack.PopMatrix();
		//Lamp 3
		modelStack.PushMatrix();
		modelStack.Translate(17, -3, 135);
		modelStack.Rotate(-60, 1, 0, 0);
		RenderMesh(meshList[Lamp], true);
		modelStack.PopMatrix();
		//Lamp 4
		modelStack.PushMatrix();
		modelStack.Translate(12, -3, 25);
		modelStack.Rotate(30, 1, 0, 1);
		RenderMesh(meshList[Lamp], true);
		modelStack.PopMatrix();
	}
	
	//axe
	if (takeaxe == false) {
		modelStack.PushMatrix();
		modelStack.Translate(5, 1.5, translateAxe);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Rotate(90, 0, 0, 1);
		modelStack.Scale(0.1, 0.1, 0.1);
		RenderMesh(meshList[Axe], true);
		modelStack.PopMatrix();
	}
	else {
		modelStack.PushMatrix();
		modelStack.Translate(camera.AxePosition.x, camera.AxePosition.y, camera.AxePosition.z);
		modelStack.Rotate(camera.AxeYaw, 0, 1, 0);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Rotate(axerotation, 0, 0, 1);
		modelStack.Scale(0.1, 0.1, 0.1);
		RenderMesh(meshList[Axe], true);
		modelStack.PopMatrix();
	}
	
	//fps
	if (finalscreen == false) {
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "FPS:" + std::to_string(fps), Color(0, 1, 0), 4, 0, 14);
		modelStack.PopMatrix();
		//instruction text
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "WASD to move and look around", Color(0, 1, 0), 4, 0, 13);
		modelStack.PopMatrix();
	}
	if (takeaxe == true) {
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Click to swing", Color(0, 1, 0), 4, 0, 12);
		modelStack.PopMatrix();
	}
	//skull
	if (renderskull == true && phase == 15) {
		modelStack.PushMatrix();
		modelStack.Translate(camera.Skullposition.x, TranslateSkullY, camera.Skullposition.z);
		modelStack.Rotate(camera.AxeYaw, 0, 1, 0);
		modelStack.Rotate(-90, 1, 0, 0);
		RenderMesh(meshList[Skeleton], true);
		modelStack.PopMatrix();
	}
	else if (renderskull == true) {
		modelStack.PushMatrix();
		modelStack.Translate(0, TranslateSkullY, -175);
		modelStack.Rotate(-90, 1, 0, 0);
		RenderMesh(meshList[Skeleton], true);
		modelStack.PopMatrix();
	}
	//Ending Screen
	if (finalscreen == true) {
		modelStack.PushMatrix();
		RenderMeshOnScreen(meshList[FinalScreen], 40, 30, 200, 200);
		modelStack.PopMatrix();
	}
	//Story text
	modelStack.PushMatrix();
	switch (phase) {
	case 0:
		RenderTextOnScreen(meshList[GEO_TEXT], "Looks like this is the place,something doesn't feel right....", Color(1,1,0), 4, 10, 5);
		break;
	case 1:
		if (textduration < 240) {
			RenderTextOnScreen(meshList[GEO_TEXT], "Let's just start by going over that building over there", Color(1,1,0), 4, 10, 5);
		}
		break;
	case 2:
		RenderTextOnScreen(meshList[GEO_TEXT], "Over...", Color(1, 1, 0),4,22,5);
		break;
	case 3:
		RenderTextOnScreen(meshList[GEO_TEXT], "Here...", Color(1, 1, 0),4,22,5);
		break;
	case 4:
		if (textduration < 80) {
			RenderTextOnScreen(meshList[GEO_TEXT], "Boy...", Color(1, 1, 0),4,22,5);
		}
		break;
	case 5:
		RenderTextOnScreen(meshList[GEO_TEXT], "My House...", Color(1, 1, 0), 4, 21, 5);
		break;
	case 6:
		RenderTextOnScreen(meshList[GEO_TEXT], "Her...", Color(1, 1, 0), 4, 22, 5);
		break;
	case 7:
		RenderTextOnScreen(meshList[GEO_TEXT], "Kill...", Color(1, 1, 0), 4, 22, 5);
		break;
	case 8:
		RenderTextOnScreen(meshList[GEO_TEXT], "Her...", Color(1, 1, 0), 4, 22, 5);
		break;
	case 9:
		if (textduration < 120) {
			RenderTextOnScreen(meshList[GEO_TEXT], "Behind...", Color(1, 1, 0), 4, 22, 5);
		}
		break;
	case 10:
		RenderTextOnScreen(meshList[GEO_TEXT], "Everything is not real", Color(1, 1, 0), 4, 18, 5);
		break;
	case 11:
		if (textduration < 240) {
			RenderTextOnScreen(meshList[GEO_TEXT], "Why must you do this", Color(1, 1, 0), 4, 18, 5);
		}
		break;
	case 12:
		RenderTextOnScreen(meshList[GEO_TEXT], "Useless", Color(1, 1, 0), 4, 22, 5);
		break;
	case 13:
		RenderTextOnScreen(meshList[GEO_TEXT], "Everything you see here is just a simulation",Color(1,1,0) ,4, 13, 5);
		break;
	case 14:
		RenderTextOnScreen(meshList[GEO_TEXT], "You can never escape...You're never real...", Color(1, 1, 0), 4, 13, 5);
		break;
	case 15:
		RenderTextOnScreen(meshList[GEO_TEXT], "Just...A....Simulation...", Color(1, 1, 0), 4, 18, 5);
		break;
	case 16:
		if (textduration == 180) {
			RenderTextOnScreen(meshList[GEO_TEXT], "FIN", Color(1, 1, 0),10,9,2.5);
		}
		break;
	}
	modelStack.PopMatrix();
	//E/Click to interact text
	if (instructiontext == true) {
		if (takeaxe == false) {
			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Press E to Interact", Color(1, 1, 0), 4, 20, 5);
			modelStack.PopMatrix();
		}
		else {
			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Click to Interact", Color(1, 1, 0), 4, 20, 5);
			modelStack.PopMatrix();
		}
	}
	//world text
	if (takeaxe == true) {
		for (int i = 0; i < 30; i++) {
			modelStack.PushMatrix();
			modelStack.Translate(movingtextX[i], movingtextY[i], movingtextZ[i]);
			modelStack.Rotate(180, 0, 1, 0);
			RenderText(meshList[World_Text], "Starting Termination", Color(1, 1, 1));
			modelStack.PopMatrix();
		}
	}
}

void Assigment2::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void Assigment2::RenderSkybox()
{
	//scale, translate, rotate
	modelStack.PushMatrix();
	modelStack.Translate(0+camera.position.x, 0+camera.position.y, 1.0f+camera.position.z);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0+camera.position.x, 0+camera.position.y, -1.0f+camera.position.z);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(1.0f+camera.position.x, 0+camera.position.y, 0+camera.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-1.0f+camera.position.x, 0+camera.position.y, 0+camera.position.z);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0+camera.position.x,-1.0f+camera.position.y, 0+camera.position.z);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0+camera.position.x, 1.0f+camera.position.y, 0+camera.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}

void Assigment2::RenderMegumin()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 280);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(1.0f, 1.0f, 1.0f);
	RenderMesh(meshList[BodyYellow], true);
		//hat
		//cone
		modelStack.PushMatrix();
		modelStack.Translate(0.f, 5.70f, 0.f);
		modelStack.Scale(1.75f, 1.5f, 1.75f);
		RenderMesh(meshList[HatCone], true);
		modelStack.PopMatrix();
		//Torus
		modelStack.PushMatrix();
		modelStack.Translate(0, 4.5f, 0);
		modelStack.Scale(2.3f, 0.5f, 2.3f);
		RenderMesh(meshList[Torus], true);
		modelStack.PopMatrix();
		//Head
		modelStack.PushMatrix();
		modelStack.Translate(0, 2.75f, 0);
		modelStack.Rotate(rotatehead, 0, 1, 0);
		modelStack.Scale(3, 3.2f, 3.5f);
		RenderMesh(meshList[BodyWheat], true);
			//hair
			//left side part 1
			//part 1
			modelStack.PushMatrix();
			modelStack.Translate(-0.65f, -0.6f, 0.32f);
			modelStack.Scale(0.3f, 0.3f, 0.3f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//part 2
			modelStack.PushMatrix();
			modelStack.Translate(-0.65f, -0.1f, 0.32f);
			modelStack.Scale(0.3f, 0.7f, 0.3f);
			RenderMesh(meshList[BodyBrown], true);
			modelStack.PopMatrix();
			//part 3
			modelStack.PushMatrix();
			modelStack.Translate(-0.65f, 0.4f, 0.32f);
			modelStack.Rotate(-90, 0, 0, 1);
			modelStack.Scale(0.3f, 0.3f, 0.3f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//Left side part 2
			//part 1
			modelStack.PushMatrix();
			modelStack.Translate(-0.7f, -0.36f, 0.1f);
			modelStack.Scale(0.4f, 0.3f, 0.2f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//part 2
			modelStack.PushMatrix();
			modelStack.Translate(-0.7f, 0.02f, 0.1f);
			modelStack.Scale(0.4f, 0.46f, 0.2f);
			RenderMesh(meshList[BodyBrown], true);
			modelStack.PopMatrix();
			//part 3
			modelStack.PushMatrix();
			modelStack.Translate(-0.7f, 0.4f, 0.1f);
			modelStack.Rotate(-90, 0, 0, 1);
			modelStack.Scale(0.3f, 0.4f, 0.2f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//Left side part 3
			//part 1
			modelStack.PushMatrix();
			modelStack.Translate(-0.7f, -0.36f, -0.15f);
			modelStack.Scale(0.4f, 0.3f, 0.3f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//part 2
			modelStack.PushMatrix();
			modelStack.Translate(-0.7f, 0.02f, -0.15f);
			modelStack.Scale(0.4f, 0.46f, 0.3f);
			RenderMesh(meshList[BodyBrown], true);
			modelStack.PopMatrix();
			//part 3
			modelStack.PushMatrix();
			modelStack.Translate(-0.8f, 0.25f, -0.15f);
			modelStack.Rotate(-90, 0, 0, 1);
			modelStack.Scale(0.5f, 0.60f, 0.3f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//Left side part 4
			//part 1
			modelStack.PushMatrix();
			modelStack.Translate(-0.7f, -0.36f, -0.38f);
			modelStack.Scale(0.4f, 0.3f, 0.25f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//part 2
			modelStack.PushMatrix();
			modelStack.Translate(-0.7f, 0.02f, -0.38f);
			modelStack.Scale(0.4f, 0.46f, 0.25f);
			RenderMesh(meshList[BodyBrown], true);
			modelStack.PopMatrix();
			//part 3
			modelStack.PushMatrix();
			modelStack.Translate(-0.7f, 0.4f, -0.38f);
			modelStack.Rotate(-90, 0, 0, 1);
			modelStack.Scale(0.3f, 0.4f, 0.25f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//right side part 1
			//part 1
			modelStack.PushMatrix();
			modelStack.Translate(0.65f, -0.6f, 0.32f);
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(0.3f, 0.3f, 0.3f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//part 2
			modelStack.PushMatrix();
			modelStack.Translate(0.65f, -0.1f, 0.32f);
			modelStack.Scale(0.3f, 0.7f, 0.3f);
			RenderMesh(meshList[BodyBrown], true);
			modelStack.PopMatrix();
			//part 3
			modelStack.PushMatrix();
			modelStack.Translate(0.65f, 0.4f, 0.32f);
			modelStack.Rotate(90, 0, 0, 1);
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(0.3f, 0.3f, 0.3f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//right side part 2
			//part 1
			modelStack.PushMatrix();
			modelStack.Translate(0.7f, -0.36f, 0.1f);
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(0.4f, 0.3f, 0.2f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//part 2
			modelStack.PushMatrix();
			modelStack.Translate(0.7f, 0.02f, 0.1f);
			modelStack.Scale(0.4f, 0.46f, 0.2f);
			RenderMesh(meshList[BodyBrown], true);
			modelStack.PopMatrix();
			//part 3
			modelStack.PushMatrix();
			modelStack.Translate(0.7f, 0.4f, 0.1f);
			modelStack.Rotate(90, 0, 0, 1);
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(0.3f, 0.4f, 0.2f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//right side part 3
			//part 1
			modelStack.PushMatrix();
			modelStack.Translate(0.7f, -0.36f, -0.15f);
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(0.4f, 0.3f, 0.3f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//part 2
			modelStack.PushMatrix();
			modelStack.Translate(0.7f, 0.02f, -0.15f);
			modelStack.Scale(0.4f, 0.46f, 0.3f);
			RenderMesh(meshList[BodyBrown], true);
			modelStack.PopMatrix();
			//part 3
			modelStack.PushMatrix();
			modelStack.Translate(0.8f, 0.25f, -0.15f);
			modelStack.Rotate(90, 0, 0, 1);
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(0.5f, 0.60f, 0.3f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//right side part 4
			//part 1
			modelStack.PushMatrix();
			modelStack.Translate(0.7f, -0.36f, -0.38f);
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(0.4f, 0.3f, 0.25f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//part 2
			modelStack.PushMatrix();
			modelStack.Translate(0.7f, 0.02f, -0.38f);
			modelStack.Scale(0.4f, 0.46f, 0.25f);
			RenderMesh(meshList[BodyBrown], true);
			modelStack.PopMatrix();
			//part 3
			modelStack.PushMatrix();
			modelStack.Translate(0.7f, 0.4f, -0.38f);
			modelStack.Rotate(90, 0, 0, 1);
			modelStack.Rotate(180, 0, 1, 0);
			modelStack.Scale(0.3f, 0.4f, 0.25f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//Front hair part 1
			modelStack.PushMatrix();
			modelStack.Translate(-0.33f, 0.275f, 0.501f);
			modelStack.Scale(0.35f, 0.5f, 0.05f);
			RenderMesh(meshList[BodyBrown], true);
			modelStack.PopMatrix();
			//Front hair part 2
			//part 1
			modelStack.PushMatrix();
			modelStack.Translate(-0.1f, 0.125f, 0.501f);
			modelStack.Scale(0.15f, 0.2f, 0.2f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//part 2
			modelStack.PushMatrix();
			modelStack.Translate(-0.1f, 0.35f, 0.501f);
			modelStack.Scale(0.15f, 0.3f, 0.2f);
			RenderMesh(meshList[BodyBrown], true);
			modelStack.PopMatrix();
			//Front hair part 3
			//part 1
			modelStack.PushMatrix();
			modelStack.Translate(0.05f, 0.125f, 0.501f);
			modelStack.Scale(0.15f, 0.2f, 0.2f);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//part 2
			modelStack.PushMatrix();
			modelStack.Translate(0.05f, 0.35f, 0.501f);
			modelStack.Scale(0.15f, 0.3f, 0.2f);
			RenderMesh(meshList[BodyBrown], true);
			modelStack.PopMatrix();
			//Front hair part 4
			modelStack.PushMatrix();
			modelStack.Translate(0.4f, 0.275f, 0.55f);
			modelStack.Rotate(20, 0, 1, 1);
			modelStack.Scale(0.35f, 0.5f, 0.05f);
			RenderMesh(meshList[BodyBrown], true);
			modelStack.PopMatrix();
			//Back hair
			//part 1
			modelStack.PushMatrix();
			modelStack.Translate(0.f, -0.36f, -0.60f);
			modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Scale(0.2f, 0.3f, 1);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//part 2
			modelStack.PushMatrix();
			modelStack.Translate(0, 0.02f, -0.60f);
			modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Scale(0.2f, 0.46f, 1);
			RenderMesh(meshList[BodyBrown], true);
			modelStack.PopMatrix();
			//part 3
			modelStack.PushMatrix();
			modelStack.Translate(0, 0.4f, -0.60f);
			modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Rotate(-90, 0, 0, 1);
			modelStack.Scale(0.3f, 0.2f, 1);
			RenderMesh(meshList[HalfCube], true);
			modelStack.PopMatrix();
			//eye 1
			modelStack.PushMatrix();
			modelStack.Translate(-0.2f, -0.10f, 0.401f);
			modelStack.Scale(0.1f, 0.25f, 0.2f);
			RenderMesh(meshList[BodyBlack], true);
			modelStack.PopMatrix();
			//eye 1 part 2
			modelStack.PushMatrix();
			modelStack.Translate(-0.3f, -0.10f, 0.401f);
			modelStack.Scale(0.1f, 0.25f, 0.2f);
			RenderMesh(meshList[BodyWhite], true);
			modelStack.PopMatrix();
			//eye 2
			modelStack.PushMatrix();
			modelStack.Translate(0.2f, -0.10f, 0.401f);
			modelStack.Scale(0.1f, 0.25f, 0.2f);
			RenderMesh(meshList[BodyBlack], true);
			modelStack.PopMatrix();
			//eye 2 part 2
			modelStack.PushMatrix();
			modelStack.Translate(0.3f, -0.10f, 0.401f);
			modelStack.Scale(0.1f, 0.25f, 0.2f);
			RenderMesh(meshList[BodyWhite], true);
			modelStack.PopMatrix();
		modelStack.PopMatrix();
	modelStack.PopMatrix();
	//Top of the body connecting to arm and head
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 280);
	modelStack.Scale(2.5f, 2.5f, 2.5f);
	RenderMesh(meshList[BodyRed], true);
		//Left arm
		modelStack.PushMatrix();
		modelStack.Translate(-0.75f, -0.2f, 0.f);
		modelStack.Scale(0.2f, 0.2f, 0.2f);
		modelStack.Rotate(-60, 0, 0, 1);
		modelStack.Rotate(0, 1, 0, 0);
		RenderMesh(meshList[Arm], true);
			//left Hand connecting to weapon
			modelStack.PushMatrix();
			modelStack.Translate(0, -2.6f, 0);
			modelStack.Rotate(0, 0, 1, 0);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[Torus], true);
				//weapon
				//part 1
				modelStack.PushMatrix();
				modelStack.Translate(-4, -0.9f, 0);
				modelStack.Scale(15, 1, 2);
				RenderMesh(meshList[BodyBrown], true);
				modelStack.PopMatrix();
				//part 2
				modelStack.PushMatrix();
				modelStack.Translate(-10, -2.3f, 0);
				modelStack.Rotate(90, 0, 0, 1);
				modelStack.Scale(3, 3, 2);
				RenderMesh(meshList[HalfCube], true);
				modelStack.PopMatrix();
				//part 3
				modelStack.PushMatrix();
				modelStack.Translate(-13, -3, 0);
				modelStack.Rotate(90, 0, 0, 1);
				modelStack.Scale(1.5, 6, 2);
				RenderMesh(meshList[BodyBrown], true);
				modelStack.PopMatrix();
				//part 4
				modelStack.PushMatrix();
				modelStack.Translate(-12.5, -2, 0);
				modelStack.Rotate(-90, 0, 0, 1);
				modelStack.Scale(2, 2, 2);
				RenderMesh(meshList[HalfCube], true);
				modelStack.PopMatrix();
				//part 5
				modelStack.PushMatrix();
				modelStack.Translate(-15, -2, 0);
				modelStack.Rotate(180, 0, 0, 1);
				modelStack.Scale(2, 2, 2);
				RenderMesh(meshList[HalfCube], true);
				modelStack.PopMatrix();
				//part 6
				modelStack.PushMatrix();
				modelStack.Translate(-13.5, -0.5, 0);
				modelStack.Scale(1, 1, 1);
				RenderMesh(meshList[Orb], true);
				modelStack.PopMatrix();
				//part 7
				modelStack.PushMatrix();
				modelStack.Translate(-17, -0.5, 0);
				modelStack.Rotate(90, 1, 0, 0);
				modelStack.Rotate(-90, 0, 0, 1);
				modelStack.Scale(2, 2, 2);
				RenderMesh(meshList[HalfCube], true);
				modelStack.PopMatrix();
				//part 8
				modelStack.PushMatrix();
				modelStack.Translate(-17, -2.5, 0);
				modelStack.Scale(2, 2, 2);
				RenderMesh(meshList[BodyBrown], true);
				modelStack.PopMatrix();
			modelStack.PopMatrix();
		modelStack.PopMatrix();
		//right arm
		modelStack.PushMatrix();
		modelStack.Translate(0.75, -0.2f, 0);
		modelStack.Scale(0.2f, 0.2f, 0.2f);
		modelStack.Rotate(45, 0, 0, 1);
		modelStack.Rotate(0, 1, 0, 0);
		RenderMesh(meshList[Arm], true);
			//Right Hand
			modelStack.PushMatrix();
			modelStack.Translate(0, -2.6f, 0);
			modelStack.Rotate(180, 0, 0, 1);
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[Torus], true);
			modelStack.PopMatrix();
		modelStack.PopMatrix();
	modelStack.PopMatrix();
	//Yellow
	modelStack.PushMatrix();
	modelStack.Translate(0, 0.65f, 0.501f+280);
	modelStack.Scale(1, 1, 1.5f);
	RenderMesh(meshList[BodyYellow], true);
	modelStack.PopMatrix();
	//Body2
	modelStack.PushMatrix();
	modelStack.Translate(0, -1.40f, 280);
	modelStack.Scale(3, 0.3f, 2.6f);
	RenderMesh(meshList[BodyBrown], true);
	modelStack.PopMatrix();
	//Silver
	modelStack.PushMatrix();
	modelStack.Translate(0, -1.401f, 0.801f+280);
	modelStack.Scale(1, 0.3f, 1.0f);
	RenderMesh(meshList[BodySilver], true);
	modelStack.PopMatrix();
	//Body 3
	modelStack.PushMatrix();
	modelStack.Translate(0, -1.70f, 280);
	modelStack.Scale(3, 0.3f, 2.6f);
	RenderMesh(meshList[BodyRed], true);
	modelStack.PopMatrix();
	//Body 4
	modelStack.PushMatrix();
	modelStack.Translate(0, -2, 280);
	modelStack.Scale(3, 0.3f, 2.6f);
	RenderMesh(meshList[BodyYellow], true);
	modelStack.PopMatrix();
	//Bottom of body connecting to legs
	modelStack.PushMatrix();
	modelStack.Translate(0, -2.24f, 280);
	modelStack.Scale(3, 0.15f, 2.6f);
	RenderMesh(meshList[BodyRed], true);
		//Left leg
		modelStack.PushMatrix();
		modelStack.Translate(-0.2f, -5, 0);
		modelStack.Rotate(0, 1, 0, 0);
		modelStack.Scale(0.15f, 4, 0.15f);
		RenderMesh(meshList[Leg], true);
		modelStack.PopMatrix();
		//Right leg
		modelStack.PushMatrix();
		modelStack.Translate(0.2f, -5, 0);
		modelStack.Rotate(0, 1, 0, 0);
		modelStack.Scale(0.15f, 4, 0.15f);
		RenderMesh(meshList[Leg], true);
		modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void Assigment2::RenderDeadTree(int x, int z,float rotate)
{
	modelStack.PushMatrix();
	modelStack.Translate(x, -5, z);
	modelStack.Rotate(rotate, 0, 0, 1);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[Deadtrees], true);
	modelStack.PopMatrix();
}

void Assigment2::RenderMesh(Mesh* mesh, bool enableLight)
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
void Assigment2::RenderText(Mesh* mesh, std::string text, Color color)
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

void Assigment2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
void Assigment2::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
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




