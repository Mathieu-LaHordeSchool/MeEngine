#pragma once

#include <unordered_map>
#include <typeinfo>

#include <me/Core/EnableObject.h>

namespace me::core::input { class Inputs; }
namespace me::render { class Renderer; }

namespace me::core {
	class Component;
	class TransformData;
	class Scene;

	class Entity
	{
	private:
		struct Internal;
		Internal* m_entity;

	public:
		explicit Entity(Scene* scn);
		~Entity() noexcept = default;

		TransformData* Transform() const;
		TransformData* TransformUi() const;
		
		Component* AddComponent(Component* comp);
		Component* GetComponent(const char* comp);
		bool	   HasComponent(const char* comp);

		Scene* GetScene() const;
		void Render(me::render::Renderer* render);
		void Start();
		void BindInputs(me::core::input::Inputs* inputs);
		void Update();

		template<typename COMP>
		COMP* AddComponent() {
			return static_cast<COMP*>(AddComponent(new COMP(this)));
		}
		template<typename COMP>
		COMP* GetComponent() {
			return static_cast<COMP*>(GetComponent(COMP::GetStaticType()));
		}
		template<typename COMP>
		bool HasComponent() {
			return HasComponent(COMP::GetStaticType());
		}
	};
}
