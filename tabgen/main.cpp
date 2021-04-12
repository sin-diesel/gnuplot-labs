#include <iostream>
#include <fstream>
#include <vector>

void parse_line(std::string& line, std::fstream& out_file) {
    int cols = 0;

    char *cstr = new char [line.length()+1];
    std::strcpy(cstr, line.c_str());

    char *p = std::strtok(cstr, " \t");
    while (p != 0) {
        std::string word(p);
        out_file << word;
        p = std::strtok(NULL, " \t");
        if (p != 0) {
            out_file << " & ";
        }
        ++cols;
    }

    /* Print new line and hline at the end of each row */
    out_file << "\\\\\\hline\n";

    delete[] cstr;
}

void print_header(int cols, std::fstream& out_file) {
    out_file << "\\input{preambule_article}\n\n"
                 "%%% [h] - place here\n" 
                 "\\begin{table}[h!]\n"
                 "\\begin{center}\n"
                 "%%% |c|c|c| - centering with vertical lines\n";

    out_file << "\\begin{tabular}{|";
    for (int i = 0; i < cols; ++i) {
        out_file << "c|";
    }
    out_file << "}\\hline\n";
    out_file << "\\multicolumn{" << cols << "}"
                "{|p{\\linewidth}|}{\\textbf{title}} \\\\\\hline\n";
}

void print_trailer(std::fstream& out_file) {
    out_file << "\\end{tabular}\n"
                "\\end{center}\n"
                "\\end{table}\n";
}

int count_cols(std::string& line) {
    int cols = 0;

    char *cstr = new char [line.length()+1];
    std::strcpy(cstr, line.c_str());

    char *p = std::strtok(cstr, " \t");
    while (p != 0) {
        p = std::strtok(NULL, " \t");
        ++cols;
    }

    delete[] cstr;
    return cols;
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
    int cols = -1;

    while (std::getline(input_file, line)) {
        if (cols == -1) {
            cols = count_cols(line);
            std::cout << "Cols: " << cols << std::endl;
            print_header(cols, out_file);
        }
        parse_line(line, out_file);
    }
    print_trailer(out_file);

    std::cout << "Cols: " << cols << std::endl;

    out_file.close();
    input_file.close();
    return 0;

}