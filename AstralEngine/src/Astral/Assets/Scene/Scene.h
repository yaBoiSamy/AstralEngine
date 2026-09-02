#pragma once
#include "Astral/Assets/Asset.h"
#include "Astral/Misc/Entity.h"
#include "Astral/Components/Camera/Camera.h"
#include "Astral/Rendering/Renderer/Renderer.h"


namespace Astral::Assets {

	class Scene : public Asset {
	public:
		Scene(Render::Renderer* renderer, std::string name);
		void SetMainCam(Components::Camera* cam);
		void Draw(uint32_t frame_width, uint32_t frame_height);

		Astral::Entity root;
	private:
		Render::Renderer* renderer;
		Components::Camera* main_camera;
	};
}

