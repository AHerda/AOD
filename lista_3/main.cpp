#include <iostream>

int main(int argc, char** argv) {
    if(argc != 7) {
        std::cerr << "Zła liczba argumentów";
    }

    std::string in_file;
    std::string out_file;
    std::string graph;

    for(int i = 1; i < 7; i++) {
        if(std::string(argv[i]) == "-d") graph = std::string(argv[i + 1]);
        else if(std::string(argv[i]) == "-ss")
    }
}