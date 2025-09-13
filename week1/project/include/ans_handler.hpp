#pragma once

struct AnswerHandler {
    double x;
    double result;
    
    AnswerHandler(double x_val, double result_val);
    void print() const;
};