
#include <glm/glm.hpp>
#include <iostream>

#include <Engine/Window/Window.h>
#include <Engine/Mesh/Mesh.h>
#include <Engine/Mesh/MeshLoader.h>

#include <Engine/Input/Inputs.h>
#include <Engine/Input/KeyCode.h>

#include <Engine/EntityComponent/Scene.h>
#include <Engine/EntityComponent/Entity.h>
#include <Engine/EntityComponent/TransformData.h>
#include <Engine/RendererObject/Renderer.h>

#include <Engine/EntityComponent/Components/Camera.h>
#include <Engine/EntityComponent/Components/StaticMesh.h>

#include <Game/Components/CharacterController.h>

int main(int argc, char** argv)
{
	Window* window = new Window("Game Engine", 700, 500);
	Inputs* inputs = new Inputs();
	Renderer* render = new Renderer();

	MeshLoader loader = MeshLoader();
	Mesh pouleMesh = loader.LoadMesh("Models/boss.obj");
	Mesh cubeMesh = loader.LoadMesh("Models/default.obj");

	Scene mainScene;

	Entity* cube1 = mainScene.CreateObject("poule");
	Entity* poule = mainScene.CreateObject("poule2", cube1->Transform());

	Entity* character = mainScene.CreateObject("Character");
	Entity* cam = mainScene.CreateObject("Camera");

	cube1->Transform()->SetLocalRotation(glm::vec3(0.f, 180.f, 0.f));
	cube1->Transform()->Translate(glm::vec3(1.f, 0.f, 0.f), 10.f);
	cube1->Transform()->Scale(glm::vec3(1.f), .1f);

	poule->Transform()->SetLocalPosition(glm::vec3(2.f, 2.f, 0.f));

	cube1->AddComponent<StaticMesh>()->SetMesh(cubeMesh);
	poule->AddComponent<StaticMesh>()->SetMesh(pouleMesh);

	CharacterController* controller = cam->AddComponent<CharacterController>();
	cam->AddComponent<Camera>();

	controller->window = window;

	mainScene.BindInput(inputs);
	mainScene.Start();

	do
	{
		window->PoolEvent();
		inputs->UpdateInputs(window);
		mainScene.Update();

		float time = mainScene.GetHandleTimer().time;
		cube1->Transform()->Rotate(glm::vec3(0.f, 1.f, 0.f), 1.f);
		cube1->Transform()->Translate(glm::vec3(cos(time * 2.f), 0.f, 0.f), .1f);

		mainScene.Render(render);
		render->Execute();

		window->SwapBuffer();
	} while (!window->IsClose());

	window->Terminate();

	return 0;
}