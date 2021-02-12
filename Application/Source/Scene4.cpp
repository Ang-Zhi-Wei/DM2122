#include "Scene4.h"
#include "GL\glew.h"
#include <stdlib.h>
#include <time.h>
#include "shader.hpp"


Scene4::Scene4()
{
}

Scene4::~Scene4()
{
}


void Scene4::Init()
{
	// Init VBO here
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
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
	//translate
	for (int i = 0; i < 15; i++) {
		switch (i) {
		case 0:
			translateX [i]= -16;
			translateY[i] = 7;
			break;
		case 1:
			translateX[i] = -14;
			translateY[i] = 8;
			break;
		case 2:
			translateX[i] = -12;
			translateY[i] = 9;
			break;
		case 3:
			translateX[i] = -10;
			translateY[i] = 10;
			break;
		case 4:
			translateX[i] = -8;
			translateY[i] = 11;
			break;
		case 5:
			translateX[i] = -6;
			translateY[i] = 12;
			break;
		case 6:
			translateX[i] = -4;
			translateY[i] = 13;
			break;
		case 7:
			translateX[i] = -2;
			translateY[i] = 14;
			break;
		case 8:
			translateX[i] = 0;
			translateY[i] = 15;
			break;
		case 9:
			translateX[i] = 2;
			translateY[i] = 16;
			break;
		case 10:
			translateX[i] = 4;
			translateY[i] = 17;
			break;
		case 11:
			translateX[i] = 6;
			translateY[i] = 18;
			break;
		case 12:
			translateX[i] = -18;
			translateY[i] = 6;
			break;
		case 13:
			translateX[i] = -20;
			translateY[i] = 5;
			break;
		case 14:
			translateX[i] = -22;
			translateY[i] = 4;
			break;
		}
	}
	//thunder
	thunder = false;
	rotateAngle = 0;
	glUseProgram(m_programID);
	//mesh
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1, 1,Red);
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1, 1, 1);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("Quad", 1, 1,Red);
	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("Circle", 1, 1, 1);
	meshList[GEO_RING] = MeshBuilder::Generatering("ring", 1, 1, 1);
	meshList[GEO_HEMISPHERE] = MeshBuilder::Generatehemisphere("hemisphere", 1, 1, 1);
	meshList[GEO_SPHERE] = MeshBuilder::Generatesphere("Sphere", 1, 1, 1,Red);
	
}

