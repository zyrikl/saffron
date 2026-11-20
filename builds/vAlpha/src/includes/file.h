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

#pragma once

#include <string>
#include <vector>

namespace file {
    void write_file(std::string fn, std::string message);
    void append_file(std::string fn, std::string message);

    std::string open_file(std::string fn);
    std::vector<std::string> open_file_by_line(std::string fn);
    std::string open_saffron_file(std::string fn);
}