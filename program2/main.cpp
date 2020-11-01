#include "dane_stat.hpp"
#include "rozklad.hpp"

#include <iostream>

int main(int argc, char **argv) {
    if(argc < 2) {
        std::cout << "Brak plikow do analizy! Podaj pliki jako argumenty programu!" << std::endl;
        return 1;
    }

    // wskaźnik do obiektów przechowujący dane
    std::vector <std::shared_ptr<DaneStat>> dane;

    // wczytanie listy plików
    std::vector<std::string> pliki;
    for(int i=1; i<argc; ++i)
        dane.push_back(std::make_shared<DaneStatProxy>(argv[i]));

    // rejestrowanie wtyczek
    FabrykaRozkladow::rejestruj(&RozkladGaussa::kreator, std::string("Rozklad Gaussa"));
    FabrykaRozkladow::rejestruj(&RozkladLorentza::kreator, std::string("Rozklad Lorentza"));
    FabrykaRozkladow::rejestruj(&RozkladPoissona::kreator, std::string("Rozklad Poissona"));

    // zmienna do wybierania opcji
    int wybor_r = 0, wybor = 0;
    while(wybor_r != -1 || wybor != -1) {
        std::cout << "Wybierz plik do analizy, lub wpisz '-1' aby zakończyć program" << std::endl;
        for(int i=0; i<(int)dane.size(); i++)
            std::cout << i << "\t" << dane[i]->nazwa() << std::endl;

        std::cout << "Wybrana pozycja: ";
        std::cin >> wybor;
        if(wybor==-1)
            return 0;
        
        std::cout << "Wybierz badany rozklad, lub wpisz '-1' aby zakończyć program" << std::endl;
        for(int i=0; i<(int)FabrykaRozkladow::ilosc(); i++)
            std::cout << i << "\t" << FabrykaRozkladow::nazwa(i) << std::endl;

        std::cout << "Wybrana pozycja: ";
        std::cin >> wybor_r;
        if(wybor_r == -1)
            return 0;
        std::cout << std::endl;

        std::unique_ptr<Rozklad> rozkl(FabrykaRozkladow::utworz(wybor_r, dane[wybor]->dane()));
        
        auto obliczone = rozkl->oblicz();
        for(auto const &i : *obliczone)
            std::cout << i.first << '\t' << i.second << std::endl;
        std::cout << std::endl;
    }

}