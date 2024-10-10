#pragma once

#include <unordered_map>

class Renderer
{
public:
	struct Internal;
	Internal* m_renderer;

	explicit Renderer();
	~Renderer() noexcept = default;

	void PushCamera(class Entity* cam);
	void PushGeometry(class Entity* cam);

	void Execute();
	void CalculViewMatrix();
	void CreateAndBindBuffers(const class Mesh& mesh);
	void Draw(const class TransformData* trans, const class Mesh& mesh);
};
