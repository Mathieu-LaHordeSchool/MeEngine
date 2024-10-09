
#include <glm/glm.hpp>

#include <Window/Window.h>
#include <Mesh/Mesh.h>
#include <Mesh/MeshLoader.h>

#include <Input/Inputs.h>
#include <Input/KeyCode.h>

#include <EntityComponent/Scene.h>
#include <EntityComponent/Entity.h>
#include <EntityComponent/TransformData.h>
#include <RendererObject/Renderer.h>

#include <EntityComponent/Components/Camera.h>
#include <EntityComponent/Components/StaticMesh.h>

int main(int argc, char** argv)
{
	Window* window = new Window("Game Engine", 700, 500);
	Inputs* inputs = new Inputs();
	Renderer* render = new Renderer();

	MeshLoader loader = MeshLoader();
	Mesh pouleMesh = loader.LoadMesh("Models/boss.obj");

	Scene* mainScene = new Scene();

	Entity* poule = mainScene->CreateObject("poule");
	poule->Transform()->rotation.y = 180.f;

	Entity* cam = mainScene->CreateObject("Camera");

	poule->AddComponent<StaticMesh>()->SetMesh(pouleMesh);
	cam->AddComponent<Camera>();

	float speed = .1f;	
	inputs->CreateInputAction("z", KeyCode::W)->BindPressAction([&](HandleTimer t) {
		cam->Transform()->position.z += speed;
	});
	inputs->CreateInputAction("s", KeyCode::S)->BindPressAction([&](HandleTimer t) {
		cam->Transform()->position.z -= speed;
	});

	do
	{
		window->PoolEvent();
		inputs->UpdateInputs(window);

		mainScene->Render(render);
		render->Execute();

		window->SwapBuffer();
	} while (!window->IsClose());

	window->Terminate();

	return 0;
}