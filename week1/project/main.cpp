#include "my_math.hpp"
#include <iostream>
#include <cmath>

int main() {
    double angle;

    std::cin >> angle;
    
    auto sin_result = my_math::sin(angle);
    auto cos_result = my_math::cos(angle);
    auto tan_result = my_math::tan(angle);
    
    sin_result.print();
    cos_result.print();
    tan_result.print();
    
    return 0;
}