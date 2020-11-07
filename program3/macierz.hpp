#ifndef _macierz_hpp_
#define _macierz_hpp_

#include <utility>
#include <istream>

typedef std::pair<int, int> RozmiarMacierzy;
typedef std::pair<int, int> Polozenie;

class Macierz {
    public:
        Macierz(std::istream &is); // tworzy macierz na podstawie strumienia
        Macierz(int n, int m); // tworzy pustą macierz n x m
        ~Macierz();
        int element(int i, int j) const; // zwraca element macierzy (kopia przez wartość)
        int &element(int i, int j); // zwraca ref. do el. macierzy
        RozmiarMacierzy rozmiar() const;

    private:
        int n_; // wierzsze
        int m_; // kolumny
        int *mac_;

        friend std::ostream &operator<<(std::ostream &os, const Macierz &m);
};

std::ostream &operator<<(std::ostream &os, const Macierz &m);

#endif