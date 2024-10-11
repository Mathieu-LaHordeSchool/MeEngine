
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
	Renderer* render = new Renderer(window);

	MeshLoader loader = MeshLoader();
	Mesh pouleMesh = loader.LoadMesh("Ressources/Models/boss.obj");
	Mesh cubeMesh = loader.LoadMesh("Ressources/Models/default.obj");

	Scene mainScene;

	Entity* poule = mainScene.CreateObject("poule");
	Entity* character = mainScene.CreateObject("Character");
	Entity* cam = mainScene.CreateObject("Camera", character->Transform());

	Entity* min = mainScene.CreateObject("", poule->Transform());
	min->AddComponent<StaticMesh>()->SetMesh(cubeMesh);
	min->Transform()->SetWorldScale(glm::vec3(.1f));

	Entity* max = mainScene.CreateObject("", poule->Transform());
	max->AddComponent<StaticMesh>()->SetMesh(cubeMesh);
	max->Transform()->SetWorldScale(glm::vec3(.1f));

	poule->AddComponent<StaticMesh>()->SetMesh(pouleMesh);
	poule->Transform()->SetLocalPosition(glm::vec3(2.f, 2.f, 0.f));
	Material* mat = poule->AddComponent<Material>();
	mat->SetColor(glm::vec4(.3, .4, .5, 1.f));

	glm::vec3 posMin, posMax;
	pouleMesh.GetBoundsMesh(posMin, posMax);
	min->Transform()->SetLocalPosition(posMin);
	max->Transform()->SetLocalPosition(posMax);

	cam->AddComponent<Camera>();
	cam->Transform()->SetLocalPosition(glm::vec3(0.f, 2.f, 0.f));

	CharacterController* controller = character->AddComponent<CharacterController>();
	controller->camera = cam;
	character->AddComponent<StaticMesh>()->SetMesh(cubeMesh);
	controller->window = window;

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