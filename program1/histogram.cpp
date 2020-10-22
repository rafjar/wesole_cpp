#include "histogram.hpp"

Histogram::Histogram() {
    srednia_akt_ = false;
    odchylenie_akt_ = false;
}

void Histogram::dodaj(float x) {
    dane_.push_back(x);

    srednia_akt_ = false;
    odchylenie_akt_ = false;
}

size_t Histogram::rozmiar() const {
    return dane_.size();
}

float Histogram::srednia() const {
    if(!srednia_akt_) {
        float srednia = 0;
        std::for_each(dane_.begin(), dane_.end(), [&srednia](const float &val) {srednia += val;});

        srednia_ = srednia / dane_.size();
        srednia_akt_ = true;
    }
    return srednia_;
}

float Histogram::odchylenie() const {
    if(!odchylenie_akt_) {
        float kwadratSredniej = this->srednia();
        kwadratSredniej *= kwadratSredniej;

        float sredniaZKwadratow = 0;
        std::for_each(dane_.begin(), dane_.end(), [&sredniaZKwadratow](const float &val) {sredniaZKwadratow += val*val;});
        sredniaZKwadratow /= dane_.size();

        odchylenie_ = std::sqrt(sredniaZKwadratow - kwadratSredniej);
        odchylenie_akt_ = true;
    }
    return odchylenie_;
}

float Histogram::max() const {
    return *std::max_element(dane_.begin(), dane_.end());
}

float Histogram::min() const {
    return *std::min_element(dane_.begin(), dane_.end());
}