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
	meshList[Ground_Mesh] = MeshBuilder::GenerateQuadRepeat("Hell", 1, 1, White);
	meshList[Ground_Mesh]->textureID = LoadTGA("Assigment2Images//GroundMesh.tga");
	meshList[Ground_Mesh]->material.kAmbient.Set(0,0.20,0.13);
	//building
	meshList[GEO_BUILDING] = MeshBuilder::GenerateOBJ("Building", "OBJ//simplebuilding.obj");
	meshList[GEO_BUILDING]->textureID = LoadTGA("Assigment2Images//buildingtexture.tga");
	meshList[GEO_BUILDING]->material.kAmbient.Set(0.35, 0.35, 0.35);
	//meshList[GEO_BUILDING]->material.kAmbient.Set(0.35, 0.35, 0.35);
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
	light[1].position.Set(0, 3, 270);
	light[1].color.Set(White);
	light[1].power = 5;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(7));
	light[1].cosInner = cos(Math::DegreeToRadian(1));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, -1.f, 0.f);
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
	
	

	//Set Material locations
	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT],
		m_parameters[U_MATERIAL_DIFFUSE],
		m_parameters[U_MATERIAL_SPECULAR],
		m_parameters[U_MATERIAL_SHININESS]);
	//number of lights
	glUniform1i(m_parameters[U_NUMLIGHTS], 2);

	//ruins
	meshList[Ruins] = MeshBuilder::GenerateOBJ("Ruins", "OBJ//Ruin.obj");
	meshList[Ruins]->textureID = LoadTGA("Assigment2Images//RuinTexture.tga");
	meshList[Ruins]->material.kAmbient.Set(0.35, 0.35, 0.35);
	//vignette
	meshList[GEO_OVERLAY] = MeshBuilder::GenerateQuad2("for overlays", 40, 30, 0);
	//init update stuff
	LSPEED = 10.F;
	flashlight = true;
	Qpressed = Qreleased = false;
	Epressed = Ereleased = false;
	Fpressed = Freleased = false;
	//collidertest
	Ruincollider.setlength(42, 20, 97);
	Ruincollider.Setposition(Vector3(0, 5, -227));
	meshList[Colliderbox] = MeshBuilder::GenerateColliderBox("Box", Ruincollider.getxlength(), Ruincollider.getylength(), Ruincollider.getzlength());
	//one collider to check for now,will edit later
	camera.setchecker(Ruincollider);
	
	//Set boundary here
	camera.SetBounds(-300, 300, -300, 300);

}

void SceneSP2Main::Update(double dt)
{
	
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
			light[1].power = 5;
		}
		else
		{
			light[1].power = 0;
		}
		glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	}
	
	//fps
	fps = 1.f / dt;
	//camera
	camera.Update(dt);
	
	
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


	//skybox
	RenderSkybox();

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
	//Ruin Collider
	modelStack.PushMatrix();
	modelStack.Translate(Ruincollider.getPosition().x, Ruincollider.getPosition().y, Ruincollider.getPosition().z);
	RenderMesh(meshList[Colliderbox], false);
	modelStack.PopMatrix();


	//front
	modelStack.PushMatrix();
	modelStack.Translate(-350, 91, -400);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-200, 91, -400);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 91, -400);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(50, 91, -400);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(200, 91, -400);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(350, 91, -400);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	

	//left

	modelStack.PushMatrix();
	modelStack.Translate(-450, 91, -280);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-450, 91, -180);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-450, 91, -80);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-450, 91, 80);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-450, 91, 180);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-450, 91, 280);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	//right

	modelStack.PushMatrix();
	modelStack.Translate(450, 91, -280);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(450, 91, -180);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(450, 91, -80);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(450, 91, 80);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(450, 91, 180);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(450, 91, 280);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	
	//back

	modelStack.PushMatrix();
	modelStack.Translate(-350, 91, 400);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-200, 91, 400);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 91, 400);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 91, 400);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(350, 91, 400);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(200, 91, 400);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(100, 91, 400);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(30, 93, 80);
	RenderMesh(meshList[GEO_BUILDING], true);
	modelStack.PopMatrix();



	//UI OVERLAY
	//vision vignette
	if (flashlight)
	{
		meshList[GEO_OVERLAY]->textureID = LoadTGA("Image//VISIONON.tga"); 
	}
	else
	{
		meshList[GEO_OVERLAY]->textureID = LoadTGA("Image//VISIONOFF.tga");
	}
	RenderMeshOnScreen(meshList[GEO_OVERLAY], 40, 30, 1, 1);
	//camcorder
	meshList[GEO_OVERLAY]->textureID = LoadTGA("Image//camcorder.tga"); 
	RenderMeshOnScreen(meshList[GEO_OVERLAY], 40, 30, 1, 1);

	std::ostringstream test1;
	test1 << "camera view: " << camera.view;
	RenderTextOnScreen(meshList[GEO_TEXT], test1.str(), Color(0, 1, 0), 4, 0, 6);
	std::ostringstream test3;
	test3 << "light[1]spotdirec: " << light[1].spotDirection;
	RenderTextOnScreen(meshList[GEO_TEXT], test3.str(), Color(0, 1, 0), 4, 0, 3);
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
	modelStack.Translate(0+camera.position.x,-1.5f+camera.position.y, 0+camera.position.z);
	modelStack.Rotate(0, 0, 1, 0);
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

void SceneSP2Main::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
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




