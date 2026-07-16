#include <Astral.h>

class Sandbox : public Astral::Application {
private:
	struct Vertex {
		Astral::Attr::Vec4 color;
		Astral::Attr::Vec2 pos;
	};

private:
	static const uint32_t VERT_COUNT = 3;
	static const uint32_t INDICES_COUNT = 3;

	const std::string VERTEX_DIR = "src/Shaders/vertex.vert.glsl";
	const std::string FRAGMENT_DIR = "src/Shaders/fragment.frag.glsl";

public:
	Sandbox(const Astral::StartupConfig& config) : 
		Astral::Application(config), 
		vertex_array(
			Astral::VertexArray<Vertex>(
				VERT_COUNT,
				INDICES_COUNT,
				Astral::UsageHint::Static,
				{
					Astral::Attr::Vec4::Layout(0, offsetof(Vertex, color)),
					Astral::Attr::Vec2::Layout(1, offsetof(Vertex, pos)),
				},
				Astral::UsageHint::Static
			)
		),
		shader(VERTEX_DIR, FRAGMENT_DIR)
	{
		Start();
	}
	~Sandbox() {}


	void Start() {
		AST_USER_INFO("Hello from Sandbox Application!");

		shader.Bind();
		Vertex vertices[VERT_COUNT] = {
			{ // Bottom left red
				{ 1.0f, 0.0f, 0.0f, 1.0f },   // color
				{ -0.5f, -0.5f }              // pos
			},
			{ // Bottom right green
				{ 0.0f, 1.0f, 0.0f, 1.0f },
				{  0.5f, -0.5f }
			},
			{ // Top center blue
				{ 0.0f, 0.0f, 1.0f, 1.0f },
				{  0.0f,  0.5f }
			}
		};
		vertex_array.WriteVertices(0, std::span<Vertex, VERT_COUNT>(vertices));

		uint32_t indices[INDICES_COUNT] = {
			0, 1, 2
		};
		vertex_array.WriteIndices(0, std::span<uint32_t, INDICES_COUNT>(indices));
	}

	void Update() override {
		shader.Bind();
		Astral::Renderer::Submit(vertex_array);
	}

	virtual bool OnKeyPressedEvent(const Astral::KeyPressedEvent& event) override {
		AST_USER_INFO("Key Pressed: {0} (repeats: {1})", event.keycode, event.repeatCount);
		return false;
	}

	Astral::Shader shader;
	Astral::VertexArray<Vertex> vertex_array;
};

Astral::Application* Astral::CreateApplication(Astral::StartupConfig& config) {
	return new Sandbox(config);
}

/*

Severity	Code	Description	Project	File	Line	Suppression State	Details
Error	LNK2019	unresolved external symbol "private: virtual unsigned int __cdecl Astral::ABuffer<struct Sandbox::Vertex>::GLTarget(void)const " (?GLTarget@?$ABuffer@UVertex@Sandbox@@@Astral@@EEBAIXZ) referenced in function "public: __cdecl Astral::ABuffer<struct Sandbox::Vertex>::ABuffer<struct Sandbox::Vertex>(unsigned int,enum Astral::UsageHint)" (??0?$ABuffer@UVertex@Sandbox@@@Astral@@QEAA@IW4UsageHint@1@@Z)	Sandbox	S:\CPP\AstralEngine\Sandbox\SandboxApp.obj	1

*/
