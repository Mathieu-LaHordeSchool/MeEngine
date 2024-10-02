#pragma once

#include <vector>
#include <unordered_map>
#include <functional>
#include <Input/InputAction.h>

struct HandleTimer;
class InputAction;
class Window;

class Inputs
{
public:
	void			UpdateInputs(HandleTimer timer, Window* window);
	InputAction*	CreateInputAction(const char* name, unsigned int key, EInputType inputType = Keyboard);
	InputAction*	GetInputbyName(const char* name);

	void BindMouseDeltaPosition(std::function<void(float, float, HandleTimer)> act);

private:
	double mouseX, mouseY;
	std::unordered_map<const char*, InputAction*> inputs;
	std::vector<std::function<void(float, float, HandleTimer)>> MouseDeltaChangedActions;

private:
	void updateMousePosition(class GLFWwindow* window, HandleTimer timer);
};
