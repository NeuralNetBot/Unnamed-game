#pragma once
#include <string>
#include <Windows.h>
#include <GL\GL.h>
#include <GL\glut.h>
#include <GLFW/glfw3.h>

class GameWindow
{
private:
public:
	GameWindow(std::string title, int argc, char** argv);
	~GameWindow();
};
