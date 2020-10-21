#include <iostream>
#include "billing.hpp"

int main() {
    Billing biling(std::cin);

    std::cout << "*** STATYSTYKA DZIENNA ***" << std::endl;
    biling.statystykaDzienna(std::cout);

    std::cout << "*** STATYSTYKA KRAJOWA ***" << std::endl;
    biling.statystykaKrajowa(std::cout);

    return 0;
}