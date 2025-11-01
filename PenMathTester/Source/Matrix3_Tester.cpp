#define MAT3_DEBUG
#define MAT3_INITIALIZER
#include <Matrix/Mat3.h>

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


#define CHECK_MATRIX3(matrix, matrixGlm) \
	CHECK(matrix[0][0] == Catch::Approx(matrixGlm[0][0])); CHECK(matrix[1][0] == Catch::Approx(matrixGlm[1][0])); CHECK(matrix[2][0] == Catch::Approx(matrixGlm[2][0])); \
	CHECK(matrix[0][1] == Catch::Approx(matrixGlm[0][1])); CHECK(matrix[1][1] == Catch::Approx(matrixGlm[1][1])); CHECK(matrix[2][1] == Catch::Approx(matrixGlm[2][1])); \
	CHECK(matrix[0][2] == Catch::Approx(matrixGlm[0][2])); CHECK(matrix[1][2] == Catch::Approx(matrixGlm[1][2])); CHECK(matrix[2][2] == Catch::Approx(matrixGlm[2][2]));


TEST_CASE("Matrix3", "[.all][matrix][Matrix3]")
{
	SECTION("Instantiation")
	{
		// destructor
		{
			PenMath::Mat3 temp;
		}

		// default constructor
		PenMath::Mat3 empty{ 0.f };
		glm::mat3 emptyGlm{ 0.f };
		CHECK_MATRIX3(empty, emptyGlm);

		// basic constructor
		PenMath::Mat3 oneParam( 2.0f );
		glm::mat3 oneParamGlm{ 2.0f };
		CHECK_MATRIX3(oneParam, oneParamGlm);

		PenMath::Mat3 copy{ oneParam };
		glm::mat3 copyGlm{ oneParamGlm };
		CHECK_MATRIX3(copy, copyGlm);

		empty = oneParam;
		emptyGlm = oneParamGlm;
		CHECK_MATRIX3(empty, emptyGlm);

		CHECK(sizeof(PenMath::Mat3) == sizeof(glm::mat3));
	}

	SECTION("Accessor")
	{
		// compare with self
		PenMath::Mat3 self{ 3.0f };
		CHECK(self == self);
		CHECK_FALSE(self != self);

		// compare with same
		CHECK(PenMath::Mat3{ 1.0f } == PenMath::Mat3{ 1.0f });
		CHECK_FALSE(PenMath::Mat3{ 1.0f } != PenMath::Mat3{ 1.0f });
	}

	SECTION("Arithmetic")
	{
		PenMath::Mat3 const small{
			1.f, 2.f, 3.f,
			2.f, 3.f, 4.f,
			3.f, 4.f, 1.f
		};

		PenMath::Mat3 const big(
			PenMath::Vector3f{9.f, 8.f, 7.f},
			PenMath::Vector3f{8.f, 7.f, 6.f},
			PenMath::Vector3f{7.f, 6.f, 9.f}
		);

		glm::mat3 const smallGlm{
			glm::vec3{1.f, 2.f, 3.f},
			glm::vec3{2.f, 3.f, 4.f},
			glm::vec3{3.f, 4.f, 1.f}
		};

		glm::mat3 const bigGlm{
			glm::vec3{9.f, 8.f, 7.f},
			glm::vec3{8.f, 7.f, 6.f},
			glm::vec3{7.f, 6.f, 9.f}
		};

		SECTION("Addition")
		{
			{
				PenMath::Mat3 sumAssignment = big;
				sumAssignment += small;

				glm::mat3 sumAssignmentGlm = bigGlm;
				sumAssignmentGlm += smallGlm;

				CHECK_MATRIX3(sumAssignment, sumAssignmentGlm);
			}

			{
				PenMath::Mat3 sum = big + small;

				glm::mat3 sumGlm = bigGlm + smallGlm;

				CHECK_MATRIX3(sum, sumGlm);
			}
		}

		SECTION("Substraction")
		{
			{
				PenMath::Mat3 difference = big;
				difference -= small;

				glm::mat3 differenceGlm = bigGlm;
				differenceGlm -= smallGlm;

				CHECK_MATRIX3(difference, differenceGlm);
			}

			{
				PenMath::Mat3 difference = big - small;

				glm::mat3 differenceGlm = bigGlm - smallGlm;

				CHECK_MATRIX3(difference, differenceGlm);
			}
		}

		SECTION("Inverse")
		{
			PenMath::Mat3 inverse = small.getInverse();

			glm::mat3 inverseGlm = glm::inverse(smallGlm);

			CHECK_MATRIX3(inverse, inverseGlm);
		}

		SECTION("Determinant")
		{
			float determinant = small.getDeterminant();

			float determinantGlm = glm::determinant(smallGlm);

			CHECK(determinant == Catch::Approx(determinantGlm));
		}

		SECTION("Multiplication")
		{
			PenMath::Mat3 product = big * small;

			glm::mat3 productGlm = bigGlm * smallGlm;

			CHECK_MATRIX3(product, productGlm);
		}
	}
}
