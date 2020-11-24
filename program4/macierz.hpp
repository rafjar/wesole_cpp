#ifndef _macierz_hpp_
#define _macierz_hpp_

#include <vector>
#include <utility>

class Macierz {
    public:
        Macierz(int x, int y); // tworzy pustą macierz n x m
        double &element(int x, int y); // zwraca ref. do el. macierzy
        std::pair<int, int> rozmiar() const;

    private:
        int x_, y_;
        std::vector<double> vals_;
};

#endif