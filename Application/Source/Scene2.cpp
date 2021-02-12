#include "Scene2.h"
#include "GL\glew.h"
#include <stdlib.h>
#include <time.h>
#include "shader.hpp"


Scene2::Scene2()
{
}

Scene2::~Scene2()
{
}


void Scene2::Init()
{
	// Init VBO here
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	//object 1
	static const GLfloat vertex_buffer_data[] = {
		0.0f,-0.5f,0.0f,//triangle 1
		0.0f,0.5f,0.0f,
		-0.8f,0.0f,0.0f,
		0.0f,-0.5f,0.0f,//triangle 2
		0.0f,0.5f,0.0f,
		0.8f,0.0f,0.0f,
		-0.5f,0.0f,0.0f,//triangle 2
		0.5f,0.0f,0.0f,
		0.0f,0.8f,0.0f,
		-0.5f,0.0f,0.0f,//triangle 2
		0.5f,0.0f,0.0f,
		0.0f,-0.8f,0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data),
		vertex_buffer_data, GL_STATIC_DRAW);
	static const GLfloat color_buffer_data[] = {
		0.7f,0.0f,0.0f,
		0.0f,0.8f,0.0f,
		0.0f,0.0f,0.5f,
		0.7f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.5f,
		0.7f,0.3f,0.0f,
		0.0f,0.8f,0.0f,
		0.0f,0.0f,0.5f,
		0.7f,0.0f,0.0f,
		0.0f,0.8f,0.0f,
		0.0f,0.0f,0.5f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data),
		color_buffer_data, GL_STATIC_DRAW);
	//Object 2
	static const GLfloat vertex_buffer_data2[] = {
	0.0f,-0.5f,0.0f,//triangle 1
	0.0f,0.5f,0.0f,
	-0.8f,0.0f,0.0f,
	0.0f,-0.5f,0.0f,//triangle 2
	0.0f,0.5f,0.0f,
	0.8f,0.0f,0.0f,
	-0.5f,0.0f,0.0f,//triangle 2
	0.5f,0.0f,0.0f,
	0.0f,0.8f,0.0f,
	-0.5f,0.0f,0.0f,//triangle 2
	0.5f,0.0f,0.0f,
	0.0f,-0.8f,0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data),
		vertex_buffer_data, GL_STATIC_DRAW);
	static const GLfloat color_buffer_data2[] = {
		0.7f,0.0f,0.0f,
		0.0f,0.8f,0.0f,
		0.0f,0.0f,0.5f,
		0.7f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.5f,
		0.7f,0.3f,0.0f,
		0.0f,0.8f,0.0f,
		0.0f,0.0f,0.5f,
		0.7f,0.0f,0.0f,
		0.0f,0.8f,0.0f,
		0.0f,0.0f,0.5f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2),
		color_buffer_data2, GL_STATIC_DRAW);
	//Object 3
	static const GLfloat vertex_buffer_data3[] = {
	0.0f,-0.5f,0.0f,//triangle 1
	0.0f,0.5f,0.0f,
	-0.8f,0.0f,0.0f,
	0.0f,-0.5f,0.0f,//triangle 2
	0.0f,0.5f,0.0f,
	0.8f,0.0f,0.0f,
	-0.5f,0.0f,0.0f,//triangle 3
	0.5f,0.0f,0.0f,
	0.0f,0.8f,0.0f,
	-0.5f,0.0f,0.0f,//triangle 4
	0.5f,0.0f,0.0f,
	0.0f,-0.8f,0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data3),
		vertex_buffer_data, GL_STATIC_DRAW);
	static const GLfloat color_buffer_data3[] = {
		0.7f,0.0f,0.0f,
		0.0f,0.8f,0.0f,
		0.0f,0.0f,0.5f,
		0.7f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.5f,
		0.7f,0.3f,0.0f,
		0.0f,0.8f,0.0f,
		0.0f,0.0f,0.5f,
		0.7f,0.0f,0.0f,
		0.0f,0.8f,0.0f,
		0.0f,0.0f,0.5f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data3),
		color_buffer_data3, GL_STATIC_DRAW);
	//Object 4
	static const GLfloat vertex_buffer_data4[] = {
	0.0f,-0.5f,0.0f,//triangle 1
	0.0f,0.5f,0.0f,
	-0.8f,0.0f,0.0f,
	0.0f,-0.5f,0.0f,//triangle 2
	0.0f,0.5f,0.0f,
	0.8f,0.0f,0.0f,
	-0.5f,0.0f,0.0f,//triangle 3
	0.5f,0.0f,0.0f,
	0.0f,0.8f,0.0f,
	-0.5f,0.0f,0.0f,//triangle 4
	0.5f,0.0f,0.0f,
	0.0f,-0.8f,0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data4),
		vertex_buffer_data4, GL_STATIC_DRAW);
	static const GLfloat color_buffer_data4[] = {
		0.7f,0.0f,0.0f,
		0.0f,0.8f,0.0f,
		0.0f,0.0f,0.5f,
		0.7f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.5f,
		0.7f,0.3f,0.0f,
		0.0f,0.8f,0.0f,
		0.0f,0.0f,0.5f,
		0.7f,0.0f,0.0f,
		0.0f,0.8f,0.0f,
		0.0f,0.0f,0.5f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data4),
		color_buffer_data4, GL_STATIC_DRAW);
	m_programID = LoadShaders(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID,
		"MVP");
	
	rotateAngle = 0;
	scaleAll = 1;
	for (int i = 0; i < 4; i++) {
		direction[i] = i;
		translateX[i] = 0;
		translateY[i] = 0;
	}
	
	glUseProgram(m_programID);

}

