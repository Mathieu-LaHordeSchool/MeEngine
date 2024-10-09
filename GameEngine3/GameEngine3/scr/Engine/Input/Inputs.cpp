#include <Input/Inputs.h>

#include <Timer/HandleTimer.h>
#include <Input/InputAction.h>
#include <Window/Window.h>
#include <iostream>

#include <GLFW/glfw3.h>

void Inputs::UpdateInputs(Window* window)
{
	updateMousePosition(window->GetWindow());

	for (auto& [key, value] : inputs)
	{
		int state = 0;

		switch (value->inputType)
		{
		case Keyboard:	state = glfwGetKey			(window->GetWindow(), value->key);	break;
		case Mouse:		state = glfwGetMouseButton	(window->GetWindow(), value->key);	break;
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

	inputs[name] = newInputAction;
	return newInputAction;
}

InputAction* Inputs::GetInputbyName(const char* name)
{
	return inputs[name];
}

void Inputs::BindMouseDeltaPosition(std::function<void(float, float)> act)
{
	MouseDeltaChangedActions.push_back(act);
}

void Inputs::updateMousePosition(GLFWwindow* window)
{
	double mX, mY;
	glfwGetCursorPos(window, &mX, &mY);

	float deltaMouseX = mX - mouseX;
	float deltaMouseY = mY - mouseY;

	if (deltaMouseX + deltaMouseY != 0.f)
		for (auto& act : MouseDeltaChangedActions)
			act(deltaMouseX, deltaMouseY);

	mouseX = mX;
	mouseY = mY;
}
