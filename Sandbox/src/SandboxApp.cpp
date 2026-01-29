#include <Astral.h>

class Sandbox : public Astral::Application {
public:
	Sandbox(const Astral::StartupConfig& config) : Astral::Application(config) {}
	~Sandbox() {}

	void Start() override {
		AST_USER_INFO("Hello from Sandbox Application!");
	}

	void Update() override {
	}

	virtual bool OnKeyPressedEvent(const Astral::KeyPressedEvent& event) override {
		AST_USER_INFO("Key Pressed: {0} (repeats: {1})", event.keycode, event.repeatCount);
		return false;
	}
};

Astral::Application* Astral::CreateApplication(Astral::StartupConfig& config) {
	return new Sandbox(config);
}