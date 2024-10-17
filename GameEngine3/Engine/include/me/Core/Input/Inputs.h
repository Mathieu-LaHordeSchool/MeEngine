#pragma once

#include <functional>
#include <me/Core/Input/InputAction.h>
#include <me/Render/Window/Window.h>

struct HandleTimer;
class InputAction;
class Window;

class Inputs
{
	struct Internal;
	Internal* m_input;

public:
	explicit Inputs(Window* window);
	~Inputs() noexcept = default;

	void			UpdateInputs();
	InputAction*	CreateInputAction(const char* name, unsigned int key, EInputType inputType = Keyboard);
	InputAction*	GetInputbyName(const char* name);

	void BindMouseDeltaPosition(std::function<void(float, float)> act);
	void GetMousePosition(double& mx, double& my);

private:
	void updateMousePosition(class GLFWwindow* window);
};
