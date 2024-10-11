#pragma once

#include <glm/glm.hpp>

struct GLFWwindow;

class Window 
{
private:
	struct Internal;
	Internal* m_window;

public:
	explicit Window(const char* title, int w, int h);
	~Window() noexcept;

	bool IsClose();
	void SwapBuffer();
	void PoolEvent();
	void Terminate();
	void SetEnableMouse(bool enable);
	glm::vec2 GetSize() const;

	GLFWwindow* GetWindow() const;
};