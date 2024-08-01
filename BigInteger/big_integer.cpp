#include "big_integer.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

void BigInteger::RemoveLeadingZeros() {
  while (digits_.size() > 1 && digits_.back() == 0) {
    digits_.pop_back();
  }
}

void BigInteger::FromString(const std::string &str) {
  digits_.clear();
  digits_.reserve(str.size());
  is_negative_ = (str[0] == '-');
  std::string absolute_str = str;
  if (-is_negative_ || str[0] == '+') {
    absolute_str = str.substr(1, str.size());
  }
  for (size_t i = absolute_str.size() - 1; i < str.size(); i -= kDigitWidth) {
    size_t end = i + 1;
    size_t begin = i < kDigitWidth ? 0 : i - kDigitWidth + 1;
    digits_.push_back(std::stoi(absolute_str.substr(begin, end - begin)));
  }
  RemoveLeadingZeros();
  if (digits_.size() * kDigitWidth > kMaxDigits) {
    throw BigIntegerOverflow();
  }
}

bool BigInteger::IsZero() const {
  return digits_.size() == 1 && digits_.front() == 0;
}

BigInteger BigInteger::Pow(const BigInteger &power) {
  if (power.IsZero()) {
    return 1;
  }
  BigInteger result = *this;
  for (BigInteger i = 2; i <= power; ++i) {
    result *= *this;
  }
  return result;
}

BigInteger::BigInteger() : is_negative_(false) {
  digits_.push_back(0);
}

BigInteger::BigInteger(int value) : BigInteger(static_cast<int64_t>(value)) {
}

BigInteger::BigInteger(int64_t value) : is_negative_(value < 0) {
  value = std::abs(value);
  while (value > 0) {
    digits_.push_back(static_cast<int>(value % kDivider));
    value /= kDivider;
  }
  if (digits_.empty()) {
    digits_.push_back(0);
  }
  if (digits_.size() * kDigitWidth > kMaxDigits) {
    throw BigIntegerOverflow();
  }
}

BigInteger::BigInteger(const char *str) {
  FromString(std::string(str));
}

bool BigInteger::IsNegative() {
  return is_negative_;
}

BigInteger Abs(const BigInteger &n) {
  BigInteger absolute = n;
  absolute.is_negative_ = false;
  return absolute;
}

BigInteger BigInteger::operator+() const {
  return *this;
}

BigInteger BigInteger::operator-() const {
  BigInteger result = *this;
  result.is_negative_ = !is_negative_;
  return result;
}

BigInteger operator+(const BigInteger &l, const BigInteger &r) {
  BigInteger result;
  result.digits_ = std::vector<int>(l.digits_.size() + r.digits_.size() + 1, 0);
  size_t size = std::max(l.digits_.size(), r.digits_.size());
  int carry = 0;
  if (l.is_negative_ == r.is_negative_) {
    result.is_negative_ = l.is_negative_;
    for (size_t i = 0; i < size || carry != 0; ++i) {
      int l_digit = i < l.digits_.size() ? l.digits_[i] : 0;
      int r_digit = i < r.digits_.size() ? r.digits_[i] : 0;
      int part_sum = l_digit + r_digit + carry;
      if (part_sum >= BigInteger::kDivider) {
        part_sum -= BigInteger::kDivider;
        carry = 1;
      } else {
        carry = 0;
      }
      result.digits_[i] = part_sum;
    }
    result.RemoveLeadingZeros();
    if (result.IsZero()) {
      result.is_negative_ = false;
    }
    return result;
  }
  BigInteger r_abs = Abs(r);
  BigInteger l_abs = Abs(l);
  result.is_negative_ = l.is_negative_ ? r < l_abs : l < r_abs;
  for (size_t i = 0; i < size || carry != 0; ++i) {
    int l_digit = i < l.digits_.size() ? l.digits_[i] : 0;
    int r_digit = i < r.digits_.size() ? r.digits_[i] : 0;
    int part_sum = 0;
    if (Abs(r) >= Abs(l)) {
      part_sum = r_digit - l_digit - carry;
    } else {
      part_sum = l_digit - r_digit - carry;
    }
    if (part_sum < 0) {
      part_sum += BigInteger::kDivider;
      carry = 1;
    } else {
      carry = 0;
    }
    result.digits_[i] = part_sum;
  }
  result.RemoveLeadingZeros();
  if (result.IsZero()) {
    result.is_negative_ = false;
  }
  return result;
}

BigInteger operator-(const BigInteger &l, const BigInteger &r) {
  BigInteger result = l + (-r);
  return result;
}

BigInteger operator*(const BigInteger &l, const BigInteger &r) {
  BigInteger result;
  result.digits_ = std::vector<int>(l.digits_.size() + r.digits_.size() + 1, 0);
  result.is_negative_ = l.is_negative_ ? !r.is_negative_ : r.is_negative_;
  int carry = 0;
  for (size_t i = 0; i < l.digits_.size() || carry != 0; ++i) {
    int l_digit = i < l.digits_.size() ? l.digits_[i] : 0;
    for (size_t j = 0; j < r.digits_.size() || carry != 0; ++j) {
      int r_digit = j < r.digits_.size() ? r.digits_[j] : 0;
      int part_mult = l_digit * r_digit + carry;
      result.digits_[j + i] += part_mult;
      if (result.digits_[j + i] >= BigInteger::kDivider) {
        carry = result.digits_[j + i] / static_cast<int>(BigInteger::kDivider);
        result.digits_[j + i] %= static_cast<int>(BigInteger::kDivider);
      } else {
        carry = 0;
      }
    }
  }
  result.RemoveLeadingZeros();
  if (result.IsZero()) {
    result.is_negative_ = false;
  }
  return result;
}

