#include <fstream>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <stdexcept>
#include "error.h"
#include "menu.h"
#include "token.h"
#include "scanner.h"

std::string logo = "\n"
"/==================================================\\\n"
"||  \x1b[93m    ____         __  __                   \x1b[0m    ||\n"
"||  \x1b[93m   / ___|  __ _ / _|/ _|_ __ ___  _ __    \x1b[0m    ||\n"
"||  \x1b[93m   \\___ \\ / _` | |_| |_| '__/ _ \\| '_ \\   \x1b[0m    ||\n"
"||  \x1b[93m    ___) | (_| |  _|  _| | | (_) | | | |  \x1b[0m    ||\n"
"||  \x1b[93m   |____/ \\__,_|_| |_| |_|  \\___/|_| |_|  \x1b[0m    ||\n"
"||                                                ||\n"
"\\==================================================/\n"
"       <<< v0.1.0 alpha release >>>";

std::string copyright_info = R"(

    Saffron programming language.  Copyright (C) 2026  Charles Wang.
    This program comes with no warranty; for details see the license.
    This is free software, and you are welcome to redistribute it
    under certain conditions; see the license for details.

    This notices requires no user input. Saffron will automatically
    load 10 seconds after Saffron is first used.

)";

void run(std::string source) {
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scan_tokens();

    for (Token token : tokens) {
        std::cout << token.to_string() << std::endl;
    }
}

namespace file {
    void write_file(std::string fn, std::string message) {
        std::ofstream file(fn);

        if (!file.is_open()) {
            error::error_log("Could not open file for writing.");
        }

        file << message;
        file.close();
    }
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
            error::error_log("Could not open file "+fn);
        }
        return "";
    }
    std::vector<std::string> open_file_by_line(std::string fn) {
        std::vector<std::string> lines;
        std::ifstream file(fn);

        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                lines.push_back(line);
            }

            file.close();
            return lines;
        } else {
            error::error_log("Could not open file "+fn);
        }
        return {""};
    }
    std::string open_saffron_file(std::string fn) {
        if ((fn.length() >= 5 && fn.substr(fn.length()-4, 4) == ".sff")) {
            std::ifstream file(fn);

            if (file.is_open()) {
                std::string file_contents(
                    (std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>()
                );

                //run(file_contents);
                file.close();
                return file_contents;
            } else {
                error::error_log("Could not open file "+fn);
            }
        } else {
            error::error_log("File not accepted! Try a .sff file.");
        }
        return "";
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        bool seen_copyright = false;

        try {
            std::vector<std::string> attributes = file::open_file_by_line(".saffron_attributes");
            if (attributes[0] == std::string("1")) {
                seen_copyright = true;
            }
        } catch (const std::runtime_error& error) {
            file::write_file(".saffron_attributes", "1\n");
        }

        if (!seen_copyright) {
            menu::clear_screen();
            std::cout << copyright_info << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        }

        menu::clear_screen();
        std::cout << logo << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        menu::clear_screen();
        // Might make 1 line below part of menu::setup_menu
        std::cout << "Please choose an option." << std::endl;
        int selection = menu::setup_menu(
            {
                "Enter IDLE", 
                "Choose a file to run", 
                "GNU General Public License v3", 
                "View copyright info", 
                "Exit Saffron"
            }
        );

        if (selection == 0) {
            menu::clear_screen();
            std::cout << "Welcome to the Saffron IDLE!" << std::endl;
            std::cout << "Type 'exit' to escape." << std::endl;

            bool wants_out = false;
            while (!wants_out) {
                std::string code_line;

                std::cout << "  \x1b[2m>>>\x1b[0m ";
                std::cin >> code_line;

                if (code_line == "exit") {
                    wants_out = true;
                    std::cout << "Exiting IDLE." << std::endl;
                } else {
                    try {
                        run(code_line);
                    }
                    catch (const std::runtime_error& error) { 
                        std::cerr << error.what() << "\n";
                    }
                }
            }
        } else if (selection == 1) {
            std::string file_name;
            std::cout << "\nType the name of a file: ";
            std::cin >> file_name;

            try {
                run(file::open_saffron_file(file_name));
            }
            catch (const std::runtime_error& error) { 
                std::cerr << error.what() << "\n";
            }
        } else if (selection == 2) {
            menu::clear_screen();
            menu::slow_print(file::open_file("LICENSE"));
        } else if (selection == 3) {
            menu::clear_screen();
            std::cout << copyright_info << std::endl;
            return 0;
        } else if (selection == 4) {
            return 0;
        }
    } else if (argc == 2) {
        try {
            run(file::open_saffron_file(argv[1]));
        }
        catch (const std::runtime_error& error) { 
            std::cerr << error.what() << "\n";
        }
    }

    return 0;
}