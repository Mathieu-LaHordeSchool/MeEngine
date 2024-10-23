#pragma once

namespace me::render::window { class Window; }
namespace me::core {
	class Entity;
	class TransformData;
}
namespace me::core::ui {
	class UIElement;
}
namespace me::core::render {
	class Texture;
	class Mesh;
}
namespace me::core::components::render {
	class Camera;
	class Material;
}

namespace me::render {
	class Renderer
	{
		struct Internal;
		Internal* m_renderer;

	public:
		explicit Renderer(me::render::window::Window* window);
		~Renderer() noexcept = default;

		void SetCamera(me::core::Entity* cam);
		void PushGeometry(me::core::Entity* cam);
		void PushImage(me::core::TransformData* trans, me::core::ui::UIElement* element, me::core::render::Texture* tex);

		void ClearAllRendererData();
		void Execute();
		void CalculViewMatrix(me::core::components::render::Camera* cam);
		void CreateAndBindBuffers(const me::core::render::Mesh& mesh);

		void DrawUIs();
		void DrawImage(me::core::TransformData* trans, me::core::ui::UIElement* element, me::core::render::Texture* tex);

		void DrawGeometry();
		void Draw(me::core::TransformData* trans, const me::core::render::Mesh& mesh);
		void Draw(me::core::TransformData* trans, me::core::components::render::Material* material, const me::core::render::Mesh& mesh);

		me::render::window::Window* GetWindow() const;
	};
}
