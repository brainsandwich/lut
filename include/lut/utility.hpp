#pragma once

#include <string>
#include <vector>

namespace lut {
	std::string timestr();
	std::vector<std::string> split(const std::string& input, char sep);
	void w8usr();
}