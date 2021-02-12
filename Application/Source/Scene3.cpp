#include "Scene3.h"
#include "GL\glew.h"
#include <stdlib.h>
#include <time.h>
#include "shader.hpp"


Scene3::Scene3()
{
}

Scene3::~Scene3()
{
}


void Scene3::Init()
{
	// Init VBO here
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	//GRASS
	static const GLfloat vertex_buffer_data[] = {
		0.0f,1.0f,-0.2f,//grass
		-1.0f,1.0f,-0.2f,
		0.0f,-1.0f,-0.2f,
		0.0f,-1.0f,-0.2f,
		-1.0f,-1.0f,-0.2f,
		-1.0f,1.0f,-0.2f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data),
		vertex_buffer_data, GL_STATIC_DRAW);
	static const GLfloat color_buffer_data[] = {
		0.000f, 0.392f, 0.000f,//grass
		0.235f, 0.702f, 0.443f,
		0.498f, 1.000f, 0.000f,
		0.000f, 1.000f, 1.000f,
		0.282f, 0.820f, 0.800f,
		0.275f, 0.510f, 0.706f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data),
		color_buffer_data, GL_STATIC_DRAW);
	//rain
	static const GLfloat vertex_buffer_data2[]{
		0.0f,0.0f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.0f,0.0f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.0f,0.0f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.0f,0.0f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.0f,0.0f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.0f,0.0f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.0f,0.0f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.0f,0.0f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.0f,0.0f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.0f,0.0f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.0f,0.0f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.0f,0.0f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.0f,0.0f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.0f,0.0f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.0f,0.0f,-0.5f,
		0.5f,-0.5f,-0.5f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2),
		vertex_buffer_data2, GL_STATIC_DRAW);
	static const GLfloat color_buffer_data2[]{
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		0.416f, 0.353f, 0.804f,
		
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2),
		color_buffer_data2, GL_STATIC_DRAW);
	//Thunder
	static const GLfloat vertex_buffer_data3[] = {
		0.0f,1.0f,-0.8f,
		-1.0f,1.0f,-0.8f,
		0.0f,-1.0f,-0.8f,
		0.0f,-1.0f,-0.8f,
		-1.0f,-1.0f,-0.8f,
		-1.0f,1.0f,-0.8f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data3),
		vertex_buffer_data3, GL_STATIC_DRAW);
	static const GLfloat color_buffer_data3[] = {
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data3),
		color_buffer_data3, GL_STATIC_DRAW);
	//windmill
	static const GLfloat vertex_buffer_data4[] = {
		0.0f,0.0f,0.0f,//top
		0.3f,0.5f,0.0f,
		-0.3f,0.5f,0.0f,
		0.0f,0.0f,0.0f,//bottom
		0.3f,-0.5f,0.0f,
		-0.3f,-0.5f,0.0f,
		0.0f,0.0f,0.0f,//left
		-0.5f,-0.3f,0.0f,
		-0.5f,0.3f,0.0f,
		0.0f,0.0f,0.0f,//right
		0.5f,-0.3f,0.0f,
		0.5f,0.3f,0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data4),
		vertex_buffer_data4, GL_STATIC_DRAW);
	static const GLfloat color_buffer_data4[] = {
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data4),
		color_buffer_data4, GL_STATIC_DRAW);
	//backsupport
	static const GLfloat vertex_buffer_data5[] = {
	0.0f,1.0f,-0.1f,
	-1.0f,1.0f,-0.1f,
	0.0f,-1.0f,-0.1f,
	0.0f,-1.0f,-0.1f,
	-1.0f,-1.0f,-0.1f,
	-1.0f,1.0f,-0.1f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data5),
		vertex_buffer_data5, GL_STATIC_DRAW);
	static const GLfloat color_buffer_data5[] = {
		0.855f, 0.647f, 0.125f,
		0.855f, 0.647f, 0.125f,
		0.855f, 0.647f, 0.125f,
		0.855f, 0.647f, 0.125f,
		0.855f, 0.647f, 0.125f,
		0.855f, 0.647f, 0.125f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data5),
		color_buffer_data5, GL_STATIC_DRAW);
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

}

void Scene3::Update(double dt)
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
}

void Scene3::Render()
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
	//grass
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0, 0 );
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(30, 3, 3);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(15, -7, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//rain
	for (int i = 0; i < 15; i++) {
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		scale.SetToScale(3, 3, 3);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(translateX[i], translateY[i], 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
			&MVP.a[0]);
		glDrawArrays(GL_LINES, 0, 2);
	}
	//thunder
	if (thunder == true) {
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		scale.SetToScale(50, 50, 3);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(15, 6, 0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
			&MVP.a[0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	//spinning fan
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_4]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_4]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(3, 3, 3);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(12, 0, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	//back support
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_5]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_5]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	scale.SetToScale(1, 5, 3);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(12.5, -4, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Scene3::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
