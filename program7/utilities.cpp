#include "utilities.hpp"

std::unique_ptr<std::vector<std::pair<double, double>>> load_data(std::string filename) {
    auto vec = std::make_unique<std::vector<std::pair<double, double>>>();

    std::ifstream ifile(filename);
    double x, y;
    while(ifile >> x >> y) {
        vec->push_back(std::make_pair(x, y));
    }
    ifile.close();

    return vec;
}

std::pair<double, double> linear_regression(std::unique_ptr<std::vector<std::pair<double, double>>> &pointer) {
    double sx = 0, sy = 0, sxx = 0, syy = 0, sxy = 0;
    for(const auto &i : *pointer) {
        double x = i.first;
        double y = i.second;

        sx += x;
        sy += y;
        sxx += x*x;
        syy += y*y;
        sxy += x*y;
    }

    double delta = pointer->size()*sxx - sx*sx;
    
    double a = (pointer->size()*sxy - sx*sy) / delta;
    double b = (sxx*sy - sx*sxy) / delta;

    return std::make_pair(a, b);
}

std::tuple<int, int, int, int> plot_size(std::unique_ptr<std::vector<std::pair<double, double>>> &pointer, float m) {
    double x_min, x_max, y_min, y_max;
    x_min = pointer->at(0).first;
    x_max = pointer->at(0).first;
    y_min = pointer->at(0).second;
    y_max = pointer->at(0).second;
    for(const auto &i : *pointer) {
        double x = i.first;
        double y = i.second;
        if(x > x_max)
            x_max = x;
        if(x < x_min)
            x_min = x;
        if(y > y_max)
            y_max = y;
        if(y < y_min)
            y_min = y;
    }

    double delta_x, delta_y;
    delta_x = x_max - x_min;
    delta_y = y_max - y_min;

    int w_min, w_max, h_min, h_max;
    w_min = x_min - m*delta_x;
    w_max = x_max + m*delta_x;
    h_min = y_min - m*delta_y;
    h_max = y_max + m*delta_y;

    return std::make_tuple(w_min, w_max, h_min, h_max);
}