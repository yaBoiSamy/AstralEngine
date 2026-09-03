#pragma once
#include <Astral.h>
#include <imgui.h>
#include "MainLayer.h"

using namespace Astral;
using namespace Astral::Components;
using namespace Astral::Assets;

MainLayer::MainLayer(App::Application* app) : ALayer(app, "Main layer") {}


void MainLayer::OnAttach() {
	Scene* scene = Assets().FetchScene("MainScene");

	Box<Entity> circle = std::make_unique<Entity>("circle");
	Box<MeshRenderer> circle_mesh_component = std::make_unique<MeshRenderer>(Assets().FetchMesh("Billboard"), Assets().FetchMaterial("white circle"));
	circle->AddComponent(std::move(circle_mesh_component));
	scene->root.AddChild(std::move(circle));

	Box<Entity> maincam = std::make_unique<Entity>("cam");
	Box<Camera> cam_component = std::make_unique<Camera>(
		45,                 // FOV (degrees)
		0.1,                // near plane
		100                 // far plane
	);
	scene->SetMainCam(cam_component.get());
	maincam->AddComponent(std::move(cam_component));
	scene->root.AddChild(std::move(maincam));

	Transform& circle_tr = *scene->root.Child("circle")->GetComponent<Transform>();
	Transform& cam_tr = *scene->root.Child("cam")->GetComponent<Transform>();

	cam_tr.Translate(glm::vec3(0, 0, 2));
}


void MainLayer::OnUpdate(const App::FrameContext& context) {
	Scene& scene = *Assets().FetchScene("MainScene");
	Entity& root = scene.root;
	Entity& circle = *root.Child("circle");
	Transform& circle_tr = *circle.GetComponent<Transform>();

	frametime = context.window_snapshot.deltatime;
	circle_tr.local_scale = glm::vec3(circle_radius, circle_radius, 1.0f);
	scene.Draw(context.window_snapshot.frame_width, context.window_snapshot.frame_height);
}

void MainLayer::OnRenderUI() {
	ImGui::Begin("Frame data");
	if (frametime != 0) {
		ImGui::Text("FPS: %.0f", 1 / frametime);
		ImGui::Text("Frametime: %.3f", frametime);
	}
	ImGui::End();
	ImGui::Begin("circle radius");
	ImGui::SliderFloat("circle radius", &circle_radius, 0.1f, 1.0f);
	ImGui::End();
}

bool MainLayer::OnMouseMovedEvent(const Astral::App::MouseMovedEvent& event) {
	if (!is_roaming)
		return false;
	const double rotation_speed = 0.001;
	Entity& root = Assets().FetchScene("MainScene")->root;
	Transform& cam_tr = *root.Child("cam")->GetComponent<Transform>();
	glm::dquat yaw = glm::angleAxis(-event.dx * rotation_speed, dvec3(0, 1, 0));
	glm::dquat pitch = glm::angleAxis(-event.dy * rotation_speed, dvec3(1, 0, 0));
	cam_tr.LocalRotate(pitch);
	cam_tr.GlobalRotate(yaw);
	return false;
}

bool MainLayer::OnMouseScrolledEvent(const Astral::App::MouseScrolledEvent& event) {
	if (!is_roaming)
		return false;
	const double translation_speed = 0.1;
	Entity& root = Assets().FetchScene("MainScene")->root;
	Transform& cam_tr = *root.Child("cam")->GetComponent<Transform>();
	cam_tr.Translate(event.y_offset * translation_speed * cam_tr.Forward());
	return false;
}

bool MainLayer::OnMouseButtonPressedEvent(const App::MouseButtonPressedEvent& event) {
	if (event.button == AST_MOUSE_BUTTON_LEFT && !is_roaming) {
		App().SetCursorEnabled(false);
		is_roaming = true;
		return true;
	}
	return false;
}

bool MainLayer::OnKeyPressedEvent(const App::KeyPressedEvent& event) {
	if (event.keycode == AST_KEY_ESCAPE && is_roaming) {
		App().SetCursorEnabled(true);
		is_roaming = false;
	}
	return false;
}
