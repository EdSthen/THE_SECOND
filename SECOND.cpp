class Rational final {

    public:
    Rational(int numerator = 0, int denominator = 1): o_num(numerator), o_den(denominator) { norm; };
    Rational(const Rational& other): o_num(other.numerator), o_den(other.denominator) { };
    Rational& operator=(const Rational& other){
        if (this != &other) {
            o_num = other.o_num;
            o_den = other.o_den;
        }
        return *this;
    }
    explicit operator double() const {
        return toDouble();
    }
    double toDouble() const {
        return static_cast<double>(o_num) / o_den;
    }

        double toDouble() const;
    private:
        int o_num;
        int o_den;
    
    void norm(){
        int g = std::gcd(o_num, o_den);
            o_num /= g;
            o_den /= g;
        }
    };