void Scene2::Update(double dt)
{
	for (int i = 0; i < 4; i++) {
		//upper
		if (translateX[i] > -15 && translateX[i] < 15 && translateY[i] >= 10) {
			switch (direction[i]) {
			case up_left:
				direction[i] = down_left;
				break;
			case up_right:
				direction[i] = down_right;
				break;
			}
		}
		//left
		if (translateY[i] > -10 && translateY[i] < 10 && translateX[i] <= -15) {
			switch (direction[i]) {
			case down_left:
				direction[i] = down_right;
				break;
			case up_left:
				direction[i] = up_right;
				break;
			}
		}
		//down
		if (translateX[i] > -15 && translateX[i] < 15 && translateY[i] <= -10) {
			switch (direction[i]) {
			case down_left:
				direction[i] = up_left;
				break;
			case down_right:
				direction[i] = up_right;
				break;
			}
		}
		//right
		if (translateY[i] > -10 && translateY[i] < 10 && translateX[i] >= 15) {
			switch (direction[i]) {
			case down_right:
				direction[i] = down_left;
				break;
			case up_right:
				direction[i] = up_left;
				break;
			}
		}
		//upper left corner
		if (translateX[i] == -15 && translateY[i] == 10) {
			direction[i] = down_right;
		}
		//upper right
		if (translateX[i] == 15 && translateY[i] == 10) {
			direction[i] = down_left;
		}
		//bottom left
		if (translateX[i] == -15 && translateY[i] == -10) {
			direction[i] = up_right;
		}
		//bottom right
		if (translateX[i] == 15 && translateY[i] == -10) {
			direction[i] = up_left;
		}
		switch (direction[i]) {
		case up_left:
			translateX[i] -= (float)(9 * dt);
			translateY[i] += (float)(9 * dt);
			break;
		case up_right:
			translateX[i] += (float)(9 * dt);
			translateY[i] += (float)(9 * dt);
			break;
		case down_left:
			translateX[i] -= (float)(9 * dt);
			translateY[i] -= (float)(9 * dt);
			break;
		case down_right:
			translateX[i] += (float)(9 * dt);
			translateY[i] -= (float)(9 * dt);
			break;
		}
	}
	
	rotateAngle += (float)(180 * dt);
	scaleAll += (float)(2 * dt);
}

void Scene2::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity();
	projection.SetToOrtho(-15, 15, -10, 10, -10, 10);
	//object 1
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0, 0 );
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(3, 3, 3);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(translateX[0], translateY[0], 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	//object 2
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(3, 3, 3);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(translateX[1], translateY[1], 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	//object 3
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(3, 3, 3);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(translateX[2], translateY[2], 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	//object 4
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_4]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_4]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(3, 3, 3);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(translateX[3], translateY[3], 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

void Scene2::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
