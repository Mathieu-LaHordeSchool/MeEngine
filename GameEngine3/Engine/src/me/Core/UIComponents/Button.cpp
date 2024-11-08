
#include <iostream>
#include <functional>

#include <me/Core/Core.h>
#include <me/Core/Components/UI/Button.h>

#include <me/Core/Entity.h>
#include <me/Core/Input/Inputs.h>
#include <me/Core/Input/KeyCode.h>
#include <me/Core/Input/InputAction.h>
#include <me/Core/TransformData.h>

#include <me/Core/Components/UI/Image.h>
#include <me/Render/Renderer.h>
#include <me/Core/Render/Texture/Texture.h>

using namespace me::core::components::ui;

struct Button::Internal
{
	bool mousePress;
	bool mouseInside;
	float mx, my;

	me::core::render::Texture* texture = new me::core::render::Texture("../Ressources/Textures/ao_default.png");
	glm::vec2 size;

	std::function<void()> onClick;
	std::function<void()> onEnter;
	std::function<void()> onExit;
};

Button::Button(me::core::Entity* owner)
	: Component(owner), m_button(new Internal())
{}

void Button::Update()
{
	float scale = me::core::Core::Global()->AspectRatioScale();
	glm::vec3 pos = GetOwner()->Transform()->GetWorldPosition();
	glm::vec3 scl = GetOwner()->Transform()->GetWorldScale();
	glm::vec3 siz = GetOwner()->Transform()->GetLocalSize();

	siz *= glm::vec3(2.f, 2.f, 0.f);
	pos -= (siz / 2.f) * scl;

	glm::vec2 min, max;
	min = (glm::vec2(pos.x, pos.y) * scale);
	max = (glm::vec2(pos.x, pos.y) * scale) + ((glm::vec2(siz.x, siz.y) * glm::vec2(scl.x, scl.y)) * scale);
	
	float mx = m_button->mx;
	float my = (m_button->my - m_button->size.y) * -1.f;

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

void Button::BindInputs(me::core::input::Inputs* inputs)
{
	me::core::input::InputAction* mouseAct = inputs->CreateInputAction(GetOwner()->Transform()->GetName(), me::core::input::KeyCode::MOUSE_BUTTON_1, me::core::input::EInputType::Mouse);
	mouseAct->BindPressDownAction([this]() { m_button->mousePress = true; });
	mouseAct->BindReleaseUpAction([this]() { m_button->mousePress = false; });

	inputs->BindMousePosition([this](float mx, float my) {
		m_button->mx = mx;
		m_button->my = my;
	});
}
void Button::Render(me::render::Renderer* render)
{
	m_button->size = render->GetWindow()->GetSize();
	render->PushImage(GetOwner()->Transform(), this, m_button->texture);
}

GetSetInternalValueCPP(OnClick, onClick, std::function<void()>, Button, m_button)
GetSetInternalValueCPP(OnEnter, onEnter, std::function<void()>, Button, m_button)
GetSetInternalValueCPP(OnExit, onExit, std::function<void()>, Button, m_button)
