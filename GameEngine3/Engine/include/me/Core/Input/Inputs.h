#pragma once

#include <functional>
#include <me/Core/Input/InputAction.h>
#include <me/Render/Window/Window.h>

namespace me::render::window { class Window; }

namespace me::core::input {
	class InputAction;

	class Inputs
	{
		struct Internal;
		Internal* m_input;

	public:
		explicit Inputs(me::render::window::Window* window);
		~Inputs() noexcept = default;

		void			UpdateInputs();
		InputAction* CreateInputAction(const char* name, unsigned int key, EInputType inputType = Keyboard);
		InputAction* GetInputbyName(const char* name);

		void BindMousePosition(std::function<void(float, float)> act);
		void GetMousePosition(double& mx, double& my);

	private:
		void updateMousePosition(struct GLFWwindow* window);
	};
}
