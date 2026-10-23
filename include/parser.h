#ifndef CPU_PARSER_HPP
#define CPU_PARSER_HPP

#include <filesystem>
#include <fstream>
#include <optional>

class CpuParser {
public:
    struct CpuTimes {
        unsigned long long user, nice, system, idle, iowait, irq, softirq;
    };

    std::optional<CpuTimes> parse_stat(const std::filesystem::path& path);

private:
    std::ifstream file;
};

#endif
