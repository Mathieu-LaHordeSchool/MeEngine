#pragma once

#include <unordered_map>

class Renderer 
{
public:
	struct Internal;
	Internal* m_renderer;

	explicit Renderer();
	~Renderer() noexcept = default;

	void PushCamera(const class Camera& cam);
	void PushGeometry(const class TransformData& trans, const class Mesh& mesh);

	void Execute();
	void CreateAndBindBuffers(const class Mesh& mesh);
	void Draw(const class TransformData& trans, const class Mesh& mesh);
};
