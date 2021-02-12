#include "Assigment1.h"
#include "GL\glew.h"
#include <stdlib.h>
#include <time.h>
#include "shader.hpp"
#include "Camera2.h"

Assigment1::Assigment1()
{
	LSPEED = 10.f;
	//Animation
	movement = false;
	jump = false;
	rotate = false;
	spell = false;
	rotateAngle = 0;
	temp = 0;
	translatex = 0;
	translatez = 0;
	rotatelegs = 0;
	rotatearms = 0;
	rotatehands = 0;
	switchrotate = 1;
	phase = 0;
	for (int i = 0; i < 6; i++) {
		scalering[i] = 1;
	}
	scalering[0] = 1;
	scalering[1] = 2;
	scalering[2] = 6;
	scalesphere = 1;
	switchtranslatey = false;
	translatey = 0;
	LSPEED = 1.5f;
	doublejump == false;
	circlex = 0;
	circley = 0;
	circlez = 0;
}

Assigment1::~Assigment1()
{
}


void Assigment1::Init()
{
	// Init VBO here
	glClearColor(0.529f, 0.808f, 0.922f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	//camera
	camera.Init(Vector3(0, 0, -3), Vector3(translatex, translatey, translatez), Vector3(0, 1,
		0));
	//shaders
	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//LightSource.fragmentshader");
	//...
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
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
	m_parameters[U_LIGHTENABLED] =
		glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID,
		"MVP");
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);
	glUseProgram(m_programID);
	//mesh
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Reference", 1, 1, 1);
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
	meshList[BodyBlack]= MeshBuilder::GenerateCube("Cube", 1, 1, 1, Black);
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
	meshList[Torus] = MeshBuilder::GenerateTorus("Torus", 36,36,1,0.5,Black);
	meshList[Torus]->material.kAmbient.Set(Black);
	//Santa clause
	meshList[HatCone] = MeshBuilder::GenerateCone("Santa Clause", 1, 1, 1, Black);
	meshList[HatCone]->material.kAmbient.Set(Black);
	//HalfCube brown
	meshList[HalfCube] = MeshBuilder::GenerateHalfCube("Weapon part and hair", 1, 1, 1, Brown);
	meshList[HalfCube]->material.kAmbient.Set(Brown);
	//Platform
	meshList[Platform] = MeshBuilder::GenerateQuad("Quad", 1, 1,Green);
	meshList[Platform]->material.kAmbient.Set(Green);
	//orb
	meshList[Orb] = MeshBuilder::Generatesphere("Orb", 1, 1, 1, Red);
	meshList[Orb]->material.kAmbient.Set(Red);
	meshList[Orb]->material.kShininess=1.f;
	//Rings
	meshList[RedRings] = MeshBuilder::Generatering("too much", 1, 1, 1);
	meshList[RedRings]->material.kAmbient.Set(Red);
	//Giant sphere
	meshList[GiantSphere] = MeshBuilder::Generatesphere("ZZZ", 1, 1, 1, Red);
	meshList[GiantSphere]->material.kAmbient.Set(Crimson);
	//spell particles
	meshList[Particlespell] = MeshBuilder::Generatesphere("Special Effects", 1, 1, 1, Crimson);
	meshList[Particlespell]->material.kAmbient.Set(Crimson);
	meshList[Particlespell]->material.kShininess = 255.f;
	//Sky walk
	meshList[circlejump] = MeshBuilder::GenerateCircle("Sky walk", 1, 1, 1);
	//Light
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);
	//Num of lights
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);
	//Animation
	movement = false;
	jump = false;
	rotate = false;
	spell = false;
	rotateAngle = 0;
	translatex = 0;
	translatez = 0;
	rotatelegs = 0;
	rotatearms = 0;
	rotatehands = 0;
	switchrotate = 1;
	increaserotation = 0;
	phase = 0;
	for (int i = 0; i < 6; i++) {
		scalering[i] = 1;
	}
	scalering[0] = 1;
	scalering[1] = 2;
	scalering[2] = 6;
	scalesphere = 1;
	switchtranslatey = false;
	LSPEED = 1.5f;
	for (int i = 0; i < 200; i++) {
		spellparticlex[i] = (rand()%200)-100;
		spellparticley[i] = (rand()%10)-20;
		spellparticleylimit[i] = (rand() % 5);
		spellparticlez[i] = (rand()%200)-100;
	}
}

