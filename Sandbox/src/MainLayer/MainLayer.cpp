#pragma once
#include <Astral.h>
#include "MainLayer.h"

using namespace Astral;


MainLayer::MainLayer() : ALayer("Main layer") {}


void MainLayer::OnAttach() {
	Assets::Scene* scene = Assets().FetchScene("MainScene");

	Box<Entity> cube = std::make_unique<Entity>("cube");
	Box<Components::MeshRenderer> cube_mesh_component = std::make_unique<Components::MeshRenderer>(Assets().FetchMesh("Cube mesh"), Assets().FetchMaterial("Finger mat"));
	cube->AddComponent(std::move(cube_mesh_component));
	scene->root.AddChild(std::move(cube));

	Box<Entity> cam_parent = std::make_unique<Entity>("cam_dad");
	Box<Entity> maincam = std::make_unique<Entity>("cam");
	Box<Components::Camera> cam_component = std::make_unique<Components::Camera>(
		45,                 // FOV (degrees)
		0.1,                // near plane
		100                 // far plane
	);
	scene->SetMainCam(cam_component.get());
	maincam->AddComponent(std::move(cam_component));
	cam_parent->AddChild(std::move(maincam));
	scene->root.AddChild(std::move(cam_parent));

	Components::Transform& cube_tr = *scene->root.Child("cube")->GetComponent<Components::Transform>();
	Components::Transform& camdad_tr = *scene->root.Child("cam_dad")->GetComponent<Components::Transform>();
	Components::Camera& cam = *scene->root.Child("cam_dad")->Child("cam")->GetComponent<Components::Camera>();
	Components::Transform& cam_tr = *scene->root.Child("cam_dad")->Child("cam")->GetComponent<Components::Transform>();

	cam_tr.Translate(glm::vec3(0, 2, 2));
	cam_tr.LookAt(cube_tr.Position());
}


void MainLayer::OnUpdate(const App::FrameContext& context) {
	Assets::Scene* scene = Assets().FetchScene("MainScene");

	const double cube_rotspeed = 1;
	const double cam_rotspeed = 0.25;
	const double cube_oscillationspeed = 1;
	static double time = 0;
	double deltatime = context.window_snapshot.deltatime;
	//AST_CORE_INFO("FPS: {}", 1 / deltatime);
	scene->root.Child("cube")->transform().Rotate(glm::quat(glm::vec3(0, deltatime * cube_rotspeed, 0)));
	scene->root.Child("cam_dad")->transform().Rotate(glm::quat(glm::vec3(deltatime * cam_rotspeed, 0, 0)));
	//scene.root.Child("cube")->transform().local_scale = glm::dvec3(1.0f) * glm::sin(time * cube_oscillationspeed);
	time += deltatime;
}


bool MainLayer::OnKeyPressedEvent(const App::KeyPressedEvent& event) {
	AST_USER_INFO("Key Pressed: {0} (repeats: {1})", event.keycode, event.repeat_count);
	return false;
}
