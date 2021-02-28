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
	flashlight = false;
	flashlight_lifetime = 90;
	inLocker = false;
	Qpressed = Qreleased = false;
	showSideBox = true;
	Epressed = Ereleased = false;
	Fpressed = Freleased = false;
	Apressed = Areleased = false;
	Dpressed = Dreleased = false;
	Rpressed = Rreleased = false;
	camBlinkOffSec = 0;
	camBlinkOnSec = 0;
	fps = 60;
	DS_main = OPEN;
	camBlinkOn = false;
	camBlinkOff = true;
	placeitem = false;
	doorunlocked = false;
	bruhmoment = false;
	flowerstaken = false;

	//@pause
	gamepaused = false;
	PKeypressed = PKeyreleased = false;

	//inventory icons
	itemImage[0] = meshList[GEO_SPARKPLUGICON];
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
	camera.Init(Vector3(-475, 9, 0), Vector3(-495, 9, 0), Vector3(0, 1, 0));
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
	meshList[GEO_INVENTORY] = MeshBuilder::GenerateQuad2("inventory", 5, 1, White);
	meshList[GEO_INVENTORY]->textureID = LoadTGA("Image//inventory.tga");
	meshList[GEO_SELECT] = MeshBuilder::GenerateQuad2("highlight", 1, 1, White);
	meshList[GEO_SELECT]->textureID = LoadTGA("Image//highlight.tga");
	meshList[GEO_CHATBOX] = MeshBuilder::GenerateQuad2("chatbox", 30, 20, 0);
	meshList[GEO_CHATBOX]->textureID = LoadTGA("Assigment2Images//chatbox.tga");
	meshList[GEO_SIDEBOX] = MeshBuilder::GenerateQuad2("chatbox", 30, 20, 0);
	meshList[GEO_SIDEBOX]->textureID = LoadTGA("Assigment2Images//sidebox.tga");
	meshList[GEO_ITEMDISPLAY] = MeshBuilder::GenerateQuad2("item details popup", 1.5, 1, White);
	meshList[GEO_ITEMDISPLAY]->textureID = LoadTGA("Image//itemdisplay.tga");

	meshList[GEO_SPARKPLUGICON] = MeshBuilder::GenerateQuad2("item image", 1, 1, White);

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

	meshList[Hdoors] = MeshBuilder::GenerateCubeT("door", 1, 1, 1, 0, 0, 1, 1, Color(1.f, 0.1f, 0.1f));
	meshList[Hdoors]->textureID = LoadTGA("Image//hospital_door_full.tga");
	meshList[Hdoors]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[frontdesk] = MeshBuilder::GenerateOBJ("desk", "OBJ//marble_desk.obj");
	meshList[frontdesk]->textureID = LoadTGA("Image//desks.tga");
	meshList[frontdesk]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);


	meshList[sparkplug] = MeshBuilder::GenerateOBJ("desk", "OBJ//sparkplug.obj");
	meshList[sparkplug]->textureID = LoadTGA("Image//sparkplug.tga");
	meshList[sparkplug]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[BATTERY] = MeshBuilder::GenerateOBJ("Building", "OBJ//Battery.obj");
	meshList[BATTERY]->textureID = LoadTGA("Assigment2Images//batterytexture.tga");
	meshList[BATTERY]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[deadbody] = MeshBuilder::GenerateOBJ("easter egg", "OBJ/DeadBody.obj");
	meshList[deadbody]->textureID = LoadTGA("Image//deadbody.tga");
	meshList[deadbody]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[rose] = MeshBuilder::GenerateOBJ("easter egg", "OBJ/Rose.obj");
	meshList[rose]->textureID = LoadTGA("Image//rose.tga");
	meshList[rose]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);

	meshList[GEO_JUMPSCARE1] = MeshBuilder::GenerateQuad2("Jumpscare1", 1, 1, 0);
	meshList[GEO_JUMPSCARE1]->textureID = LoadTGA("Image//skulljumpscare.tga");

	

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
	glUniform1i(m_parameters[U_NUMLIGHTS], 6);

	
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


	translateobj = 6;

	flowerCounter = 0;
	jumpscareTimerActive1 = false;
	jumpscareTimer1 = 0.2;
	jumpscareActive1 = false;


	//scene items
	items[0] = new Item("Spark Plug", Item::SPARK_PLUG, Vector3(-492, -3, 39));
	items[1] = new Item("Battery", Item::BATTERY, Vector3(-539.6, 6.3, 0));
	items[2] = new Item("Battery", Item::BATTERY, Vector3(-483, 6.5, -17));
	items[3] = new Item("Roses", Item::FLOWER, Vector3(-538, 6.5, -8)); //pos diff from in render


	//itemplaced
	for (int i = 0; i < 7; i++) {
		itemplaced[i] = false;
	}

	main_door[0].mid.Set(-470, 7.69, 4.1);
	main_door[1].mid.Set(-470.f, 7.79f, -4.1f);
	main_door[0].lengthz = main_door[1].lengthz = 5;
	main_door[0].rotateY = 90;
	main_door[1].rotateY = -90;

	//list of lockers
	Lockerlist.push_back(Locker());
	Lockerlist[0].setpos(Vector3(-550.f, -0.2f, 58.f));
	Lockerlist[0].setyaw(90);

	//wall colliders
	//@collider

	Colliderlist.push_back(ColliderBox());
	Colliderlist[0].setlength(12, 17, 3);
	Colliderlist[0].Setposition(Vector3(-535, 7, 59));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[1].setlength(3, 17, 12);
	Colliderlist[1].Setposition(Vector3(-535, 7, -59));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[2].setlength(100, 25, 3);
	Colliderlist[2].Setposition(Vector3(-520, 12, 60));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[3].setlength(100, 25, 3);
	Colliderlist[3].Setposition(Vector3(-520, 12, -60));

	//@bedcolliders
	//right row
	Colliderlist.push_back(ColliderBox());
	Colliderlist[4].setlength(10, 7, 12);
	Colliderlist[4].Setposition(Vector3(-475, 0, -23));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[5].setlength(10, 7, 12);
	Colliderlist[5].Setposition(Vector3(-490, 0, -23));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[6].setlength(10, 7, 12);
	Colliderlist[6].Setposition(Vector3(-505, 0, -23));

	//left row
	Colliderlist.push_back(ColliderBox());
	Colliderlist[7].setlength(10, 7, 12);
	Colliderlist[7].Setposition(Vector3(-475, 0, -53));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[8].setlength(10, 7, 12);
	Colliderlist[8].Setposition(Vector3(-490, 0, -53));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[9].setlength(10, 7, 12);
	Colliderlist[9].Setposition(Vector3(-505, 0, -53));

	//right room colliders
	Colliderlist.push_back(ColliderBox());
	Colliderlist[10].setlength(12, 7, 25);
	Colliderlist[10].Setposition(Vector3(-489, 3, 40));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[11].setlength(16, 7, 10);
	Colliderlist[11].Setposition(Vector3(-494, 9, 28));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[12].setlength(20, 7, 10);
	Colliderlist[12].Setposition(Vector3(-494, 9, 56));

	//back wall
	Colliderlist.push_back(ColliderBox());
	Colliderlist[13].setlength(3, 25, 165);
	Colliderlist[13].Setposition(Vector3(-570, 12, 0));


	//entrance walls
	Colliderlist.push_back(ColliderBox());
	Colliderlist[14].setlength(43, 25, 3);
	Colliderlist[14].Setposition(Vector3(-492, 12, 15));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[15].setlength(43, 25, 3);
	Colliderlist[15].Setposition(Vector3(-492, 12, -15));

	//room front walls
	Colliderlist.push_back(ColliderBox());
	Colliderlist[16].setlength(3, 25, 20);
	Colliderlist[16].Setposition(Vector3(-514, 12, -20));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[17].setlength(3, 25, 20);
	Colliderlist[17].Setposition(Vector3(-514, 12, -50));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[18].setlength(3, 25, 20);
	Colliderlist[18].Setposition(Vector3(-514, 12, 20));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[19].setlength(3, 25, 20);
	Colliderlist[19].Setposition(Vector3(-514, 12, 50));

	//OP room door 
	Colliderlist.push_back(ColliderBox());
	Colliderlist[20].setlength(3, 25, 10);
	Colliderlist[20].Setposition(Vector3(-514, 12, 35));

	//metal cabinet
	Colliderlist.push_back(ColliderBox());
	Colliderlist[21].setlength(9, 12, 9);
	Colliderlist[21].Setposition(Vector3(-474, 7, -37.5));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[22].setlength(24, 12, 5);
	Colliderlist[22].Setposition(Vector3(-488, 0, -57));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[23].setlength(24, 12, 5);
	Colliderlist[23].Setposition(Vector3(-488, 0, -16));

	//left room doors
	Colliderlist.push_back(ColliderBox());
	Colliderlist[24].setlength(4, 15.5, 5);
	Colliderlist[24].Setposition(Vector3(-512.5f, 7.2f, -32.f));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[25].setlength(4, 15.5, 2);
	Colliderlist[25].Setposition(Vector3(-512.5, 7.2, -41));

	Colliderlist.push_back(ColliderBox());
	Colliderlist[26].setlength(7.5, 15.5, 22);
	Colliderlist[26].Setposition(Vector3(-542, 3, 0));

	//front wall
	Colliderlist.push_back(ColliderBox());
	Colliderlist[27].setlength(3, 25, 165);
	Colliderlist[27].Setposition(Vector3(-470, 12, 0));

	//lockercollider
	Colliderlist.push_back(ColliderBox());
	Colliderlist[28].setlength(4.3, 10, 3.9);
	Colliderlist[28].Setposition(Vector3(Lockerlist[0].getpos()));

	//easter egg collider
	Colliderlist.push_back(ColliderBox());
	Colliderlist[29].setlength(10, 6, 10);
	Colliderlist[29].Setposition(Vector3(-479, 0, 45));


	//colliderbox for checking any collider(just one)
	meshList[Colliderbox] = MeshBuilder::GenerateColliderBox("Box", Colliderlist[9].getxlength(), Colliderlist[9].getylength(), Colliderlist[9].getzlength());

	//terrain
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad2("floor/ceiling", 1, 1, White);
	meshList[GEO_QUAD]->textureID = LoadTGA("Assigment2Images//garage.tga");//this one was in render cousing memory leak
	meshList[GEO_WALL] = MeshBuilder::GenerateCubeT("walls", 1, 1, 1, 0, 0, 1, 1, Color(1.f, 0.1f, 0.1f));
	meshList[GEO_WALL]->textureID = LoadTGA("Assigment2Images//garage.tga");
	meshList[GEO_FLOOR] = MeshBuilder::GenerateCubeT("walls", 1, 1, 1, 0, 0, 1, 1, Color(1.f, 0.1f, 0.1f));
	meshList[GEO_FLOOR]->textureID = LoadTGA("Image//floor-green-scrach.tga");
	meshList[GEO_LEFTDOOR] = MeshBuilder::GenerateCubeT("door", 1, 1, 1, 0, 0, 1, 1, Color(1.f, 0.1f, 0.1f));
	meshList[GEO_LEFTDOOR]->textureID = LoadTGA("Image//hos_door_L.tga");
	meshList[GEO_RIGHTDOOR] = MeshBuilder::GenerateCubeT("door", 1, 1, 1, 0, 0, 1, 1, Color(1.f, 0.1f, 0.1f));
	meshList[GEO_RIGHTDOOR]->textureID = LoadTGA("Image//hos_door_R.tga");
	
	//UI
	meshList[GEO_BATTERY] = MeshBuilder::GenerateQuad2("flashlight lifetime bar", 1, 1, White);
	meshList[GEO_STAMINA] = MeshBuilder::GenerateQuad2("UI usage", 1, 1, White);
	meshList[GEO_STAMINA]->textureID = LoadTGA("Assigment2Images//sprint.tga");
	meshList[SUFFOCATION] = MeshBuilder::GenerateQuad2("UI usage", 1, 1, White);
	meshList[SUFFOCATION]->textureID = LoadTGA("Assigment2Images//suffocation.tga");
	meshList[GEO_OVERLAY] = MeshBuilder::GenerateQuad2("for overlays", 80, 60, 0);
	meshList[GEO_OVERLAY2] = MeshBuilder::GenerateQuad2("Camcorder", 80, 60, 0);
	meshList[GEO_BAR] = MeshBuilder::GenerateQuad2("UI usage", 1, 1, Yellow);
	meshList[GEO_BAR2] = MeshBuilder::GenerateQuad2("stamina bar", 1, 1, Red);
	meshList[GEO_OVERLAY]->textureID = LoadTGA("Image//VISIONOFF.tga");
	meshList[GEO_OVERLAY2]->textureID = LoadTGA("Image//camcorder2.tga");
	meshList[GEO_REDDOT] = MeshBuilder::GenerateQuad2("dot", 1, 1, White);
	meshList[GEO_REDDOT]->textureID = LoadTGA("Image//redDot.tga");
	meshList[GEO_WARNING1] = MeshBuilder::GenerateQuad2("warning overlay", 80, 60, 0);
	meshList[GEO_WARNING1]->textureID = LoadTGA("Image//pinktint.tga");
	meshList[GEO_WARNING2] = MeshBuilder::GenerateQuad2("warning overlay", 80, 60, 0);
	meshList[GEO_WARNING2]->textureID = LoadTGA("Image//redtint.tga");
	meshList[GEO_DEATH] = MeshBuilder::GenerateQuad2("death overlay", 80, 60, 0);
	meshList[GEO_DEATH]->textureID = LoadTGA("Image//death.tga");
	meshList[GEO_YOUDIED] = MeshBuilder::GenerateQuad2("death overlay words", 80, 60, 0);
	meshList[GEO_YOUDIED]->textureID = LoadTGA("Image//YouDiedScreen.tga");

	//@pause
	//pause menu
	meshList[GEO_PAUSEMENU] = MeshBuilder::GenerateQuad2("pause", 1, 1, 0);
	meshList[GEO_PAUSEMENU]->textureID = LoadTGA("Image//pause.tga");

	//Locker mesh
	meshList[locker] = MeshBuilder::GenerateOBJ("Locker", "OBJ//locker.obj");
	meshList[locker]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	meshList[locker]->textureID = LoadTGA("Assigment2Images//locker.tga");

	//default active
	for (int i = 0; i < signed(Colliderlist.size()); i++) {
		Colliderlist[i].setactive(true);
	}
	//list of colliders
	camera.setchecker(Colliderlist);
	
	//Set boundary here
	camera.SetBounds(-1500, 1500, -365, 360);
	//camblink
	camBlinkOffSec = 0;
	camBlinkOnSec = 0;
	camBlinkOn = false;
	camBlinkOff = true;
	//door state
	DS_opRoom = CLOSED;
	DS_main = OPEN;
	//trap mesh
	meshList[GEO_BEARTRAP] = MeshBuilder::GenerateOBJ("Beartrap", "OBJ//BearTrap.obj");
	meshList[GEO_BEARTRAP]->textureID = LoadTGA("Assigment2Images//BearTrap.tga");
	meshList[GEO_BEARTRAP]->material.kAmbient.Set(0.35f, 0.35f, 0.35f);
	//trap list
	traplist.push_back(trap(trap::beartrap, Vector3(-480, 0, -10)));
	traplist.push_back(trap(trap::beartrap, Vector3(-535, 0, 25)));
	
}

