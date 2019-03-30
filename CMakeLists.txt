cmake_minimum_required(VERSION 3.5)
project(Hello LANGUAGES CXX)

# Add local project module path so CMake includes custom CMake modules.
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")

include(CTest)
enable_testing()

add_library(hello
	src/Hello.h
	src/Hello.cpp
)
target_include_directories(hello
	PUBLIC
		src
)
target_compile_options(hello
	PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			-Werror -Wall -Wextra>
		$<$<CXX_COMPILER_ID:MSVC>:
			/W4>
)

#
# Create a library target for the docopt.cpp command line parsing library.
#
add_library(docopt
	src/docopt/docopt.h
	src/docopt/docopt_private.h
	src/docopt/docopt_util.h
	src/docopt/docopt_value.h
	src/docopt/docopt.cpp
)
target_compile_features(docopt
	PUBLIC
		cxx_std_11
)

#
# Create executable that uses the hello lib to say Hello.
#
add_executable(say_hello
	src/main.cpp
)
target_link_libraries(say_hello
	PRIVATE
		hello
		docopt
)
target_compile_options(hello
	PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			-Werror -Wall -Wextra>
		$<$<CXX_COMPILER_ID:MSVC>:
			/W4>
)

#
# Create a library target for the Catch header-only test framework.
#
add_library(Catch INTERFACE)
target_include_directories(Catch
	INTERFACE
		test/
)

#
# Create a target for executing the Catch unit tests.
#
add_executable(unit_tests
	test/main.cpp
	test/test_Hello.cpp
)
target_include_directories(unit_tests
	PUBLIC
		test/
)
target_link_libraries(unit_tests
	Catch
	hello
)
target_compile_options(unit_tests
	PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			-Werror -Wall -Wextra>
		$<$<CXX_COMPILER_ID:MSVC>:
			/W4>
)

# Load and use the .cmake file provided by Catch so all the test cases
# are made available to CTest.
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(unit_tests)

install(
	TARGETS unit_tests
	RUNTIME DESTINATION bin
)

set(CPACK_PACKAGE_NAME "Hello")
set(CPACK_PACKAGE_VENDOR "erichschroeter.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Hello - CPack Component Installation Example")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Hello CPack Component Example")

# This must always be last!
include(CPack)

