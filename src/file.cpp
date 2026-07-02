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

#include "file.h"
#include "error.h"
#include <string>
#include <fstream>
#include <vector>

namespace file {
    void write_file(std::string fn, std::string message) {
        std::ofstream file(fn);

        if (!file.is_open()) {
            error::error_log("Could not open file for writing.");
        }

        file << message;
        file.close();
    }
    void append_file(std::string fn, std::string message) {
        std::ofstream file(fn, std::ios_base::app);

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