void Assigment1::Update(double dt)
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
	//Movement Animation
	//forward
    if (Application::IsKeyPressed('I')) {
		movement = true;
	}
	//back
	else if (Application::IsKeyPressed('K')) {
		movement = true;
	}
	else if (Application::IsKeyPressed('J')) {
		movement = true;
	}
	else if (Application::IsKeyPressed('L')) {
		movement = true;
	}
	else {
		movement = false;
	}
	

	//Jumping
	if (jump != true) {
		if (Application::IsKeyPressed('O') && doublejump!=true) {
			jump = true;
		}
	}
	//Double Jumping
	if (doublejump != true) {
		if (Application::IsKeyPressed('O') && jump == true) {
			if (translatey>0.5) {
				jump = false;
				doublejump = true;
				temp = translatey;
				circlex = translatex;
				circley = translatey;
				circlez = translatez;
			}
		}
	}
	
	
	//Spell
	if (spell != true && jump == false && doublejump==false) {
		if (Application::IsKeyPressed('P')) {
			spell = true;
			phase = 1;
		}
	}
	//movement
	if (rotateAngle > 180) {
		rotateAngle = -179;
	}
	else if (rotateAngle < -180) {
		rotateAngle = 179;
	}
	if (movement == true && jump == false && doublejump == false && spell == false) {
		if (camera.horizontalrotation<22.5 && camera.horizontalrotation>-22.5) {
			//I and J
			if (Application::IsKeyPressed('I') && Application::IsKeyPressed('J')) {
				if (rotateAngle < 40 && rotateAngle >= -135) {
					rotateAngle += float(360.f * dt);
				}
				else if ((rotateAngle > 50 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -135)) {
					rotateAngle -= float(360.f * dt);
				}
				translatex += float(1.5f * dt);
				translatez += float(1.5f * dt);
			}
			//I and L
			else if (Application::IsKeyPressed('I') && Application::IsKeyPressed('L')) {
				if (rotateAngle <= 135 && rotateAngle > -40) {
					rotateAngle -= float(360.f * dt);
				}
				else if ((rotateAngle >= 135 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -50)) {
					rotateAngle += float(360.f * dt);
				}
				translatex -= float(1.5f * dt);
				translatez += float(1.5f * dt);
			}
			//K and J
			else if (Application::IsKeyPressed('K') && Application::IsKeyPressed('J')) {
				if (rotateAngle < 130 && rotateAngle >= -45) {
					rotateAngle += float(360.f * dt);
				}
				else if ((rotateAngle > 140 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -45)) {
					rotateAngle -= float(360.f * dt);
				}
				translatex += float(1.5f * dt);
				translatez -= float(1.5f * dt);
			}
			//K and L
			else if (Application::IsKeyPressed('K') && Application::IsKeyPressed('L')) {
				if (rotateAngle <= 45 && rotateAngle > -130) {
					rotateAngle -= float(360.f * dt);
				}
				else if ((rotateAngle >= 45 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -140)) {
					rotateAngle += float(360.f * dt);
				}
				translatex -= float(1.5f * dt);
				translatez -= float(1.5f * dt);
			}
			//I
			else if (Application::IsKeyPressed('I')) {
				if (rotateAngle > 5) {
					rotateAngle -= float(360.f * dt);
				}
				else if (rotateAngle < -5) {
					rotateAngle += float(360.f * dt);
				}
				translatez += float(1.5f * dt);
			}
			//J
			else if (Application::IsKeyPressed('J')) {
				if (rotateAngle < 85 && rotateAngle >= -90) {
					rotateAngle += float(360.f * dt);
				}
				else if ((rotateAngle > 95 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -90)) {
					rotateAngle -= float(360.f * dt);
				}
				translatex += float(1.5f * dt);
			}
			//K
			else if (Application::IsKeyPressed('K')) {
				if (rotateAngle <= 175 && rotateAngle >= 0) {
					rotateAngle += float(360.f * dt);
				}
				else if (rotateAngle >= -175 && rotateAngle <= 0) {
					rotateAngle -= float(360.f * dt);
				}
				translatez -= float(1.5f * dt);
			}
			//L
			else if (Application::IsKeyPressed('L')) {
				if (rotateAngle <= 90 && rotateAngle > -85) {
					rotateAngle -= float(360.f * dt);
				}
				else if ((rotateAngle >= 90 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -95)) {
					rotateAngle += float(360.f * dt);
				}
				translatex -= float(1.5f * dt);
			}
		}	
		else if (camera.horizontalrotation > -67.5 && camera.horizontalrotation < -22.5) {
		//I and J
	    if (Application::IsKeyPressed('I') && Application::IsKeyPressed('J')) {
			if (rotateAngle > 5) {
				rotateAngle -= float(360.f * dt);
			}
			else if (rotateAngle < -5) {
				rotateAngle += float(360.f * dt);
			}
			translatez += float(1.5f * dt);
		}
		//J and K
		else if (Application::IsKeyPressed('J') && Application::IsKeyPressed('K')) {
			if (rotateAngle < 85 && rotateAngle >= -90) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 95 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -90)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
		}
		//K and L
		else if (Application::IsKeyPressed('K') && Application::IsKeyPressed('L')) {
			if (rotateAngle <= 175 && rotateAngle >= 0) {
				rotateAngle += float(360.f * dt);
			}
			else if (rotateAngle >= -175 && rotateAngle <= 0) {
				rotateAngle -= float(360.f * dt);
			}
			translatez -= float(1.5f * dt);
		}
		//L and I
		else if (Application::IsKeyPressed('L') && Application::IsKeyPressed('I')) {
			if (rotateAngle <= 90 && rotateAngle > -85) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 90 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -95)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
		}
			//J
		else if (Application::IsKeyPressed('J')) {
				if (rotateAngle < 40 && rotateAngle >= -135) {
					rotateAngle += float(360.f * dt);
				}
				else if ((rotateAngle > 50 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -135)) {
					rotateAngle -= float(360.f * dt);
				}
				translatex += float(1.5f * dt);
				translatez += float(1.5f * dt);
			}
		//I
		else if (Application::IsKeyPressed('I')) {
			if (rotateAngle <= 135 && rotateAngle > -40) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 135 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -50)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
			translatez += float(1.5f * dt);
		}
		//K
		else if (Application::IsKeyPressed('K')) {
			if (rotateAngle < 130 && rotateAngle >= -45) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 140 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -45)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
			translatez -= float(1.5f * dt);
		}
		//L
		else if (Application::IsKeyPressed('L')) {
			if (rotateAngle <= 45 && rotateAngle > -130) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 45 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -140)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
			translatez -= float(1.5f * dt);
		}
	}
		else if (camera.horizontalrotation > -112.5 && camera.horizontalrotation < -67.5) {
		//K and J
		if (Application::IsKeyPressed('K') && Application::IsKeyPressed('J')) {
			if (rotateAngle < 40 && rotateAngle >= -135) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 50 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -135)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
			translatez += float(1.5f * dt);
		}
		//I and J
		else if (Application::IsKeyPressed('I') && Application::IsKeyPressed('J')) {
			if (rotateAngle <= 135 && rotateAngle > -40) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 135 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -50)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
			translatez += float(1.5f * dt);
		}
		//K and L
		else if (Application::IsKeyPressed('K') && Application::IsKeyPressed('L')) {
			if (rotateAngle < 130 && rotateAngle >= -45) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 140 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -45)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
			translatez -= float(1.5f * dt);
		}
		//I and L
		else if (Application::IsKeyPressed('I') && Application::IsKeyPressed('L')) {
			if (rotateAngle <= 45 && rotateAngle > -130) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 45 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -140)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
			translatez -= float(1.5f * dt);
		}
		//J
		else if (Application::IsKeyPressed('J')) {
			if (rotateAngle > 5) {
				rotateAngle -= float(360.f * dt);
			}
			else if (rotateAngle < -5) {
				rotateAngle += float(360.f * dt);
			}
			translatez += float(1.5f * dt);
		}
		//K
		else if (Application::IsKeyPressed('K')) {
			if (rotateAngle < 85 && rotateAngle >= -90) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 95 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -90)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
		}
		//L
		else if (Application::IsKeyPressed('L')) {
			if (rotateAngle <= 175 && rotateAngle >= 0) {
				rotateAngle += float(360.f * dt);
			}
			else if (rotateAngle >= -175 && rotateAngle <= 0) {
				rotateAngle -= float(360.f * dt);
			}
			translatez -= float(1.5f * dt);
		}
		//I
		else if (Application::IsKeyPressed('I')) {
			if (rotateAngle <= 90 && rotateAngle > -85) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 90 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -95)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
		}
	}
		else if (camera.horizontalrotation > -157.5 && camera.horizontalrotation < -112.5) {
		//K and J
		if (Application::IsKeyPressed('K') && Application::IsKeyPressed('J')) {
			if (rotateAngle > 5) {
				rotateAngle -= float(360.f * dt);
			}
			else if (rotateAngle < -5) {
				rotateAngle += float(360.f * dt);
			}
			translatez += float(1.5f * dt);
		}
		//L and K
		else if (Application::IsKeyPressed('L') && Application::IsKeyPressed('K')) {
			if (rotateAngle < 85 && rotateAngle >= -90) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 95 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -90)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
		}
		//I and L
		else if (Application::IsKeyPressed('I') && Application::IsKeyPressed('L')) {
			if (rotateAngle <= 175 && rotateAngle >= 0) {
				rotateAngle += float(360.f * dt);
			}
			else if (rotateAngle >= -175 && rotateAngle <= 0) {
				rotateAngle -= float(360.f * dt);
			}
			translatez -= float(1.5f * dt);
		}
		//J and I
		else if (Application::IsKeyPressed('J') && Application::IsKeyPressed('I')) {
			if (rotateAngle <= 90 && rotateAngle > -85) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 90 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -95)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
		}
		//K
		else if (Application::IsKeyPressed('K')) {
			if (rotateAngle < 40 && rotateAngle >= -135) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 50 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -135)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
			translatez += float(1.5f * dt);
		}
		//I
		else if (Application::IsKeyPressed('J')) {
			if (rotateAngle <= 135 && rotateAngle > -40) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 135 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -50)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
			translatez += float(1.5f * dt);
		}
		//K
		else if (Application::IsKeyPressed('L')) {
			if (rotateAngle < 130 && rotateAngle >= -45) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 140 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -45)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
			translatez -= float(1.5f * dt);
		}
		//L
		else if (Application::IsKeyPressed('I')) {
			if (rotateAngle <= 45 && rotateAngle > -130) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 45 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -140)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
			translatez -= float(1.5f * dt);
		}
}
		else if ((camera.horizontalrotation > 157.5 && camera.horizontalrotation <= 180) || (camera.horizontalrotation > -157.5 && camera.horizontalrotation <= -180)) {
		//K and L
		if (Application::IsKeyPressed('K') && Application::IsKeyPressed('L')) {
			if (rotateAngle < 40 && rotateAngle >= -135) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 50 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -135)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
			translatez += float(1.5f * dt);
		}
		//K and J
		else if (Application::IsKeyPressed('K') && Application::IsKeyPressed('J')) {
			if (rotateAngle <= 135 && rotateAngle > -40) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 135 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -50)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
			translatez += float(1.5f * dt);
		}
		//I and L
		else if (Application::IsKeyPressed('I') && Application::IsKeyPressed('L')) {
			if (rotateAngle < 130 && rotateAngle >= -45) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 140 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -45)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
			translatez -= float(1.5f * dt);
		}
		//I and J
		else if (Application::IsKeyPressed('I') && Application::IsKeyPressed('J')) {
			if (rotateAngle <= 45 && rotateAngle > -130) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 45 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -140)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
			translatez -= float(1.5f * dt);
		}
		//K
		else if (Application::IsKeyPressed('K')) {
			if (rotateAngle > 5) {
				rotateAngle -= float(360.f * dt);
			}
			else if (rotateAngle < -5) {
				rotateAngle += float(360.f * dt);
			}
			translatez += float(1.5f * dt);
		}
		//L
		else if (Application::IsKeyPressed('L')) {
			if (rotateAngle < 85 && rotateAngle >= -90) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 95 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -90)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
		}
		//I
		else if (Application::IsKeyPressed('I')) {
			if (rotateAngle <= 175 && rotateAngle >= 0) {
				rotateAngle += float(360.f * dt);
			}
			else if (rotateAngle >= -175 && rotateAngle <= 0) {
				rotateAngle -= float(360.f * dt);
			}
			translatez -= float(1.5f * dt);
		}
		//J
		else if (Application::IsKeyPressed('J')) {
			if (rotateAngle <= 90 && rotateAngle > -85) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 90 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -95)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
		}
	}
		else if (camera.horizontalrotation > 112.5 && camera.horizontalrotation < 157.5) {
		//K and L
		if (Application::IsKeyPressed('K') && Application::IsKeyPressed('L')) {
			if (rotateAngle > 5) {
				rotateAngle -= float(360.f * dt);
			}
			else if (rotateAngle < -5) {
				rotateAngle += float(360.f * dt);
			}
			translatez += float(1.5f * dt);
		}
		//I and L
		else if (Application::IsKeyPressed('I') && Application::IsKeyPressed('L')) {
			if (rotateAngle < 85 && rotateAngle >= -90) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 95 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -90)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
		}
		//I and J
		else if (Application::IsKeyPressed('I') && Application::IsKeyPressed('J')) {
			if (rotateAngle <= 175 && rotateAngle >= 0) {
				rotateAngle += float(360.f * dt);
			}
			else if (rotateAngle >= -175 && rotateAngle <= 0) {
				rotateAngle -= float(360.f * dt);
			}
			translatez -= float(1.5f * dt);
		}
		//K and J
		else if (Application::IsKeyPressed('K') && Application::IsKeyPressed('J')) {
			if (rotateAngle <= 90 && rotateAngle > -85) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 90 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -95)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
		}
		//L
		else if (Application::IsKeyPressed('L')) {
			if (rotateAngle < 40 && rotateAngle >= -135) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 50 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -135)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
			translatez += float(1.5f * dt);
		}
		//K
		else if (Application::IsKeyPressed('K')) {
			if (rotateAngle <= 135 && rotateAngle > -40) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 135 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -50)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
			translatez += float(1.5f * dt);
		}
		//I
		else if (Application::IsKeyPressed('I')) {
			if (rotateAngle < 130 && rotateAngle >= -45) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 140 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -45)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
			translatez -= float(1.5f * dt);
		}
		//J
		else if (Application::IsKeyPressed('J')) {
			if (rotateAngle <= 45 && rotateAngle > -130) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 45 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -140)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
			translatez -= float(1.5f * dt);
		}
	}
		else if (camera.horizontalrotation > 67.5 && camera.horizontalrotation < 112.5) {
		//I and L
		if (Application::IsKeyPressed('I') && Application::IsKeyPressed('L')) {
			if (rotateAngle < 40 && rotateAngle >= -135) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 50 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -135)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
			translatez += float(1.5f * dt);
		}
		//K and L
		else if (Application::IsKeyPressed('K') && Application::IsKeyPressed('L')) {
			if (rotateAngle <= 135 && rotateAngle > -40) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 135 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -50)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
			translatez += float(1.5f * dt);
		}
		//I and J
		else if (Application::IsKeyPressed('I') && Application::IsKeyPressed('J')) {
			if (rotateAngle < 130 && rotateAngle >= -45) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 140 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -45)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
			translatez -= float(1.5f * dt);
		}
		//K and J
		else if (Application::IsKeyPressed('K') && Application::IsKeyPressed('J')) {
			if (rotateAngle <= 45 && rotateAngle > -130) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 45 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -140)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
			translatez -= float(1.5f * dt);
		}
		//L
		else if (Application::IsKeyPressed('L')) {
			if (rotateAngle > 5) {
				rotateAngle -= float(360.f * dt);
			}
			else if (rotateAngle < -5) {
				rotateAngle += float(360.f * dt);
			}
			translatez += float(1.5f * dt);
		}
		//I
		else if (Application::IsKeyPressed('I')) {
			if (rotateAngle < 85 && rotateAngle >= -90) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 95 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -90)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
		}
		//J
		else if (Application::IsKeyPressed('J')) {
			if (rotateAngle <= 175 && rotateAngle >= 0) {
				rotateAngle += float(360.f * dt);
			}
			else if (rotateAngle >= -175 && rotateAngle <= 0) {
				rotateAngle -= float(360.f * dt);
			}
			translatez -= float(1.5f * dt);
		}
		//K
		else if (Application::IsKeyPressed('K')) {
			if (rotateAngle <= 90 && rotateAngle > -85) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 90 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -95)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
		}
	}
		else if (camera.horizontalrotation > 22.5 && camera.horizontalrotation < 67.5) {
		//I and L
		if (Application::IsKeyPressed('I') && Application::IsKeyPressed('L')) {
			if (rotateAngle > 5) {
				rotateAngle -= float(360.f * dt);
			}
			else if (rotateAngle < -5) {
				rotateAngle += float(360.f * dt);
			}
			translatez += float(1.5f * dt);
		}
		//I and J
		else if (Application::IsKeyPressed('J') && Application::IsKeyPressed('I')) {
			if (rotateAngle < 85 && rotateAngle >= -90) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 95 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -90)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
		}
		//K and J
		else if (Application::IsKeyPressed('K') && Application::IsKeyPressed('J')) {
			if (rotateAngle <= 175 && rotateAngle >= 0) {
				rotateAngle += float(360.f * dt);
			}
			else if (rotateAngle >= -175 && rotateAngle <= 0) {
				rotateAngle -= float(360.f * dt);
			}
			translatez -= float(1.5f * dt);
		}
		//L and K
		else if (Application::IsKeyPressed('L') && Application::IsKeyPressed('K')) {
			if (rotateAngle <= 90 && rotateAngle > -85) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 90 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -95)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
		}
		//I
		else if (Application::IsKeyPressed('I')) {
			if (rotateAngle < 40 && rotateAngle >= -135) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 50 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -135)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
			translatez += float(1.5f * dt);
		}
		//L
		else if (Application::IsKeyPressed('L')) {
			if (rotateAngle <= 135 && rotateAngle > -40) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 135 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -50)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
			translatez += float(1.5f * dt);
		}
		//J
		else if (Application::IsKeyPressed('J')) {
			if (rotateAngle < 130 && rotateAngle >= -45) {
				rotateAngle += float(360.f * dt);
			}
			else if ((rotateAngle > 140 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle <= -45)) {
				rotateAngle -= float(360.f * dt);
			}
			translatex += float(1.5f * dt);
			translatez -= float(1.5f * dt);
		}
		//K
		else if (Application::IsKeyPressed('K')) {
			if (rotateAngle <= 45 && rotateAngle > -130) {
				rotateAngle -= float(360.f * dt);
			}
			else if ((rotateAngle >= 45 && rotateAngle <= 180) || (rotateAngle >= -180 && rotateAngle < -140)) {
				rotateAngle += float(360.f * dt);
			}
			translatex -= float(1.5f * dt);
			translatez -= float(1.5f * dt);
		}
	}
}

	
	
	//rotation of legs and arms
	if (movement == true && jump == false && doublejump==false && spell == false) {
		switch (switchrotate) {
		case 1:
			if (rotatelegs < 2) {
				rotatelegs += float(20.f * dt);
				rotatearms += float(400.f * dt);
				
			}
			else {
				switchrotate = 2;
			}
			break;
		case 2:
			if (rotatelegs > -2 ) {
				rotatelegs -= float(20.f * dt);
				rotatearms -= float(400.f * dt);
			}
			else {
				switchrotate = 1;
			}
			break;
		}
	}
	else {
			rotatelegs = 0;
			rotatearms = 0;
	}


	//Jump
	if (jump == true&& doublejump==false && spell == false) {
		if (switchtranslatey == false) {
			translatey += float(4.f * dt);
			increaserotation += float(600.f * dt);
			rotatearms = increaserotation;
		}
		else if (switchtranslatey == true) {
			translatey -= float(4.f * dt);
			increaserotation -= float(600.f * dt);
			rotatearms = increaserotation;
			if (translatey <= 0) {
				translatey = 0;
				jump = false;
				increaserotation = 0;
				switchtranslatey = false;
			}
		}
		if (translatey >= 1) {
			switchtranslatey = true;
		}
	}
	else if (jump == false && doublejump == true && spell == false) {
		if (switchtranslatey == false) {
			translatey += float(8.f * dt);
			increaserotation += float(600.f * dt);
			rotatearms = increaserotation;
			if (rotatearms > 90) {
				rotatearms = 90;
			}
			rotateAngle += float(1440.f * dt);
		}
		else if (switchtranslatey == true) {
			translatey -= float(6.f * dt);
			increaserotation -= float(600.f * dt);
			rotatearms = increaserotation;
			if (rotatearms < 0) {
				rotatearms = 0;
			}
			if (translatey <= 0) {
				translatey = 0;
				doublejump = false;
				increaserotation = 0;
				switchtranslatey = false;
			}
		}
		if (translatey>temp+2) {
			switchtranslatey = true;
		}
	}
	//spell
	if (spell == true) {
		rotatearms = 0;
		switch (phase) {
		case 1:
			light[0].type = Light::LIGHT_SPOT;
			light[0].position.Set(translatex, 5, translatez);
			glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
			glClearColor(0.663f, 0.663f, 0.663f, 0.f);
			rotatehands = 90;
			increaserotation += float(80.f * dt);
			rotatearms = increaserotation;
			for (int i = 0; i < 200; i++) {
				spellparticley[i] += float(5.f * dt);
				if (spellparticley[i] >= spellparticleylimit[i]) {
					spellparticley[i] = (rand() % 10) - 20;
				}
			}
			if (rotatearms > 90) {
				rotatearms = 90;
				phase = 2;
			}
			break;
		case 2:
			scalering[0] += float(1.f*dt);
			rotatearms = 90;
			rotatehands = 90;
			for (int i = 0; i < 200; i++) {
				spellparticley[i] += float(5.f * dt);
				if (spellparticley[i] >= spellparticleylimit[i]) {
					spellparticley[i] = (rand() % 10) - 20;
				}
			}
			if (scalering[0] > 2) {
				scalering[0] = 2;
				phase = 3;
			}
			break;
		case 3:
			scalering[1] += float(1.5f * dt);
			rotatearms = 90;
			rotatehands = 90;
			for (int i = 0; i < 200; i++) {
				spellparticley[i] += float(5.f * dt);
				if (spellparticley[i] >= spellparticleylimit[i]) {
					spellparticley[i] = (rand() % 10) - 20;
				}
			}
			if (scalering[1] > 6) {
				scalering[1] = 6;
				phase = 4;
			}
			break;
		case 4:
			scalering[2] += float(2.f * dt);
			rotatearms = 90;
			rotatehands = 90;
			for (int i = 0; i < 200; i++) {
				spellparticley[i] += float(5.f * dt);
				if (spellparticley[i] >= spellparticleylimit[i]) {
					spellparticley[i] = (rand() % 10) - 20;
				}
			}
			if (scalering[2] > 14) {
				scalering[2] = 14;
				phase = 5;
			}
			break;
		case 5:
			rotatearms = 90;
			rotatehands = 90;
			scalering[3] += float(2.5f * dt);
			scalering[4] += float(2.5f * dt);
			scalering[5] += float(2.5f * dt);
			for (int i = 0; i < 200; i++) {
				spellparticley[i] += float(5.f * dt);
				if (spellparticley[i] >= spellparticleylimit[i]) {
					spellparticley[i] = (rand() % 10) - 20;
				}
			}
			if (scalering[3] > 12.5) {
				scalering[3] = 12.5;
			}
			if (scalering[4] > 25) {
				scalering[4] = 25;
				phase = 6;
			}
			if (scalering[5] > 12.5) {
				scalering[5] = 12.5;
			}
			break;
		case 6:
			increaserotation -= float(80.f * dt);
			rotatearms = increaserotation;
			if (rotatearms <= 0) {
				rotatearms = 0;
			}
			if (scalering[3] > 1) {
				scalering[3] -= float(5.f * dt);
			}
			if (scalering[4] > 1) {
				scalering[4] -= float(10.f * dt);
			}
			else {
				phase=7;
			}
			if (scalering[5] > 1) {
				scalering[5] -= float(5.f * dt);
			}
			break;
		case 7:
			light[0].type = Light::LIGHT_POINT;
			light[0].position.Set(translatex, 5, translatez);
			light[0].power = 10;
			glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
			glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
			if (scalesphere >= 100) {
				scalesphere += float(40.f * dt);
			}
			else {
				scalesphere += float(200.f * dt);
			}
			if (scalesphere > 400) {
				scalesphere = 400;
				phase = 0;
			}
			break;
		default:
			light[0].type = Light::LIGHT_DIRECTIONAL;
			light[0].position.Set(0, 20, 0);
			light[0].power = 1;
			glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
			glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
			glClearColor(0.529f, 0.808f, 0.922f, 0.0f);
			scalering[0] = 1;
			scalering[1] = 2;
			scalering[2] = 6;
			scalesphere = 1;
			rotatearms = 0;
			increaserotation = 0;
			spell = false;
			for (int i = 0; i < 200; i++) {
				spellparticlex[i] = (rand() % 200) - 100;
				spellparticley[i] = (rand() % 10) - 20;
				spellparticleylimit[i] = (rand() % 5);
				spellparticlez[i] = (rand() % 200) - 100;
			}
		}
	}
	//camera
	camera.Update(dt);
	camera.AnimationStatus(jump, spell,doublejump);
	//reset
	if (Application::IsKeyPressed('R')) {
		movement = false;
		jump = false;
		rotate = false;
		spell = false;
		rotateAngle = 0;
		translatex = 0;
		translatey = 0;
		translatez = 0;
		rotatelegs = 0;
		rotatearms = 0;
		rotatehands = 0;
		switchrotate = 1;
		phase = 0;
		for (int i = 0; i < 6; i++) {
			scalering[i] = 1;
		}
		scalering[0] = 1;
		scalering[1] = 2;
		scalering[2] = 6;
		scalesphere = 1;
		increaserotation = 0;
		switchtranslatey = false;
		LSPEED = 1.5f;
		light[0].type = Light::LIGHT_DIRECTIONAL;
		light[0].position.Set(0, 20, 0);
		light[0].power = 1;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
		glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
		glClearColor(0.529f, 0.808f, 0.922f, 0.0f);
		for (int i = 0; i < 200; i++) {
			spellparticlex[i] = (rand() % 200) - 100;
			spellparticley[i] = (rand() % 10) - 20;
			spellparticleylimit[i] = (rand() % 5);
			spellparticlez[i] = (rand() % 200) - 100;
		}
	}
}

