#include <iostream>

int main(int argc, char** argv) {
    if(argc != 7) {
        std::cerr << "Zła liczba argumentów";
        return -1;
    }

    std::string in_file;
    std::string out_file;
    std::string graph;
    short mode;

    for(int i = 1; i < 7; i++) {
        if(std::string(argv[i]) == "-d") {
            graph = std::string(argv[i + 1]);
        }
        else if(std::string(argv[i]) == "-ss") {
            in_file = std::string(argv[i + 1]);
            mode = 1;
        }
        else if(std::string(argv[i]) == "-p2p") {
            in_file = std::string(argv[i + 1]);
            mode = 2;
        }
        else if(std::string(argv[i]) == "-oss" || std::string(argv[i]) == "-op2p") {
            out_file = std::string(argv[i + 1]);
        }
    }

    return 1;
}