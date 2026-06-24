import std;

int main() {
    std::ifstream file("./tests/hello_word.sff");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }

    file.close(); 
    return 0;
}