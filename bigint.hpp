#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>

namespace Math {

class BigInt {
public:
    BigInt();
    BigInt(const std::string&);

    BigInt(const BigInt&);
    BigInt& operator=(const BigInt&);

    virtual ~BigInt() = default;

    friend std::ostream& operator<<(std::ostream&, const BigInt&);

    friend bool operator==(const BigInt&, const BigInt&);
    friend bool operator!=(const BigInt&, const BigInt&);

    friend bool operator<(const BigInt&, const BigInt&);
    friend bool operator>(const BigInt&, const BigInt&);

    friend bool operator>=(const BigInt&, const BigInt&);
    friend bool operator<=(const BigInt&, const BigInt&);

    friend void operator+=(BigInt&, BigInt&);
    friend void operator-=(BigInt&, BigInt&);

    friend BigInt& operator+(BigInt&, BigInt&);
    friend BigInt& operator-(BigInt&, BigInt&);

private:
    std::string m_digits {""};

    static void sum(BigInt&, BigInt&);
    static void diff(BigInt&, BigInt&);
    static bool null(const BigInt&);
};

}

#endif
