#define MAT4_DEBUG
#define MAT4_INITIALIZER
#include <Matrix/Mat4.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#define GLM_FORCE_XYZW_ONLY
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <iostream>

using namespace PenMath;

#define CHECK_MATRIX4(matrix, matrixGlm) \
	CHECK(matrix[0][0] == Catch::Approx(matrixGlm[0][0])); CHECK(matrix[1][0] == Catch::Approx(matrixGlm[1][0])); CHECK(matrix[2][0] == Catch::Approx(matrixGlm[2][0])); CHECK(matrix[3][0] == Catch::Approx(matrixGlm[3][0])); \
	CHECK(matrix[0][1] == Catch::Approx(matrixGlm[0][1])); CHECK(matrix[1][1] == Catch::Approx(matrixGlm[1][1])); CHECK(matrix[2][1] == Catch::Approx(matrixGlm[2][1])); CHECK(matrix[3][1] == Catch::Approx(matrixGlm[3][1])); \
	CHECK(matrix[0][2] == Catch::Approx(matrixGlm[0][2])); CHECK(matrix[1][2] == Catch::Approx(matrixGlm[1][2])); CHECK(matrix[2][2] == Catch::Approx(matrixGlm[2][2])); CHECK(matrix[3][2] == Catch::Approx(matrixGlm[3][2])); \
	CHECK(matrix[0][3] == Catch::Approx(matrixGlm[0][3])); CHECK(matrix[1][3] == Catch::Approx(matrixGlm[1][3])); CHECK(matrix[2][3] == Catch::Approx(matrixGlm[2][3])); CHECK(matrix[3][3] == Catch::Approx(matrixGlm[3][3]));

