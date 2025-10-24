#define VECTOR3_ANGLE
#define VECTOR3_CAST
//#define VECTOR2_DEBUG
#include <Vector/Vector3/Vector3.h>

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
#define CHECK_VECTOR3(vector, vectorGlm) CHECK(vector.x== Catch::Approx(vectorGlm.x)); CHECK(vector.y == Catch::Approx(vectorGlm.y)); CHECK(vector.z == Catch::Approx(vectorGlm.z))

using namespace PenMath;

#include <iostream>

TEST_CASE("Vector3", "[.all][vector][Vector3]")
{
	SECTION("Instantiation")
	{
		// destructor
		{
			Vector3f temp;
		}

		// default constructor
		Vector3f empty;
		glm::vec3 emptyGlm{};
		CHECK_VECTOR3(empty, emptyGlm);

		// basic constructor
		Vector3f oneParam{ 2.5f };
		glm::vec3 oneParamGlm{ 2.5f };
		CHECK_VECTOR3(oneParam, oneParamGlm);

		Vector3f allParam{ 2.5f, .5f, 2.f };
		glm::vec3 allParamGlm{ 2.5f, .5f, 2.f };
		CHECK_VECTOR3(allParam, allParamGlm);

		// copy constructor
		Vector3f copy{ allParam };
		glm::vec3 copyGlm{ allParamGlm };
		CHECK_VECTOR3(copy, copyGlm);

		// assignment operator
		empty = allParam;
		emptyGlm = allParamGlm;
		CHECK_VECTOR3(empty, emptyGlm);

		// OpenGL compatibility
		CHECK(sizeof Vector3f == sizeof glm::vec3);
		CHECK(memcmp(&allParam, &allParamGlm, sizeof Vector3f) == 0);
	}

	SECTION("Accessor")
	{
		float const x = 2.5f;
		float const y = .5f;
		float const z = 2.f;
		Vector3f vector{ x, y, z };

		{
			Vector3f const& vectorConst = vector;
			CHECK(vectorConst[0] == x);
			CHECK(vectorConst[1] == y);
			CHECK(vectorConst[2] == z);
		}

		{
			vector[0] += 1.f;
			vector[1] += 1.f;
			vector[2] += 1.f;
			CHECK(vector[0] == x + 1.f);
			CHECK(vector[1] == y + 1.f);
			CHECK(vector[2] == z + 1.f);
		}
	}

	SECTION("Comparator")
	{
		// compare with self
		Vector3f self{ 2.5f, .5f, 2.f };
		CHECK(self == self);
		CHECK_FALSE(self != self);

		// compare with same
		CHECK(Vector3f{ 2.5f, .5f, 2.f } == Vector3f{ 2.5f, .5f, 2.f });
		CHECK_FALSE(Vector3f{ 2.5f, .5f, 2.f } != Vector3f{ 2.5f, .5f, 2.f });

		// trying to find copy/paste mistake
		Vector3f twos{ 2.f, 2.f, 2.f };
		CHECK_FALSE(Vector3f{ .5f, 2.f, 2.f } == twos);
		CHECK_FALSE(Vector3f{ 2.f, .5f, 2.f } == twos);
		CHECK_FALSE(Vector3f{ 2.f, 2.f, .5f } == twos); 

		CHECK(Vector3f{ .5f, 2.f, 2.f } != twos);
		CHECK(Vector3f{ 2.f, .5f, 2.f } != twos);
		CHECK(Vector3f{ 2.f, 2.f, .5f } != twos);

		CHECK_FALSE(twos == Vector3f{ .5f, 2.f, 2.f });
		CHECK_FALSE(twos == Vector3f{ 2.f, .5f, 2.f });
		CHECK_FALSE(twos == Vector3f{ 2.f, 2.f, .5f });

		CHECK(twos != Vector3f{ .5f, 2.f, 2.f });
		CHECK(twos != Vector3f{ 2.f, .5f, 2.f });
		CHECK(twos != Vector3f{ 2.f, 2.f, .5f });

		CHECK_FALSE(Vector3f::isUnit(self));
		CHECK(Vector3f::isUnit({ 0.771516740f, 0.154303357f, 0.617213428f }));
	}

	SECTION("Constant")
	{
		CHECK_VECTOR3(Vector3f::Back(), glm::vec3(0.f, 0.f, -1.f));

		CHECK_VECTOR3(Vector3f::Down(), glm::vec3(0.f, -1.f, 0.f));

		CHECK_VECTOR3(Vector3f::Front(), glm::vec3(0.f, 0.f, 1.f));

		CHECK_VECTOR3(Vector3f::Left(), glm::vec3(-1.f, 0.f, 0.f));

		CHECK_VECTOR3(Vector3f::One(), glm::vec3(1.f, 1.f, 1.f));

		CHECK_VECTOR3(Vector3f::Right(), glm::vec3(1.f, 0.f, 0.f));

		CHECK_VECTOR3(Vector3f::Up(), glm::vec3(0.f, 1.f, 0.f));

		CHECK_VECTOR3(Vector3f::Zero(), glm::vec3(0.f, 0.f, 0.f));
	}

	SECTION("Arithmetic")
	{
		Vector3f const small{ 2.5f, .5f, 2.f };
		Vector3f const big{ 3.75f, 3.f, .75f };

		glm::vec3 const smallGlm{ 2.5f, .5f, 2.f };
		glm::vec3 const bigGlm{ 3.75f, 3.f, .75f };

		SECTION("Addition")
		{
			{
				Vector3f sumAssignment = big;
				sumAssignment += small;

				glm::vec3 sumAssignmentGlm = bigGlm;
				sumAssignmentGlm += smallGlm;

				CHECK_VECTOR3(sumAssignment, sumAssignmentGlm);
			}

			{
				Vector3f sum = big + small;

				glm::vec3 sumGlm = bigGlm + smallGlm;

				CHECK_VECTOR3(sum, sumGlm);
			}
		}

		SECTION("Opposite")
		{
			Vector3f opposite = -Vector3f{ 3.7f, 3.f, .7f };

			glm::vec3 oppositeGlm = -glm::vec3{ 3.7f, 3.f, .7f };

			CHECK_VECTOR3(opposite, oppositeGlm);
		}

		SECTION("Subtraction")
		{
			{
				Vector3f differenceAssignment = big;
				differenceAssignment -= small;

				glm::vec3 differenceAssignmentGlm = bigGlm;
				differenceAssignmentGlm -= smallGlm;

				CHECK_VECTOR3(differenceAssignment, differenceAssignmentGlm);
			}

			{
				Vector3f difference = big - small;

				glm::vec3 differenceGlm = bigGlm - smallGlm;

				CHECK_VECTOR3(difference, differenceGlm);
			}
		}

		SECTION("Multiplication")
		{
			{
				Vector3f productAssignment = big;
				productAssignment *= small;

				glm::vec3 productAssignmentGlm = bigGlm;
				productAssignmentGlm *= smallGlm;

				CHECK_VECTOR3(productAssignment, productAssignmentGlm);
			}

			{
				Vector3f product = big * small;

				glm::vec3 productGlm = bigGlm * smallGlm;

				CHECK_VECTOR3(product, productGlm);
			}
		}

		SECTION("Division")
		{
			{
				Vector3f quotientAssignment = big;
				quotientAssignment /= small;

				glm::vec3 quotientAssignmentGlm = bigGlm;
				quotientAssignmentGlm /= smallGlm;

				CHECK_VECTOR3(quotientAssignment, quotientAssignmentGlm);
			}

			{
				Vector3f quotient = big / small;

				glm::vec3 quotientGlm = bigGlm / smallGlm;

				CHECK_VECTOR3(quotient, quotientGlm);
			}
		}
	}

#if defined(VECTOR3_ANGLE)
	SECTION("Rotation")
	{
		Vector3f const origin{ 2.5f, .5f, 2.f };
		Vector3f const transformation{ -2.f, 0.f, 1.25f };

		glm::vec4 const originGlm{ 2.5f, .5f, 2.f, 1.f };
		glm::vec3 const transformationGlm{ -2.f, 0.f, 1.25f };

		SECTION("Euler Angle")
		{
			Vector3f rotate = origin;
			rotate.rotate(Radian{ transformation.x }, Radian{ transformation.y }, Radian{ transformation.z });

			glm::vec4 rotateGlm = glm::orientate4(transformationGlm) * originGlm;

			CHECK_VECTOR3(rotate, rotateGlm);
		}

		SECTION("Axis")
		{
			Vector3f rotate = origin;
			rotate.rotate( Radian{ -3 }, transformation);

			glm::vec4 rotateGlm = glm::rotate(-3.f, transformationGlm) * originGlm;

			CHECK_VECTOR3(rotate, rotateGlm);
		}
	}
#endif

	SECTION("Functionality")
	{
		Vector3f const base{ 2.5f, .5f, 2.f };
		Vector3f const other{ 3.75f, 3.f, .75f };

		glm::vec3 const baseGlm{ 2.5f, .5f, 2.f };
		glm::vec3 const otherGlm{ 3.75f, 3.f, .75f };

#if defined(VECTOR3_ANGLE)
		SECTION("Angle")
		{
			Radian angle = Vector3f::angle(base, other);

			float angleGlm = glm::angle(glm::normalize(baseGlm), glm::normalize(otherGlm));

			CHECK(angle.raw() == Catch::Approx(angleGlm));
		}
#endif
		SECTION("Cross")
		{
			Vector3f cross = Vector3f::cross(base, other);

			glm::vec3 crossGlm = glm::cross(baseGlm, otherGlm);

			CHECK_VECTOR3(cross, crossGlm);
		}

		SECTION("Dot")
		{
			float dot = Vector3f::dot(base, other);

			float dotGlm = glm::dot(baseGlm, otherGlm);

			CHECK(dot == dotGlm);
		}

		SECTION("Distance")
		{
			{
				float distance = Vector3f::distance(base, other);

				float distanceGlm = glm::distance(baseGlm, otherGlm);

				CHECK(distance == Catch::Approx(distanceGlm));
			}

			{
				float distanceSquare = Vector3f::distanceSquared(base, other);

				float distanceSquareGlm = glm::distance2(baseGlm, otherGlm);

				CHECK(distanceSquare == Catch::Approx(distanceSquareGlm));
			}
#if defined(VECTOR3_CAST)
			{
				float distance2D = Vector3f::distance2(base, other);

				float distance2DGlm = glm::distance(glm::vec2(baseGlm), glm::vec2(otherGlm));

				CHECK(distance2D == Catch::Approx(distance2DGlm));
			}

			{
				float distance2DSquare = Vector3f::distance2Squared(base, other);

				float distance2DSquareGlm = glm::distance2(glm::vec2(baseGlm), glm::vec2(otherGlm));

				CHECK(distance2DSquare == Catch::Approx(distance2DSquareGlm));
			}
#endif
		}

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
			Vector3f normalize = Vector3f::normal(base);

			glm::vec3 normalizeGlm = glm::normalize(baseGlm);

			CHECK_VECTOR3(normalize, normalizeGlm);
		}

		SECTION("ProjectOnto")
		{
			Vector3f project = Vector3f::project(base, other);

			glm::vec3 projectGlm = glm::proj(baseGlm, otherGlm);

			CHECK_VECTOR3(project, projectGlm);
		}

		SECTION("ReflectOnto")
		{
			Vector3f reflect = Vector3f::reflect(base, other);

			glm::vec3 reflectGlm = glm::reflect(baseGlm, glm::normalize(otherGlm));

			CHECK_VECTOR3(reflect, reflectGlm);
		}
	}
}