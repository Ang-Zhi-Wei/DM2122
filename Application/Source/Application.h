
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
	void setscene(int scenenum);
	int scenetype;
private:
	//Declare a window object
	StopWatch m_timer;
};
enum Scenemanager {
	Scenetest,
};

#endif