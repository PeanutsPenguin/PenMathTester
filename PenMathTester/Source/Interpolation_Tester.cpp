#define LERP_DEGREE
#define LERP_RADIAN
#define LERP_VECTOR2
#define LERP_VECTOR3
#define LERP_VECTOR4
#include "Interpolation.h"
#include "Trigonometry.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>

using namespace PenMath;

TEST_CASE("Interpolation", "[.all]")
{
	/* Float lerp */
	{
		float half = 0.5f, quarter = 0.25f, threeQuarter = 0.75f;

		float positiveAlpha = 1.f, negativeAlpha = -3.5f, positiveBeta = 3.5f, negativeBeta = -1.f;

		CHECK(Lerp(positiveAlpha, positiveBeta, half) == 2.25f);
		CHECK(Lerp(negativeAlpha, positiveBeta, half) == 0.f);
		CHECK(Lerp(positiveAlpha, negativeBeta, half) == 0.f);
		CHECK(Lerp(negativeAlpha, negativeBeta, half) == -2.25f);

		CHECK(Lerp(positiveAlpha, positiveBeta, quarter) == 1.625f);
		CHECK(Lerp(negativeAlpha, positiveBeta, quarter) == -1.75f);
		CHECK(Lerp(positiveAlpha, negativeBeta, quarter) == 0.5f);
		CHECK(Lerp(negativeAlpha, negativeBeta, quarter) == -2.875f);

		CHECK(Lerp(positiveAlpha, positiveBeta, threeQuarter) == 2.875);
		CHECK(Lerp(negativeAlpha, positiveBeta, threeQuarter) == 1.75f);
		CHECK(Lerp(positiveAlpha, negativeBeta, threeQuarter) == -0.5f);
		CHECK(Lerp(negativeAlpha, negativeBeta, threeQuarter) == -1.625f);
	}

	/* Vector2 lerp */
	{
		float half = 0.5f, zero = 0.f, one = 1.f;

		Vector2f first(1.f, 3.5f), second(-3.5f, 3.5f), third(1.f, -1.f), fourth(-3.5f, -1.f);

		CHECK(Lerp(first, second, half) == Vector2f(-1.25f, 3.5f));
		CHECK(Lerp(first, third, half) == Vector2f(1.f, 1.25f));
		CHECK(Lerp(first, fourth, half) == Vector2f(-1.25f, 1.25f));

		CHECK(Lerp(second, first, half) == Vector2f(-1.25f, 3.5f));
		CHECK(Lerp(second, third, half) == Vector2f(-1.25f, 1.25f));
		CHECK(Lerp(second, fourth, half) == Vector2f(-3.5f, 1.25f));

		CHECK(Lerp(third, first, half) == Vector2f(1.f, 1.25f));
		CHECK(Lerp(third, second, half) == Vector2f(-1.25f, 1.25f));
		CHECK(Lerp(third, fourth, half) == Vector2f(-1.25f, -1.f));

		CHECK(Lerp(fourth, first, half) == Vector2f(-1.25f, 1.25f));
		CHECK(Lerp(fourth, second, half) == Vector2f(-3.5f, 1.25f));
		CHECK(Lerp(fourth, third, half) == Vector2f(-1.25f, -1.f));

		CHECK(Lerp(first, second, zero) == first);
		CHECK(Lerp(first, third, zero) == first);
		CHECK(Lerp(first, fourth, zero) == first);

		CHECK(Lerp(first, second, one) == second);
		CHECK(Lerp(first, third, one) == third);
		CHECK(Lerp(first, fourth, one) == fourth);
	}

	/* Vector3 lerp */
	{
		Vector3f first(1.f), second(2.f, 2.f, -2.f), third(3.f, -3.f, 3.f), fourth(-4.f, 4.f, 4.f),
			fifth(5.f, -5.f, -5.f), sixth(-6.f, 6.f, -6.f), seventh(-7.f, -7.f, 7.f), eighth(-8.f);

		CHECK(Lerp(first, second, 0.5f) == Vector3f(1.5f, 1.5f, -0.5f));
		CHECK(Lerp(first, third, 0.5f) == Vector3f(2.f, -1.f, 2.f));
		CHECK(Lerp(first, fourth, 0.5f) == Vector3f(-1.5f, 2.5f, 2.5f));
		CHECK(Lerp(first, fifth, 0.5f) == Vector3f(3.f, -2.f, -2.f));
		CHECK(Lerp(first, sixth, 0.5f) == Vector3f(-2.5f, 3.5f, -2.5f));
		CHECK(Lerp(first, seventh, 0.5f) == Vector3f(-3.f, -3.f, 4.f));
		CHECK(Lerp(first, eighth, 0.5f) == Vector3f(-3.5f, -3.5f, -3.5f));

		CHECK(Lerp(first, first, 0.f) == first);
		CHECK(Lerp(first, first, 0.5f) == first);
		CHECK(Lerp(first, first, 1.f) == first);
	}

	/* Vector4 lerp */
	{
		float zero = 0.f, half = 0.5f, quarter = 0.25f, threeQuarter = 0.75f, one = 1.f;

		Vector4f first(0.f, 1.f, 2.f, 3.f), second(7.f, 7.f, 7.f, 1.f);

		CHECK(Lerp(first, second, zero) == first);
		CHECK(Lerp(first, second, quarter) == Vector4f(1.75f, 2.5f, 3.25f, 2.5f));
		CHECK(Lerp(first, second, half) == Vector4f(3.5f, 4.f, 4.5f, 2.f));
		CHECK(Lerp(first, second, threeQuarter) == Vector4f(5.25f, 5.5f, 5.75f, 1.5f));
		CHECK(Lerp(first, second, one) == second);

		CHECK(Lerp(second, first, zero) == second);
		CHECK(Lerp(second, first, quarter) == Vector4f(5.25f, 5.5f, 5.75f, 1.5f));
		CHECK(Lerp(second, first, half) == Vector4f(3.5f, 4.f, 4.5f, 2.f));
		CHECK(Lerp(second, first, threeQuarter) == Vector4f(1.75f, 2.5f, 3.25f, 2.5f));
		CHECK(Lerp(second, first, one) == first);
	}

	/* Degree/Radian lerp */
	{
		float half = 0.5f, quarter = 0.25f, threeQuarter = 0.75f;

		Degree ninetyDegrees(90.f), twoSeventyDegrees(270.f);
		Radian halfPiRad(c_halfPi), piRad(c_pi);

		CHECK(Lerp(ninetyDegrees, twoSeventyDegrees, half) == Degree(180.f));
		CHECK(Lerp(twoSeventyDegrees, ninetyDegrees, half) == Degree(180.f));
		CHECK(Lerp(halfPiRad, piRad, half) == Radian(c_halfPi * 1.5f));
		CHECK(Lerp(piRad, halfPiRad, half) == Radian(c_halfPi * 1.5f));

		CHECK(Lerp(ninetyDegrees, twoSeventyDegrees, quarter) == Degree(135.f));
		CHECK(Lerp(twoSeventyDegrees, ninetyDegrees, quarter) == Degree(225.f));
		CHECK(Lerp(halfPiRad, piRad, quarter) == Radian(c_halfPi * 1.25f));
		CHECK(Lerp(piRad, halfPiRad, quarter) == Radian(c_halfPi * 1.75f));

		CHECK(Lerp(ninetyDegrees, twoSeventyDegrees, threeQuarter) == Degree(225.f));
		CHECK(Lerp(twoSeventyDegrees, ninetyDegrees, threeQuarter) == Degree(135.f));
		CHECK(Lerp(halfPiRad, piRad, threeQuarter) == Radian(c_halfPi * 1.75f));
		CHECK(Lerp(piRad, halfPiRad, threeQuarter) == Radian(c_halfPi * 1.25f));
	}
}
