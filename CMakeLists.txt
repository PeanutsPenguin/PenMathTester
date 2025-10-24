#PenMathTester RootCmake
cmake_minimum_required(VERSION 3.24 FATAL_ERROR) # PATH_EQUAL

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME} LANGUAGES CXX)




#PenMath
include(FetchContent)

#PenMath
FetchContent_Declare(
	PenMath
	GIT_REPOSITORY  https://github.com/PeanutsPenguin/PenMath
	GIT_TAG "origin/main"
)
FetchContent_MakeAvailable(PenMath)

#add_subdirectory(PenMath)
add_subdirectory(PenMathTester)




#include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
#link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

#add_dependencies(FirstTest googletest)
#target_link_libraries(FirstTest gtest gtest_main pthread)



if(MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT PenMathTester)
endif()