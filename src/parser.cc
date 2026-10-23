#include "parser.h"
#include <cctype>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <ios>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

std::optional<std::vector<CpuParser::CpuTimes>> CpuParser::parse_stat(const std::filesystem::path& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return std::nullopt;
    }

    std::vector<CpuTimes> cpus;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream stream(line);
        CpuTimes cpu{};

        if (!(stream >> cpu.name)) {
            continue;
        }

        std::string_view name {cpu.name};

        bool valid = (name == "cpu") ||
            (name.size() > 3 && name.starts_with("cpu")
                && std::isdigit(static_cast<unsigned char>(name[3])));

        if (!valid) {
            continue;
        }

        if (!(stream >> cpu.user >> cpu.nice >> cpu.system>> cpu.idle)) {
            return std::nullopt;
        }

        stream >> cpu.iowait >> cpu.irq >> cpu.softirq;

        cpus.push_back(cpu);
    }

    if (cpus.empty()) {
        return std::nullopt;
    }

    return cpus;
}

std::optional<std::size_t> CpuParser::count_cpu(const std::filesystem::path &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return std::nullopt;
    }

    std::string line;
    size_t core_count = 0;

    while (std::getline(file, line)) {
        if (line.rfind("cpu", 0) == 0 && line.size() > 3 && std::isdigit(static_cast<unsigned char>(line[3]))) {
            core_count++;
        }
    }

    return core_count;
}
