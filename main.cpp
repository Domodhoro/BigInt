#include <iostream>
#include <algorithm>

class BigInt {
    std::string m_digits = "";

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

	BigInt& operator++();
	BigInt& operator--();

    friend void operator+=(BigInt&, BigInt&);
    friend void operator-=(BigInt&, BigInt&);

    friend BigInt& operator+(BigInt&, BigInt&);
    friend BigInt& operator-(BigInt&, BigInt&);

    bool null(const BigInt&) const;

protected:
    static void sum(BigInt&, BigInt&), diff(BigInt&, BigInt&);

    friend bool minimum(const BigInt&, const BigInt&);
};

BigInt::BigInt() : m_digits("0") {}

BigInt::BigInt(const std::string& digits) : m_digits("") {
    for (const auto& it : digits) {
        if (!isdigit(it)) {
            throw std::runtime_error("Entrada inválida!");
        }
    }
    this->m_digits = digits;
}

BigInt::BigInt(const BigInt& rhs) {
    this->m_digits = rhs.m_digits;
}

BigInt& BigInt::operator=(const BigInt& rhs) {
	this->m_digits = rhs.m_digits;
	return * this;
}

std::ostream& operator<<(std::ostream& output, const BigInt& bigint) {
	for (int i = bigint.m_digits.length() - 1; i >= 0; --i) {
		std::cout << static_cast<char>(bigint.m_digits.at(i));
	}
	return std::cout;
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

BigInt& BigInt::operator++() {
    int i = 0, n = m_digits.length();

    for (i = 0; i < n && m_digits.at(i) == 9; ++i) {
        m_digits.at(i) = 0;
    }

    if (i == n) {
        m_digits.push_back(1);
    } else {
        m_digits.at(i)++;
    }
    return * this;
}

BigInt& BigInt::operator--() {
    int i = 0, n = m_digits.length();

    if(m_digits.at(0) == 0 && m_digits.length() == 1) {
        throw std::runtime_error("Operação impossível!");
    }

    for (i = 0; m_digits.at(i) == 0 && i < n; ++i) {
        m_digits.at(i) = 9;
    }

    m_digits.at(i)--;

    if (n > 1 && m_digits.at(n - 1) == 0) {
        m_digits.pop_back();
    }
    return * this;
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
        std::swap(lhs.m_digits, rhs.m_digits);
    }

    m = lhs.m_digits.length();
    n = rhs.m_digits.length();

    std::string result = "";

    for (int i = m - 1; i >= 0; --i) {
        int sum = ((lhs.m_digits.at(i)-'0') + (rhs.m_digits.at(i + n - m) - '0') + carry);

        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    for (int i = n - m - 1; i >= 0; --i) {
        int sum = ((rhs.m_digits.at(i) - '0') + carry);

        result.push_back(sum%10 + '0');
        carry = sum / 10;
    }

    if (carry != 0) {
        result.push_back(carry + '0');
    }

    std::reverse(result.begin(), result.end());
    lhs.m_digits = result;
}

bool minimum(const BigInt& lhs, const BigInt& rhs) {
    int m = lhs.m_digits.length(), n = rhs.m_digits.length();

    if (m < n) {
        return true;
    } else {
        return false;
    }

    for (int i = 0; i < m; ++i) {
        if (lhs.m_digits.at(i) < rhs.m_digits.at(i)) {
            return true;
        } else if (lhs.m_digits.at(i) > rhs.m_digits.at(i)) {
            return false;
        }
    }
    return false;
}

void BigInt::diff(BigInt& lhs, BigInt& rhs) {
    int m = lhs.m_digits.length(), n = rhs.m_digits.length(), carry = 0;

    if (minimum(lhs, rhs)) {
        std::swap(lhs.m_digits, rhs.m_digits);
    }

    std::string result = "";

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

    std::reverse(result.begin(), result.end());
    lhs.m_digits = result;
}

int main() {
	try {
        BigInt x("100000000000000000000000000000000000000000000000000000000"), y("1");

        x += y;

        std::cout << "x + y = " << x << "\n";
        std::cin.get();
        return 0;
	} catch (const std::exception& e) {
        std::cerr << e.what();
        std::cin.get();
        return 1;
	}
}
