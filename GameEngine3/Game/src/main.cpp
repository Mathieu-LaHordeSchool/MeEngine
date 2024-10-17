
#include <glm/glm.hpp>
#include <iostream>

#include <me/Render/Window/Window.h>
#include <me/Core/Render/Mesh/Mesh.h>
#include <me/Core/Render/Mesh/MeshLoader.h>
#include <me/Core/Render/Texture/Texture.h>

#include <me/Core/Input/Inputs.h>
#include <me/Core/Input/KeyCode.h>

#include <me/Core/Scene.h>
#include <me/Core/Entity.h>
#include <me/Core/TransformData.h>
#include <me/Render/Renderer.h>

#include <me/Core/Components/Render/Camera.h>
#include <me/Core/Components/Render/StaticMesh.h>
#include <me/Core/Components/Render/Material.h>

#include <me/Core/ComponentsUI/UIElements.h>
#include <me/Core/ComponentsUI/Image.h>
#include <me/Core/ComponentsUI/Button.h>

#include <Components/CharacterController.h>

int main(int argc, char** argv)
{
	Window* window = new Window("Game Engine", 700, 500);
	Inputs* inputs = new Inputs(window);
	Renderer* render = new Renderer(window);
	
	MeshLoader loader = MeshLoader();
	Mesh pouleMesh = loader.LoadMesh("../Ressources/Models/boss.obj");
	Mesh cubeMesh = loader.LoadMesh("../Ressources/Models/default.obj");

	Texture* bg = new Texture("../Ressources/Textures/Test.png");
	Texture* boss = new Texture("../Ressources/Textures/Boss.png");

	Scene mainScene;

	Entity* poule = mainScene.CreateObject("poule");
	Entity* character = mainScene.CreateObject("Character");
	character->Transform()->SetLocalPosition(glm::vec3(0.f, -10.f, 5.f));

	Entity* cam = mainScene.CreateObject("Camera", character->Transform());
	Entity* ui = mainScene.CreateObject("ui");

	ui->AddComponent<Image>()->SetTexture(bg);
	Button* btn = ui->AddComponent<Button>();
	btn->SetOnClick([]() { std::cout << "click" << std::endl; });
	btn->SetOnEnter([]() { std::cout << "enter" << std::endl; });
	btn->SetOnExit([]() { std::cout << "exit" << std::endl; });

	ui->Transform()->SetLocalScale(glm::vec3(100.f));
	ui->Transform()->SetLocalPosition(glm::vec3(-.5f));

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
		inputs->UpdateInputs();

		 mainScene.Render(render);
		 render->Execute();

		mainScene.Update();
		window->SwapBuffer();
	} while (!window->IsClose());

	window->Terminate();

	return 0;
}

#if NDEBUG
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	// Initialisez votre fenêtre GLFW ici
	return 0;
}
#endif