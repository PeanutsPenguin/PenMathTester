#define MAT2_DEBUG
#include <Matrix/Mat2.h>

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

#define CHECK_MATRIX2(matrix, matrixGlm) \
	CHECK(matrix[0][0] == Catch::Approx(matrixGlm[0][0])); CHECK(matrix[1][0] == Catch::Approx(matrixGlm[1][0])); \
	CHECK(matrix[0][1] == Catch::Approx(matrixGlm[0][1])); CHECK(matrix[1][1] == Catch::Approx(matrixGlm[1][1]));

TEST_CASE("Matrix2", "[.all][matrix][Matrix2]")
{
	SECTION("Instantiation")
	{
		// destructor
		{
			PenMath::Mat2 temp;
		}

		// default constructor
		PenMath::Mat2 empty{ 0.f };
		glm::mat2 emptyGlm{ 0.f };
		CHECK_MATRIX2(empty, emptyGlm);

		// basic constructor
		PenMath::Mat2 oneParam{ 2.0f };
		glm::mat2 oneParamGlm{ 2.0f };
		CHECK_MATRIX2(oneParam, oneParamGlm);

		PenMath::Mat2 copy{ oneParam };
		glm::mat2 copyGlm{ oneParamGlm };
		CHECK_MATRIX2(copy, copyGlm);

		empty = oneParam;
		emptyGlm = oneParamGlm;
		CHECK_MATRIX2(empty, emptyGlm);
	}

	SECTION("Accessor")
	{
		// compare with self
		PenMath::Mat2 self{ 3.0f };
		CHECK(self == self);
		CHECK_FALSE(self != self);

		// compare with same
		CHECK(PenMath::Mat2{ 1.0f } == PenMath::Mat2{ 1.0f });
		CHECK_FALSE(PenMath::Mat2{ 1.0f } != PenMath::Mat2{ 1.0f });
	}

	SECTION("Arithmetic")
	{
		PenMath::Mat2 const small(
			PenMath::Vector2f{1.f, 2.f},
			PenMath::Vector2f{2.f, 3.f}
		);

		PenMath::Mat2 const big(
			PenMath::Vector2f{9, 8},
			PenMath::Vector2f{8, 7}
		);

		glm::mat2 const smallGlm{
			glm::vec2{1.f, 2.f},
			glm::vec2{2.f, 3.f}
		};

		glm::mat2 const bigGlm{
			glm::vec2{9.f, 8.f},
			glm::vec2{8.f, 7.f}
		};

		SECTION("Addition")
		{
			{
				PenMath::Mat2 sumAssignment = big;
				sumAssignment += small;

				glm::mat2 sumAssignmentGlm = bigGlm;
				sumAssignmentGlm += smallGlm;

				CHECK_MATRIX2(sumAssignment, sumAssignmentGlm);
			}

			{
				PenMath::Mat2 sum = big + small;

				glm::mat2 sumGlm = bigGlm + smallGlm;

				CHECK_MATRIX2(sum, sumGlm);
			}
		}

		SECTION("Substraction")
		{
			{
				PenMath::Mat2 difference = big;
				difference -= small;

				glm::mat2 differenceGlm = bigGlm;
				differenceGlm -= smallGlm;

				CHECK_MATRIX2(difference, differenceGlm);
			}

			{
				PenMath::Mat2 difference = big - small;

				glm::mat2 differenceGlm = bigGlm - smallGlm;

				CHECK_MATRIX2(difference, differenceGlm);
			}
		}

		SECTION("Determinant")
		{
			float determinant = small.getDeterminant();

			float determinantGlm = glm::determinant(smallGlm);

			CHECK(determinant == Catch::Approx(determinantGlm));
		}

		SECTION("Multiplication")
		{
			PenMath::Mat2 product = big * small;

			glm::mat2 productGlm = bigGlm * smallGlm;

			CHECK_MATRIX2(product, productGlm);
		}

		SECTION("Print")
		{
			std::cout << small << std::endl;
		}
	}
}