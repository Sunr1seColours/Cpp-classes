#ifndef MATRIX_H_
#define MATRIX_H_
#define MATRIX_SQUARE_MATRIX_IMPLEMENTED

#include <stddef.h>
#include <stdexcept>

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template<class Number, size_t N, size_t M>
class Matrix {
  public:
  Number matrix[N][M];

  size_t RowsNumber() const {
    return N;
  }

  size_t ColumnsNumber() const {
    return M;
  }

  Number &operator()(size_t i, size_t j) {
    return matrix[i][j];
  }

  const Number &operator()(size_t i, size_t j) const {
    return matrix[i][j];
  }

  Number &At(size_t i, size_t j) {
    if (i < N && j < M) {
      return matrix[i][j];
    }
    throw MatrixOutOfRange();
  }

  const Number &At(size_t i, size_t j) const {
    if (i < N && j < M) {
      return matrix[i][j];
    }
    throw MatrixOutOfRange();
  }

  friend Matrix<Number, N, M> operator+(const Matrix<Number, N, M> &left, const Matrix<Number, N, M> &right) {
    Matrix<Number, N, M> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        result(i, j) = left(i, j) + right(i, j);
      }
    }
    return result;
  }

  friend Matrix<Number, N, M> operator-(const Matrix<Number, N, M> &left, const Matrix<Number, N, M> &right) {
    Matrix<Number, N, M> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        result(i, j) = left(i, j) - right(i, j);
      }
    }
    return result;
  }

  friend Matrix<Number, N, M> &operator+=(Matrix<Number, N, M> &left, const Matrix<Number, N, M> &right) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        left(i, j) += right(i, j);
      }
    }
    return left;
  }

  friend Matrix<Number, N, M> &operator-=(Matrix<Number, N, M> &left, const Matrix<Number, N, M> &right) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        left(i, j) -= right(i, j);
      }
    }
    return left;
  }

  template<size_t K>
  friend Matrix<Number, N, K> operator*(const Matrix<Number, N, M> &left, const Matrix<Number, M, K> &right) {
    Matrix<Number, N, K> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < K; ++j) {
        result(i, j) = Number();
        for (size_t k = 0; k < M; ++k) {
          result(i, j) += left(i, k) * right(k, j);
        }
      }
    }
    return result;
  }

  template<size_t K>
  friend Matrix<Number, N, K> &operator*=(Matrix<Number, N, M> &left, const Matrix<Number, M, K> &right) {
    Matrix<Number, N, K> result = left * right;
    left = result;
    return left;
  }

  friend Matrix<Number, N, M> &operator*=(Matrix<Number, N, M> &matrix, const int n) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix(i, j) *= n;
      }
    }
    return matrix;
  }

  friend Matrix<Number, N, M> &operator*=(const int n, Matrix<Number, N, M> &matrix) {
    return matrix *= n;
  }

  friend Matrix<Number, N, M> operator*(const Matrix<Number, N, M> &matrix, const int n) {
    Matrix<Number, N, M> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        result(i, j) = matrix(i, j) * n;
      }
    }
    return result;
  }

  friend Matrix<Number, N, M> operator*(const int n, const Matrix<Number, N, M> &matrix) {
    return matrix * n;
  }

  friend Matrix<Number, N, M> operator/(const Matrix<Number, N, M> &matrix, const int n) {
    Matrix<Number, N, M> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        result(i, j) = matrix(i, j) / n;
      }
    }
    return result;
  }

  friend Matrix<Number, N, M> operator/(const int n, const Matrix<Number, N, M> &matrix) {
    return matrix / n;
  }

  friend Matrix<Number, N, M> &operator/=(Matrix<Number, N, M> &matrix, const int n) {
    matrix = matrix / n;
    return matrix;
  }

  friend Matrix<Number, N, M> &operator/=(const int n, Matrix<Number, N, M> &matrix) {
    return matrix /= n;
  }

  friend bool operator==(const Matrix<Number, N, M> &left, const Matrix<Number, N, M> &right) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        if (left(i, j) != right(i, j)) {
          return false;
        }
      }
    }
    return true;
  }

  friend bool operator!=(const Matrix<Number, N, M> &left, const Matrix<Number, N, M> &right) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        if (left(i, j) != right(i, j)) {
          return true;
        }
      }
    }
    return false;
  }

  friend std::istream &operator>>(std::istream &is, Matrix<Number, N, M> &matrix) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        is >> matrix(i, j);
      }
    }
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, const Matrix<Number, N, M> &matrix) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        if (j != M - 1) {
          os << matrix(i, j) << ' ';
        } else {
          os << matrix(i, j);
        }
      }
      os << '\n';
    }
    return os;
  }
};

template<class Number, size_t N, size_t M>
Matrix<Number, M, N> GetTransposed(const Matrix<Number, N, M> &matrix) {
  Matrix<Number, M, N> transposed;
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      transposed(i, j) = matrix(j, i);
    }
  }
  return transposed;
}

template<class Number, size_t N, size_t M>
Matrix<Number, N, M> &Transpose(Matrix<Number, N, M> &matrix) {
  matrix = GetTransposed(matrix);
  return matrix;
}

template<class Number, size_t N>
Number Trace(Matrix<Number, N, N> &matrix) {
  Number trace = Number();
  for (size_t i = 0; i < N; ++i) {
    trace += matrix(i, i);
  }
  return trace;
}

template<class Number, size_t N>
Matrix<Number, N - 1, N - 1> GetAlgebraicAddition(const Matrix<Number, N, N> &matrix, size_t row, size_t column) {
  Matrix<Number, N - 1, N - 1> addition;
  size_t addition_row = 0;
  size_t addition_col = 0;
  for (size_t i = 0; i < N; ++i) {
    if (i == row) {
      continue;
    }
    addition_col = 0;
    for (size_t j = 0; j < N; ++j) {
      if (j == column) {
        continue;
      }
      addition(addition_row, addition_col) = matrix(i, j) * ((i + j) % 2 == 0 ? 1 : -1);
      ++addition_col;
    }
    ++addition_row;
  }
  return addition;
}

template<class Number>
Number Determinant(const Matrix<Number, 1, 1> &matrix) {
  return matrix(0, 0);
}

template<class Number, size_t N>
Number Determinant(const Matrix<Number, N, N> &matrix) {
  Number determinant = Number();
  for (size_t j = 0; j < N; ++j) {
    Matrix<Number, N - 1, N - 1> addition = GetAlgebraicAddition(matrix, 0, j);
    determinant +=  matrix(0, j) * Determinant(addition);
  }

  return determinant;
}

template<class Number>
Matrix<Number, 1, 1> GetInversed(const Matrix<Number, 1, 1> &matrix) {
  if (matrix(0, 0) == 0) {
    throw MatrixIsDegenerateError();
  }
  Matrix<Number, 1, 1> inversed;
  inversed(0, 0) = 1 / matrix(0, 0);
  return inversed;
}

template<class Number, size_t N>
Matrix<Number, N, N> GetInversed(const Matrix<Number, N, N> &matrix) {
  Number determinant = Determinant(matrix);
  if (determinant == 0) {
    throw MatrixIsDegenerateError();
  }

  Matrix<Number, N, N> inversed;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      inversed(i, j) = Determinant(GetAlgebraicAddition(matrix, i, j)) / (determinant);
    }
  }
  inversed = GetTransposed(inversed);
  return inversed;
}

template<class Number, size_t N>
Matrix<Number, N, N> &Inverse(Matrix<Number, N, N> &matrix) {
  matrix = GetInversed(matrix);
  return matrix;
}

#endif