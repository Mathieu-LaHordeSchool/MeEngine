#pragma once

#include <GLFW/glfw3.h>

namespace me::core::timer {
	class HandleTimer
	{
	public:
		float lastTime;
		float dt, time;

		void Update() {
			lastTime = static_cast<float>(glfwGetTime());
			dt = lastTime - time;
			time = lastTime;
		}
	};
}
