#include "SceneSP2Room2.h"
#include "GL\glew.h"
#include <stdlib.h>
#include <time.h>
#include "shader.hpp"
#include "LoadTGA.h"
#include <sstream>

SceneSP2Room2::SceneSP2Room2()
{
	//if you see anything from here missing in init just copy and paste them 
	LSPEED = 10.F;
	flashlight = true;
	flashlight_lifetime = 90;
	inLocker = false;
	Qpressed = Qreleased = false;
	Epressed = Ereleased = false;
	Fpressed = Freleased = false;
	Apressed = Areleased = false;
	Dpressed = Dreleased = false;
	Rpressed = Rreleased = false;
	camBlinkOffSec = 0;
	camBlinkOnSec = 0;
	camBlinkOn = false;
	camBlinkOff = true;
	interact = false;
	DS_classroom = CLOSED;
	DS_lounge = CLOSED;
	DS_school = OPEN;
	fps = 60;
	/*itemImage[0] = meshList[GEO_ITEMIMAGE0];
	itemImage[1] = meshList[GEO_ITEMIMAGE1];
	itemImage[2] = meshList[GEO_ITEMIMAGE2];
	itemImage[3] = meshList[GEO_ITEMIMAGE3];
	itemImage[4] = meshList[GEO_ITEMIMAGE4];
	itemImage[5] = meshList[GEO_ITEMIMAGE5];
	itemImage[6] = meshList[GEO_ITEMIMAGE6];
	itemImage[7] = meshList[GEO_ITEMIMAGE7];*/
}

SceneSP2Room2::~SceneSP2Room2()
{
}


