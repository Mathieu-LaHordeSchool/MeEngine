#pragma once

class GLFWwindow;

class Window 
{
public:
	explicit Window(const char* title, int w, int h);
	~Window() noexcept;

private:
	GLFWwindow* window;

public:
	bool IsClose();
	void SwapBuffer();
	void PoolEvent();
	void Terminate();
	void SetEnableMouse(bool enable);

	inline GLFWwindow* GetWindow() const { return window; }
};