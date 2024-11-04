
#include <iostream>

#include <me/Render/Renderer.h>
#include <me/Render/RendererObjects/Shader/Shader.h>
#include <me/Render/RendererObjects/Shader/ShaderProgram.h>
#include <me/Render/RendererObjects/Buffer.h>
#include <me/Render/RendererObjects/VertexArray.h>
#include <me/Render/RendererObjects/RenderObjectData.h>
#include <me/Render/Window/Window.h>
#include <me/Core/Render/Mesh/Mesh.h>
#include <me/Core/TransformData.h>
#include <me/Core/Entity.h>
#include <me/Core/Render/Texture/Texture.h>

#include <me/Core/Components/Render/Camera.h>
#include <me/Core/Components/Render/Material.h>
#include <me/Core/Components/Render/StaticMesh.h>
#include <me/Core/Components/UI/Image.h>
#include <me/Core/UI/UIElements.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tuple>
#include <vector>

struct me::render::Renderer::Internal
{
	me::render::window::Window* window = nullptr;
	me::core::render::Mesh baseMesh = me::core::render::Mesh();
	me::core::TransformData* uiTransform = new me::core::TransformData();

	std::vector<std::tuple<me::core::TransformData*, me::core::components::render::Material*, me::core::render::Mesh>> geometrys;
	std::map<int, std::vector<std::tuple<me::core::TransformData*, me::core::ui::UIElement*, me::core::render::Texture*>>> images;
	me::core::components::render::Camera* camera = nullptr;

	glm::mat4 viewMatrix = glm::mat4(1.f);
	glm::mat4 projectionMatrix = glm::mat4(1.f);

	me::render::shader::Shader* vsShader			= new me::render::shader::Shader("../Ressources/Shaders/vertex.vert",				me::render::shader::EShaderType::Vertex);
	me::render::shader::Shader* vsUIShader			= new me::render::shader::Shader("../Ressources/Shaders/uiVertex.vert",				me::render::shader::EShaderType::Vertex);
	me::render::shader::Shader* fsNoTextureShader	= new me::render::shader::Shader("../Ressources/Shaders/fragmentNoTexture.frag",	me::render::shader::EShaderType::Fragment);
	me::render::shader::Shader* fsTextureShader		= new me::render::shader::Shader("../Ressources/Shaders/fragmentTexture.frag",		me::render::shader::EShaderType::Fragment);
	me::render::shader::Shader* fsUIShader			= new me::render::shader::Shader("../Ressources/Shaders/uiFragment.frag",			me::render::shader::EShaderType::Fragment);

	me::render::shader::ShaderProgram* shaderProgramUI			= new me::render::shader::ShaderProgram(vsUIShader, fsUIShader);
	me::render::shader::ShaderProgram* shaderProgramNoTexture	= new me::render::shader::ShaderProgram(vsShader, fsNoTextureShader);
	me::render::shader::ShaderProgram* shaderProgramTexture		= new me::render::shader::ShaderProgram(vsShader, fsTextureShader);

	me::render::object::Buffer* vertexsBuffer	= new me::render::object::Buffer();
	me::render::object::Buffer* normalsBuffer	= new me::render::object::Buffer();
	me::render::object::Buffer* uvsBuffer		= new me::render::object::Buffer();
	me::render::object::Buffer* elementsBuffer	= new me::render::object::Buffer();

	me::render::object::VertexArrayObject* vao			= new me::render::object::VertexArrayObject();
	me::render::object::RenderObjectData* bufferData	= new me::render::object::RenderObjectData();
};