void SceneSP2Room2::Init()
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
	////shaders
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
	//light 0
	//light[0].type = Light::LIGHT_POINT;
	//light[0].position.Set(0, 7, 270);
	//light[0].color.Set(White);
	//light[0].power = 1;
	//light[0].kC = 1.f;
	//light[0].kL = 0.01f;
	//light[0].kQ = 0.001f;
	//light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	//light[0].cosInner = cos(Math::DegreeToRadian(30));
	//light[0].exponent = 3.f;
	//light[0].spotDirection.Set(0.f, 1.f, 0.f);
	//glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1,&light[0].color.r);
	//glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	//glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	//glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	//glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	//glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	//glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	//glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	//glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);
	////light 1
	//light[1].type = Light::LIGHT_SPOT;
	//light[1].position.Set(0, 3, 270);
	//light[1].color.Set(White);
	//light[1].power = 2; 
	//light[1].kC = 1.f;
	//light[1].kL = 0.01f;
	//light[1].kQ = 0.001f;
	//light[1].cosCutoff = cos(Math::DegreeToRadian(7));
	//light[1].cosInner = cos(Math::DegreeToRadian(1));
	//light[1].exponent = 3.f;
	//light[1].spotDirection.Set(0.f, -1.f, 0.f);
	//glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1,
	//	&light[1].color.r);
	//glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	//glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	//glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	//glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	//glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	//glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	//glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	//glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);
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

	
	//init update stuff
	LSPEED = 10.F;
	flashlight = true;
	flashlight_lifetime = 90;
	inLocker = false;
	Qpressed = Qreleased = false;
	Epressed = Ereleased = false;
	Fpressed = Freleased = false;
	Apressed = Areleased = false;
	Dpressed = Dreleased = false;
	Rpressed = Rreleased = false;
	//Jumpscare
	jumpscareTimerActive1 = false;
	jumpscareCounter1 = 0;
	jumpscareTimer1 = 0.2;
	jumpscareTimerActive2 = false;
	jumpscareTimer2 = 0.2;
	jumpscare2Counter = 0;
	jumpscare2Pass = false;
	jumpscareActive1 = false;
	jumpscareActive2 = false;

	//walls
	school_walls[0].mid.Set(470, 20, 0); 
	school_walls[1].mid.Set(470, 12.5, -57.5);
	school_walls[2].mid.Set(470, 12.5, 57.5); 
	school_walls[3].mid.Set(570, 12.5, 0); //back
	school_walls[4].mid.Set(520, 12.5, -110);
	school_walls[5].mid.Set(520, 12.5, 110);
	
	school_walls[1].lengthz = 105;
	school_walls[2].lengthz = 105;
	school_walls[4].lengthx = school_walls[5].lengthx = 100;
	school_walls[0].lengthz = 10;
	school_walls[3].lengthz = 220;

	for (int i = 1; i < 6; i++)
	{
		school_walls[i].lengthy = 25;
	}
	school_walls[0].lengthy = 10;


	lounge_walls[0].mid.Set(520, 20, -10);
	lounge_walls[1].mid.Set(492.5, 12.5, -10);
	lounge_walls[2].mid.Set(547.5, 12.5, -10);
	lounge_walls[1].lengthx = lounge_walls[2].lengthx = 45;
	lounge_walls[0].lengthx = 10;

	classroom_walls[0].mid.Set(565, 20, 10);
	classroom_walls[1].mid.Set(515, 12.5, 10);
	classroom_walls[1].lengthx = 90;
	classroom_walls[0].lengthx = 10;
	for (int i = 1; i < 3; i++)
	{
		lounge_walls[i].lengthy = 25;
	}
	classroom_walls[1].lengthy = 25;
	classroom_walls[0].lengthy = 10;
	lounge_walls[0].lengthy = 10;
	



	//doors
	school_door[0].mid.Set(470, 7.5, -2.5);
	school_door[1].mid.Set(470, 7.5, 2.5);
	lounge_door[0].mid.Set(517.5, 7.5, -10);
	lounge_door[1].mid.Set(522.5, 7.5, -10);
	classroom_door[0].mid.Set(567.5, 7.5, 10);
	classroom_door[1].mid.Set(562.5, 7.5, 10);
	school_door[0].lengthz = 5;
	school_door[1].lengthz = 5;
	lounge_door[0].lengthx = 5;
	lounge_door[1].lengthx = 5;
	classroom_door[0].lengthx = 5;
	classroom_door[1].lengthx = 5;
	for (int i = 0; i < 6; i++)
	{
		all_doors[i]->lengthy = 15;
	}
	school_door[0].rotateY = -90;
	school_door[1].rotateY = 90;
	
	//chairs/table
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			//classroom_tables[row * 5 + col].mid.Set(float(40 + row * 15), 3.f, float(-80 + (col * 15)));
			classroom_tables[row * 5 + col].mid.Set(float(550 - col * 15), 3.f, float(40 + (row * 15)));
			classroom_tables[row * 5 + col].lengthx = 5; //not sure since obj
			classroom_tables[row * 5 + col].lengthz = 5; //not sure since obj
			//lengthy unset
			//classroom_chairs[row * 5 + col].mid.Set(float(40 + row * 15 + 5), 3.f, float(-80 + (col * 15)));
			classroom_chairs[row * 5 + col].mid.Set(float(550 - col * 15 + 5), 3.f, float(40 + (row * 15)));
			classroom_chairs[row * 5 + col].lengthx = 5; //not sure since obj
			classroom_chairs[row * 5 + col].lengthz = 5; //not sure since obj
			//lengthy unset
		}
	}
	lounge_table.mid.Set(500, 2.5, -105); //y value estimated
	lounge_table.lengthz = 10; //not sure since obj
	lounge_table.lengthx = 20; //not sure since obj
	//lengthy unset

	//podium
	podium.mid.Set(480, 1, 60);
	podium.lengthx = 5;
	podium.lengthz = 5;

	//list of lockers
	Lockerlist.push_back(Locker());
	Lockerlist[0].setpos(Vector3(500, 0, 8));
	Lockerlist[0].setyaw(90);
	Lockerlist.push_back(Locker());
	Lockerlist[1].setpos(Vector3(472.1, 0.f, 50));
	Lockerlist.push_back(Locker());
	Lockerlist[2].setpos(Vector3(568, 0, -70));

	//wall colliders

	Colliderlist.push_back(ColliderBox());
	Colliderlist[0].setlength(school_walls[1].lengthx+2.5, school_walls[1].lengthy, school_walls[1].lengthz);
	Colliderlist[0].Setposition(Vector3(school_walls[1].mid.x, school_walls[1].mid.y, school_walls[1].mid.z));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[1].setlength(school_walls[2].lengthx+2.5, school_walls[2].lengthy, school_walls[2].lengthz);
	Colliderlist[1].Setposition(Vector3(school_walls[2].mid.x, school_walls[2].mid.y, school_walls[2].mid.z));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[2].setlength(school_walls[3].lengthx+2.5, school_walls[3].lengthy, school_walls[3].lengthz);
	Colliderlist[2].Setposition(Vector3(school_walls[3].mid.x, school_walls[3].mid.y, school_walls[3].mid.z));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[3].setlength(school_walls[4].lengthx, school_walls[4].lengthy, school_walls[4].lengthz+2.5);
	Colliderlist[3].Setposition(Vector3(school_walls[4].mid.x, school_walls[4].mid.y, school_walls[4].mid.z));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[4].setlength(school_walls[5].lengthx, school_walls[5].lengthy, school_walls[5].lengthz+2.5);
	Colliderlist[4].Setposition(Vector3(school_walls[5].mid.x, school_walls[5].mid.y, school_walls[5].mid.z));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[5].setlength(classroom_walls[1].lengthx,classroom_walls[1].lengthy,classroom_walls[1].lengthz+2.5);
	Colliderlist[5].Setposition(Vector3(classroom_walls[1].mid.x,classroom_walls[1].mid.y,classroom_walls[1].mid.z));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[6].setlength(lounge_walls[1].lengthx,lounge_walls[1].lengthy,lounge_walls[1].lengthz+2.5);
	Colliderlist[6].Setposition(Vector3(lounge_walls[1].mid.x,lounge_walls[1].mid.y,lounge_walls[1].mid.z));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[7].setlength(lounge_walls[2].lengthx, lounge_walls[2].lengthy, lounge_walls[2].lengthz+2.5);
	Colliderlist[7].Setposition(Vector3(lounge_walls[2].mid.x, lounge_walls[2].mid.y, lounge_walls[2].mid.z));
	//Locker colliders
	Colliderlist.push_back(ColliderBox());
	Colliderlist[8].setlength(4.3,10,3.9);
	Colliderlist[8].Setposition(Lockerlist[0].getpos());
	Colliderlist.push_back(ColliderBox());
	Colliderlist[9].setlength(3.9, 10, 4.3);
	Colliderlist[9].Setposition(Lockerlist[1].getpos());
	Colliderlist.push_back(ColliderBox());
	Colliderlist[10].setlength(3.9, 10, 4.3);
	Colliderlist[10].Setposition(Lockerlist[2].getpos());
	//Door colliders
	Colliderlist.push_back(ColliderBox());
	Colliderlist[11].setlength(school_door[0].lengthx+2.5,school_door[0].lengthy,school_door[0].lengthz);
	Colliderlist[11].Setposition(school_door[0].mid);
	Colliderlist.push_back(ColliderBox());
	Colliderlist[12].setlength(school_door[1].lengthx+2.5, school_door[1].lengthy, school_door[1].lengthz);
	Colliderlist[12].Setposition(school_door[1].mid);
	Colliderlist.push_back(ColliderBox());
	Colliderlist[13].setlength(classroom_door[0].lengthx,classroom_door[0].lengthy,classroom_door[0].lengthz+2.5);
	Colliderlist[13].Setposition(classroom_door[0].mid);
	Colliderlist.push_back(ColliderBox());
	Colliderlist[14].setlength(classroom_door[1].lengthx, classroom_door[1].lengthy, classroom_door[1].lengthz+2.5);
	Colliderlist[14].Setposition(classroom_door[1].mid);
	Colliderlist.push_back(ColliderBox());
	Colliderlist[15].setlength(lounge_door[0].lengthx,lounge_door[0].lengthy,lounge_door[0].lengthz+2.5);
	Colliderlist[15].Setposition(lounge_door[0].mid);
	Colliderlist.push_back(ColliderBox());
	Colliderlist[16].setlength(lounge_door[1].lengthx, lounge_door[1].lengthy, lounge_door[1].lengthz+2.5);
	Colliderlist[16].Setposition(lounge_door[1].mid);
	//chair colliders
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			Colliderlist.push_back(ColliderBox());
			Colliderlist[(row * 5 + col) + 17].setlength(classroom_chairs[row * 5 + col].lengthx, classroom_chairs[row * 5 + col].lengthy,
				classroom_chairs[row * 5 + col].lengthz);
			Colliderlist[(row * 5 + col) + 17].Setposition(classroom_chairs[row * 5 + col].mid);
		}
	}
	//table colliders
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			Colliderlist.push_back(ColliderBox());
			Colliderlist[(row * 5 + col) + 37].setlength(classroom_tables[row * 5 + col].lengthx, classroom_tables[row * 5 + col].lengthy,
				classroom_tables[row * 5 + col].lengthz);
			Colliderlist[(row * 5 + col) + 37].Setposition(classroom_tables[row * 5 + col].mid);
		}
	}
	//colliderbox for checking any collider(just one)
	//@collider
	meshList[Colliderbox] = MeshBuilder::GenerateColliderBox("Box", Colliderlist[7].getxlength(), Colliderlist[7].getylength(), Colliderlist[7].getzlength());

	//terrain
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad2("floor/ceiling", 1, 1, White);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//schoolfloor.tga");//this one was in render cousing memory leak
	meshList[GEO_WALL1] = MeshBuilder::GenerateCubeT("walls", 1, 1, 1, 0, 0, 1, 1, Color(1.f, 0.1f, 0.1f));
	meshList[GEO_WALL1]->textureID = LoadTGA("Image//schoolwall.tga");/////////////////////////////////////////////////////////
	meshList[GEO_WALL2] = MeshBuilder::GenerateCubeT("walls", 1, 1, 1, 0, 0, 1, 1, Color(1.f, 0.1f, 0.1f));
	meshList[GEO_WALL2]->textureID = LoadTGA("Image//schoolwall.tga");
	meshList[GEO_WALL3] = MeshBuilder::GenerateCubeT("walls", 1, 1, 1, 0, 0, 1, 1, Color(1.f, 0.1f, 0.1f));
	meshList[GEO_WALL3]->textureID = LoadTGA("Image//schoolwall.tga");
	meshList[GEO_TOPHALFWALL] = MeshBuilder::GenerateCubeT("walls", 1, 1, 1, 0, 0, 1.f/22.f, 10.f/25.f, Color(1.f, 0.1f, 0.1f));
	meshList[GEO_TOPHALFWALL]->textureID = LoadTGA("Image//schoolwall.tga");
	meshList[GEO_LEFTDOOR] = MeshBuilder::GenerateCubeT("door", 1, 1, 1, 0, 0, 1, 1, White);
	meshList[GEO_LEFTDOOR]->textureID = LoadTGA("Image//schooldoorleft.tga");
	meshList[GEO_RIGHTDOOR] = MeshBuilder::GenerateCubeT("door", 1, 1, 1, 0, 0, 1, 1, White);
	meshList[GEO_RIGHTDOOR]->textureID = LoadTGA("Image//schooldoorright.tga");
	meshList[GEO_CHAIR] = MeshBuilder::GenerateOBJ("chair", "OBJ//schoolChair.obj");
	meshList[GEO_CHAIR]->textureID = LoadTGA("Image//greywood.tga");
	meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("table", "OBJ//Table.obj");
	meshList[GEO_TABLE]->textureID = LoadTGA("Image//greywood.tga");
	meshList[GEO_LONGTABLE] = MeshBuilder::GenerateOBJ("table", "OBJ//LongTable.obj");
	meshList[GEO_LONGTABLE]->textureID = LoadTGA("Image//darkwood.tga");
	meshList[GEO_PODIUM] = MeshBuilder::GenerateOBJ("podium", "OBJ//Podium.obj");
	meshList[GEO_PODIUM]->textureID = LoadTGA("Image//greywood.tga");
	meshList[GEO_PIGEONHOLE] = MeshBuilder::GenerateOBJ("podium", "OBJ//PigeonHole.obj");
	meshList[GEO_PIGEONHOLE]->textureID = LoadTGA("Image//greywood.tga");
	//ghost
	meshList[GEO_SKULL] = MeshBuilder::GenerateOBJ("skull", "OBJ//Skull.obj");
	meshList[GEO_SKULL]->material.kAmbient.Set(Gray);
	meshList[GEO_MYSTERIOUSMAN] = MeshBuilder::GenerateOBJ("man npc", "OBJ//man1.obj");
	meshList[GEO_MYSTERIOUSMAN]->textureID = LoadTGA("Image//man1.tga");
	meshList[GEO_MYSTERIOUSMAN]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

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
	meshList[GEO_OVERLAY]->textureID = LoadTGA("Image//VISIONON.tga");
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


	//Locker mesh
	meshList[locker] = MeshBuilder::GenerateOBJ("Locker", "OBJ//locker.obj");
	meshList[locker]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[locker]->textureID = LoadTGA("Assigment2Images//locker.tga");
	//list of colliders
	camera.setchecker(Colliderlist);
	
	//Set boundary here
	camera.SetBounds(-415, 1500, -365, 360);
	//camblink
	camBlinkOffSec = 0;
	camBlinkOnSec = 0;
	camBlinkOn = false;
	camBlinkOff = true;
	//door state
	DS_classroom =CLOSED;
	DS_lounge = CLOSED;
	DS_school = OPEN;
	//trap mesh
	meshList[GEO_BEARTRAP] = MeshBuilder::GenerateOBJ("Beartrap", "OBJ//BearTrap.obj");
	meshList[GEO_BEARTRAP]->textureID = LoadTGA("Assigment2Images//BearTrap.tga");
	meshList[GEO_BEARTRAP]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	//trap list
	traplist.push_back(trap(trap::beartrap, Vector3(480, 0, -57)));
	traplist.push_back(trap(trap::beartrap, Vector3(525, 0, 100)));
	traplist.push_back(trap(trap::beartrap, Vector3(510, 0, -15)));
	traplist.push_back(trap(trap::beartrap, Vector3(540, 0, 5)));
	
}

