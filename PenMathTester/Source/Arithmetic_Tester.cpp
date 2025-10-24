#include <Arithmetic.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>

using namespace PenMath;

TEST_CASE("Arithmetic", "[.all]")
{
	/* Almost equals */
	{
		float valueA = 1.5000001f, valueB = 1.4999999f;
		CHECK(PenMath::almostEqual(valueA, valueB));
	}

	/* Rounding/Truncating */
	{
		float value = 6.66f;
		CHECK(PenMath::ceiling(value) == 7);
		CHECK(PenMath::floor(value) == 6);
	}

	/* Clamp */
	{
		float valueA = 3.47f, valueB = 4.73f, valueC = 7.34f;
		CHECK(PenMath::clamp(valueB, valueA, valueC) == valueB);	/* Value is in the range */
		CHECK(PenMath::clamp(valueB, valueC, valueA) == valueB); /* Min and max are inverted */
		CHECK(PenMath::clamp(valueC, valueA, valueB) == valueB); /* Value is greater than max */
		CHECK(PenMath::clamp(valueA, valueB, valueC) == valueB); /* Value is smaller than min */
		CHECK(PenMath::clamp(valueA, valueA, valueC) == valueA); /* Value is equal to min */
		CHECK(PenMath::clamp(valueC, valueB, valueC) == valueC); /* Value is equal to max */
	}

	/*Power*/
	{
		CHECK(PenMath::power(25.f, 2) == 625.f);
		CHECK(PenMath::power(7.f, 3) == 343.f);	}

	/* Swap */
	{
		float valueA = 75.57f, valueB = 57.75f;
		int valueC = 100, valueD = 200;
		PenMath::swap(valueA, valueB);
		PenMath::swap(valueC, valueD);
		CHECK(valueA == 57.75f);
		CHECK(valueB == 75.57f);
		CHECK(valueC == 200);
		CHECK(valueD == 100);
	}
}