

#include <iostream>
#include <fstream>
#include <vector>

#define PRECISION 1e-5

double average(int n, std::vector<double>& data);

double average_weighted(int n, std::vector<double>& data, std::vector<double>& err);

bool check_args(int argc, char** argv);

int enter_data(std::fstream& data_file, std::vector<double>& xdat, std::vector<double>& ydat, std::vector<double>& errydat);
