#pragma once

#include <glm/glm.hpp>

namespace me::core::input { class Inputs; }
namespace me::render::window { class Window; }
namespace me::render { class Renderer; }
namespace me::core { class Scene; }

namespace me::core
{
	struct CoreConfigs
	{
		const char* title;
		glm::vec2 windowSize;
		bool fullScreen = false;
		bool resezable = false;

		glm::vec2 defaultWinowSize;
	};

	class Core
	{
		static Core* instance;

		struct Internal;
		static Internal* m_core;

	public:
		explicit Core();
		~Core() noexcept = default;

		static Core* Global();
		static void Initialize(CoreConfigs configs);

		me::core::input::Inputs*	Inputs()	const;
		me::render::Renderer*		Renderer()	const;
		me::render::window::Window* Window()	const;

		void LoadScene(me::core::Scene* scn);
		void Execute();
		void Stop();
	};
}
