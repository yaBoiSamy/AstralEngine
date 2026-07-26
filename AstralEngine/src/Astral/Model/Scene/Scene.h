#pragma once
#include "Astral/Model/Entity.h"

namespace Astral {

	class Scene {
	public:
		Scene() = default;
		void Draw();

		Entity root;
	};
}

