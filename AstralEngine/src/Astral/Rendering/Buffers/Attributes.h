#pragma once
#include <glad/glad.h>


namespace Astral {

	// For C++ type -> OpenGL type conversion
	template<typename T>
	struct GLNumericType;

	#define IMPLEMENT_GL_TYPE_CONVERSION(cpp_type, gl_type_enum)	\
	template<>														\
	struct GLNumericType<cpp_type> {								\
		static constexpr GLenum value = gl_type_enum;				\
	};

	IMPLEMENT_GL_TYPE_CONVERSION(int8_t, GL_BYTE)
	IMPLEMENT_GL_TYPE_CONVERSION(uint8_t, GL_UNSIGNED_BYTE)
	IMPLEMENT_GL_TYPE_CONVERSION(int16_t, GL_SHORT)
	IMPLEMENT_GL_TYPE_CONVERSION(uint16_t, GL_UNSIGNED_SHORT)
	IMPLEMENT_GL_TYPE_CONVERSION(int32_t, GL_INT)
	IMPLEMENT_GL_TYPE_CONVERSION(uint32_t, GL_UNSIGNED_INT)
	IMPLEMENT_GL_TYPE_CONVERSION(float, GL_FLOAT)
	IMPLEMENT_GL_TYPE_CONVERSION(double, GL_DOUBLE)

	#undef IMPLEMENT_GL_TYPE_CONVERSION


	struct AttributeLayout {
		template <typename FieldT>
		static AttributeLayout Create(uint32_t index, uint32_t fieldCount, uint32_t offset, bool normalized = false);
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
			static AttributeLayout Layout(uint32_t index, uint32_t offset);
			const FieldT data;
		};

		template <typename FieldT, uint32_t dimensionality>
		struct Vector {
			static AttributeLayout Layout(uint32_t index, uint32_t offset, bool normalized = false);
			const FieldT data[dimensionality];
		};

		template <typename FieldT, uint32_t row_dimensionality, uint32_t col_dimensionality>
		struct Matrix {
			static AttributeLayout Layout(uint32_t index, uint32_t offset);
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




	// =================================================================================================================
	// ================================================ IMPLEMENTATIONS ================================================
	// =================================================================================================================

	template<typename FieldT>
	AttributeLayout AttributeLayout::Create(uint32_t index, uint32_t fieldCount, uint32_t offset, bool normalized) {
		return { index, GLNumericType<FieldT>::value, fieldCount, sizeof(FieldT) * fieldCount, offset, normalized };
	}

	template<typename FieldT>
	AttributeLayout Attr::Scalar<FieldT>::Layout(uint32_t index, uint32_t offset) {
		return AttributeLayout::Create<FieldT>(index, 1, offset, false);
	}

	template<typename FieldT, uint32_t dimensionality>
	AttributeLayout Attr::Vector<FieldT, dimensionality>::Layout(uint32_t index, uint32_t offset, bool normalized) {
		return AttributeLayout::Create<FieldT>(index, dimensionality, offset, normalized);
	}

	template <typename FieldT, uint32_t row_dimensionality, uint32_t col_dimensionality>
	AttributeLayout Attr::Matrix<FieldT, row_dimensionality, col_dimensionality>::Layout(uint32_t index, uint32_t offset) {
		return AttributeLayout::Create<FieldT>(index, row_dimensionality * col_dimensionality, offset, false);
	}
}

