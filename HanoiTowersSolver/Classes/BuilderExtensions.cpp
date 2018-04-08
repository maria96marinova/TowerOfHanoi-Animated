#include "stdafx.h"
#include "BuilderExtensions.h"

#include <sstream>

using std::string;
using std::ostringstream;

string BuilderExtensions::IntToString(size_t number)
{
	ostringstream oss;
	
	oss<< number;
	
	return oss.str();
}