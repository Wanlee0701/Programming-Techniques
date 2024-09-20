#ifndef BIGINT_H
#define BIGINT_H

#include <vector>
#include <iostream>
#include <iomanip>

class bigint {
private:
    std::vector<int> a;
    int sign;
    static const int base = 1000000000;
    static const int base_digits = 9;

    void trim();
    void read(const std::string &s);
    static std::vector<int> convert_base(const std::vector<int> &a, int old_digits, int new_digits);
    static std::vector<long long> karatsubaMultiply(const std::vector<long long> &a, const std::vector<long long> &b);

public:
    bigint();
    bigint(long long v);
    bigint(const std::string &s);

    void operator=(const bigint &v);
    void operator=(long long v);

    bigint operator+(const bigint &v) const;
    bigint operator-(const bigint &v) const;
    void operator*=(int v);
    bigint operator*(int v) const;
    bigint operator*(const bigint &v) const;

    friend std::pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1);

    bigint operator/(const bigint &v) const;
    bigint operator%(const bigint &v) const;
    void operator/=(int v);
    bigint operator/(int v) const;
    int operator%(int v) const;

    void operator+=(const bigint &v);
    void operator-=(const bigint &v);
    void operator*=(const bigint &v);
    void operator/=(const bigint &v);

    bool operator<(const bigint &v) const;
    bool operator>(const bigint &v) const;
    bool operator<=(const bigint &v) const;
    bool operator>=(const bigint &v) const;
    bool operator==(const bigint &v) const;
    bool operator!=(const bigint &v) const;

    bool isZero() const;
    bigint operator-() const;
    bigint abs() const;
    long long longValue() const;

    friend bigint gcd(const bigint &a, const bigint &b);
    friend bigint lcm(const bigint &a, const bigint &b);

    friend std::istream& operator>>(std::istream &stream, bigint &v);
    friend std::ostream& operator<<(std::ostream &stream, const bigint &v);
};

#endif // BIGINT_H

