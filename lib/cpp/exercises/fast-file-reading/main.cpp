// Fast File Reading — "How can I read a file, fast!"
// Видео: https://www.youtube.com/watch?v=Et1owjLHpS4
//
// Реконструкция из скриншотов. POSIX + C++23 (std::println), собирать на Linux/macOS:
//   clang++ -std=c++23 -O2 main.cpp -o parse
// Строки, восстановленные по смыслу (например fstat), помечены комментарием // [reconstructed].

#include <algorithm>
#include <charconv>
#include <chrono>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <print>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <unordered_map>

// POSIX
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 * You have a 10 million row file formatted as Location;Temperature called gas_stations.csv.
 * There are 10'000 unique locations (stations).
 * Temperature readings are -99.9 to 99.9.
 * All floats are single decimal (e.g. 22.0)
 * You want to read it quickly and compute summary statistics (e.g. min, max, average).
 * What should you do.
 *
 * Note: Don't worry about output formatting.
 *
 * Essentially, 'How can I read a file, fast!'
 */

namespace {

const std::string Filename = "gas_stations.csv";

struct Record {
	size_t Count{};
	float Min{}, Max{}, Sum{};
};

using StationRecords = std::unordered_map<std::string, Record>;

// Bad (default) implementation.
void Version1() {
	std::ifstream ifs(Filename, std::ifstream::in);
	if (!ifs.is_open()) {
		throw std::runtime_error("Cannot open file!");
	}

	// Process the input.
	StationRecords records;
	std::string station, reading;
	while (std::getline(ifs, station, ';') &&
	       std::getline(ifs, reading, '\n')) {
		const float readingValue = std::stof(reading);
		if (!records.contains(station)) {
			records[station] = {.Count = 1,
			                    .Min = readingValue,
			                    .Max = readingValue,
			                    .Sum = readingValue};
		} else {
			Record& existing = records[station];
			existing.Sum += readingValue;
			existing.Count += 1;
			existing.Max = std::max(readingValue, existing.Max);
			existing.Min = std::min(readingValue, existing.Min);
		}
	}
}

void TimeExecution(auto&& callable) {
	const auto start = std::chrono::steady_clock::now();
	callable();
	const auto end = std::chrono::steady_clock::now();
	std::println(
	    "Took {}ms",
	    std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
	        .count());
}

// We need to improve this!

struct MappedFileDetails {
	static constexpr int InvalidDescriptor = -1;

	int Descriptor{InvalidDescriptor};
	char* Begin{nullptr};
	size_t Size{0};

	[[nodiscard]] bool IsOpen() { return Descriptor != InvalidDescriptor; }

	void Close() {
		if (Descriptor == InvalidDescriptor) {
			return;
		}
		close(Descriptor);
	}
};

class MappedFile {
public:
	MappedFile(const std::filesystem::path& path) {
		const auto descriptor = open(path.c_str(), O_RDONLY);
		if (descriptor == -1) {
			throw std::system_error(errno, std::system_category(),
			                        "Cannot open file!");
		}

		struct stat sb{};                 // [reconstructed]
		if (fstat(descriptor, &sb) == -1) {  // [reconstructed] — нужен размер файла
			throw std::system_error(errno, std::system_category(),
			                        "Cannot stat file!");
		}

		// Lets open a handle.
		const auto start = static_cast<char*>(
		    mmap(nullptr, sb.st_size, PROT_READ, MAP_PRIVATE, descriptor, 0));
		if (start == MAP_FAILED) {
			throw std::system_error(errno, std::system_category(),
			                        "Cannot mmap file!");
		}

		details_ = {
		    .Descriptor = descriptor,
		    .Begin = start,
		    .Size = static_cast<size_t>(sb.st_size),
		};

		// Since we are reading sequentially, we tell the kernel to prefetch
		// pages aggressively.
		madvise(details_.Begin, details_.Size, MADV_SEQUENTIAL);
	}

	[[nodiscard]] std::span<const char> Data() const {
		return {details_.Begin, details_.Size};
	}

	~MappedFile() {
		if (!details_.IsOpen()) {
			return;
		}
		details_.Close();
		if (details_.Begin == nullptr) {
			return;
		}
		munmap(details_.Begin, details_.Size);
	}

private:
	MappedFileDetails details_;
};

struct StringStringViewHasher {
	// Allow for heterogeneous lookups,
	// so that std::string_view can be used to query for std::string key objects.
	using is_transparent = void;

	size_t operator()(std::string_view str) const {
		return std::hash<std::string_view>{}(str);
	}
	size_t operator()(const std::string& str) const {
		return std::hash<std::string>{}(str);
	}
};

void Version2() {
	MappedFile file{Filename};
	const auto view = file.Data();

	// Гетерогенный map: ключ std::string, но искать можно по string_view
	// без создания временного string-ключа.
	std::unordered_map<std::string, Record, StringStringViewHasher,
	                   std::equal_to<>>
	    records;

	auto begin = view.begin();
	while (begin != view.end()) {
		// Поле станции: до ';'.
		const auto endStation = std::ranges::find(begin, view.end(), ';');
		std::string_view station(std::to_address(begin),
		                         static_cast<size_t>(endStation - begin));
		begin = endStation + 1;

		// Поле температуры: до '\n'.
		const auto endLine = std::ranges::find(begin, view.end(), '\n');
		float reading;
		std::from_chars(std::to_address(begin), std::to_address(endLine),
		                reading);
		begin = (endLine == view.end()) ? endLine : endLine + 1;

		// Find the station.
		if (auto iterator = records.find(station);
		    iterator == records.end()) {
			records.emplace(station, Record{.Count = 1,
			                                .Min = reading,
			                                .Max = reading,
			                                .Sum = reading});
		} else {
			auto& existing = iterator->second;
			existing.Sum += reading;
			existing.Count += 1;
			existing.Max = std::max(reading, existing.Max);
			existing.Min = std::min(reading, existing.Min);
		}
	}
}

}  // namespace

int main() {
	TimeExecution(Version1);  // ~1520ms
	TimeExecution(Version2);  // mmap + from_chars + heterogeneous lookup
	return 0;
}
