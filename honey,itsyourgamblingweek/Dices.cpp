#include <random>
#include <memory>
#include <iostream>
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
double expected_value(RandomVariable& rv, unsigned number_of_rolls = 1000) {
    auto accum = 0llu;
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
        accum += rv.roll();
    return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
};

struct Base {
 virtual ~Base() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
 }
};

struct Base2 : Base {
    ~Base2() {
       std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
   };

int main() {
    Base* b = new Base2();
    delete b;
    // const unsigned NUM_ROLLS = 10000;
    
    // Dice single_dice(20, 228);
    // double dice_expected = expected_value(single_dice, NUM_ROLLS);
    // double theoretical_dice = (1.0 + 20.0) / 2.0;
    
    // std::cout << "один" << std::endl;
    // std::cout << "Теория " << theoretical_dice << std::endl;
    // std::cout << "Практика " << dice_expected << std::endl;
    // std::cout << "На сколько нужно подгонять " << std::abs(dice_expected - theoretical_dice) << std::endl;
    
    // ThreeDicePool three_dice(20, 3, 3, 7);
    // double three_dice_expected = expected_value(three_dice, NUM_ROLLS);
    // double theoretical_three_dice = 3 * (1.0 + 20.0) / 2.0;
    
    // std::cout << "\nтри" << std::endl;
    // std::cout << "Теория " << theoretical_three_dice << std::endl;
    // std::cout << "Практика " << three_dice_expected << std::endl;
    // std::cout << "На сколько нужно подгонять " << std::abs(three_dice_expected - theoretical_three_dice) << std::endl;
    
}
