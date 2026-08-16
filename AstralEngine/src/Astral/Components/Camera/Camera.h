#pragma once
#include "Common.h"
#include "Astral/Components/Component.h"


namespace Astral::Components {
	using namespace glm;
	class Camera : public AComponent {
	public:
		Camera(double fov, double near_plane, double far_plane);

		void SetPerspective(double fov, double near_plane, double far_plane);
		void UpdateRenderedPOV(uint32_t frame_width, uint32_t frame_height);

	private:
		mat4 ViewMatrix() const;
		mat4 ProjectionMatrix(uint32_t frame_width, uint32_t frame_height) const;

		double fov;
		double near_plane;
		double far_plane;
	};
}

