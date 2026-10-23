#include "parser.h"
#include <cstdlib>
#include <filesystem>
#include <iostream>

const std::filesystem::path path {"/proc/stat"};

int main() {
    CpuParser parser;

    auto s {parser.parse_stat(path)};

    if (s.has_value()) {

        auto [user, nice, system, idle, iowait, irq, softirq] = *s;

        std::cout
            << "cpu" << ""
            << s->user << " "
            << s->nice << " "
            << s->system << " "
            << s->idle << " "
            << s->iowait << " "
            << s->irq << " "
            << s->softirq << "\n";

        return EXIT_SUCCESS;
    }

    std::cerr << "Failed to parse CPU stats.\n";
    return EXIT_FAILURE;
}
