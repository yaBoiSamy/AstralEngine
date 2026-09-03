#include <Astral.h>
#include <filesystem>
#include "MainLayer/MainLayer.h"

using namespace Astral;

class Sandbox : public App::Application {
public:

	Sandbox(const App::StartupConfig& config) : Application(config) {

		Assets::Texture* circle_texture = Assets().CreateTexture("circle", "resources/circle.png");
        Assets::Shader* flat_shader = Assets().FetchShader("Flat");
		Assets().CreateMaterial("white circle", flat_shader, glm::vec4(1, 1, 1, 1), circle_texture);

        Assets::Scene* main_scene = Assets().CreateScene("MainScene");

        Box<MainLayer> main_layer = std::make_unique<MainLayer>(this);
        Layers().PushLayer(std::move(main_layer));
	}
};

App::Application* App::CreateApplication(App::StartupConfig& config) {
	return new Sandbox(config);
}
