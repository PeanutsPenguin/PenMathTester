//Got tired of writing test cases 

#define VECTOR4_CAST
#define VECTOR4_DEBUG
#include <Vector/Vector4/Vector4.h>

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

#define CHECK_VECTOR4(vector, vectorGlm) CHECK(vector.x== Catch::Approx(vectorGlm.x)); CHECK(vector.y == Catch::Approx(vectorGlm.y)); CHECK(vector.z == Catch::Approx(vectorGlm.z)); CHECK(vector.w == Catch::Approx(vectorGlm.w))

using namespace PenMath;

#include <iostream>

TEST_CASE("Vector4", "[.all][vector][Vector4]")
{
	SECTION("Compilation Test")
	{
		// destructor
		{
			Vector4f temp;
		}

		// default constructor
		Vector4f empty;
		glm::vec4 emptyGlm{};
		CHECK_VECTOR4(empty, emptyGlm);

		// basic constructor
		Vector4f oneParam{ 2.5f };
		glm::vec4 oneParamGlm{ 2.5f };
		CHECK_VECTOR4(oneParam, oneParamGlm);

		Vector4f allParam{ 2.5f, .5f, 2.f, 1.f };
		glm::vec4 allParamGlm{ 2.5f, .5f, 2.f, 1.f };
		CHECK_VECTOR4(allParam, allParamGlm);

		// copy constructor
		Vector4f copy{ allParam };
		glm::vec4 copyGlm{ allParamGlm };
		CHECK_VECTOR4(copy, copyGlm);

		// assignment operator
		empty = allParam;
		emptyGlm = allParamGlm;
		CHECK_VECTOR4(empty, emptyGlm);

		// OpenGL compatibility
		CHECK(sizeof Vector4f == sizeof glm::vec4);
		CHECK(memcmp(&allParam, &allParamGlm, sizeof Vector4f) == 0);

		Vector4f::dot(allParam, empty);

		std::cout << allParam << '\n';
	}
}
