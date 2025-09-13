#include "my_math.hpp"
#include <cmath>

namespace my_math {

double factorial(int n) {
    double result = 1.0;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double power(double base, int exponent) {
    double result = 1.0;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}

AnswerHandler sin(double x) {
    double result = 0.0;
    for (int n = 0; n < 10; ++n) {
        double term = power(-1, n) * power(x, 2*n + 1) / factorial(2*n + 1);
        result += term;
    }
    return AnswerHandler(x, result);
}

AnswerHandler cos(double x) {
    double result = 0.0;
    for (int n = 0; n < 10; ++n) {
        double term = power(-1, n) * power(x, 2*n) / factorial(2*n);
        result += term;
    }
    return AnswerHandler(x, result);
}

AnswerHandler tan(double x) {
    double sin_val = sin(x).result;
    double cos_val = cos(x).result;
    return AnswerHandler(x, sin_val / cos_val);
}
}