#pragma once

#include "LUT/io.hpp"

namespace lut {

	detail::LogFileWrapper::LogFileWrapper() {
		fopen_s(&logfile, "log.txt", "w+");
	}

	detail::LogFileWrapper::~LogFileWrapper() {
		fclose(logfile);
	}

	const detail::LogFileWrapper detail::lfw;

	uint32_t detail::loglevel = LogLevel::Trace;
	bool detail::logtoconsole = false;

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

}