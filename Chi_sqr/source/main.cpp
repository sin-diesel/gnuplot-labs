/* This is a program for computing the a, b coefficients of of best-fit line
    for given set of data using chi-squares method 
    
    Data in file is represented as follows:
    x   y   yerr
    2   3   0.5
    3   4   0.2
    ...                 */


  /* TODO:
    1) Add coefficients errors calculation */

#include "chi.h"

int main(int argc, char** argv) {

    bool args_input = check_args(argc, argv);
    if (!args_input) {
        std::cerr << "Error entering arguments." << std::endl;
        return -1;
    }

    std::string file_name(argv[1]);
    std::fstream data_file;
    data_file.open(file_name, std::ios::in);
    if (!data_file) {
        std::cerr << "Error opening file." << std::endl;
        return -1;
    }

    std::vector<double> xdat;
    std::vector<double> ydat;
    std::vector<double> errydat;

    int N = enter_data(data_file, xdat, ydat, errydat);


    /* assuming sigma_i = errydat[i] */
    double weighted_x = average_weighted(N, xdat, errydat);
    std::cout << "Weighted (average) x: " << weighted_x << std::endl;

    double weighted_y = average_weighted(N, ydat, errydat);
    std::cout << "Weighted y: " << weighted_y << std::endl;

    std::vector<double> xdat_sqr;
    for (int i = 0; i < N; ++i) {
        xdat_sqr.push_back(xdat[i] * xdat[i]);
    }

    double weighted_x_sqr = average_weighted(N, xdat_sqr, errydat);
    std::cout << "Weighted(average) x^2: " << weighted_x_sqr << std::endl;

    std::vector<double> xydat;
    std::vector<double> errxydat;

    for (int i = 0; i < N; ++i) {
        xydat.push_back(xdat[i] * ydat[i]);
        /* there is no errx, hence, errxydat = errx + erry = 0 + erry = erry */
        errxydat.push_back(errydat[i]);
    }

    double weighted_xy = average_weighted(N, xydat, errxydat);
    std::cout << "Weighted xy: " << weighted_xy << std::endl;

    double a = (weighted_xy - weighted_y * weighted_x)/(weighted_x_sqr - weighted_x * weighted_x);
    std::cout << "Calculated a: " << a << std::endl;

    double b = weighted_y - a * weighted_x;
    std::cout << "Calculated b: " << b << std::endl;

    /* count chi squared: */
    double delta_y = 0;
    double sigma = 0;
    double expected = 0;
    double real = 0;
    double chi_sqr = 0;

    for (int i = 0; i < N; ++i) {
        /* count delta y */
        expected = a * xdat[i] + b;
        real = ydat[i];
        delta_y = expected - real;  

        /* count sigma */
        sigma = errydat[i];

        double chi = delta_y / sigma;
        chi_sqr += chi * chi;
    } 

    std::cout << "Calculated chi_sqr: " << chi_sqr << std::endl;

    /* degrees of freedom */
    std::cout << "chi_sqr / (n - p), where p = 2: " << chi_sqr / (N - 2) << std::endl;

    std::ofstream output;
    output.open("coefficients.dat");
    output << a << std::endl << b << std::endl;
    output.close();

    data_file.close();

    return 0;
}

