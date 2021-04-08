/* This is a program for computing the a, b coefficients of of best-fit line
    for given set of data using khi-squares method 
    
    Data in file is represented as follows:
    x   y   yerr
    2   3   0.5
    3   4   0.2
    ...
                    */

#include <iostream>
#include <fstream>
#include <vector>

#define PRECISION 1e-5

double average(int n, std::vector<double>& data) {
    double sigma_i = 0.0;
    double w_i = 0.0;
    double w = 0.0;
    double dat_i = 0.0;
    double res = 0.0;
    /* average  x
        dat_i = data[i], res += dat_i; */
    for (int i = 0; i < n; ++i) {

        dat_i = data[i];
        res += dat_i;

    }

    return res;
}


double average_weighted(int n, std::vector<double>& data, std::vector<double>& err) {
    double sigma_i = 0.0;
    double w_i = 0.0;
    double w = 0.0;
    double dat_i = 0.0;
    double res = 0.0;
    /* average weighted x
        w - sum of w_i, where w_i  = 1 / sigma_i^2, sigma_i = err[i]
        dat_i = data[i], res = w_i * dat_i; */
    for (int i = 0; i < n; ++i) {
        sigma_i = err[i];
        assert(sigma_i > PRECISION);

        w_i = 1 / (sigma_i * sigma_i);
        w += w_i;

        dat_i = data[i];
        res += w_i * dat_i;

    }

    res = res / w;
    return res;
}

int main(int argc, char** argv) {
    if (argc > 1) {
        std::cout << "Usage: ./fit < <data_file>" << std::endl;
        exit(EXIT_FAILURE);
    }

    // std::string data_file(argv[1]);
    // std::cout << "Calculating data from file " << data_file << "..." << std::endl;

    /* enter data */
    int N = 0;
    std::cin >> N;
    double elem = 0.0;

    std::cout << "Number of points: " << N << std::endl;

    std::vector<double> xdat;
    std::vector<double> ydat;
    std::vector<double> errydat;

    for (int i = 0; i < N; ++i) {
        /* read in xdat, ydat, and errydat */
        std::cin >> elem;
        xdat.push_back(elem);

        std::cin >> elem;
        ydat.push_back(elem);

        std::cin >> elem;
        errydat.push_back(elem);

    }

    std::cout << "Entered data: " << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << "x " << xdat[i] << " y " << ydat[i] << " erry " << errydat[i] << std::endl;
    }

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
    double chi = 0;

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
    int p = 2;
    std::cout << "chi_sqr / (n - p), where p = 2: " << chi_sqr / (N - 2) << std::endl;

    std::ofstream output;
    output.open("coefficients.dat");
    output << a << std::endl << b << std::endl;
    output.close();


    /* calculate errors */
    
    return 0;
}