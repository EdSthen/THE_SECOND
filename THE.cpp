#include <iostream>
#include <numeric>

class Rational final {
public:
    Rational(int numerator = 0, int denominator = 1) 
        : m_numerator(numerator), m_denominator(denominator) {
        normalize();
    }

    Rational(const Rational& other) 
        : m_numerator(other.m_numerator), m_denominator(other.m_denominator) {}

    Rational& operator=(const Rational& other) {
        if (this != &other) {
            m_numerator = other.m_numerator;
            m_denominator = other.m_denominator;
        }
        return *this;
    }

    explicit operator double() const {
        return toDouble();
    }

    double toDouble() const {
        return static_cast<double>(m_numerator) / m_denominator;
    }

    Rational& operator+=(const Rational& rhs) {
        m_numerator = m_numerator * rhs.m_denominator + rhs.m_numerator * m_denominator;
        m_denominator *= rhs.m_denominator;
        normalize();
        return *this;
    }
    Rational& operator-=(const Rational& rhs) {
        m_numerator = m_numerator * rhs.m_denominator - rhs.m_numerator * m_denominator;
        m_denominator *= rhs.m_denominator;
        normalize();
        return *this;
    }
    Rational& operator*=(const Rational& rhs) {
        m_numerator *= rhs.m_numerator;
        m_denominator *= rhs.m_denominator;
        normalize();
        return *this;
    }
    Rational& operator/=(const Rational& rhs) {
        m_numerator *= rhs.m_denominator;
        m_denominator *= rhs.m_numerator;
        normalize();
        return *this;
    }

    Rational& operator+=(int value) { return *this += Rational(value); }
    Rational& operator-=(int value) { return *this -= Rational(value); }
    Rational& operator*=(int value) { return *this *= Rational(value); }
    Rational& operator/=(int value) { return *this /= Rational(value); }

    Rational operator+() const { return *this; }
    Rational operator-() const { return Rational(-m_numerator, m_denominator); }

    friend Rational operator+(Rational lhs, const Rational& rhs) { return lhs += rhs; }
    friend Rational operator-(Rational lhs, const Rational& rhs) { return lhs -= rhs; }
    friend Rational operator*(Rational lhs, const Rational& rhs) { return lhs *= rhs; }
    friend Rational operator/(Rational lhs, const Rational& rhs) { return lhs /= rhs; }

    friend bool operator<(const Rational& a, const Rational& b) {
        return a.m_numerator * b.m_denominator < b.m_numerator * a.m_denominator;
    }
    friend bool operator>(const Rational& a, const Rational& b) { return b < a; }
    friend bool operator<=(const Rational& a, const Rational& b) { return !(b < a); }
    friend bool operator>=(const Rational& a, const Rational& b) { return !(a < b); }
    friend bool operator==(const Rational& a, const Rational& b) {
        return a.m_numerator == b.m_numerator && a.m_denominator == b.m_denominator;
    }
    friend bool operator!=(const Rational& a, const Rational& b) { return !(a == b); }

private:
    int m_numerator;
    int m_denominator;

    void normalize() {
        if (m_denominator < 0) {
            m_numerator = -m_numerator;
            m_denominator = -m_denominator;
        }
        int g = std::gcd(m_numerator, m_denominator);
        m_numerator /= g;
        m_denominator /= g;
    }
};

int main() {
    Rational a(1, 2), b(3, 4);
    Rational c = a + b;
    std::cout << c.toDouble() << "\n"; 
}
