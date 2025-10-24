#include <Angle/Degree.h>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

using namespace PenMath;

TEST_CASE("Degree", "[.all][angle]")
{
	SECTION("Instantiation")
	{
		// destructor
		{
			Degree temp;
		}

		// default constructor
		Degree empty;
		CHECK(empty.raw() == 0.f);

		// basic constructor
		float value = 60.f;
		Degree angle{ value };
		CHECK(angle.raw() == value);

		//copy constructor
		Degree copy{ angle };
		CHECK(copy.raw() == value);

		// assignment operator
		empty = angle;
		CHECK(empty.raw() == value);

		CHECK(sizeof Degree == sizeof(float));
	}

	SECTION("Accessor")
	{
		{
			// 0 value
			Degree zeroDegree;
			CHECK(zeroDegree == 0.f);
			CHECK(zeroDegree == 0.f);
		}

		{
			// no change value
			Degree sixtyDegree{ 60.f };
			CHECK(sixtyDegree == 60.f);
			CHECK(sixtyDegree == 60.f);
		}

		{
			// wrap when true value
			Degree threeHundredDegree{ 300.f };
			threeHundredDegree.wrap(true);
			CHECK(threeHundredDegree.raw() == -60.f);
		}

		{
			// wrap when false value
			Degree minusSixtyDegree{ -60.f };
			minusSixtyDegree.wrap(false);
			CHECK(minusSixtyDegree == 300.f);
		}

		{
			// positive wrap value
			Degree oneThousandDegree{ 1000.f };
			oneThousandDegree.wrap(true);
			CHECK(oneThousandDegree.raw() == -80.f);

			Degree oneThousandDegree2{ 1000.f };
			oneThousandDegree2.wrap(false);
			CHECK(oneThousandDegree2 == 280.f);
		}

		{
			// negative wrap value
			Degree minusOneThousandDegree{ -1000.f };
			minusOneThousandDegree.wrap(true);
			CHECK(minusOneThousandDegree == 80.f);

			Degree minusOneThousandDegree2{ -1000.f };
			minusOneThousandDegree2.wrap(false);
			CHECK(minusOneThousandDegree2 == 80.f);
		}
	}

	SECTION("Comparator")
	{
		// compare with self
		Degree self{ 60.f };
		CHECK(self == self);

		// compare with same
		CHECK(Degree{ 60.f } == Degree{ 60.f });

		// compare with wrapped value
		Degree deg(450.f);
		deg.wrap();
		CHECK(Degree{ 90.f } == deg);

		// compare with wrap edge value
		CHECK(Degree{ 0.f } == Degree{ 360.f });
		CHECK(Degree{ -180.f } == Degree{ 180.f });
	}

	SECTION("Arithmetic")
	{
		{
			// operator +
			Degree sum = Degree(45.f) + Degree(30.f);
			CHECK(sum == 75.f);
		}

		{
			// operator +=
			Degree sum(45.f);
			sum += Degree(30.f);
			CHECK(sum == 75.f);
		}

		{
			// operator -
			Degree opposite = -Degree(45.f);
			CHECK(opposite == 315.f);
		}

		{
			// operator -
			Degree difference = Degree(45.f) - Degree(30.f);
			CHECK(difference == 15.f);
		}

		{
			// operator -=
			Degree difference(45.f);
			difference -= Degree(30.f);
			CHECK(difference == 15.f);
		}

		{
			// operator *
			Degree product = Degree(45.f) * 10.f;
			CHECK(product == 90.f);
		}

		{
			// operator *=
			Degree product(45.f);
			product *= 10.f;
			CHECK(product == 90.f);
		}

		{
			// operator /
			Degree quotient = Degree(45.f) / 5.f;
			CHECK(quotient == 9.f);
		}

		{
			// operator /=
			Degree quotient(45.f);
			quotient /= 5.f;
			CHECK(quotient == 9.f);
		}
	}

	SECTION("Functionality")
	{
		{
			// wrap value
			Degree wrapAngle{ 900.f };
			wrapAngle.wrap(false);
			CHECK(wrapAngle.raw() == 180.f);
		}

		{
			// prefere lower edge value
			Degree wrapEdge{ 360.f };
			wrapEdge.wrap(false);
			CHECK(wrapEdge.raw() == 0.f);

			wrapEdge = Degree{ 900.f };
			wrapEdge.wrap(true);
			CHECK(wrapEdge.raw() == -180.f);
		}
	}
}