void SceneSP2Room4::UseItem(int itemname)
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
	case Item::FLOWER:
		if (camera.position.z <= -45 && camera.position.z >= -55 && camera.position.x >= -483 && camera.position.x <= -479 && !itemplaced[3])
		{
			//left body top
			
			itemplaced[body1_l] = true;
			if (inventory->items[inventory->selected]->count > 1)
			{
				inventory->items[inventory->selected]->count--;
			}
			else
			{
				inventory->items[inventory->selected] = nullptr;
			}
		}
		else if (camera.position.z <= -45 && camera.position.z >= -55 && camera.position.x >= -496 && camera.position.x <= -484 && !itemplaced[4])
		{
			//left body med
			
			itemplaced[body2_l] = true;
			if (inventory->items[inventory->selected]->count > 1)
			{
				inventory->items[inventory->selected]->count--;
			}
			else
			{
				inventory->items[inventory->selected] = nullptr;
			}
		}
		else if (camera.position.z <= -45 && camera.position.z >= -55 && camera.position.x >= -512 && camera.position.x <= -498 && !itemplaced[5])
		{
		
			itemplaced[body3_l] = true;
			if (inventory->items[inventory->selected]->count > 1)
			{
				inventory->items[inventory->selected]->count--;
			}
			else
			{
				inventory->items[inventory->selected] = nullptr;
			}
			
		}
		else if (camera.position.z <= -20 && camera.position.z >= -30 && camera.position.x >= -483 && camera.position.x <= -479 && !itemplaced[0])
		{
			
			itemplaced[body1_r] = true;
			if (inventory->items[inventory->selected]->count > 1)
			{
				inventory->items[inventory->selected]->count--;
			}
			else
			{
				inventory->items[inventory->selected] = nullptr;
			}
			
		}
		else if (camera.position.z <= -20 && camera.position.z >= -30 && camera.position.x >= -496 && camera.position.x <= -484 && !itemplaced[1])
		{
		
			itemplaced[body2_r] = true;
			if (inventory->items[inventory->selected]->count > 1)
			{
				inventory->items[inventory->selected]->count--;
			}
			else
			{
				inventory->items[inventory->selected] = nullptr;
			}
			
		}
		else if (camera.position.z <= -20 && camera.position.z >= -30 && camera.position.x >= -511 && camera.position.x <= -499 && !itemplaced[2])
		{
			
			itemplaced[body3_r] = true;
			if (inventory->items[inventory->selected]->count > 1)
			{
				inventory->items[inventory->selected]->count--;
			}
			else
			{
				inventory->items[inventory->selected] = nullptr;
			}
			
		}
		else if (camera.position.z <= 43 && camera.position.z >= 36 && camera.position.x >= -498 && camera.position.x <= -495 && !itemplaced[6])
		{
			
			itemplaced[body_op] = true;
			Creakingdoor->play2D("Sound\\Effects\\383083__chrisreierson__creaking-door-2.wav", false);
			DS_main = OPENING;
			if (inventory->items[inventory->selected]->count > 1)
			{
				inventory->items[inventory->selected]->count--;
			}
			else
			{
				inventory->items[inventory->selected] = nullptr;
			}
			
		}

		//if all placed, unlock door
		if (itemplaced[0] && itemplaced[1] && itemplaced[2] && itemplaced[3] && itemplaced[4] && itemplaced[5])
		{
			doorunlocked = true;
		}
		break;
	}
	//death timer
	deathtimer = 0;
}

