#include "ans_handler.hpp"
#include <iostream>

AnswerHandler::AnswerHandler(double x_val, double result_val) 
    : x(x_val), result(result_val) {}

void AnswerHandler::print() const {
    std::cout << result << std::endl;
}