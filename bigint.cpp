#include <iostream>
#include <stdexcept>
#include <algorithm>

using std::cout;
using std::runtime_error;

#include "bigint.hpp"

BigInt::BigInt() : m_digits("0") {}

BigInt::BigInt(const string& digits) : m_digits("") {
    for (const auto& it : digits) {
        if (!isdigit(it)) {
            throw runtime_error("Entrada inválida!");
        }
    }
    this->m_digits = digits;
}

BigInt::BigInt(const BigInt& rhs) {
    this->m_digits = rhs.m_digits;
}

BigInt& BigInt::operator=(const BigInt& rhs) {
	this->m_digits = rhs.m_digits;

	return (* this);
}

ostream& operator<<(ostream& os, const BigInt& bigInt) {
	const int length = bigInt.m_digits.length();
	for (int i = length - 1; i >= 0; --i) {
		cout << static_cast<char>(bigInt.m_digits.at(i));
	}

	return cout;
}

bool operator==(const BigInt& lhs, const BigInt& rhs) {
    return lhs.m_digits == rhs.m_digits;
}

bool operator!=(const BigInt& lhs, const BigInt& rhs) {
    return !(lhs == rhs);
}

bool operator<(const BigInt& lhs, const BigInt& rhs) {
	int n = lhs.m_digits.length(), m = rhs.m_digits.length();

	if (n != m) {
		return n < m;
	}

	while (--n) {
		if (lhs.m_digits.at(n) != rhs.m_digits.at(n)) {
			return lhs.m_digits.at(n) < rhs.m_digits.at(n);
		}
	}

	return false;
}

bool operator>(const BigInt& lhs, const BigInt& rhs) {
    return rhs < lhs;
}

bool operator>=(const BigInt& lhs, const BigInt& rhs) {
    return !(lhs < rhs);
}

bool operator<=(const BigInt& lhs, const BigInt& rhs) {
    return !(lhs > rhs);
}

void operator+=(BigInt& lhs, BigInt& rhs) {
    BigInt::sum(lhs, rhs);
}

void operator-=(BigInt& lhs, BigInt& rhs) {
    BigInt::diff(lhs, rhs);
}

BigInt& operator+(BigInt& lhs, BigInt& rhs) {
    BigInt::sum(lhs, rhs);

    return lhs;
}

BigInt& operator-(BigInt& lhs, BigInt& rhs) {
    BigInt::diff(lhs, rhs);

    return lhs;
}

bool BigInt::null(const BigInt& rhs) const {
    if (rhs.m_digits.length() == 1 && rhs.m_digits.at(0) == 0) {
        return true;
    } else {
        return false;
    }
}

void BigInt::sum(BigInt& lhs, BigInt& rhs) {
    int m = lhs.m_digits.length(), n = rhs.m_digits.length(), carry = 0;

    if (m > n) {
        swap(lhs.m_digits, rhs.m_digits);
    }

    m = lhs.m_digits.length();
    n = rhs.m_digits.length();

    string result = "";

    for (int i = m - 1; i >= 0; --i) {
        int sum = ((lhs.m_digits.at(i) - '0') + (rhs.m_digits.at(i + n - m) - '0') + carry);

        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    for (int i = n - m - 1; i >= 0; --i) {
        int sum = ((rhs.m_digits.at(i) - '0') + carry);

        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    if (carry != 0) {
        result.push_back(carry + '0');
    }

    reverse(result.begin(), result.end());
    lhs.m_digits = result;
}

auto minimum = [](const string& lhs, const string& rhs) {
    int m = lhs.length(), n = rhs.length();

    if (m < n) {
        return true;
    } else {
        return false;
    }

    for (int i = 0; i < m; ++i) {
        if (lhs.at(i) < rhs.at(i)) {
            return true;
        } else if (lhs.at(i) > rhs.at(i)) {
            return false;
        }
    }

    return false;
};

void BigInt::diff(BigInt& lhs, BigInt& rhs) {
    int m = lhs.m_digits.length(), n = rhs.m_digits.length(), carry = 0;

    if (minimum(lhs.m_digits, rhs.m_digits)) {
        swap(lhs.m_digits, rhs.m_digits);
    }

    string result = "";

    for (int i = n - 1; i >= 0; --i) {
        int sub = ((lhs.m_digits.at(i + m - n) - '0') - (rhs.m_digits.at(i) - '0') - carry);

        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        } else {
            carry = 0;
        }

        result.push_back(sub + '0');
    }

    for (int i = m - n - 1; i >= 0; --i) {
        if (lhs.m_digits.at(i) == '0' && carry) {
            result.push_back('9');

            continue;
        }

        int sub = ((lhs.m_digits.at(i) - '0') - carry);

        if (i > 0 || sub > 0) {
            result.push_back(sub + '0');
        }

        carry = 0;
    }

    reverse(result.begin(), result.end());
    lhs.m_digits = result;
}
