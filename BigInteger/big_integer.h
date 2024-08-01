#ifndef BIG_INTEGER_H_
#define BIG_INTEGER_H_

#define BIG_INTEGER_DIVISION_IMPLEMENTED

#include <cstdint>
#include <string>
#include <stdexcept>
#include <vector>

class BigIntegerOverflow : public std::runtime_error {
 public:
  BigIntegerOverflow() : std::runtime_error("BigIntegerOverflow") {
  }
};

class BigIntegerDivisionByZero : public std::runtime_error {
 public:
  BigIntegerDivisionByZero() : std::runtime_error("BigIntegerDivisionByZero") {
  }
};

class BigInteger {
 private:
  std::vector<int> digits_;
  bool is_negative_;
  static const int64_t kDivider = 1000;
  static const int64_t kDigitWidth = 3;
  static const int64_t kMaxDigits = 30000;

  void RemoveLeadingZeros();
  void FromString(const std::string &);
  bool IsZero() const;
  BigInteger Pow(const BigInteger &);

 public:
  BigInteger();
  explicit BigInteger(int);
  BigInteger(int64_t);       // NOLINT
  explicit BigInteger(const char *);

  bool IsNegative();
  friend BigInteger Abs(const BigInteger &n);

  BigInteger operator+() const;
  BigInteger operator-() const;

  friend BigInteger operator+(const BigInteger &, const BigInteger &);
  friend BigInteger operator-(const BigInteger &, const BigInteger &);
  friend BigInteger operator*(const BigInteger &, const BigInteger &);

  friend BigInteger &operator+=(BigInteger &, const BigInteger &);
  friend BigInteger &operator-=(BigInteger &, const BigInteger &);
  friend BigInteger &operator*=(BigInteger &, const BigInteger &);

  friend BigInteger operator+(BigInteger &, int);
  friend BigInteger operator-(BigInteger &, int);
  friend BigInteger operator*(BigInteger &, int);

  friend BigInteger &operator+=(BigInteger &, int);
  friend BigInteger &operator-=(BigInteger &, int);
  friend BigInteger &operator*=(BigInteger &, int);

  friend BigInteger operator+(int, BigInteger &);
  friend BigInteger operator-(int, BigInteger &);
  friend BigInteger operator*(int, BigInteger &);

  friend BigInteger &operator+=(int, BigInteger &);
  friend BigInteger &operator-=(int, BigInteger &);
  friend BigInteger &operator*=(int, BigInteger &);

  friend BigInteger operator/(const BigInteger &, const BigInteger &);
  friend BigInteger operator%(const BigInteger &, const BigInteger &);
  friend BigInteger &operator/=(BigInteger &, const BigInteger &);
  friend BigInteger &operator%=(BigInteger &, const BigInteger &);

  BigInteger &operator++();
  BigInteger operator++(int);
  BigInteger &operator--();
  BigInteger operator--(int);

  explicit operator bool() const;
  bool operator==(const BigInteger &) const;
  bool operator!=(const BigInteger &) const;
  bool operator<(const BigInteger &) const;
  bool operator>(const BigInteger &) const;
  bool operator<=(const BigInteger &) const;
  bool operator>=(const BigInteger &) const;

  friend std::istream &operator>>(std::istream &, BigInteger &);
  friend std::ostream &operator<<(std::ostream &, const BigInteger &);
};

#endif