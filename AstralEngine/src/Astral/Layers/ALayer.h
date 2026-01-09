#pragma once
#include <Common.h>

class ALayer
{
public:
	ALayer(const std::string name = "Layer") : debugName(name) {}

	virtual void OnAttach() = 0;
	virtual void OnDetach() = 0;
	virtual void OnUpdate() = 0;

	const std::string debugName;
};

