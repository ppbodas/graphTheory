#include "AppUtility.h"
#include <assert.h>
#include <iostream>
#include <sstream>
#include <iterator>
#include <iosfwd>
using namespace std;

template<typename T>
std::vector<T> AppUtility::split(const std::string& line)
{
	std::istringstream is(line);
	return std::vector<T>(std::istream_iterator<T>(is), std::istream_iterator<T>());
}
void AppUtility::showAssert(const std::string & errorMsg)
{
	assert(false && errorMsg.c_str());
	std::cout << errorMsg.c_str() <<std::endl;
}

void tempFunc()
{
	std::vector<int> v = AppUtility::split<int>("3");
}