#include "parser.h"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <ostream>

const std::filesystem::path path {"/proc/stat"};

int main() {
    CpuParser parser;
    auto cpus {parser.parse_stat(path)};

    if (!cpus) {
        std::cerr << "Failed to parse /proc/stat\n";
        return 1;
    }

    for (const auto& cpu : *cpus) {
            std::cout << cpu.name << " "
                      << cpu.user << " "
                      << cpu.nice << " "
                      << cpu.system << " "
                      << cpu.idle << " "
                      << cpu.iowait << " "
                      << cpu.irq << " "
                      << cpu.softirq << "\n";
    }

    auto cpu_count {parser.count_cpu(path)};

    if (cpu_count.has_value()) {
        std::cout << "CPU count: " << *cpu_count << std::endl;
    } else {
        std::cerr << "Error: CPU count can not be determined for path" << path << std::endl;
    }


    return EXIT_SUCCESS;
}
