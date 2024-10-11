#pragma once

#include <Engine/EntityComponent/Component.h>

class Window;
class Entity;

class CharacterController
	: public Component
{
public:
	GetComponentType(00001);

	explicit CharacterController(class Entity* owner);
	~CharacterController() noexcept = default;

	void Start() override;

	void BindInputs(Inputs* inputs) override;

	void MoveZ(float scale);
	void MoveX(float scale);
	void MoveY(float scale);
	void Rotate(float x, float y);

	float moveSpeed = 10.f;
	float rotateSpeed = 1.f;
	Window* window;
	Entity* camera;
};
