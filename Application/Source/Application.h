
#ifndef APPLICATION_H
#define APPLICATION_H

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
	static void hidemousecursor(void);
	static int GetWindowWidth();
	static int GetWindowHeight();
	static unsigned m_width;
	static unsigned m_height;
	static void setscene(int scenenum);
	
private:
	//Declare a window object
	StopWatch m_timer;
	static int scenetype;
};
enum Scenemanager {
	Scene_1,
	Scene_2,
	Scene_3,
	Scene_4,
	Scene_5,
};

#endif