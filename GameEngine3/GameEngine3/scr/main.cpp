
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Window/Window.h>

#include <RendererObject/Shader/Shader.h>
#include <RendererObject/Shader/ShaderProgram.h>

#include <RendererObject/Buffer.h>
#include <RendererObject/VertexArray.h>

#include <RendererObject/InstancedMap.h>

#include <Mesh/Mesh.h>
#include <Mesh/MeshLoader.h>

#include <Input/Inputs.h>
#include <Input/KeyCode.h>

#include <EntityComponent/Scene.h>
#include <EntityComponent/Entity.h>

int main(int argc, char** argv)
{
	Window* window = new Window("Game Engine", 700, 500);
	Inputs* inputs = new Inputs();

	MeshLoader loader = MeshLoader();
	Mesh cube = loader.LoadMesh("Models/boss.obj");

	Scene* mainScene = new Scene();

	Entity* poule = mainScene->CreateObject("poule");


	Shader* vs = new Shader("Shaders/vertex.vert", EShaderType::Vertex);
	Shader* fs = new Shader("Shaders/fragment.frag", EShaderType::Fragment);
	ShaderProgram* sp = new ShaderProgram(vs, fs);

	Buffer* verticesBuffer = new Buffer();
	verticesBuffer->InitBuffer<float>(cube.Vertices);

	Buffer* normalsBuffer = new Buffer();
	normalsBuffer->InitBuffer<float>(cube.Normals);

	Buffer* elementBuffer = new Buffer();
	elementBuffer->InitBuffer<uint32_t>(cube.Elements);

	InstancedMap<glm::mat4>* instancedMapBuffer = new InstancedMap<glm::mat4>();
	for (size_t i = 0; i < 10; i++) {
		glm::mat4 model = glm::mat4(1.f);
		model = glm::rotate(model, glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
		model = glm::translate(model, glm::vec3(3.f * i, 0.f, 0.f));
		model = glm::scale(model, glm::vec3(.5f));

		instancedMapBuffer->AddElement(model);
	}

	VertexArrayObject* VAO = new VertexArrayObject();
	VAO->BindElementBuffer(elementBuffer);

	VAO->BindingBuffer<float>(0, 0, verticesBuffer, 3);
	VAO->AttributeBinding(0, 0, 3, GL_FLOAT, GL_FALSE, 0);

	VAO->BindingBuffer<float>(1, 0, normalsBuffer, 3);
	VAO->AttributeBinding(1, 1, 3, GL_FLOAT, GL_FALSE, 0);

	VAO->BindingBuffer<glm::mat4>(2, 0, instancedMapBuffer->GetMapBuffer());
	for (size_t i = 0; i < 4; i++) {
		VAO->AttributeBinding(2, i + 2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4) * i);
		VAO->BindMapBuffer(i + 2, 1);
	}

	float speed = .1f;
	glm::vec3 camPos = glm::vec3(0.f, 0.f, -10.f);
	
	inputs->CreateInputAction("z", KeyCode::W)->BindPressAction([&](HandleTimer t) {
		camPos.z += speed;
	});
	inputs->CreateInputAction("s", KeyCode::S)->BindPressAction([&](HandleTimer t) {
		camPos.z -= speed;
	});

	glEnable(GL_DEPTH_TEST);
	do
	{
		window->PoolEvent();
		inputs->UpdateInputs({}, window);
		
		glm::mat4 viewMatrix = glm::lookAt(
			camPos,
			glm::vec3(0.f, 0.f, 1.f) + camPos, // direction
			glm::vec3(0.f, 1.f, 0.f)  // vector up
		);

		glm::mat4 projectionMatrix = glm::perspective(
			glm::radians(90.f), // fov
			700.f / 500.f,      // width / height
			0.1f, 1000000.f     // zNear, zFar
		);

		glClearColor(.1f, .2f, .3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sp->StartShaderProgram();
		VAO->BindVertexArray();

		int view = glGetUniformLocation(sp->GetShaderProgram(), "uViewMatrix");
		int proj = glGetUniformLocation(sp->GetShaderProgram(), "uProjectionMatrix");

		glUniformMatrix4fv(view, 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix4fv(proj, 1, GL_FALSE, &projectionMatrix[0][0]);

		glDrawElementsInstanced(GL_TRIANGLES, cube.Vertices.size(), GL_UNSIGNED_INT, nullptr, instancedMapBuffer->GetNumInstance());

		VAO->UnbindVertexArray();
		sp->StopShaderProgram();

		window->SwapBuffer();
	} while (!window->IsClose());

	window->Terminate();

	return 0;
}