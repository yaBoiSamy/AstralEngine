#include <Astral.h>

class Sandbox : public Astral::Application {
private:
	const std::string VERTEX_DIR = "src/Shaders/vertex.vert.glsl";
	const std::string FRAGMENT_DIR = "src/Shaders/fragment.frag.glsl";
    const std::string TEXTURE_DIR = "resources/checkmark.png";
    const std::vector<Astral::Vertex> vertices = {
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

    const std::vector<uint32_t> indices = {
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
	const Astral::Mesh MESH = Astral::Mesh(std::move(vertices), std::move(indices));

    ptr<Astral::Scene> scene;
	ptr<Astral::Shader> shader;
    ptr<Astral::Texture> texture;
    ptr<Astral::Material> material;

public:

	Sandbox(const Astral::StartupConfig& config) : 
		Astral::Application(config), 
        scene(std::make_unique<Astral::Scene>()),
		shader(std::make_unique<Astral::Shader>(VERTEX_DIR, FRAGMENT_DIR)),
        texture(std::make_unique<Astral::Texture>(TEXTURE_DIR)),
        material(nullptr) {
        material = std::make_unique<Astral::Material>(shader.get(), glm::vec4(1, 1, 1, 0), texture.get());

		ptr<Astral::Entity> cube = std::make_unique<Astral::Entity>("cube");
        ptr<Astral::MeshRenderer> cube_mesh = std::make_unique<Astral::MeshRenderer>(&MESH, material.get());
        cube->AddComponent(std::move(cube_mesh));
		scene->root.AddChild(std::move(cube));

        ptr<Astral::Entity> cam_parent = std::make_unique<Astral::Entity>("cam_dad");
		ptr<Astral::Entity> maincam = std::make_unique<Astral::Entity>("cam");
        const Astral::FrameContext context = GetFrameContext();
		ptr<Astral::Camera> cam_component = std::make_unique<Astral::Camera>(
			45,                 // FOV (degrees)
			0.1,                // near plane
			100                 // far plane
		);
		scene->SetMainCam(cam_component.get());
		maincam->AddComponent(std::move(cam_component));
        cam_parent->AddChild(std::move(maincam));
		scene->root.AddChild(std::move(cam_parent));

        Astral::Transform& cube_tr = *scene->root.Child("cube")->GetComponent<Astral::Transform>();
        Astral::Transform& camdad_tr = *scene->root.Child("cam_dad")->GetComponent<Astral::Transform>();
        Astral::Camera& cam = *scene->root.Child("cam_dad")->Child("cam")->GetComponent<Astral::Camera>();
        Astral::Transform& cam_tr = *scene->root.Child("cam_dad")->Child("cam")->GetComponent<Astral::Transform>();

        cam_tr.Translate(glm::vec3(0, 2, 2));
        cam_tr.LookAt(cube_tr.Position());
	}

	void Update() override {
		const float cube_rotspeed = 1;
        const float cam_rotspeed = 0.25;
        const float cube_oscillationspeed = 1;
        const float cube_oscillationrange = 1;
        static double time = 0;
        const Astral::FrameContext context = GetFrameContext();
        //AST_CORE_INFO("FPS: {}", 1 / context.deltaTime);
		scene->root.Child("cube")->transform().Rotate(glm::quat(glm::vec3(0, context.deltaTime * cube_rotspeed, 0)));
        scene->root.Child("cam_dad")->transform().Rotate(glm::quat(glm::vec3(context.deltaTime * cam_rotspeed, 0, 0)));
        //scene.root.Child("cube")->transform().local_scale = glm::dvec3(1.0f) * glm::sin(time * cube_oscillationspeed);
		scene->Draw();
        time += context.deltaTime;
	}

	virtual bool OnKeyPressedEvent(const Astral::KeyPressedEvent& event) override {
		AST_USER_INFO("Key Pressed: {0} (repeats: {1})", event.keycode, event.repeatCount);
		return false;
	}
};

Astral::Application* Astral::CreateApplication(Astral::StartupConfig& config) {
	return new Sandbox(config);
}
