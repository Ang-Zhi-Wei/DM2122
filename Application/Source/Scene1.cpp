#include "Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"


Scene1::Scene1()
{
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
	// Init VBO here
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glGenVertexArrays(1, &m_vertexArrayID);
	//glGenVertexArrays(2, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	//glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[1]);
	//glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[1]);
	//triangle 1
	static const GLfloat vertex_buffer_data[] = {
		0.0f,-0.5f,0.0f,//triangle 1
		0.0f,0.5f,0.0f,
		-0.5f,0.0f,0.0f,
		0.0f,-0.5f,0.0f,//triangle 2
		0.0f,0.5f,0.0f,
		0.5f,0.0f,0.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data),
		vertex_buffer_data, GL_STATIC_DRAW);
	//triangle 1
	static const GLfloat color_buffer_data[] = {
		-0.5f,0.3f,0.4f,
		-0.5f,0.3f,0.4f,
		-0.5f,0.3f,0.4f,
		-0.5f,0.3f,0.4f,
		-0.5f,0.3f,0.4f,
		-0.5f,0.3f,0.4f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data),
		color_buffer_data, GL_STATIC_DRAW);
	//triangle 2
	/*static const GLfloat vertex_buffer_data2[] = {
		1.0f, -1.0f, 0.1f,
		0.0f, 0.0f, 0.1f,
		1.0f, 1.0f, 0.1f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2),
		vertex_buffer_data2, GL_STATIC_DRAW);
	static const GLfloat color_buffer_data2[] = {
		0.0f,0.8f,0.0f,
		0.3f,0.2f,0.2f,
		0.2f,1.0f,-1.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data2),
		color_buffer_data2, GL_STATIC_DRAW);*/
	m_programID = LoadShaders(
		"C://Users//Skycl//Source//Repos//DM2122//Application//Shader//SimpleVertexShader.vertexshader",
		"C://Users//Skycl//Source//Repos//DM2122//Application//Shader//SimpleFragmentShader.fragmentshader");
	glUseProgram(m_programID);

}

void Scene1::Update(double dt)
{
}

void Scene1::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//triangle 1
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0, 0 );
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6); 

	////triangle 2
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

void Scene1::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[1]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[1]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
