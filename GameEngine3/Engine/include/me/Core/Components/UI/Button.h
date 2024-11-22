#pragma once

#include <me/Core/Component.h>
#include <me/Core/UI/UIElements.h>

namespace me::core { class Entity; }
namespace me::core::input { class Inputs; }

namespace me::core::components::ui {
	class Button
		: public Component
		, public me::core::ui::UIElement
	{
		struct Internal;
		Internal* m_button;

	public:
		GetComponentType("Button")

			explicit Button(me::core::Entity* owner);
		~Button() noexcept = default;

		void Start() override;
		void Update() override;
		void BindInputs(me::core::input::Inputs* inputs) override;
		void Render(me::render::Renderer* render) override;

		GetSetInternalValueHPP(OnClick, std::function<void()>)
		GetSetInternalValueHPP(OnEnter, std::function<void()>)
		GetSetInternalValueHPP(OnExit, std::function<void()>)
	};
}
