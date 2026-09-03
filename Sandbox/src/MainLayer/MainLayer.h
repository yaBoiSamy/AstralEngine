#pragma once
#include <Astral.h>

class Astral::App::Application;

class MainLayer : public Astral::App::ALayer {
public:
	MainLayer(Astral::App::Application* app);
	virtual void OnAttach() override;
	virtual void OnUpdate(const Astral::App::FrameContext& context) override;
	virtual void OnRenderUI() override;
	virtual bool OnMouseMovedEvent(const Astral::App::MouseMovedEvent& event) override;
	virtual bool OnMouseScrolledEvent(const Astral::App::MouseScrolledEvent& event) override;
	virtual bool OnMouseButtonPressedEvent(const Astral::App::MouseButtonPressedEvent& event) override;
	virtual bool OnKeyPressedEvent(const Astral::App::KeyPressedEvent& event) override;

private:
	double frametime = 0;
	float circle_radius = 0.5f;
	bool is_roaming = false;
};
