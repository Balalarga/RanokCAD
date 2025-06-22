cmake_minimum_required(VERSION 3.20)
project(RanokCAD)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 20)

#target_compile_definitions(RanokCAD PRIVATE
#	RCAD_ASSETS_DIR="${CMAKE_CURRENT_LIST_DIR}/Assets"
#	RCAD_CONFIG_DIR="${CMAKE_CURRENT_LIST_DIR}/Config"
#)
add_compile_definitions(
	RCAD_ASSETS_DIR="${CMAKE_CURRENT_LIST_DIR}/Assets"
	RCAD_CONFIG_DIR="${CMAKE_CURRENT_LIST_DIR}/Config"
)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	#target_compile_definitions(RanokCAD PRIVATE RCAD_DEBUG_BUILD)
	add_compile_definitions(RCAD_DEBUG_BUILD)
endif ()

add_subdirectory(Source)