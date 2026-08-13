#pragma once
#include "Common.h"
#include "Astral/Model/Entity.h"
#include "Astral/Rendering/Buffers/Buffers.h"
#include "Astral/Events/EventHandlers/EventHandlers.h"


namespace Astral {
	using namespace glm;
	class Camera : public AComponent {
	public:
		Camera(double fov, double near_plane, double far_plane);

		void SetPerspective(double fov, double near_plane, double far_plane);
		void UpdateRenderedPOV(uint32_t frame_width, uint32_t frame_height);

	private:
		mat4 ViewMatrix();
		mat4 ProjectionMatrix(uint32_t frame_width, uint32_t frame_height);

		double fov;
		double near_plane;
		double far_plane;
	};
}

