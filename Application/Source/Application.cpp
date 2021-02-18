
#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>
#include "SceneSP2Menu.h"
#include "SceneSP2Main.h"
#include "SceneSP2Room1.h"
#include "SceneSP2Room2.h"
GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

//Define an error callback
int Application::scenetype = Scene_1;
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


bool Application::IsKeyPressed(unsigned short key)
{
	    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{
}

Application::~Application()
{
}
void resize_callback(GLFWwindow* window, int w, int h)
{
	Application::m_width = w;
	Application::m_height = h;
	glViewport(0, 0, w, h);
}
void Application::Init()
{
	glfwSetWindowSizeCallback(m_window, resize_callback);
	//Set the error callback
	glfwSetErrorCallback(error_callback);
	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//FullScreen (massive problem,unless the crashing bug is fixed don't use this)

	//FullScreen

	//m_window = glfwCreateWindow(1920, 1080, "The Ghost City", glfwGetPrimaryMonitor(), NULL);
	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(1920, 1080, "The Ghost City", NULL, NULL);
	//megumin
	//m_window = glfwCreateWindow(1440, 1080, "Megumin", NULL, NULL);
	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
}

void Application::Run()
{
	Scene* scene = new SceneSP2Main;//don't change here
	//Main Loop
	//Scene Manager
	switch (scenetype) {
	case Scene_1:
		scene->Init();
		break;
	case Scene_2:
		delete scene;
		scene = new SceneSP2Room1();
		scene->Init();
		break;
	case Scene_3:
		delete scene;
		scene = new SceneSP2Room2();
		scene->Init();
		break;
	case Scene_4:
		delete scene;
		scene = new SceneSP2Menu();
		scene->Init();
		break;
	}
	

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		scene->Update(m_timer.getElapsedTime());
		scene->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   
		
	} //Check if the ESC key had been pressed or if the window had been closed
	delete scene;
}
unsigned Application::m_width;
unsigned Application::m_height;

bool Application::IsMousePressed(unsigned short key) //0 - Left, 1 - Right, 2 - Middle
{
	return glfwGetMouseButton(m_window, key) != 0;
}
void Application::GetCursorPos(double* xpos, double* ypos)
{
	glfwGetCursorPos(m_window, xpos, ypos);
}
void Application::SetCursorPos(double xpos, double ypos)
{
	glfwSetCursorPos(m_window, xpos, ypos);
}

void Application::hidemousecursor(void)
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}



int Application::GetWindowWidth()
{
	return m_width;
}
int Application::GetWindowHeight()
{
	return m_height;
}

void Application::setscene(static int scenenum)
{
	scenetype = scenenum;
}


void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}

