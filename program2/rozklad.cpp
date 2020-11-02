#include "rozklad.hpp"

Rozklad::Rozklad(const std::vector<float> &dane) : dane_(dane) {}


RozkladGaussa::RozkladGaussa(const std::vector<float> &dane) : Rozklad(dane) {}

std::unique_ptr<ParametryRozkladu> RozkladGaussa::oblicz() const {
    auto params = std::make_unique<ParametryRozkladu>();

    double srednia = 0, sredniaZKwadratow = 0;
    std::for_each(dane_.begin(), dane_.end(), [&srednia, &sredniaZKwadratow] (const float val) {srednia += val; sredniaZKwadratow += val*val;});
    srednia /= dane_.size();
    sredniaZKwadratow /= dane_.size();

    (*params)["mean"] = srednia;
    (*params)["stdev"] = std::sqrt(sredniaZKwadratow - srednia*srednia);

    return params;
}

Rozklad* RozkladGaussa::kreator(const std::vector<float> &dane) {
    return new RozkladGaussa(dane);
}


RozkladPoissona::RozkladPoissona(const std::vector<float> &dane) : Rozklad(dane) {}

std::unique_ptr<ParametryRozkladu> RozkladPoissona::oblicz() const {
    auto params = std::make_unique<ParametryRozkladu>();

    double srednia = 0;
    std::for_each(dane_.begin(), dane_.end(), [&srednia](const float val) {srednia += val;});
    srednia /= dane_.size();

    (*params)["mean"] = srednia;

    return params;
}

Rozklad* RozkladPoissona::kreator(const std::vector<float> &dane) {
    return new RozkladPoissona(dane);
}


RozkladLorentza::RozkladLorentza(const std::vector<float> &dane) : Rozklad(dane) {}

std::unique_ptr<ParametryRozkladu> RozkladLorentza::oblicz() const {
    auto params = std::make_unique<ParametryRozkladu>();
    std::vector<float> kopia_danych(dane_.size());

    std::partial_sort_copy(dane_.begin(), dane_.end(), kopia_danych.begin(), kopia_danych.end());
    auto size = kopia_danych.size();
    double lambda = size % 2 == 0 ? (kopia_danych[size/2 - 1] + kopia_danych[size/2])/2 : kopia_danych[size/2];

    double srednia = 0;
    std::for_each(dane_.begin(), dane_.end(), [&srednia](const float val) {srednia += val;});
    srednia /= dane_.size();

    (*params)["median"] = lambda;
    (*params)["mean"] = srednia;

    return params;
}

Rozklad* RozkladLorentza::kreator(const std::vector<float> &dane) {
    return new RozkladLorentza(dane);
}


std::map<unsigned, KreatorRozkladu> FabrykaRozkladow::rozklady;
std::map<unsigned, std::string> FabrykaRozkladow::nazwy;

void FabrykaRozkladow::rejestruj(KreatorRozkladu kr, const std::string &nazwa) {
    auto rozmiar = rozklady.size();

    rozklady[rozmiar] = kr;
    nazwy[rozmiar] = nazwa;
}

Rozklad *FabrykaRozkladow::utworz(unsigned id, const std::vector<float> &dane) {
    return rozklady[id](dane);
}

std::string FabrykaRozkladow::nazwa(unsigned id) {
    return nazwy[id];
}

unsigned FabrykaRozkladow::ilosc() {
    return rozklady.size();
}