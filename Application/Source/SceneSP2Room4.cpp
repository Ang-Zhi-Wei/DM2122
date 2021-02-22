#include "SceneSP2Room4.h"
#include "GL\glew.h"
#include <stdlib.h>
#include <time.h>
#include "shader.hpp"
#include "LoadTGA.h"
#include <sstream>

SceneSP2Room4::SceneSP2Room4()
{
	//if you see anything from here missing in init just copy and paste them 
	LSPEED = 10.F;
	interact = false;
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
	fps = 60;
	DS_classroom = CLOSED;
	DS_lounge = CLOSED;
	DS_school = OPEN;
	camBlinkOn = false;
	camBlinkOff = true;
}

SceneSP2Room4::~SceneSP2Room4()
{
}


void SceneSP2Room4::Init()
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



	//meshList[workbench] = MeshBuilder::GenerateOBJ("Building", "OBJ//Workbench.obj");
	////meshList[workbench]->textureID = LoadTGA("Assigment2Images//barreltexture.tga");
	//meshList[workbench]->material.kAmbient.Set(0.35, 0.35, 0.35);
	meshList[GEO_SKULL] = MeshBuilder::GenerateOBJ("skull", "OBJ//Skull.obj");
	meshList[GEO_SKULL]->material.kAmbient.Set(Gray);
	//Mysterious man
	meshList[GEO_MYSTERIOUSMAN] = MeshBuilder::GenerateOBJ("man npc", "OBJ//man1.obj");
	meshList[GEO_MYSTERIOUSMAN]->textureID = LoadTGA("Image//man1.tga");
	meshList[GEO_MYSTERIOUSMAN]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);


	//hospital scene items
	meshList[metalcabinet] = MeshBuilder::GenerateOBJ("Building", "OBJ//metalcabinet.obj");
	meshList[metalcabinet]->textureID = LoadTGA("Assigment2Images//cabinettexture.tga");
	meshList[metalcabinet]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[bedscreen] = MeshBuilder::GenerateOBJ("Building", "OBJ//bed_screen.obj");
	meshList[bedscreen]->textureID = LoadTGA("Image//bed-screen-blood2.tga");
	meshList[bedscreen]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[bedscreenZ] = MeshBuilder::GenerateOBJ("Building", "OBJ//bed_screen_Z.obj");
	meshList[bedscreenZ]->textureID = LoadTGA("Image//bed-screen-blood2.tga");
	meshList[bedscreenZ]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[bedscreenL] = MeshBuilder::GenerateOBJ("Building", "OBJ//bed_screen_L.obj");
	meshList[bedscreenL]->textureID = LoadTGA("Image//bed-screen-blood2.tga");
	meshList[bedscreenL]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[bedframe] = MeshBuilder::GenerateOBJ("Building", "OBJ//bed_frame.obj");
	meshList[bedframe]->textureID = LoadTGA("Assigment2Images//garage.tga");
	meshList[bedframe]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[matress] = MeshBuilder::GenerateOBJ("Building", "OBJ//bed_mattress.obj");
	meshList[matress]->textureID = LoadTGA("Image//mattrees3-blood.tga");
	meshList[matress]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[beddrawer] = MeshBuilder::GenerateOBJ("Building", "OBJ//bedside_cabinet.obj");
	meshList[beddrawer]->textureID = LoadTGA("Image//bedcab.tga");
	meshList[beddrawer]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[xtable] = MeshBuilder::GenerateOBJ("Building", "OBJ//exam_bed.obj");
	meshList[xtable]->textureID = LoadTGA("Image//Ex-Bed-1-blood_i.tga");
	meshList[xtable]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[corpse] = MeshBuilder::GenerateOBJ("body", "OBJ//corpse.obj");
	meshList[corpse]->textureID = LoadTGA("Image/corpse.tga");
	meshList[corpse]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[bedtable] = MeshBuilder::GenerateOBJ("Building", "OBJ//bed_table.obj");
	meshList[bedtable]->textureID = LoadTGA("Image//bed-table-blood.tga");
	meshList[bedtable]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[stand] = MeshBuilder::GenerateOBJ("Building", "OBJ//stand.obj");
	meshList[stand]->textureID = LoadTGA("Assigment2Images//garage.tga");
	meshList[stand]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[heartmon] = MeshBuilder::GenerateOBJ("Building", "OBJ//heartmon.obj");
	meshList[heartmon]->textureID = LoadTGA("Image//hartmon-blood.tga");
	meshList[heartmon]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[Hdoors] = MeshBuilder::GenerateCubeT("door", 1, 1, 1, 0, 1, White);
	meshList[Hdoors]->textureID = LoadTGA("Image//hospital_door_full.tga");
	meshList[Hdoors]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	/*meshList[garagedoor] = MeshBuilder::GenerateOBJ("Building", "OBJ//door.obj");*/
	//meshList[metalcabinet]->textureID = LoadTGA("Assigment2Images//cabinettexture.tga");
	//meshList[garagedoor]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	//meshList[rolldoor] = MeshBuilder::GenerateOBJ("Building", "OBJ//RollDoor.obj");
	////meshList[rolldoor]->textureID = LoadTGA("Assigment2Images//barreltexture.tga");
	//meshList[rolldoor]->material.kAmbient.Set(0.35, 0.35, 0.35);
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
	light[1].power = 2; 
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
	glUniform1i(m_parameters[U_NUMLIGHTS], 2);

	
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
	//wall colliders
	//@collider
	Colliderlist.push_back(ColliderBox());
	Colliderlist[0].setlength(3, 25, 100);
	Colliderlist[0].Setposition(Vector3(30, 12, -50));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[1].setlength(3, 25, 100);
	Colliderlist[1].Setposition(Vector3(-30, 12, -50));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[2].setlength(100, 25, 3);
	Colliderlist[2].Setposition(Vector3(0, 12, -100));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[3].setlength(20, 30, 3);
	Colliderlist[3].Setposition(Vector3(-25, 12, 2));
	Colliderlist.push_back(ColliderBox());
	Colliderlist[4].setlength(20, 30, 3);
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
	Colliderlist[12].setlength(3.9, 10, 4.3);
	Colliderlist[12].Setposition(Vector3(Lockerlist[0].getpos()));
	//colliderbox for checking any collider(just one)
	meshList[Colliderbox] = MeshBuilder::GenerateColliderBox("Box", Colliderlist[12].getxlength(), Colliderlist[12].getylength(), Colliderlist[12].getzlength());

	//terrain
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad2("floor/ceiling", 1, 1, White);
	meshList[GEO_QUAD]->textureID = LoadTGA("Assigment2Images//garage.tga");//this one was in render cousing memory leak
	meshList[GEO_WALL] = MeshBuilder::GenerateCubeT("walls", 1, 1, 1, 0, 1, Color(1.f, 0.1f, 0.1f));
	meshList[GEO_WALL]->textureID = LoadTGA("Assigment2Images//garage.tga");
	meshList[GEO_FLOOR] = MeshBuilder::GenerateCubeT("walls", 1, 1, 1, 0, 1, Color(1.f, 0.1f, 0.1f));
	meshList[GEO_FLOOR]->textureID = LoadTGA("Image//floor-green-scrach.tga");
	meshList[GEO_LEFTDOOR] = MeshBuilder::GenerateCubeT("door", 1, 1, 1, 0, 1, White);
	meshList[GEO_LEFTDOOR]->textureID = LoadTGA("Image//schooldoorleft.tga");
	meshList[GEO_RIGHTDOOR] = MeshBuilder::GenerateCubeT("door", 1, 1, 1, 0, 1, White);
	meshList[GEO_RIGHTDOOR]->textureID = LoadTGA("Image//schooldoorright.tga");
	
	//UI
	meshList[GEO_OVERLAY] = MeshBuilder::GenerateQuad2("for overlays", 80, 60, 0);
	meshList[GEO_OVERLAY2] = MeshBuilder::GenerateQuad2("Camcorder", 80, 60, 0);
	meshList[GEO_BAR] = MeshBuilder::GenerateQuad2("UI usage", 1, 1, White);
	meshList[GEO_OVERLAY]->textureID = LoadTGA("Image//VISIONON.tga");
	meshList[GEO_OVERLAY2]->textureID = LoadTGA("Image//camcorder.tga");
	//Locker mesh
	meshList[locker] = MeshBuilder::GenerateOBJ("Locker", "OBJ//locker.obj");
	meshList[locker]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[locker]->textureID = LoadTGA("Assigment2Images//locker.tga");

	//list of colliders
	//camera.setchecker(Colliderlist);
	
	//Set boundary here
	camera.SetBounds(-415, 415, -365, 360);
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

