function(InstallConanPackages)
	find_program(CONAN_PATH conan)
	if(NOT EXISTS ${CONAN_PATH})
		message(FATAL_ERROR "Conan package manager is required. Please run this command to install and setup conan: pip install conan")
	else()
		message(STATUS "Conan path = ${CONAN_PATH}")
	endif()

	execute_process(COMMAND ${CONAN_PATH} install ${CMAKE_CURRENT_SOURCE_DIR} -s build_type=${CMAKE_BUILD_TYPE} RESULT_VARIABLE return_code)
	message("Conan packages install return code:" ${return_code})	
endfunction()

cmake_minimum_required(VERSION 3.13)
InstallConanPackages()

project(ArithmeticParser VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(ArithmeticParserObjectLib OBJECT "")
# shared libraries need PIC
set_property(TARGET ArithmeticParserObjectLib PROPERTY POSITION_INDEPENDENT_CODE 1)
# shared and static libraries built from the same object files
add_library(ArithmeticParserSharedLib SHARED $<TARGET_OBJECTS:ArithmeticParserObjectLib>)
add_library(ArithmeticParserStaticLib STATIC $<TARGET_OBJECTS:ArithmeticParserObjectLib>)

add_executable(ArithmeticParserExecutable "")
set_target_properties(ArithmeticParserExecutable PROPERTIES OUTPUT_NAME "aparser")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory("src")
add_subdirectory("tests")

target_link_libraries(ArithmeticParserExecutable ArithmeticParserObjectLib)

enable_testing()