void SceneSP2Room2::Set(Scene* scene)
{
	inventory = scene->inventory;
	ghost = scene->ghost;
	flashlight = scene->flashlight;
	flashlight_lifetime = scene->flashlight_lifetime;
	DS_school = OPEN;
	school_door[0].rotateY = -90;
	school_door[1].rotateY = 90;

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

	camera.position.Set(475, 9, 0);
	camera.rawTarget = camera.position;
}

void SceneSP2Room2::SetBackground()
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

void SceneSP2Room2::Update(double dt)
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
	if (ghost->kill == false && ghost->state == Ghost::DEATH) {
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

	if (nearExit == true && Fpressed == true)
	{
		exitSchool = true;
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



	/*if (campos_x < 480 && campos_z > -4 && campos_z < 4)
	{
		nearExit = true;
	}
	else {
		nearExit = false;
		showChatbox = false;
	}

	if (exitSchool == true && nearExit == true)
	{
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_Main);
		exitSchool = false;
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
	
	//camera dot blink logic (not the best, but works)
	if (camBlinkOff && camBlinkOffSec >= 0.5)
	{
		camBlinkOn = true;
		camBlinkOff = false;
		camBlinkOffSec = 0;
		meshList[GEO_OVERLAY2]->textureID = LoadTGA("Image//camcorder.tga");
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
		meshList[GEO_OVERLAY2]->textureID = LoadTGA("Image//camcorder2.tga");
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
	ghost->UpdateState(camera.position, inLocker, dt);



	//INTERACTION CHECKS
	interact = false;
	Vector3 origin(470, 5, 0);
	//doors
	switch (DS_school)
	{
	case OPEN:
		//doors close on their own
		if ((camera.position - origin).Length() >= 20)
		{
			DS_school = CLOSING;
		}
		if (camera.position.z <= 5 && camera.position.z >= -5 && camera.position.x <= 480 && camera.position.x >= 471)
		{
			interact = true;
			interact_message = "Exit School";
			if (Fpressed)
			{
				Fpressed = false;
				Background->setSoundVolume(0.f);
				Effect->setSoundVolume(0.f);
				Jumpscare->setSoundVolume(0.f);
				Application::setscene(Scene_Main);
			}
		}
		break;
	case CLOSED:
		if (camera.position.z <= 5 && camera.position.z >= -5 && camera.position.x >= 471 && camera.position.x <= 480)
		{
			interact = true;
			interact_message = "Exit School";
			if (Fpressed)
			{
				Fpressed = false;
				DS_school = OPENING;
			}
		}
		break;
	case OPENING:
		school_door[0].rotateY -= float(20 * dt);
		school_door[1].rotateY += float(20 * dt);
		if (school_door[1].rotateY >= 90)
		{
			Background->setSoundVolume(0.f);
			Effect->setSoundVolume(0.f);
			Jumpscare->setSoundVolume(0.f);
			Application::setscene(Scene_Main);
		}
		break;
	case CLOSING:
		school_door[0].rotateY += 20 * float(dt);
		school_door[1].rotateY -= 20 * float(dt);
		if (school_door[1].rotateY <= 0)
		{
			DS_school = CLOSED;
		}
		break;
	}

	origin.Set(565, 5, 10);
	switch (DS_classroom)
	{
	case OPEN:
		//doors close on their own
		if ((camera.position - origin).Length() >= 20)
		{
			DS_classroom = CLOSING;
			Colliderlist[13].setactive(true);
			Colliderlist[14].setactive(true);
			camera.setchecker(Colliderlist);
		}
		if (camera.position.z <= 15 && camera.position.z >= 5 && camera.position.x >= 560 && camera.position.x <= 570)
		{
			interact = true;
			interact_message = "Close Door";
			if (Fpressed)
			{
				Fpressed = false;
				DS_classroom = CLOSING;
				Colliderlist[13].setactive(true);
				Colliderlist[14].setactive(true);
				camera.setchecker(Colliderlist);

				
			}
		}
		break;
	case CLOSED:
		if (camera.position.z <= 15 && camera.position.z >= 5 && camera.position.x >= 560 && camera.position.x <= 570)
		{
			interact = true;
			interact_message = "Open Door";
			if (Fpressed)
			{
				Fpressed = false;
				DS_classroom = OPENING;
				Colliderlist[13].setactive(false);
				Colliderlist[14].setactive(false);
				camera.setchecker(Colliderlist);
				
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

	origin.Set(520, 5, -10);
	switch (DS_lounge)
	{
	case OPEN:
		//doors close on their own
		if ((camera.position - origin).Length() >= 20)
		{
			DS_lounge = CLOSING;
			Colliderlist[15].setactive(true);
			Colliderlist[16].setactive(true);
			camera.setchecker(Colliderlist);
		}
		if (camera.position.z <= 5 && camera.position.z >= -10 && camera.position.x >= 515 && camera.position.x <= 525)
		{
			interact = true;
			interact_message = "Close Door";
			if (Fpressed)
			{
				Fpressed = false;
				DS_lounge = CLOSING;
				Colliderlist[15].setactive(true);
				Colliderlist[16].setactive(true);
				camera.setchecker(Colliderlist);
			}
		}
		break;
	case CLOSED:
		if (camera.position.z <= 5 && camera.position.z >= -20 && camera.position.x >= 515 && camera.position.x <= 525)
		{
			interact = true;
			interact_message = "Open Door";
			if (Fpressed)
			{
				Fpressed = false;
				DS_lounge = OPENING;
				Colliderlist[15].setactive(false);
				Colliderlist[16].setactive(false);
				camera.setchecker(Colliderlist);
			}
		}
		break;
	case OPENING:
		lounge_door[0].rotateY += float(20 * dt);
		lounge_door[1].rotateY -= float(20 * dt);
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
		if (Lockerlist[i].status(camera.position, -1*camera.view, Fpressed)) {
			if (Lockerlist[i].gethidden() == false) {
				Lockerlist[i].Sethidden(true);
				temp.Set(camera.position.x, camera.position.y, camera.position.z);
				camera.teleport(Lockerlist[i].getpos());
				glDisable(GL_CULL_FACE);//To see the inside of the locker
				inLocker = true;
			}
		}
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

	//Jumpscares ((Might add on that you press the button to open the door before this activates))
	if ((camera.position.y >= 0) && ((camera.position.x >= 510) && (camera.position.x <= 520)) && ((camera.position.z >= -10) && (camera.position.z <= -5)) && (jumpscareCounter1 == 0) && (jumpscareTimer1 != 0))
	{
		jumpscareActive1 = true;
		Jumpscare->play2D("Sound\\Jumpscares\\Horror_Sound_Effects_For_Youtubers_-_No_Copyrighted_SFX_For_Video_Editing (mp3cut.net).wav", false);
	}
	if (jumpscareActive1 == true)
	{
		jumpscareTimerActive1 = true;
	}
	if (jumpscareTimerActive1 == true)
	{
		jumpscareTimer1 -= dt;
	}
	if (jumpscareTimer1 <= 0)
	{
		jumpscareActive1 = false;
		jumpscareCounter1 = 1;
	}

	//Jumpscare 2
	if ((camera.position.y >= 0) && ((camera.position.x >= 560) && (camera.position.x <= 570)) && ((camera.position.z >= 10) && (camera.position.z <= 15)) && (jumpscare2Counter == 0))
	{
		jumpscare2Pass = true;
		Jumpscare->play2D("Sound\\Jumpscares\\Horror_Sound_Effects_For_Youtubers_-_No_Copyrighted_SFX_For_Video_Editing (mp3cut.net).wav", false);
	}
	else
	{
		jumpscare2Pass = false;
	}
	if (jumpscare2Pass == true)
	{
		jumpscare2Counter = 1;
	}
	if ((camera.position.y >= 0) && ((camera.position.x >= 11) && (camera.position.x <= 18)) && ((camera.position.z >= -100) && (camera.position.z <= -90)) && (jumpscare2Counter == 1) && (jumpscare2Pass == false) && (jumpscareTimer2 != 0))
	{
		jumpscareActive1 = true;
	}
	if (jumpscareActive2 == true)
	{
		jumpscareTimerActive2 = true;
	}
	if (jumpscareTimerActive2 == true)
	{
		jumpscareTimer2 -= dt;
	}
	if (jumpscareTimer2 <= 0)
	{
		jumpscareActive2 = false;
		jumpscare2Counter = 2;
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

void SceneSP2Room2::PauseUpdate()
{
	Application::hidemousecursor(false);
}

void SceneSP2Room2::Render()
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
	modelStack.Translate(Colliderlist[7].getPosition().x, Colliderlist[7].getPosition().y, Colliderlist[7].getPosition().z);
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
	//lockers
	for (int i = 0; i < signed(Lockerlist.size()); i++) {
		modelStack.PushMatrix();
		modelStack.Translate(Lockerlist[i].getpos().x, Lockerlist[i].getpos().y, Lockerlist[i].getpos().z);
		modelStack.Rotate(Lockerlist[i].getyaw(), 0, 1, 0);
		modelStack.Scale(0.2f, 0.2f, 0.2f);
		RenderMesh(meshList[locker], true);
		modelStack.PopMatrix();
	}
	//all walls
	for (int i = 0; i < 3; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(all_walls[i]->mid.x, all_walls[i]->mid.y, all_walls[i]->mid.z);
		modelStack.Scale(all_walls[i]->lengthx, all_walls[i]->lengthy, all_walls[i]->lengthz);
		RenderMesh(meshList[GEO_TOPHALFWALL], true);
		modelStack.PopMatrix();
	}
	for (int i = 3; i < 8; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(all_walls[i]->mid.x, all_walls[i]->mid.y, all_walls[i]->mid.z);
		modelStack.Scale(all_walls[i]->lengthx, all_walls[i]->lengthy, all_walls[i]->lengthz);
		RenderMesh(meshList[GEO_WALL2], true);
		modelStack.PopMatrix();
	}
	for (int i = 8; i < 10; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(all_walls[i]->mid.x, all_walls[i]->mid.y, all_walls[i]->mid.z);
		modelStack.Scale(all_walls[i]->lengthx, all_walls[i]->lengthy, all_walls[i]->lengthz);
		RenderMesh(meshList[GEO_WALL3], true);
		modelStack.PopMatrix();
	}
	modelStack.PushMatrix();
	modelStack.Translate(all_walls[10]->mid.x, all_walls[10]->mid.y, all_walls[10]->mid.z);
	modelStack.Scale(all_walls[10]->lengthx, all_walls[10]->lengthy, all_walls[10]->lengthz);
	RenderMesh(meshList[GEO_WALL1], true);
	modelStack.PopMatrix();
	//tables and chairs in classroom
	for (int i = 0; i < 20; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(classroom_tables[i].mid.x, classroom_tables[i].mid.y, classroom_tables[i].mid.z);
		modelStack.Rotate(-90, 1, 0, 0);
		modelStack.Scale(0.025f, 0.025f, 0.05f);
		RenderMesh(meshList[GEO_TABLE], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(classroom_chairs[i].mid.x, classroom_chairs[i].mid.y, classroom_chairs[i].mid.z);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Rotate(-90, 1, 0, 0);
		modelStack.Scale(0.05f, 0.05f, 0.05f);
		RenderMesh(meshList[GEO_CHAIR], true);
		modelStack.PopMatrix();
	}

	//all doors
	//schoolleft
	modelStack.PushMatrix();
	modelStack.Translate(school_door[0].mid.x, school_door[0].mid.y, school_door[0].mid.z);
	modelStack.Translate(0.25, 0, -2.5);
	modelStack.Rotate(school_door[0].rotateY, 0, 1, 0);
	modelStack.Translate(-0.25, 0, 2.5);
	modelStack.Scale(school_door[0].lengthx, school_door[0].lengthy, school_door[0].lengthz);
	RenderMesh(meshList[GEO_LEFTDOOR], true);
	modelStack.PopMatrix();
	//school right
	modelStack.PushMatrix();
	modelStack.Translate(school_door[1].mid.x, school_door[1].mid.y, school_door[1].mid.z);
	modelStack.Translate(0.25, 0, 2.5);
	modelStack.Rotate(school_door[1].rotateY, 0, 1, 0);
	modelStack.Translate(-0.25, 0, -2.5);
	modelStack.Scale(school_door[1].lengthx, school_door[1].lengthy, school_door[1].lengthz);
	RenderMesh(meshList[GEO_RIGHTDOOR], true);
	modelStack.PopMatrix();
	//loungeright
	modelStack.PushMatrix();
	modelStack.Translate(lounge_door[1].mid.x, lounge_door[1].mid.y, lounge_door[1].mid.z);
	modelStack.Translate(2.5, 0, 0.25);
	modelStack.Rotate(lounge_door[1].rotateY, 0, 1, 0);
	modelStack.Translate(-2.5, 0, -0.25);
	modelStack.Scale(lounge_door[1].lengthx, lounge_door[1].lengthy, lounge_door[1].lengthz);
	RenderMesh(meshList[GEO_RIGHTDOOR], true);
	modelStack.PopMatrix();
	//classroomleft
	modelStack.PushMatrix();
	modelStack.Translate(classroom_door[0].mid.x, classroom_door[0].mid.y, classroom_door[0].mid.z);
	modelStack.Translate(2.5, 0, 0.25);
	modelStack.Rotate(classroom_door[0].rotateY, 0, 1, 0);
	modelStack.Translate(-2.5, 0, -0.25);
	modelStack.Scale(classroom_door[0].lengthx, classroom_door[0].lengthy, classroom_door[0].lengthz);
	RenderMesh(meshList[GEO_LEFTDOOR], true);
	modelStack.PopMatrix();
	//classroom right
	modelStack.PushMatrix();
	modelStack.Translate(classroom_door[1].mid.x, classroom_door[1].mid.y, classroom_door[1].mid.z);
	modelStack.Translate(-2.5, 0, 0.25);
	modelStack.Rotate(classroom_door[1].rotateY, 0, 1, 0);
	modelStack.Translate(2.5, 0, -0.25);
	modelStack.Scale(classroom_door[1].lengthx, classroom_door[1].lengthy, classroom_door[1].lengthz);
	RenderMesh(meshList[GEO_RIGHTDOOR], true);
	modelStack.PopMatrix();
	//lounge left
	modelStack.PushMatrix();
	modelStack.Translate(lounge_door[0].mid.x, lounge_door[0].mid.y, lounge_door[0].mid.z);
	modelStack.Translate(-2.5, 0, 0.25);
	modelStack.Rotate(lounge_door[0].rotateY, 0, 1, 0);
	modelStack.Translate(2.5, 0, -0.25);
	modelStack.Scale(lounge_door[1].lengthx, lounge_door[1].lengthy, lounge_door[1].lengthz);
	RenderMesh(meshList[GEO_LEFTDOOR], true);
	modelStack.PopMatrix();
	//school floor
	modelStack.PushMatrix();
	modelStack.Translate(520, 0, 0);
	modelStack.Scale(100, 1, 220);
	modelStack.Rotate(-90, 1, 0, 0);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();
	//school ceiling
	modelStack.PushMatrix();
	modelStack.Translate(520, 25, 0);
	modelStack.Scale(100, 1, 220);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();
	//longtable in faculty lounge
	modelStack.PushMatrix();
	modelStack.Translate(lounge_table.mid.x, 0, lounge_table.mid.z);
	modelStack.Scale(0.1f, 0.1f, 0.1f);
	modelStack.Rotate(-90, 1, 0, 0);
	RenderMesh(meshList[GEO_LONGTABLE], true);
	modelStack.PopMatrix();
	//podium
	modelStack.PushMatrix();
	modelStack.Translate(podium.mid.x - 3, podium.mid.y, podium.mid.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(0.1, 0.1, 0.1);
	RenderMesh(meshList[GEO_PODIUM], true);
	modelStack.PopMatrix();
	//pigeon hole in lounge
	modelStack.PushMatrix();
	modelStack.Translate(560, 10, -60); // pos on map
	modelStack.Translate(100, 0, 0); //move to origin
	modelStack.Scale(0.4, 0.4, 0.4);
	RenderMesh(meshList[GEO_PIGEONHOLE], true);
	modelStack.PopMatrix();
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
		RenderTextOnScreen(meshList[GEO_TEXT], "Press F to go outside?", Color(0.f, 0.f, 1.f), 4.f, 10.f, 1.8f);
	}
	//UI OVERLAY

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
	if (inLocker == true)
	{
		//RenderMeshOnScreen(meshList[GEO_BAR], 14, 50, suffocationScale, 1);
	}
	//stamina icon
	RenderMeshOnScreen(meshList[GEO_STAMINA], 6, 52, 2, 2);
	//battery bar
	RenderMeshOnScreen(meshList[GEO_BATTERY], 4.5f + (4.5f - flashlight_lifetime * 0.025f), 6.4f, flashlight_lifetime * 0.05f, 2);
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
	std::ostringstream test1;
	test1 << "camera facing: " << camera.view;
	RenderTextOnScreen(meshList[GEO_TEXT], test1.str(), Color(0, 1, 0), 4, 0, 6);
	std::ostringstream test3;
	test3 << "ghost distance: " << ghost->distance;
	RenderTextOnScreen(meshList[GEO_TEXT], test3.str(), Color(0, 1, 0), 4, 0, 3);
	std::ostringstream test2;
	test2 << "ghost stat: " << ghost->state;
	RenderTextOnScreen(meshList[GEO_TEXT], test2.str(), Color(0, 1, 0), 4, 0, 9);
	////checking
	//std::cout << camera.position.x << std::endl;
	//std::cout << camera.position.z << std::endl;

	if (jumpscareActive1 == true)
	{
		RenderMeshOnScreen(meshList[GEO_JUMPSCARE1], 40, 30, 100, 100);
	}

	if (jumpscareActive2 == true)
	{
		RenderMeshOnScreen(meshList[GEO_JUMPSCARE1], 40, 30, 100, 100);
	}


	RenderTextOnScreen(meshList[GEO_TEXT], "X:" + std::to_string(camera.position.x), Color(0, 1, 0), 3, 35, 5);
	RenderTextOnScreen(meshList[GEO_TEXT], "Y:" + std::to_string(camera.position.y), Color(0, 1, 0), 3, 35, 4);
	RenderTextOnScreen(meshList[GEO_TEXT], "Z:" + std::to_string(camera.position.z), Color(0, 1, 0), 3, 35, 3);
}

void SceneSP2Room2::Exit()
{
	delete ghost;
	delete inventory;
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneSP2Room2::RenderSkybox()
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

void SceneSP2Room2::UseItem(int itemname)
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
			inventory->items[inventory->selected] = nullptr;
		}
		
		//else warning message?
		break;
	case Item::ITEM2:
		break;
	}
}

bool SceneSP2Room2::PickUpItem(Item* item)
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


void SceneSP2Room2::RenderMesh(Mesh* mesh, bool enableLight)
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

void SceneSP2Room2::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneSP2Room2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SceneSP2Room2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, int limit)
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

void SceneSP2Room2::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey)
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


