#pragma once

#include <Engine/EntityComponent/Component.h>

class CharacterController
	: public Component
{
public:
	explicit CharacterController(class Entity* owner);
	~CharacterController() noexcept = default;

	void BindInputs(Inputs* inputs) override;
	const char* GetType() const override { return "CharacterControllerComponentType"; }

	void MoveZ(float scale);
	void MoveX(float scale);
	void MoveY(float scale);
	void Rotate(float x, float y);

	float moveSpeed = 10.f;
	float rotateSpeed = 5.f;
};
