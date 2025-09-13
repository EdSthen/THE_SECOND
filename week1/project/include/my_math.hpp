#pragma once
#include "ans_handler.hpp"

namespace my_math {
    AnswerHandler sin(double x);
    AnswerHandler cos(double x);
    AnswerHandler tan(double x);
    
    double factorial(int n);
    double power(double base, int exponent);
}