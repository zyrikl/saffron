#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

std::string open_file(std::string fn) {
    std::ifstream file(fn);

    if (file.is_open()) {
        std::string file_contents(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
        );

        file.close();
        return file_contents;
    } else {
        std::cerr << "Could not open file "+fn << std::endl;
        std:exit(1);
    }

    return "";
}

enum Token {};

int main(int argc, char *argv[]) {
    if (argc == 2) {
        open_file(argv[1]);
    } else {
        std::cout << "Usage: saffron [filename]" << std::endl;
    }

    return 0;
}