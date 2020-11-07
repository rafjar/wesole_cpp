#include "macierz.hpp"

Macierz::Macierz(std::istream &is) {
    is >> n_ >> m_;

    int matrix_size = n_ * m_;
    mac_ = new int[matrix_size];
    for(int i=0; i<matrix_size; i++)
        is >> mac_[i];
}

Macierz::Macierz(int n, int m) {
    n_ = n;
    m_ = m;

    mac_ = new int[n*m]();
}

Macierz::~Macierz() {
    delete[] mac_;
}

int Macierz::element(int i, int j) const {
    return mac_[i*m_ + j];
}

int &Macierz::element(int i, int j) {
    return mac_[i*m_ + j];
}

RozmiarMacierzy Macierz::rozmiar() const {
    return RozmiarMacierzy(n_, m_);
}

std::ostream &operator<<(std::ostream &os, const Macierz &m) {
    os << m.n_ << '\t' << m.m_ << '\n'; // zapisanie rozmiaru

    for(int nn=0; nn<m.n_; nn++) {
        for(int mm=0; mm<m.m_; mm++) {
            os << m.mac_[nn*m.m_ + mm] << '\t';
        }
        os << '\n';
    }

    return os;
}