#pragma once

#include <GLFW/glfw3.h>

class HandleTimer
{
public:
	float lastTime;
	float dt, time;

	void Update() {
		lastTime = glfwGetTime();
		dt = lastTime - time;
		time = lastTime;
	}
};