void Scene4::Update(double dt)
{
	
	
	//rain
	for (int i = 0; i < 15; i++) {
		switch (i) {
		case 0:
			if (translateY[i] <= -10) {
				translateX[i] = -16;
				translateY[i] = 7;
			}
			else {
				translateX[i] += (float)(15 * dt);
				translateY[i] -= (float)(15 * dt);
			}
			break;
		case 1:
			if (translateY[i] <= -10) {
				translateX[i] = -14;
				translateY[i] = 8;
			}
			else {
				translateX[i] += (float)(15 * dt);
				translateY[i] -= (float)(15 * dt);
			}
			break;
		case 2:
			if (translateY[i] <= -10) {
				translateX[i] = -12;
				translateY[i] = 9;
			}
			else {
				translateX[i] += (float)(15 * dt);
				translateY[i] -= (float)(15 * dt);
			}
			break;
		case 3:
			if (translateY[i] <= -10) {
				translateX[i] = -10;
				translateY[i] = 10;
			}
			else {
				translateX[i] += (float)(15 * dt);
				translateY[i] -= (float)(15 * dt);
			}
			break;
		case 4:
			if (translateY[i] <= -10) {
				translateX[i] = -8;
				translateY[i] = 11;
			}
			else {
				translateX[i] += (float)(15 * dt);
				translateY[i] -= (float)(15 * dt);
			}
			break;
		case 5:
			if (translateY[i] <= -10) {
				translateX[i] = -6;
				translateY[i] = 12;
			}
			else {
				translateX[i] += (float)(15 * dt);
				translateY[i] -= (float)(15 * dt);
			}
			break;
		case 6:
			if (translateY[i] <= -10) {
				translateX[i] = -4;
				translateY[i] = 13;
			}
			else {
				translateX[i] += (float)(15 * dt);
				translateY[i] -= (float)(15 * dt);
			}
			break;
		case 7:
			if (translateY[i] <= -10) {
				translateX[i] = -2;
				translateY[i] = 14;
			}
			else {
				translateX[i] += (float)(15 * dt);
				translateY[i] -= (float)(15 * dt);
			}
			break;
		case 8:
			if (translateY[i] <= -10) {
				translateX[i] = 0;
				translateY[i] = 15;
			}
			else {
				translateX[i] += (float)(15 * dt);
				translateY[i] -= (float)(15 * dt);
			}
			break;
		case 9:
			if (translateY[i] <= -10) {
				translateX[i] = 2;
				translateY[i] = 16;
			}
			else {
				translateX[i] += (float)(15 * dt);
				translateY[i] -= (float)(15 * dt);
			}
			break;
		case 10:
			if (translateY[i] <= -10) {
				translateX[i] = 4;
				translateY[i] = 17;
			}
			else {
				translateX[i] += (float)(15 * dt);
				translateY[i] -= (float)(15 * dt);
			}
			break;
		case 11:
			if (translateY[i] <= -10) {
				translateX[i] = 6;
				translateY[i] = 18;
			}
			else {
				translateX[i] += (float)(15 * dt);
				translateY[i] -= (float)(15 * dt);
			}
			break;
		case 12:
			if (translateY[i] <= -10) {
				translateX[i] = -18;
				translateY[i] = 6;
			}
			else {
				translateX[i] += (float)(15 * dt);
				translateY[i] -= (float)(15 * dt);
			}
			break;
		case 13:
			if (translateY[i] <= -10) {
				translateX[i] = -20;
				translateY[i] = 5;
			}
			else {
				translateX[i] += (float)(15 * dt);
				translateY[i] -= (float)(15 * dt);
			}
			break;
		case 14:
			if (translateX[i] >= -10 && translateX[i] <= -9.8) {
				thunder = true;
			}
			else {
				thunder = false;
			}
			if (translateY[i] <= -10) {
				translateX[i] = -22;
				translateY[i] = 4;
			}
			else {
				translateX[i] += (float)(5 * dt);
				translateY[i] -= (float)(5 * dt);
			}
			break;
		}
	}
	rotateAngle += (float)(180 * dt);
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

void Scene4::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity();
	view.SetToLookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);
	projection.SetToOrtho(-15, 15, -10, 10, -10, 10);
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f,
		1000.0f);
	//Cube
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(rotateAngle, 1, 1, 1);
	translate.SetToTranslation(0, 0, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	meshList[GEO_CUBE]->Render();
	//Axes
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(0, 0, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	meshList[GEO_AXES]->Render();
	//quad 1
	scale.SetToScale(10, 10, 10);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(15, 15, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	meshList[GEO_QUAD]->Render();
	//quad 2
	scale.SetToScale(10, 10, 10);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-15, -15, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	meshList[GEO_QUAD]->Render();
	//circle
	scale.SetToScale(10, 10, 10);
	rotate.SetToRotation(0, 0, 1, 0);
	translate.SetToTranslation(0, -8, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	meshList[GEO_CIRCLE]->Render();
	//ring
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(rotateAngle, 1, 0, 0);
	translate.SetToTranslation(0, 2, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	meshList[GEO_RING]->Render();
	//ring 2
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(rotateAngle, 1, 1, 1);
	translate.SetToTranslation(0, 2, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	meshList[GEO_RING]->Render();
	//ring 3
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(-rotateAngle, 1, 1, 1);
	translate.SetToTranslation(0, 2, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	meshList[GEO_RING]->Render();
	//ring 4
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(-rotateAngle, 1, 0, 0);
	translate.SetToTranslation(0, 2, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	meshList[GEO_RING]->Render();
	//hemisphere
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(0, 20, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	meshList[GEO_HEMISPHERE]->Render();
	//sphere 1
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(-15, 15, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	meshList[GEO_SPHERE]->Render();
	//sphere 2
	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(15, -15, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	meshList[GEO_SPHERE]->Render();
}

void Scene4::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}


