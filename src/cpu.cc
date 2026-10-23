#include "cpu.h"
#include <filesystem>
#include <fstream>
#include <ios>
#include <optional>
#include <stdexcept>
#include <string>

std::optional<CpuParser::CpuTimes> CpuParser::parse_stat(const std::filesystem::path& path) {
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {

        if (file.is_open()) {
            file.close();
        }

        file.open(path);

        std::string label;
        CpuTimes times { };

        file >> label >> times.user >> times.nice >> times.system >> times.idle >> times.iowait >> times.irq >> times.softirq;

        return times;
    } catch (const std::ios_base::failure& e) {
        throw std::runtime_error("File error: failed to open or read /proc/stat");
    }
}
