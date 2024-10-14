
#include <glm/glm.hpp>
#include <iostream>

#include <Engine/Window/Window.h>
#include <Engine/Mesh/Mesh.h>
#include <Engine/Mesh/MeshLoader.h>
#include <Engine/Texture/Texture.h>

#include <Engine/Input/Inputs.h>
#include <Engine/Input/KeyCode.h>

#include <Engine/EntityComponent/Scene.h>
#include <Engine/EntityComponent/Entity.h>
#include <Engine/EntityComponent/TransformData.h>
#include <Engine/RendererObject/Renderer.h>

#include <Engine/EntityComponent/Components/Camera.h>
#include <Engine/EntityComponent/Components/StaticMesh.h>
#include <Engine/EntityComponent/Components/Material.h>

#include <Engine/EntityComponent/UIComponents/UIElements.h>
#include <Engine/EntityComponent/UIComponents/Image.h>

#include <Game/Components/CharacterController.h>

int main(int argc, char** argv)
{
	Window* window = new Window("Game Engine", 700, 500);
	Inputs* inputs = new Inputs();
	Renderer* render = new Renderer(window);

	MeshLoader loader = MeshLoader();
	Mesh pouleMesh = loader.LoadMesh("Ressources/Models/boss.obj");
	Mesh cubeMesh = loader.LoadMesh("Ressources/Models/default.obj");

	Texture* bg = new Texture("Ressources/Textures/Test.png");
	Texture* boss = new Texture("Ressources/Textures/Boss.png");

	Scene mainScene;

	Entity* poule = mainScene.CreateObject("poule");
	Entity* character = mainScene.CreateObject("Character");
	character->Transform()->SetLocalPosition(glm::vec3(0.f, -10.f, 5.f));

	Entity* cam = mainScene.CreateObject("Camera", character->Transform());
	Entity* ui = mainScene.CreateObject("ui");

	ui->AddComponent<Image>()->SetTexture(bg);
	ui->GetComponent<Image>()->color.a = .5f;
	ui->Transform()->SetLocalScale(glm::vec3(.5f));
	ui->Transform()->SetLocalPosition(glm::vec3(-0.75f));

	poule->AddComponent<StaticMesh>()->SetMesh(pouleMesh);
	poule->Transform()->SetLocalPosition(glm::vec3(2.f, 2.f, 0.f));
	poule->Transform()->SetLocalScale(glm::vec3(10.f));

	Material* mat = poule->AddComponent<Material>();
	mat->SetColor(glm::vec4(.3, .4, .5, 1.f));
	mat->SetAlbedoTexture(boss);

	cam->AddComponent<Camera>();
	cam->Transform()->SetLocalPosition(glm::vec3(0.f, 2.f, 0.f));

	CharacterController* controller = character->AddComponent<CharacterController>();
	controller->camera = cam;
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