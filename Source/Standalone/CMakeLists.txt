cmake_minimum_required(VERSION 3.20)

add_executable(
	RanokCAD
	Ranok.cpp
)

# System libs
target_link_libraries(RanokCAD PRIVATE RanokCAD::Core)
target_compile_definitions(RanokCAD INTERFACE PROJECT_NAME=\"$<TARGET_PROPERTY:NAME>\")
