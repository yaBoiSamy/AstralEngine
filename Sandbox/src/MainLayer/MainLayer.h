#pragma once
#include <Astral.h>


class MainLayer : public Astral::App::ALayer {
public:
	MainLayer();
	virtual void OnAttach() override;
	virtual void OnUpdate(const Astral::App::FrameContext& context) override;
	virtual bool OnKeyPressedEvent(const Astral::App::KeyPressedEvent& event) override;
};
