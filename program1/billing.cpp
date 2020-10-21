#include "billing.hpp"

std::string Polaczenie::kod() const {
    return nr.substr(0, 2);
}

std::istream &operator>> (std::istream &is, Polaczenie &p) {
    is >> p.dzien >> p.nr >> p.czas;
    return is;
}

Billing::Billing(std::istream &is) {
    Polaczenie a;
    while(is >> a) {
        blng_.push_back(a);
    }
}

void Billing::statystykaDzienna(std::ostream &os) const {
    std::vector <unsigned> statystyka(31, 0);
    int total = 0;

    for(auto &polaczenie : blng_) {
         statystyka[polaczenie.dzien-1]++;
         total++;
    }

    int max_element = *std::max_element(statystyka.begin(), statystyka.end());
    int nrDnia = 0;
    for(auto &statDzienna : statystyka) {
        os << std::setw(2) << ++nrDnia << ": " << std::setw(3) << statDzienna << " (" << std::setprecision(3) << (float)statDzienna/total*100 << "%)\t";


        int nGwiazdek = 20 * statDzienna/max_element; 
        for(int i=0; i<nGwiazdek; i++) {
            os << '*';
        }
        os << std::endl;
    }
    os << std::endl << "Wykonanych polaczen: " << total << std::endl << std::endl;
}

void Billing::statystykaKrajowa(std::ostream &os) const {
    std::map <std::string, Histogram> statystyka;

    for(auto &statDzienna : blng_) {
        statystyka[statDzienna.kod()].dodaj(statDzienna.czas);
    }

    os << "Kraj" << std::setw(4) << "N." << std::setw(5) << " Sred." << std::setw(5) << " Odch." << std::setw(5) << " Min." << std::setw(6) << " Max." << std::endl;
    for(auto it=statystyka.begin(); it!=statystyka.end(); it++) {
        os << it->first << ": " << std::setw(4) << it->second.rozmiar() << ' ' << std::setprecision(4) << std::setw(5) << it->second.srednia() << ' ' << std::setprecision(4) << std::setw(5) << it->second.odchylenie() << ' ' << std::setw(5) << it->second.min() << ' ' << std::setw(5) << it->second.max() << std::endl;
    }
}