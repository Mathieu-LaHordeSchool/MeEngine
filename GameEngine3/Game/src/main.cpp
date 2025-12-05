
#include <glm/glm.hpp>
#include <iostream>
#include <string>

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
#include <glm/detail/type_quat.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>

int main(int argc, char** argv)
{
	// shop update a
	me::core::CoreConfigs configs;
	configs.title = "A";
	configs.windowSize = glm::vec2(700.f, 500.f);
	configs.resezable = true;
	me::core::Core::Global()->Initialize(configs);

	me::core::render::MeshLoader loader = me::core::render::MeshLoader();
	me::core::render::Mesh pouleMesh = loader.LoadObjMesh("../Ressources/Models/boss.obj");
	me::core::render::Mesh cubeMesh = loader.LoadObjMesh("../Ressources/Models/default.obj");
	// me::core::render::Mesh mapMesh = loader.LoadObjMesh("../Ressources/Models/Map.obj");
	me::core::render::Mesh platfomr = loader.LoadObjMesh("../Ressources/Models/platforme2.obj");
	
	me::core::render::Texture* bg = new me::core::render::Texture("../Ressources/Textures/Test.png");
	me::core::render::Texture* boss = new me::core::render::Texture("../Ressources/Textures/Boss.jpg");
	me::core::render::Texture* mapTexture = new me::core::render::Texture("../Ressources/Textures/Map.png");
	
	me::core::Scene* mainScene = new me::core::Scene;

	me::core::Entity* character = mainScene->CreateObject("Character");
	me::core::Entity* cam = mainScene->CreateObject("Camera", character->Transform());

	me::core::Entity* ui = mainScene->CreateObject("button");
	me::core::Entity* uiC = mainScene->CreateObject("image", ui->Transform());

	me::core::Entity* map = mainScene->CreateObject("map");

	me::core::components::ui::Button* btn = ui->AddComponent<me::core::components::ui::Button>();
	btn->SetOnClick([&]() {std::cout << "Click" << std::endl; });
	btn->SetOnEnter([&]() {std::cout << "Enter" << std::endl; });
	btn->SetOnExit([&]() {std::cout << "exit" << std::endl; });

	map->AddComponent<me::core::components::render::StaticMesh>()->SetMesh(pouleMesh);
	map->AddComponent<me::core::components::render::Material>()->SetAlbedoTexture(boss);

	ui->Transform()->SetLocalSize(glm::vec3(50.f));
	ui->Transform()->SetLocalPosition(glm::vec3(50.f, 50.f, 0.f));
	
	character->Transform()->SetLocalPosition(glm::vec3(0.f, 0.f, 5.f));
	CharacterController* controller = character->AddComponent<CharacterController>();
	controller->camera = cam;

	cam->AddComponent<me::core::components::render::Camera>();
	cam->Transform()->SetLocalPosition(glm::vec3(0.f, 2.f, 0.f));
	
	me::core::Core::Global()->LoadScene(mainScene);
	me::core::Core::Global()->Execute();
	
	return 0;
}

#pragma region DontTuchOrKYS

#if NDEBUG
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	// Initialisez votre fen?tre GLFW ici
	return 0;
}
#endif

#pragma endregion