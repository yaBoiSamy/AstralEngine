#pragma once
#include "Astral/Rendering/OpenGLTranslations.h"
#include <glad/glad.h>


namespace Astral {

	struct AttributeLayout {
		template <typename FieldT>	
		inline static AttributeLayout Create(uint32_t index, uint32_t fieldCount, uint32_t offset, bool normalized = false) {
			return { index, GLNumericType<FieldT>::value, fieldCount, sizeof(FieldT) * fieldCount, offset, normalized };
		}
		const uint32_t index;
		const GLenum fieldType;
		const uint32_t fieldCount;
		const uint32_t stride;
		const uint32_t offset;
		const bool normalized;
	};

	namespace Attr {

		template <typename FieldT>
		struct Scalar {
			inline static AttributeLayout Layout(uint32_t index, uint32_t offset) {
				return AttributeLayout::Create<FieldT>(index, 1, offset, false);
			}
			const FieldT data;
		};

		template <typename FieldT, uint32_t dimensionality>
		struct Vector {
			inline static AttributeLayout Layout(uint32_t index, uint32_t offset, bool normalized = false) {
				return AttributeLayout::Create<FieldT>(index, dimensionality, offset, normalized);
			}
			const FieldT data[dimensionality];
		};

		template <typename FieldT, uint32_t row_dimensionality, uint32_t col_dimensionality>
		struct Matrix {
			inline static AttributeLayout Layout(uint32_t index, uint32_t offset) {
				return AttributeLayout::Create<FieldT>(index, row_dimensionality * col_dimensionality, offset, false);
			}
			const FieldT data[row_dimensionality][col_dimensionality];
		};

		// Scalars
		using Float = Scalar<float>;
		using Double = Scalar<double>;
		using Int = Scalar<int32_t>;
		using UInt = Scalar<uint32_t>;
		using Bool = Scalar<bool>;

		// Vectors
		using Vec2 = Vector<float, 2>;
		using Vec3 = Vector<float, 3>;
		using Vec4 = Vector<float, 4>;
		using DVec2 = Vector<double, 2>;
		using DVec3 = Vector<double, 3>;
		using DVec4 = Vector<double, 4>;
		using IVec2 = Vector<int32_t, 2>;
		using IVec3 = Vector<int32_t, 3>;
		using IVec4 = Vector<int32_t, 4>;
		using UVec2 = Vector<uint32_t, 2>;
		using UVec3 = Vector<uint32_t, 3>;
		using UVec4 = Vector<uint32_t, 4>;
		using BVec2 = Vector<bool, 2>;
		using BVec3 = Vector<bool, 3>;
		using BVec4 = Vector<bool, 4>;

		// Matrices
		using Mat2 = Matrix<float, 2, 2>;
		using Mat3 = Matrix<float, 3, 3>;
		using Mat4 = Matrix<float, 4, 4>;
		using DMat2 = Matrix<double, 2, 2>;
		using DMat3 = Matrix<double, 3, 3>;
		using DMat4 = Matrix<double, 4, 4>;
		using IMat2 = Matrix<int32_t, 2, 2>;
		using IMat3 = Matrix<int32_t, 3, 3>;
		using IMat4 = Matrix<int32_t, 4, 4>;
		using UMat2 = Matrix<uint32_t, 2, 2>;
		using UMat3 = Matrix<uint32_t, 3, 3>;
		using UMat4 = Matrix<uint32_t, 4, 4>;
		using BMat2 = Matrix<bool, 2, 2>;
		using BMat3 = Matrix<bool, 3, 3>;
		using BMat4 = Matrix<bool, 4, 4>;
	}
}

