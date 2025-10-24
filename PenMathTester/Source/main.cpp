#include <catch2/catch_session.hpp>

int main(int argc, char* argv[])
{
	// transfers command line argument to dynamic collection so we can add our own argument easily
	std::vector<char const*> arguments;
	for (int i = 0; i < argc; i++)
	{
		arguments.push_back(argv[i]);
	}

	///TEST GLOBAL FUNCTIONS
	//arguments.push_back("Vector2,");
	//arguments.push_back("Vector3,");
	//arguments.push_back("Vector4,");
	arguments.push_back("Quaternion,");
	//arguments.push_back("Degree,");
	//arguments.push_back("Arithmetic,");
	//arguments.push_back("[Angle],");




	return Catch::Session().run((int)arguments.size(), &arguments[0]);
}
