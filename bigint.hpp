#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>

class BigInt {
    std::string m_digits = "";

    static void sum(BigInt&, BigInt&), diff(BigInt&, BigInt&);

    bool null(const BigInt&) const;

public:
    BigInt();
    BigInt(const std::string&);
    BigInt(const BigInt&);
    BigInt& operator=(const BigInt&);

    ~BigInt() = default;

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
};

#endif
