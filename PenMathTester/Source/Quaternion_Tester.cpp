#define QUATERNION_CAST
#include "Quaternion.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#define GLM_FORCE_XYZW_ONLY
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace PenMath;

#define CHECK_QUATERNION(quat, quatGlm)          \
	CHECK(quat.w == Catch::Approx(quatGlm.w)); \
	CHECK(quat.x == Catch::Approx(quatGlm.x)); \
	CHECK(quat.y == Catch::Approx(quatGlm.y)); \
	CHECK(quat.z == Catch::Approx(quatGlm.z))

TEST_CASE("Quaternion", "[.all][quat]")
{
	SECTION("Instantiation")
	{
		// destructor
		{
			Quaternion temp;
		}

		// default constructor
		Quaternion empty;
		glm::quat			emptyGlm{};
		CHECK_QUATERNION(empty, emptyGlm);

		// basic constructor
		Quaternion oneParam(2.5f);
		glm::quat			oneParamGlm(2.5f, 2.5f, 2.5f, 2.5f);
		CHECK_QUATERNION(oneParam, oneParamGlm);

		Quaternion allParam(2.5f, .5f, 2.f, 0.f);
		glm::quat	allParamGlm(2.5f, .5f, 2.f, 0.f);
		CHECK_QUATERNION(allParam, allParamGlm);

		// copy constructor
		Quaternion copy(allParam);
		glm::quat			copyGlm(allParamGlm);
		CHECK_QUATERNION(copy, copyGlm);

		// assignment operator
		empty = allParam;
		emptyGlm = allParamGlm;
		CHECK_QUATERNION(empty, emptyGlm);

		// OpenGL compatibility
		CHECK(sizeof Quaternion == sizeof glm::quat);
		CHECK(memcmp(&allParam, &allParamGlm, sizeof Quaternion) == 0);
	}

	SECTION("Accessor")
	{
		float const			w = 5.f;
		float const			x = 2.5f;
		float const			y = .5f;
		float const			z = 2.f;
		Quaternion quat{ w, x, y, z };

		{
			Quaternion const& quatConst = quat;
			CHECK(quatConst[0] == w);
			CHECK(quatConst[1] == x);
			CHECK(quatConst[2] == y);
			CHECK(quatConst[3] == z);
		}

		{
			quat[0] += 1.f;
			quat[1] += 1.f;
			quat[2] += 1.f;
			quat[3] += 1.f;
			CHECK(quat[0] == w + 1.f);
			CHECK(quat[1] == x + 1.f);
			CHECK(quat[2] == y + 1.f);
			CHECK(quat[3] == z + 1.f);
		}
	}

	SECTION("Comparator")
	{
		// compare with self
		Quaternion self{ 5.f, 2.5f, .5f, 2.f };
		CHECK(self == self);
		CHECK_FALSE(self != self);

		// compare with same
		CHECK(Quaternion{ 5.f, 2.5f, .5f, 2.f } == Quaternion{ 5.f, 2.5f, .5f, 2.f });
		CHECK(Quaternion{ 5.f, 2.5f, .5f, 2.f } != Quaternion{ 0.f, 2.5f, 1.5f, 2.f });

		// trying to find copy/paste mistake
		Quaternion twos{ 2.f };
		CHECK_FALSE(Quaternion{ .5f, 2.f, 2.f, 2.f } == twos);
		CHECK_FALSE(Quaternion{ 2.f, .5f, 2.f, 2.f } == twos);
		CHECK_FALSE(Quaternion{ 2.f, 2.f, .5f, 2.f } == twos);
		CHECK_FALSE(Quaternion{ 2.f, 2.f, 2.f, .5f } == twos);
		CHECK(Quaternion{ .5f, 2.f, 2.f, 2.f } != twos);
		CHECK(Quaternion{ 2.f, .5f, 2.f, 2.f } != twos);
		CHECK(Quaternion{ 2.f, 2.f, .5f, 2.f } != twos);
		CHECK(Quaternion{ 2.f, 2.f, 2.f, .5f } != twos);
		CHECK_FALSE(twos == Quaternion{ .5f, 2.f, 2.f, 2.f });
		CHECK_FALSE(twos == Quaternion{ 2.f, .5f, 2.f, 2.f });
		CHECK_FALSE(twos == Quaternion{ 2.f, 2.f, .5f, 2.f });
		CHECK_FALSE(twos == Quaternion{ 2.f, 2.f, 2.f, .5f });
		CHECK(twos != Quaternion{ .5f, 2.f, 2.f, 2.f });
		CHECK(twos != Quaternion{ 2.f, .5f, 2.f, 2.f });
		CHECK(twos != Quaternion{ 2.f, 2.f, .5f, 2.f });
		CHECK(twos != Quaternion{ 2.f, 2.f, 2.f, .5f });

		CHECK_FALSE(self.isUnit());
		CHECK(Quaternion{ 0.83918136f, 0.41959068f, 0.08391814f, 0.33567256f }.isUnit());
	}

	SECTION("Arithmetic")
	{
		Quaternion const small{ 5.f, 2.5f, .5f, 2.f };
		Quaternion const big{ 7.5f, 3.75f, 3.f, .75f };

		glm::quat const smallGlm{ 5.f, 2.5f, .5f, 2.f };
		glm::quat const bigGlm{ 7.5f, 3.75f, 3.f, .75f };

		SECTION("Addition")
		{
			{
				Quaternion sumAssignment = big;
				sumAssignment += small;

				glm::quat sumAssignmentGlm = bigGlm;
				sumAssignmentGlm += smallGlm;

				CHECK_QUATERNION(sumAssignment, sumAssignmentGlm);
			}

			{
				Quaternion sum = big + small;

				glm::quat sumGlm = bigGlm + smallGlm;

				CHECK_QUATERNION(sum, sumGlm);
			}
		}

		SECTION("Opposite")
		{
			Quaternion opposite = -Quaternion{ 7.4f, 3.7f, 3.f, .7f };

			glm::quat oppositeGlm = -glm::quat{ 7.4f, 3.7f, 3.f, .7f };

			CHECK_QUATERNION(opposite, oppositeGlm);
		}

		SECTION("Substraction")
		{
			{
				Quaternion differenceAssignment = big;
				differenceAssignment -= small;

				glm::quat differenceAssignmentGlm = bigGlm;
				differenceAssignmentGlm -= smallGlm;

				CHECK_QUATERNION(differenceAssignment, differenceAssignmentGlm);
			}

			{
				Quaternion difference = big - small;

				glm::quat differenceGlm = bigGlm - smallGlm;

				CHECK_QUATERNION(difference, differenceGlm);
			}
		}

		SECTION("Multiplication")
		{
			{
				Quaternion productAssignment = big;
				productAssignment *= small;

				glm::quat productAssignmentGlm = bigGlm;
				productAssignmentGlm *= smallGlm;

				CHECK_QUATERNION(productAssignment, productAssignmentGlm);
			}

			{
				Quaternion scaleQuat = big;
				scaleQuat *= 10.f;

				glm::quat scaleQuatglm = bigGlm;
				scaleQuatglm *= 10.f;

				CHECK_QUATERNION(scaleQuat, scaleQuatglm);
			}

			{
				Quaternion product = big * small;

				glm::quat productGlm = bigGlm * smallGlm;

				CHECK_QUATERNION(product, productGlm);
			}

			{
				Quaternion scaleQuat;
				scaleQuat = small * 10.f;

				glm::quat scaleQuatglm;
				scaleQuatglm = smallGlm * 10.f;

				CHECK_QUATERNION(scaleQuat, scaleQuatglm);
			}

			{
				Quaternion scaleQuat;
				scaleQuat = small * 5.f;

				glm::quat scaleQuatglm;
				scaleQuatglm = 5.f * smallGlm;

				CHECK_QUATERNION(scaleQuat, scaleQuatglm);
			}
		}

		SECTION("Division")
		{
			{
				Quaternion scaleQuat = big;
				scaleQuat /= 10.f;

				glm::quat scaleQuatglm = bigGlm;
				scaleQuatglm = scaleQuatglm / 10.f;

				CHECK_QUATERNION(scaleQuat, scaleQuatglm);
			}

			{
				Quaternion scaleQuat;
				scaleQuat = small / 10.f;

				glm::quat scaleQuatglm(smallGlm.w / 10, smallGlm.x / 10, smallGlm.y / 10, smallGlm.z / 10);

				CHECK_QUATERNION(scaleQuat, scaleQuatglm);
			}
		}
	}

	SECTION("Transformation")
	{
		Vector3f const		  originVec3{ 2.5f, .5f, 2.f };
		Vector4f const		  originVec4{ 2.5f, .5f, 2.f, 0.f };
		Quaternion const	  transformation{ -0.75f, -2.f, 0.f, 1.25f };

		glm::vec3 const origin3Glm{ 2.5f, .5f, 2.f };
		glm::vec4 const originGlm{ 2.5f, .5f, 2.f, 0.f };
		glm::quat const transformationGlm{ -0.75f, -2.f, 0.f, 1.25f };

		SECTION("Rotation")
		{
			Vector3f rotated3 = Quaternion::rotate(transformation, originVec3);
			glm::vec3	  rotated3Glm = glm::rotate(transformationGlm, origin3Glm);

			CHECK(rotated3.x == Catch::Approx(rotated3Glm.x));
			CHECK(rotated3.y == Catch::Approx(rotated3Glm.y));
			CHECK(rotated3.z == Catch::Approx(rotated3Glm.z));
		}
	}

	SECTION("Functionality")
	{
		Quaternion const base{ 5.f, 2.5f, .5f, 2.f };
		glm::quat const baseGlm{ 5.f, 2.5f, .5f, 2.f };

		Quaternion const other{ 7.5f, 3.75f, 3.f, .75f };
		glm::quat const otherGlm{ 7.5f, 3.75f, 3.f, .75f };

		SECTION("Magnitude")
		{
			{
				float magnitude = base.magnitude();
				float magnitudeGlm = glm::length(baseGlm);

				CHECK(magnitude == Catch::Approx(magnitudeGlm));
			}

			{
				float magnitudeSquare = base.magnitudeSquared();
				float magnitudeSquareGlm = glm::length2(baseGlm);

				CHECK(magnitudeSquare == Catch::Approx(magnitudeSquareGlm));
			}
		}

		SECTION("Normal")
		{
			Quaternion normalize(base);
			normalize.normalize();
			glm::quat			normalizeGlm = glm::normalize(baseGlm);

			CHECK_QUATERNION(normalize, normalizeGlm);
		}

		SECTION("Conjugate")
		{
			Quaternion conjugate(base);
			conjugate.conjugate();
			glm::quat			conjugateGlm = glm::conjugate(baseGlm);

			CHECK_QUATERNION(conjugate, conjugateGlm);
		}

		SECTION("Slerp")
		{
			Quaternion slerped = Quaternion::slerp(base, other, 0.f);
			glm::quat			slerpedGlm = glm::slerp(baseGlm, otherGlm, 0.f);

			CHECK_QUATERNION(slerped, slerpedGlm);

			slerped = Quaternion::slerp(base, other, 0.25f);
			slerpedGlm = glm::slerp(baseGlm, otherGlm, 0.25f);

			CHECK_QUATERNION(slerped, slerpedGlm);

			slerped = Quaternion::slerp(base, other, 0.5f);
			slerpedGlm = glm::slerp(baseGlm, otherGlm, 0.5f);

			CHECK_QUATERNION(slerped, slerpedGlm);

			slerped = Quaternion::slerp(base, other, 0.75f);
			slerpedGlm = glm::slerp(baseGlm, otherGlm, 0.75f);

			CHECK_QUATERNION(slerped, slerpedGlm);

			slerped = Quaternion::slerp(base, other, 1.f);
			slerpedGlm = glm::slerp(baseGlm, otherGlm, 1.f);

			CHECK_QUATERNION(slerped, slerpedGlm);
		}
	}
}