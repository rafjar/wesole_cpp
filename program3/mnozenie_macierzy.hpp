#ifndef _mnozenie_macierzy_hpp_
#define _mnozenie_macierzy_hpp_

#include "macierz.hpp"
#include <optional>
#include <mutex>
#include <memory>
#include <vector>
#include <thread>

class KontrolerMnozenia {
    public:
        KontrolerMnozenia(const Macierz &m1, const Macierz &m2, Macierz &m3);
        inline const Macierz &czynnik1() const { return m1_; }
        inline const Macierz &czynnik2() const { return m2_; }
        inline Macierz &wynik() const { return m3_; }
        std::optional<Polozenie> coMamLiczyc();

    private:
        std::mutex blokada_;
        const Macierz &m1_;
        const Macierz &m2_;
        Macierz &m3_;
        Polozenie polozenieDoLiczenia_;
};

std::unique_ptr<Macierz> mnozenie_macierzy(const Macierz &m1, const Macierz &m2, int p);

class MnozycielMacierzy {
    public:
        MnozycielMacierzy(KontrolerMnozenia &km);
        void operator()();

    private:
        KontrolerMnozenia &km;
        const Macierz *m1_;
        const Macierz *m2_;
        Macierz *m3_;
};

#endif