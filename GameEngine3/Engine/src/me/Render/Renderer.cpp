
#include <me/Core/Core.h>

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
#include <glm/detail/type_quat.hpp>

using namespace me::render;

struct Renderer::Internal
{
	me::core::render::Mesh baseMesh = me::core::render::Mesh();
	me::core::TransformData* uiTransform = new me::core::TransformData();

	std::vector<std::tuple<me::core::TransformData*, me::core::components::render::Material*, me::core::render::Mesh>> geometrys;
	std::map<int, std::vector<std::tuple<me::core::Entity*, me::core::ui::UIElement*, me::core::render::Texture*>>> images;
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

	std::unordered_map<const char*, me::render::object::VertexArrayObject*> vertexArrays;
	me::render::object::RenderObjectData* bufferData		= new me::render::object::RenderObjectData();
};

Renderer::Renderer(me::render::window::Window* window)
	: m_renderer(new Internal())
{
	m_renderer->baseMesh.path = "Engine_BaseUiMesh";

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glDepthMask(GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::SetCamera(me::core::Entity* entity)
{
	if (entity->HasComponent<me::core::components::render::Camera>())
		m_renderer->camera = entity->GetComponent<me::core::components::render::Camera>();
}
void Renderer::PushGeometry(me::core::Entity* entity)
{
	me::core::components::render::StaticMesh* staticMesh = entity->GetComponent<me::core::components::render::StaticMesh>();
	me::core::components::render::Material* material = entity->GetComponent<me::core::components::render::Material>();

	if (material) {
		if (!material->GetActive())
			material = nullptr;
	}

	m_renderer->geometrys.push_back(std::make_tuple(entity->Transform(), material, staticMesh->GetMesh()));
}
void Renderer::PushImage(me::core::Entity* entity, me::core::ui::UIElement* element, me::core::render::Texture* tex)
{
	m_renderer->images[element->order].push_back(std::make_tuple(entity, element, tex));
}

void Renderer::ClearAllRendererData()
{
	m_renderer->geometrys.clear();
	m_renderer->images.clear();
}

void Renderer::Execute()
{
	glClearColor(.1f, .2f, .3f, 1.f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawGeometry();

	glDisable(GL_DEPTH_TEST);
	DrawUIs();
	glEnable(GL_DEPTH_TEST);
}

void Renderer::CalculViewMatrix(me::core::components::render::Camera* cam)
{
	me::core::TransformData* trans = cam->GetOwner()->Transform();
	glm::vec3 camPos = trans->GetWorldPosition();
	glm::vec3 fwd = trans->GetTransformForward();
	glm::vec2 sizeWindow = me::core::Core::Global()->Window()->GetSize();

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
void Renderer::CreateAndBindBuffers(const me::core::render::Mesh& mesh)
{
	const char* idMesh = mesh.path;
	if (m_renderer->vertexArrays.count(idMesh))
		return;

	m_renderer->vertexArrays[idMesh] = new me::render::object::VertexArrayObject();
	m_renderer->vertexArrays[idMesh]->AttributeBinding(0, 0, 3, GL_FLOAT, GL_FALSE, 0); // for vertices
	m_renderer->vertexArrays[idMesh]->AttributeBinding(1, 1, 3, GL_FLOAT, GL_FALSE, 0); // for normals
	m_renderer->vertexArrays[idMesh]->AttributeBinding(2, 2, 2, GL_FLOAT, GL_FALSE, 0); // for uvs
	
	m_renderer->vertexsBuffer = m_renderer->bufferData->GetOrCreateVertexBuffer(mesh.Vertices);
	m_renderer->normalsBuffer = m_renderer->bufferData->GetOrCreateNormalBuffer(mesh.Normals);
	m_renderer->uvsBuffer = m_renderer->bufferData->GetOrCreateUvsBuffer(mesh.Uvs);
	m_renderer->elementsBuffer = m_renderer->bufferData->GetOrCreateElementBuffer(mesh.Elements);

	m_renderer->vertexArrays[idMesh]->BindElementBuffer(m_renderer->elementsBuffer);
	m_renderer->vertexArrays[idMesh]->BindingBuffer<float>(0, 0, m_renderer->vertexsBuffer, 3);
	m_renderer->vertexArrays[idMesh]->BindingBuffer<float>(1, 0, m_renderer->normalsBuffer, 3);
	m_renderer->vertexArrays[idMesh]->BindingBuffer<float>(2, 0, m_renderer->uvsBuffer, 2);
}

void Renderer::DrawUIs()
{
	for (auto [key, value] : m_renderer->images)
	{
		for (auto& u : value)
		{
			me::core::Entity*			entity	= std::get<0>(u);
			me::core::ui::UIElement*	element	= std::get<1>(u);
			me::core::render::Texture*	texture	= std::get<2>(u);

			glm::vec2 size = me::core::Core::Global()->Window()->GetSize();
			m_renderer->projectionMatrix = glm::ortho(
				0.f,
				size.x,
				0.f,
				size.y
			);
			
			CreateAndBindBuffers(m_renderer->baseMesh);
			me::render::object::VertexArrayObject* vao = m_renderer->vertexArrays[m_renderer->baseMesh.path];
			
			DrawImage(entity, element, texture, vao);
		}
	}
}
void Renderer::DrawImage(me::core::Entity* entity, me::core::ui::UIElement* element, me::core::render::Texture* tex, me::render::object::VertexArrayObject* vao)
{
	me::render::shader::ShaderProgram* sp = m_renderer->shaderProgramUI;

	sp->StartShaderProgram();
	vao->BindVertexArray();

	CalculTransformUI(entity, element);

	glm::mat4 modelTrans = entity->TransformUi()->GetTransformMatrix();
	sp->SetMat4("uModel", modelTrans);

	tex->BindTexture(GL_TEXTURE0);
	sp->SetSampler2D("image", GL_TEXTURE0);
	sp->SetVec4("uColor", element->color);
	sp->SetMat4("uProjection", m_renderer->projectionMatrix);

	glDrawElements(GL_TRIANGLES, m_renderer->baseMesh.Elements.size(), GL_UNSIGNED_INT, 0);

	vao->UnbindVertexArray();
	sp->StopShaderProgram();
}
void Renderer::CalculTransformUI(me::core::Entity* entity, me::core::ui::UIElement* element)
{
	float scale = me::core::Core::Global()->AspectRatioScale();

	me::core::TransformData* trans = entity->Transform();
	me::core::TransformData* transUi = entity->TransformUi();
	
	transUi->SetLocalPosition(trans->GetWorldPosition() * scale);
	transUi->SetLocalScale((trans->GetWorldScale() * trans->GetLocalSize()) * scale);
	transUi->SetLocalRotation(trans->GetWorldRotation());
}

void Renderer::DrawGeometry()
{
	for (auto& g : m_renderer->geometrys)
	{
		me::core::TransformData*					transform	= std::get<0>(g);
		me::core::components::render::Material*		material	= std::get<1>(g);
		me::core::render::Mesh						mesh		= std::get<2>(g);
		me::core::components::render::Camera*		cam			= m_renderer->camera;

		// if (!cam->InFieldOfView(mesh, transform))
		// 	continue;

		CalculViewMatrix(cam);
		CreateAndBindBuffers(mesh);
		me::render::object::VertexArrayObject* vao = m_renderer->vertexArrays[mesh.path];
		
		if (!material)
			Draw(transform, mesh, vao);
		else
			Draw(transform, material, mesh, vao);
	}
}
void Renderer::Draw(me::core::TransformData* trans, const me::core::render::Mesh& mesh, me::render::object::VertexArrayObject* vao)
{
	me::render::shader::ShaderProgram* sp = m_renderer->shaderProgramNoTexture;

	sp->StartShaderProgram();
	vao->BindVertexArray();

	glm::mat4 modelTrans = trans->GetTransformMatrix();
	sp->SetMat4("uViewMatrix", m_renderer->viewMatrix);
	sp->SetMat4("uProjectionMatrix", m_renderer->projectionMatrix);
	sp->SetMat4("uModel", modelTrans);

	glDrawElements(GL_TRIANGLES, mesh.Elements.size(), GL_UNSIGNED_INT, 0);

	vao->UnbindVertexArray();
	sp->StopShaderProgram();
}
void Renderer::Draw(me::core::TransformData* trans, me::core::components::render::Material* material, const me::core::render::Mesh& mesh, me::render::object::VertexArrayObject* vao)
{
	me::render::shader::ShaderProgram* sp = m_renderer->shaderProgramTexture;

	sp->StartShaderProgram();
	vao->BindVertexArray();

	glm::mat4 modelTrans = trans->GetTransformMatrix();
	sp->SetMat4("MVP", m_renderer->projectionMatrix * m_renderer->viewMatrix * modelTrans);

	material->GetAlbedoTexture()->BindTexture(GL_TEXTURE0);
	glm::vec4 color = material->GetColor();
	sp->SetSampler2D("albedoTexture", GL_TEXTURE0);
	sp->SetVec4("color", color);
	
	glDrawElements(GL_TRIANGLES, mesh.Elements.size(), GL_UNSIGNED_INT, 0);

	vao->UnbindVertexArray();
	sp->StopShaderProgram();
}
