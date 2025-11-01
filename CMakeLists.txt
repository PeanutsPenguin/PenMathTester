#PenMathTester RootCmake
cmake_minimum_required(VERSION 4.0 FATAL_ERROR) # PATH_EQUAL

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

#Catch2
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
	GIT_TAG         v3.8.0 # or a later release
	GIT_SHALLOW		ON
)
FetchContent_MakeAvailable(Catch2)

#glm
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	a532f5b1cf27d6a3c099437e6959cf7e398a0a67 #v1.0.2
)
FetchContent_MakeAvailable(glm)



#Header
file(GLOB_RECURSE TARGET_HEADER_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl)
list(FILTER TARGET_HEADER_FILES EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR})

#Source
file(GLOB_RECURSE TARGET_SOURCE_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cc # C with classe
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
	${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
list(FILTER TARGET_SOURCE_FILES EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR})

#Target files
add_executable(${PROJECT_NAME})
set(TARGET_FILES ${TARGET_HEADER_FILES} ${TARGET_SOURCE_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_FILES}) # generate visual studio filter

#Executable
target_sources(${PROJECT_NAME} PRIVATE ${TARGET_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Header)


target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE PenMath)


if(MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT PenMathTester)
endif()