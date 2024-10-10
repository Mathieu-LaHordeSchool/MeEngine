
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
#include <Engine/EntityComponent/Components/Material.h>

#include <Game/Components/CharacterController.h>

int main(int argc, char** argv)
{
	Window* window = new Window("Game Engine", 700, 500);
	Inputs* inputs = new Inputs();
	Renderer* render = new Renderer();

	MeshLoader loader = MeshLoader();
	Mesh pouleMesh = loader.LoadMesh("Ressources/Models/boss.obj");
	Mesh cubeMesh = loader.LoadMesh("Ressources/Models/default.obj");

	Scene mainScene;

	Entity* cube1 = mainScene.CreateObject("poule");
	Entity* poule = mainScene.CreateObject("poule2", cube1->Transform());
	Entity* character = mainScene.CreateObject("Character");
	Entity* cam = mainScene.CreateObject("Camera", character->Transform());

	cube1->AddComponent<StaticMesh>()->SetMesh(cubeMesh);
	cube1->Transform()->SetLocalRotation(glm::vec3(0.f, 180.f, 0.f));
	cube1->Transform()->Translate(glm::vec3(1.f, 0.f, 0.f), 10.f);
	cube1->Transform()->Scale(glm::vec3(1.f), .1f);
	cube1->AddComponent<Material>();

	poule->AddComponent<StaticMesh>()->SetMesh(pouleMesh);
	poule->Transform()->SetLocalPosition(glm::vec3(2.f, 2.f, 0.f));

	cam->AddComponent<Camera>();
	cam->Transform()->SetLocalPosition(glm::vec3(0.f, 2.f, 0.f));

	CharacterController* controller = character->AddComponent<CharacterController>();
	controller->camera = cam;
	character->AddComponent<StaticMesh>()->SetMesh(cubeMesh);
	controller->window = window;

	for (size_t i = 0; i < 50; i++)
	{
		Entity* tt = mainScene.CreateObject("");
		tt->AddComponent<StaticMesh>()->SetMesh(cubeMesh);
		tt->Transform()->Translate(glm::vec3(1.f, 0.f, 0.f), i * 3.f);
	}

	mainScene.BindInput(inputs);
	mainScene.Start();

	do
	{
		window->PoolEvent();
		inputs->UpdateInputs(window);
		mainScene.Update();

		mainScene.Render(render);
		render->Execute();

		window->SwapBuffer();
	} while (!window->IsClose());

	window->Terminate();

	return 0;
}