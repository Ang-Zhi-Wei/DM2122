#include "Scene5.h"
#include "GL\glew.h"
#include <stdlib.h>
#include <time.h>
#include "shader.hpp"


Scene5::Scene5()
{
}

Scene5::~Scene5()
{
}


void Scene5::Init()
{
	// Init VBO here
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	//camera
	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1,
		0));
	//shaders
	m_programID = LoadShaders(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID,
		"MVP");
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);
	glUseProgram(m_programID);
	//mesh
	meshList[Sun] = MeshBuilder::Generatesphere("Sphere", 1, 1, 1,Yellow);
	meshList[Planet1] = MeshBuilder::Generatesphere("Sphere", 1, 1, 1, Blue);
	meshList[Planet2] = MeshBuilder::Generatesphere("Sphere", 1, 1, 1, Purple);
	meshList[Planet3] = MeshBuilder::Generatesphere("Sphere", 1, 1, 1, Orange);
	meshList[Planet4] = MeshBuilder::Generatesphere("Sphere", 1, 1, 1, Green);
	meshList[Planet5] = MeshBuilder::Generatesphere("Sphere", 1, 1, 1, Purple);
	meshList[Planet6] = MeshBuilder::Generatesphere("Sphere", 1, 1, 1, Blue);
	meshList[Ring] = MeshBuilder::Generatering("Ring", 1, 1, 1);
	meshList[Moon] = MeshBuilder::Generatesphere("Sphere", 1, 1, 1, Gray);
	meshList[Moon2] = MeshBuilder::Generatesphere("Sphere", 1, 1, 1, Gray);
}

void Scene5::Update(double dt)
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
	//camera
	camera.Update(dt);

}

void Scene5::Render()
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
	//Sun
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(rotateAngle, 0, 1, 0);
	MVP = projectionStack.Top() * viewStack.Top() *
		modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[Sun]->Render();
		//Planet 4
		modelStack.PushMatrix();
		modelStack.Translate(-5, 3, 7);
		modelStack.Rotate(52, 1, 0, 0);
		modelStack.Rotate(rotateAngle / 2.0f, 0, 1, 0);
		modelStack.Scale(0.5, 0.5, 0.5);
		MVP = projectionStack.Top() * viewStack.Top() *
			modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		meshList[Planet4]->Render();
			//Ring
			modelStack.PushMatrix();
			MVP = projectionStack.Top() * viewStack.Top() *
				modelStack.Top();
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
			meshList[Ring]->Render();
			modelStack.PopMatrix();
		modelStack.PopMatrix();
		//planet 5
		modelStack.PushMatrix();
		modelStack.Translate(30, -7, 30);
		modelStack.Rotate(-20, 1, 0, 0);
		modelStack.Rotate(rotateAngle / 0.3f, 0, 1, 0);
		modelStack.Scale(3, 3, 3);
		MVP = projectionStack.Top() * viewStack.Top() *
			modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		meshList[Planet5]->Render();
		   //Moon 1
			modelStack.PushMatrix();
			modelStack.Translate(15, 0, 0);
			modelStack.Scale(0.2, 0.2, 0.2);
			MVP = projectionStack.Top() * viewStack.Top() *
				modelStack.Top();
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
			meshList[Moon]->Render();
			modelStack.PopMatrix();
		modelStack.PopMatrix();
		//planet 6
		modelStack.PushMatrix();
		modelStack.Translate(45, -2, -32);
		modelStack.Rotate(12, 1, 0, 0);
		modelStack.Rotate(rotateAngle / 0.8f, 0, 1, 0);
		modelStack.Scale(1.5, 1.5, 1.5);
		MVP = projectionStack.Top() * viewStack.Top() *
			modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		meshList[Planet6]->Render();
		//Moon 1
			modelStack.PushMatrix();
			modelStack.Translate(15, 0, 0);
			modelStack.Scale(0.4, 0.4, 0.4);
			MVP = projectionStack.Top() * viewStack.Top() *
				modelStack.Top();
			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
			meshList[Moon]->Render();
			modelStack.PopMatrix();
		modelStack.PopMatrix();;
	modelStack.PopMatrix();
	//rotate other way
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(-rotateAngle, 0, 1, 0);
	MVP = projectionStack.Top() * viewStack.Top() *
		modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[Sun]->Render();
	//planet 1
	modelStack.PushMatrix();
	modelStack.Translate(20, 10, 20);
	modelStack.Rotate(rotateAngle, 0, 1, 0);
	MVP = projectionStack.Top() * viewStack.Top() *
		modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[Planet1]->Render();
	modelStack.PopMatrix();
	//Planet 2
	modelStack.PushMatrix();
	modelStack.Translate(-20, -5, -20);
	modelStack.Rotate(36, 1, 0, 0);
	modelStack.Rotate(rotateAngle / 2.0f, 0, 1, 0);
	MVP = projectionStack.Top() * viewStack.Top() *
		modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[Planet2]->Render();
	modelStack.PopMatrix();
	//Planet 3
	modelStack.PushMatrix();
	modelStack.Translate(5, -5, 17);
	modelStack.Rotate(-20, 1, 0, 0);
	modelStack.Rotate(rotateAngle / 0.5f, 0, 1, 0);
	modelStack.Scale(0.5, 0.5, 0.5);
	MVP = projectionStack.Top() * viewStack.Top() *
		modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[Planet3]->Render();
	modelStack.PopMatrix();

}

void Scene5::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}


