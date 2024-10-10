
#include <glm/glm.hpp>

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

	Scene mainScene;

	Entity* poule = mainScene.CreateObject("poule");
	Entity* poule2 = mainScene.CreateObject("poule2", poule->Transform());

	Entity* character = mainScene.CreateObject("Character");
	Entity* cam = mainScene.CreateObject("Camera");

	character->Transform()->SetPosition(glm::vec3(0.f, 3.f, 0.f));
	poule->Transform()->SetRotation(glm::vec3(90.f, 180.f, 0.f));
	poule2->Transform()->SetPosition(glm::vec3(0.f, 2.f, 0.f));

	poule->AddComponent<StaticMesh>()->SetMesh(pouleMesh);
	poule2->AddComponent<StaticMesh>()->SetMesh(pouleMesh);
	cam->AddComponent<CharacterController>();
	cam->AddComponent<Camera>();

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