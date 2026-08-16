#pragma once
#include "Astral/Assets/Asset.h"
#include "Astral/Misc/Entity.h"
#include "Astral/Components/Camera/Camera.h"


namespace Astral::Assets {

	class Scene : public Asset {
	public:
		Scene(std::string name);
		void SetMainCam(Components::Camera* cam);
		void Draw(uint32_t frame_width, uint32_t frame_height);

		Astral::Entity root;
	private:
		Components::Camera* main_camera;
	};
}

