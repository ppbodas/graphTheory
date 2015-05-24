#pragma once
#include <vector>
namespace AppUtility
{
	template<typename T>
	std::vector<T> split(const std::string& line);	
	void showAssert(const std::string & errorMsg);

	std::vector<std::string> split(const std::string& line);
}