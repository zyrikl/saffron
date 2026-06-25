#include <fstream>
#include <iostream>
#include "error.h"
#include "menu.h"

void open_file(std::string fn) {
    if (fn.length() >= 5 && fn.substr(fn.length()-4, 4) == ".sff") {
        std::ifstream file(fn);

        if (file.is_open()) {
            std::string file_contents(
                (std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>()
            );

            file.close();
        } else {
            error::error_log("Could not open file "+fn);
        }
    } else {
        error::error_log("File not accepted! Try a .sff file.");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please choose an option." << std::endl;
        int selection = menu::setup_menu({"Enter IDLE", "Choose a file to run", "Exit"});

        if (selection == 0) {
            std::cout << "Entering IDLE..." << std::endl;
        } else if (selection == 1) {
            std::cout << "Type the name of a file: ";

            std::string file_name;
            std::cin >> file_name;
            
            open_file(file_name);
        } else if (selection == 2) {
            return 0;
        }
    } else if (argc == 2) {
        open_file(std::string(argv[1]));
    }

    return 0;
}