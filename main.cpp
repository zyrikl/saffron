#include <fstream>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
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

void run(std::string source) {
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scan_tokens();

    for (Token token : tokens) {
        std::cout << token.to_string() << std::endl;
    }
}

namespace file {
    void open_file(std::string fn) {
        if (fn.length() >= 5 && fn.substr(fn.length()-4, 4) == ".sff") {
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
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        menu::clear_screen();
        std::cout << logo << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        menu::clear_screen();
        // Might make 1 line below part of menu::setup_menu
        std::cout << "Please choose an option." << std::endl;
        int selection = menu::setup_menu({"Enter IDLE", "Choose a file to run", "License", "Exit Saffron"});

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
                } else run(code_line);
            }
        } else if (selection == 1) {
            std::cout << "\nType the name of a file: ";

            std::string file_name;
            std::cin >> file_name;
            
            run(file::open_file(file_name));
        } else if (selection == 2) {
            std::cout << file::open_file("LICENSE") << std::endl;
        } else if (selection == 3) {
            return 0;
        }
    } else if (argc == 2) {
        run(file::open_file(std::string(argv[1])));
    }

    return 0;
}