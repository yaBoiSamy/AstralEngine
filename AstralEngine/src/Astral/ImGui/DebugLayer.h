#pragma once
#include "Astral/Layers/ALayer.h"

class DebugLayer : public ALayer
{
public:
	DebugLayer();
	~DebugLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
};

