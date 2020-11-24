#include "macierz.hpp"

Macierz::Macierz(int x, int y)
    : x_(x), y_(y), vals_(std::vector<double>(x*y)) {

}

double &Macierz::element(int x, int y) {
    return vals_[x_*y + x];
}

std::pair<int, int> Macierz::rozmiar() const {
    return std::make_pair(x_, y_);
}