void SceneSP2Room4::Set(Scene* scene)
{
	inventory = scene->inventory;
	ghost = scene->ghost;
	flashlight = scene->flashlight;
	flashlight_lifetime = scene->flashlight_lifetime;

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

void SceneSP2Room4::SetBackground()
{
	
}



void SceneSP2Room4::Update(double dt)
{
	//mouse cursor show/hide
	//Application::hidemousecursor(true);
	//switch scenes button for now
	if (Application::IsKeyPressed('5')) {
		Application::setscene(Scene_Menu);
	}
	if (Application::IsKeyPressed('6')) {
		Application::setscene(Scene_Main);
	}
	if (Application::IsKeyPressed('7')) {
		Application::setscene(Scene_1);
	}
	if (Application::IsKeyPressed('8')) {
		Application::setscene(Scene_2);
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
	//fps
	fps = 1.f / float(dt);
	//camera
	camera.Update(dt);
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

	//INTERACTION CHECKS
	interact = false;
	Vector3 origin(0, 5, 0);
	//doors
	switch (DS_school)
	{
	case OPEN:
		//doors close on their own
		if ((camera.position - origin).Length() >= 20)
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
		}
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

		ghost->facing = (camera.position - ghost->pos).Normalized();
		ghost->facing.y = 0;
		ghost->distance = (camera.position - ghost->pos).Length();
		ghost->UpdateMovement(dt);

		if (ghost->distance <= 50)
		{
			ghost->state = Ghost::CHASING;
			ghost->speed = 25;
		}
		break;
	case Ghost::CHASING:
		ghost->facing = (camera.position - ghost->pos).Normalized();
		ghost->distance = (camera.position - ghost->pos).Length();
		ghost->UpdateMovement(dt);
		if (ghost->distance <= 3 && inLocker)
		{
			ghost->state = Ghost::WAITING;
			ghost->waitTime = 3;
		}
		else if (ghost->distance <= 1)
		{
			//TBC
			//end game condition met, either that or HP - 1
		}
		break;
	case Ghost::WAITING:
		ghost->waitTime -= float(dt);
		if (ghost->waitTime <= 0)
		{
			ghost->state = Ghost::SPEEDRUN;
			ghost->speed = 50;
		}
		break;
	case Ghost::SPEEDRUN:
		ghost->facing = (ghost->pos - camera.position).Normalized();
		ghost->facing.y = 0;
		ghost->distance = (camera.position - ghost->pos).Length();
		ghost->UpdateMovement(dt);
		if (ghost->distance > 500 || !inLocker)
		{
			ghost->state = Ghost::NORMAL;
			ghost->speed = 5;
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
}

void SceneSP2Room4::PauseUpdate()
{
	Application::hidemousecursor(false);
}

void SceneSP2Room4::RenderLeftRoom()
{
	//bed row (right)
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(1, 1, 1);
		modelStack.PushMatrix();
		modelStack.Translate(23, 0, -5);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
			modelStack.PushMatrix();
			modelStack.Translate(0, 1.7, 0);
			modelStack.Scale(0.1, 0.1, 0.1);
			RenderMesh(meshList[matress], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(0, 1, 0);
			modelStack.Scale(0.165, 0.165, 0.165);
			RenderMesh(meshList[bedframe], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(-0.3, 3, 0);
			modelStack.Scale(0.06, 0.06, 0.06);
			RenderMesh(meshList[corpse], true);
			modelStack.PopMatrix();
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(23, 0, -20);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
			modelStack.PushMatrix();
			modelStack.Translate(0, 1.7, 0);
			modelStack.Scale(0.1, 0.1, 0.1);
			RenderMesh(meshList[matress], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(0, 1, 0);
			modelStack.Scale(0.165, 0.165, 0.165);
			RenderMesh(meshList[bedframe], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(-0.3, 3, 0);
			modelStack.Scale(0.06, 0.06, 0.06);
			RenderMesh(meshList[corpse], true);
			modelStack.PopMatrix();
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(23, 0, -35);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
			modelStack.PushMatrix();
			modelStack.Translate(0, 1.7, 0);
			modelStack.Scale(0.1, 0.1, 0.1);
			RenderMesh(meshList[matress], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(0, 1, 0);
			modelStack.Scale(0.165, 0.165, 0.165);
			RenderMesh(meshList[bedframe], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(-0.3, 3, 0);
			modelStack.Scale(0.06, 0.06, 0.06);
			RenderMesh(meshList[corpse], true);
			modelStack.PopMatrix();
		modelStack.PopMatrix();
	modelStack.PopMatrix();

	//bed row (left)
	modelStack.PushMatrix();
	modelStack.Translate(75, 0, -40);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1, 1, 1);
		modelStack.PushMatrix();
		modelStack.Translate(23, 0, -5);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
			modelStack.PushMatrix();
			modelStack.Translate(0, 1.7, 0);
			modelStack.Scale(0.1, 0.1, 0.1);
			RenderMesh(meshList[matress], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(0, 1, 0);
			modelStack.Scale(0.165, 0.165, 0.165);
			RenderMesh(meshList[bedframe], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(-0.3, 3, 0);
			modelStack.Scale(0.06, 0.06, 0.06);
			RenderMesh(meshList[corpse], true);
			modelStack.PopMatrix();
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(23, 0, -20);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
			modelStack.PushMatrix();
			modelStack.Translate(0, 1.7, 0);
			modelStack.Scale(0.1, 0.1, 0.1);
			RenderMesh(meshList[matress], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(0, 1, 0);
			modelStack.Scale(0.165, 0.165, 0.165);
			RenderMesh(meshList[bedframe], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(-0.3, 3, 0);
			modelStack.Scale(0.06, 0.06, 0.06);
			RenderMesh(meshList[corpse], true);
			modelStack.PopMatrix();
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(23, 0, -35);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
			modelStack.PushMatrix();
			modelStack.Translate(0, 1.7, 0);
			modelStack.Scale(0.1, 0.1, 0.1);
			RenderMesh(meshList[matress], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(0, 1, 0);
			modelStack.Scale(0.165, 0.165, 0.165);
			RenderMesh(meshList[bedframe], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(-0.3, 3, 0);
			modelStack.Scale(0.06, 0.06, 0.06);
			RenderMesh(meshList[corpse], true);
			modelStack.PopMatrix();
		modelStack.PopMatrix();
	modelStack.PopMatrix();

	//bed drawers
	modelStack.PushMatrix();
	modelStack.Translate(57, 0, -13);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(0.15, 0.15, 0.15);
	RenderMesh(meshList[beddrawer], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(57, 0, -27);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(0.15, 0.15, 0.15);
	RenderMesh(meshList[beddrawer], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(17, 0, -13);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(0.15, 0.15, 0.15);
	RenderMesh(meshList[beddrawer], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(17, 0, -27);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(0.15, 0.15, 0.15);
	RenderMesh(meshList[beddrawer], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(37.5, 7, -4);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(8, 8, 8);
	RenderMesh(meshList[metalcabinet], true);
	modelStack.PopMatrix();
}

void SceneSP2Room4::RenderRightRoom()
{
	modelStack.PushMatrix();
	modelStack.Translate(-28, 0, -20);
	modelStack.Rotate(110, 0, 1, 0);
	modelStack.Scale(0.16, 0.16, 0.16);
	RenderMesh(meshList[bedscreenZ], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-40, 0, -13);
	modelStack.Rotate(50, 0, 1, 0);
	modelStack.Scale(0.16, 0.16, 0.16);
	RenderMesh(meshList[bedscreenZ], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-52, 0, -18);
	modelStack.Rotate(20, 0, 1, 0);
	modelStack.Scale(0.16, 0.16, 0.16);
	RenderMesh(meshList[bedscreenL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-40, 3, -22);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(0.04, 0.04, 0.04);
	RenderMesh(meshList[xtable], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-28, 1, -24);
	modelStack.Rotate(30, 0, 1, 0);
	modelStack.Scale(0.08, 0.08, 0.08);
	RenderMesh(meshList[stand], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-28, 9, -24);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(0.06, 0.06, 0.06);
	RenderMesh(meshList[heartmon], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-50, 0, -20);
	modelStack.Rotate(-30, 0, 1, 0);
	modelStack.Scale(0.12, 0.12, 0.12);
	RenderMesh(meshList[bedtable], true);
	modelStack.PopMatrix();
}

void SceneSP2Room4::Render()
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
	//modelStack.PushMatrix();
	//modelStack.Translate(Colliderlist[12].getPosition().x, Colliderlist[12].getPosition().y, Colliderlist[12].getPosition().z);
	//RenderMesh(meshList[Colliderbox], false);
	//modelStack.PopMatrix();

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
	
	


	//all doors
	//schoolleft
	

	//left and right main walls
	modelStack.PushMatrix();
	modelStack.Translate(-60, 12, -50);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(25, 1, 100);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(60, 12, -50);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(25, 1, 100);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-59, 7, -65);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(12, 17, 1);
	RenderMesh(meshList[Hdoors], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(59, 7, -65);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(12, 17, 1);
	RenderMesh(meshList[Hdoors], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 12, -100);
	//modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(165, 25, 1);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();
	
	//entrance walls
	modelStack.PushMatrix();
	modelStack.Translate(-15, 12, -23);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(43, 25, 1);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(15, 12, -23);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(43, 25, 1);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();


	//front walls
	modelStack.PushMatrix();
	modelStack.Translate(-43.5, 12, 0);
	modelStack.Scale(70.5, 25, 1);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(43.5, 12, 0);
	modelStack.Scale(70.5, 25, 1);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();

	//left room front walls
	modelStack.PushMatrix();
	modelStack.Translate(20, 12, -44);
	modelStack.Scale(20, 25, 1);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(55, 12, -44);
	modelStack.Scale(20, 25, 1);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(37.5, 20, -44);
	modelStack.Scale(20, 10, 1);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();

	//right room front walls
	modelStack.PushMatrix();
	modelStack.Translate(-20, 12, -44);
	modelStack.Scale(20, 25, 1);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-55, 12, -44);
	modelStack.Scale(20, 25, 1);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-37.5, 20, -44);
	modelStack.Scale(20, 10, 1);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();

	//signholder wall
	modelStack.PushMatrix();
	modelStack.Translate(0, 20, 0);
	modelStack.Scale(30, 10, 1);
	RenderMesh(meshList[GEO_WALL], true);
	modelStack.PopMatrix();

	RenderLeftRoom();

	RenderRightRoom();

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


	//UI OVERLAY
	//vision vignette
	RenderMeshOnScreen(meshList[GEO_OVERLAY], 40, 30, 1, 1);
	//camcorder
	RenderMeshOnScreen(meshList[GEO_OVERLAY2], 40, 30, 1, 1);
	//stamina
	RenderMeshOnScreen(meshList[GEO_BAR], 10 - (5 - float(camera.playerStamina) * 0.25f), 52, float(camera.playerStamina) * 0.5f, 1);
	//INTERACTIONS
	if (interact)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], interact_message, Color(1, 1, 0), 4, 22, 5);
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

void SceneSP2Room4::Exit()
{
	// Cleanup VBO here
	delete ghost;
	delete inventory;
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneSP2Room4::RenderSkybox()
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




void SceneSP2Room4::RenderMesh(Mesh* mesh, bool enableLight)
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

void SceneSP2Room4::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneSP2Room4::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SceneSP2Room4::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey)
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



