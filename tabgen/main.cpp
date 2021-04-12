#include <iostream>
#include <fstream>
#include <vector>

void parse_line(char* cstr, std::fstream& out_file) {
    char *p = std::strtok(cstr, " \t");
    while (p != 0) {
        std::string word(p);
        out_file << word;
        p = std::strtok(NULL, " \t");
        if (p != 0) {
            out_file << " & ";
        }
    }
}

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cout << "Usage: tabgen <input_file>" << std::endl;
        return EXIT_FAILURE;
    }
    std::string file_name(argv[1]);

    std::fstream input_file;
    input_file.open(file_name, std::ios::in);
    if (!(input_file.is_open())) {
        std::cout << "Error opening file" << std::endl;
    }

    std::fstream out_file;
    out_file.open("output.tex", std::ios::out | std::ios::trunc);
    if (!(out_file.is_open())) {
        std::cout << "Error opening file" << std::endl;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input_file, line)) {
        char *cstr = new char [line.length()+1];
        std::strcpy(cstr, line.c_str());
        parse_line(cstr, out_file);
        /* print new line when line has been parsed and delimiters added */
        out_file << std::endl;
        delete[] cstr;
    }

    out_file.close();
    input_file.close();
    return 0;

}