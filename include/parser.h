#ifndef CPU_PARSER_HPP
#define CPU_PARSER_HPP

#include <cstddef>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

class CpuParser {
public:
    struct CpuTimes {
        std::string name;
        unsigned long long user{}, nice{}, system{}, idle{};
        unsigned long long iowait{}, irq{}, softirq{};
    };

    std::optional<std::vector<CpuTimes>> parse_stat(const std::filesystem::path& path);
    std::optional<std::size_t> count_cpu(const std::filesystem::path& path);

};

#endif
