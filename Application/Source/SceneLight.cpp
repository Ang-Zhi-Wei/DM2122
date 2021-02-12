#include "SceneLight.h"
#include "GL\glew.h"
#include <stdlib.h>
#include <time.h>
#include "shader.hpp"


SceneLight::SceneLight()
{
}

SceneLight::~SceneLight()
{
}


void SceneLight::Init()
{
	// Init VBO here
	glClearColor(0.529f, 0.808f, 0.922f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	//camera
	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1,
		0));
	//shaders
	m_programID = LoadShaders("Shader//Shading.vertexshader",
		"Shader//Shading.fragmentshader");
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
	projection.SetToPerspective(46.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);
	glUseProgram(m_programID);
	//mesh
	meshList[Sphere] = MeshBuilder::Generatesphere("Sphere 1", 1, 1, 1, Blue);
	meshList[Sphere]->material.kAmbient.Set(Red);
	meshList[Sphere]->material.kDiffuse.Set(0.3f, 0.3f, 0.3f);
	meshList[Sphere]->material.kSpecular.Set(0.6f, 0.6f, 0.6f);
	meshList[Sphere]->material.kShininess = 1.f;
	meshList[LightSphere] = MeshBuilder::Generatesphere("LightBall", 1, 1, 1, Red);
	meshList[Quad] = MeshBuilder::GenerateQuad("Floor", 1, 1,Red);
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Reference", 1, 1, 1);
	//light
	light[0].position.Set(0, 5, 0);
	light[0].color.Set(Blue);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	// Make sure you pass uniform parameters after glUseProgram()
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1,
		&light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	//init update stuff
	LSPEED = 10.F;
	
}

void SceneLight::Update(double dt)
{
	
	
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
	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);
	//camera
	camera.Update(dt);

}

void SceneLight::Render()
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
	//1
	modelStack.PushMatrix();
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[Sphere], true);
	modelStack.PopMatrix();
	//2
	modelStack.PushMatrix();
	modelStack.Translate(-2, 0, -2);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[Sphere], true);
	modelStack.PopMatrix();
	//3
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -2);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[Sphere], true);
	modelStack.PopMatrix();
	//4
	modelStack.PushMatrix();
	modelStack.Translate(-2, 0, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[Sphere], true);
	modelStack.PopMatrix();
	//5
	modelStack.PushMatrix();
	modelStack.Translate(2, 0, 2);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[Sphere], true);
	modelStack.PopMatrix();
	//6
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 2);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[Sphere], true);
	modelStack.PopMatrix();
	//7
	modelStack.PushMatrix();
	modelStack.Translate(2, 0, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[Sphere], true);
	modelStack.PopMatrix();
	//8
	modelStack.PushMatrix();
	modelStack.Translate(2, 0, -2);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[Sphere], true);
	modelStack.PopMatrix();
	//9
	modelStack.PushMatrix();
	modelStack.Translate(-2, 0, 2);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[Sphere], true);
	modelStack.PopMatrix();
	RenderMesh(meshList[GEO_AXES], false);
	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y,
		light[0].position.z);
	modelStack.Scale(0.5, 0.5, 0.5);
	RenderMesh(meshList[LightSphere], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[Quad], true);
	modelStack.PopMatrix();

}

void SceneLight::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneLight::RenderMesh(Mesh* mesh, bool enableLight)
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
	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	mesh->Render();
}


