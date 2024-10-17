
#include <iostream>
#include <functional>

#include <me/Core/ComponentsUI/Button.h>

#include <me/Core/Entity.h>
#include <me/Core/Input/Inputs.h>
#include <me/Core/Input/KeyCode.h>
#include <me/Core/Input/InputAction.h>
#include <me/Core/TransformData.h>

#include <me/Core/ComponentsUI/Image.h>

struct Button::Internal
{
	bool mousePress;
	bool mouseInside;

	Inputs* inputs;

	std::function<void()> onClick;
	std::function<void()> onEnter;
	std::function<void()> onExit;
};

Button::Button(Entity* owner)
	: Component(owner), m_button(new Internal())
{}

void Button::Update()
{
	Image* img = GetOwner()->GetComponent<Image>();
	glm::vec2 size = img->GetWindowSize();

	glm::vec3 pos = GetOwner()->Transform()->GetWorldPosition();
	glm::vec3 scl = GetOwner()->Transform()->GetWorldScale();

	glm::vec2 min, max;
	min = (glm::vec2(pos.x - scl.x, pos.y - scl.y) * size) * glm::vec2(scl.x, scl.y);
	max = (glm::vec2(pos.x + scl.x, pos.y + scl.y) * size) * glm::vec2(scl.x, scl.y);

	double mx, my;
	m_button->inputs->GetMousePosition(mx, my);
	
	mx = mx - size.x / 2.0;
	my = (size.y / 2.0) - my;

	bool isMouseInside = (mx >= min.x && mx <= max.x && my >= min.y && my <= max.y);

	if (isMouseInside) {

		if (!m_button->mouseInside) {
			if (m_button->onEnter)
				m_button->onEnter();
		}
		m_button->mouseInside = true;

		if (m_button->mousePress) {
			if (m_button->onClick)
				m_button->onClick();

			m_button->mousePress = false;
		}
	}
	else if (m_button->mouseInside) {

		if (m_button->onExit)
			m_button->onExit();
		
		m_button->mouseInside = false;
	}
}

void Button::BindInputs(Inputs* inputs)
{
	InputAction* mouseAct = inputs->CreateInputAction(GetOwner()->Transform()->GetName(), KeyCode::MOUSE_BUTTON_1, EInputType::Mouse);
	mouseAct->BindPressDownAction([this]() { m_button->mousePress = true; });
	mouseAct->BindReleaseUpAction([this]() { m_button->mousePress = false; });

	m_button->inputs = inputs;
}

GetSetInternalValueCPP(OnClick, onClick, std::function<void()>, Button, m_button)
GetSetInternalValueCPP(OnEnter, onEnter, std::function<void()>, Button, m_button)
GetSetInternalValueCPP(OnExit, onExit, std::function<void()>, Button, m_button)
