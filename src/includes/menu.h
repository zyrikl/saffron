#pragma once

#include <vector>
#include <string>

namespace menu {
    void clear_screen();
    void print_menu(const std::vector<std::string>& options, int highlighted, int times);
    int setup_menu(const std::vector<std::string>& options);
}