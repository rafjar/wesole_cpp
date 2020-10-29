#include "dane_stat.hpp"

// Klasa bazowa
DaneStat::DaneStat(const std::string &nazwa) {
    nazwa_ = nazwa;
}

// Klasa prawdziwa
DaneStatReal::DaneStatReal(const std::string &nazwa) : DaneStat(nazwa) {
    double liczba;
    std::ifstream file(nazwa);

    while(file >> liczba)
        data_.push_back(liczba);

    file.close();
}

const std::vector<float> &DaneStatReal::dane() const {
    return data_;
}

const std::string &DaneStatReal::nazwa() const { return nazwa_; } // nie robi nic, bo proxy to wykonuje

// Proxy
DaneStatProxy::DaneStatProxy(const std::string &nazwa) : DaneStat(nazwa), real_obj_(NULL) {}

DaneStatProxy::~DaneStatProxy() { delete real_obj_; }

const std::vector<float> &DaneStatProxy::dane() const {
    if(!real_obj_)
        real_obj_ =  new DaneStatReal(nazwa_);

    return real_obj_->dane();
}

const std::string &DaneStatProxy::nazwa() const {
    return nazwa_;
}