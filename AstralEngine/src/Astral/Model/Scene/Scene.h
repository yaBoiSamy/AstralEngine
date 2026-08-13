#pragma once
#include "Astral/Model/Entity.h"
#include "Astral/Model/Components/Camera/Camera.h"
#include "Astral/Application/Application.h"

namespace Astral {

	class Scene {
	public:
		Scene(Application* app, std::string name, ALayer* layer = nullptr);
		void SetMainCam(Camera* cam);
		void Draw();

		Entity root;
	private:
		Camera* main_camera;
		Application* app;
	};
}