BigInteger &operator+=(BigInteger &l, const BigInteger &r) {
  l = l + r;
  return l;
}

BigInteger &operator-=(BigInteger &l, const BigInteger &r) {
  l = l - r;
  return l;
}

BigInteger &operator*=(BigInteger &l, const BigInteger &r) {
  l = l * r;
  return l;
}

BigInteger operator+(const BigInteger &l, int r) {
  return l + BigInteger(r);
}

BigInteger operator-(const BigInteger &l, int r) {
  return l - BigInteger(r);
}

BigInteger operator*(const BigInteger &l, int r) {
  return l * BigInteger(r);
}

BigInteger operator+(int r, const BigInteger &l) {
  return BigInteger(r) + l;
}

BigInteger operator-(int r, const BigInteger &l) {
  return BigInteger(r) - l;
}

BigInteger operator*(int r, const BigInteger &l) {
  return BigInteger(r) * l;
}

BigInteger &operator+=(BigInteger &l, int r) {
  return l += BigInteger(r);
}

BigInteger &operator-=(BigInteger &l, int r) {
  return l -= BigInteger(r);
}

BigInteger &operator*=(BigInteger &l, int r) {
  return l *= BigInteger(r);
}

BigInteger &operator+=(int l, BigInteger &r) {
  return r += BigInteger(l);
}

BigInteger &operator-=(int l, BigInteger &r) {
  return r -= BigInteger(l);
}

BigInteger &operator*=(int l, BigInteger &r) {
  return r *= BigInteger(l);
}

BigInteger operator/(const BigInteger &l, const BigInteger &r) {
  if (r.IsZero()) {
    throw BigIntegerDivisionByZero();
  }

  BigInteger dividend = Abs(l);
  BigInteger divisor = Abs(r);
  BigInteger result;
  result.digits_.resize(dividend.digits_.size(), 0);

  BigInteger current;
  current.digits_.clear();

  for (size_t i = dividend.digits_.size() - 1; i < dividend.digits_.size(); --i) {
    current.digits_.insert(current.digits_.begin(), dividend.digits_[i]);
    current.RemoveLeadingZeros();

    int x = 0;
    int left = 0;
    int right = static_cast<int>(BigInteger::kDivider);
    while (left <= right) {
      int mid = (left + right) / 2;
      BigInteger mid_value = divisor * BigInteger(mid);
      if (mid_value <= current) {
        x = mid;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    result.digits_[i] = x;
    current = current - (divisor * BigInteger(x));
  }

  result.is_negative_ = l.is_negative_ != r.is_negative_;
  result.RemoveLeadingZeros();
  if (result.IsZero()) {
    result.is_negative_ = false;
  }

  return result;
}

BigInteger operator%(const BigInteger &l, const BigInteger &r) {
  BigInteger result = l - (l / r) * r;
  return result;
}

BigInteger &operator/=(BigInteger &l, const BigInteger &r) {
  return l = l / r;
}

BigInteger &operator%=(BigInteger &l, const BigInteger &r) {
  return l = l % r;
}

BigInteger &BigInteger::operator++() {
  *this += 1;
  return *this;
}

BigInteger BigInteger::operator++(int) {
  BigInteger temp = *this;
  ++(*this);
  return temp;
}

BigInteger &BigInteger::operator--() {
  *this -= 1;
  return *this;
}

BigInteger BigInteger::operator--(int) {
  BigInteger temp = *this;
  --(*this);
  return temp;
}

BigInteger::operator bool() const {
  return digits_.size() != 1 || digits_[0] != 0;
}

bool BigInteger::operator==(const BigInteger &other) const {
  return is_negative_ == other.is_negative_ && digits_ == other.digits_;
}

bool BigInteger::operator!=(const BigInteger &other) const {
  return !(*this == other);
}

bool BigInteger::operator<(const BigInteger &other) const {
  if (is_negative_ != other.is_negative_) {
    return is_negative_;
  }
  if (digits_.size() != other.digits_.size()) {
    return digits_.size() < other.digits_.size();
  }
  for (size_t i = digits_.size() - 1; i < digits_.size(); --i) {
    if (digits_[i] != other.digits_[i]) {
      return digits_[i] < other.digits_[i];
    }
  }
  return false;
}

bool BigInteger::operator<=(const BigInteger &other) const {
  return *this < other || *this == other;
}

bool BigInteger::operator>(const BigInteger &other) const {
  return !(*this <= other);
}

bool BigInteger::operator>=(const BigInteger &other) const {
  return !(*this < other);
}

std::istream &operator>>(std::istream &is, BigInteger &big_integer) {
  std::string input;
  is >> input;
  big_integer.FromString(input);
  return is;
}

std::ostream &operator<<(std::ostream &os, const BigInteger &big_integer) {
  if (big_integer.is_negative_) {
    os << '-';
  }
  for (size_t i = big_integer.digits_.size() - 1; i < big_integer.digits_.size(); --i) {
    if (big_integer.digits_[i] < 100 && i != big_integer.digits_.size() - 1) {
      if (big_integer.digits_[i] < 10) {
        os << "00" << big_integer.digits_[i];
      } else {
        os << "0" << big_integer.digits_[i];
      }
    } else {
      os << big_integer.digits_[i];
    }
  }
  return os;
}