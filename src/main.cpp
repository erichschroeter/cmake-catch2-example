#include <iostream>

#include <docopt/docopt.h>

#include <Hello.h>

using namespace Hello;

static const char USAGE[] =
	R"(Say hello.

Usage:
  hello [<name>]

Options:
  -h, --help           Show this screen.
  --version            Show version.
)";

int main( int argc, const char * argv[] )
{
	std::map< std::string, docopt::value > args = docopt::docopt(
		USAGE,
	{
		argv + 1, argv + argc
	},
		true,
		"Hello 1.0" );

	std::string name = "";

	if ( args[ "<name>" ] && args[ "<name>" ].isString() )
	{
		name = args[ "<name>" ].asString();
	}
	
	std::cout << Say_Hello( name ) << std::endl;

	return 0;
}

