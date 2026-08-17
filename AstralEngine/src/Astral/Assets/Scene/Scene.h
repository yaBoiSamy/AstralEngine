#pragma once
#include "Astral/Assets/Asset.h"
#include "Astral/Misc/Entity.h"
#include "Astral/Components/Camera/Camera.h"
#include "Astral/Rendering/Invoker/Invoker.h"


namespace Astral::Assets {

	class Scene : public Asset {
	public:
		Scene(std::string name, Render::Invoker* renderer_invoker);
		void SetMainCam(Components::Camera* cam);
		void Draw(uint32_t frame_width, uint32_t frame_height);

		Astral::Entity root;
	private:
		Components::Camera* main_camera;
		Render::Invoker* renderer_invoker;
	};
}

