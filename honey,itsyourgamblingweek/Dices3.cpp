#include <random>
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <iomanip>

class RandomVariable {
public:
    virtual ~RandomVariable() = default;
    virtual unsigned roll() = 0;
};

class Dice : public RandomVariable {
public:
    Dice(unsigned max, unsigned seed = std::random_device{}()) :
        max(max), dstr(1, max), reng(seed) {}
    
    unsigned roll() override {
        return dstr(reng);
    }
    
    unsigned getMax() const { return max; }

private:
    unsigned max;
    std::uniform_int_distribution<unsigned> dstr;
    std::default_random_engine reng;
};

class ThreeDicePool : public RandomVariable {
public:
    ThreeDicePool(unsigned max, 
                  unsigned seed_1 = std::random_device{}(), 
                  unsigned seed_2 = std::random_device{}(), 
                  unsigned seed_3 = std::random_device{}()) :
        dice_1(std::make_unique<Dice>(max, seed_1)),
        dice_2(std::make_unique<Dice>(max, seed_2)),
        dice_3(std::make_unique<Dice>(max, seed_3)) {}
    
    unsigned roll() override {
        return dice_1->roll() + dice_2->roll() + dice_3->roll();
    }

private:
    std::unique_ptr<Dice> dice_1;
    std::unique_ptr<Dice> dice_2;
    std::unique_ptr<Dice> dice_3;
};

class PenaltyDice : public virtual RandomVariable {
public:
    PenaltyDice(std::unique_ptr<RandomVariable> dice) : dice(std::move(dice)) {}
    
    unsigned roll() override {
        unsigned first_roll = dice->roll();
        unsigned second_roll = dice->roll();
        return std::min(first_roll, second_roll);
    }

private:
    std::unique_ptr<RandomVariable> dice;
};

class BonusDice : public virtual RandomVariable {
public:
    BonusDice(std::unique_ptr<RandomVariable> dice) : dice(std::move(dice)) {}
    
    unsigned roll() override {
        unsigned first_roll = dice->roll();
        unsigned second_roll = dice->roll();
        return std::max(first_roll, second_roll);
    }

private:
    std::unique_ptr<RandomVariable> dice;
};

//С
class DoubleDice : public PenaltyDice, public BonusDice {
public:
    DoubleDice(Dice& dice) : 
        PenaltyDice(std::make_unique<Dice>(dice.getMax())),
        BonusDice(std::make_unique<Dice>(dice.getMax())) {}
    
    unsigned roll() override {
        unsigned penalty_roll = PenaltyDice::roll();
        unsigned bonus_roll = BonusDice::roll();
        return penalty_roll + bonus_roll;
    }
};

//Без
class DoubleDiceSimple : public RandomVariable {
public:
    DoubleDiceSimple(Dice& dice) : 
        dice_impl(std::make_unique<Dice>(dice.getMax())) {}
    
    unsigned roll() override {
        unsigned penalty_roll1 = dice_impl->roll();
        unsigned penalty_roll2 = dice_impl->roll();
        unsigned bonus_roll1 = dice_impl->roll();
        unsigned bonus_roll2 = dice_impl->roll();
        
        unsigned penalty_result = std::min(penalty_roll1, penalty_roll2);
        unsigned bonus_result = std::max(bonus_roll1, bonus_roll2);
        
        return penalty_result + bonus_result;
    }

private:
    std::unique_ptr<Dice> dice_impl;
};

double value_probability(unsigned value, RandomVariable &rv, unsigned number_of_rolls = 10000) {
    unsigned count = 0;
    for (unsigned i = 0; i < number_of_rolls; ++i) {
        if (rv.roll() == value) {
            ++count;
        }
    }
    return static_cast<double>(count) / static_cast<double>(number_of_rolls);
}

void print_histogram(RandomVariable &rv, unsigned min_value, unsigned max_value, unsigned number_of_rolls = 10000) {
    
    for (unsigned value = min_value; value <= max_value; value+=10) {
        double prob = value_probability(value, rv, number_of_rolls);
        std::cout << std::fixed << std::setprecision(4) << ": " << prob << " ";
        int bars = static_cast<int>(prob * 500);
        for (int i = 0; i < 2*bars; ++i) {
            std::cout << "█";
        }
        std::cout << " | " << value << std::endl;
    }
}

double expected_value(RandomVariable &rv, unsigned rolls = 10000) {
    double sum = 0;
    for (unsigned i = 0; i < rolls; ++i) {
        sum += rv.roll();
    }
    return sum / rolls;
}


int main() {
    const unsigned NUM_ROLLS = 50000;
    
    Dice base_dice(100);
    
    std::cout << "Вариант 1" << std::endl;
    DoubleDice double_dice_mi(base_dice);
    double exp_mi = expected_value(double_dice_mi, NUM_ROLLS);
    std::cout << "Мат ожидание: " << exp_mi << std::endl;
    print_histogram(double_dice_mi, 2, 200);
    
    std::cout << "Вариант 2" << std::endl;
    DoubleDiceSimple double_dice_simple(base_dice);
    double exp_simple = expected_value(double_dice_simple, NUM_ROLLS);
    std::cout << "Мат ожидание: " << exp_simple << std::endl;
    print_histogram(double_dice_simple, 2, 200);
    
    PenaltyDice penalty(std::make_unique<Dice>(100));
    BonusDice bonus(std::make_unique<Dice>(100));
    Dice regular(std::make_unique<Dice>(100)->getMax());
    
    
    std::cout << "Мат. ожидание обычного: " << expected_value(penalty, NUM_ROLLS) << std::endl;
    std::cout << "Мат. ожидание PenaltyDice: " << expected_value(bonus, NUM_ROLLS) << std::endl;
    std::cout << "Мат. ожидание BonusDice: " << expected_value(regular, NUM_ROLLS) << std::endl;
    std::cout << "Вариант 1 эксперементально: " << exp_mi << std::endl;
    std::cout << "Вариант 2 эксперементально: " << exp_simple << std::endl;
}