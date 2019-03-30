
#include "Hello.h"

using namespace Hello;

std::string Hello::Say_Hello( std::string name )
{
	if ( name.empty() )
	{
		return "Hello World";
	}
	else
	{
		return "Hello " + name;
	}
}
