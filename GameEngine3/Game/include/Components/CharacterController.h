#pragma once

#include <me/Core/Component.h>

namespace me::render::window { class Window; }
namespace me::core::input { class Inputs; }
namespace me::core { class Entity; }

class CharacterController
	: public me::core::Component
{
private:
	float moX, moY;

public:
	GetComponentType("CharacterController")

	explicit CharacterController(me::core::Entity* owner);
	~CharacterController() noexcept = default;

	void Start() override;
	void Update() override;
	
	void BindInputs(me::core::input::Inputs* inputs) override;

	void MoveZ(float scale);
	void MoveX(float scale);
	void MoveY(float scale);
	void Rotate(float x, float y);

	float moveSpeed = 10.f;
	float rotateSpeed = 200.f;
	me::core::Entity* camera;
};
