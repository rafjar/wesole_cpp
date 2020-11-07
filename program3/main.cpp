#include "macierz.hpp"
#include "mnozenie_macierzy.hpp"

#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>

using namespace std::chrono_literals;

int main(int argc, char **argv) {
    if(argc != 5) {
        std::cout << "Podano zla liczbe argumentow! Podaj cztery argumenty: macierz1, macierz2, wynik, liczba wątków" << std::endl;
        return 1;
    }

    // Otworzenie plików    
    std::ifstream ifile1(argv[1]);
    std::ifstream ifile2(argv[2]);
    std::ofstream ofile(argv[3]);

    // Przypisanie liczby wątków
    int n_threads = std::atoi(argv[4]);

    // Utworzenie macierzy
    Macierz m1(ifile1);
    Macierz m2(ifile2);
    
    // Sprawdzenie czy to wgl da się pomonożyć
    if(m1.rozmiar().second != m2.rozmiar().first) {
        std::cout << "Złe wymiary macierzy - macierz1 powinna mieć tyle kolumn co macierz2 wierszy" << std::endl;
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    auto m3 = mnozenie_macierzy(m1, m2, n_threads);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << "us" << std::endl;
    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "ms" << std::endl;
    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::seconds>(end-start).count() << "s" << std::endl;

    ofile << *m3;

    ifile1.close();
    ifile2.close();
    ofile.close();
}