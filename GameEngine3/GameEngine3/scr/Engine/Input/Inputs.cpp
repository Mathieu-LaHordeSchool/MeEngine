
#include <Engine/Input/Inputs.h>
#include <Engine/Timer/HandleTimer.h>
#include <Engine/Input/InputAction.h>
#include <Engine/Window/Window.h>
#include <iostream>

#include <GLFW/glfw3.h>

struct Inputs::Internal
{
	Window* window;

	double mouseX, mouseY;
	std::unordered_map<const char*, InputAction*> inputs;
	std::vector<std::function<void(float, float)>> MouseDeltaChangedActions;
};

Inputs::Inputs(Window* window)
	: m_input(new Internal())
{
	m_input->window = window;
}

void Inputs::UpdateInputs()
{
	GLFWwindow* glWindow = m_input->window->GetWindow();
	updateMousePosition(glWindow);

	for (auto& [key, value] : m_input->inputs)
	{
		int state = 0;

		switch (value->inputType)
		{
		case Keyboard:	state = glfwGetKey			(glWindow, value->key);	break;
		case Mouse:		state = glfwGetMouseButton	(glWindow, value->key);	break;
		default:	break;
		}

		if (state == GLFW_PRESS) {
			if (!value->isPress) {
				for (auto& pressAction : value->pressDownAction) {
					pressAction();
				}
				value->isPress   = true;
				value->isRelease = false;
			}
			else {
				for (auto& pressAction : value->pressAction) {
					pressAction();
				}
			}
		}
		else if (state == GLFW_RELEASE) {
			if (!value->isRelease) {
				for (auto& releaseAction : value->releaseUpAction) {
					releaseAction();
				}
				value->isRelease = true;
				value->isPress   = false;
			}
			else {
				for (auto& releaseAction : value->releaseAction) {
					releaseAction();
				}
			}
		}
	}
}

InputAction* Inputs::CreateInputAction(const char* name, unsigned int key, EInputType inputType)
{
	InputAction* newInputAction = new InputAction();
	newInputAction->key = key;
	newInputAction->inputType = inputType;

	m_input->inputs[name] = newInputAction;
	return newInputAction;
}

InputAction* Inputs::GetInputbyName(const char* name)
{
	return m_input->inputs[name];
}

void Inputs::BindMouseDeltaPosition(std::function<void(float, float)> act)
{
	m_input->MouseDeltaChangedActions.push_back(act);
}

void Inputs::GetMousePosition(double& mx, double& my)
{
	glfwGetCursorPos(m_input->window->GetWindow(), &mx, &my);
}

void Inputs::updateMousePosition(GLFWwindow* window)
{
	double mX, mY;
	glfwGetCursorPos(window, &mX, &mY);

	float deltaMouseX = mX - m_input->mouseX;
	float deltaMouseY = mY - m_input->mouseY;

	if (deltaMouseX + deltaMouseY != 0.f)
		for (auto& act : m_input->MouseDeltaChangedActions)
			act(deltaMouseX, deltaMouseY);

	m_input->mouseX = mX;
	m_input->mouseY = mY;
}
