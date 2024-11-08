#pragma once

#include <glm/glm.hpp>

struct GLFWwindow;

namespace me::render::window {
	class Window
	{
	public:
		struct Internal;
		Internal* m_window;

		explicit Window(const char* title, int w, int h, bool fullScreen, bool resizable);
		~Window() noexcept;

		bool IsClose();
		void SwapBuffer();
		void PoolEvent();
		void Terminate();
		void SetEnableMouse(bool enable);
		glm::vec2 GetSize() const;

		GLFWwindow* window;
		GLFWwindow* GetWindow() const;
	};
}