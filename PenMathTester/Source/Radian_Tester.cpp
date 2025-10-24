#include <Angle/Radian.h>
#include <Angle/Degree.h>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

using namespace PenMath;

TEST_CASE("Radian", "[.all][angle]")
{
	constexpr float halfRadianCircle = glm::pi<float>();
	constexpr float radianCircle = glm::two_pi<float>();

	SECTION("Instantiation")
	{
		// destructor
		{
			Radian temp;
		}

		// default constructor
		Radian empty;
		CHECK(empty.raw() == 0.f);

		// basic constructor
		float value = 1.2f;
		Radian angle{ value };
		CHECK(angle.raw() == value);

		// copy constructor
		Radian copy{ angle };
		CHECK(copy.raw() == value);

		// assignment operator
		empty = angle;
		CHECK(empty.raw() == value);

		CHECK(sizeof Radian == sizeof(float));
	}

	SECTION("Accessor")
	{
		{
			// 0 value
			Radian zeroRadian;
			CHECK(zeroRadian.raw() == 0.f);
		}

		{
			// no change value
			Radian oneRadian{ 1.2f };
			CHECK(oneRadian.raw() == 1.2f);
		}

		{
			// wrap when true value
			const float wrapRadian = 5.8f - radianCircle;

			Radian sixRadian{ 5.8f };
			sixRadian.wrap(true);
			CHECK(sixRadian.raw() == Catch::Approx(wrapRadian));
		}

		{
			// positive wrap value
			const float radian = 15.f - 2.f * radianCircle;

			Radian fifteenRadian{ 15.f };
			CHECK(fifteenRadian.wrappedValue(true) == Catch::Approx(radian));
			CHECK(fifteenRadian.wrappedValue(false) == Catch::Approx(radian));
		}

		{
			// negative wrap value
			Radian radian(-15.f + 4.f * radianCircle);
			Radian wrapRadian(-15.f + 2.f * radianCircle);

			Radian minusFifteenRadian{ -15.f };
			CHECK(minusFifteenRadian.wrappedValue(true) == Catch::Approx(wrapRadian.wrappedValue(true)));

			CHECK(minusFifteenRadian.wrappedValue(false) == Catch::Approx(radian.wrappedValue(false)));
		}
	}

	SECTION("Comparator")
	{
		// compare with self
		Radian self{ 1.2f };
		CHECK(self == self);

		// compare with same
		CHECK(Radian{ 1.2f } == Radian{ 1.2f });

		// compare with wrapped value
		CHECK(Radian(1.2f).wrappedValue() == Catch::Approx(Radian(1.2f + radianCircle).wrappedValue()));

		// compare with wrap edge value
		CHECK(Radian{ 0.f } == Radian{ radianCircle });

		CHECK(Radian{ -halfRadianCircle } == Radian{ halfRadianCircle });
	}

	SECTION("Arithmetic")
	{
		{
			// operator +
			Radian sum = Radian(0.75f) + Radian(0.5f);
			CHECK(sum.wrappedValue() == 1.25f);
		}

		{
			// operator +=
			Radian sum(0.75f);
			sum += Radian(0.5f);
			CHECK(sum.wrappedValue() == 1.25f);
		}

		{
			// operator -
			Radian opposite = -Radian(0.75f);
			CHECK(opposite.wrappedValue() == -0.75f);
		}

		{
			// operator -
			Radian difference = Radian(0.75f) - Radian(0.5f);
			CHECK(difference.wrappedValue() == 0.25f);
		}

		{
			// operator -=
			Radian difference(0.75f);
			difference -= Radian(0.5f);
			CHECK(difference.wrappedValue() == 0.25f);
		}

		{
			// operator *
			Radian product = Radian(0.75f) * 10.f;
			CHECK(product.wrappedValue() == 7.5f - radianCircle);
		}

		{
			// operator *=
			Radian product(0.75f);
			product *= 10.f;
			CHECK(product.wrappedValue() == 7.5f - radianCircle);
		}

		{
			// operator /
			Radian quotient = Radian(0.75f) / 4.f;
			CHECK(quotient.wrappedValue() == 0.1875f);
		}

		{
			// operator /=
			Radian quotient(0.75f);
			quotient /= 4.f;
			CHECK(quotient.wrappedValue() == 0.1875f);
		}
	}

	SECTION("Functionality")
	{
		{
			// wrap value
			Radian wrapAngle{ halfRadianCircle * 5.f };
			wrapAngle.wrap(false);
			CHECK(wrapAngle.raw() == Catch::Approx(halfRadianCircle));
		}

		{
			// prefer lower edge value
			Radian wrapEdge{ radianCircle };
			wrapEdge.wrap(false);
			CHECK(wrapEdge.raw() == 0.f);

			wrapEdge = Radian{ halfRadianCircle };
			wrapEdge.wrap(true);
			CHECK(wrapEdge.raw() == Catch::Approx(-halfRadianCircle));
		}
	}

	SECTION("Conversion")
	{
		Radian radian{ Degree{ 60.f } };
		CHECK(radian.raw() == Catch::Approx(glm::radians(60.f)));

		Degree degree{ Radian{ 1.2f } };
		CHECK(degree.raw() == Catch::Approx(glm::degrees(1.2f)));
	}
}