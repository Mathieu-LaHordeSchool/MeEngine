#pragma once

#include <functional>
#include <vector>
#include <Timer/HandleTimer.h>

enum EInputType
{
	Keyboard,
	Mouse
};

class InputAction
{
public:
	std::vector<std::function<void(HandleTimer)>> pressAction;
	std::vector<std::function<void(HandleTimer)>> pressDownAction;
	std::vector<std::function<void(HandleTimer)>> releaseAction;
	std::vector<std::function<void(HandleTimer)>> releaseUpAction;
	unsigned int key;
	EInputType inputType;

	bool isPress;
	bool isRelease;

public:
	inline void BindPressAction(std::function<void(HandleTimer)> act) {
		pressAction.push_back(act);
	}
	inline void BindPressDownAction(std::function<void(HandleTimer)> act) {
		pressDownAction.push_back(act);
	}
	inline void BindReleaseAction(std::function<void(HandleTimer)> act) {
		releaseAction.push_back(act);
	}
	inline void BindReleaseUpAction(std::function<void(HandleTimer)> act) {
		releaseUpAction.push_back(act);
	}
};