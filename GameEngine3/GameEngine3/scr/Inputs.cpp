#include <Input/Inputs.h>

#include <Timer/HandleTimer.h>
#include <Input/InputAction.h>
#include <Window/Window.h>
#include <iostream>

#include <GLFW/glfw3.h>

void Inputs::UpdateInputs(HandleTimer timer, Window* window)
{
	updateMousePosition(window->GetWindow(), timer);

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
					pressAction(timer);
				}
				value->isPress   = true;
				value->isRelease = false;
			}
			else {
				for (auto& pressAction : value->pressAction) {
					pressAction(timer);
				}
			}
		}
		else if (state == GLFW_RELEASE) {
			if (!value->isRelease) {
				for (auto& releaseAction : value->releaseUpAction) {
					releaseAction(timer);
				}
				value->isRelease = true;
				value->isPress   = false;
			}
			else {
				for (auto& releaseAction : value->releaseAction) {
					releaseAction(timer);
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

void Inputs::BindMouseDeltaPosition(std::function<void(float, float, HandleTimer)> act)
{
	MouseDeltaChangedActions.push_back(act);
}

void Inputs::updateMousePosition(GLFWwindow* window, HandleTimer timer)
{
	double mX, mY;
	glfwGetCursorPos(window, &mX, &mY);

	float deltaMouseX = mX - mouseX;
	float deltaMouseY = mY - mouseY;

	if (deltaMouseX + deltaMouseY != 0.f)
		for (auto& act : MouseDeltaChangedActions)
			act(deltaMouseX, deltaMouseY, timer);

	mouseX = mX;
	mouseY = mY;
}