TEST_CASE("Matrix4", "[.all][matrix][Matrix4]")
{
	SECTION("Instantiation")
	{
		// destructor
		{
			Mat4 temp;
		}

		// default constructor
		Mat4 empty{ 0.f };
		glm::mat4 emptyGlm{ 0.f };
		CHECK_MATRIX4(empty, emptyGlm);

		// basic constructor
		Mat4 oneParam( 2.0f );
		glm::mat4 oneParamGlm{ 2.0f };
		CHECK_MATRIX4(oneParam, oneParamGlm);

		Mat4 copy{ oneParam };
		glm::mat4 copyGlm{ oneParamGlm };
		CHECK_MATRIX4(copy, copyGlm);

		empty = oneParam;
		emptyGlm = oneParamGlm;
		CHECK_MATRIX4(empty, emptyGlm);

		CHECK(sizeof(Mat4) == sizeof(glm::mat4));
	}

	SECTION("Accessor")
	{
		// compare with self
		Mat4 self{ 3.0f };
		CHECK(self == self);
		CHECK_FALSE(self != self);

		// compare with same
		CHECK(Mat4{ 1.0f } == Mat4{ 1.0f });
		CHECK_FALSE(Mat4{ 1.0f } != Mat4{ 1.0f });
	}

	SECTION("Constant")
	{
		CHECK_MATRIX4(Mat4::translate(Vector3f{ 1.1f, 2.3f, 1.f }), glm::translate(glm::vec3{ 1.1f, 2.3f, 1.f }));

		Mat4 rotateTester = Mat4::rotate(Vector3f{ 0.f, 0.f, c_halfPi });

		rotateTester *= Mat4::rotate(Vector3f{ 0.f, c_halfPi, 0.f });

		glm::mat4 rotateTesterGlm = glm::rotate(glm::mat4(1.f), c_halfPi, glm::vec3{ 0.f, 0.f, 1.f });
		
		rotateTesterGlm = glm::rotate(rotateTesterGlm, c_halfPi, glm::vec3{ 0.f, 1.f, 0.f });
		
		CHECK_MATRIX4(rotateTester, rotateTesterGlm);

		CHECK_MATRIX4(Mat4::scale(Vector3f{ 1.1f, 2.3f, 1.f }), glm::scale(glm::mat4{ 1.f }, glm::vec3{ 1.1f, 2.3f, 1.f }));

		CHECK_MATRIX4(Mat4::Ortho(0.f, 10.f, 0.f, 10.f), glm::ortho(0.f, 10.f, 0.f, 10.f));

		CHECK_MATRIX4(Mat4::Ortho(0.f, 10.f, 0.f, 10.f, -1.f, 1.f), glm::ortho(0.f, 10.f, 0.f, 10.f, -1.f, 1.f));

		CHECK_MATRIX4(Mat4::Perspective(90.f, 0.8f, -1.f, 1.f), glm::perspective(90.f, 0.8f, -1.f, 1.f));

		CHECK_MATRIX4(Mat4::LookAt(Vector3f{ 1.f, 1.f, 0.f }, Vector3f{ 0.f, 0.f, 0.f }, Vector3f{ 0.f, 1.f, 0.f }), glm::lookAtLH(glm::vec3{ 1.f, 1.f, 0.f }, glm::vec3{ 0.f, 0.f, 0.f }, glm::vec3{ 0.f, 1.f, 0.f }));
	}

	SECTION("Arithmetic")
	{
		Mat4 const small{
			Vector4f(1.f, 2.f, 3.f, 4.f),
			Vector4f(2.f, 3.f, 4.f, 1.f),
			Vector4f(3.f, 4.f, 1.f, 2.f),
			Vector4f(4.f, 1.f, 2.f, 3.f)
		};

		Mat4 const big(
			Vector4f{9.f, 8.f, 7.f, 6.f},
			Vector4f{8.f, 7.f, 6.f, 9.f},
			Vector4f{7.f, 6.f, 9.f, 8.f},
			Vector4f{6.f, 9.f, 8.f, 7.f}
		);

		glm::mat4 const smallGlm{
			glm::vec4{1.f, 2.f, 3.f, 4.f},
			glm::vec4{2.f, 3.f, 4.f, 1.f},
			glm::vec4{3.f, 4.f, 1.f, 2.f},
			glm::vec4{4.f, 1.f, 2.f, 3.f}
		};

		glm::mat4 const bigGlm{
			glm::vec4{9.f, 8.f, 7.f, 6.f},
			glm::vec4{8.f, 7.f, 6.f, 9.f},
			glm::vec4{7.f, 6.f, 9.f, 8.f},
			glm::vec4{6.f, 9.f, 8.f, 7.f}
		};

		SECTION("Addition")
		{
			{
				Mat4 sumAssignment = big;
				sumAssignment += small;

				glm::mat4 sumAssignmentGlm = bigGlm;
				sumAssignmentGlm += smallGlm;

				CHECK_MATRIX4(sumAssignment, sumAssignmentGlm);
			}

			{
				Mat4 sum = big + small;

				glm::mat4 sumGlm = bigGlm + smallGlm;

				CHECK_MATRIX4(sum, sumGlm);
			}
		}

		SECTION("Substraction")
		{
			{
				Mat4 difference = big;
				difference -= small;

				glm::mat4 differenceGlm = bigGlm;
				differenceGlm -= smallGlm;

				CHECK_MATRIX4(difference, differenceGlm);
			}

			{
				Mat4 difference = big - small;

				glm::mat4 differenceGlm = bigGlm - smallGlm;

				CHECK_MATRIX4(difference, differenceGlm);
			}
		}

		SECTION("Inverse")
		{
			Mat4 inverse = small.getInverse();

			glm::mat4 inverseGlm = glm::inverse(smallGlm);

			CHECK_MATRIX4(inverse, inverseGlm);
		}

		SECTION("Determinant")
		{
			float determinant = small.getDeterminant();

			float determinantGlm = glm::determinant(smallGlm);

			CHECK(determinant == Catch::Approx(determinantGlm));
		}

		SECTION("Multiplication")
		{
			Mat4 product = big * small;

			glm::mat4 productGlm = bigGlm * smallGlm;

			CHECK_MATRIX4(product, productGlm);
		}

		std::cout << big << std::endl;
	}
}