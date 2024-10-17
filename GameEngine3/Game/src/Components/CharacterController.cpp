
#include <iostream>

#include <Components/CharacterController.h>

#include <me/Core/Scene.h>
#include <me/Core/Entity.h>
#include <me/Core/Input/Inputs.h>
#include <me/Core/Input/InputAction.h>
#include <me/Core/Input/KeyCode.h>
#include <me/Core/TransformData.h>
#include <me/Core/Timer/HandleTimer.h>
#include <me/Render/Window/Window.h>

CharacterController::CharacterController(Entity* owner)
	: Component(owner), camera(nullptr), window(nullptr)
{}

void CharacterController::Start()
{
	// window->SetEnableMouse(false);
}

void CharacterController::BindInputs(Inputs* inputs)
{
	inputs->CreateInputAction("z", KeyCode::W)->BindPressAction([this]() { MoveZ(1.f);  });
	inputs->CreateInputAction("s", KeyCode::S)->BindPressAction([this]() { MoveZ(-1.f); });
	inputs->CreateInputAction("q", KeyCode::A)->BindPressAction([this]() { MoveX(1.f);  });
	inputs->CreateInputAction("d", KeyCode::D)->BindPressAction([this]() { MoveX(-1.f); });

	inputs->CreateInputAction("up", KeyCode::SPACE)->BindPressAction([this]() { MoveY(1.f); });
	inputs->CreateInputAction("down", KeyCode::LEFT_SHIFT)->BindPressAction([this]() { MoveY(-1.f); });
	inputs->BindMouseDeltaPosition([this](float x, float y) { Rotate(x, y); });
}

void CharacterController::MoveZ(float scale)
{
	float dt = GetOwner()->GetScene()->GetHandleTimer().dt;
	glm::vec3 fwd = camera->Transform()->GetTransformForward();
	GetOwner()->Transform()->Translate(fwd, moveSpeed * dt * scale);
}
void CharacterController::MoveX(float scale)
{
	float dt = GetOwner()->GetScene()->GetHandleTimer().dt;
	glm::vec3 right = camera->Transform()->GetTransformRight();
	GetOwner()->Transform()->Translate(right, moveSpeed * dt * scale);
}
void CharacterController::MoveY(float scale)
{
	float dt = GetOwner()->GetScene()->GetHandleTimer().dt;
	glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
	GetOwner()->Transform()->Translate(up, moveSpeed * dt * scale);
}

void CharacterController::Rotate(float x, float y)
{
	float dt = GetOwner()->GetScene()->GetHandleTimer().dt;
	TransformData* trans = camera->Transform();

	float rotXmovement = y * rotateSpeed * dt * -1.f;
	if (abs(trans->GetLocalRotation().x + rotXmovement) < glm::radians(80.f))
		trans->Rotate(glm::vec3(1.f, 0.f, 0.f), rotXmovement);

	trans->Rotate(glm::vec3(0.f, 1.f, 0.f), x * rotateSpeed * dt * -1.f);
}