void Assigment1::Render()
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
	//Light
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
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}
	//Axes
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	RenderMesh(meshList[GEO_AXES], false);
	modelStack.PopMatrix();
	//Platform
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(1000, 1, 1000);
	RenderMesh(meshList[Platform], true);
	modelStack.PopMatrix();
	//core
	modelStack.PushMatrix();
	modelStack.Translate(translatex, translatey, translatez);
	modelStack.Rotate(rotateAngle, 0, 1, 0);
	modelStack.Scale(0.1f, 0.1f, 0.1f);
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
		//Top of the body connecting to arm and head
		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 0);
		modelStack.Scale(2.5f, 2.5f, 2.5f);
		RenderMesh(meshList[BodyRed], true);
			//Left arm
			modelStack.PushMatrix();
			modelStack.Translate(-0.75f, -0.2f, 0.f);
			modelStack.Scale(0.2f, 0.2f, 0.2f);
			modelStack.Rotate(-60, 0, 0, 1);
			modelStack.Rotate(-rotatearms , 1, 0, 0);
			RenderMesh(meshList[Arm], true);
				//left Hand connecting to weapon
				modelStack.PushMatrix();
				modelStack.Translate(0, -2.6f, 0);
				modelStack.Rotate(rotatehands, 0, 1, 0);
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
			if (jump == true ||spell==true) {
				rotatearms = -rotatearms;
			}
			modelStack.Rotate(rotatearms, 1, 0, 0);
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
		modelStack.Translate(0, 0.65f, 0.501f);
		modelStack.Scale(1, 1, 1.5f);
		RenderMesh(meshList[BodyYellow], true);
		modelStack.PopMatrix();
		//Body2
		modelStack.PushMatrix();
		modelStack.Translate(0, -1.40f, 0);
		modelStack.Scale(3, 0.3f, 2.6f);
		RenderMesh(meshList[BodyBrown], true);
		modelStack.PopMatrix();
		//Silver
		modelStack.PushMatrix();
		modelStack.Translate(0, -1.401f, 0.801f);
		modelStack.Scale(1, 0.3f, 1.0f);
		RenderMesh(meshList[BodySilver], true);
		modelStack.PopMatrix();
		//Body 3
		modelStack.PushMatrix();
		modelStack.Translate(0, -1.70f, 0);
		modelStack.Scale(3, 0.3f, 2.6f);
		RenderMesh(meshList[BodyRed], true);
		modelStack.PopMatrix();
		//Body 4
		modelStack.PushMatrix();
		modelStack.Translate(0, -2, 0);
		modelStack.Scale(3, 0.3f, 2.6f);
		RenderMesh(meshList[BodyYellow], true);
		modelStack.PopMatrix();
		//Bottom of body connecting to legs
		modelStack.PushMatrix();
		modelStack.Translate(0, -2.24f, 0);
		modelStack.Scale(3, 0.15f, 2.6f);
		RenderMesh(meshList[BodyRed], true);
		//Left leg
			modelStack.PushMatrix();
			modelStack.Translate(-0.2f, -5, 0);
			modelStack.Rotate(rotatelegs, 1, 0, 0);
			modelStack.Scale(0.15f, 4, 0.15f);
			RenderMesh(meshList[Leg], true);
			modelStack.PopMatrix();
			//Right leg
			modelStack.PushMatrix();
			modelStack.Translate(0.2f, -5, 0);
			modelStack.Rotate(-rotatelegs, 1, 0, 0);
			modelStack.Scale(0.15f, 4, 0.15f);
			RenderMesh(meshList[Leg], true);
			modelStack.PopMatrix();
		modelStack.PopMatrix();
		//Animation
		if (spell == true) {
			switch (phase) {
			case 2:
				//ring 1
				modelStack.PushMatrix();
				modelStack.Translate(0, -3.8f, 0);
				modelStack.Scale(scalering[0], 1, scalering[0]);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				break;
			case 3:
				//ring 1
				modelStack.PushMatrix();
				modelStack.Translate(0, -3.8f, 0);
				modelStack.Scale(2, 1, 2);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				//ring 2
				modelStack.PushMatrix();
				modelStack.Translate(0, -3.8f, 0);
				modelStack.Scale(scalering[1], 1, scalering[1]);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				break;
			case 4:
				//ring 1
				modelStack.PushMatrix();
				modelStack.Translate(0, -3.8f, 0);
				modelStack.Scale(2, 1, 2);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				//ring 2
				modelStack.PushMatrix();
				modelStack.Translate(0, -3.8f, 0);
				modelStack.Scale(6, 1, 6);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				//ring 3
				modelStack.PushMatrix();
				modelStack.Translate(0, -3.8f, 0);
				modelStack.Scale(scalering[2], 1, scalering[2]);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				break;
			case 5:
				//ring 1
				modelStack.PushMatrix();
				modelStack.Translate(0, -3.8f, 0);
				modelStack.Scale(2, 1, 2);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				//ring 2
				modelStack.PushMatrix();
				modelStack.Translate(0, -3.8f, 0);
				modelStack.Scale(6, 1, 6);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				//ring 3
				modelStack.PushMatrix();
				modelStack.Translate(0, -3.8f, 0);
				modelStack.Scale(14, 1, 14);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				//ring 4
				modelStack.PushMatrix();
				modelStack.Translate(0, 50.f, 450.f);
				modelStack.Rotate(180, 1, 0, 0);
				modelStack.Scale(scalering[3], 1, scalering[3]);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(0, 50.f, 450.f);
				modelStack.Scale(scalering[3], 1, scalering[3]);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				//ring 5
				modelStack.PushMatrix();
				modelStack.Translate(0, 100, 450);
				modelStack.Rotate(180, 1, 0, 0);
				modelStack.Scale(scalering[4], 1, scalering[4]);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(0, 100, 450);
				modelStack.Scale(scalering[4], 1, scalering[4]);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				//ring 6
				modelStack.PushMatrix();
				modelStack.Translate(0, 150, 450);
				modelStack.Rotate(180, 1, 0, 0);
				modelStack.Scale(scalering[5], 1, scalering[5]);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(0, 150, 450);
				modelStack.Scale(scalering[5], 1, scalering[5]);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				break;
			case 6:
				//ring 4
				modelStack.PushMatrix();
				modelStack.Translate(0, 50, 450);
				modelStack.Rotate(180, 1, 0, 0);
				modelStack.Scale(scalering[3], 1, scalering[3]);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(0, 50, 450);
				modelStack.Scale(scalering[3], 1, scalering[3]);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				//ring 5
				modelStack.PushMatrix();
				modelStack.Translate(0, 100, 450);
				modelStack.Rotate(180, 1, 0, 0);
				modelStack.Scale(scalering[4], 1, scalering[4]);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(0, 100, 450);
				modelStack.Scale(scalering[4], 1, scalering[4]);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				//ring 6
				modelStack.PushMatrix();
				modelStack.Translate(0, 150, 450);
				modelStack.Rotate(180, 1, 0, 0);
				modelStack.Scale(scalering[5], 1, scalering[5]);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(0, 150, 450);
				modelStack.Scale(scalering[5], 1, scalering[5]);
				RenderMesh(meshList[RedRings], true);
				modelStack.PopMatrix();
				break;
			case 7:
				//Giant Sphere
				modelStack.PushMatrix();
				modelStack.Translate(0, 100, 450);
				modelStack.Scale(scalesphere, scalesphere, scalesphere);
				RenderMesh(meshList[GiantSphere], true);
				modelStack.PopMatrix();
				break;
			}
		//particle
		if (spell == true && phase<6) {
			for (int i = 0; i < 200; i++) {
				modelStack.PushMatrix();
				modelStack.Translate(spellparticlex[i], spellparticley[i], spellparticlez[i]);
				RenderMesh(meshList[Particlespell], false);
				modelStack.PopMatrix();
			}
		}
			
			
		
		}
	modelStack.PopMatrix();
	//sky walk
	if (doublejump == true && switchtranslatey==false) {
		modelStack.PushMatrix();
		modelStack.Translate(circlex, circley, circlez);
		RenderMesh(meshList[circlejump], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(circlex, circley, circlez);
		modelStack.Rotate(180, 1, 0, 0);
		RenderMesh(meshList[circlejump], true);
		modelStack.PopMatrix();
	}
	//light
	Position lightPosition_cameraspace = viewStack.Top() *
		light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1,
		&lightPosition_cameraspace.x);
}
void Assigment1::RenderMesh(Mesh* mesh, bool enableLight)
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
	mesh->Render();
}



void Assigment1::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}