void SceneSP2Room4::Set(Scene* scene)
{
	inventory = scene->inventory;
	ghost = scene->ghost;
	screwDriverFound = scene->screwDriverFound;
	hammerFound = scene->hammerFound;
	wrenchFound = scene->wrenchFound;
	SparkplugFound = scene->SparkplugFound;
	ObjectivePhase = scene->ObjectivePhase;
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
	light[2].power = 0;
	light[3].power = 0;
	light[4].power = 0;
	light[5].power = 0;
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT4_POWER], light[4].power);
	glUniform1f(m_parameters[U_LIGHT5_POWER], light[5].power);

	Application::SetCursorPos(480, camera.mousePosY);
	//OP room door
	opRoom_door[0].rotateY = 0;
	opRoom_door[1].rotateY = 0;
	DS_main = OPEN;
	main_door[0].rotateY = 90;
	main_door[1].rotateY = -90;
	//inventory item image
	for (int i = 0; i < 8; i++)
	{
		itemImage[i] = scene->itemImage[i];
	}
}

void SceneSP2Room4::SetBackground()
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
	if (!Creakingdoor) {
		Creakingdoor = createIrrKlangDevice();
	}
	Heartbeat->setSoundVolume(0.f);
	Background->setSoundVolume(0.25f);//Volume control
	Effect->setSoundVolume(0.f);
	
}

