#pragma once

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

			LogFileWrapper() {
				fopen_s(&logfile, "log.txt", "w+");
			}

			~LogFileWrapper() {
				fclose(logfile);
			}
		} const lfw;

		uint32_t loglevel = LogLevel::Trace;
		bool logtoconsole = false;
	}

	void trace(const char* format, fmt::ArgList args) {
		if (detail::loglevel > LogLevel::Trace) return;

		fmt::print(detail::lfw.logfile, "{} trace : ", timestr());
		fmt::print(detail::lfw.logfile, format, args);

		if (detail::logtoconsole) {
			fmt::print("{} trace : ", timestr());
			fmt::print(format, args);
		}
	}

	void warn(const char* format, fmt::ArgList args) {
		if (detail::loglevel > LogLevel::Warn) return;

		fmt::print(detail::lfw.logfile, "{} warn  : ", timestr());
		fmt::print(detail::lfw.logfile, format, args);

		if (detail::logtoconsole) {
			fmt::print("{} warn : ", timestr());
			fmt::print(format, args);
		}
	}

	void yell(const char* format, fmt::ArgList args) {
		if (detail::loglevel > LogLevel::Error) return;

		fmt::print(detail::lfw.logfile, "{} yell  : ", timestr());
		fmt::print(detail::lfw.logfile, format, args);

		if (detail::logtoconsole) {
			fmt::print("{} yell : ", timestr());
			fmt::print(format, args);
		}
	}

	FMT_VARIADIC(void, trace, const char *)
	FMT_VARIADIC(void, warn, const char *)
	FMT_VARIADIC(void, yell, const char *)

}