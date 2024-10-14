#pragma once

#include <unordered_map>

class Renderer
{
public:
	struct Internal;
	Internal* m_renderer;

	explicit Renderer(class Window* window);
	~Renderer() noexcept = default;

	void SetCamera(class Entity* cam);
	void PushGeometry(class Entity* cam);

	void ClearAllRendererData();
	void Execute();
	void CalculViewMatrix(class Camera* cam);
	void CreateAndBindBuffers(const class Mesh& mesh);

	void DrawUIs();
	void DrawUI(TransformData* trans, Texture* tex);

	void DrawGeometry();
	void Draw(class TransformData* trans, const class Mesh& mesh);
	void Draw(class TransformData* trans, class Material* material, const class Mesh& mesh);
};
