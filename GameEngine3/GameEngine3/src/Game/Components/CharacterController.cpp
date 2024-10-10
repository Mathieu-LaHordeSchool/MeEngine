
#include <iostream>

#include <Game/Components/CharacterController.h>

#include <Engine/EntityComponent/Entity.h>
#include <Engine/Input/Inputs.h>
#include <Engine/Input/KeyCode.h>
#include <Engine/EntityComponent/TransformData.h>
#include <Engine/EntityComponent/Scene.h>
#include <Engine/Window/Window.h>

CharacterController::CharacterController(Entity* owner)
	: Component(owner)
{}

void CharacterController::Start()
{
	window->SetEnableMouse(false);
}

void CharacterController::BindInputs(Inputs* inputs)
{
	inputs->CreateInputAction("z", KeyCode::W)->BindPressAction([this]() { MoveZ(1.f);  });
	inputs->CreateInputAction("s", KeyCode::S)->BindPressAction([this]() { MoveZ(-1.f); });
	inputs->CreateInputAction("q", KeyCode::A)->BindPressAction([this]() { MoveX(-1.f);  });
	inputs->CreateInputAction("d", KeyCode::D)->BindPressAction([this]() { MoveX(1.f); });

	inputs->CreateInputAction("up", KeyCode::SPACE)->BindPressAction([this]() { MoveY(1.f); });
	inputs->CreateInputAction("down", KeyCode::LEFT_SHIFT)->BindPressAction([this]() { MoveY(-1.f); });
	inputs->BindMouseDeltaPosition([this](float x, float y) { Rotate(x, y); });
}

void CharacterController::MoveZ(float scale)
{
	float dt = owner->GetScene()->GetHandleTimer().dt;
	glm::vec3 fwd = owner->Transform()->GetTransformForward();
	owner->Transform()->Translate(fwd, moveSpeed * dt * scale);
}
void CharacterController::MoveX(float scale)
{
	float dt = owner->GetScene()->GetHandleTimer().dt;
	glm::vec3 fwd = owner->Transform()->GetTransformForward();
	glm::vec3 right = glm::cross(fwd, glm::vec3(0.f, 1.f, 0.f));
	owner->Transform()->Translate(right, moveSpeed * dt * scale);
}
void CharacterController::MoveY(float scale)
{
	float dt = owner->GetScene()->GetHandleTimer().dt;
	glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
	owner->Transform()->Translate(up, moveSpeed * dt * scale);
}

void CharacterController::Rotate(float x, float y)
{
	float dt = owner->GetScene()->GetHandleTimer().dt;
	TransformData* trans = owner->Transform();

	float rotXmovement = y * rotateSpeed * dt * -1.f;
	if (abs(trans->GetLocalRotation().x + rotXmovement) < glm::radians(80.f))
		trans->Rotate(glm::vec3(1.f, 0.f, 0.f), rotXmovement);

	trans->Rotate(glm::vec3(0.f, 1.f, 0.f), x * rotateSpeed * dt * -1.f);
}
