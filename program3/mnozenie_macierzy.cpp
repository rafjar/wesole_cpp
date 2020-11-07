#include "mnozenie_macierzy.hpp"

KontrolerMnozenia::KontrolerMnozenia(const Macierz &m1, const Macierz &m2, Macierz &m3)
    : m1_(m1), m2_(m2), m3_(m3), polozenieDoLiczenia_(0, 0)
    {}

std::optional<Polozenie> KontrolerMnozenia::coMamLiczyc() {
    blokada_.lock(); // blokada jak na usosie o 14:00
    auto zwracanePolozenie = polozenieDoLiczenia_; // zapamiętanie pozycji do obliczenia
    polozenieDoLiczenia_.second++; // inkrementacja położenia do obliczenia dla potomnych
    if(polozenieDoLiczenia_.second == m3_.rozmiar().second) { // sprawdzenie czy należy dodać wiersz w położeniu
        polozenieDoLiczenia_.first++;
        polozenieDoLiczenia_.second = 0;
    }
    blokada_.unlock();

    // jesli wyszło poza zakres, to zwróć nic
    if(zwracanePolozenie.first == m3_.rozmiar().first)
        return {};

    // jeśli jest ok, to zwróć zapamiętaną pozycję
    return zwracanePolozenie;
}

std::unique_ptr<Macierz> mnozenie_macierzy(const Macierz &m1, const Macierz &m2, int p) {
    auto macierz = std::make_unique<Macierz>(m1.rozmiar().first, m2.rozmiar().second);
    KontrolerMnozenia kontroler(m1, m2, *macierz);
    std::vector<MnozycielMacierzy*> mnozyciele(p);

    std::vector<std::thread> matrixThreads(p);
    for(int i=0; i<p; i++) {
        mnozyciele[i] = new MnozycielMacierzy(kontroler);
        matrixThreads[i] = std::thread(*mnozyciele[i]);
    }

    for(auto &watek : matrixThreads)
        watek.join();

    return macierz;
}

MnozycielMacierzy::MnozycielMacierzy(KontrolerMnozenia &km) 
    : km(km), m1_(&km.czynnik1()), m2_(&km.czynnik2()), m3_(&km.wynik())
    {}

void MnozycielMacierzy::operator()() {
    auto rozmiarWiersza = m1_->rozmiar().second;

    auto poleDoLiczenia = km.coMamLiczyc();
    while(poleDoLiczenia) {
        for(int i=0; i<rozmiarWiersza; i++)
            m3_->element(poleDoLiczenia->first, poleDoLiczenia->second) += m1_->element(poleDoLiczenia->first, i) * m2_->element(i, poleDoLiczenia->second);

        poleDoLiczenia = km.coMamLiczyc();            
    }
}