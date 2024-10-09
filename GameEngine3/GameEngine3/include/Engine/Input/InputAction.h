#pragma once

#include <functional>
#include <vector>
#include <Engine/Timer/HandleTimer.h>

enum EInputType
{
	Keyboard,
	Mouse
};

class InputAction
{
public:
	std::vector<std::function<void()>> pressAction;
	std::vector<std::function<void()>> pressDownAction;
	std::vector<std::function<void()>> releaseAction;
	std::vector<std::function<void()>> releaseUpAction;
	unsigned int key;
	EInputType inputType;

	bool isPress;
	bool isRelease;

public:
	inline void BindPressAction(std::function<void()> act) {
		pressAction.push_back(act);
	}
	inline void BindPressDownAction(std::function<void()> act) {
		pressDownAction.push_back(act);
	}
	inline void BindReleaseAction(std::function<void()> act) {
		releaseAction.push_back(act);
	}
	inline void BindReleaseUpAction(std::function<void()> act) {
		releaseUpAction.push_back(act);
	}
};