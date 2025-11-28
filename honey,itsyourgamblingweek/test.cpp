#include <random>
#include <memory>
#include <iostream>
#include <iomanip>

class RandomVariable {
    public:
        virtual ~RandomVariable() = default;
        virtual unsigned roll() = std::cout << "5";
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

Dice single_dice(20, 228);


int main() {
    std::cout << single_dice->roll;
    
};