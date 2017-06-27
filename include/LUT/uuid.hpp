#pragma once

#include <random>
#include <sstream>
#include <iomanip>

namespace lut {
	struct UUID {
		static const std::size_t size = 16;
		static const UUID Null;
		static UUID random() {
			std::random_device engine;
			const std::size_t rs = sizeof(unsigned int);

			UUID result;
			for (std::size_t i = 0; i < size; i += rs) {
				unsigned int value = engine();
				memcpy(result.data + i, &value, rs);
			}
			return result;
		}
		
		uint8_t data[size];

		UUID() {
			*this = Null;
		}

		UUID(const std::string& value) {
			assign(value);
		}

		UUID(const UUID& other) {
			memcpy(data, other.data, size);
		}

		UUID(UUID&& other) {
			memmove(data, other.data, size);
		}

		UUID& operator=(const UUID& other) {
			memcpy(data, other.data, size);
			return *this;
		}

		UUID& operator=(UUID&& other) {
			memmove(data, other.data, size);
			return *this;
		}

		void assign(const std::string& value) {
			std::vector<std::string> chunks = lut::split(value, '-');
			if (chunks.size() != 5
				|| chunks[0].size() != 8
				|| chunks[1].size() != 4
				|| chunks[2].size() != 4
				|| chunks[3].size() != 4
				|| chunks[4].size() != 12)
				return;

			std::size_t offset = 0;
			for (const auto& str : chunks) {
				for (std::size_t i = 0; i < str.size(); i += 2)
					data[offset++] = std::stoi(str.substr(i, i + 2));
			}
		}

		std::string tostring() const {
			const std::size_t chunksizes[] = { 8, 4, 4, 4, 12 };

			std::stringstream ss;
			std::size_t offset = 0;
			for (std::size_t i = 0; i < 5; i++) {
				for (std::size_t k = 0; k < chunksizes[i] / 2; k++)
					ss << std::setfill('0') << std::setw(2) << std::hex << (uint32_t) data[offset++];
				if (i < 4)
					ss << '-';
			}

			return ss.str();
		}

		bool operator==(const UUID& other) const {
			return memcmp(data, other.data, size) == 0;
		}

		bool operator!=(const UUID& other) const {
			return !(*this == other);
		}

		bool operator<(const UUID& other) const {
			return memcmp(data, other.data, size) < 0;
		}

		bool operator>(const UUID& other) const {
			return memcmp(data, other.data, size) > 0;
		}
	};

	const UUID UUID::Null = UUID("ffffffff-ffff-ffff-ffff-ffffffffffff");
}

namespace std {

	template <>
	struct hash<lut::UUID> {
		std::size_t operator()(const lut::UUID& k) const {
			return std::hash<const uint8_t*>()(k.data);
		}
	};

}