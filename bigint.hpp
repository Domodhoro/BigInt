#ifndef bigint_HPP
#define bigint_HPP

#include <string>

namespace math {

struct bigint {
    bigint() : m_digits{"0"} {}

    bigint(const std::string &digits) : m_digits{""} {
        for (auto &it : digits) if (!isdigit(it)) my_exception {__FILE__, __LINE__, "Entrada inválida!"};

        this->m_digits = digits;
    }

    bigint(const bigint &rhs) { this->m_digits = rhs.m_digits; }

    bigint &operator=(const bigint &rhs) {
        this->m_digits = rhs.m_digits;

        return (*this);
    }

    ~bigint() = default;

    friend std::ostream &operator<<(std::ostream &os, const bigint &bigint) {
        for (const auto &it : bigint.m_digits) std::cout << static_cast<char>(it);

        return std::cout;
    }

    friend bool operator==(const bigint &lhs, const bigint &rhs) { return lhs.m_digits == rhs.m_digits; }
    friend bool operator!=(const bigint &lhs, const bigint &rhs) { return !(lhs == rhs); }

    friend bool operator<(const bigint &lhs, const bigint &rhs) {
        int n {lhs.m_digits.length()};
        int m {rhs.m_digits.length()};

        if (n != m) return n < m;

        while (--n) {
            if (lhs.m_digits.at(n) != rhs.m_digits.at(n)) return lhs.m_digits.at(n) < rhs.m_digits.at(n);
        }

        return false;
    }

    friend bool operator> (const bigint &lhs, const bigint &rhs) { return rhs < lhs; }
    friend bool operator>=(const bigint &lhs, const bigint &rhs) { return !(lhs < rhs); }
    friend bool operator<=(const bigint &lhs, const bigint &rhs) { return !(lhs > rhs); }
    friend void operator+=(bigint &lhs, bigint &rhs)             { bigint::sum(lhs, rhs); }
    friend void operator-=(bigint &lhs, bigint &rhs)             { bigint::diff(lhs, rhs); }

    friend bigint &operator+(bigint &lhs, bigint &rhs) {
        bigint::sum(lhs, rhs);

        return lhs;
    }

    friend bigint &operator-(bigint &lhs, bigint &rhs) {
        bigint::diff(lhs, rhs);

        return lhs;
    }

private:
    std::string m_digits {""};

    static bool null(const bigint &rhs);
    static void sum (bigint &lhs, bigint &rhs);
    static void diff(bigint &lhs, bigint &rhs);
};

bool bigint::null(const bigint &rhs) {
    if (rhs.m_digits.length() == 1 && rhs.m_digits.at(0) == 0) return true;
    else                                                       return false;
}

void bigint::sum(bigint &lhs, bigint &rhs) {
    int m     {lhs.m_digits.length()};
    int n     {rhs.m_digits.length()};
    int carry {0};

    if (m > n) std::swap(lhs.m_digits, rhs.m_digits);

    m = lhs.m_digits.length();
    n = rhs.m_digits.length();

    std::string result {""};

    for (int i = m - 1; i >= 0; --i) {
        int sum {
            ((lhs.m_digits.at(i) - '0') + (rhs.m_digits.at(i + n - m) - '0') + carry)
        };

        result.push_back(sum % 10 + '0');

        carry = sum / 10;
    }

    for (int i = n - m - 1; i >= 0; --i) {
        int sum {((rhs.m_digits.at(i) - '0') + carry)};

        result.push_back(sum % 10 + '0');

        carry = sum / 10;
    }

    if (carry != 0) result.push_back(carry + '0');

    std::reverse(result.begin(), result.end());

    lhs.m_digits = result;
}

static auto minimum = [](const std::string &lhs, const std::string &rhs) -> bool {
    auto m {lhs.length()};
    auto n {rhs.length()};

    if (m < n) return true;
    else       return false;

    for (int i = 0; i < m; ++i) {
        if      (lhs.at(i) < rhs.at(i)) return true;
        else if (lhs.at(i) > rhs.at(i)) return false;
    }

    return false;
};

void bigint::diff(bigint &lhs, bigint &rhs) {
    int m     {lhs.m_digits.length()};
    int n     {rhs.m_digits.length()};
    int carry {0};

    if (minimum(lhs.m_digits, rhs.m_digits)) std::swap(lhs.m_digits, rhs.m_digits);

    std::string result {""};

    for (int i = n - 1; i >= 0; --i) {
        int sub {((lhs.m_digits.at(i + m - n) - '0') - (rhs.m_digits.at(i) - '0') - carry)};

        if (sub < 0) {
            sub   += 10;
            carry  = 1;
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

        int sub {((lhs.m_digits.at(i) - '0') - carry)};

        if (i > 0 || sub > 0) result.push_back(sub + '0');

        carry = 0;
    }

    std::reverse(result.begin(), result.end());

    lhs.m_digits = result;
}

}

#endif
