#include "turbo_vector.hpp"

#include <cmath>
#include <iostream>

int main() {
    TurboVector<float> vec;
    TurboVector<int> vec2;
    for(uint i=0; i<10; ++i)
        vec.push_back(std::sqrt(i));
    vec.push_at(3, 4.4444);

    vec.print();
    std::cout << std::endl;

    vec.pop_back();
    vec.print();
    std::cout << std::endl;

    for(const auto &i : vec)
        vec2.push_back(i);
    vec2.print();

    std::cout << "Czy ten typ jest moim wektorem? " << is_vector<float> << std::endl;
    std::cout << "Czy ten typ jest moim wektorem? " << is_vector<bool> << std::endl;
    std::cout << "Czy ten typ jest moim wektorem? " << is_vector<TurboVector<float>> << std::endl;
    std::cout << "Czy ten typ jest moim wektorem? " << is_vector<TurboVector<int>> << std::endl;
}