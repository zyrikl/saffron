/*
    Copyright (C) 2026  Charles Wang

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
#include "file.h"
#include "parser.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

int terminal_height() {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        }
    #else
        struct winsize w;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
            return w.ws_row;
        }
    #endif
        return 24;
}

std::string logo = "\n"
"/==================================================\\\n"
"||  \x1b[93m    ____         __  __                   \x1b[0m    ||\n"
"||  \x1b[93m   / ___|  __ _ / _|/ _|_ __ ___  _ __    \x1b[0m    ||\n"
"||  \x1b[93m   \\___ \\ / _` | |_| |_| '__/ _ \\| '_ \\   \x1b[0m    ||\n"
"||  \x1b[93m    ___) | (_| |  _|  _| | | (_) | | | |  \x1b[0m    ||\n"
"||  \x1b[93m   |____/ \\__,_|_| |_| |_|  \\___/|_| |_|  \x1b[0m    ||\n"
"||                                                ||\n"
"\\==================================================/\n"
"       <<< v0.1.0 alpha release >>>\n";

std::string copyright_info = R"(

    Saffron programming language.  Copyright (C) 2026  Charles Wang.
    This program comes with no warranty; for details see the license.
    This is free software, and you are welcome to redistribute it
    under certain conditions; see the license for details.
)";

void run(std::string source) {
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scan_tokens();

    Parser parser(tokens);

    //std::cout << "ready>" << std::endl;
    //parser.get_next_token();
    parser.mainloop();
}

void text_file_choose() {
    std::string file_name;
    std::cout << "\nType the name of a file: ";
    std::cin >> file_name;

    try {
        run(file::open_saffron_file(file_name));
    }
    catch (const std::runtime_error& error) {
        std::cerr << error.what();
        text_file_choose();
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
            // might want to change to file::append_file
            file::write_file(".saffron_attributes", "1\n");
        }

        if (!seen_copyright) {
            menu::clear_screen();
            std::cout << copyright_info << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        }

        menu::clear_screen();
        std::cout << logo << std::endl;

        if (terminal_height() < 20) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            menu::clear_screen();
        }
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
            text_file_choose();
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