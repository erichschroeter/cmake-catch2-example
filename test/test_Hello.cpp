
#include <catch.hpp>

#include <Hello.h>

using namespace Hello;

SCENARIO( "Verify no argument returns Hello World", "[test_Hello.cpp]" )
{
    REQUIRE( Say_Hello() == "Hello World" );
}

SCENARIO( "Verify empty string argument returns Hello World", "[test_Hello.cpp]" )
{
    REQUIRE( Say_Hello( "" ) == "Hello World" );
}