void SceneSP2Room4::Update(double dt)
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
	if (ghost->kill) {
		deathtimer += dt;
		if (deathtimer > 7) {
			Background->setSoundVolume(0.f);
			Effect->setSoundVolume(0.f);
			Jumpscare->setSoundVolume(0.f);
			Heartbeat->setSoundVolume(0.f);
			Application::Load();
			Application::setscene(Scene_Menu);
			return;
		}
	}
	else if (ghost->kill == false && ghost->state == Ghost::SPIN) {
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
	else if (ghost->kill == false) {
		Heartbeat->setSoundVolume(0.f);
		Background->setSoundVolume(0.5f);
	}
	//key input
	//if (Application::IsKeyPressed('1')) {
	//	glEnable(GL_CULL_FACE);
	//}
	//else if (Application::IsKeyPressed('2')) {
	//	glDisable(GL_CULL_FACE);
	//}
	//else if (Application::IsKeyPressed('3')) {
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//}
	//else if (Application::IsKeyPressed('4')) {
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//}
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

	if (wrenchFound == 1 && screwDriverFound == 1 && SparkplugFound == 1 && screwDriverFound == 1)
	{
		ObjectivePhase = 3;
	}

	if (campos_x > -479 && campos_z < 4 && campos_z > -4)
	{
		nearExit = true;
	}
	else {
		nearExit = false;
		showChatbox = false;
	}


	if (exitHospital == true && nearExit == true)
	{
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_Main);
		exitHospital = false;
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

	//@pause
	if (PKeypressed)
	{
		PKeypressed = false;
		gamepaused = true;
		Application::GetCursorPos(&Mousetempx, &Mousetempy);
		Application::pause(true);
	}


	if (nearExit == true && Fpressed == true && itemplaced[body_op])
	{
		exitHospital = true;
		Fpressed = false;
	}



	//items
	for (int i = 0; i < 4; i++) 
	{
		if (items[i] != nullptr)
		{
			if (camera.position.z > items[i]->pos.z - 10 && camera.position.z < items[i]->pos.z + 10
				&& camera.position.x > items[i]->pos.x - 10 && camera.position.x < items[i]->pos.x + 10)
			{
				interact = true;
				interact_message = "F to pick up " + items[i]->name;
				if (Fpressed)
				{
					if (PickUpItem(items[i]))
					{
						delete items[i];
					}
					Fpressed = false;
					items[i] = nullptr;
					if (i == 3)
					{
						flowerstaken = true;
					}
					else if (i == 0)
					{
						SparkplugFound = 1;
					}
				}
			}
		}
	}

	//door states
	Vector3 origin(470, 7.75, 0);
	switch (DS_main)
	{
	case OPEN:
		//doors close on their own
		if ((camera.position - origin).Length() >= 20 && !itemplaced[body_op])
		{
			DS_main = CLOSING;
			Creakingdoor->play2D("Sound\\Effects\\383083__chrisreierson__creaking-door-2.wav", false);
		}
		if (camera.position.z >= -5 && camera.position.z <= 5 && camera.position.x <= -471 && camera.position.x >= -480)
		{
			interact = true;
			interact_message = "Exit Hospital";
			if (Fpressed)
			{
				Fpressed = false;
				Application::setscene(Scene_Main);
			}
			
		}
		break;
	case CLOSED:
		if (camera.position.z >= -5 && camera.position.z <= 5 && camera.position.x <= -471 && camera.position.x >= -480)
		{
			interact = true;
			interact_message = "Door is Locked";
		}
		break;
	case OPENING:
		main_door[0].rotateY += float(20 * dt);
		main_door[1].rotateY -= float(20 * dt);
		if (main_door[0].rotateY >= 90)
		{
			main_door[0].rotateY = 90;
			main_door[1].rotateY = -90;
			DS_main = OPEN;
		}
		break;
	case CLOSING:
		main_door[0].rotateY -= 70 * float(dt);
		main_door[1].rotateY += 70 * float(dt);
		if (main_door[0].rotateY <= 0)
		{
			main_door[0].rotateY = 0;
			main_door[1].rotateY = 0;
			DS_main = CLOSED;
		}
		break;
	}

	switch (DS_opRoom)
	{
	case CLOSED:
		if (camera.position.z >= 33 && camera.position.z <= 36 && camera.position.x <= -503 && camera.position.x >= -520 && doorunlocked)
		{
			interact = true;
			interact_message = "Open Door";
			if (Fpressed)
			{
				Fpressed = false;
				DS_opRoom = OPENING;
				Creakingdoor->play2D("Sound\\Effects\\383083__chrisreierson__creaking-door-2.wav", false);
				Colliderlist[20].setactive(false);
				camera.setchecker(Colliderlist);
			}
		}
		else if(camera.position.z >= 33 && camera.position.z <= 36 && camera.position.x <= -503 && camera.position.x >= -520 && !doorunlocked && !flowerstaken)
		{
			interact = true;
			interact_message = "Locked";
		}
		break;
	case OPENING:
		opRoom_door[0].rotateY -= float(40 * dt);
		opRoom_door[1].rotateY += float(40 * dt);
		if (opRoom_door[1].rotateY >= 90)
		{
			DS_opRoom = OPEN;
		}
		break;
	}

	//rotate sparkplug
	rotateobj += float(40 * dt);


	if (jumpscareTimerActive1 == true)
	{
		jumpscareTimer1 -= dt;
	}
	if (jumpscareTimer1 <= 0)
	{
		jumpscareActive1 = false;
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
		while (Colliderlist[28 + ghost->lockerIndex].iscollide(ghost->pos + 5 * ghost->facing))
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
		if (!inLocker)
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
			ghost->speed = 250;
		}
		if (!inLocker)
		{
			camera.lockedTarget.Set(ghost->pos.x, ghost->pos.y + 15, ghost->pos.z);
			camera.newTarget = camera.target;
			ghost->state = Ghost::SPIN;
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
			ghost->speed = 7;
		}
		break;
	case Ghost::SPIN:
		camera.can_move = false;

		camera.newTarget += (camera.lockedTarget - camera.newTarget).Normalized() * 10 * dt;
		camera.target = camera.newTarget;
		camera.view = (camera.target - camera.position).Normalized();

		camera.up = camera.defaultUp;
		camera.right = camera.view.Cross(camera.up).Normalized();
		camera.up = camera.right.Cross(camera.view).Normalized();

		if ((camera.lockedTarget - camera.target).Length() < 0.1)
		{
			camera.target = camera.lockedTarget;
			ghost->state = Ghost::DEATH;
			showSideBox = false;
			inventory->open = false;
			meshList[GEO_BAR]->textureID = LoadTGA("Image//transparent.tga");
			meshList[GEO_OVERLAY2]->textureID = LoadTGA("Image//transparent.tga");
			meshList[GEO_STAMINA]->textureID = LoadTGA("Image//transparent.tga");
			meshList[GEO_REDDOT]->textureID = LoadTGA("Image//transparent.tga");
			meshList[GEO_BATTERY]->textureID = LoadTGA("Image//transparent.tga");
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
		if (Lockerlist[i].status(camera.position, -1 * camera.view, Fpressed)) {
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
	/*if (Application::IsKeyPressed('6')) {
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
	if (Application::IsKeyPressed('9')) {
		Background->setSoundVolume(0.f);
		Effect->setSoundVolume(0.f);
		Jumpscare->setSoundVolume(0.f);
		Heartbeat->setSoundVolume(0.f);
		Application::setscene(Scene_3);
	}*/

	campos_x = camera.position.x;
	campos_y = camera.position.y;
	campos_z = camera.position.z;


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

	//check if placed flowers on bed
	if (flowerstaken)
	{
		if (camera.position.z <= -45 && camera.position.z >= -55 && camera.position.x >= -483 && camera.position.x <= -479 && !itemplaced[3])
		{
			//left body top
			interact = true;
			interact_message = "Place Flower";
		}
		else if (camera.position.z <= -45 && camera.position.z >= -55 && camera.position.x >= -496 && camera.position.x <= -484 && !itemplaced[4])
		{
			//left body med
			interact = true;
			interact_message = "Place Flower";
		}
		else if (camera.position.z <= -45 && camera.position.z >= -55 && camera.position.x >= -512 && camera.position.x <= -498 && !itemplaced[5])
		{
			//left body bottom
			interact = true;
			interact_message = "Place Flower";
		}
		else if (camera.position.z <= -20 && camera.position.z >= -30 && camera.position.x >= -483 && camera.position.x <= -479 && !itemplaced[0])
		{
			//left body top
			interact = true;
			interact_message = "Place Flower";
		}
		else if (camera.position.z <= -20 && camera.position.z >= -30 && camera.position.x >= -496 && camera.position.x <= -484 && !itemplaced[1])
		{
			//left body med
			interact = true;
			interact_message = "Place Flower";
		}
		else if (camera.position.z <= -20 && camera.position.z >= -30 && camera.position.x >= -511 && camera.position.x <= -499 && !itemplaced[2])
		{
			//left body bottom
			interact = true;
			interact_message = "Place Flower";
		}
		else if (camera.position.z <= 43 && camera.position.z >= 36 && camera.position.x >= -498 && camera.position.x <= -495 && !itemplaced[6])
		{
			//left body bottom
			interact = true;
			interact_message = "Place Flower";
		}
		else
		{
			placeitem = false;
		}
	}

	//if final item placed, give sparkplug
	if (itemplaced[6])
	{
		if (translateobj <= 7.5)
		{
			translateobj += float(0.5 * dt);
		}
	}

	//easter egg jumpscare
	if (camera.position.z <= 55 && camera.position.z >= 35 && camera.position.x >= -481 && camera.position.x <= -473 && !bruhmoment)
	{
		interact = true;
		interact_message = "Press F to pay respects";
		if (Fpressed)
		{

			jumpscareActive1 = true;
			jumpscareTimerActive1 = true;
			Jumpscare->play2D("Sound\\Jumpscares\\Horror_Sound_Effects_For_Youtubers_-_No_Copyrighted_SFX_For_Video_Editing (mp3cut.net).wav", false);


			bruhmoment = true;
		}
	}


}



void SceneSP2Room4::PauseUpdate()
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
			Application::Load();
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
			modelStack.Translate(0.f, 1.7f, 0.f);
			modelStack.Scale(0.1f, 0.1f, 0.1f);
			RenderMesh(meshList[matress], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(0, 1, 0);
			modelStack.Scale(0.165f, 0.165f, 0.165f);
			RenderMesh(meshList[bedframe], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(-0.3, 3, 0);
			modelStack.Scale(0.06f, 0.06f, 0.06f);
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
			modelStack.Scale(0.165f, 0.165f, 0.165f);
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
			modelStack.Scale(0.1f, 0.1f, 0.1f);
			RenderMesh(meshList[matress], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(0, 1, 0);
			modelStack.Scale(0.165, 0.165, 0.165);
			RenderMesh(meshList[bedframe], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(-0.3f, 3.f, 0.f);
			modelStack.Scale(0.06f, 0.06f, 0.06f);
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
			modelStack.Scale(0.1f, 0.1f, 0.1f);
			RenderMesh(meshList[matress], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(0, 1, 0);
			modelStack.Scale(0.165, 0.165, 0.165);
			RenderMesh(meshList[bedframe], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(-0.3f, 3.f, 0.f);
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

	//render flowers

	if (itemplaced[0])
	{
		modelStack.PushMatrix();
		modelStack.Translate(23, 4.4, -5);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(0.05, 0.05, 0.05);
		RenderMesh(meshList[rose], true);
		modelStack.PopMatrix();
	}

	if (itemplaced[1])
	{
		modelStack.PushMatrix();
		modelStack.Translate(23, 4.4, -20);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(0.05, 0.05, 0.05);
		RenderMesh(meshList[rose], true);
		modelStack.PopMatrix();
	}
	
	if (itemplaced[2])
	{
		modelStack.PushMatrix();
		modelStack.Translate(23, 4.4, -35);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(0.05, 0.05, 0.05);
		RenderMesh(meshList[rose], true);
		modelStack.PopMatrix();
	}

	if (itemplaced[3])
	{
		modelStack.PushMatrix();
		modelStack.Translate(52, 4.4, -5);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(0.05f, 0.05f, 0.05f);
		RenderMesh(meshList[rose], true);
		modelStack.PopMatrix();
	}

	if (itemplaced[4])
	{
		modelStack.PushMatrix();
		modelStack.Translate(52, 4.4, -20);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(0.05, 0.05, 0.05);
		RenderMesh(meshList[rose], true);
		modelStack.PopMatrix();
	}

	if (itemplaced[5])
	{
		modelStack.PushMatrix();
		modelStack.Translate(52.f, 4.4f, -35.f);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(0.05f, 0.05f, 0.05f);
		RenderMesh(meshList[rose], true);
		modelStack.PopMatrix();
	}
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
	modelStack.Scale(0.16f, 0.16f, 0.16f);
	RenderMesh(meshList[bedscreenZ], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-52, 0, -18);
	modelStack.Rotate(20, 0, 1, 0);
	modelStack.Scale(0.16, 0.16, 0.16);
	RenderMesh(meshList[bedscreenL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-45, 0, -9);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(6, 6, 6);
	RenderMesh(meshList[deadbody], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-40, 3, -22);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(0.04, 0.04, 0.04);
	RenderMesh(meshList[xtable], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-40.2, 5.5, -22);
	modelStack.Scale(0.06f, 0.06f, 0.06f);
	RenderMesh(meshList[corpse], true);
	modelStack.PopMatrix();

	if (itemplaced[6])
	{
		modelStack.PushMatrix();
		modelStack.Translate(-40.2, 6.8, -22);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(0.05f, 0.05f, 0.05f);
		RenderMesh(meshList[rose], true);
		modelStack.PopMatrix();
	}

	if (items[0] != nullptr)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-39, translateobj, -22);
		modelStack.Rotate(rotateobj, 0, 1, 0);
		modelStack.Scale(0.2, 0.2, 0.2);
		RenderMesh(meshList[sparkplug], true);
		modelStack.PopMatrix();
	}

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
	modelStack.Scale(0.12f, 0.12f, 0.12f);
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
	/*modelStack.PushMatrix();
	modelStack.Translate(Colliderlist[9].getPosition().x, Colliderlist[9].getPosition().y, Colliderlist[9].getPosition().z);
	RenderMesh(meshList[Colliderbox], false);
	modelStack.PopMatrix();*/

	//SOFT CODED
	//main door
	modelStack.PushMatrix();
	modelStack.Translate(main_door[0].mid.x, main_door[0].mid.y, main_door[0].mid.z);

	modelStack.Translate(0.25, 0, 2.5);
	modelStack.Rotate(main_door[0].rotateY, 0, 1, 0);
	modelStack.Translate(-0.25, 0, -2.5);

	modelStack.Scale(1, 15, 8.2);
	RenderMesh(meshList[GEO_RIGHTDOOR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(main_door[1].mid.x, main_door[1].mid.y, main_door[1].mid.z);

	modelStack.Translate(0.25, 0, -2.5);
	modelStack.Rotate(main_door[1].rotateY, 0, 1, 0);
	modelStack.Translate(-0.25, 0, 2.5);

	modelStack.Scale(1.f, 15.f, 8.2f);
	RenderMesh(meshList[GEO_LEFTDOOR], true);
	modelStack.PopMatrix();

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

	
	//HARD CODED
	modelStack.PushMatrix();
	modelStack.Translate(-470, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	{


		//@doors

		//left room doors
		modelStack.PushMatrix();
		modelStack.Translate(37.5, 7.2, -44);
		modelStack.Translate(2.5, 0, 0);
		modelStack.Rotate(110, 0, 1, 0);
		modelStack.Translate(-2.5, 0, 0);
		modelStack.Scale(5, 15.5, 1);
		RenderMesh(meshList[GEO_LEFTDOOR], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(32.5, 7.2, -44);
		modelStack.Translate(-2.5, 0, 0);
		modelStack.Rotate(-40, 0, 1, 0);
		modelStack.Translate(2.5, 0, 0);
		modelStack.Scale(5, 15.5, 1);
		RenderMesh(meshList[GEO_RIGHTDOOR], true);
		modelStack.PopMatrix();

		//right room doors
		modelStack.PushMatrix();
		modelStack.Translate(-32.5, 7.2, -44);
		modelStack.Translate(2.5, 0, 0);
		modelStack.Rotate(opRoom_door[1].rotateY, 0, 1, 0);
		modelStack.Translate(-2.5, 0, 0);
		modelStack.Scale(5, 15.5, 1);
		RenderMesh(meshList[GEO_LEFTDOOR], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-37.5, 7.2, -44);
		modelStack.Translate(-2.5, 0, 0);
		modelStack.Rotate(opRoom_door[0].rotateY, 0, 1, 0);
		modelStack.Translate(2.5, 0, 0);
		modelStack.Scale(5, 15.5, 1);
		RenderMesh(meshList[GEO_RIGHTDOOR], true);
		modelStack.PopMatrix();


		//skybox
		//RenderSkybox();


		//front desk
		modelStack.PushMatrix();
		modelStack.Translate(0, 3, -73);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(0.1f, 0.15f, 0.1f);
		RenderMesh(meshList[frontdesk], true);
		modelStack.PopMatrix();

		//roses on front desk
		if (items[3] != nullptr)
		{
			modelStack.PushMatrix();
			modelStack.Translate(7, 6.5, -73);
			modelStack.Rotate(40, 0, 1, 0);
			modelStack.Scale(0.05, 0.05, 0.05);
			RenderMesh(meshList[rose], true);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(9, 6.5, -73);
			modelStack.Rotate(-30, 0, 1, 0);
			modelStack.Scale(0.05, 0.05, 0.05);
			RenderMesh(meshList[rose], true);
			modelStack.PopMatrix();
		}

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
		modelStack.Translate(-15, 12, -22);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(43, 25, 1);
		RenderMesh(meshList[GEO_WALL], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(15, 12, -22);
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
		modelStack.Translate(50, 12, -44);
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
		modelStack.Translate(-50, 12, -44);
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
		modelStack.Translate(0, 24.5, -50);
		modelStack.Scale(165, 1, 100);
		modelStack.Rotate(90, 1, 0, 0);
		RenderMesh(meshList[GEO_QUAD], true);
		modelStack.PopMatrix();

		if (items[1] != nullptr) {
			modelStack.PushMatrix();
			modelStack.Translate(0, 6.3, -69.6);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(0.03, 0.03, 0.03);
			RenderMesh(meshList[BATTERY], true);
			modelStack.PopMatrix();
		}

		if (items[2] != nullptr) {
			modelStack.PushMatrix();
			modelStack.Translate(17, 6.5, -13);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(0.03f, 0.03f, 0.03f);
			RenderMesh(meshList[BATTERY], true);
			modelStack.PopMatrix();
		}
	}
	modelStack.PopMatrix();

	//SOFTCODED
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
	/*modelStack.PushMatrix();
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
	modelStack.PopMatrix();*/








	//RenderTextOnScreen(meshList[GEO_TEXT], "Flower Counter: "+ std::to_string(flowerCounter), Color(0.f, 0.f, 1.f), 4.f, 10.f, 1.8f);

	//UI OVERLAY

	//Vision vignette
	RenderMeshOnScreen(meshList[GEO_OVERLAY], 40, 30, 1, 1);
	//warning overlay
	if (ghost->state == Ghost::DEATH)
	{
		RenderMeshOnScreen(meshList[GEO_DEATH], 40, 30, 1, 1);
		RenderMeshOnScreen(meshList[GEO_YOUDIED], 40, 30, 1, 1);
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
	//suffocation icon
	if (inLocker == true) {
		RenderMeshOnScreen(meshList[SUFFOCATION], 6, 50, 2, 2);
	}
	//battery bar
	RenderMeshOnScreen(meshList[GEO_BATTERY], 4.6f + (4.5f - flashlight_lifetime * 0.025f), 6.35f, flashlight_lifetime * 0.05f, 2.1);
	if (showChatbox == true) {
		RenderMeshOnScreen(meshList[GEO_CHATBOX], 40.f, 10.f, 2.f, 0.7f);
	}
	if (nearExit == true) {
		showChatbox = true;
		RenderTextOnScreen(meshList[GEO_TEXT], "Press F to Exit", Color(0.f, 0.f, 1.f), 4.f, 10.f, 1.8f);
	}
	
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
			hammer << "Plier:" << hammerFound;
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
			RenderTextOnScreen(meshList[GEO_TEXT], sparkplug.str(), Color(1, 1, 0), 2.5f, 1.2f, 9.2f);
			modelStack.PopMatrix();

			break;
		}
	case 3:
		if (showSideBox == true) {
			RenderTextOnScreen(meshList[GEO_TEXT], "GET BACK TO CAR AND ESCAPE!", Color(1.f, 1.f, 0.f), 2.8f, 1.2f, 11.7f);
			break;
		}
	}
	//INTERACTIONS
	if (interact)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], interact_message, Color(1, 1, 0), 4, 22, 5);
	}

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
		RenderMeshOnScreen(meshList[GEO_BAR2], 14 - (4.75 - float(suffocationTranslate) * 0.25f), 50, float(suffocationScale) * 0.5f, 1);
	}

	/*std::ostringstream test1;
	test1 << "camera up: " << camera.up;
	RenderTextOnScreen(meshList[GEO_TEXT], test1.str(), Color(0, 1, 0), 4, 0, 6);
	std::ostringstream test3;
	test3 << "camera target: " << camera.target;
	RenderTextOnScreen(meshList[GEO_TEXT], test3.str(), Color(0, 1, 0), 4, 0, 3);
	std::ostringstream test2;
	test2 << "camera view: " << camera.view;
	RenderTextOnScreen(meshList[GEO_TEXT], test2.str(), Color(0, 1, 0), 4, 0, 9);*/

	/*RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(camera.position.x) + " " + std::to_string(camera.position.y) + " " + std::to_string(camera.position.z), Color(0, 1, 0), 4, 0, 3);*/
	if (jumpscareActive1 == true)
	{
		RenderMeshOnScreen(meshList[GEO_JUMPSCARE1], 40, 30, 100, 100);
	}
	//checking
	//std::cout << camera.position.x << std::endl;
	//std::cout << camera.position.z << std::endl;

	//@pause
	//pause menu, place all the way at the bottom in render
	if (gamepaused)
		RenderMeshOnScreen(meshList[GEO_PAUSEMENU], 40, 30, 35, 54);
}

void SceneSP2Room4::Exit()
{
	// Cleanup VBO here
	for (int i = 0; i < 4; i++)
	{
		if (items[i] != nullptr)
		{
			delete items[i];
		}
	}
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


bool SceneSP2Room4::PickUpItem(Item* item)
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
			return false;
		}
	}
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

void SceneSP2Room4::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, int limit)
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