me::render::Renderer::Renderer(me::render::window::Window* window)
	: m_renderer(new Internal())
{
	m_renderer->vao->AttributeBinding(0, 0, 3, GL_FLOAT, GL_FALSE, 0); // for vertices
	m_renderer->vao->AttributeBinding(1, 1, 3, GL_FLOAT, GL_FALSE, 0); // for normals
	m_renderer->vao->AttributeBinding(2, 2, 2, GL_FLOAT, GL_FALSE, 0); // for uvs

	m_renderer->window = window;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glDepthMask(GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void me::render::Renderer::SetCamera(me::core::Entity* entity)
{
	if (entity->HasComponent<me::core::components::render::Camera>())
		m_renderer->camera = entity->GetComponent<me::core::components::render::Camera>();
}
void me::render::Renderer::PushGeometry(me::core::Entity* entity)
{
	me::core::components::render::StaticMesh* staticMesh = entity->GetComponent<me::core::components::render::StaticMesh>();
	me::core::components::render::Material* material = entity->GetComponent<me::core::components::render::Material>();

	if (material) {
		if (!material->GetActive())
			material = nullptr;
	}

	m_renderer->geometrys.push_back(std::make_tuple(entity->Transform(), material, staticMesh->GetMesh()));
}
void me::render::Renderer::PushImage(me::core::TransformData* trans, me::core::ui::UIElement* element, me::core::render::Texture* tex)
{
	m_renderer->images[element->order].push_back(std::make_tuple(trans, element, tex));
}

void me::render::Renderer::ClearAllRendererData()
{
	m_renderer->geometrys.clear();
	m_renderer->images.clear();
}

void me::render::Renderer::Execute()
{
	glClearColor(.1f, .2f, .3f, 1.f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawGeometry();

	glDisable(GL_DEPTH_TEST);
	DrawUIs();
	glEnable(GL_DEPTH_TEST);
}

void me::render::Renderer::CalculViewMatrix(me::core::components::render::Camera* cam)
{
	me::core::TransformData* trans = cam->GetOwner()->Transform();
	glm::vec3 camPos = trans->GetWorldPosition();
	glm::vec3 fwd = trans->GetTransformForward();
	glm::vec2 sizeWindow = m_renderer->window->GetSize();

	m_renderer->viewMatrix = glm::lookAt(
		camPos,
		fwd + camPos, // direction
		glm::vec3(0.f, 1.f, 0.f)  // vector up
	);

	float fov = cam->GetFov();
	float zNear = cam->GetNearRender();
	float zFar = cam->GetFarRender();

	m_renderer->projectionMatrix = glm::perspective(
		glm::radians(fov),
		sizeWindow.x / sizeWindow.y,
		zNear, zFar
	);
}
void me::render::Renderer::CreateAndBindBuffers(const me::core::render::Mesh& mesh)
{
	m_renderer->vertexsBuffer = m_renderer->bufferData->GetOrCreateVertexBuffer(mesh.Vertices);
	m_renderer->normalsBuffer = m_renderer->bufferData->GetOrCreateNormalBuffer(mesh.Normals);
	m_renderer->uvsBuffer = m_renderer->bufferData->GetOrCreateUvsBuffer(mesh.Uvs);
	m_renderer->elementsBuffer = m_renderer->bufferData->GetOrCreateElementBuffer(mesh.Elements);

	m_renderer->vao->BindElementBuffer(m_renderer->elementsBuffer);
	m_renderer->vao->BindingBuffer<float>(0, 0, m_renderer->vertexsBuffer, 3);
	m_renderer->vao->BindingBuffer<float>(1, 0, m_renderer->normalsBuffer, 3);
	m_renderer->vao->BindingBuffer<float>(2, 0, m_renderer->uvsBuffer, 2);
}

void me::render::Renderer::DrawUIs()
{
	for (auto [key, value] : m_renderer->images)
	{
		for (auto& u : value)
		{
			me::core::TransformData*	trans	= std::get<0>(u);
			me::core::ui::UIElement*	element	= std::get<1>(u);
			me::core::render::Texture*	texture	= std::get<2>(u);

			m_renderer->projectionMatrix = glm::ortho(
				0.f,
				m_renderer->window->GetSize().x,
				0.f,
				m_renderer->window->GetSize().y
			);

			CreateAndBindBuffers(m_renderer->baseMesh);
			DrawImage(trans, element, texture);
		}
	}
}
void me::render::Renderer::DrawImage(me::core::TransformData* trans, me::core::ui::UIElement* element, me::core::render::Texture* tex)
{
	me::render::shader::ShaderProgram* sp = m_renderer->shaderProgramUI;
	me::render::object::VertexArrayObject* VAO = m_renderer->vao;

	sp->StartShaderProgram();
	VAO->BindVertexArray();

	CalculTransformUI(trans, element);

	glm::mat4 modelTrans = m_renderer->uiTransform->GetTransformMatrix();
	sp->SetMat4("uModel", modelTrans);

	tex->BindTexture(GL_TEXTURE0);
	sp->SetSampler2D("image", GL_TEXTURE0);
	sp->SetVec4("uColor", element->color);
	sp->SetMat4("uProjection", m_renderer->projectionMatrix);

	glDrawElements(GL_TRIANGLES, m_renderer->baseMesh.Vertices.size(), GL_UNSIGNED_INT, 0);

	VAO->UnbindVertexArray();
	sp->StopShaderProgram();
}
void me::render::Renderer::CalculTransformUI(me::core::TransformData* trans, me::core::ui::UIElement* element)
{
	glm::vec3 anchors = glm::vec3(element->anchors.x, element->anchors.y, 0.f);

	m_renderer->uiTransform->SetLocalPosition(trans->GetWorldPosition() + ((anchors * -1.f) * trans->GetWorldScale()));
	m_renderer->uiTransform->SetLocalScale(trans->GetWorldScale());
	m_renderer->uiTransform->SetLocalRotation(trans->GetWorldRotation());
}

void me::render::Renderer::DrawGeometry()
{
	for (auto& g : m_renderer->geometrys)
	{
		me::core::TransformData*					transform	= std::get<0>(g);
		me::core::components::render::Material*		material	= std::get<1>(g);
		me::core::render::Mesh						mesh		= std::get<2>(g);
		me::core::components::render::Camera*		cam			= m_renderer->camera;

		if (!cam->InFieldOfView(mesh, transform))
			continue;

		CalculViewMatrix(cam);
		CreateAndBindBuffers(mesh);

		if (!material)
			Draw(transform, mesh);
		else
			Draw(transform, material, mesh);
	}
}
void me::render::Renderer::Draw(me::core::TransformData* trans, const me::core::render::Mesh& mesh)
{
	me::render::shader::ShaderProgram* sp = m_renderer->shaderProgramNoTexture;
	me::render::object::VertexArrayObject* VAO = m_renderer->vao;

	sp->StartShaderProgram();
	VAO->BindVertexArray();

	glm::mat4 modelTrans = trans->GetTransformMatrix();
	sp->SetMat4("uViewMatrix", m_renderer->viewMatrix);
	sp->SetMat4("uProjectionMatrix", m_renderer->projectionMatrix);
	sp->SetMat4("uModel", modelTrans);

	glDrawElements(GL_TRIANGLES, mesh.Vertices.size(), GL_UNSIGNED_INT, 0);

	VAO->UnbindVertexArray();
	sp->StopShaderProgram();
}
void me::render::Renderer::Draw(me::core::TransformData* trans, me::core::components::render::Material* material, const me::core::render::Mesh& mesh)
{
	me::render::shader::ShaderProgram* sp = m_renderer->shaderProgramTexture;
	me::render::object::VertexArrayObject* VAO = m_renderer->vao;

	sp->StartShaderProgram();
	VAO->BindVertexArray();

	glm::mat4 modelTrans = trans->GetTransformMatrix();
	sp->SetMat4("uViewMatrix", m_renderer->viewMatrix);
	sp->SetMat4("uProjectionMatrix", m_renderer->projectionMatrix);
	sp->SetMat4("uModel", modelTrans);

	material->GetAlbedoTexture()->BindTexture(GL_TEXTURE0);
	glm::vec4 color = material->GetColor();
	sp->SetSampler2D("albedoTexture", GL_TEXTURE0);
	sp->SetVec4("color", color);
	
	glDrawElements(GL_TRIANGLES, mesh.Vertices.size(), GL_UNSIGNED_INT, 0);

	VAO->UnbindVertexArray();
	sp->StopShaderProgram();
}

me::render::window::Window* me::render::Renderer::GetWindow() const
{
	return m_renderer->window;
}
