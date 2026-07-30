#pragma once
#include "Common.h"
#include "Astral/Model/Entity.h"
#include "Astral/Rendering/Buffers/Buffers.h"


namespace Astral {
	using namespace glm;
	class Camera : public AComponent {
	public:
		Camera(double fov, double near_plane, double far_plane);

		void SetPerspective(double fov, double near_plane, double far_plane);
		void UpdateRenderedPOV();

	private:
		mat4 ViewMatrix();
		mat4 ProjectionMatrix();

		double fov;
		double near_plane;
		double far_plane;
	};
}

