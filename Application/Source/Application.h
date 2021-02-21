
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Scene.h"
#include "timer.h"

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static bool IsMousePressed(unsigned short key);
	static void GetCursorPos(double* xpos, double* ypos);
	static void SetCursorPos(double xpos, double ypos);
	static void hidemousecursor(bool hide);
	static int GetWindowWidth();
	static int GetWindowHeight();
	static unsigned m_width;
	static unsigned m_height;
	static void setscene(int scenenum);
	static void quit(bool quit);
	static void pause(bool pause);
	
private:
	//Declare a window object
	StopWatch m_timer;
	static int scenetype;
	static Scene* scene;
	static Scene* sceneMain, *sceneMenu, *scene1, *scene2,* scene3;
	static bool isquit;
	static bool ispaused;
	static bool mainInit;
};
enum Scenemanager {
	
	Scene_Main,
	Scene_Menu,
	Scene_1,
	Scene_2,
	Scene_3,
	Scene_4
	
};

#endif