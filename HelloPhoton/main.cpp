#include <iostream>
#include <WinSock2.h>
#include <windows.h>
#include <GL/GLU.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include "MyPhoton.h"

using namespace std;

static int playerID;

Application& app = Application::getInstance();
MyPhoton& photon = MyPhoton::getInstance();

void onWindowResized(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//! Use ortho2D view
	gluOrtho2D(0, width, 0, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// close game
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

static void cursor_position_callback(GLFWwindow* window, double xPos, double yPos)
{
	app.onMouseMoved(xPos, yPos);
	playerID = 6969;
}

static void mouse_button_callback (GLFWwindow* window, int button, int action, int mods)
{
	if (button == 0 && action == 1)
	{
		photon.sendEvent(playerID, 1.0f, 0.0f);
		if (GameState() == START)
		{
			app.onMouseClick();
		}
	}
}

int main (void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create m_a windowed mode window and its OpenGL context */
	window = glfwCreateWindow (RESOLUTION_X, RESOLUTION_Y, "Tic Tac Toe - Multiplayer", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback (window, onWindowResized);
	
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	onWindowResized (window, RESOLUTION_X, RESOLUTION_Y);

	/* Inputs */
	glfwSetKeyCallback (window, key_callback);
	glfwSetMouseButtonCallback (window, mouse_button_callback);
	glfwSetCursorPosCallback (window, cursor_position_callback);

	double prevTime = glfwGetTime();
	app.start ();

	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		double elapsedTime = currentTime - prevTime;

		app.update(elapsedTime);
		app.draw ();

		glfwSwapBuffers (window);
		glfwPollEvents ();

		prevTime = currentTime;
	}

	glfwTerminate();
	return 0;
}