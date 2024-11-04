#pragma once

#include <functional>

namespace me::core::timer { class HandleTimer; }
namespace me::core::input { class Inputs; }
namespace me::render { class Renderer; }

namespace me::core {
	class Entity;
	class TransformData;

	class Scene
	{
	private:
		struct Internal;
		Internal* m_scene;

		void UpdateTimer();
		void LoopOnEntity(std::function<void(Entity*)> func);
		void DestroyVectorObject();

	public:
		explicit Scene();
		~Scene() noexcept = default;

		Entity* CreateObject(const char* name, TransformData* parent = nullptr);
		void Destroy(Entity* e);

		me::core::timer::HandleTimer GetHandleTimer() const;

		void Start();
		void BindInput(me::core::input::Inputs* inputs);
		void Update();

		void Render(me::render::Renderer* render);
	};
}