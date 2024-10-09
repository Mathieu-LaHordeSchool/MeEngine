#pragma once

#include <Engine/EntityComponent/Component.h>

class Camera
	: public Component
{
public:
	explicit Camera(class Entity* owner);
	~Camera() noexcept = default;

	const char* GetType() const override { return "CameraComponentType"; }
	void Render(Renderer* render);

	void SetRenderCameraSize(float h, float w);
	void SetRenderCameraDistance(float near, float far);
	void SetRenderCmaeraFov(float fov);

	float height, width;
	float zNear, zFar;
	float fov;
};
