#include "dane_stat.hpp"

// Klasa bazowa
DaneStat::DaneStat(const std::string &nazwa) {
    nazwa_ = nazwa;
}

const std::string &DaneStat::nazwa() const {
    return nazwa_;
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

// Proxy
DaneStatProxy::DaneStatProxy(const std::string &nazwa) : DaneStat(nazwa), real_obj_(NULL) {}

DaneStatProxy::~DaneStatProxy() { delete real_obj_; }

const std::vector<float> &DaneStatProxy::dane() const {
    if(!real_obj_)
        real_obj_ =  new DaneStatReal(nazwa_);

    return real_obj_->dane();
}