#pragma once

#include <Engine/EntityComponent/Component.h>
#include <Engine/EntityComponent/UIComponents/UIElements.h>

class Button
	: public Component
	, public UIElement
{
	struct Internal;
	Internal* m_button;

public:
	GetComponentType(80002)

	explicit Button(class Entity* owner);
	~Button() noexcept = default;

	void Update() override;
	void BindInputs(class Inputs* inputs) override;

	GetSetInternalValueHPP(OnClick, std::function<void()>)
	GetSetInternalValueHPP(OnEnter, std::function<void()>)
	GetSetInternalValueHPP(OnExit, std::function<void()>)
};
