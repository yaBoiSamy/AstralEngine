#include <Astral.h>


class Sandbox : public Astral::Application {
public:
	Sandbox() {}
	~Sandbox() {}
};

Astral::Application* Astral::CreateApplication() {
	return new Sandbox();
}