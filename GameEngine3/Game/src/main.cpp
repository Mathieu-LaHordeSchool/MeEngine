
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
#include <glm/ext/matrix_transform.hpp>

int main(int argc, char** argv)
{
	me::core::CoreConfigs configs;
	configs.title = "A";
	configs.windowSize = glm::vec2(700.f, 500.f);
	configs.resezable = true;
	me::core::Core::Global()->Initialize(configs);
	
	me::core::render::MeshLoader loader = me::core::render::MeshLoader();
	me::core::render::Mesh pouleMesh = loader.LoadMesh("../Ressources/Models/boss.obj");
	me::core::render::Mesh cubeMesh = loader.LoadMesh("../Ressources/Models/default.obj");

	me::core::render::Texture* bg = new me::core::render::Texture("../Ressources/Textures/Test.png");
	me::core::render::Texture* boss = new me::core::render::Texture("../Ressources/Textures/Boss.png");

	me::core::Scene* mainScene = new me::core::Scene;

	me::core::Entity* character = mainScene->CreateObject("Character");
	me::core::Entity* cam = mainScene->CreateObject("Camera", character->Transform());

	me::core::Entity* ui = mainScene->CreateObject("button");
	me::core::Entity* uiC = mainScene->CreateObject("image", ui->Transform());

	me::core::Entity* poule = mainScene->CreateObject("poule");
	
	character->Transform()->SetLocalPosition(glm::vec3(0.f, 0.f, 5.f));
	CharacterController* controller = character->AddComponent<CharacterController>();
	controller->camera = cam;

	cam->AddComponent<me::core::components::render::Camera>();
	cam->Transform()->SetLocalPosition(glm::vec3(0.f, 2.f, 0.f));
	
	me::core::components::render::StaticMesh* mesh = poule->AddComponent<me::core::components::render::StaticMesh>();
	mesh->SetMesh(pouleMesh);

	poule->Transform()->SetLocalPosition(glm::vec3(0.f, 0.f, 0.f));
	
	me::core::Core::Global()->LoadScene(mainScene);
	me::core::Core::Global()->Execute();
	
	return 0;
}

#if NDEBUG
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	// Initialisez votre fen?tre GLFW ici
	return 0;
}
#endif