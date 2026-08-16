#include <Astral.h>
#include <filesystem>
#include "MainLayer/MainLayer.h"

using namespace Astral;

class Sandbox : public App::Application {
private:
    std::filesystem::path TEXTURE_DIR = "resources/finger.png";
    std::vector<Assets::Vertex> vertices = {
        // Front
        { { -0.5f, -0.5f,  0.5f }, { 0, 0 } }, // 0
        { {  0.5f, -0.5f,  0.5f }, { 1, 0 } }, // 1
        { {  0.5f,  0.5f,  0.5f }, { 1, 1 } }, // 2
        { { -0.5f,  0.5f,  0.5f }, { 0, 1 } }, // 3

        // Right
        { {  0.5f, -0.5f,  0.5f }, { 0, 0 } }, // 4
        { {  0.5f, -0.5f, -0.5f }, { 1, 0 } }, // 5
        { {  0.5f,  0.5f, -0.5f }, { 1, 1 } }, // 6
        { {  0.5f,  0.5f,  0.5f }, { 0, 1 } }, // 7

        // Back
        { {  0.5f, -0.5f, -0.5f }, { 0, 0 } }, // 8
        { { -0.5f, -0.5f, -0.5f }, { 1, 0 } }, // 9
        { { -0.5f,  0.5f, -0.5f }, { 1, 1 } }, // 10
        { {  0.5f,  0.5f, -0.5f }, { 0, 1 } }, // 11

        // Left
        { { -0.5f, -0.5f, -0.5f }, { 0, 0 } }, // 12
        { { -0.5f, -0.5f,  0.5f }, { 1, 0 } }, // 13
        { { -0.5f,  0.5f,  0.5f }, { 1, 1 } }, // 14
        { { -0.5f,  0.5f, -0.5f }, { 0, 1 } }, // 15

        // Top
        { { -0.5f,  0.5f,  0.5f }, { 0, 0 } }, // 16
        { {  0.5f,  0.5f,  0.5f }, { 1, 0 } }, // 17
        { {  0.5f,  0.5f, -0.5f }, { 1, 1 } }, // 18
        { { -0.5f,  0.5f, -0.5f }, { 0, 1 } }, // 19

        // Bottom
        { { -0.5f, -0.5f, -0.5f }, { 0, 0 } }, // 20
        { {  0.5f, -0.5f, -0.5f }, { 1, 0 } }, // 21
        { {  0.5f, -0.5f,  0.5f }, { 1, 1 } }, // 22
        { { -0.5f, -0.5f,  0.5f }, { 0, 1 } }, // 23
    };

    std::vector<uint32_t> indices = {
        // Front
        0, 1, 2,  2, 3, 0,

        // Right
        4, 5, 6,  6, 7, 4,

        // Back
        8, 9, 10, 10, 11, 8,

        // Left
        12, 13, 14, 14, 15, 12,

        // Top
        16, 17, 18, 18, 19, 16,

        // Bottom
        20, 21, 22, 22, 23, 20
    };

public:

	Sandbox(const App::StartupConfig& config) : Application(config) {

        Box<Assets::Scene> scene = std::make_unique<Assets::Scene>("MainScene");
        Box<Assets::Mesh> cube_mesh = std::make_unique<Assets::Mesh>("Cube mesh", std::move(vertices), std::move(indices));
        Box<Assets::Texture> texture = std::make_unique<Assets::Texture>(TEXTURE_DIR);
        Box<Assets::Material> material = std::make_unique<Assets::Material>("fuckyou mat", Assets().Fetch<Assets::Shader>("Flat Shader"), glm::vec4(1, 1, 1, 0), texture.get());

        Assets().Load<Assets::Scene>(std::move(scene));
        Assets().Load<Assets::Mesh>(std::move(cube_mesh));
        Assets().Load<Assets::Texture>(std::move(texture));
        Assets().Load<Assets::Material>(std::move(material));

        Box<MainLayer> main_layer = std::make_unique<MainLayer>();
        Layers().PushLayer(std::move(main_layer));

	}

	virtual void Update(const App::FrameContext& context) override {}

	virtual bool OnKeyPressedEvent(const App::KeyPressedEvent& event) override {
		AST_USER_INFO("Key Pressed: {0} (repeats: {1})", event.keycode, event.repeat_count);
		return false;
	}
};

App::Application* App::CreateApplication(App::StartupConfig& config) {
	return new Sandbox(config);
}
