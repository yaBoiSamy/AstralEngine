#include <Astral.h>

class Sandbox : public Astral::Application {
private:
	const std::string VERTEX_DIR = "src/Shaders/vertex.vert.glsl";
	const std::string FRAGMENT_DIR = "src/Shaders/fragment.frag.glsl";
	const std::vector<Astral::Vertex> vertices = {
			{ // Bottom left red
				{ -0.5f, -0.5f, 0.0f },       // pos
				{ 1.0f, 0.0f, 0.0f, 1.0f },   // color
			},
			{ // Bottom right green
				{ 0.5f, -0.5f, 0.0f },
				{ 0.0f, 1.0f, 0.0f, 1.0f },
			},
			{ // Top center blue
				{ 0.0f,  0.5f, 0.0f },
				{ 0.0f, 0.0f, 1.0f, 1.0f },
			}
	};
	const std::vector<uint32_t> indices = {
		0, 1, 2
	};
	const Astral::MeshData MESH_DATA = Astral::MeshData(std::move(vertices), std::move(indices));


	Astral::Shader shader;
	Astral::Scene scene;

public:
	Sandbox(const Astral::StartupConfig& config) : 
		Astral::Application(config), 
		shader(VERTEX_DIR, FRAGMENT_DIR) {

		AST_USER_INFO("Hello from Sandbox Application!");

		shader.Bind();

		ptr<Astral::Entity> triangle = std::make_unique<Astral::Entity>("triangole");
		ptr<Astral::Mesh> triangle_mesh_component = std::make_unique<Astral::Mesh>(&MESH_DATA);
		triangle->AddComponent(std::move(triangle_mesh_component));
		scene.root.AddChild(std::move(triangle));

	}

	void Update() override {
		scene.Draw();
	}

	virtual bool OnKeyPressedEvent(const Astral::KeyPressedEvent& event) override {
		AST_USER_INFO("Key Pressed: {0} (repeats: {1})", event.keycode, event.repeatCount);
		return false;
	}
};

Astral::Application* Astral::CreateApplication(Astral::StartupConfig& config) {
	return new Sandbox(config);
}
