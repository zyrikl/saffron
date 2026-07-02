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

#include "menu.h"
#include <iostream>
#include <thread>
#include <chrono>

#ifdef _WIN32
    #include <conio.h>
    #define CLEAR_CMD "cls"
#else
    #include <termios.h>
    #include <unistd.h>
    #define CLEAR_CMD "clear"

    int getch() {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif

namespace menu {
    // Not really used but still useful
    void clear_screen() {
        std::system(CLEAR_CMD);
    }

    void print_menu(const std::vector<std::string>& options, int highlighted, int times = 0) {
        if (times > 0) {
            for (int i = 0; i < options.size() + 3; i++) {
                std::cout << "\033[A\033[K";
            }
        }
        std::cout << "Use up/down arrows to navigate. Press [enter] to select.\n";
        std::cout << "/==================================================\\\n";
        
        for (size_t i = 0; i < options.size(); ++i) {
            if (static_cast<int>(i) == highlighted) {
                std::string repeated_chars(45-options[i].length(), ' ');
                std::cout << "|| > \x1b[92m" << options[i] << repeated_chars << "\x1b[0m||\n";
            } else {
                std::string repeated_chars(45-options[i].length(), ' ');
                std::cout << "||   " << options[i] << repeated_chars << "||\n";
            }
        }
        std::cout << "\\==================================================/\n";
    }

    int setup_menu(const std::vector<std::string>& options) {
        int current_selection = 0;
        int times = 0;
        bool choosing = true;

        print_menu(options, current_selection, times);

        while (choosing) {
            int key = getch();

            #ifdef _WIN32
                if (key == 0 || key == 224) {
                    key = getch(); 
                    if (key == 72) key = 'UP';
                    if (key == 80) key = 'DOWN';
                }
                
                if (key == 'UP' || key == 72) {
                    current_selection = (current_selection - 1 + options.size()) % options.size();
                    times++;
                    print_menu(options, current_selection, times);
                } else if (key == 'DOWN' || key == 80) {
                    current_selection = (current_selection + 1) % options.size();
                    times++;
                    print_menu(options, current_selection, times);
                } else if (key == 13) { // enter
                    choosing = false;
                    times++;
                    print_menu(options, current_selection, times);
                }
            #else
                if (key == 27) { 
                    if (getch() == 91) { 
                        switch (getch()) {
                            case 65: // up
                                current_selection = (current_selection - 1 + options.size()) % options.size();
                                times++;
                                print_menu(options, current_selection, times);
                                break;
                            case 66: // down
                                current_selection = (current_selection + 1) % options.size();
                                times++;
                                print_menu(options, current_selection, times);
                                break;
                        }
                    }
                } else if (key == 10) { // enter
                    choosing = false;
                    times++;
                    print_menu(options, current_selection, times);
                }
            #endif
        }

        return current_selection;
    }

    void slow_print(std::string input) {
        std::stringstream ss(input);
        std::string token;
        
        while (std::getline(ss, token)) {
            std::cout << token << std::endl;
            if (token != "") std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}