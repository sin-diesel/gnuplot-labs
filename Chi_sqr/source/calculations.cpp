

#include "chi.h"

double average(int n, std::vector<double>& data) {

    double res = 0.0;

    for (int i = 0; i < n; ++i) {
        res += data[i];
    }

    return res;
}


double average_weighted(int n, std::vector<double>& data, std::vector<double>& err) {

    double sigma_i = 0.0;
    double w_i = 0.0;
    double w = 0.0;
    double res = 0.0;
    /* average weighted x
    w - sum of w_i, where w_i  = 1 / sigma_i^2, sigma_i = err[i]
    dat_i = data[i], res = w_i * dat_i; */
    for (int i = 0; i < n; ++i) {
        sigma_i = err[i];
        assert(sigma_i > PRECISION);
        w_i = 1 / (sigma_i * sigma_i);
        w += w_i;
        res += w_i * data[i];
    }

    res = res / w;
    return res;
}

bool check_args(int argc, char** argv) {
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: chi data_file" << std::endl;
        return false;
    }
    return true;
}

int enter_data(std::fstream& data_file, std::vector<double>& xdat, std::vector<double>& ydat, std::vector<double>& errydat) {
    /* enter data */
    int N = 0;
    double elem = 0.0;
    data_file >> N;
    std::cout << "Number of points entered: " << N << std::endl;

    if (N < 0) {
        return -1;
    }

    for (int i = 0; i < N; ++i) {
        /* read in xdat, ydat, and errydat */
        data_file >> elem;
        xdat.push_back(elem);

        data_file >> elem;
        ydat.push_back(elem);

        data_file >> elem;
        errydat.push_back(elem);

    }

    std::cout << "Entered data: " << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << "x " << xdat[i] << " y " << ydat[i] << " erry " << errydat[i] << std::endl;
    }
    
    return N;
}