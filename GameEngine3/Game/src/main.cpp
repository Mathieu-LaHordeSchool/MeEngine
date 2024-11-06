
#include <glm/glm.hpp>
#include <iostream>

#include <me/Core/Core.h>

#include <me/Core/Render/Mesh/Mesh.h>
#include <me/Core/Render/Mesh/MeshLoader.h>
#include <me/Core/Render/Texture/Texture.h>

#include <me/Core/Scene.h>
#include <me/Core/Entity.h>
#include <me/Core/TransformData.h>

#include <me/Core/Components/Render/Camera.h>
#include <me/Core/Components/Render/StaticMesh.h>
#include <me/Core/Components/Render/Material.h>

#include <me/Core/UI/UIElements.h>
#include <me/Core/Components/UI/Image.h>
#include <me/Core/Components/UI/Button.h>

#include <Components/CharacterController.h>

int main(int argc, char** argv)
{
	me::core::CoreConfigs configs;
	configs.title = "A";
	configs.windowSize = glm::vec2(700.f, 500.f);
	me::core::Core::Global()->Initialize(configs);
	
	me::core::render::MeshLoader loader = me::core::render::MeshLoader();
	me::core::render::Mesh pouleMesh = loader.LoadMesh("../Ressources/Models/boss.obj");
	me::core::render::Mesh cubeMesh = loader.LoadMesh("../Ressources/Models/default.obj");

	me::core::render::Texture* bg = new me::core::render::Texture("../Ressources/Textures/Test.png");
	me::core::render::Texture* boss = new me::core::render::Texture("../Ressources/Textures/Boss.png");

	me::core::Scene* mainScene = new me::core::Scene;

	me::core::Entity* poule = mainScene->CreateObject("poule");
	me::core::Entity* character = mainScene->CreateObject("Character");
	me::core::Entity* cam = mainScene->CreateObject("Camera", character->Transform());

	me::core::Entity* ui = mainScene->CreateObject("button");
	me::core::Entity* uiC = mainScene->CreateObject("image", ui->Transform());

	ui->Transform()->SetLocalPosition(glm::vec3(50.f, 50.f, 0.f));
	ui->Transform()->SetLocalSize(glm::vec3(50.f));
	me::core::components::ui::Button* btn = ui->AddComponent<me::core::components::ui::Button>();
	btn->SetOnEnter([]() {std::cout << "Enter" << std::endl; });
	btn->SetOnExit([]() {std::cout << "Exit" << std::endl; });

	uiC->Transform()->SetLocalPosition(glm::vec3(30.f, 30.f, 0.f));
	uiC->Transform()->SetLocalSize(glm::vec3(15.f));
	auto* img = uiC->AddComponent<me::core::components::ui::Image>();
	img->color = glm::vec4(1.f, 0.f, 0.f, 1.f);
	img->order = 10;

	character->Transform()->SetLocalPosition(glm::vec3(0.f, -10.f, 5.f));
	poule->AddComponent<me::core::components::render::StaticMesh>()->SetMesh(pouleMesh);
	poule->Transform()->SetLocalPosition(glm::vec3(2.f, 2.f, 0.f));

	me::core::components::render::Material* mat = poule->AddComponent<me::core::components::render::Material>();
	mat->SetColor(glm::vec4(.3, .4, .5, 1.f));
	mat->SetAlbedoTexture(boss);

	cam->AddComponent<me::core::components::render::Camera>();
	cam->Transform()->SetLocalPosition(glm::vec3(0.f, 2.f, 0.f));

	CharacterController* controller = character->AddComponent<CharacterController>();
	controller->camera = cam;

	me::core::Core::Global()->LoadScene(mainScene);
	me::core::Core::Global()->Execute();

	return 0;
}

#if NDEBUG
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	// Initialisez votre fenêtre GLFW ici
	return 0;
}
#endif