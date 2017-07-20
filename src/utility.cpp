#pragma once

#include "lut/utility.hpp"

#include <ctime>

namespace lut {
	std::string timestr() {
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[80];

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
		return std::string(buffer);
	}

	std::vector<std::string> split(const std::string& input, char sep) {
		std::vector<std::string> result;
		std::size_t pos = 0;
		while (pos != std::string::npos) {
			std::size_t newpos = input.find(sep, pos);
			if (newpos == std::string::npos)
				return result;

			result.push_back(input.substr(pos, newpos));
			pos = newpos + 1;
		}
		return result;
	}

	void w8usr() { getc(stdin); }
}