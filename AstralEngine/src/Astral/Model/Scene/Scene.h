#pragma once
#include "Astral/Model/Entity.h"
#include "Astral/Model/Components/Camera/Camera.h"

namespace Astral {

	class Scene {
	public:
		Scene();
		void SetMainCam(Camera* cam);
		void Draw();

		Entity root;
	private:
		void FindDefaultMainCam();

		Camera* main_camera;
	};
}

