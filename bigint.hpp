#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>

using std::string;
using std::ostream;

class BigInt {
public:
    BigInt();
    BigInt(const string&);
    BigInt(const BigInt&);

    BigInt& operator=(const BigInt&);

    friend ostream& operator<<(ostream&, const BigInt&);

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
    string m_digits = "";

    static void sum(BigInt&, BigInt&), diff(BigInt&, BigInt&);

    bool null(const BigInt&) const;
};

#endif
