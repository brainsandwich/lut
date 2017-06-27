#pragma once

#include <string>

namespace lut {
	struct UUID {
		static const std::size_t size = 16;
		static const UUID Null;
		static UUID random();
		
		uint8_t data[size];

		UUID();
		UUID(const std::string& value);
		UUID(const UUID& other);
		UUID(UUID&& other);
		UUID& operator=(const UUID& other);
		UUID& operator=(UUID&& other);

		void assign(const std::string& value);
		std::string tostring() const;

		bool operator==(const UUID& other) const;
		bool operator!=(const UUID& other) const;
		bool operator<(const UUID& other) const;
		bool operator>(const UUID& other) const;
	};
}

namespace std {

	template <>
	struct hash<lut::UUID> {
		std::size_t operator()(const lut::UUID& k) const {
			return std::hash<const uint8_t*>()(k.data);
		}
	};

}