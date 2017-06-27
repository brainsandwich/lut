#pragma once

#include "utility.hpp"

#include <fmt/format.h>

namespace lut {

	struct LogLevel {
		static const uint32_t Trace = 0;
		static const uint32_t Warn = 1;
		static const uint32_t Error = 2;
	};

	namespace detail {
		struct LogFileWrapper {
			FILE* logfile;

			LogFileWrapper();
			~LogFileWrapper();
		}

		extern const lfw;
		extern uint32_t loglevel;
		extern bool logtoconsole;
	}

	void trace(const char* format, fmt::ArgList args);
	void warn(const char* format, fmt::ArgList args);
	void yell(const char* format, fmt::ArgList args);

	FMT_VARIADIC(void, trace, const char *)
	FMT_VARIADIC(void, warn, const char *)
	FMT_VARIADIC(void, yell, const char *)

}