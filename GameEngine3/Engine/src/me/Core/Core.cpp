
#include <me/Core/Core.h>

#include <me/Render/Window/Window.h>
#include <me/Render/Renderer.h>
#include <me/Core/Input/Inputs.h>
#include <me/Core/Scene.h>

using namespace me::core;

Core::Internal* Core::m_core = nullptr;

struct Core::Internal
{
	static me::core::input::Inputs*		inputs;
	static me::render::Renderer*		renderer;
	static me::render::window::Window*	window;

	me::core::Scene* currentScene;
	bool shouldStop = false;
};

me::core::input::Inputs*	Core::Internal::inputs		= nullptr;
me::render::Renderer*		Core::Internal::renderer	= nullptr;
me::render::window::Window* Core::Internal::window		= nullptr;

Core* Core::instance = nullptr;

Core::Core()
{
}

Core* Core::Global()
{
	return instance;
}

void Core::Initialize(CoreConfigs configs)
{
	m_core = new Internal();

	Core::Internal::window = new me::render::window::Window(
		configs.title,
		configs.windowSize.x, configs.windowSize.y,
		configs.fullScreen, configs.resezable
	);
	Core::Internal::inputs = new me::core::input::Inputs(Core::Internal::window);
	Core::Internal::renderer = new me::render::Renderer(Core::Internal::window);
}

me::core::input::Inputs* Core::Inputs() const
{
	return Core::Internal::inputs;
}
me::render::Renderer* Core::Renderer() const
{
	return Core::Internal::renderer;
}
me::render::window::Window* Core::Window() const
{
	return Core::Internal::window;
}

void Core::LoadScene(me::core::Scene* scn)
{
	m_core->currentScene = scn;
}
void Core::Execute()
{
	m_core->currentScene->BindInput(Core::Internal::inputs);
	m_core->currentScene->Start();

	while (!m_core->shouldStop && !Core::Internal::window->IsClose())
	{
		Core::Internal::window->PoolEvent();
		Core::Internal::inputs->UpdateInputs();

		m_core->currentScene->Render(Core::Internal::renderer);
		Core::Internal::renderer->Execute();

		m_core->currentScene->Update();
		Core::Internal::window->SwapBuffer();
	}

	Core::Internal::window->Terminate();
}
void me::core::Core::Stop()
{
	m_core->shouldStop = true;
}
